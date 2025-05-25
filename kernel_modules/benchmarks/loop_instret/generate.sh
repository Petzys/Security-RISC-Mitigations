#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

OUTPUT_FILE="loop_instret"

if [ ! -f "$OUTPUT_FILE" ]; then
echo "Generating $OUTPUT_FILE"
gcc -O0 loop_instret.c -o "$OUTPUT_FILE"
fi
