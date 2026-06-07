#include "Gauss_solve.h"

GaussVector Gauss_solve(GaussMatrix& ab)
{
    int n = ab.rows();
    int m = ab.cols() - 1;


    for (int col = 0; col < m; ++col)
    {
        int pivot_row = col;
        double max_val = std::abs(ab(col, col));
        for (int row = col + 1; row < n; ++row)
        {
            if (std::abs(ab(row, col)) > max_val)
            {
                max_val = std::abs(ab(row, col));
                pivot_row = row;
            }
        }

        if (max_val < 1e-12)
        {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        if (pivot_row != col)
        {
            ab.row(col).swap(ab.row(pivot_row));
        }

        for (int row = col + 1; row < n; ++row)
        {
            double factor = ab(row, col) / ab(col, col);
            ab.row(row) -= factor * ab.row(col);
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = 0.0;
        for (int j = i + 1; j < m; ++j)
        {
            sum += ab(i, j) * x[j];
        }
        x[i] = (ab(i, m) - sum) / ab(i, i);
    }

    return x;
}
