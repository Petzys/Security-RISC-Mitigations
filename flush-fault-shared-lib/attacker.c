#include "mylib.h"
#include <stdint.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>

size_t cycle_start, cycle_end;

static jmp_buf trycatch_buf;
void unblock_signal(int signum) {
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static inline size_t rdtsc() {
    size_t val;
    asm volatile ("rdcycle %0" : "=r"(val));
    return val;
}

void trycatch_segfault_handler(int signum) {
    (void)signum;

    cycle_end = rdtsc();

    // puts("running fault handler");

    unblock_signal(SIGILL);
    unblock_signal(SIGSEGV);
    longjmp(trycatch_buf, 1);
}


static inline void flush(void* addr)
{
    asm volatile("xor a7, a7, a7 \n"
                 "add a7, a7, %0 \n"
                 "fence.i        \n"
    : : "r"(addr) : "a7", "memory");
}


size_t flush_fault_measure(void* addr)
{
    flush(addr);

    usleep(100000);

    if (!setjmp(trycatch_buf)) {
        sched_yield();
        
        cycle_start = rdtsc();
        asm volatile ("xor a5, a5, a5\n\t"
                      "xor a0, a0, a0\n\t"
                      "jr %0 \n\t" :: "r"(addr) : "memory", "a0", "a5");
        puts("WE SHOULD NEVER SEE THIS");
      }
      return cycle_end - cycle_start;
}


int main()
{
    void* jump_target = (void*)((size_t)control_flow_1 + 14);

    signal(SIGILL, trycatch_segfault_handler);
    
    for (int i = 0; i < 100; ++i) {
        size_t duration = flush_fault_measure(jump_target);
        if (i >= 50) {
            printf("%zu\n", duration);
        }
    }
}
