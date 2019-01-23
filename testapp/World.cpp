#include "stdafx.h"
#include "World.h"

#include "SNRand.h"

World::World()
{
    // ground
    hitables.push_back(std::make_unique<Sphere>(Vector3(1.0f, -1000.0f, 0.0f), 1000.0f,
        std::make_unique<Lambertian>(Lambertian(Vector3(0.4f,0.4f,0.5f)))));

    /*
    const int ball_min = -4;
    const int ball_max = 4;
    for (int i = ball_min; i <= ball_max; i++) {
        for (int j = ball_min; j <= ball_max; j++) {
            float rad = SNRand::getRand() * 0.1f + 0.2f;
            Vector3 center{ float(i)+SNRand::getRand() * 0.9f, rad, float(j)+SNRand::getRand() * 0.9f };
            hitables.push_back(std::make_unique<Sphere>(center, rad, std::make_unique<Lambertian>(Lambertian(Vector3(SNRand::getRand(), SNRand::getRand(), SNRand::getRand())))));
        }
    }
    */

    hitables.push_back(std::make_unique<Sphere>(Vector3(-4.0f, 1.0f, -1.0f), 1.0f, std::make_unique<Lambertian>(Lambertian(Vector3(0.1f, 0.2f, 0.5f)))));
    hitables.push_back(std::make_unique<Sphere>(Vector3(4.0f, 1.0f, -1.0f), 1.0f, std::make_unique<Metallic>(Metallic(Vector3(0.7f, 0.6f, 0.5f),0.1f))));
    hitables.push_back(std::make_unique<Sphere>(Vector3(0.0f, 1.0f, -1.0f), 1.0f, std::make_unique<Lambertian>(Lambertian(Vector3(1.0f, 0.0f, 0.5f)))));
}


World::~World()
{
}

hit_result World::trace(Ray &r, float t_min, float t_max) {
    float t_nearest = std::numeric_limits<float>::max();
    int ix_nearest = -1;
    for (size_t i = 0; i < hitables.size(); i++) {
        auto &x = hitables[i];
        float t_result = 0.0f;
        if (x->hitCheck(r, t_min, t_max, t_result) && t_result < t_nearest) {
            t_nearest = t_result;
            ix_nearest = i;
        }
    }
    
    if (ix_nearest != -1) {
        auto& x = hitables[ix_nearest];

        return x->hitProcess(r,t_nearest);
    }
    return hit_result();
}