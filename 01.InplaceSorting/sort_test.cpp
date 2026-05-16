#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"

// Но проверьте, что сортировки таки работают...

TEST(Bubble_sort, empty) {
	std::vector<int> v1;
	bubble_sort(v1.begin(), v1.end());
	EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));
}

TEST(Bubble_sort, one_elem) {
	std::vector<int> v2 = {3};
	bubble_sort(v2.begin(), v2.end());
	EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));
}

TEST(Bubble_sort, sorted) {
	std::vector<int> v3 = { -15, 16, 17, 19 };
	bubble_sort(v3.begin(), v3.end());
	EXPECT_TRUE(std::is_sorted(v3.begin(), v3.end()));
}

TEST(Bubble_sort, reversed) {
	std::vector<int> v4 = { 19, 17, 16, -15 };
	bubble_sort(v4.begin(), v4.end());
	EXPECT_TRUE(std::is_sorted(v4.begin(), v4.end()));
}

TEST(Bubble_sort, repeat) {
	std::vector<int> v5 = { 2, 1, 15, 2, 7, -13 };
	bubble_sort(v5.begin(), v5.end());
	EXPECT_TRUE(std::is_sorted(v5.begin(), v5.end()));
}


TEST(Quick_sort, empty) {
	std::vector<int> v1;
	quick_sort(v1.begin(), v1.end());
	EXPECT_TRUE(std::is_sorted(v1.begin(), v1.end()));
}

TEST(Quick_sort, one_elem) {
	std::vector<int> v2 = { 3 };
	quick_sort(v2.begin(), v2.end());
	EXPECT_TRUE(std::is_sorted(v2.begin(), v2.end()));
}

TEST(Quick_sort, sorted) {
	std::vector<int> v3 = { -15, 16, 17, 19 };
	quick_sort(v3.begin(), v3.end());
	EXPECT_TRUE(std::is_sorted(v3.begin(), v3.end()));
}

TEST(Quick_sort, reversed) {
	std::vector<int> v4 = { 19, 17, 16, -15 };
	quick_sort(v4.begin(), v4.end());
	EXPECT_TRUE(std::is_sorted(v4.begin(), v4.end()));
}

TEST(Quick_sort, repeat) {
	std::vector<int> v5 = { 2, 1, 15, 2, 7, -13 };
	quick_sort(v5.begin(), v5.end());
	EXPECT_TRUE(std::is_sorted(v5.begin(), v5.end()));
}
