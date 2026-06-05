#!/bin/bash

set -euo pipefail

status=true

mkdir -p .itest

cat > .itest/input.csv <<EOF
A,B,C
2,1,5
1,3,7
EOF

cat > .itest/expected.csv <<EOF
x
1.600000
1.800000
EOF

./debug .itest/input.csv > .itest/output.csv

if cmp -s .itest/expected.csv .itest/output.csv; then
    echo "Integration test passed"
else
    echo "Integration test failed"
    status=false
fi

$status