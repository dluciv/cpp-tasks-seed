#ifndef SORTING_H
#define SORTING_H


#include <algorithm>
#include <iterator>
#include "collvalue.h"

// ----------------------------- Bubble sort --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }
    for (Iterator last = end; last != begin; --last)
    {
        for (Iterator current = begin; std::next(current) != last; ++current)
        {
            Iterator next = std::next(current);
            if (*next < *current)
            {
                using std::swap;
                swap(*current, *next);
            }
        }
    }
}

// --------------------------- Quick sort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin < 2)
    {
        return;
    }
    Iterator pivot_pos = end - 1;
    auto pivot = *pivot_pos;
    Iterator less_equal_end = begin;
    for (Iterator current = begin; current != pivot_pos; ++current)
    {
        if (!(pivot < *current))
        {
            using std::swap;
            swap(*less_equal_end, *current);
            ++less_equal_end;
        }
    }
    using std::swap;
    swap(*less_equal_end, *pivot_pos);
    quick_sort(begin, less_equal_end);
    quick_sort(less_equal_end + 1, end);
}

#endif // SORTING_H