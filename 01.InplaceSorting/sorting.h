#ifndef SORTING_H
#define SORTING_H


#include "collvalue.h"
#include <algorithm>

// Пузырёк 
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    
    bool swapped;
    for (auto last = end; last != begin; --last)
    {
        swapped = false;
        for (auto it = begin; it + 1 != last; ++it)
        {
            if (*(it + 1) < *it)
            {
                std::iter_swap(it, it + 1);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// QuickSort
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin <= 1) return;
    
    Iterator pivot = begin + (end - begin) / 2;
    Iterator i = begin;
    
    std::iter_swap(pivot, end - 1);
    pivot = end - 1;
    
    for (Iterator j = begin; j < pivot; ++j)
    {
        if (*j < *pivot)
        {
            std::iter_swap(i, j);
            ++i;
        }
    }
    
    std::iter_swap(i, pivot);
    
    quick_sort(begin, i);
    quick_sort(i + 1, end);
}

#endif 
