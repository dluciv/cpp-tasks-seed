#include <gtest/gtest.h>
#include "Gauss_solve.h"

TEST(GaussSolve, System2x2)
{

    GaussMatrix ab(2, 3);
    ab << 2,  1,  5,
    1, -1,  1;

    GaussVector result = Gauss_solve(ab);

    EXPECT_NEAR(result(0), 2.0, 1e-5);
    EXPECT_NEAR(result(1), 1.0, 1e-5);
}

TEST(GaussSolve, System3x3)
{
    GaussMatrix ab(3, 4);
    ab <<  2,  1, -1,   8,
    -3, -1,  2, -11,
    -2,  1,  2,  -3;

    GaussVector result = Gauss_solve(ab);

    EXPECT_NEAR(result(0),  2.0, 1e-5);
    EXPECT_NEAR(result(1),  3.0, 1e-5);
    EXPECT_NEAR(result(2), -1.0, 1e-5);
}

TEST(GaussSolve, SingularMatrixException)
{
    GaussMatrix ab(2, 3);
    ab << 1, 1, 5,
    1, 1, 5;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}