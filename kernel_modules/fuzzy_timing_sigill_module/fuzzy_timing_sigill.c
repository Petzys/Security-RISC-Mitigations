#include <linux/module.h>
#include <linux/init.h>

// requires correct (custom) kernel
extern unsigned long mitigation_fuzzy_timing_SIGILL_cycles;

static int __init enable_mitigation(void)
{
    pr_info("Enabling mitigation: fuzzy_timing_SIGILL_cycles set to 128K\n");
    mitigation_fuzzy_timing_SIGILL_cycles = 128 * 1024;
    return 0;
}

static void __exit disable_mitigation(void)
{
    pr_info("Disabling mitigation: fuzzy_timing_SIGILL_cycles set to 0\n");
    mitigation_fuzzy_timing_SIGILL_cycles = 0;
}

module_init(enable_mitigation);
module_exit(disable_mitigation);

MODULE_LICENSE("GPL");
