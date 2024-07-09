#include <iostream>
#include <vector>

template<class T>
using vec = std::vector<T>;

/**
 * @brief Determines if given infinite copies of coins of denominations d, you can make change for the amount k using at most C coins
 * @param d list of coin denominations available
 * @param k amount we want to break into change
 * @param C maximum amount of total coins allowed
 */
bool can_make_change(const vec<int>& d, int k, int C)
{
    
    return true;
}

int main()
{
    vec<int> coins{ 2, 5, 10 };
    int C = 4;
    int k = 25;
    bool cmc = can_make_change(coins, k, C);
    std::cout << "Can make change? " << (cmc ? "Yes" : "No") << std::endl; // should be true (2 + 5 + 10)

    k = 8;
    cmc = can_make_change(coins, k, C);
    std::cout << "Can make change? " << (cmc ? "Yes" : "No") << std::endl; // should be true (2 + 2 + 2 + 2)

    k = 18;
    cmc = can_make_change(coins, k, C);
    std::cout << "Can make change? " << (cmc ? "Yes" : "No") << std::endl; // should be false (10 + 2 + 2 + 2 + 2 requires 5 coins)
}