#include <string>
#include <iomanip>
#include <lazycsv.hpp>
#include <stdexcept>
#include <vector>

#include "util.h"

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::vector<std::vector<double>> rows;
    lazycsv::parser parser{filename};

    for (const auto& row : parser)
    {
        std::vector<double> values;
        bool valid_row = true;

        for (const auto& cell : row)
        {
            try
            {
                values.push_back(std::stod(std::string(cell.raw())));
            }
            catch (...)
            {
                valid_row = false;
                break;
            }
        }

        if (valid_row && !values.empty())
        {
            rows.push_back(values);
        }
    }

    if (rows.empty())
    {
        throw std::runtime_error("CSV-файл не содержит числовых данных");
    }

    const size_t cols = rows[0].size();


    for (const auto& row : rows)
    {
        if (row.size() != cols)
        {
            throw std::runtime_error("Таблица CSV должна быть прямоугольной");
        }
    }


    if (cols != rows.size() + 1)
    {
        throw std::runtime_error("Ожидаемая расширенная матрица с N строками и N + 1 столбцом");
    }

    GaussMatrix matrix(rows.size(), cols);
    for (size_t i = 0; i < rows.size(); ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix(i, j) = rows[i][j];
        }
    }

    return matrix;
}




void print_matrix_as_csv(std::ostream& out, const GaussVector& x, int prec)
{
    out << "x\n";
    out << std::fixed << std::setprecision(prec);

    for (Eigen::Index i = 0; i < x.size(); ++i)
    {
        out << x(i) << '\n';
    }
}
