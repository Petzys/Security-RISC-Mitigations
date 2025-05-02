#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>
#include <fcntl.h>    // For O_CREAT, O_EXCL

static inline void flush(void* addr) {

    asm volatile("xor a7, a7, a7\n"
                 "add a7, a7, %0\n"
                 "fence.i\n\t"
    : : "r"(addr) : "a7","memory");
  }

typedef void (*fnc)();
int main(int argc, char** argv)
{
    while (1)
    {
        victim();
        
        if (argc > 1) {
            flush(0);
        } else {
            asm volatile ("nop");
        }
    }
}
