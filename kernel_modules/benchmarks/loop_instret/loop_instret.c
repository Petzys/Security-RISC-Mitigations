#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "../../../rlibsc.h"

int main(int argc, char* argv[])
{
    const int nr_iterations = 10000;
    for (int i = 0; i < nr_iterations; ++i) {
        rdinstret();
    }
}