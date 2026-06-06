#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

template <typename SortFunc>
void test_sort(SortFunc sort_func, std::vector<int> data)
{
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());
    sort_func(data.begin(), data.end());
    EXPECT_EQ(data, expected);
}

// ----- Bubble Sort Tests -----
TEST(BubbleSort, Empty)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSort, SingleElement)
{
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(BubbleSort, AlreadySorted)
{
    test_sort(bubble_sort<std::vector<int>::iterator>, {1, 2, 3, 4, 5});
}

TEST(BubbleSort, ReverseSorted)
{
    test_sort(bubble_sort<std::vector<int>::iterator>, {5, 4, 3, 2, 1});
}

TEST(BubbleSort, RandomWithDuplicates)
{
    test_sort(bubble_sort<std::vector<int>::iterator>, {3, 1, 4, 1, 5, 9, 2, 6, 5, 3});
}

// ----- Quick Sort Tests -----
TEST(QuickSort, Empty)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSort, SingleElement)
{
    std::vector<int> v = {42};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(QuickSort, AlreadySorted)
{
    test_sort(quick_sort<std::vector<int>::iterator>, {1, 2, 3, 4, 5});
}

TEST(QuickSort, ReverseSorted)
{
    test_sort(quick_sort<std::vector<int>::iterator>, {5, 4, 3, 2, 1});
}

TEST(QuickSort, RandomWithDuplicates)
{
    test_sort(quick_sort<std::vector<int>::iterator>, {3, 1, 4, 1, 5, 9, 2, 6, 5, 3});
}
