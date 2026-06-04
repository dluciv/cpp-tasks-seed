#include <gtest/gtest.h>
#include <vector>
#include "sorting.h"

// Bubble Sort Tests

TEST(BubbleSortSuite, SimpleArray)
{
    std::vector<int> data = { 5, 1, 4, 2, 3 };

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(BubbleSortSuite, EmptyArray)
{
    std::vector<int> data;

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(data.empty());
}

TEST(BubbleSortSuite, OneElement)
{
    std::vector<int> data = { 10 };

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data[0], 10);
}

// Quick Sort Tests

TEST(QuickSortSuite, SimpleArray)
{
    std::vector<int> data = { 9, 7, 5, 3, 1 };

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, (std::vector<int>{1, 3, 5, 7, 9}));
}

TEST(QuickSortSuite, AlreadySorted)
{
    std::vector<int> data = { 1, 2, 3, 4, 5 };

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(QuickSortSuite, Duplicates)
{
    std::vector<int> data = { 3, 1, 2, 1, 3 };

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, (std::vector<int>{1, 1, 2, 3, 3}));
}