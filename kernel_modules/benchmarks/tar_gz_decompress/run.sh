#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

sudo perf stat tar -xzf testfile.tar.gz
rm -f testfile
