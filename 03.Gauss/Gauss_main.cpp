#include <iostream>
#include <fstream>
#include "util.h"
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_csv_file>\n";
        return 1;
    }

    GaussMatrix Ab = load_csv_to_matrix(argv[1]);

    GaussVector solution = Gauss_solve(Ab);

    std::cout << "Solution vector:\n";
    for (int i = 0; i < solution.size(); ++i)
    {
        std::cout << solution(i) << "\n";
    }

    return 0;
}