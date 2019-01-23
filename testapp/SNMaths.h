#pragma once

#include <stdint.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include "SNRand.h"

class Vector3;
Vector3 operator*(const float f, const Vector3 &v);
Vector3 operator*(const Vector3 &v, const float f);
Vector3 operator/(const Vector3 &v, const float f);

class Vector3 {
public:
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;

    Vector3 operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const Vector3 &other) const {
        return Vector3(x*other.x, y*other.y, z*other.z);
    }

    float dot(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3 &other) const {
        return Vector3(
            y*other.z - z * other.y,
            z*other.x - x * other.z,
            x*other.y - y * other.x
        );
    }

    float length() const {
        return sqrtf(this->dot(*this));
    }

    float length_sq() const {
        return this->dot(*this);
    }

    Vector3 normalized() const {
        float l = 1.0f / length();
        return Vector3(x * l, y * l, z * l);
    }

    Vector3 reflect_on(const Vector3& n) const {
        return -2.0f*dot(n)*n;
    }

    static Vector3 lerp(const Vector3& a, const Vector3& b, const float t) {
        Vector3 diff = b - a;
        return a + Vector3(diff.x*t, diff.y*t, diff.z*t);
    }

    static Vector3 generateRandomUnitVector() {
        Vector3 p { 100.0f, 0.0f, 0.0f };
        Vector3 ones { 1.0f, 1.0f, 1.0f };
        while (p.length_sq() > 1.0f) {
            p = 2.0f*Vector3{ SNRand::getRand(), SNRand::getRand(), SNRand::getRand() } - ones;
        }
        return p;
    }

    static Vector3 generateRandomUnitDisc() {
        Vector3 p{ 100.0f, 0.0f, 0.0f };
        Vector3 ones{ 1.0f, 1.0f, 0.0f };
        while (p.length_sq() > 1.0f) {
            p = 2.0f*Vector3{ SNRand::getRand(), SNRand::getRand(), 0.0f } - ones;
        }
        return p;
    }


    //color

    static uint8_t float_to_byte(float f) { return (uint8_t)(255.99*powf(f,1.0f/2.2f)); }

    uint8_t rByte() { return float_to_byte(x); }
    uint8_t gByte() { return float_to_byte(y); }
    uint8_t bByte() { return float_to_byte(z); }
};

class Ray {
public:
    Ray() : origin(Vector3()), dir(Vector3()) {};
    Ray(const Vector3 &o, const Vector3 &d) : origin(o), dir(d) {};

    Vector3 origin;
    Vector3 dir;

    Vector3 point_at_t(float t) {
        return(origin + t * dir);
    }
};