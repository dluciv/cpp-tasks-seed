#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <deque>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

// Random data
std::vector<CollInt> generate_data(size_t n)
{
    std::vector<CollInt> data(n);
    std::iota(data.begin(), data.end(), CollInt(0));
    return data;
}

void shuffle_data(std::vector<CollInt>& data)
{
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
}

void add_to_deque(std::deque<std::vector<int>>& deq, const std::vector<CollInt>& vec)
{
    std::vector<int> int_vec;
    int_vec.reserve(vec.size());
    for (const auto& val : vec) {
        int_vec.push_back(val.value);
    }
    deq.push_back(int_vec);
}

void print_deque(const std::deque<std::vector<int>>& deq)
{
    std::cout << "\n=== Deque contents ===\n";
    int idx = 1;
    for (const auto& vec : deq) {
        std::cout << "Vector " << idx++ << " (size " << vec.size() << "): ";
        if (vec.size() <= 20) {
            for (int x : vec) std::cout << x << " ";
        } else {
            for (int i = 0; i < 10; ++i) std::cout << vec[i] << " ";
            std::cout << "... ";
            for (size_t i = vec.size() - 10; i < vec.size(); ++i) std::cout << vec[i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "=====================\n";
}

int main()
{
    std::vector<size_t> sizes = {100, 500, 1000, 2000};
    std::deque<std::vector<int>> results_deque;

    std::cout << "N\tAlgo\t\tComps\t\tSwaps\t\tMoves\n";
    std::cout << "----------------------------------------------------------------\n";

    for (size_t n : sizes)
    {
        auto number_data = generate_data(n);

        // --- Std Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        std::sort(number_data.begin(), number_data.end());
        std::cout << n << "\tstd::sort\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Bubble Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        bubble_sort(number_data.begin(), number_data.end());
        std::cout << n << "\tBubble\t\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        // --- Insertion Sort ---
        shuffle_data(number_data);
        CollInt::reset_stats();
        quick_sort(number_data.begin(), number_data.end());
        std::cout << n << "\tQuick\t\t" << CollInt::comps << "\t\t" << CollInt::swaps << "\t\t" << CollInt::moves << "\n";

        add_to_deque(results_deque, number_data);
        
        std::cout << "--------------------------------------------------------------\n";
    }
    
    print_deque(results_deque);

    return 0;
}
