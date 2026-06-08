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
    auto A = load_csv_to_matrix(argv[1]);
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <matrix.csv> [output.csv] [--generate N]\n";
        return 1;
    }

    std::string arg1(argv[1]);

    GaussMatrix ab;

    Eigen::MatrixXd B(3, 2); 
    B << 7, 8,
    9, 10,
    11, 12;
    if (arg1 == "--generate" && argc >= 3)
    {
        int n = std::stoi(argv[2]);
        ab = generate_random_system(n);
    }
    else
    {
        ab = load_csv_to_matrix(argv[1]);
    }

    Eigen::MatrixXd C = A * B;
    std::cerr << "Loaded matrix " << ab.rows() << "x" << ab.cols() << "\n";

    std::cout << "Матрица A:\n" << A << "\n\n";
    std::cout << "Матрица B:\n" << B << "\n\n";
    std::cout << "Результат умножения (C = A * B):\n" << C << "\n";
    GaussVector x = Gauss_solve(ab);

    double c = 2.0;
    A.row(0) += c * A.row(1);
    A.coeffRef(1, 1) -= B.coeff(1, 1);
    std::cout << "Новая матрица A:\n" << A << "\n\n";
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
