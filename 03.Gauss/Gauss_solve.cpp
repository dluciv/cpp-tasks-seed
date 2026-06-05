#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix& ab)
{
    const Eigen::Index n = ab.rows();

    if (n == 0 || ab.cols() != n + 1)
    {
        throw std::runtime_error("Matrix must be Nx(N+1)");
    }

    constexpr double eps = 1e-12;

    for (Eigen::Index col = 0; col < n; ++col)
    {
        Eigen::Index pivot = col;
        double max_abs = std::abs(ab(col, col));

        for (Eigen::Index row = col + 1; row < n; ++row)
        {
            const double value = std::abs(ab(row, col));

            if (value > max_abs)
            {
                max_abs = value;
                pivot = row;
            }
        }

        if (max_abs < eps)
        {
            throw std::runtime_error("System has no unique solution");
        }

        if (pivot != col)
        {
            ab.row(col).swap(ab.row(pivot));
        }

        for (Eigen::Index row = col + 1; row < n; ++row)
        {
            const double factor = ab(row, col) / ab(col, col);
            ab.row(row) -= factor * ab.row(col);
        }
    }

    GaussVector x(n);

    for (Eigen::Index row = n - 1; row >= 0; --row)
    {
        double sum = ab(row, n);

        for (Eigen::Index col = row + 1; col < n; ++col)
        {
            sum -= ab(row, col) * x(col);
        }

        x(row) = sum / ab(row, row);
    }

    return x;
}