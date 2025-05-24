#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running loop_sigill"

# for some reason, `perf stat` doesn't work properly for this test
# use `time` instead
{ time ./loop_sigill ; } &> ../loop_sigill.stat
