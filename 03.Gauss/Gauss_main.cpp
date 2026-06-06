#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "Gauss_solve.h"

int main(int argc, const char *argv[])
{
    if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <input.csv>\n";
            return 1;
        }

    // Загружаем расширенную матрицу [A|b] из CSV
    GaussMatrix ab = load_csv_to_matrix(argv[1]);

    // Убираем отладочный вывод
    // std::cout << "Загруженная матрица (" << ab.rows() << "x" << ab.cols() << "):\n" << ab << "\n\n";

    // Решаем систему методом Гаусса
    GaussVector x = Gauss_solve(ab);

    // Выводим решение в CSV-формате
    std::cout << "X\n";
    std::cout << std::fixed << std::setprecision(6);

    for (int i = 0; i < x.size(); ++i)
        {
            std::cout << x(i) << "\n";
        }

    return 0;
}