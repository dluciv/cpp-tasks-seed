#!/bin/bash
set -e

python3 -c "
import random

random.seed(42)
n = 50
A = [[random.uniform(-50, 50) for _ in range(n)] for _ in range(n)]
true_x = [random.uniform(-10, 10) for _ in range(n)]
B = [sum(A[i][j] * true_x[j] for j in range(n)) for i in range(n)]

with open('test_input_AB.csv', 'w') as f:
    for i in range(n):
        row = A[i] + [B[i]]
        f.write(','.join(f'{val:.10f}' for val in row) + '\n')

with open('test_expected_X.csv', 'w') as f:
    for x in true_x:
        f.write(f'{x:.10f}\n')
"

./gauss test_input_AB.csv test_output_X.csv

python3 -c "
import sys

try:
    def read_vals(fname):
        with open(fname) as f:
            return [float(line.strip()) for line in f if line.strip()]
            
    expected = read_vals('test_expected_X.csv')
    output = read_vals('test_output_X.csv')
    
    for e, o in zip(expected, output):
        if abs(e - o) > 1e-4:
            print('[FAILED] The output differs from the expected result.')
            sys.exit(1)
            
    print('[OK] Integration test passed!')
    sys.exit(0)
except Exception as e:
    print('[FAILED] Error during comparison: ' + str(e))
    sys.exit(1)
"

rm -f test_input_AB.csv test_expected_X.csv test_output_X.csv