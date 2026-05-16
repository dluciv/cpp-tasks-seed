#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <iterator>
#include "collvalue.h"

// Сортировка пузырьком — O(N^2)[cite: 1, 3]
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;[cite: 1]
    for (auto i = begin; i != std::prev(end); ++i) {
        for (auto j = begin; j != std::prev(end, std::distance(begin, i) + 1); ++j) {
            if (*std::next(j) < *j) {[cite: 4]
                std::swap(*j, *std::next(j));[cite: 4]
            }
        }
    }
}

// Быстрая сортировка (QuickSort) — O(N log N)[cite: 1, 3]
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto size = std::distance(begin, end);
    if (size <= 1) return;[cite: 1]

    auto pivot = *std::prev(end); // Выбор опорного элемента
    auto i = begin;
    for (auto j = begin; j != std::prev(end); ++j) {
        if (*j < pivot) {[cite: 4]
            std::swap(*i, *j);[cite: 4]
            ++i;
        }
    }
    std::swap(*i, *std::prev(end));[cite: 4]

    quick_sort(begin, i);
    quick_sort(std::next(i), end);
}

#endif
