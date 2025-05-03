#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "../rlibsc.h"

int main() {
    size_t instructions = rdinstret();
    printf("Instructions Retired: %zu\n", instructions);
    return 0;
}
