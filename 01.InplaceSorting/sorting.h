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
    
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        Iterator i = begin;
        Iterator next = std::next(begin);
        
        while (next != end)
        {
            if (*next < *i)
            {
                using std::swap;
                swap(*i, *next);
                swapped = true;
            }
            ++i;
            ++next;
        }
        --end;
    }
}
// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end || std::distance(begin, end) <= 1) return;
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
