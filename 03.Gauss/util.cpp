#include <string>
#include <iomanip>
#include <stdexcept>
#include <lazycsv.hpp>

#include "util.h"

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::vector<std::vector<double>> rcsv;
    lazycsv::parser parser{filename};
    bool header_checked = false;

    for (const auto row : parser)
    {
        std::vector<double> r;
        bool is_header = false;

        for (const auto cell : row)
        {
            if (!header_checked)
            {
                header_checked = true;
                try
                {
                    std::stod(std::string(cell.raw()));
                }
                catch (...)
                {
                    is_header = true;
                    break;
                }
            }
            r.push_back(std::stod(std::string(cell.raw())));
        }

        if (!is_header)
            rcsv.push_back(r);
    }

    if (rcsv.empty())
        throw std::runtime_error("Empty or invalid CSV file");

    int rows = static_cast<int>(rcsv.size());
    int cols = static_cast<int>(rcsv[0].size());

    for (int i = 1; i < rows; ++i)
        if (static_cast<int>(rcsv[i].size()) != cols)
            throw std::runtime_error("CSV rows have inconsistent number of columns");
    GaussMatrix mat(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat(i, j) = rcsv[i][j];
    return mat;
}

void print_matrix_as_csv(std::ostream &out, const GaussMatrix &matrix, int prec)
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
                out << ',';
        }
        out << '\n';
    }
}