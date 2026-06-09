#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "sorting.h"

namespace
{

using SortFunction = void (*)(std::vector<int>::iterator, std::vector<int>::iterator);

void expect_sorted_like_std(std::vector<int> data, SortFunction sort_function)
{
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    sort_function(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

} // namespace

TEST(SortingTest, BubbleSortsMixedPositiveNumbers)
{
    expect_sorted_like_std({64, 34, 25, 12, 22, 11, 90},
                           &bubble_sort<std::vector<int>::iterator>);
}

TEST(SortingTest, QuickSortsMixedPositiveNumbers)
{
    expect_sorted_like_std({64, 34, 25, 12, 22, 11, 90},
                           &quick_sort<std::vector<int>::iterator>);
}

TEST(SortingTest, BubbleSortsDuplicatesAndNegativeNumbers)
{
    expect_sorted_like_std({3, -1, 3, 0, -7, 8, -1},
                           &bubble_sort<std::vector<int>::iterator>);
}

TEST(SortingTest, QuickSortsDuplicatesAndNegativeNumbers)
{
    expect_sorted_like_std({3, -1, 3, 0, -7, 8, -1},
                           &quick_sort<std::vector<int>::iterator>);
}

TEST(SortingTest, SortsEmptyAndSingleElementVectors)
{
    expect_sorted_like_std({}, &bubble_sort<std::vector<int>::iterator>);
    expect_sorted_like_std({}, &quick_sort<std::vector<int>::iterator>);
    expect_sorted_like_std({42}, &bubble_sort<std::vector<int>::iterator>);
    expect_sorted_like_std({42}, &quick_sort<std::vector<int>::iterator>);
}