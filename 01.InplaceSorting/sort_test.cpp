#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

TEST(BubbleSort, EmptyVector)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSort, SingleElement)
{
    std::vector<int> v = {1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 1);
}

TEST(BubbleSort, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BubbleSort, ReverseSorted)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BubbleSort, WithDuplicates)
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSort, RandomData)
{
    std::vector<int> v = {42, 15, 8, 99, 1, 0, -5, 23};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSort, EmptyVector)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSort, SingleElement)
{
    std::vector<int> v = {1};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 1);
}

TEST(QuickSort, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSort, ReverseSorted)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSort, WithDuplicates)
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSort, RandomData)
{
    std::vector<int> v = {42, 15, 8, 99, 1, 0, -5, 23};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortingComparison, BubbleVsQuick)
{
    std::vector<int> v1 = {10, -1, 5, 0, 10, 2, 8};
    std::vector<int> v2 = v1;

    bubble_sort(v1.begin(), v1.end());
    quick_sort(v2.begin(), v2.end());

    EXPECT_EQ(v1, v2);
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));
}
