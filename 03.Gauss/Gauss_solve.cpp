#include "Gauss_solve.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iomanip>

using namespace Eigen;

MatrixXd read_csv(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in.is_open()) throw std::runtime_error("Cannot open input file");

    std::string line, cell;
    std::vector<std::vector<double>> data;

    while (std::getline(in, line))
    {
        std::stringstream lineStream(line);
        std::vector<double> row;
        while (std::getline(lineStream, cell, ','))
        {
            row.push_back(std::stod(cell));
        }
        if (!row.empty()) data.push_back(row);
    }

    if (data.empty()) return MatrixXd(0, 0);

    int rows = data.size();
    int cols = data[0].size();
    MatrixXd mat(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            mat(i, j) = data[i][j];
        }
    }
    return mat;
}

void write_csv(const std::string& filename, const Eigen::VectorXd& x)
{
    std::ofstream out(filename);
    if (!out.is_open()) throw std::runtime_error("Cannot open output file");

    out << std::fixed << std::setprecision(10);
    for (int i = 0; i < x.size(); ++i)
    {
        out << x(i) << "\n";
    }
}

VectorXd solve_gauss(MatrixXd AB)
{
    int n = AB.rows();
    if (AB.cols() != n + 1)
    {
        throw std::invalid_argument("Invalid size");
    }

    for (int i = 0; i < n; ++i)
    {
        int max_row = i;
        double max_val = std::abs(AB(i, i));
        for (int k = i + 1; k < n; ++k)
        {
            if (std::abs(AB(k, i)) > max_val)
            {
                max_val = std::abs(AB(k, i));
                max_row = k;
            }
        }

        if (max_val < 1e-12)
        {
            throw std::runtime_error("Singular");
        }

        if (max_row != i)
        {
            AB.row(i).swap(AB.row(max_row));
        }

        for (int k = i + 1; k < n; ++k)
        {
            double factor = AB(k, i) / AB(i, i);
            AB.row(k) -= factor * AB.row(i);
        }
    }

    VectorXd x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        x(i) = AB(i, n);
        if (i < n - 1)
        {
            int len = n - 1 - i;
            x(i) -= AB.row(i).segment(i + 1, len).dot(x.segment(i + 1, len));
        }
        x(i) /= AB(i, i);
    }

    return x;
}