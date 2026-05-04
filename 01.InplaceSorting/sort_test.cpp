#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

// тест для bubble_sort
TEST(BubbleSortTest, EmptyArray) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortTest, SingleElement) {
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
}

TEST(BubbleSortTest, Sorted) {
    std::vector<int> v = {1,2,3,4,5};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BubbleSortTest, ReverseSorted) {
    std::vector<int> v = {5,4,3,2,1};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BubbleSortTest, Random) {
    std::vector<int> v = {3,1,4,1,5,9,2,6};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

// тесты для quick_sort
TEST(QuickSortTest, EmptyArray) {
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> v = {42};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
}

TEST(QuickSortTest, Sorted) {
    std::vector<int> v = {1,2,3,4,5};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSortTest, ReverseSorted) {
    std::vector<int> v = {5,4,3,2,1};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(QuickSortTest, Random) {
    std::vector<int> v = {3,1,4,1,5,9,2,6};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}