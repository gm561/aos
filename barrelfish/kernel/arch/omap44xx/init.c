/*
 * Copyright (c) 2009,2012, ETH Zurich. All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, CAB F.78, Universitaetstr. 6, CH-8092 Zurich,
 * Attn: Systems Group.
 */

/**
 * \file
 * \brief CPU driver init code for the OMAP44xx series SoCs.
 */

#include <kernel.h>
#include <string.h>
#include <init.h>
#include <exec.h>

#include <serial.h>
#include <stdio.h>
#include <global.h>

/**
 * \brief Kernel stack.
 *
 * This is the one and only kernel stack for a kernel instance.
 */
uintptr_t kernel_stack[KERNEL_STACK_SIZE/sizeof(uintptr_t)]
	__attribute__ ((aligned(8)));

/*
 * LED section
 */

/*
 * Doesn't work yet on the second LED for some reason...
 */
static void flash_leds(void)
{
    // TODO: Output enable

    while (true) {
        // TODO: Write data out

        // TODO: wait for approximately 1 second.
    }
}

// You might want to use this or some other fancy/creative banner ;-)
static const char banner[] =
"   ___                   ______     __ \n\r"\
"  / _ )___ ____________ / / _(_)__ / / \n\r"\
" / _  / _ `/ __/ __/ -_) / _/ (_-</ _ \\\n\r"\
"/____/\\_,_/_/ /_/  \\__/_/_//_/___/_//_/\n\r";

static const char myfancy[] = "ala ma kota\n\r i ma psa\n\r";

/**
 * Entry point called from boot.S for bootstrap processor.
 * if is_bsp == true, then pointer points to multiboot_info
 * else pointer points to a global struct
 */
void arch_init(void *pointer)
{
    serial_init(); // TODO: complete implementation of serial_init
    
    //serial_putchar(42);
    for(int i = 0; i <42*4; ++i) {
	serial_putchar(banner[i]);
    }
    // You should be able to call serial_purchar(42); here.
    // Also, you can call printf here!
    // TODO: Produce some output that will surprise your TA.
    flash_leds(); // TODO: complete implementation of flash_leds

    for(;;); // Infinite loop to keep the system busy.
}
