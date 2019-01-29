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

    hit_result trace(const Ray &r, const float t_min, const float t_max) const;

};

