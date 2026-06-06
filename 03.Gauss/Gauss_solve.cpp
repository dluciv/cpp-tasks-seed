#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int n = ab.rows();

    for (int i = 0; i < n; ++i)
        {
            int pivotRow = i;
            double maxVal = std::abs(ab(i, i));

            for (int k = i + 1; k < n; ++k)
                {
                    double val = std::abs(ab(k, i));

                    if (val > maxVal)
                        {
                            maxVal = val;
                            pivotRow = k;
                        }
                }

            if (maxVal < 1e-12)
                {
                    throw std::runtime_error("Matrix is singular or nearly singular");
                }

            if (pivotRow != i)
                {
                    ab.row(i).swap(ab.row(pivotRow));
                }

            ab.row(i) /= ab(i, i);

            for (int k = i + 1; k < n; ++k)
                {
                    ab.row(k) -= ab(k, i) * ab.row(i);
                }
        }

    GaussVector x(n);

    for (int i = n - 1; i >= 0; --i)
        {
            x(i) = ab(i, n);

            for (int k = i - 1; k >= 0; --k)
                {
                    ab(k, n) -= ab(k, i) * x(i);
                }
        }

    return x;
}