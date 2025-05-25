#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running loop_instret"
sudo perf stat -o ../loop_instret.stat ./loop_instret