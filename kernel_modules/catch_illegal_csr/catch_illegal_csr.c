#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/ptrace.h>

static struct kprobe kp;

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    pr_info("Caught illegal instruction!\n");
    pr_info("EPC: 0x%lx\n", regs->epc);
    return 0;
}

static int __init my_kprobe_init(void)
{
    kp.symbol_name = "do_trap_insn_illegal";
    kp.pre_handler = handler_pre;

    if (register_kprobe(&kp) < 0) {
        pr_err("register_kprobe failed\n");
        return -1;
    }

    pr_info("kprobe registered\n");
    return 0;
}

static void __exit my_kprobe_exit(void)
{
    unregister_kprobe(&kp);
    pr_info("kprobe unregistered\n");
}

module_init(my_kprobe_init);
module_exit(my_kprobe_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Catch illegal instructions via kprobe");
