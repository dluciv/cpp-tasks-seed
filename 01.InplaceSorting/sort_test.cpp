#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include "sorting.h"

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(SortTest, BubbleSortWorks)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());

    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, QuickSortWorks)
{
    std::vector<int> v = {5, 1, 4, 2, 3};
    quick_sort(v.begin(), v.end());

    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SortTest, EmptyArray)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    quick_sort(v.begin(), v.end());

    EXPECT_TRUE(v.empty());
}

TEST(SortTest, OneElement)
{
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    quick_sort(v.begin(), v.end());

    EXPECT_EQ(v[0], 42);
}

TEST(SortTest, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    quick_sort(v.begin(), v.end());

    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}
