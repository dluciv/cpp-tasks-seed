#ifndef SORTING_H
#define SORTING_H

#include "collvalue.h"
#include <iterator>
#include <algorithm>

// Bubble Sort

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator i = begin; i != end; ++i)
    {
        for (Iterator j = begin; std::next(j) != end; ++j)
        {
            Iterator next = std::next(j);

            if (*next < *j)
            {
                std::iter_swap(j, next);
            }
        }
    }
}

// Quick Sort 

template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
    auto pivot = *std::prev(end);

    Iterator i = begin;

    for (Iterator j = begin; j != std::prev(end); ++j)
    {
        if (*j < pivot)
        {
            std::iter_swap(i, j);
            ++i;
        }
    }

    std::iter_swap(i, std::prev(end));

    return i;
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;
    }

    Iterator pivot = partition(begin, end);

    quick_sort(begin, pivot);
    quick_sort(std::next(pivot), end);
}

#endif // SORTING_H 