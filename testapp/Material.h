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
public:
    Dielectric(float ior) : ior(ior) {};

    virtual hit_result scatter(Ray& r_in, Vector3 &pos, Vector3 &normal);
};

