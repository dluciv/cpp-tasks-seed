#!/bin/bash
set -e

dd bs=512 count=1 if=/dev/random of=random.bin 2>/dev/null
python3 -c 'import sys; import base64; sys.stdout.buffer.write(base64.b85encode(sys.stdin.buffer.read()))' <random.bin >random.b85

./base85 -e <random.bin >random.b85.test
./base85 -d <random.b85 >random.bin.test

if cmp -s random.b85 random.b85.test; then
    echo "Encoder OK"
else
    echo "Encoder FAILED"
    exit 1
fi

if cmp -s random.bin random.bin.test; then
    echo "Decoder OK"
else
    echo "Decoder FAILED"
    exit 1
fi

echo "All integration tests passed"
