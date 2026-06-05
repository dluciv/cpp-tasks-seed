#ifndef SORTING_H
#define SORTING_H

#include "collvalue.h"  // Для swap

// --- Bubble Sort ---
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;

    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        Iterator current = begin;
        Iterator next = std::next(current);

        while (next != end)
        {
            if (*next < *current)
            {
                using std::swap;
                swap(*current, *next);
                swapped = true;
            }
            current = next;
            ++next;
        }
        --end;
    }
}


// --- Heap Sort ---
template <typename Iterator>
void heapify(Iterator begin, size_t n, size_t i)
{
    size_t largest = i, left = 2*i+1, right = 2*i+2;

    if (left < n && *(begin + largest) < *(begin + left))
        largest = left;

    if (right < n && *(begin + largest) < *(begin + right))
        largest = right;

    if (largest != i)
    {
        using std::swap;
        swap(*(begin + i), *(begin + largest));
        heapify(begin, n, largest);
    }
}

template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
    size_t n = std::distance(begin, end);
    if (n <= 1)
    {
        return;
    }

    for (int i = (int)n/2-1; i >= 0; --i)
    {
        heapify(begin, n, i);
    }

    for (int i = (int)n-1; i > 0; --i)
    {
        using std::swap;
        swap(*begin, *(begin + i));
        heapify(begin, i, 0);
    }
}

#endif // SORTING_H