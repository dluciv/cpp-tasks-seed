#include <gtest/gtest.h>
#include <cmath>
#include "Gauss_solve.h"

static bool approx_eq(double a, double b, double eps = 1e-6)
{
    return std::abs(a - b) < eps;
}

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(2, 3);
    ab << 2, 1, 5,
          1, 3, 7;

    GaussVector x = Gauss_solve(ab);

    EXPECT_TRUE(approx_eq(x(0), 1.6));
    EXPECT_TRUE(approx_eq(x(1), 1.8));
}

TEST(GaussSolve, DebugTest)
{
    GaussMatrix ab(2, 3);
    ab << 1, 0, 5,
          0, 1, 3;

    GaussVector x = Gauss_solve(ab);

    std::cout << "Simple test: x(0)=" << x(0) << ", x(1)=" << x(1) << std::endl;
    
    EXPECT_EQ(x(0), 5.0);
    EXPECT_EQ(x(1), 3.0);
}

TEST(GaussSolve, ThreeByThree)
{
    GaussMatrix ab(3, 4);
    ab << 1, 1, 1, 6,
          0, 2, 1, 5,
          0, 0, 3, 9;

    GaussVector x = Gauss_solve(ab);

    EXPECT_TRUE(approx_eq(x(0), 2.0)); 
    EXPECT_TRUE(approx_eq(x(1), 1.0));  
    EXPECT_TRUE(approx_eq(x(2), 3.0)); 
}

TEST(GaussSolve, NeedsPivoting)
{
    GaussMatrix ab(2, 3);
    ab << 0, 2, 4,
          3, 4, 14;

    GaussVector x = Gauss_solve(ab);

    EXPECT_TRUE(approx_eq(x(0), 2.0));
    EXPECT_TRUE(approx_eq(x(1), 2.0));
}

TEST(GaussSolve, LargerSystem)
{
    GaussMatrix ab(4, 5);
    ab << 4, 1, 2, 3, 20,
          1, 5, 1, 2, 18,
          2, 1, 6, 1, 22,
          3, 2, 1, 7, 26;

    GaussVector x = Gauss_solve(ab);

    GaussMatrix A = ab.leftCols(4);
    GaussVector b = ab.col(4);
    GaussVector Ax = A * x;

    for (int i = 0; i < 4; ++i)
    {
        EXPECT_TRUE(approx_eq(Ax(i), b(i), 1e-5));
    }
}

TEST(GaussSolve, SingularMatrixThrows)
{
    GaussMatrix ab(2, 3);
    ab << 1, 2, 3,
          2, 4, 6;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}
