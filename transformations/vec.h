#pragma once

#include <iostream>

struct vec3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    vec3() : x(0.0f), y(0.0f), z(0.0f) { }
    vec3(float x, float y, float z) : x(x), y(y), z(z) { }

    vec3 operator+(const vec3 &other) const;
    vec3 operator-(const vec3 &other) const;
    float operator*(const vec3 &other) const;
    bool operator==(const vec3 &other) const;
    bool operator!=(const vec3 &other) const;

    static vec3 cross(const vec3 &a, const vec3 &b);
};

vec3 operator*(const float k, const vec3& v);
std::ostream& operator<<(std::ostream& stream, const vec3& vec);
