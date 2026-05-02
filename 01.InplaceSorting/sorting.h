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

    for (auto pass = end; pass != begin; --pass)
    {
        for( auto curr = begin; curr != std::prev(pass); ++curr)
        {
            auto next = std::next(curr);
            if( *next < *curr)
            {
                using std::swap;
                swap(*curr, *next);
            }
        }
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    auto n = std::distance(begin, end);
    if (n < 2) return;

    Iterator pivot = end - 1;
    Iterator i = begin;

    for (Iterator j = begin; j != pivot; ++j)
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

    quick_sort(begin, i);
    quick_sort(i + 1, end);
}

#endif // SORTING_H
