#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const int n = ab.rows();
    const int m = ab.cols(); 

    if (m != n + 1)
    {
        throw std::runtime_error("Invalid augmented matrix dimensions");
    }

    for (int col = 0; col < n; ++col)
    {
        int max_row = col;
        double max_val = std::abs(ab(col, col));
        for (int row = col + 1; row < n; ++row)
        {
            double val = std::abs(ab(row, col));
            if (val > max_val)
            {
                max_val = val;
                max_row = row;
            }
        }

        if (max_val < 1e-10)
        {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }

        // Обмен строк
        if (max_row != col)
        {
            ab.row(col).swap(ab.row(max_row));
        }

        // Исключение переменных
        for (int row = col + 1; row < n; ++row)
        {
            double factor = ab(row, col) / ab(col, col);
            for (int j = col; j < m; ++j)
            {
                ab(row, j) -= factor * ab(col, j);
            }
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = ab(i, n);
        for (int j = i + 1; j < n; ++j)
        {
            sum -= ab(i, j) * x(j);
        }
        x(i) = sum / ab(i, i);
    }

    return x;
}
