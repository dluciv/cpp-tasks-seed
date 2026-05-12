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
	
	bool swapped;
	for (auto last = end; last != begin; --last)
	{
		swapped = false;
		for (auto it = begin; it != last - 1; ++it)
		{
			if (*(it+1) < *it)
				{
				std::swap(*it, *(it+1));
				swapped = true;
				}
		}
	if (!swapped) break;
}

}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
	if (end - begin <= 1) return;

	Iterator pivot = begin + (end - begin) / 2;
	std::swap(*pivot, *(end - 1));
    	pivot = end - 1;

	Iterator left = begin;

	for (Iterator right = begin; right != pivot; ++right)
	{
        	if (*right < *pivot)
		{
			std::swap(*left, *right);
			++left;
		}
	}

	std::swap(*left, *pivot);

	quick_sort(begin, left);
	quick_sort(left + 1, end);
}

#endif // SORTING_H
