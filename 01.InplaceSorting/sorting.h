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
    for (Iterator outer = begin; outer != end; ++outer) {
        for (Iterator inner = begin; inner != end - 1 - (outer - begin); ++inner) {
            if (*inner > *(inner + 1)) {
                std::swap(*(inner + 1), *inner);
            }
        }
    }
}


// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    if (begin + 1 == end) return;
    
    Iterator pivot = end;
    --pivot;
    
    Iterator border = begin;
    
    for (Iterator current = begin; current != pivot; ++current) {
        if (*current < *pivot) {
            std::swap(*current, *border);
            ++border;
        }
    }
    
    std::swap(*border, *pivot);
    quick_sort(begin, border);
    quick_sort(border + 1, end);
}

#endif // SORTING_H
