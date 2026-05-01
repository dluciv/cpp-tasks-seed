#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(FooSuite, FooTest)
{
    EXPECT_EQ(0, 0);
}

TEST(BubbleSortTest, SortsEmptyVector) {
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSortTest, SortsSingleElement) {
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
}

TEST(BubbleSortTest, SortsAlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, SortsReverseOrder) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, SortsRandomOrder) {
    std::vector<int> v = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(BubbleSortTest, SortsWithDuplicates) {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, SortsEmptyVector) {
    std::vector<int> v;
    quick_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(QuickSortTest, SortsSingleElement) {
    std::vector<int> v = {42};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v[0], 42);
}

TEST(QuickSortTest, SortsAlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, SortsReverseOrder) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, SortsRandomOrder) {
    std::vector<int> v = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(QuickSortTest, SortsWithDuplicates) {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> expected = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    quick_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}

TEST(ComparisonTest, BothSortsProduceSameResult) {
    std::vector<int> original = {64, 34, 25, 12, 22, 11, 90, 1, 5, 8, 3};
    std::vector<int> v1 = original;
    std::vector<int> v2 = original;
    
    bubble_sort(v1.begin(), v1.end());
    quick_sort(v2.begin(), v2.end());
    
    EXPECT_EQ(v1, v2);
    
    std::vector<int> expected = original;
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(v1, expected);
    EXPECT_EQ(v2, expected);
}

TEST(CustomTypeTest, WorksWithCollectingValue) {
    using CollInt = CollectingValue<int>;
    std::vector<CollInt> v;
    for (int i = 5; i >= 1; --i) {
        v.push_back(CollInt(i));
    }
    
    CollInt::reset_stats();
    quick_sort(v.begin(), v.end());
    
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i].value, i + 1);
    }
    
    EXPECT_GT(CollInt::comps, 0);
    EXPECT_GT(CollInt::swaps, 0);
}
