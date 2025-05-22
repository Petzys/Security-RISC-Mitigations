#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

sudo perf stat tar -czf testfile.tar.gz testfile
rm -f testfile.tar.gz
