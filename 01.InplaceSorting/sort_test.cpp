#include <gtest/gtest.h>
#include <vector>


#include "sorting.h"

TEST(BubbleSort, NormalArray)
{
    std::vector<int> arr = {6, 7, 11, 7, 6, -1125, 236325, 0, 0, -1125, 2};
    std::vector<int> expected = {-1125, -1125, 0, 0, 2, 6, 6, 7, 7, 11, 236325};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(BubbleSort, EmptyArray)
{
    std::vector<int> arr = {};
    std::vector<int> expected = {};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(BubbleSort, AlreadySortedArray)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(BubbleSort, ReverseSortedArray)
{
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}


TEST(QuickSort, NormalArray)
{
    std::vector<int> arr = {6, 7, 11, 7, 6, -1125, 236325, 0, 0, -1125, 2};
    std::vector<int> expected = {-1125, -1125, 0, 0, 2, 6, 6, 7, 7, 11, 236325};
    quick_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(QuickSort, EmptyArray)
{
    std::vector<int> arr = {};
    std::vector<int> expected = {};
    quick_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(QuickSort, AlreadySortedArray)
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    quick_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}

TEST(QuickSort, ReverseSortedArray)
{
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    quick_sort(arr.begin(), arr.end());
    EXPECT_EQ(arr, expected);
}