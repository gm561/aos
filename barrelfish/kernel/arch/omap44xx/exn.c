/*
 * Copyright (c) 2009 ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#include <kernel.h>
#include <dispatch.h>
#include <arm.h>
#include <arm_hal.h>
#include <cp15.h>
#include <exceptions.h>
#include <exec.h>
#include <misc.h>
#include <syscall.h>
#include <stdio.h>
#include <wakeup.h>

__attribute__((noreturn)) void sys_syscall_kernel(void);
__attribute__((noreturn)) void sys_syscall(arch_registers_state_t*);

void handle_user_page_fault(lvaddr_t                fault_address,
                            arch_registers_state_t* save_area)
{
    uintptr_t saved_pc = save_area->named.pc;
    panic("user page fault: addr %"PRIxLVADDR" IP %"PRIxPTR"\n",
           fault_address, saved_pc);
}

void handle_user_undef(lvaddr_t fault_address,
                       arch_registers_state_t* save_area)
{
    panic("user undef fault: IP %" PRIuPTR "\n", fault_address);
}

void fatal_kernel_fault(uint32_t evector, lvaddr_t address, arch_registers_state_t* save_area
    )
{
    panic("Kernel fault at %08"PRIxLVADDR" vector %08"PRIx32"\n", 
	  address, evector);
}

void handle_irq(arch_registers_state_t* save_area, uintptr_t fault_pc)
{
    panic("Unhandled IRQ\n");
}

void sys_syscall_kernel(void)
{
    panic("Why is the kernel making a system call?");
}
void sys_syscall(arch_registers_state_t* context)
{
    panic("Can't handle user mode syscalls yet");
}

