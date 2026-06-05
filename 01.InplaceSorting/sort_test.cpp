#include <gtest/gtest.h>
#include <vector>
#include "sorting.h"

// --- Bubble Sort ---
TEST(BubbleSort, Empty)
{
    std::vector<int> v;
    bubble_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(BubbleSort, SingleElement)
{
    std::vector<int> v = {42};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(BubbleSort, Sorted)
{
    std::vector<int> v = {1,2,3,4,5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,2,3,4,5}));
}

TEST(BubbleSort, Reverse)
{
    std::vector<int> v = {5,4,3,2,1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,2,3,4,5}));
}

TEST(BubbleSort, Random)
{
    std::vector<int> v = {3,1,4,1,5,9,2};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,1,2,3,4,5,9}));
}

TEST(BubbleSort, Repetitions)
{
    std::vector<int> v = {1,4,2,2,1};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,1,2,2,4}));
}

TEST(BubbleSort, Negatives)
{
    std::vector<int> v = {1,4,-3,2,5};
    bubble_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({-3,1,2,4,5}));
}

// --- Heap Sort ---

TEST(HeapSort, Empty)
{
    std::vector<int> v;
    heap_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(HeapSort, SingleElement)
{
    std::vector<int> v = {42};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({42}));
}

TEST(HeapSort, Sorted)
{
    std::vector<int> v = {1,2,3,4,5};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,2,3,4,5}));
}

TEST(HeapSort, Reverse)
{
    std::vector<int> v = {5,4,3,2,1};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,2,3,4,5}));
}

TEST(HeapSort, Random)
{
    std::vector<int> v = {10, -1, 7, 3, 2, 0};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({-1, 0, 2, 3, 7, 10}));
}

TEST(HeapSort, Repetitions)
{
    std::vector<int> v = {1,4,2,2,1};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({1,1,2,2,4}));
}

TEST(HeapSort, Negatives)
{
    std::vector<int> v = {1,4,-3,2,5};
    heap_sort(v.begin(), v.end());
    EXPECT_EQ(v, std::vector<int>({-3,1,2,4,5}));
}