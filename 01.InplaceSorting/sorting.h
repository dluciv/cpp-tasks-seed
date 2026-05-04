#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// Добавляем нужные библиотеки стандартной библиотеки
#include <algorithm> // для std::iter_swap
#include <iterator>  // для std::next, std::prev, std::distance

// ----------------------------- Пузырёк (O(N^2)) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end) return;

    for (Iterator i = begin; i != end; ++i) {
        Iterator j = begin;
        // Проходим до предпоследнего элемента
        while (std::next(j) != end) {
            if (*j > *std::next(j)) {
                std::iter_swap(j, std::next(j));
            }
            ++j;
        }
    }
}

// Вспомогательная функция разделения для QuickSort
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end) {
    // Выбираем опорный элемент (pivot) - последний
    auto pivot = std::prev(end);
    auto i = begin;

    for (auto j = begin; j != pivot; ++j) {
        // Если элемент меньше пивота, меняем с i
        if (*j < *pivot) {
            std::iter_swap(i, j);
            ++i;
        }
    }
    // Ставим пивот на его место
    std::iter_swap(i, pivot);
    return i;
}

// --------------------------- QuickSort (O(N log N)) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1) return;

    // Получаем позицию пивота
    Iterator p = partition(begin, end);
    
    // Сортируем левую и правую части
    quick_sort(begin, p);
    quick_sort(std::next(p), end);
}

#endif // SORTING_H