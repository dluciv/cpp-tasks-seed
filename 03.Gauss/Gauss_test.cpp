TEST(GaussSolve, DifferentCoefficientScales)
{
    GaussMatrix matrix(2, 3);

    matrix << 1e20, 0.0, 1e20,
              0.0, 1.0, 2.0;

    const GaussVector solution = Gauss_solve(matrix);

    EXPECT_NEAR(solution(0), 1.0, 1e-12);
    EXPECT_NEAR(solution(1), 2.0, 1e-12);
}

TEST(GaussSolve, DifferentScalesWithPivoting)
{
    GaussMatrix matrix(3, 4);

    matrix << 0.0, 1e20, 0.0, 2e20,
              1.0, 0.0, 0.0, 3.0,
              0.0, 0.0, 1e-10, 4e-10;

    const GaussVector solution = Gauss_solve(matrix);

    EXPECT_NEAR(solution(0), 3.0, 1e-12);
    EXPECT_NEAR(solution(1), 2.0, 1e-12);
    EXPECT_NEAR(solution(2), 4.0, 1e-12);
}
