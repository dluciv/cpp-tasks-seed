#include <gtest/gtest.h>

#include <cmath>
#include <initializer_list>
#include <random>
#include <sstream>
#include <stdexcept>

#include "Gauss_solve.h"

TEST(GaussSolve, SingleEquation)
{
    GaussMatrix matrix(1, 2);
    matrix << 4.0, 12.0;

    const GaussVector solution = Gauss_solve(matrix);

    EXPECT_NEAR(solution(0), 3.0, 1e-12);
}

TEST(GaussSolve, TwoEquations)
{
    GaussMatrix matrix(2, 3);
    matrix << 2.0, 1.0, 5.0,
           1.0, -1.0, 1.0;

    const GaussVector solution = Gauss_solve(matrix);

    EXPECT_NEAR(solution(0), 2.0, 1e-12);
    EXPECT_NEAR(solution(1), 1.0, 1e-12);
}

TEST(GaussSolve, PartialPivoting)
{
    GaussMatrix matrix(2, 3);
    matrix << 0.0, 2.0, 4.0,
           1.0, 1.0, 3.0;

    const GaussVector solution = Gauss_solve(matrix);

    EXPECT_NEAR(solution(0), 1.0, 1e-12);
    EXPECT_NEAR(solution(1), 2.0, 1e-12);
}

TEST(GaussSolve, SingularMatrix)
{
    GaussMatrix matrix(2, 3);
    matrix << 1.0, 2.0, 3.0,
           2.0, 4.0, 6.0;

    EXPECT_THROW(Gauss_solve(matrix), std::runtime_error);
}

TEST(GaussSolve, IncorrectDimensions)
{
    GaussMatrix matrix(2, 2);
    matrix.setIdentity();

    EXPECT_THROW(Gauss_solve(matrix), std::invalid_argument);
}

TEST(GaussSolve, ReproducibleRandomSystems)
{
    for (int size :
            {
                8, 32, 128
            })
    {
        std::mt19937 generator(static_cast<unsigned int>(42 + size));
        std::uniform_int_distribution<int> distribution(-5, 5);

        GaussVector expected(size);

        for (int i = 0; i < size; ++i)
        {
            expected(i) = distribution(generator);
        }

        GaussMatrix matrix(size, size + 1);

        for (int row = 0; row < size; ++row)
        {
            double sum = 0.0;

            for (int column = 0; column < size; ++column)
            {
                if (row != column)
                {
                    matrix(row, column) = distribution(generator);
                    sum += std::abs(matrix(row, column));
                }
            }

            matrix(row, row) = sum + 1.0;
            matrix(row, size) = matrix.row(row).head(size).dot(expected);
        }

        const GaussVector actual = Gauss_solve(matrix);

        for (int i = 0; i < size; ++i)
        {
            EXPECT_NEAR(actual(i), expected(i), 1e-8);
        }
    }
}

TEST(GaussCsv, OutputFormat)
{
    GaussMatrix matrix(2, 1);
    matrix << 1.5, -2.0;

    std::ostringstream output;
    print_matrix_as_csv(output, matrix);

    EXPECT_EQ(output.str(), "X\n1.500000\n-2.000000\n");
}

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
