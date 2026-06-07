#include <gtest/gtest.h>
#include <random>
#include <cmath>

#include "Gauss_solve.h"

static GaussMatrix make_ab(const GaussMatrix &A, const GaussVector &b)
{
    int n = A.rows();
    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = A;
    ab.col(n) = b;
    return ab;
}

TEST(GaussSolve, OneByOne)
{
    GaussMatrix ab(1, 2);
    ab << 3.0, 6.0;
    GaussVector x = Gauss_solve(ab);
    EXPECT_NEAR(x(0), 2.0, 1e-9);
}

TEST(GaussSolve, TwoByTwo)
{
    GaussMatrix ab(2, 3);
    ab << 1.1, 2.2, 3.3,
    4.4, 5.5, 6.6;
    GaussVector x = Gauss_solve(ab);
    EXPECT_NEAR(x(0), -1.0, 1e-9);
    EXPECT_NEAR(x(1),  2.0, 1e-9);
}

TEST(GaussSolve, ThreeByThreeKnown)
{
    GaussMatrix ab(3, 4);
    ab << 2, 1, 1, 7,
    4, 3, 3, 19,
    8, 7, 9, 49;
    GaussVector x = Gauss_solve(ab);
    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
    EXPECT_NEAR(x(2), 3.0, 1e-9);
}

TEST(GaussSolve, IdentityMatrix)
{
    const int n = 5;
    GaussMatrix A(n, n);
    A.setIdentity();
    GaussVector b(n);
    b << 1.0, 2.0, 3.0, 4.0, 5.0;
    GaussMatrix ab = make_ab(A, b);
    GaussVector x = Gauss_solve(ab);
    for (int i = 0; i < n; ++i)
        EXPECT_NEAR(x(i), b(i), 1e-9);
}

TEST(GaussSolve, LargeRandomSystem)
{
    const int n = 100;
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    GaussMatrix A(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A(i, j) = dist(rng);

    for (int i = 0; i < n; ++i)
        A(i, i) = A.row(i).cwiseAbs().sum() + 1.0;

    GaussVector x_true(n);
    for (int i = 0; i < n; ++i)
        x_true(i) = i + 1.0;

    GaussVector b = A * x_true;
    GaussMatrix ab = make_ab(A, b);
    GaussVector x = Gauss_solve(ab);

    for (int i = 0; i < n; ++i)
        EXPECT_NEAR(x(i), x_true(i), 1e-6);
}

TEST(GaussSolveErrors, EmptyMatrix)
{
    GaussMatrix ab(0, 0);
    EXPECT_THROW(Gauss_solve(ab), std::invalid_argument);
}

TEST(GaussSolveErrors, WrongShape)
{
    GaussMatrix ab(3, 3);
    ab.setIdentity();
    EXPECT_THROW(Gauss_solve(ab), std::invalid_argument);
}

TEST(GaussSolveErrors, SingularMatrix)
{
    GaussMatrix ab(2, 3);
    ab << 1.0, 2.0, 3.0,
    1.0, 2.0, 3.0;
    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}