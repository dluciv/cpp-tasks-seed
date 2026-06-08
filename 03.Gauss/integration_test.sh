#!/bin/bash

status=true

echo "A,B,C,b" > int_test_in.csv
echo "2,1,-1,8" >> int_test_in.csv
echo "-3,-1,2,-11" >> int_test_in.csv
echo "-2,1,2,-3" >> int_test_in.csv

echo "x" > int_test_expected.csv
echo "2.000000" >> int_test_expected.csv
echo "3.000000" >> int_test_expected.csv
echo "-1.000000" >> int_test_expected.csv

./gauss int_test_in.csv > int_test_out.csv

if cmp -s int_test_out.csv int_test_expected.csv; then
    echo "Integration test: PASSED"
else
    echo "Integration test: FAILED"
    status=false
fi

rm -f int_test_in.csv int_test_expected.csv int_test_out.csv

if [ "$status" = true ]; then
    exit 0
else
    exit 1
fi