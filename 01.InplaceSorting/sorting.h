#ifndef SORTING_H
#define SORTING_H

// Header-only

#include <algorithm>
#include <iterator>
#include <utility>
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator last = end; last != begin; --last)
    {
        bool swapped = false;
        for (Iterator it = begin; std::next(it) != last; ++it)
        {
            Iterator next = std::next(it);
            if (*next < *it)
            {
                std::iter_swap(it, next);
                swapped = true;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;
    }

    auto pivot = *std::next(begin, std::distance(begin, end) / 2);

    Iterator middle1 = std::partition(begin, end, [&](const auto& value)
    {
        return value < pivot;
    });

    Iterator middle2 = std::partition(middle1, end, [&](const auto& value)
    {
        return !(pivot < value);
    });

    quick_sort(begin, middle1);
    quick_sort(middle2, end);
}

#endif // SORTING_H
