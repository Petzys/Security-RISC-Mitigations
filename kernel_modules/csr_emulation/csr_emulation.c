#include <linux/module.h>
#include <linux/init.h>

// requires correct (custom) kernel
extern unsigned long enable_mitigation_emulate_csr;

static int __init enable_mitigation(void)
{
    pr_info("Enabling mitigation: csr_emulation is ON\n");
    enable_mitigation_emulate_csr = 1;
    return 0;
}

static void __exit disable_mitigation(void)
{
    pr_info("Disabling mitigation: csr_emulation is OFF\n");
    enable_mitigation_emulate_csr = 0;
}

module_init(enable_mitigation);
module_exit(disable_mitigation);

MODULE_LICENSE("GPL");