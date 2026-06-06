#!/bin/bash
for file in *.cpp *.h *.c; do
    if [ -f "$file" ]; then
        case "$file" in
            *.c)
                clang-tidy "$file" -- -std=c11
                ;;
            *.h)
                clang-tidy "$file" -- -std=c++17 -x c++
                ;;
            *.cpp)
                clang-tidy "$file" -- -std=c++17 -I../external/gtest/include
                ;;
        esac
    fi
done
