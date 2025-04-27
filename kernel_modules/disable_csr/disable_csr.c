#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <asm/csr.h>
#include <linux/smp.h> // For on_each_cpu()

static void disable_csr(void *info)
{
    csr_clear(CSR_SCOUNTEREN, 0b111); // Clear relevant CSR bits
}

static void enable_csr(void *info)
{
    csr_set(CSR_SCOUNTEREN, 0b111); // Restore access if needed
}

static int __init disable_csr_wrapper(void)
{
    pr_info("Disabling user access to cycle, time, instret\n");
    on_each_cpu(disable_csr, NULL, 1);
    return 0;
}

static void __exit enable_csr_wrapper(void)
{
    pr_info("Restoring scounteren to allow cycle, time, instret\n");
    on_each_cpu(enable_csr, NULL, 1);
}

module_init(disable_csr_wrapper);
module_exit(enable_csr_wrapper);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GitHub Nopilot");
MODULE_DESCRIPTION("Disable CSRs (time, cycle, instret) on all cores");