#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

OUTPUT_FILE="testfile"

if [ ! -f "$OUTPUT_FILE" ]; then
echo "Generating $OUTPUT_FILE"
base64 /dev/urandom | head -c 10000000 > testfile
fi
