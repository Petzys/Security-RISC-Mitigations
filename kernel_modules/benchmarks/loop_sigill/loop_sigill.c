#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static jmp_buf trycatch_buf;
static size_t cycles_start;
static size_t cycles_end;

// Get number of spend CPU cycpes
static inline size_t rdcycle()
{
    size_t val;
    asm volatile("rdcycle %0" : "=r"(val));
    return val;
}

static void unblock_signal(int signum)
{
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static void sigill_handler(int signum)
{
    (void)signum;

    cycles_end = rdcycle();

    unblock_signal(SIGILL);
    longjmp(trycatch_buf, 1);
}

static size_t measure_sigill_time()
{
    cycles_start = rdcycle();

    if (!setjmp(trycatch_buf))
    {
        asm volatile("unimp"); // illegal instruction
        puts("WE SHOULD NEVER SEE THIS");
    }
    return cycles_end - cycles_start;
}

int main(int argc, char* argv[])
{
    // set signal handler
    signal(SIGILL, sigill_handler);
    
    size_t sum = 0;
    const int nr_iterations = 100000;
    for (int i = 0; i < nr_iterations; ++i) {
        sum += measure_sigill_time();
    }

    printf("SIGILL handling took %zu cycles on average.\n", sum / nr_iterations);
}
