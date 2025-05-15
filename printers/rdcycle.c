#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "../rlibsc.h"

int main() {
    size_t cycles = rdcycle();
    printf("CPU Cycles: %zu\n", cycles);
    return 0;
}
