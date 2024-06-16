#include <iostream>
#include <vector>
#include "../common.h"

// Longest Increasing Subsequence (LIS)
// Given n numbers/chars, the goal is to figure out the length of the LIS
// of these numbers/chars, then return the actual LIS

/**
 * @brief Dynamic programming step for the LIS algorithm.
 * Runtime: O(n^2)
 * @tparam a Character type (int or char, or another type that supports comparison operators)
 * @param A Input list of characters
 * @return List of lengths of the LIS that end with the ith character in the input A
 */
template <typename a>
std::vector<int> lis_lengths(const std::vector<a> &A)
{
    // create list for lengths of LIS ending with a_i
    std::vector<int> L(A.size(), 1);
    for (int i = 1; i < A.size(); i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (A[j] < A[i] && L[i] < 1 + L[j])
            {
                // L[i] is 1 + the longest length of the LIS that can have some A[j] appended to it
                L[i] = 1 + L[j];
            }
        }
    }
    return L;
}

/**
 * @brief Return a list containing the characters of the LIS of a given input.
 * Runtime: O(n) without recomputing lengths, O(n^2) if so
 * @tparam a Character type (int or char, or another type that supports comparison operators)
 * @param A Input list of characters
 * @param lengths_ptr If lis_lengths was run separately, we can use this result here instead of regenerating it
 * @return The (first) LIS of the given input
 */
template <typename a>
std::vector<a> lis(const std::vector<a> &A, const std::vector<a>* lengths_ptr = nullptr)
{
    std::vector<int> L;
    if (lengths_ptr == nullptr)
    {
        L = lis_lengths(A);
    }
    else
    {
        L = *lengths_ptr;
    }

    // determine the index of the longest length in L
    int max_index = 0;
    for (int i = 1; i < L.size(); i++)
    {
        if (L[i] > L[max_index])
        {
            max_index = i;
        }
    }

    // using max_index, trace backwards to generate the LIS
    std::vector<a> lis_vec(L[max_index], 0);
    size_t vec_index = lis_vec.size() - 1;
    lis_vec[vec_index] = A[max_index];
    vec_index--;
    for (int j = max_index - 1; j >= 0; j--)
    {
        if (L[j] == L[max_index] - 1)
        {
            max_index = j;
            lis_vec[vec_index] = A[j];
            vec_index--;
        }

    }
    return lis_vec;
}

/**
 * @brief Non-templated version of the complete LIS algorithm.
 * Runtime: O(n^2)
 * @param A input list of characters/numbers
 * @return List containing the longest increasing subsequence from `A`
 */
std::vector<int> lis(const std::vector<int> &A) {
    /* create list L where each element L[i] 
    is the length of the LIS ending with A[i] */
    std::vector<int> L(A.size(), 1);
    for (int i = 1; i < A.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (A[j] < A[i] && L[i] < 1 + L[j]) {
                /* L[i] is 1 + the length of the longest LIS
                that can have some A[j] appended to it */
                L[i] = 1 + L[j];
            }
        }
    }
    // determine the index of the longest length in L
    int max_index = 0;
    for (int i = 1; i < L.size(); i++) {
        if (L[i] > L[max_index]) {
            max_index = i;
        }
    }
    // using max_index, trace backwards to generate the LIS
    std::vector<int> lis_vec(L[max_index], 0);
    size_t vec_index = lis_vec.size() - 1;
    lis_vec[vec_index] = A[max_index];
    vec_index--;
    for (int j = max_index - 1; j >= 0; j--) {
        if (L[j] == L[max_index] - 1) {
            max_index = j;
            lis_vec[vec_index] = A[j];
            vec_index--;
        }
    }
    return lis_vec;
}

int main()
{
    std::vector<int> input{5, 7, 4, -3, 9, 1, 10, 4, 5, 8, 9, 3};
    std::vector<int> lengths = lis_lengths(input);
    std::vector<int> output = lis(input, &lengths);
    // std::vector<int> output = lis(input);

    std::cout << "Lengths: ";
    print_vec(lengths);
    std::cout << "LIS: ";
    print_vec(output);
}