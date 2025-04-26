#include <linux/module.h>
#include <linux/init.h>
#include <asm/csr.h>

static int __init disable_csr_user(void)
{
    pr_info("Disabling user access to cycle, time, instret\n");
    csr_clear(CSR_SCOUNTEREN, 0b111); // Clear relevant CSR bits
    return 0;
}

static void __exit restore_counters(void)
{
    pr_info("Restoring scounteren to allow cycle, time, instret\n");
    csr_set(CSR_SCOUNTEREN, 0b111); // Restore access if needed
}

module_init(disable_csr_user);
module_exit(restore_counters);

MODULE_LICENSE("GPL");
