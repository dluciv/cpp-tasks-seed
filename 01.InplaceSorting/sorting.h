#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;

    bool swapped = true;
    auto last = end;

    while (swapped)
    {
        swapped = false;
        for (auto it = begin; it != std::prev(last); ++it)
        {
            auto next_it = std::next(it);
            if (*next_it < *it)
            {
                using std::swap;
                swap(*it, *next_it);
                swapped = true;
            }
        }
        --last;
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1) return;

    Iterator pivot_it = std::prev(end);
    Iterator i = begin;

    for (Iterator j = begin; j != pivot_it; ++j)
    {
        if (*j < *pivot_it)
        {
            using std::swap;
            swap(*i, *j);
            ++i;
        }
    }

    using std::swap;
    swap(*i, *pivot_it);

    quick_sort(begin, i);
    quick_sort(std::next(i), end);
}

#endif // SORTING_H