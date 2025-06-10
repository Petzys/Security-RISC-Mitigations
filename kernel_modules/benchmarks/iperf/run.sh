#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running iperf3"

# start server in the background
iperf3 -s -i 0 -1 --idle-timeout 3 &>/dev/null &

# run 60 second benchmark on a client with 10 parallel connections
sudo perf stat -o ../iperf.stat iperf3 -c 127.0.0.1 -i 0 -P 10 --time 60
