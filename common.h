#pragma once
#include <numbers>
#include <vector>

constexpr double pi = 3.14159265358979323846;

template <typename a>
void print_vec(const std::vector<a> &v)
{
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i];
        if (i + 1 < v.size())
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

constexpr double DEG_TO_RAD = pi / 180.0;
constexpr double RAD_TO_DEG = 180.0 / pi;