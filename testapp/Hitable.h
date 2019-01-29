#pragma once
#include <memory>

#include "SNMaths.h"
#include "Material.h"

class Material; 

class hit_result {
public:
    bool didHit { false };
    Ray scatter { Ray() };
    Vector3 attenuation { Vector3() };

    hit_result() {};
    hit_result(const bool hit, const Ray &scatter, const Vector3& att) : didHit{ hit }, scatter { scatter }, attenuation{ att } {};
};

class Hitable
{
public:
    Hitable();
    virtual ~Hitable();

    virtual hit_result hitProcess(const Ray &r, float t) const = 0;
    virtual bool hitCheck(const Ray &r, const float t_min, const float t_max, float& t_out) const = 0;
};

class Sphere : public Hitable {
public:
    Sphere(Vector3 p, float r, std::unique_ptr<Material> mat) : pos{ p }, radius(r), material{ std::move(mat) } {};
    virtual ~Sphere() {};

    virtual hit_result hitProcess(const Ray &r, float t) const;
    virtual bool hitCheck(const Ray &r, const float t_min, const float t_max, float& t_out) const;

    Vector3 pos;
    float radius;
    std::unique_ptr<Material> material;
};
