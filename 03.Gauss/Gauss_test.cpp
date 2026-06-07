#include <random>
#include <stdexcept>

#include <gtest/gtest.h>

#include "Gauss_solve.h"

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(2, 3);

    ab << 1.0, 2.0, 5.0,
        3.0, 4.0, 11.0;

    auto x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
}

TEST(GaussSolve, ExampleFromCsv)
{
    GaussMatrix ab(2, 3);

    ab << 1.1, 2.2, 3.3,
        4.4, 5.5, 6.6;

    auto x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), -1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
}

TEST(GaussSolve, SwapRows)
{
    GaussMatrix ab(2, 3);

    ab << 0.0, 1.0, 2.0,
        1.0, 1.0, 3.0;

    auto x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
}

TEST(GaussSolve, SingularMatrix)
{
    GaussMatrix ab(2, 3);

    ab << 1.0, 2.0, 3.0,
        2.0, 4.0, 6.0;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, GeneratedSystem)
{
    const int n = 20;

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-5.0, 5.0);

    GaussMatrix a(n, n);
    GaussVector expected(n);

    for (int i = 0; i < n; ++i)
    {
        expected(i) = dist(gen);

        for (int j = 0; j < n; ++j)
        {
            a(i, j) = dist(gen);
        }

        a(i, i) += 100.0;
    }

    GaussVector b = a * expected;

    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = a;
    ab.col(n) = b;

    auto actual = Gauss_solve(ab);

    for (int i = 0; i < n; ++i)
    {
        EXPECT_NEAR(actual(i), expected(i), 1e-7);
    }
}