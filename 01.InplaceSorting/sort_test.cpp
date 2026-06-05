#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

// Тестируем Bubble Sort
TEST(SortSuite, BubbleSortTest)
{
    std::vector<int> arr = {5, 2, 9, 1, 5, 6};
    std::vector<int> expected = {1, 2, 5, 5, 6, 9};

    bubble_sort(arr.begin(), arr.end());

    EXPECT_EQ(arr, expected);
}

TEST(SortSuite, BubbleSortEmptyTest)
{
    std::vector<int> arr = {};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_TRUE(arr.empty());
}

// Тестируем Quick Sort
TEST(SortSuite, QuickSortTest)
{
    std::vector<int> arr = {10, -3, 21, 0, 0, 5};
    std::vector<int> expected = {-3, 0, 0, 5, 10, 21};

    quick_sort(arr.begin(), arr.end());

    EXPECT_EQ(arr, expected);
}

TEST(SortSuite, QuickSortSortedTest)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    quick_sort(arr.begin(), arr.end());
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}