#include <gtest/gtest.h>
#include <random>
#include "Gauss_solve.h"

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(3, 4);
    ab << 2, 1, -1, 8,
    -3, -1, 2, -11,
    -2, 1, 2, -3;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 3.0, 1e-9);
    EXPECT_NEAR(x(2), -1.0, 1e-9);
}

TEST(GaussSolve, ReproducibleLargeSystem)
{
    const int N = 100;
    GaussMatrix ab(N, N + 1);

    std::mt19937 gen(1337);
    std::uniform_real_distribution<double> dist(-50.0, 50.0);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ab(i, j) = dist(gen);
        }
    }

    GaussVector expected_x = GaussVector::Ones(N);

    for (int i = 0; i < N; ++i)
    {
        double b_val = 0.0;
        for (int j = 0; j < N; ++j)
        {
            b_val += ab(i, j) * expected_x(j);
        }
        ab(i, N) = b_val;
    }

    GaussVector x = Gauss_solve(ab);

    for (int i = 0; i < N; ++i)
    {
        EXPECT_NEAR(x(i), expected_x(i), 1e-5);
    }
}