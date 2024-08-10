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
    float newX = w*other.x + x*other.w + y*other.z - z*other.x;
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
    std::cout << vec3::cross(v_a, v_b) << "\n";
    // float expectedW = a.w * b.w - (v_a * v_b);
    // vec3 expectedV = b.w * v_a + a.w * v_b + vec3::cross(v_a, v_b);
    // std::cout << "Expected result:" << "(" << expectedW << ", " << expectedV.x << ", " << expectedV.y << ", " << expectedV.z << ")\n";
    std::cout << "Actual result:" << a * b << "\n";
    std::cout << std::endl;
}
