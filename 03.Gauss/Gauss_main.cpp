#include "Gauss_solve.h"

#include <exception>
#include <iostream>

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: gauss <input.csv>\n";
        return 1;
    }

    try
    {
        GaussMatrix matrix = load_csv_to_matrix(argv[1]);
        GaussVector solution = Gauss_solve(matrix);
        GaussMatrix output(solution.size(), 1);
        output.col(0) = solution;
        print_matrix_as_csv(std::cout, output);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Gauss error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}