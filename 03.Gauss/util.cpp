#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>

#include <lazycsv.hpp>

#include "util.h"

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::vector<std::vector<double>> rcsv{};
    {
        lazycsv::parser parser{ filename };
        for (const auto row : parser)
        {
            std::vector<double> r{};
            bool row_is_numeric = true;
            for (const auto cell : row)
            {
                try
                {
                    r.push_back(std::stod(std::string(cell.raw())));
                }
                catch (const std::invalid_argument&)
                {
                    row_is_numeric = false;
                    break;
                }
            }
            if (row_is_numeric && !r.empty())
            {
                rcsv.push_back(r);
            }
        }
    }

    if (rcsv.empty())
    {
        throw std::invalid_argument("CSV file does not contain matrix rows");
    }

    const auto cols = rcsv.front().size();
    GaussMatrix matrix(rcsv.size(), cols);

    for (int i = 0; i < matrix.rows(); ++i)
    {
        if (rcsv[i].size() != cols)
        {
            throw std::invalid_argument("CSV rows must have the same length");
        }
        for (int j = 0; j < matrix.cols(); ++j)
        {
            matrix(i, j) = rcsv[i][j];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix &matrix, int prec)
{
    for (int j = 0; j < matrix.cols(); ++j)
        out << "A,";
    out << "B\n";

    out << std::fixed << std::setprecision(prec);

    for (int i = 0; i < matrix.rows(); ++i)
    {
        for (int j = 0; j < matrix.cols(); ++j)
        {
            out << matrix(i, j);
            if (j < matrix.cols() - 1)
            {
                out << ',';
            }
        }
        out << '\n';
    }
}
