// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/kdebug.h>
#include <linux/ptrace.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Catch illegal CSR access and emulate on RISC-V");

static int illegal_insn_notifier(struct notifier_block *self, unsigned long val, void *data) {
    struct die_args *args = (struct die_args *)data;
    struct pt_regs *regs = args->regs;
    u32 insn;
    unsigned long pc;

    if (!user_mode(regs))
        return NOTIFY_DONE; // Only handle user space

    pc = regs->sepc;

    if (copy_from_user(&insn, (void __user *)pc, sizeof(insn))) {
        pr_err("Failed to fetch instruction at %lx\n", pc);
        return NOTIFY_DONE;
    }

    // Decode instruction: look for CSR reads
    // Example: rdcycle, rdtime, rdinstret are CSR instructions
    // rdcycle:    0xc0002073 (CSR 0xc00)
    // rdtime:     0xc0102073 (CSR 0xc01)
    // rdinstret:  0xc0202073 (CSR 0xc02)

    u32 opcode = insn & 0x7f; // Bits [6:0]
    u32 funct3 = (insn >> 12) & 0x7;
    u32 csr    = (insn >> 20) & 0xfff;

    if (opcode == 0x73 && funct3 == 0x2) {
        if (csr == 0xc00 || csr == 0xc01 || csr == 0xc02) {
            // Emulate the CSR read

            unsigned long value = 0;

            switch (csr) {
            case 0xc00: // cycle
                value = 123456; // Fake cycle count
                break;
            case 0xc01: // time
                value = 654321; // Fake timer
                break;
            case 0xc02: // instret
                value = 111111; // Fake instruction retired
                break;
            }

            // Destination register is bits [11:7]
            u32 rd = (insn >> 7) & 0x1f;
            if (rd != 0) { // rd != x0
                regs->regs[rd] = value;
            }

            // Advance PC to next instruction
            regs->sepc += 4;

            pr_info("Emulated CSR read 0x%x at PC=0x%lx into x%d with value=%lu\n", csr, pc, rd, value);

            return NOTIFY_STOP; // We handled it
        }
    }

    return NOTIFY_DONE;
}

static struct notifier_block nb = {
    .notifier_call = illegal_insn_notifier,
};

static int __init illegal_csr_emulator_init(void) {
    pr_info("Illegal CSR Emulator loaded\n");
    register_die_notifier(&nb);
    return 0;
}

static void __exit illegal_csr_emulator_exit(void) {
    unregister_die_notifier(&nb);
    pr_info("Illegal CSR Emulator unloaded\n");
}

module_init(illegal_csr_emulator_init);
module_exit(illegal_csr_emulator_exit);
