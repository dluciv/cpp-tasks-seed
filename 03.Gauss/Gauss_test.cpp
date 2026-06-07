#include <gtest/gtest.h>
#include "Gauss_solve.h"
#include "util.h"

TEST(GaussSolve, 2x2)
{
    GaussMatrix ab(2, 3);
    ab << 1,  1, 3,
    1, -1, 1;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 2.0, 1e-9);
    EXPECT_NEAR(x(1), 1.0, 1e-9);
}

TEST(GaussSolve, 3x3)
{
    GaussMatrix ab(3, 4);
    ab << 2, 1, 1, 7,
    1, 3, 2, 13,
    1, 1, 4, 15;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
    EXPECT_NEAR(x(2), 3.0, 1e-9);
}

TEST(GaussSolve, NeedsPivot)
{
    GaussMatrix ab(2, 3);
    ab << 0, 2, 4,
    1, 1, 3;

    GaussVector x = Gauss_solve(ab);

    EXPECT_NEAR(x(0), 1.0, 1e-9);
    EXPECT_NEAR(x(1), 2.0, 1e-9);
}
