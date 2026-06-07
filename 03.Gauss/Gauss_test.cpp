#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "Gauss_solve.h"

TEST(GaussSolve, SmallSystem2x2)
{
    GaussMatrix ab(2, 3);
    ab << 2, 1, 5,
    1, -1, 1;

    GaussVector expected(2);
    expected << 2, 1;

    GaussVector result = Gauss_solve(ab);
    EXPECT_TRUE(result.isApprox(expected, 1e-10));
}

TEST(GaussSolve, SmallSystem3x3)
{
    GaussMatrix ab(3, 4);
    ab << 1, 1, 1, 6,
    2, -1, 1, 3,
    3, 2, -1, 4;

    GaussVector expected(3);
    expected << 1, 2, 3;

    GaussVector result = Gauss_solve(ab);
    EXPECT_TRUE(result.isApprox(expected, 1e-10));
}

TEST(GaussSolve, RandomSystem)
{
    int n = 10;
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
    Eigen::VectorXd b = Eigen::VectorXd::Random(n);

    GaussMatrix ab(n, n + 1);
    ab.leftCols(n) = A;
    ab.col(n) = b;

    GaussVector result = Gauss_solve(ab);

    Eigen::VectorXd expected = A.colPivHouseholderQr().solve(b);

    EXPECT_TRUE(result.isApprox(expected, 1e-8));
}

TEST(GaussSolve, IdentityMatrix)
{
    int n = 5;
    GaussMatrix ab(n, n + 1);
    ab.setIdentity();
    ab.col(n) = Eigen::VectorXd::Random(n);

    GaussVector result = Gauss_solve(ab);
    GaussVector expected = ab.col(n);

    EXPECT_TRUE(result.isApprox(expected, 1e-10));
}

TEST(GaussSolve, ZeroSolution)
{
    int n = 4;
    GaussMatrix ab(n, n + 1);
    ab.setRandom();
    ab.col(n).setZero();

    GaussVector result = Gauss_solve(ab);
    GaussVector expected = GaussVector::Zero(n);

    EXPECT_TRUE(result.isApprox(expected, 1e-10));
}
