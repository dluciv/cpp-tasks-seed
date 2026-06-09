#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix &ab)
{
    const int rows = ab.rows();
    const int cols = ab.cols();
    const double eps = 1e-12;

    if (rows == 0 || cols != rows + 1)
    {
        throw std::invalid_argument("Expected an augmented matrix with N rows and N + 1 columns");
    }

    for (int column = 0; column < rows; ++column)
    {
        int pivot_row = column;
        double best_abs = std::abs(ab(column, column));

        for (int row = column + 1; row < rows; ++row)
        {
            const double current_abs = std::abs(ab(row, column));
            if (current_abs > best_abs)
            {
                best_abs = current_abs;
                pivot_row = row;
            }
        }

        if (best_abs < eps)
        {
            throw std::runtime_error("The system has no unique solution");
        }

        if (pivot_row != column)
        {
            ab.row(column).swap(ab.row(pivot_row));
        }

        for (int row = column + 1; row < rows; ++row)
        {
            const double factor = ab(row, column) / ab(column, column);
            ab.row(row).segment(column, cols - column) -=
                factor * ab.row(column).segment(column, cols - column);
        }
    }

    GaussVector result(rows);
    for (int row = rows - 1; row >= 0; --row)
    {
        double right_part = ab(row, rows);
        if (row + 1 < rows)
        {
            right_part -= ab.row(row).segment(row + 1, rows - row - 1).dot(
                              result.segment(row + 1, rows - row - 1));
        }

        if (std::abs(ab(row, row)) < eps)
        {
            throw std::runtime_error("The system has no unique solution");
        }

        result(row) = right_part / ab(row, row);
    }

    return result;
}
