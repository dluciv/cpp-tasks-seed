#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include "collvalue.h"

// O(N^2) Пузырёк
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;

    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (auto it = begin; it != end - 1; ++it)
        {
            if (*(it + 1) < *it)
            {
                using std::swap;
                swap(*it, *(it + 1));
                swapped = true;
            }
        }
        end--;
    }
}

// Вспомогательная для QuickSort
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
    auto pivot = end - 1;
    auto i = begin;

    for (auto j = begin; j != pivot; ++j)
    {
        if (*j < *pivot)
        {
            using std::swap;
            swap(*i, *j);
            ++i;
        }
    }
    using std::swap;
    swap(*i, *pivot);
    return i;
}

// O(N log N) QuickSort
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1) return;

    Iterator pivot = partition(begin, end);

    quick_sort(begin, pivot);
    quick_sort(pivot + 1, end);
}

#endif
