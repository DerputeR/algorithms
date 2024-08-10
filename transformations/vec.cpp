#include "vec.h"

vec3 vec3::operator+(const vec3 &other) const
{
    return vec3{this->x + other.x, this->y + other.y, this->z + other.z};
}

vec3 vec3::operator-(const vec3 &other) const
{
    return vec3{this->x - other.x, this->y - other.y, this->z - other.z};
}

float vec3::operator*(const vec3 &other) const
{
    return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

bool vec3::operator==(const vec3 &other) const
{
    return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
}

bool vec3::operator!=(const vec3 &other) const
{
    return (this->x != other.x) || (this->y != other.y) || (this->z != other.z);
}

vec3 vec3::cross(const vec3 &a, const vec3 &b)
{
    return vec3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

vec3 operator*(const float k, const vec3& v)
{
    return vec3{k * v.x, k * v.y, k * v.z};
}

std::ostream& operator<<(std::ostream& stream, const vec3& vec)
{
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream;
}

int main()
{
    vec3 a = vec3{1, 0, 0};
    vec3 b = vec3{0, 1, 0};
    std::cout << 2 * b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << vec3::cross(a, b) << std::endl;
}