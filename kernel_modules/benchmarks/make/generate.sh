#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

# switch to kernel directory
cd ../../../custom-kernel/visionfive-linux-mitigations/

echo "Preparing kernel repo for benchmark build"

# set repo to known state
git checkout kernel-6.6.y
sudo cp arch/riscv/configs/starfive_visionfive2_defconfig .config
make ARCH=riscv olddefconfig
make clean
