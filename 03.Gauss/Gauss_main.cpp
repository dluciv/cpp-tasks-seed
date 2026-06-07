#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include <Eigen/Dense>
#include <lazycsv.hpp>

#include "util.h"
#include "Gauss_solve.h"

GaussMatrix generate_random_system(int n, unsigned seed = 42)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    GaussMatrix ab(n, n + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= n; ++j)
            ab(i, j) = dist(gen);
    }
    return ab;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <matrix.csv> [output.csv] [--generate N]\n";
        return 1;
    }

    std::string arg1(argv[1]);

    GaussMatrix ab;

    if (arg1 == "--generate" && argc >= 3)
    {
        int n = std::stoi(argv[2]);
        ab = generate_random_system(n);
    }
    else
    {
        ab = load_csv_to_matrix(argv[1]);
    }

    std::cerr << "Loaded matrix " << ab.rows() << "x" << ab.cols() << "\n";

    GaussVector x = Gauss_solve(ab);

    // Вывод результата
    if (argc >= 3 && arg1 != "--generate")
    {
        std::ofstream out(argv[2]);
        print_matrix_as_csv(out, ab);
        out << "\nSolution:\n";
        for (int i = 0; i < x.size(); ++i)
            out << "x" << i << ",";
        out << "\n";
        for (int i = 0; i < x.size(); ++i)
        {
            out << x(i);
            if (i < x.size() - 1)
                out << ',';
        }
        out << '\n';
    }
    else
    {
        std::cout << "Solution:\n" << x << "\n";
    }

    return 0;
}
