#pragma once
#include "vec.h"

struct quat
{
    float w = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    quat(float w, float x, float y, float z) : w{w}, x{x}, y{y}, z{z} {}
    quat(float rads, const vec3 &axis);

    quat operator*(const quat &other) const;
    quat inverse() const;
};

std::ostream& operator<<(std::ostream& stream, const quat& q);