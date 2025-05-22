#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running tar decompression"

sudo perf stat -o ../decompress.stat tar -xzf testfile.tar.gz
rm -f testfile
