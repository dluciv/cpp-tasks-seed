#!/usr/bin/env bash
set -euo pipefail

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

python3 -c '
import csv
import pathlib
import random
import sys

folder = pathlib.Path(sys.argv[1])

for n in (1, 2, 3, 16, 64, 128):
    rng = random.Random(2026 + n)
    expected = [rng.randint(-5, 5) for _ in range(n)]

    with (folder / f"system_{n}.csv").open("w", newline="") as stream:
        writer = csv.writer(stream, lineterminator="\n")
        writer.writerow([f"A{i + 1}" for i in range(n)] + ["B"])

        for i in range(n):
            row = [rng.randint(-4, 4) for _ in range(n)]
            row[i] = sum(abs(row[j]) for j in range(n) if j != i) + 1
            rhs = sum(a * x for a, x in zip(row, expected))
            writer.writerow(row + [rhs])

    with (folder / f"expected_{n}.csv").open("w") as stream:
        stream.write("X\n")
        for value in expected:
            stream.write(f"{value:.6f}\n")
' "$tmpdir"

for n in 1 2 3 16 64 128; do
    ./gauss "$tmpdir/system_$n.csv" > "$tmpdir/result_$n.csv"
    cmp "$tmpdir/expected_$n.csv" "$tmpdir/result_$n.csv"
done

printf 'Gauss integration tests passed.\n'