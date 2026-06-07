#ifndef SORTING_H
#define SORTING_H

// Header-only

#include "collvalue.h"
#include <iterator>
#include <algorithm>

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    auto n = std::distance(begin, end);
    for (decltype(n) i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        auto left = begin;
        for (decltype(n) j = 0; j < n - 1 - i; ++j)
        {
            auto right = std::next(left);
            if (*right < *left)
            {
                std::iter_swap(left, right);
                swapped = true;
            }
            std::advance(left, 1);
        }
        if (!swapped) break;
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto dist = std::distance(begin, end);
    if (dist <= 1) return;
    auto pivot = std::prev(end);
    Iterator i = begin;
    for (Iterator j = begin; j != pivot; ++j)
    {
        if (*j < *pivot)
        {
            std::iter_swap(i, j);
            ++i;
        }
    }
    std::iter_swap(i, pivot);
    quick_sort(begin, i);
    quick_sort(std::next(i), end);
}

#endif // SORTING_H