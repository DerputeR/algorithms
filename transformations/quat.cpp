#include "quat.h"
#include "../common.h"
#include <cmath>

quat::quat(float rads, const vec3 &axis)
{
    w = cos(rads / 2.0);
    double s = sin(rads / 2.0);
    x = s * axis.x;
    y = s * axis.y;
    z = s * axis.z;
}

quat quat::operator*(const quat &other) const
{
    float newW = w*other.w - x*other.x - y*other.y - z*other.z;
    float newX = w*other.x + x*other.w + y*other.z - z*other.y;
    float newY = w*other.y - x*other.z + y*other.w + z*other.x;
    float newZ = w*other.z + x*other.y - y*other.x + z*other.w;
    return quat{newW, newX, newY, newZ};
}

quat quat::inverse() const
{
    return quat{w, -x, -y, -z};
}

std::ostream &operator<<(std::ostream &stream, const quat &q)
{
    stream << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
    return stream;
}

vec3 operator*(const quat &q, const vec3 &v)
{
    quat p{0, v.x, v.y, v.z};
    quat p_prime = q * p * q.inverse();
    return vec3{p_prime.x, p_prime.y, p_prime.z};
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << "Rotating 0 degrees around (1, 0, 0) :" << quat(0, vec3{1, 0, 0}) << '\n';
    std::cout << "Rotating 90 degrees around (1, 0, 0) :" << quat(90 * DEG_TO_RAD, vec3{1, 0, 0}) << '\n';
    std::cout << "Rotating 180 degrees around (1, 0, 0) :" << quat(180 * DEG_TO_RAD, vec3{1, 0, 0}) << '\n';
    std::cout << std::endl;
    std::cout << "Rotating 90 degrees around (0, 1, 0) :" << quat(90 * DEG_TO_RAD, vec3{0, 1, 0}) << '\n';
    std::cout << "Rotating 180 degrees around (0, 1, 0) :" << quat(180 * DEG_TO_RAD, vec3{0, 1, 0}) << '\n';
    std::cout << std::endl;
    std::cout << "Multiplying two quaternions together:" << '\n';
    quat a = quat(90 * DEG_TO_RAD, vec3{0, 1, 0});
    quat b = quat(90 * DEG_TO_RAD, vec3{1, 0, 0});
    vec3 v_a = vec3{a.x, a.y, a.z};
    vec3 v_b = vec3{b.x, b.y, b.z};
    float expectedW = a.w * b.w - (v_a * v_b);
    vec3 expectedV = b.w * v_a + a.w * v_b + vec3::cross(v_a, v_b);
    std::cout << "Expected result:" << "(" << expectedW << ", " << expectedV.x << ", " << expectedV.y << ", " << expectedV.z << ")\n";
    std::cout << "Actual result:" << a * b << "\n";
    std::cout << std::endl;
    std::cout << "Inverse quaternions and rotating vectors:" << '\n';
    std::cout << "Original: " << a << "\n";
    std::cout << "Inverse: " << a.inverse() << "\n";
    vec3 v{0, 0, 1};
    std::cout << "Original vec: " << v << "\n";
    quat q{45 * DEG_TO_RAD, vec3{1, 0, 0}};
    quat q2{90 * DEG_TO_RAD, vec3{1, 0, 0}};
    std::cout << "Rotated vec 45 degrees about (1, 0, 0): " << q * v << "\n";
    std::cout << "Rotated vec 90 degrees about (1, 0, 0): " << q2 * v << "\n";

    std::cout << std::endl;
    // sanity check against https://www.youtube.com/watch?v=Ne3RNhEVSIE&list=PLW3Zl3wyJwWOpdhYedlD-yCB7WQoHf-My&index=35
    quat q01 = quat{90 * DEG_TO_RAD, vec3{0, 1, 0}};
    quat q02 = quat{45 * DEG_TO_RAD, vec3{1, 0, 0}};
    quat q03 = q02 * q01;
    std::cout << "Quaternion 1: " << q01 << "\n";
    std::cout << "Quaternion 2: " << q02 << "\n";
    std::cout << "Quaternion 3 = q02 * q01: " << q03 << "\n";
    std::cout << "Rotating (1, 0, 0) with q3: " << q03 * vec3{1, 0, 0} << "\n";
}
