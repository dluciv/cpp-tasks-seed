#!/usr/bin/env bash
set -euo pipefail

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

for length in 0 1 2 3 4 5 7 16 257 1027 65537; do
    python3 - "$length" "$tmpdir/input.bin" "$tmpdir/reference.b85" <<'PY'
import base64
import random
import sys

length = int(sys.argv[1])
generator = random.Random(42 + length)
data = generator.randbytes(length)

with open(sys.argv[2], 'wb') as stream:
    stream.write(data)

with open(sys.argv[3], 'wb') as stream:
    stream.write(base64.b85encode(data))
PY

    ./base85 -e < "$tmpdir/input.bin" > "$tmpdir/encoded.b85"
    cmp "$tmpdir/reference.b85" "$tmpdir/encoded.b85"

    ./base85 -d < "$tmpdir/reference.b85" > "$tmpdir/decoded.bin"
    cmp "$tmpdir/input.bin" "$tmpdir/decoded.bin"
done

printf 'Base85 integration tests passed.\n'