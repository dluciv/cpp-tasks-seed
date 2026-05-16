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
    while (swapped){
        swapped = false;

        Iterator current = begin;
        Iterator next = begin;
        ++next;

        while (next != end){
            if (*next < *current)
            {
                std::swap(*current,*next);
                swapped = true;
            }
            ++current;
            ++next;
        }
        --end;
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;
    Iterator curr = end;
    --curr;
    auto curr_val = *curr;

    Iterator left = begin;
    Iterator right = curr;

    while (left != right){
        while (left != right && *left < curr_val) {
            ++left;
        }
        while (left != right && !(*right < curr_val)){
            --right;
        }
        if (left != right){
        std::swap(*left,*right);
        }
    }
    std::swap(*left,*curr);
    quick_sort(begin, left);
    ++left;
    quick_sort(left, end);
}

#endif // SORTING_H
