#!/bin/bash
for file in *.cpp *.h; do
    if [ -f "$file" ]; then
        if [[ "$file" == *.h ]]; then
            clang-tidy "$file" -- -std=c++17 -x c++
        else
            clang-tidy "$file" -- -std=c++17
        fi
    fi
done
