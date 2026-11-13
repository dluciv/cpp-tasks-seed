#include "util.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::ifstream input(filename);
    if (!input)
    {
        throw std::runtime_error("Cannot open CSV file");
    }

    std::vector<std::vector<double>> rows;
    std::string line;
    bool first_line = true;

    while (std::getline(input, line))
    {
        if (line.find_first_not_of(" \t\r") == std::string::npos)
        {
            continue;
        }

        std::vector<double> values;
        std::size_t start = 0;
        bool header = false;

        while (start <= line.size())
        {
            const std::size_t end = line.find(',', start);
            const std::string cell = line.substr(start, end - start);
            std::size_t used = 0;
            double number = 0.0;

            try
            {
                number = std::stod(cell, &used);
            }
            catch (const std::invalid_argument&)
            {
                if (first_line && values.empty())
                {
                    header = true;
                    break;
                }
                throw std::invalid_argument("Invalid number in CSV file");
            }
            catch (const std::out_of_range&)
            {
                throw std::invalid_argument("Number outside double range in CSV file");
            }

            if (cell.find_first_not_of(" \t\r", used) != std::string::npos ||
                !std::isfinite(number))
            {
                throw std::invalid_argument("Invalid number in CSV file");
            }

            values.push_back(number);
            if (end == std::string::npos)
            {
                break;
            }
            start = end + 1;
        }

        first_line = false;
        if (header)
        {
            continue;
        }

        if (!rows.empty() && values.size() != rows.front().size())
        {
            throw std::invalid_argument("CSV rows have different lengths");
        }
        rows.push_back(values);
    }

    if (rows.empty())
    {
        throw std::invalid_argument("CSV file contains no numeric rows");
    }

    GaussMatrix matrix(static_cast<Eigen::Index>(rows.size()),
                       static_cast<Eigen::Index>(rows.front().size()));

    for (Eigen::Index row = 0; row < matrix.rows(); ++row)
    {
        for (Eigen::Index column = 0; column < matrix.cols(); ++column)
        {
            matrix(row, column) = rows[static_cast<std::size_t>(row)]
                                      [static_cast<std::size_t>(column)];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix& matrix, int prec)
{
    for (Eigen::Index column = 0; column < matrix.cols(); ++column)
    {
        if (column > 0)
        {
            out << ',';
        }
        if (matrix.cols() == 1)
        {
            out << "X";
        }
        else if (column == matrix.cols() - 1)
        {
            out << "B";
        }
        else
        {
            out << 'A' << column + 1;
        }
    }
    out << '\n';

    out << std::fixed << std::setprecision(prec);
    const double zero_threshold = 0.5 * std::pow(10.0, -prec);

    for (Eigen::Index row = 0; row < matrix.rows(); ++row)
    {
        for (Eigen::Index column = 0; column < matrix.cols(); ++column)
        {
            if (column > 0)
            {
                out << ',';
            }

            const double value = matrix(row, column);
            out << (std::abs(value) < zero_threshold ? 0.0 : value);
        }
        out << '\n';
    }
}