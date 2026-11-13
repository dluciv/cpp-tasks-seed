#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting.h"

template <typename Sort>
void check_sort(Sort sorter)
{
    std::vector<std::vector<int>> test_cases =
    {
        {},
        {1},
        {2, 1},
        {1, 2},
        {5, 3, 8, 1, 2},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {7, 7, 7, 7, 7},
        {3, 1, 3, 2, 1},
        {-5, -1, -10, 0, 3},
        {0, 0, -1, 1, 0},
        {100, -100, 50, -50, 0}
    };

    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(-1000, 1000);

    for (unsigned int size :
            {
                10u, 50u, 100u, 500u, 1000u
            })
    {
        std::vector<int> values(size);

        for (auto& value : values)
        {
            value = distribution(generator);
        }

        test_cases.push_back(values);
    }

    for (auto values : test_cases)
    {
        auto expected = values;
        std::sort(expected.begin(), expected.end());

        sorter(values.begin(), values.end());

        EXPECT_EQ(values, expected);
    }
}

TEST(SortingTest, BubbleSort)
{
    check_sort([](auto begin, auto end)
    {
        bubble_sort(begin, end);
    });
}

TEST(SortingTest, QuickSort)
{
    check_sort([](auto begin, auto end)
    {
        quick_sort(begin, end);
    });
}

TEST(SortingTest, BubbleSortSubrange)
{
    std::vector<int> values = {100, 5, 3, 1, 4, 2, -100};

    bubble_sort(values.begin() + 1, values.end() - 1);

    std::vector<int> expected = {100, 1, 2, 3, 4, 5, -100};

    EXPECT_EQ(values, expected);
}

TEST(SortingTest, QuickSortSubrange)
{
    std::vector<int> values = {100, 5, 3, 1, 4, 2, -100};

    quick_sort(values.begin() + 1, values.end() - 1);

    std::vector<int> expected = {100, 1, 2, 3, 4, 5, -100};

    EXPECT_EQ(values, expected);
}