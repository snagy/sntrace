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
    hit_result(bool hit, Ray &scatter, Vector3& att) : didHit{ hit }, scatter { scatter }, attenuation{ att } {};
};

class Hitable
{
public:
    Hitable();
    virtual ~Hitable();

    virtual hit_result hitProcess(Ray &r, float t) = 0;
    virtual bool hitCheck(Ray &r, float t_min, float t_max, float& t_out) = 0;
};

class Sphere : public Hitable {
public:
    Sphere(Vector3 p, float r, std::unique_ptr<Material> mat) : pos{ p }, radius(r), material{ std::move(mat) } {};
    virtual ~Sphere() {};

    virtual hit_result hitProcess(Ray &r, float t);
    virtual bool hitCheck(Ray &r, float t_min, float t_max, float& t_out);

    Vector3 pos;
    float radius;
    std::unique_ptr<Material> material;
};
