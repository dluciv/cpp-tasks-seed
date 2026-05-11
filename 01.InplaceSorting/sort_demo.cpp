#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <numeric>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

// Random data

std::vector<CollInt> generate_data(size_t n)
{
    std::vector<CollInt> data(n);

int main()
{
    std::vector<size_t> sizes = {100, 500, 1000, 2000};
    std::vector<size_t> sizes = {0, 1, 10, 100, 500, 1000, 2000};

    std::cout << "N\tAlgo\t\tComps\t\tSwaps\t\tMoves\n";
    std::cout << "----------------------------------------------------------------\n";
    {
        auto number_data = generate_data(n);

        // --- Std Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        std::sort(number_data.begin(), number_data.end());
        assert(std::is_sorted(number_data.begin(), number_data.end()));
        std::cout << n << "\tstd::sort\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Bubble Sort ---

        shuffle_data(number_data);
        CollInt::reset_stats();
        bubble_sort(number_data.begin(), number_data.end());
        assert(std::is_sorted(number_data.begin(), number_data.end()));
        std::cout << n << "\tBubble\t\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Insertion Sort ---

        shuffle_data(number_data);
        CollInt::reset_stats();
        quick_sort(number_data.begin(), number_data.end());
        std::cout << n << "\tInsertion\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";
        assert(std::is_sorted(number_data.begin(), number_data.end()));
        std::cout << n << "\tQuick\t\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        std::cout << "--------------------------------------------------------------\n";
    }
