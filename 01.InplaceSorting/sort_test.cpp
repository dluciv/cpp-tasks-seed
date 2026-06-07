#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(BubbleSort, RandomArray)
{
    std::vector<int> v = {5, 1, 4, 2, 8};

    bubble_sort(v.begin(), v.end());

    EXPECT_EQ(v, (std::vector<int> {1, 2, 4, 5, 8}));
}

TEST(BubbleSort, EmptyArray)
{
    std::vector<int> v;

    bubble_sort(v.begin(), v.end());

    EXPECT_TRUE(v.empty());
}

TEST(BubbleSort, OneElement)
{
    std::vector<int> v = {42};

    bubble_sort(v.begin(), v.end());

    EXPECT_EQ(v[0], 42);
}

TEST(QuickSort, RandomArray)
{
    std::vector<int> v = {10, 7, 8, 9, 1, 5};

    quick_sort(v.begin(), v.end());

    EXPECT_EQ(v, (std::vector<int> {1, 5, 7, 8, 9, 10}));
}

TEST(QuickSort, Duplicates)
{
    std::vector<int> v = {4, 2, 4, 1, 2};

    quick_sort(v.begin(), v.end());

    EXPECT_EQ(v, (std::vector<int> {1, 2, 2, 4, 4}));
}

TEST(QuickSort, SortedArray)
{
    std::vector<int> v = {1, 2, 3, 4, 5};

    quick_sort(v.begin(), v.end());

    EXPECT_EQ(v, (std::vector<int> {1, 2, 3, 4, 5}));
}