#include <iostream>
#include <iomanip>

#include "util.h"
#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <AB.csv>\n";
        return 1;
    }

    GaussMatrix ab = load_csv_to_matrix(argv[1]);
    GaussVector x = Gauss_solve(ab);

    std::cout << "x\n";
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < x.size(); ++i)
        std::cout << x(i) << "\n";

    return 0;
}