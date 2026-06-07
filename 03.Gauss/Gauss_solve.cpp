#include "Gauss_solve.h"
#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    int rows = ab.rows();
    int cols = ab.cols();

    if (cols != rows + 1)
    {
        throw std::invalid_argument("Матрица должна быть расширенной (N x N+1)");
    }

    for (int i = 0; i < rows; ++i)
    {
        int max_row = i;
        double max_val = std::abs(ab(i, i));
        for (int k = i + 1; k < rows; ++k)
        {
            if (std::abs(ab(k, i)) > max_val)
            {
                max_val = std::abs(ab(k, i));
                max_row = k;
            }
        }

        if (max_row != i)
        {
            ab.row(i).swap(ab.row(max_row));
        }

        if (std::abs(ab(i, i)) < 1e-9)
        {
            throw std::runtime_error("Система не имеет единственного решения (матрица вырождена)");
        }

        ab.row(i) /= ab(i, i);

        for (int j = 0; j < rows; ++j)
        {
            if (i != j)
            {
                ab.row(j) -= ab(j, i) * ab.row(i);
            }
        }
    }

    return ab.col(cols - 1).eval();
}
