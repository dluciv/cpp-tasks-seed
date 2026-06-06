#!/bin/bash

status=true

# ---------------------------------------------------
# Тест 1: Известная система 3x3
# ---------------------------------------------------
cat > test_input.csv << 'EOF'
A,A,A,B
2,1,-1,8
-3,-1,2,-11
-2,1,2,-3
EOF

cat > expected_output.csv << 'EOF'
X
2.000000
3.000000
-1.000000
EOF

./gauss test_input.csv | tr -d '\r' > actual_output.csv
tr -d '\r' < expected_output.csv > expected_fixed.csv

if cmp -s actual_output.csv expected_fixed.csv; then
    echo "Known system test PASSED!"
else
    echo "Known system test FAILED!" >&2
    status=false
fi

rm -f test_input.csv expected_output.csv expected_fixed.csv actual_output.csv

# ---------------------------------------------------
# Тест 2: Случайная система с фиксированным seed
# ---------------------------------------------------
python -c "
import numpy as np
np.random.seed(42)
n = 5
A = np.random.randn(n, n)
b = np.random.randn(n)
np.savetxt('random_test.csv', np.hstack([A, b.reshape(-1,1)]), delimiter=',', header=','.join(['A']*n + ['B']), comments='')
x = np.linalg.solve(A, b)
np.savetxt('random_expected.csv', x, delimiter=',', header='X', comments='', fmt='%.6f')
" 2>/dev/null

if [ -f random_test.csv ]; then
    ./gauss random_test.csv | tr -d '\r' > random_actual.csv
    tr -d '\r' < random_expected.csv > random_expected_fixed.csv

    if cmp -s random_actual.csv random_expected_fixed.csv; then
        echo "Random system test PASSED!"
    else
        echo "Random system test FAILED!" >&2
        status=false
    fi

    rm -f random_test.csv random_expected.csv random_expected_fixed.csv random_actual.csv
else
    echo "Python not found or numpy missing, skipping random test"
fi

# ---------------------------------------------------

$status