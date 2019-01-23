#pragma once


class Camera {
public:
    Camera(const Vector3 &look_from, const Vector3& look_at, const Vector3& up, float fov, float aspect_ratio, float aperture, float focal_dist) {
        lens_radius = aperture / 2.0f;
        float theta = fov * float(M_PI) / 180.0f;
        float half_height = tanf(theta / 2.0f);
        float half_width = aspect_ratio * half_height;

        w = (look_from - look_at).normalized();
        u = up.cross(w).normalized();
        v = w.cross(u);

        origin = look_from;
        lower_left_corner = -half_width * focal_dist*u - half_height * focal_dist*v - focal_dist * w;
        horizontal = 2.0f*half_width*focal_dist*u;
        vertical = 2.0f*half_height*focal_dist*v;
    }

    Ray getRay(float s, float t) const {
        Vector3 rd = lens_radius * Vector3(1.0f,1.0f,0.0f);// *Vector3::generateRandomUnitDisc();
        Vector3 jitter = u * rd.x + v * rd.y;
        return Ray(origin + jitter, lower_left_corner + horizontal * s + vertical * t - jitter);
    }

    Vector3 origin;
    Vector3 lower_left_corner;
    Vector3 horizontal;
    Vector3 vertical;

    Vector3 u;
    Vector3 v;
    Vector3 w;

    float lens_radius;
};
