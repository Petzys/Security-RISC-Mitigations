# Software Mitigations for "A Security RISC" by Gerlach, Weber, Zhang and Schwarz
This repository contains the software mitigations for the novel attack primitives presented in the IEEE S&P 2023 paper ["A Security RISC: Microarchitectural Attacks on Hardware RISC-V CPUs"](https://misc0110.net/files/riscv_attacks_sp23.pdf). 

This repository is part of a project in "CS4702-Computer Security" at University of Lübeck.

The proposed mitigations are:
- Disable+Emulate: Disable the RISC-V performance counters and emulate the values to make all attacks less reliable
- Catch+Wait: Wait on context switch to make Flush+Fault attacks less reliable
- Switch+Clear: Clear the I-Cache on every context switch to make Flush+Fault attacks infeasible

The mitigations require custom Linux kernel patches that can be found under [custom-kernel](./custom-kernel/).
