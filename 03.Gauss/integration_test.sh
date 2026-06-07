#!/bin/bash

set -e

status=true
PROGRAM="./gauss"

echo "Test 1: Solve from CSV"
$PROGRAM AB.csv output.csv
if [ -f output.csv ]; then
    echo "PASS: output.csv created"
else
    echo "FAIL: output.csv not created"
    status=false
fi

echo "Test 2: Compare with expected output"
cat > expected.csv << 'EOF'
A0,A1,B
1.000000,1.500000,4.000000
-0.000000,1.000000,2.000000

Solution:
x0,x1,
1.000000,2.000000
EOF

if diff --strip-trailing-cr output.csv expected.csv > /dev/null 2>&1; then
    echo "PASS: output matches expected"
else
    echo "FAIL: output differs"
    diff --strip-trailing-cr output.csv expected.csv
    status=false
fi

echo "Test 3: Generate random system"
$PROGRAM --generate 5
if [ $? -eq 0 ]; then
    echo "PASS: random system solved"
else
    echo "FAIL: random system failed"
    status=false
fi

rm -f output.csv expected.csv

$status
