#include <string>
#include <iomanip>
#include <stdexcept>
#include <vector>

#include <lazycsv.hpp>

#include "util.h"

GaussMatrix load_csv_to_matrix(const char* filename)
{
    std::vector<std::vector<double>> rcsv{};
    {
        lazycsv::parser parser{ filename };
        for (const auto row : parser)
        {
            std::vector<double> r{};
            for (const auto cell : row)
            {
                r.push_back(std::stod(std::string(cell.raw())));
            }

            if (!rcsv.empty() && r.size() != rcsv.begin()->size())
            {
                throw std::runtime_error("CSV rows have different sizes");
            }

            rcsv.push_back(r);
        }
    }

    if (rcsv.empty())
    {
        throw std::runtime_error("CSV file is empty");
    }

    GaussMatrix result(rcsv.size(), rcsv.begin()->size());

    for (int i = 0; i < result.rows(); ++i)
    {
        for (int j = 0; j < result.cols(); ++j)
        {
            result(i, j) = rcsv[i][j];
        }
    }

    return result;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix& matrix, int prec)
{
    for (int j = 0; j < matrix.cols() - 1; ++j)
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