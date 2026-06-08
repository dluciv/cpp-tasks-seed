#include <gtest/gtest.h>
#include <random>
#include <stdexcept>


#include "Gauss_solve.h"


TEST(GaussSolve, SolveSmall2x2_Modified)
{
    GaussMatrix ab(2, 3);

    ab << 2, 1, 4,
    1, 3, 5;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.4, 1e-9);
    EXPECT_NEAR(x(1), 1.2, 1e-9);
}


TEST(GaussSolve, SolveClassic3x3_Modified)
{
    GaussMatrix ab(3, 4);

    ab << 1, 1, 1, 6,
    2, 3, 1, 11,
    3, 1, 2, 11;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
    EXPECT_NEAR(x(2), 3.0, 1e-9);
}


TEST(GaussSolve, SingularMatrixThrows)
{
    GaussMatrix ab(2, 3);

    ab << 1, 2, 3,
    2, 4, 6;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}

TEST(GaussSolve, GeneratedLargeSystem)
{
    constexpr int n = 50;

    std::mt19937 gen(456);
    std::uniform_real_distribution<double> dist(-20.0, 20.0);

    GaussMatrix a(n, n);
    GaussVector expected(n);

    for (int i = 0; i < n; ++i)
    {
        expected(i) = dist(gen);

        for (int j = 0; j < n; ++j)
        {
            a(i, j) = dist(gen);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        a(i, i) += 300.0;
    }

    GaussVector b = a * expected;

    GaussMatrix ab(n, n + 1);
    ab.block(0, 0, n, n) = a;
    ab.col(n) = b;

    GaussVector actual = Gauss_solve(ab);

    for (int i = 0; i < n; ++i)
    {
        EXPECT_NEAR(actual(i), expected(i), 1e-6);
    }
}