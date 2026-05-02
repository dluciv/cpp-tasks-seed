#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(FooSuite, FooTest)
{
    EXPECT_EQ(0, 0);
}

TEST(SortSuite, BubbleSortTest)
{
    std::vector<int> v1 = {5, 3, 8, 1, 2, 7};
    bubble_sort(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    std::vector<int> v2 = {};
    bubble_sort(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));

    std::vector<int> v3 = {42};
    bubble_sort(v3.begin(), v3.end());
    EXPECT_TRUE(std::is_sorted(v3.begin(), v3.end()));

    std::vector<int> v4 = {1, 2, 3, 4, 5};
    bubble_sort(v4.begin(), v4.end());
    EXPECT_TRUE(std::is_sorted(v4.begin(), v4.end()));

    std::vector<int> v5 = {3, 1, 2, 3, 1, 2};
    bubble_sort(v5.begin(), v5.end());
    EXPECT_TRUE(std::is_sorted(v5.begin(), v5.end()));
}

TEST(SortSuite, QuickSortTest)
{
    std::vector<int> v1 = {5, 3, 8, 1, 2, 7};
    quick_sort(v1.begin(), v1.end());
    EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));

    std::vector<int> v2 = {};
    quick_sort(v2.begin(), v2.end());
    EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));

    std::vector<int> v3 = {42};
    quick_sort(v3.begin(), v3.end());
    EXPECT_TRUE(std::is_sorted(v3.begin(), v3.end()));

    std::vector<int> v4 = {1, 2, 3, 4, 5};
    quick_sort(v4.begin(), v4.end());
    EXPECT_TRUE(std::is_sorted(v4.begin(), v4.end()));

    std::vector<int> v5 = {3, 1, 2, 3, 1, 2};
    quick_sort(v5.begin(), v5.end());
    EXPECT_TRUE(std::is_sorted(v5.begin(), v5.end()));
}