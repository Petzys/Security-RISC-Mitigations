#include "mylib.h"

#define FUNC_ALIGN __attribute__((aligned(128)))

FUNC_ALIGN
void shared_lib_func(int secret)
{
    if (secret) {
        control_flow_1();
    } else {
        control_flow_2();
    }
}

FUNC_ALIGN
void control_flow_1()
{
    asm volatile (
        "j l1   \n"
        "nop    \n"
        "nop    \n"
        "nop    \n"
        "nop    \n"
        "nop    \n"
        "nop    \n"
        "unimp  \n"
        "unimp  \n"
        "unimp  \n"
        "nop    \n"
        "l1:nop \n"
    );
}

FUNC_ALIGN
void control_flow_2()
{
    asm volatile ("nop");
}
