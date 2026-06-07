#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix& ab)
{
    const double eps = 1e-12;
    const int n = ab.rows();

    if (ab.cols() != n + 1)
    {
        throw std::invalid_argument("Expected augmented matrix n x (n + 1)");
    }

    for (int col = 0; col < n; ++col)
    {
        int pivot = col;

        for (int row = col + 1; row < n; ++row)
        {
            if (std::abs(ab(row, col)) > std::abs(ab(pivot, col)))
            {
                pivot = row;
            }
        }

        if (std::abs(ab(pivot, col)) < eps)
        {
            throw std::runtime_error("Matrix is singular");
        }

        if (pivot != col)
        {
            ab.row(col).swap(ab.row(pivot));
        }

        ab.row(col) /= ab(col, col);

        for (int row = 0; row < n; ++row)
        {
            if (row != col)
            {
                double c = ab(row, col);
                ab.row(row) -= c * ab.row(col);
            }
        }
    }

    return ab.col(n);
}