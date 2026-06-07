#include <cmath>
#include <stdexcept>

#include "Gauss_solve.h"

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();

    if (n == 0)
        throw std::invalid_argument("Matrix is empty");
    if (ab.cols() != n + 1)
        throw std::invalid_argument("Expected augmented matrix of shape n x (n+1)");

    for (int col = 0; col < n; ++col)
    {
        int pivot = col;
        for (int row = col + 1; row < n; ++row)
            if (std::abs(ab(row, col)) > std::abs(ab(pivot, col)))
                pivot = row;

        if (std::abs(ab(pivot, col)) < 1e-12)
            throw std::runtime_error("Matrix is singular");

        ab.row(col).swap(ab.row(pivot));

        for (int row = col + 1; row < n; ++row)
        {
            double factor = ab(row, col) / ab(col, col);
            ab.row(row) -= factor * ab.row(col);
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double s = ab(i, n);
        for (int j = i + 1; j < n; ++j)
            s -= ab(i, j) * x(j);
        x(i) = s / ab(i, i);
    }

    return x;
}