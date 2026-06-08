#include <gtest/gtest.h>
#include <random>
#include "Gauss_solve.h"

GaussMatrix generate_random_system(int n, unsigned seed = 42)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    GaussMatrix ab(n, n + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            ab(i, j) = dist(rng);
        }
    }
    return ab;
}

TEST(GaussSolve, SmallSystem2x2)
{
    GaussMatrix ab(2, 3);
    ab << 2, 3, 8,
    5, -1, 3;
    GaussVector sol = Gauss_solve(ab);
    EXPECT_NEAR(sol(0), 1.0, 1e-6);
    EXPECT_NEAR(sol(1), 2.0, 1e-6);
}

TEST(GaussSolve, SmallSystem3x3)
{
    GaussMatrix ab(3, 4);
    ab << 1, 1, 1, 6,
    2, -1, 3, 14,
    -1, 2, -1, -2;

    GaussVector sol = Gauss_solve(ab);

    EXPECT_NEAR(sol(0), -4.0/3.0, 1e-6);
    EXPECT_NEAR(sol(1),  4.0/3.0, 1e-6);
    EXPECT_NEAR(sol(2),  6.0,     1e-6);
}

TEST(GaussSolve, RandomSystem)
{
    int n = 10;
    GaussMatrix ab = generate_random_system(n);
    GaussMatrix ab_copy = ab;
    GaussVector x = Gauss_solve(ab);
    for (int i = 0; i < n; ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < n; ++j)
        {
            sum += ab_copy(i, j) * x(j);
        }
        EXPECT_NEAR(sum, ab_copy(i, n), 1e-6);
    }
}