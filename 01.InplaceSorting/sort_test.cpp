#include <gtest/gtest.h>
#include "sorting.h"

#include <algorithm>
#include <string>
#include <vector>


using namespace std;

// проверяем, что массив отсортирован
static void expect_sorted(vector<int> const &data)
{
    EXPECT_TRUE(is_sorted(data.begin(), data.end())) << "Массив должен быть отсортирован";
}


// роверяем что после сорировки остались те же элементы
static void expect_same_elements(vector<int> before, vector<int> after)
{
    sort(before.begin(), before.end());
    sort(after.begin(), after.end());

    EXPECT_EQ(before, after) << "После сортировки должны остаться те же самые элементы";
}

// хапускаем пузырьковую сортировку и проверяем результат
static void check_bubble_sort(vector<int> data)
{
    vector<int> before = data;

    int *old_place = data.empty() ? nullptr : data.data();

    bubble_sort(data.begin(), data.end());

    expect_sorted(data);
    expect_same_elements(before, data);

    if (!data.empty())
    {
        EXPECT_EQ(old_place, data.data()) << "Пузырьковая сортировка должна работать на месте";
    }
}


// запускаем быструю сортировку и проверяем результат
static void check_quick_sort(vector<int> data)
{
    vector<int> before = data;

    int *old_place = data.empty() ? nullptr : data.data();

    quick_sort(data.begin(), data.end());

    expect_sorted(data);
    expect_same_elements(before, data);

    if (!data.empty())
    {
        EXPECT_EQ(old_place, data.data()) << "Быстрая сортировка должна работать на месте";
    }
}

// роверяем сразу обе сортировки на одном наборе данных
static void check_both_sorts(vector<int> data)
{
    check_bubble_sort(data);
    check_quick_sort(data);
}

TEST(BubbleSort, EmptyVector)
{
    vector<int> data;

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(data.empty()) << "Пустой массив должен остаться пустым";
}

TEST(QuickSort, EmptyVector)
{
    vector<int> data;

    quick_sort(data.begin(), data.end());

    EXPECT_TRUE(data.empty()) << "Пустой массив должен остаться пустым";
}


TEST(AllSorts, OneElement)
{
    check_both_sorts({7});
}

TEST(AllSorts, AlreadySorted)
{
    check_both_sorts({1, 2, 3, 4, 5, 6, 7, 8});
}


TEST(AllSorts, Reversed)
{
    check_both_sorts({9, 8, 7, 6, 5, 4, 3, 2, 1});
}

TEST(AllSorts, RandomSmallArray)
{
    check_both_sorts({5, 1, 9, 3, 7, 2, 8, 4, 6});
}

TEST(AllSorts, WithDuplicates)
{
    check_both_sorts({5, 1, 5, 3, 5, 2, 1, 3, 2, 5});
}


TEST(AllSorts, WithNegativeNumbers)
{
    check_both_sorts({0, -10, 5, -3, 2, -100, 50, 1});
}

TEST(AllSorts, AllEqual)
{
    check_both_sorts({4, 4, 4, 4, 4, 4, 4, 4});
}

TEST(AllSorts, TwoElementsSorted)
{
    check_both_sorts({1, 2});
}

TEST(AllSorts, TwoElementsUnsorted)
{
    check_both_sorts({2, 1});
}

TEST(AllSorts, BigArray)
{
    vector<int> data;

    for (int i = 300; i >= -300; i--)
    {
        data.push_back((i * 37) % 101);
    }

    check_both_sorts(data);
}

TEST(BubbleSort, ManyDifferentLengths)
{
    for (int len = 0; len <= 80; len++)
    {
        vector<int> data;

        for (int i = 0; i < len; i++)
        {
            data.push_back((i * 19 + len * 7) % 53 - 20);
        }

        vector<int> before = data;

        bubble_sort(data.begin(), data.end());

        expect_sorted(data);
        expect_same_elements(before, data);
    }
}



TEST(QuickSort, ManyDifferentLengths)
{
    for (int len = 0; len <= 500; len++)
    {
        vector<int> data;

        for (int i = 0; i < len; i++)
        {
            data.push_back((i * 31 + len * 11) % 97 - 40);
        }

        vector<int> before = data;

        quick_sort(data.begin(), data.end());

        expect_sorted(data);
        expect_same_elements(before, data);
    }
}

TEST(QuickSort, BigSortedArray)
{
    vector<int> data;

    for (int i = 0; i < 2000; i++)
    {
        data.push_back(i);
    }

    check_quick_sort(data);
}


TEST(QuickSort, BigReversedArray)
{
    vector<int> data;

    for (int i = 2000; i >= 0; i--)
    {
        data.push_back(i);
    }

    check_quick_sort(data);
}


TEST(QuickSort, BigArrayWithManySameValues)
{
    vector<int> data;

    for (int i = 0; i < 3000; i++)
    {
        data.push_back(i % 5);
    }

    check_quick_sort(data);
}
