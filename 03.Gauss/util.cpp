#include <string>
#include <iomanip>
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

                for (const auto cell : row)
                    {
                        std::string s(cell.raw());

                        // Пропускаем нечисловые строки (заголовки)
                        try
                            {
                                r.push_back(std::stod(s));
                            }
                        catch (const std::invalid_argument &)
                            {
                                r.clear();
                                break;  // это заголовок, пропускаем всю строку
                            }
                    }

                if (!r.empty())
                    {
                        rcsv.push_back(r);
                    }
            }
    }

    if (rcsv.empty())
        {
            throw std::runtime_error("Empty CSV file or no numeric data");
        }

    GaussMatrix mat(rcsv.size(), rcsv.begin()->size());

    for (size_t i = 0; i < rcsv.size(); ++i)
        for (size_t j = 0; j < rcsv[i].size(); ++j)
            {
                mat(i, j) = rcsv[i][j];
            }

    return mat;
}

void print_matrix_as_csv(std::ostream &out, const GaussMatrix &matrix, int prec)
{
    for (int j = 0; j < matrix.cols(); ++j)
        {
            out << "A,";
        }

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
