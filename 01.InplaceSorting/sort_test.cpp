#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

#include "sorting.h"

// Пузырек

TEST(BubbleSort, EmptyVector) {
    std::vector<int> data;
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(BubbleSort, SingleElement) {
    std::vector<int> data = {42};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, AlreadySorted) {
    std::vector<int> data = {-10, 0, 10, 20};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, ReverseSorted) {
    std::vector<int> data = {20, 10, 0, -10};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, RepeatedElements) {
    std::vector<int> data = {5, 3, 5, 2, 3, -1};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

// Быстрая сортировка

TEST(QuickSort, EmptyVector) {
    std::vector<int> data;
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(QuickSort, SingleElement) {
    std::vector<int> data = {42};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, AlreadySorted) {
    std::vector<int> data = {-10, 0, 10, 20};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, ReverseSorted) {
    std::vector<int> data = {20, 10, 0, -10};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, RepeatedElements) {
    std::vector<int> data = {5, 3, 5, 2, 3, -1};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}