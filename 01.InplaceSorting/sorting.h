#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>
#include "collvalue.h"

using namespace std;


// Пузырьковая сортировка O(N^2)
// идёт по массиву и меняет соседние элементы местами,если они стоят в неправильном порядке
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    bool was_swap = true;

    while (was_swap)
    {
        was_swap = false;

        Iterator current = begin;
        Iterator next = current;
        ++next;

        Iterator last_changed = end;

        while (next != end)
        {
            if (*next < *current)
            {
                using std::swap;
                swap(*current, *next);

                was_swap = true;
                last_changed = next;
            }

            current = next;
            ++next;
        }

        // всё  то, что правее последней перестановки, уже стоит нормальн,
        // так пузырёк чуть меньше делает лишних проходов
        if (was_swap)
        {
            end = last_changed;
        }
    }
}


// Быстрая сортировка  O(N log N)
// тут используется разделение на 3 части: меньше опорного элемента, равные ему и больше него
template <typename Iterator>
void quick_sort_impl(Iterator begin, Iterator end)
{
    auto size = end - begin;

    if (size <= 1)
    {
        return;
    }

    Iterator middle = begin + size / 2;
    auto pivot = *middle;

    Iterator left = begin;
    Iterator current = begin;
    Iterator right = end;

    while (current < right)
    {
        if (*current < pivot)
        {
            using std::swap;
            swap(*left, *current);

            ++left;
            ++current;
        }
        else if (pivot < *current)
        {
            --right;

            using std::swap;
            swap(*current, *right);
        }
        else
        {
            ++current;
        }
    }

    quick_sort_impl(begin, left);
    quick_sort_impl(right, end);
}

// -----------Быстрая сортировка 
// Это алгоритм за O(N log N) в среднем случае.
// Сортировка делается на месте, то есть новый массив не создаётся.
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    quick_sort_impl(begin, end);
}

#endif // SORTING_H
