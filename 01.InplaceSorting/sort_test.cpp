#include <gtest/gtest.h>
#include <vector>
// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(BubbleSort, Empty) {
    std::vector<int> v = {};
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}
TEST(BubbleSort, Normal) {
    std::vector<int> v = {3, 1, 4, 2};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4}));
}
TEST(BubbleSort, Duplicates) {
    std::vector<int> v = {2, 1, 2, 1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 1, 2, 2}));
}
TEST(QuickSort, Empty) {
    std::vector<int> v = {};
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSort, Normal) {
    std::vector<int> v = {3, 1, 4, 2};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4}));
}

TEST(QuickSort, Duplicates) {
    std::vector<int> v = {2, 1, 2, 1};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 1, 2, 2}));
}
