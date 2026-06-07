#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <lazycsv.hpp>

#include "Gauss_solve.h"
#include "util.h"

int main(int argc, const char* argv[])
{
    auto ab = load_csv_to_matrix(argv[1]);

    auto x = Gauss_solve(ab);

    GaussMatrix result(x.rows(), 1);
    result.col(0) = x;

    print_matrix_as_csv(std::cout, result);

    return 0;
}