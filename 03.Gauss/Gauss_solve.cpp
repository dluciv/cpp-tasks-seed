#include "Gauss_solve.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();
    int m = ab.cols();

    if (m != n + 1)
        throw std::runtime_error("Matrix must be N x (N+1)");
    if (n == 0)
        throw std::runtime_error("Empty matrix");

    for (int k = 0; k < n; ++k)
    {
        int maxRow = k;
        double maxVal = std::abs(ab(k, k));
        for (int i = k + 1; i < n; ++i)
        {
            if (std::abs(ab(i, k)) > maxVal)
            {
                maxVal = std::abs(ab(i, k));
                maxRow = i;
            }
        }

        if (maxVal < 1e-12)
            throw std::runtime_error("Singular matrix");

        if (maxRow != k)
            ab.row(k).swap(ab.row(maxRow));

        double pivot = ab(k, k);
        ab.row(k) /= pivot;

        for (int i = k + 1; i < n; ++i)
        {
            double factor = ab(i, k);
            ab.row(i) -= factor * ab.row(k);
        }
    }

    GaussVector x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        x(i) = ab(i, n);
        for (int j = i + 1; j < n; ++j)
            x(i) -= ab(i, j) * x(j);
    }

    return x;
}
