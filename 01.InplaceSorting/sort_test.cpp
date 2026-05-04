#include <gtest/gtest.h>
#include <vector>
#include <algorithm> // Для std::sort как эталона

#include "sorting.h"

// Тест для пустого массива
TEST(SortingTest, EmptyArray) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v.size(), 0);
}

// Тест для пузырьковой сортировки
TEST(SortingTest, BubbleSortBasic) {
    std::vector<int> v = {5, 1, 4, 2, 8};
    bubble_sort(v.begin(), v.end());
    
    std::vector<int> expected = {1, 2, 4, 5, 8};
    EXPECT_EQ(v, expected);
}

// Тест для быстрой сортировки
TEST(SortingTest, QuickSortBasic) {
    std::vector<int> v = {10, 7, 8, 9, 1, 5};
    quick_sort(v.begin(), v.end());
    
    std::vector<int> expected = {1, 5, 7, 8, 9, 10};
    EXPECT_EQ(v, expected);
}

// Тест на случай когда массив уже отсортирован
TEST(SortingTest, SortedArray) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

// Тест на случай когда массив отсортирован в обратном порядке
TEST(SortingTest, ReverseSortedArray) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

// Большой тест (для проверки O(N log N) чтобы не упало)
TEST(SortingTest, LargeRandom) {
    std::vector<int> v(1000);
    for(auto& x : v) x = rand() % 5000;
    
    quick_sort(v.begin(), v.end());
    
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}