#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <lazycsv.hpp>

#include "util.h"
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input.csv>" << std::endl;
        return 1;
    }

    GaussMatrix ab = load_csv_to_matrix(argv[1]);

    std::cout << "Augmented matrix [A|b]:" << std::endl;
    std::cout << ab << std::endl << std::endl;

    GaussVector x = Gauss_solve(ab);

    std::cout << "Solution x:" << std::endl;
    std::cout << x << std::endl << std::endl;

    std::cout << "Result as CSV:" << std::endl;
    print_matrix_as_csv(std::cout, x, 6);

    return 0;
}
