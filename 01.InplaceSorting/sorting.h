#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (auto it = begin; it != end; ++it) {
        bool swapped = false;
        for (auto it2 = begin; it2 != end - 1; ++it2) {
            if (*(it2 + 1) < *it2) {
                std::swap(*it2, *(it2 + 1));
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin <= 1) return;
    Iterator pivot = begin + (end - begin) / 2;
    std::swap(*pivot, *(end - 1));
    pivot = end - 1;
    Iterator left = begin;
    for (Iterator right = begin; right != pivot; ++right) {
        if (*right < *pivot) {
            std::swap(*left, *right);
            ++left;
        }
    }
    std::swap(*left, *pivot);
    quick_sort(begin, left);
    quick_sort(left + 1, end);
}

#endif // SORTING_H
