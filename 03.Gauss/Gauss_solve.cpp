#include "Gauss_solve.h"
#include <stdexcept>
#include <cmath>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();
    int m = ab.cols();

    if (m != n + 1)
    {
        throw std::invalid_argument("Matrix must have n rows and n+1 columns (augmented matrix)");
    }

    for (int i = 0; i < n; ++i)
    {
        int pivot_row = i;
        double max_abs = std::abs(ab(i, i));
        for (int k = i + 1; k < n; ++k)
        {
            if (std::abs(ab(k, i)) > max_abs)
            {
                max_abs = std::abs(ab(k, i));
                pivot_row = k;
            }
        }

        if (max_abs < 1e-12)
        {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        if (pivot_row != i)
        {
            ab.row(i).swap(ab.row(pivot_row));
        }

        double divisor = ab(i, i);
        ab.row(i) /= divisor;

        for (int k = i + 1; k < n; ++k)
        {
            double factor = ab(k, i);
            if (std::abs(factor) > 1e-15)
            {
                ab.row(k) -= factor * ab.row(i);
            }
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        x(i) = ab(i, n);
        if (i < n - 1)
        {
            x(i) -= ab.row(i).segment(i + 1, n - 1 - i).dot(x.segment(i + 1, n - 1 - i));
        }
    }

    return x;
}