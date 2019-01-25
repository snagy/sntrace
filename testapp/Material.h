#pragma once
#include "SNMaths.h"
#include "Hitable.h"

class hit_result;

class Material
{
public:
    Material() {};
    virtual ~Material() {};

    virtual hit_result scatter(Ray& r_in, Vector3 &pos, Vector3 &normal) = 0;
};

class Lambertian : public Material
{
    Vector3 albedo{ Vector3() };
public:
    Lambertian(Vector3& color) : albedo{ color } {};

    virtual hit_result scatter(Ray& r_in, Vector3 &pos, Vector3 &normal);
};

class Metallic : public Material
{
    Vector3 albedo{ Vector3() };
    float roughness;
public:
    Metallic(Vector3& color, float roughness) : albedo{ color }, roughness(roughness) {};

    virtual hit_result scatter(Ray& r_in, Vector3 &pos, Vector3 &normal);
};

class Dielectric : public Material
{
    float ior;

    static float schlick(const float cosine, const float ior) {
        float r0 = (1.0f - ior) / (1.0f + ior);
        r0 *= r0;
        return r0 + (1.0f - r0)*pow((1.0f - cosine), 5);
    }

public:
    Dielectric(float ior) : ior(ior) {};

    virtual hit_result scatter(Ray& r_in, Vector3 &pos, Vector3 &normal);
};

