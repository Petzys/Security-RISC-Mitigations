#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running make on the linux kernel"

# have make switch to the kernel directory
KERNEL_DIR="../../../custom-kernel/visionfive-linux-mitigations/"

# build kernel
sudo perf stat -o ../make.stat make -C "$KERNEL_DIR" ARCH=riscv -j$(nproc) bindeb-pkg

# remove output
rm -f ../linux-*riscv64.deb
rm -f ../linux-*riscv64.buildinfo
rm -f ../linux-*riscv64.changes
