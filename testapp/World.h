#pragma once
#include <memory>
#include <vector>

#include "SNMaths.h"
#include "Hitable.h"

class World
{
    std::vector<std::unique_ptr<Hitable>> hitables;

public:
    World();
    ~World();

    hit_result trace(Ray &r, float t_min, float t_max);

};

