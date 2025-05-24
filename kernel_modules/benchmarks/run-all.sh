#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Testing baseline"
echo "Removing all modules"
sudo rmmod clear_icache_on_context_switch
sudo rmmod disable_csr
sudo rmmod csr_emulation
sudo rmmod fuzzy_timing_sigill
echo "Current modules:"
lsmod
./run-current.sh "$1" # pass argument along ("nomake")

# move results (use sudo, as some results are owned by root)
OUT_DIR="results/baseline/"
mkdir -p "$OUT_DIR"
sudo mv *.stat "$OUT_DIR"
sudo mv *.log  "$OUT_DIR"



echo "Testing mitigations"
sudo modprobe ./../fuzzy_timing_sigill/fuzzy_timing_sigill.ko
./run-current.sh "$1" # pass argument along ("nomake")
sudo rmmod fuzzy_timing_sigill

# move results (use sudo, as some results are owned by root)
OUT_DIR="results/catch_wait/"
mkdir -p "$OUT_DIR"
sudo mv *.stat "$OUT_DIR"
sudo mv *.log  "$OUT_DIR"



sudo modprobe ./../csr_emulation/csr_emulation.ko
sudo modprobe ./../disable_csr/disable_csr.ko
./run-current.sh "$1"
sudo rmmod disable_csr
sudo rmmod csr_emulation

# move results
OUT_DIR="results/disable_emulate/"
mkdir -p "$OUT_DIR"
sudo mv *.stat "$OUT_DIR"
sudo mv *.log  "$OUT_DIR"



# TODO
