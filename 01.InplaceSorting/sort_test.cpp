#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>

#include "sorting.h"

// ======================== Тесты для пузырька ========================

TEST(BubbleSortTest, EmptyVector) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortTest, SingleElement) {
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
}

TEST(BubbleSortTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, ReverseOrder) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, Duplicates) {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

// ======================== Тесты для QuickSort ========================

TEST(QuickSortTest, EmptyVector) {
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> v = {100};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 100);
}

TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, ReverseOrder) {
    std::vector<int> v = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, RandomWithDuplicates) {
    std::vector<int> v = {5, 2, 2, 8, 1, 9, 3, 2, 7, 5, 4, 6, 0};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

// Опционально: тест, который сравнивает обе сортировки между собой на случайных данных
// (можно считать 11-м, но для набора из 10 оставим как есть)
