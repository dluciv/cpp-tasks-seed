#include "Gauss_solve.h"
#include <stdexcept>
#include <cmath>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();
    for (int k = 0; k < n; ++k)
    {
        int max_row = k;
        double max_val = std::fabs(ab(k, k));
        for (int i = k + 1; i < n; ++i)
        {
            double val = std::fabs(ab(i, k));
            if (val > max_val)
            {
                max_val = val;
                max_row = i;
            }
        }
        if (max_val < 1e-12)
        {
            throw std::runtime_error("Матрица вырождена");
        }
        if (max_row != k)
        {
            ab.row(k).swap(ab.row(max_row));
        }
        for (int i = k + 1; i < n; ++i)
        {
            double factor = ab(i, k) / ab(k, k);
            ab.row(i) -= factor * ab.row(k);
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