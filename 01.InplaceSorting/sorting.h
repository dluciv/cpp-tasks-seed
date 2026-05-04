#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

#include <utility>
#include <iterator>


// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    for (Iterator i = begin; i != end; ++i) {
        Iterator j = begin;
        Iterator next = begin;
        ++next;
        while (next != end) {
            if (*next < *j) {
                std::swap(*j, *next);
            }
            ++j;
            ++next;
        }
    }
}


// --------------------------- QuickSort  ---------------------------------------
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
    auto pivot = *begin;
    Iterator left = begin;
    ++left;
    Iterator right = end;
    --right;

    while (true)
    {
        while (left <= right && !(pivot < *left)) ++left;
        while (left <= right && pivot < *right) --right;
        if (left < right)
            std::swap(*left, *right);
        else
            break;
    }
    std::swap(*begin, *right);
    return right;
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    if (std::distance(begin, end) <= 1) return;

    Iterator p = partition(begin, end);
    quick_sort(begin, p);
    quick_sort(p + 1, end);
}

#endif // SORTING_H