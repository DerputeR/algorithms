#include <iostream>
#include <vector>
#include <string>
#include "common.h"

// Knapsack
// Given n objects with integer weights and values and a total capacity B,
// find a subset S of the objects such that
// 1. The objects fit in the backpack (total weight <= B)
// 2. The total value is maximized
// Versions:
// 1. Without reptition (limited supply of each object)
// 2. With reptition (unlimited supply of each object)

struct item
{
    std::string name;
    int weight;
    int value;
}

std::vector<item> knapsack_v1(const std::vector<item>& items)


int main()
{

}