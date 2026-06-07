#include "Gauss_solve.h"
#include <cmath>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const Eigen::Index n = ab.rows();

    for (Eigen::Index k = 0; k < n; ++k)
    {
        Eigen::Index piv = k;
        for (Eigen::Index i = k + 1; i < n; ++i)
            if (std::abs(ab(i, k)) > std::abs(ab(piv, k)))
                piv = i;

        if (piv != k)
            ab.row(k).swap(ab.row(piv));

        for (Eigen::Index i = k + 1; i < n; ++i)
        {
            double f = ab(i, k) / ab(k, k);
            ab.row(i) -= f * ab.row(k);
        }
    }

    GaussVector x(n);
    for (Eigen::Index i = n - 1; i >= 0; --i)
    {
        double s = ab(i, n);
        for (Eigen::Index j = i + 1; j < n; ++j)
            s -= ab(i, j) * x(j);
        x(i) = s / ab(i, i);
    }

    return x;
}
