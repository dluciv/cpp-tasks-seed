#include <iostream>
#include "Gauss_solve.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_AB.csv> <output_X.csv>\n";
        return 1;
    }

    try
    {
        Eigen::MatrixXd AB = read_csv(argv[1]);
        Eigen::VectorXd x = solve_gauss(AB);
        write_csv(argv[2], x);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}