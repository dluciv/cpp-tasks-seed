#!/bin/bash

set -euo pipefail

status=true

mkdir -p .itest

# ---------------------------------------------------
echo "Запуск теста 1..."

cat > .itest/input.csv <<EOF
A,B,C
2,1,5
1,-3,-1
EOF

cat <<EOF > .itest/expected.csv
x
2.000000
1.000000
EOF

./gauss .itest/input.csv > .itest/output.csv

if cmp -s .itest/expected.csv .itest/output.csv; then
    echo "Integration test passed"
else
    echo "Integration test failed"
    status=false
fi

$status
