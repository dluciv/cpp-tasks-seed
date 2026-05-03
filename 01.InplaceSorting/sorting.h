#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Insertion sort --------------------------------------
template <typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
    using std::swap;
    for (Iterator i = begin; i != end; i++)
        for (Iterator j = i; j != begin && *j < *(j-1); j--)
            swap(*j, *(j-1));
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin < 2) return;

    using std::swap;
    Iterator base = begin;
    Iterator current = begin + 1;
    Iterator check = end - 1;

    while (current <= check)
    {
        if (*current < *base)
            ++current;
        else
        {
            swap(*current, *check);
            --check;
        }
    }
    swap(*base, *check);
    quick_sort(begin, check);
    quick_sort(check + 1, end);
}

#endif // SORTING_H


