#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"[cite: 2]

// Проверка Bubble Sort
TEST(SortingTest, BubbleSortCorrectness)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    bubble_sort(data.begin(), data.end());[cite: 1]
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));[cite: 2]
}

// Проверка Quick Sort
TEST(SortingTest, QuickSortCorrectness)
{
    std::vector<int> data = {3, 1, 4, 1, 5, 9};
    quick_sort(data.begin(), data.end());[cite: 1]
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));[cite: 2]
}

// Тест на пустой массив (граничный случай)
TEST(SortingTest, HandlesEmptyRange)
{
    std::vector<int> data = {};
    EXPECT_NO_THROW(bubble_sort(data.begin(), data.end()));[cite: 1]
    EXPECT_NO_THROW(quick_sort(data.begin(), data.end()));[cite: 1]
}
