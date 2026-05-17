#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    for (Iterator i = begin; i != end; ++i)
    {
        bool is_swapped = false;
        for (auto j = begin; j != end - 1 - (i - begin); ++j)
        {
            Iterator next = j + 1;
            if (*next < *j)
            {
                std::swap(*j, *next);
                is_swapped = true;
            }
        }
        if (!is_swapped) break;
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1) return;
    auto pivot = *std::prev(end);
    Iterator i = begin;
    
    for (Iterator j = begin; j != std::prev(end); ++j)
    {
        if (*j < pivot)
        {
            std::swap(*i, *j);
            ++i;
        }
    }
    
    std::swap(*i, *std::prev(end));
    quick_sort(begin, i);
    quick_sort(std::next(i), end);
}

#endif // SORTING_H
