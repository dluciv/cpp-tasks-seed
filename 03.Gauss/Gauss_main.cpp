#include <iostream>
#include "util.h"
#include "Gauss_solve.h"


int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Используйте: " << argv[0] << " input.csv\n";
        return 1;
    }


    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        GaussVector x = Gauss_solve(ab);

        print_matrix_as_csv(std::cout, x);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}