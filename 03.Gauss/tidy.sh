#!/bin/bash
for file in *.cpp *.h; do
    if [ -f "$file" ]; then
        if [[ "$file" == *.h ]]; then
            clang-tidy "$file" -- -std=c++17 -x c++ -I../external/eigen -I../external/lazycsv
        else
            clang-tidy "$file" -- -std=c++17 -I../external/eigen -I../external/lazycsv
        fi
    fi
done
