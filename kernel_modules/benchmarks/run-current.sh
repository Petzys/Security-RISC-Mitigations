#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

./ffmpeg/generate.sh
sleep 3 # "cool down" the system
./ffmpeg/run.sh

./iperf/generate.sh
sleep 3
echo "Running iperf3"
./iperf/run.sh > iperf.log # iperf output (bandwidth) is interesting in addition to perf stat

./loop_sigill/generate.sh
sleep 3
./loop_sigill/run.sh

./tar_gz_compress/generate.sh
sleep 3
./tar_gz_compress/run.sh

./tar_gz_decompress/generate.sh
sleep 3
./tar_gz_decompress/run.sh

# run this last, because it's slow
if [ "$1" != "nomake" ]; then
./make/generate.sh
sleep 3
./make/run.sh
fi
