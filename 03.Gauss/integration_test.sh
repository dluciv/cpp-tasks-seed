#!/bin/bash

status=true

echo "Running integration test..."

./gauss AB.csv > /tmp/gauss_output.csv 2>&1
if [ $? -ne 0 ]; then
    echo "FAIL: gauss exited with non-zero status"
    status=false
fi

if [ ! -s /tmp/gauss_output.csv ]; then
    echo "FAIL: output is empty"
    status=false
fi

echo "Output:"
cat /tmp/gauss_output.csv

$status
