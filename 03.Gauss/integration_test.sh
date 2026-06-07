#!/bin/bash

status=true

# ---------------------------------------------------

cat > itest_ab.csv << 'CSVEOF'
A,A,A,B
2,1,1,7
4,3,3,19
8,7,9,49
CSVEOF

cat > itest_expected.csv << 'CSVEOF'
x
1.000000
2.000000
3.000000
CSVEOF

./gauss itest_ab.csv > itest_result.csv

if cmp -s itest_expected.csv itest_result.csv; then
    echo "Gauss 3x3 ok!"
else
    echo "Gauss 3x3 failed!" >&2
    status=false
fi

# ---------------------------------------------------

cat > itest_ab_expected.csv << 'CSVEOF'
x
-1.000000
2.000000
CSVEOF

./gauss AB.csv > itest_ab_result.csv

if cmp -s itest_ab_expected.csv itest_ab_result.csv; then
    echo "Gauss AB.csv ok!"
else
    echo "Gauss AB.csv failed!" >&2
    status=false
fi

# ---------------------------------------------------

$status