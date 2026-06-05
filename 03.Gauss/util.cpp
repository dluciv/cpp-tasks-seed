#include "util.h"

#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>

#include <lazycsv.hpp>

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::vector<std::vector<double>> rows;

    lazycsv::parser parser{filename};

    for (const auto row : parser)
    {
        std::vector<double> values;
        bool numeric_row = true;

        for (const auto cell : row)
        {
            try
            {
                values.push_back(std::stod(std::string(cell.raw())));
            }
            catch (...)
            {
                numeric_row = false;
                break;
            }
        }

        if (numeric_row && !values.empty())
        {
            rows.push_back(values);
        }
    }

    if (rows.empty())
    {
        throw std::runtime_error("CSV does not contain numeric data");
    }

    const size_t cols = rows[0].size();

    for (const auto& row : rows)
    {
        if (row.size() != cols)
        {
            throw std::runtime_error("CSV table must be rectangular");
        }
    }

    if (cols != rows.size() + 1)
    {
        throw std::runtime_error("Expected augmented matrix with N rows and N + 1 columns");
    }

    GaussMatrix matrix(rows.size(), cols);

    for (Eigen::Index i = 0; i < matrix.rows(); ++i)
    {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j)
        {
            matrix(i, j) = rows[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
    }

    return matrix;
}

void print_solution_csv(std::ostream& out, const GaussVector& solution, int prec)
{
    out << "x\n";
    out << std::fixed << std::setprecision(prec);

    for (Eigen::Index i = 0; i < solution.size(); ++i)
    {
        out << solution(i) << '\n';
    }
}