#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "Gauss_solve.h"

TEST(GaussSolve, Solve2x2)
{
    GaussMatrix ab(2, 3);
    ab << 2, 3, 8,
    1, -1, -1;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
}

TEST(GaussSolve, Solve3x3)
{
    GaussMatrix ab(3, 4);
    ab << 1, 2, 3, 14,
    2, 1, 1, 7,
    3, -1, 2, 7;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
    EXPECT_NEAR(x(2), 3.0, 1e-9);
}

TEST(GaussSolve, SolveWithPivoting)
{
    GaussMatrix ab(3, 4);
    ab << 0.001, 1.0, 2.0, 3.0,
    1.0, 0.0, 1.0, 2.0,
    2.0, 1.0, 0.0, 3.0;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(0.001*x(0) + x(1) + 2*x(2), 3.0, 1e-6);
    EXPECT_NEAR(x(0) + x(2), 2.0, 1e-6);
    EXPECT_NEAR(2*x(0) + x(1), 3.0, 1e-6);
}

TEST(GaussSolve, SingularMatrix)
{
    GaussMatrix ab(2, 3);
    ab << 1, 2, 3,
    2, 4, 6;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}