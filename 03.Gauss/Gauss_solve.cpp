#include "Gauss_solve.h"

#include <cmath>
#include <limits>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const Eigen::Index n = ab.rows();

    if (n == 0 || ab.cols() != n + 1)
    {
        throw std::invalid_argument("Expected an N x (N+1) augmented matrix");
    }

    if (!ab.array().isFinite().all())
    {
        throw std::invalid_argument("Matrix contains a non-finite value");
    }

    const double scale = ab.leftCols(n).cwiseAbs().maxCoeff();
    if (scale == 0.0)
    {
        throw std::runtime_error("Singular matrix");
    }

    const double tolerance =
        std::numeric_limits<double>::epsilon() * static_cast<double>(n) * scale;

    for (Eigen::Index column = 0; column < n; ++column)
    {
        Eigen::Index offset = 0;
        const double largest = ab.col(column)
                               .segment(column, n - column)
                               .cwiseAbs()
                               .maxCoeff(&offset);

        if (largest <= tolerance)
        {
            throw std::runtime_error("Singular or ill-conditioned matrix");
        }

        const Eigen::Index pivot = column + offset;
        if (pivot != column)
        {
            ab.row(column).swap(ab.row(pivot));
        }

        for (Eigen::Index row = column + 1; row < n; ++row)
        {
            const double factor = ab(row, column) / ab(column, column);
            ab.row(row).segment(column + 1, n - column) -=
                factor * ab.row(column).segment(column + 1, n - column);
            ab(row, column) = 0.0;
        }
    }

    GaussVector solution(n);
    for (Eigen::Index row = n; row-- > 0;)
    {
        double rhs = ab(row, n);
        const Eigen::Index count = n - row - 1;

        if (count > 0)
        {
            rhs -= ab.row(row).segment(row + 1, count)
                   .dot(solution.segment(row + 1, count));
        }

        solution(row) = rhs / ab(row, row);
    }

    return solution;
}