#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"
#include <iterator>
#include <algorithm>

using namespace std;

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    auto n = distance(begin, end);
    for (decltype(n) i = 0; i < n - 1; ++i) {
        bool swapped = false;
        auto left = begin;
        for (decltype(n) j = 0; j < n - 1 - i; ++j) {
            auto right = next(left);
            if (*right < *left) {
                swap(*left, *right);
                swapped = true;
            }
            advance(left, 1);
        }
        if (!swapped) break;
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto dist = distance(begin, end);
    if (dist <= 1) return;
    auto pivot = prev(end);
    Iterator i = begin;
    for (Iterator j = begin; j != pivot; ++j) {
        if (*j < *pivot) {
            swap(*i, *j);
            ++i;
        }
    }
    swap(*i, *pivot);
    quick_sort(begin, i);
    quick_sort(next(i), end);
}

#endif // SORTING_H
