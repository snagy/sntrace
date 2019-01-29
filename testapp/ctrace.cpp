// testapp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdint.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <array>
#include <future>
#include <chrono>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include "SNRand.h"
#include "SNMaths.h"
#include "World.h"
#include "Camera.h"

Vector3 get_color(World &world, Ray &r, int bounce) {
    if (bounce > 50) {
        return Vector3(1.0f,1.0f,1.0f);
    }

    auto result = world.trace(r, 0.001f, 100000.0f);
    if (result.didHit) {
        return result.attenuation * get_color(world, result.scatter, bounce + 1);
    }
    else {
        //fake sky
        Vector3 dir_norm = r.dir.normalized();
        float t = 0.5f*(dir_norm.y + 1.0f);
        return Vector3::lerp(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.5f, 0.7f, 1.0f), t);
    }
}

int main()
{
    // Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    SNRand::initRand();

    World world;
    const int width = 640;
    const int height = 480;
    const int numChannels = 3;

    const int num_samples = 150;

    std::vector<uint8_t> outColors(width * height * numChannels);

    const Vector3 look_from = Vector3(7.0f, 2.0f, 2.0f);
    const Vector3 look_at = Vector3(0.0f, 0.0f, 0.0f);
    const float focal_dist = (look_from - look_at).length();
    Camera cam = Camera(look_from, look_at, Vector3(0.0f, 1.0f, 0.0f), 40.0f, float(width) / float(height), 0.3f, focal_dist);

    std::vector<std::future<void>> futures;

    auto lamb = [&outColors, &cam, &world, width, height, num_samples](int j) {
        for (int i = 0; i < width; i++) {

            Vector3 c = Vector3();
            for (int k = 0; k < num_samples; k++) {
                float u = (float(i) + SNRand::getRand()) / float(width);
                float v = (float(j) + SNRand::getRand()) / float(height);
                //float u = (float(i)) / float(width);
                //float v = (float(j)) / float(height);
                Ray r = cam.getRay(u, v);
                c = c + get_color(world, r, 0);
            }

            c = c * (1.0f / float(num_samples));
            int iColor = ((height - j - 1)*width + i) * 3;
            outColors[iColor + 0] = c.rByte();
            outColors[iColor + 1] = c.gByte();
            outColors[iColor + 2] = c.bByte();
        }
    };

    for (int j = 0; j < height; j++) {
        futures.push_back(std::async(lamb, j));
    }
    
    for (auto &f : futures) {
        f.wait();
    }

    auto finish_trace = std::chrono::high_resolution_clock::now();

    stbi_write_bmp("out.bmp", width, height, numChannels, outColors.data());

    auto finish_write = std::chrono::high_resolution_clock::now();

    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(finish_write - start_time).count() <<
        " (tracing took: " << std::chrono::duration_cast<std::chrono::duration<double>>(finish_trace - start_time).count() << ")\n";
}

