#include <gtest/gtest.h>
#include <random>
#include "Gauss_solve.h"

using namespace Eigen;

TEST(GaussSolve, Simple2x2)
{
    MatrixXd AB(2, 3);
    AB << 2, 1, 5,
    1, -3, -1;
    VectorXd x = solve_gauss(AB);
    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 1.0, 1e-9);
}

TEST(GaussSolve, NeedsPivot)
{
    MatrixXd AB(2, 3);
    AB << 0, 1, 1,
    2, 1, 5;
    VectorXd x = solve_gauss(AB);
    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 1.0, 1e-9);
}

TEST(GaussSolve, SingularMatrix)
{
    MatrixXd AB(2, 3);
    AB << 1, 1, 5,
    1, 1, 10;
    EXPECT_THROW(solve_gauss(AB), std::runtime_error);
}

TEST(GaussSolve, LargeReproducibleMatrix)
{
    int n = 150;
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-100.0, 100.0);

    MatrixXd A(n, n);
    VectorXd true_x(n);

    for(int i = 0; i < n; ++i)
    {
        true_x(i) = dist(gen);
        for(int j = 0; j < n; ++j)
        {
            A(i, j) = dist(gen);
        }
    }

    VectorXd B = A * true_x;
    MatrixXd AB(n, n + 1);
    AB << A, B;

    VectorXd calc_x = solve_gauss(AB);

    for(int i = 0; i < n; ++i)
    {
        EXPECT_NEAR(calc_x(i), true_x(i), 1e-6);
    }
}