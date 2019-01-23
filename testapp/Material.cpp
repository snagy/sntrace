#include "stdafx.h"
#include "Material.h"

hit_result Lambertian::scatter(Ray& r_in, Vector3 &pos, Vector3 &normal)
{
    Vector3 target = pos + normal +Vector3::generateRandomUnitVector();
    Ray scattered = Ray{ pos, target - pos };
    return hit_result{ true, scattered, albedo };
}

hit_result Metallic::scatter(Ray& r_in, Vector3 &pos, Vector3 &normal)
{
    Vector3 reflected_vec = r_in.dir.normalized().reflect_on(normal);
    Ray scattered = Ray{ pos, reflected_vec + Vector3::generateRandomUnitVector()*roughness };
    return hit_result{ normal.dot(scattered.dir) > 0.0f, scattered, albedo };
}

hit_result Dielectric::scatter(Ray& r_in, Vector3 &pos, Vector3 &normal)
{
    // todo implement
    return hit_result{ true, Ray{pos,normal}, Vector3(ior,ior,ior) };
}