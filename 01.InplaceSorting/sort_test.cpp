#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"
#include <vector>
// Но проверьте, что сортировки таки работают...

TEST(BubbleSortTest, SortsRegularArray)
{
    std::vector<int> data = {5, 1, 4, 2, 3};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, SortsAlreadySortedArray)
{
    std::vector<int> data = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, SortsReverseSortedArray)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, SortsArrayWithDuplicates)
{
    std::vector<int> data = {4, 2, 4, 1, 2, 3};
    std::vector<int> expected = {1, 2, 2, 3, 4, 4};

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, SortsEmptyArray)
{
    std::vector<int> data = {};
    std::vector<int> expected = {};

    bubble_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, SortsRegularArray)
{
    std::vector<int> data = {5, 1, 4, 2, 3};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, SortsReverseSortedArray)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, SortsArrayWithDuplicates)
{
    std::vector<int> data = {4, 2, 4, 1, 2, 3};
    std::vector<int> expected = {1, 2, 2, 3, 4, 4};

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, SortsEmptyArray)
{
    std::vector<int> data = {};
    std::vector<int> expected = {};

    quick_sort(data.begin(), data.end());

    EXPECT_EQ(data, expected);
}
