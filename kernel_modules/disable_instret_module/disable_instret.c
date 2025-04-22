#include <linux/module.h>
#include <linux/init.h>
#include <asm/csr.h>

static int __init disable_instret_user(void)
{
    pr_info("Disabling user access to instret\n");
    csr_clear(CSR_SCOUNTEREN, 1 << 2); // Clear instret bit
    return 0;
}

static void __exit restore_counters(void)
{
    pr_info("Restoring scounteren to allow instret\n");
    csr_set(CSR_SCOUNTEREN, 1 << 2); // Restore access if needed
}

module_init(disable_instret_user);
module_exit(restore_counters);

MODULE_LICENSE("GPL");
