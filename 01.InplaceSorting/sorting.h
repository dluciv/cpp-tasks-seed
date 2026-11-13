#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <iterator>

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    for (Iterator last = end; last - begin > 1; --last)
    {
        bool swapped = false;

        for (Iterator it = begin; it + 1 < last; ++it)
        {
            if (*(it + 1) < *it)
            {
                std::iter_swap(it, it + 1);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

namespace sorting_detail
{
template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
    using Difference = typename std::iterator_traits<Iterator>::difference_type;
    const Difference count = end - begin;

    auto sift_down = [&](Difference root, Difference length)
    {
        while (root < length / 2)
        {
            Difference child = 2 * root + 1;
            if (child + 1 < length && *(begin + child) < *(begin + child + 1))
            {
                ++child;
            }
            if (!(*(begin + root) < *(begin + child)))
            {
                break;
            }
            std::iter_swap(begin + root, begin + child);
            root = child;
        }
    };

    for (Difference start = count / 2; start > 0; --start)
    {
        sift_down(start - 1, count);
    }

    for (Difference length = count; length > 1; --length)
    {
        std::iter_swap(begin, begin + length - 1);
        sift_down(0, length - 1);
    }
}
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    using Difference = typename std::iterator_traits<Iterator>::difference_type;
    const Difference count = end - begin;
    if (count < 2)
    {
        return;
    }

    int depth_limit = 0;
    for (Difference length = count; length > 1; length /= 2)
    {
        ++depth_limit;
    }
    depth_limit *= 2;

    auto sort_part = [&](auto&& self, Iterator first, Iterator last, int depth) -> void
    {
        while (last - first > 1)
        {
            if (depth == 0)
            {
                sorting_detail::heap_sort(first, last);
                return;
            }
            --depth;