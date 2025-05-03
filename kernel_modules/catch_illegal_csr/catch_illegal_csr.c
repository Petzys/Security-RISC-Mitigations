#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

static struct kprobe kp;

static int handler_pre(struct kprobe *p, struct pt_regs *regs) // TODO: We are probably getting the kernel regs here, not the userspace one --> Use fprobes?
{
    u32 insn;
    if (get_user(insn, (u32 __user *)regs->epc)) {
        pr_warn("Failed to read instruction from EPC: 0x%lx\n", regs->epc);
    } else {
        pr_info("Fetched instruction: 0x%08x\n", insn);
    }

    u32 opcode  = insn & 0x7f;
    u32 rd      = (insn >> 7) & 0x1f;
    u32 funct3  = (insn >> 12) & 0x7;
    u32 rs1     = (insn >> 15) & 0x1f;
    u32 csr     = (insn >> 20) & 0xfff;

    pr_info("Instruction: 0x%08x\n", insn);
    pr_info("Opcode: 0x%02x, rd:0x%01x, funct3: 0x%01x, rs1: 0x%01x, csr: 0x%03x\n",
            opcode, rd, funct3, rs1, csr);

    if (opcode == 0x73 && funct3 == 0x2 && rs1 == 0) {
        if (csr == 0xC00 || csr == 0xC01 || csr == 0xC02) {
            pr_info("Blocked CSR read (0x%03x) from PID %d at 0x%lx\n",
                    csr, current->pid, regs->epc);
        }
    }

    return 0;
}

static int __init kprobe_init(void)
{
    kp.symbol_name = "do_trap";
    kp.pre_handler = handler_pre;

    if (register_kprobe(&kp) < 0) {
        pr_err("register_kprobe failed!\n");
        return -1;
    }

    pr_info("Kprobe registered on do_trap\n");
    return 0;
}

static void __exit kprobe_exit(void)
{
    unregister_kprobe(&kp);
    pr_info("Kprobe unregistered.\n");
}

module_init(kprobe_init);
module_exit(kprobe_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("bwe");
MODULE_DESCRIPTION("Kprobe to detect illegal CSR reads from userspace");
