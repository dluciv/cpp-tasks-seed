#ifndef SORTING_H
#define SORTING_H
#include <utility>
// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    int len_a = end - begin;

    for (int i = 0; i < len_a - 1; i++)
    {
        bool flag = false;

        for (int j = 0; j < len_a - i - 1; j++)
        {
            if (*(begin + j + 1) < *(begin + j))
            {
                using std::swap;
                swap(*(begin + j), *(begin + j + 1));

                flag = true;
            }
        }

        if (!flag)
        {
            break;
        }
    }
}

template <typename Iterator>
void to_heap(Iterator begin, int work_space, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < work_space && *(begin + largest) < *(begin + left))
    {
        largest = left;
    }

    if (right < work_space && *(begin + largest) < *(begin + right))
    {
        largest = right;
    }

    if (largest != i)
    {
        using std::swap;
        swap(*(begin + i), *(begin + largest));
        to_heap(begin, work_space, largest);
    }
}


//тут реализована heap sort, но чтобы не менять везде названия, я не переименовывал функцию
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    int len_a = end - begin;

    for (int i = len_a / 2 - 1; i >= 0; i--)
    {
        to_heap(begin, len_a, i);
    }

    for (int i = len_a - 1; i > 0; i--)
    {
        using std::swap;
        swap(*begin, *(begin + i));
        to_heap(begin, i, 0);
    }
}

#endif