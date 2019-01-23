#include "stdafx.h"
#include "SNMaths.h"


Vector3 operator*(const float f, const Vector3 &v) {
    return Vector3(f*v.x, f*v.y, f*v.z);
}

Vector3 operator*(const Vector3 &v, const float f) {
    return f * v;
}

Vector3 operator/(const Vector3 &v, const float f) {
    return Vector3(v.x / f, v.y / f, v.z / f);
}