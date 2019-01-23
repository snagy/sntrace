#include "stdafx.h"
#include "Hitable.h"


Hitable::Hitable()
{
}


Hitable::~Hitable()
{
}

hit_result Sphere::hitProcess(Ray &r, float t)
{
    Vector3 hit_pos = r.point_at_t(t);
    Vector3 hit_normal = (hit_pos - pos) / radius;

    return material->scatter(r,hit_pos,hit_normal);
}

bool Sphere::hitCheck(Ray &r, float t_min, float t_max, float &t_out)
{
    Vector3 oc = r.origin - pos;

    float a = r.dir.dot(r.dir);
    float b = oc.dot(r.dir);
    float c = oc.dot(oc) - radius*radius;

    float discriminant = b * b - a * c;

    if(discriminant > 0.0f) {
        float sqrtD = sqrtf(discriminant);
        float t = (-b - sqrtD) / a;
        if (t > t_min && t < t_max) {
            t_out = t;
            return true;
        }

        float t2 = (-b + sqrtD) / a;
        if (t2 > t_min && t2 < t_max) {
            t_out = t2;
            return true;
        }
    }

    return false;
}