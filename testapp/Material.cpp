#include "stdafx.h"
#include "Material.h"
#include "SNRand.h"

hit_result Lambertian::scatter(const Ray& r_in, const Vector3 &pos, const Vector3 &normal) const
{
    Vector3 target = pos + normal +Vector3::generateRandomUnitVector();
    Ray scattered = Ray{ pos, target - pos };
    return hit_result{ true, scattered, albedo };
}

hit_result Metallic::scatter(const Ray& r_in, const Vector3 &pos, const Vector3 &normal) const
{
    Vector3 reflected_vec = r_in.dir.normalized().reflect_on(normal);
    Ray scattered = Ray{ pos, reflected_vec + Vector3::generateRandomUnitVector()*roughness };
    return hit_result{ normal.dot(scattered.dir) > 0.0f, scattered, albedo };
}

hit_result Dielectric::scatter(const Ray& r_in, const Vector3 &pos, const Vector3 &normal) const
{
    Vector3 attenuation { 1.0f, 1.0f, 1.0 };
    Vector3 reflected = r_in.dir.reflect_on(normal);
    bool facing = r_in.dir.dot(normal) > 0.0f;

    float ni_over_nt = facing?ior:(1.0f / ior);
    Vector3 outward_normal = facing ? (normal * -1.0f) : normal;

    float cosine = facing ? (ior * r_in.dir.dot(normal) / r_in.dir.length()) : (-r_in.dir.dot(normal) / r_in.dir.length());

    Vector3 refraction;

    float reflect_probability = r_in.dir.refract(outward_normal, ni_over_nt, refraction) ? Dielectric::schlick(cosine, ior) : 1.0f;

    if ( SNRand::getRand() < reflect_probability ) {
        return hit_result{ true, Ray {pos, reflected}, attenuation };
    }
    return hit_result{ true, Ray{ pos, refraction }, attenuation };
}