#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting.h"

// тесты для пузырька

TEST(BubbleSort, empty_array) {
    std::vector<int> data;
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, single_number) {
    std::vector<int> data = {42};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, already_sorted) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, reversed_order) {
    std::vector<int> data = {9, 7, 5, 3, 1};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, with_duplicates) {
    std::vector<int> data = {3, 1, 4, 1, 5, 3, 2};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(BubbleSort, negative_numbers) {
    std::vector<int> data = {-5, -2, -8, 0, -1, 3};
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

// тесты для быстрой сортировки

TEST(QuickSort, empty_array) {
    std::vector<int> data;
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, single_number) {
    std::vector<int> data = {7};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, already_sorted) {
    std::vector<int> data = {10, 20, 30, 40, 50};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, reversed_order) {
    std::vector<int> data = {50, 40, 30, 20, 10};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, random_order) {
    std::vector<int> data = {8, 3, 1, 7, 0, 9, 2, 5, 4, 6};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(QuickSort, with_duplicates) {
    std::vector<int> data = {5, 2, 5, 1, 2, 5, 1};
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

// интеграционный тест

TEST(Integration, compare_both_sorts) {
    std::vector<int> source = {9, 2, 7, 4, 1, 8, 3, 6, 5};
    
    std::vector<int> bubble_copy = source;
    std::vector<int> quick_copy = source;
    
    bubble_sort(bubble_copy.begin(), bubble_copy.end());
    quick_sort(quick_copy.begin(), quick_copy.end());
    
    EXPECT_EQ(bubble_copy, quick_copy);
}
