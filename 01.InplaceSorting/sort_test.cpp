#include <gtest/gtest.h>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...


#include <vector>
#include <algorithm> // Для std::sort (чтобы было с чем сравнивать)

#include "sorting.h"

// =========================================================================
// Тесты для Bubble Sort
// =========================================================================

TEST(BubbleSortTest, EmptyVector) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortTest, SingleElement) {
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>{42});
}

TEST(BubbleSortTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, ReverseSorted) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, WithDuplicatesAndRandom) {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end()); 
    
    bubble_sort(v.begin(), v.end());
    
    EXPECT_EQ(v, expected);
}


// =========================================================================
// Тесты для Quick Sort
// =========================================================================

TEST(QuickSortTest, EmptyVector) {
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> v = {42};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>{42});
}

TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, ReverseSorted) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, WithDuplicatesAndRandom) {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end()); 
    
    quick_sort(v.begin(), v.end());
    
    EXPECT_EQ(v, expected);
}
