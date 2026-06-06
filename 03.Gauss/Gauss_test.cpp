#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "Gauss_solve.h"

TEST(GaussSolve, Solve2x2)
{
    GaussMatrix ab(2, 3);
    // Система:
    // 2x + y = 5
    // x - y = 1
    ab << 2.0,  1.0, 5.0,
    1.0, -1.0, 1.0;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);  // x = 2
    EXPECT_NEAR(x(1), 1.0, 1e-9);  // y = 1
}

TEST(GaussSolve, Solve3x3)
{
    GaussMatrix ab(3, 4);
    // Система:
    // 2x + y - z = 8
    // -3x - y + 2z = -11
    // -2x + y + 2z = -3
    // Ответ: x=2, y=3, z=-1
    ab <<  2.0,  1.0, -1.0,  8.0,
    -3.0, -1.0,  2.0, -11.0,
    -2.0,  1.0,  2.0, -3.0;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 3.0, 1e-9);
    EXPECT_NEAR(x(2), -1.0, 1e-9);
}