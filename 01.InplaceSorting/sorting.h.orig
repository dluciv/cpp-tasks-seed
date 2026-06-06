#ifndef SORTING_H
#define SORTING_H

#include <iterator>   
#include <algorithm>  
#include <utility>    

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end) {
    if (begin == end) return;

    bool swapped;
    for (auto it_end = end; it_end != begin; --it_end) {
        swapped = false;
        auto current = begin;
        auto next = std::next(current);
        while (next != it_end) {
            if (*next < *current) {
                using std::swap;
                swap(*current, *next);
                swapped = true;
            }
            ++current;
            ++next; 
        }
        if (!swapped) break;
    }
}

// --------------------------- QuickSort ---------------------------------------
namespace detail {
    template <typename Iterator>
    Iterator partition(Iterator begin, Iterator end) {
        if (begin == end) return begin;

        auto pivot = std::prev(end);
        auto i = begin; 
        for (auto j = begin; j != pivot; ++j) {
            if (*j < *pivot) {
                using std::swap;
                swap(*i, *j);
                ++i;
            }
        }
        using std::swap;
        swap(*i, *pivot);
        return i;
    }
} // namespace detail

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end) {
    if (std::distance(begin, end) <= 1) return;

    Iterator pivot_it = detail::partition(begin, end);

    quick_sort(begin, pivot_it);
    quick_sort(std::next(pivot_it), end);
}

#endif // SORTING_H
