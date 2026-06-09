#include <exception>
#include <iomanip>
#include <iostream>

#include "Gauss_solve.h"
#include "util.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " matrix.csv\n";
        return 1;
    }

    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        const GaussVector solution = Gauss_solve(ab);

        std::cout << "X\n" << std::fixed << std::setprecision(6);
        for (int i = 0; i < solution.rows(); ++i)
        {
            std::cout << solution(i) << '\n';
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
