#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"
#include <iterator>

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
        return;

    bool swapped;
    Iterator last = end;

    do
    {
        swapped = false;

        for (Iterator j = begin; std::next(j) != last; ++j)
        {
            Iterator next = std::next(j);

            if (*next < *j)
            {
                std::iter_swap(j, next);
                swapped = true;
            }
        }

        last = std::prev(last);
    }
    while (swapped);
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1)
        return;

    Iterator pivot_it = std::prev(end);
    auto pivot = *pivot_it;

    Iterator middle = begin;

    for (Iterator it = begin; it != pivot_it; ++it)
    {
        if (*it < pivot)
        {
            std::iter_swap(it, middle);
            ++middle;
        }
    }

    std::iter_swap(middle, pivot_it);

    quick_sort(begin, middle);
    quick_sort(std::next(middle), end);
}

#endif // SORTING_H