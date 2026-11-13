#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

std::vector<CollInt> generate_data(std::size_t size)
{
    std::vector<CollInt> values(size);
    std::iota(values.begin(), values.end(), CollInt(0));
    return values;
}

template <typename Sort>
bool run_sort(std::size_t size, const char* name, std::vector<CollInt> values, Sort sorter)
{
    CollInt::reset_stats();
    sorter(values.begin(), values.end());

    const auto comparisons = CollInt::comps;
    const auto swaps = CollInt::swaps;
    const auto moves = CollInt::moves;

    if (!std::is_sorted(values.begin(), values.end()))
    {
        std::cerr << "Sorting failed: " << name << ", size " << size << '\n';
        return false;
    }

    std::cout << size << '\t' << name << '\t'
              << comparisons << '\t' << swaps << '\t' << moves << '\n';
    return true;
}

int main()
{
    std::mt19937 generator(42);
    std::cout << "N\tAlgorithm\tComparisons\tSwaps\tMoves\n";

    for (std::size_t size :
            {
                100u, 500u, 1000u, 2000u
            })
    {
        auto values = generate_data(size);
        std::shuffle(values.begin(), values.end(), generator);

        if (!run_sort(size, "std::sort", values, [](auto first, auto last)
    {
        std::sort(first, last);
        }))
        {
            return 1;
        }

        if (!run_sort(size, "Bubble", values, [](auto first, auto last)
    {
        bubble_sort(first, last);
        }))
        {
            return 1;
        }

        if (!run_sort(size, "Quick", values, [](auto first, auto last)
    {
        quick_sort(first, last);
        }))
        {
            return 1;
        }
    }

    return 0;
}