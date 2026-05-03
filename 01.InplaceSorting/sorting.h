#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
	if (begin == end) return;

	for (Iterator i = begin; i != end; ++i) {
		for (Iterator j = begin; j != end - 1 - i + begin; ++j) {
			if (*(j + 1) < *j) {
				std::swap(*(j + 1), *j);
			}
		}
	}
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
	if (begin == end || begin + 1 == end) return;

	Iterator pivot = end - 1;
	Iterator i = begin;
	for (Iterator j = begin; j != end - 1; ++j) {
		if (*j < *pivot) {
			std::swap(*j, *i);
			++i;
		}
	}
	std::swap(*i, *pivot);
	quick_sort(begin, i);
	quick_sort(i + 1, end);
}

#endif // SORTING_H

