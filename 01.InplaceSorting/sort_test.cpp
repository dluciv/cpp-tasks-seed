#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include "sorting.h"

// Тесты для bubble_sort
TEST(BubbleSortTest, EmptyArray)
{
    std::vector<int> data = {};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSortTest, SingleElement)
{
    std::vector<int> data = {42};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data[0], 42);
}

TEST(BubbleSortTest, SortedArray)
{
    std::vector<int> data = {1, 2, 3, 4, 5};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, ReverseSortedArray)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, RandomArray)
{
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {11, 12, 22, 25, 34, 64, 90}));
}

TEST(BubbleSortTest, WithDuplicates)
{
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 1, 2, 3, 4, 5, 5, 6, 9}));
}

TEST(BubbleSortTest, LargeArray)
{
    std::vector<int> data(1000);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    for (size_t i = 0; i < data.size(); ++i)
    {
        EXPECT_EQ(data[i], static_cast<int>(i));
    }
}

// Тесты для quick_sort
TEST(QuickSortTest, EmptyArray)
{
    std::vector<int> data = {};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSortTest, SingleElement)
{
    std::vector<int> data = {42};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data[0], 42);
}

TEST(QuickSortTest, SortedArray)
{
    std::vector<int> data = {1, 2, 3, 4, 5};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, ReverseSortedArray)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, RandomArray)
{
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {11, 12, 22, 25, 34, 64, 90}));
}

TEST(QuickSortTest, WithDuplicates)
{
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    EXPECT_EQ(data, (std::vector<int> {1, 1, 2, 3, 4, 5, 5, 6, 9}));
}

TEST(QuickSortTest, LargeArray)
{
    std::vector<int> data(1000);
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    quick_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
    for (size_t i = 0; i < data.size(); ++i)
    {
        EXPECT_EQ(data[i], static_cast<int>(i));
    }
}