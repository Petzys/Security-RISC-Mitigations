#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running tar compression"

sudo perf stat -o ../compress.stat tar -czf testfile.tar.gz testfile
rm -f testfile.tar.gz
