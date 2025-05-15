#include <linux/module.h>
#include <linux/init.h>

// requires correct (custom) kernel
extern unsigned long mitigation_clear_icache_on_context_switch_enable;

static int __init enable_mitigation(void)
{
    pr_info("Enabling mitigation: clear_icache_on_context_switch is ON\n");
    mitigation_clear_icache_on_context_switch_enable = 1;
    return 0;
}

static void __exit disable_mitigation(void)
{
    pr_info("Disabling mitigation: clear_icache_on_context_switch is OFF\n");
    mitigation_clear_icache_on_context_switch_enable = 0;
}

module_init(enable_mitigation);
module_exit(disable_mitigation);

MODULE_LICENSE("GPL");
