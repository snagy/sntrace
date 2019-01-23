#pragma once
#include <random>

namespace SNRand
{
    static std::mt19937 mt;
    static std::uniform_real_distribution<float> dist;

    static void initRand() {
        std::random_device rd;
        mt = std::mt19937{ rd() };
        dist = std::uniform_real_distribution<float>{ 0.0f, 1.0f };
    }

    static float getRand() {
        return dist(mt);
    };
};

