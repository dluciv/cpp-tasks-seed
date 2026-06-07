#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (auto i = begin; i != end; ++i)
    {
        for (auto j = begin; j + 1 != end; ++j)
        {
            if (*(j + 1) < *j)
            {
                auto t = *j;
                *j = *(j + 1);
                *(j + 1) = t;
            }
        }
        --end;
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (end - begin <= 1)
        return;

    auto left = begin;
    auto right = end - 1;
    auto pivot = *(begin + (end - begin) / 2);

    while (left <= right)
    {
        while (*left < pivot)
            left++;
        while (*right > pivot)
            right--;

        if (left <= right)
        {
            auto t = *left;
            *left = *right;
            *right = t;
            left++;
            right--;
        }
    }

    if (begin < right)
        quick_sort(begin, right + 1);

    if (left < end)
        quick_sort(left, end);
}

#endif // SORTING_H
