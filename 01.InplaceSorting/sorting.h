#ifndef SORTING_H
#define SORTING_H

#include <iterator>
#include <utility>
#include "collvalue.h"

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
  if (begin == end) return;
    
    bool swapped;
    Iterator last = end;
    --last;
    
    do {
        swapped = false;
        for (Iterator it = begin; it != last; ++it) {
            Iterator next = it;
            ++next;
            if (*next < *it) {
                using std::swap;
                swap(*it, *next);
                swapped = true;
            }
        }
        --last;
    } while (swapped);
}

template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
    auto pivot = end;
    --pivot;
    
    Iterator i = begin;
    --i;
    
    for (Iterator j = begin; j != pivot; ++j) {
        if (*j < *pivot) {
            ++i;
            using std::swap;
            swap(*i, *j);
        }
    }
    ++i;
    using std::swap;
    swap(*i, *pivot);
    return i;
}

template <typename Iterator>
void quick_sort_helper(Iterator begin, Iterator end)
{
    if (begin == end) return;
    
    Iterator next = begin;
    ++next;
    if (next == end) return;
    
    Iterator pivot_pos = partition(begin, end);
    
    quick_sort_helper(begin, pivot_pos);
    
    Iterator pivot_next = pivot_pos;
    ++pivot_next;
    quick_sort_helper(pivot_next, end);
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
  quick_sort_helper(begin, end);
}

#endif // SORTING_H
