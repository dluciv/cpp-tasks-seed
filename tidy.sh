#!/bin/bash
# Для Gauss: обрабатываем .cpp и .h отдельно, добавляем пути к Eigen и lazycsv
for file in *.cpp *.h; do
    if [ -f "$file" ]; then
        case "$file" in
            *.h)
                clang-tidy "$file" -- -std=c++17 -x c++ -I../external/eigen -I../external/lazycsv
                ;;
            *.cpp)
                clang-tidy "$file" -- -std=c++17 -I../external/eigen -I../external/lazycsv
                ;;
        esac
    fi
done
