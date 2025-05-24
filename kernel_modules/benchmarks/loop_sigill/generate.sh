#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

OUTPUT_FILE="loop_sigill"

if [ ! -f "$OUTPUT_FILE" ]; then
echo "Generating $OUTPUT_FILE"
gcc -O2 loop_sigill.c -o "$OUTPUT_FILE"
fi
