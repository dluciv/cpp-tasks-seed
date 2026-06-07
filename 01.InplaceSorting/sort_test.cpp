#include <gtest/gtest.h>
#include <vector>

#include "sorting.h"

TEST(BubbleSortSuite, EmptyVector)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortSuite, SingleElement)
{
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(BubbleSortSuite, BasicCase)
{
    std::vector<int> v = {5, 1, 4, 2, 8};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1, 2, 4, 5, 8}));
}

TEST(BubbleSortSuite, ReverseOrder)
{
    std::vector<int> v = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(BubbleSortSuite, EqualElements)
{
    std::vector<int> v = {7, 7, 7, 7};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({7, 7, 7, 7}));
}

TEST(QuickSortSuite, EmptyVector)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortSuite, SingleElement)
{
    std::vector<int> v = {42};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(QuickSortSuite, BasicCase)
{
    std::vector<int> v = {5, 1, 4, 2, 8};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1, 2, 4, 5, 8}));
}

TEST(QuickSortSuite, ReverseOrder)
{
    std::vector<int> v = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(QuickSortSuite, EqualElements)
{
    std::vector<int> v = {3, 3, 3, 3, 3};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({3, 3, 3, 3, 3}));
}
