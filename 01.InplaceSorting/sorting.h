#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <cstddef>
#include <utility>

#include "collvalue.h"

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (Iterator last = end; last - begin > 1; --last)
    {
        bool changed = false;

        for (Iterator it = begin; it + 1 < last; ++it)
        {
            if (*(it + 1) < *it)
            {
                std::iter_swap(it, it + 1);
                changed = true;
            }
        }

        if (!changed)
        {
            return;
        }
    }
}

namespace sorting_detail
{
template <typename Iterator>
void quick_sort_impl(Iterator begin, Iterator end, int depth)
{
    while (end - begin > 1)
    {
        if (depth == 0)
        {
            std::make_heap(begin, end);
            std::sort_heap(begin, end);
            return;
        }

        --depth;

        const auto pivot = *(begin + (end - begin) / 2);

        Iterator left = begin;
        Iterator current = begin;
        Iterator right = end;

        while (current < right)
        {
            if (*current < pivot)
            {
                std::iter_swap(left, current);
                ++left;
                ++current;
            }
            else if (pivot < *current)
            {
                --right;
                std::iter_swap(current, right);
            }
            else
            {
                ++current;
            }
        }

        if (left - begin < end - right)
        {
            quick_sort_impl(begin, left, depth);
            begin = right;
        }
        else
        {
            quick_sort_impl(right, end, depth);
            end = left;
        }
    }
}
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    auto count = end - begin;
    int depth = 0;

    while (count > 1)
    {
        depth += 2;
        count /= 2;
    }

    sorting_detail::quick_sort_impl(begin, end, depth);
}

#endif // SORTING_H