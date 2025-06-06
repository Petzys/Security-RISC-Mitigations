# Software Mitigations for "A Security RISC" by Gerlach, Weber, Zhang and Schwarz
This repository contains the software mitigations for the novel attack primitives presented in the IEEE S&P 2023 paper ["A Security RISC: Microarchitectural Attacks on Hardware RISC-V CPUs"](https://misc0110.net/files/riscv_attacks_sp23.pdf). 

This repository is part of a project in "CS4702-Computer Security" at University of Lübeck.

Testing Device:
- Board: StarFive VisionFive2 
- OS: [StarFive Debian 6.6.20](./custom-kernel/)

## Mitigations

The proposed mitigations are:
- Disable+Emulate: Disable the RISC-V performance counters and emulate the values to make all attacks less reliable
    - [Module (disable)](./kernel_modules/disable_csr/)
    - [Module (emulate)](./kernel_modules/csr_emulation/)
- Catch+Wait: Wait on context switch to make Flush+Fault attacks less reliable
    - [Module](./kernel_modules/fuzzy_timing_sigill/)
- Switch+Clear: Clear the I-Cache on every context switch to make Flush+Fault attacks infeasible
    - [Module](./kernel_modules/clear_icache_on_context_switch/)

The mitigations require custom Linux kernel patches that can be found under [custom-kernel](./custom-kernel/).

## Benchmarks

All benchmarks can be run automatically by using the [run-all.sh](./kernel_modules/benchmarks/run-all.sh) script:

```bash
cd ./kernel_modules/benchmarks && sudo ./run-all.sh
```

## Simple Testing Programs for Hardware Performance Counters

To test the availability of the performance counters and their output, we added simple testing programs that simply print the value of each counter. They can be found under [printers](./printers/).