#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "sorting.h"

using namespace std;

// Bubble-sort

TEST(BubbleSortTest, Empty) {
    vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortTest, SingleElement) {
    vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
}

TEST(BubbleSortTest, AlreadySorted) {
    vector<int> v = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, Reversed) {
    vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, Duplicates) {
    vector<int> v = {3, 1, 2, 1, 3, 2};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 1, 2, 2, 3, 3};
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, LargeRandom) {
    vector<int> v(1000);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), mt19937{ random_device{}() });
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
}

// Quick-sort

TEST(QuickSortTest, Empty) {
    vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortTest, SingleElement) {
    vector<int> v = { 42 };
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
}

TEST(QuickSortTest, AlreadySorted) {
    vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, Reversed) {
    vector<int> v = {5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, Duplicates) {
    vector<int> v = {3, 1, 2, 1, 3, 2};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
    vector<int> expected = {1, 1, 2, 2, 3, 3};
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, LargeRandom) {
    vector<int> v(1000);
    iota(v.begin(), v.end(), 0);
    shuffle(v.begin(), v.end(), mt19937{random_device{}()});
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(is_sorted(v.begin(), v.end()));
}