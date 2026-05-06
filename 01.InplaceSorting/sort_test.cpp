#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(BubbleSort, EmptyArray)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BubbleSort, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}

TEST(BubbleSort, ReverseSorted)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}

TEST(BubbleSort, RandomArray)
{
    std::vector<int> v = {7, 2, 9, 1, 8, 3, 5};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}


TEST(QuickSort, EmptyArray)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSort, AlreadySorted)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}

TEST(QuickSort, ReverseSorted)
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}

TEST(QuickSort, RandomArray)
{
    std::vector<int> v = {7, 2, 9, 1, 8, 3, 5};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    EXPECT_EQ(v, expected);
}
