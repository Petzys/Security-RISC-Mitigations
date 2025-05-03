#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "../rlibsc.h"

int main() {
    uint64_t time = rdtime();
    printf("Time (rdtime): %llu\n", (unsigned long long)time);
    return 0;
}
