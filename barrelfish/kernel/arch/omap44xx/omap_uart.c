/**
 * \file
 * \brief Kernel serial driver for the OMAP44xx UARTs.  Implements the
 * interface found in /kernel/include/serial.h
 */

/*
 * Copyright (c) 2012, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#include <kernel.h>
#include <arm.h>

#include <serial.h>

#define UART_BASE 0x48020000
#define UART_LSR ((volatile uint32_t*) 0x48020014)
#define UART_IER ((uint8_t* ) 0x48020004)
#define RX_FIFO_TRIG ((uint32_t*) 0x48020008)
#define TX_FIFO_TRIG ((uint32_t*) 0x48020008)
#define FIFO_EN ((uint32_t*) 0x48020008)
#define UART_LCR ((uint8_t*) 0x4802000C)

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

/**
 * \brief Initialize the console UART
 */
void serial_init(void)
{
  // TODO: Disable all interrupts
  uint8_t saved_ier = *UART_IER;
  
  // TODO: Enable FIFOs and select highest trigger levels
  // i.e.  RX_FIFO_TRIG = TX_FIFO_TRIG = 3, FIFO_EN = 1

  //enable fifo
  (*FIFO_EN) |= 1;

  //set to reg. values to 3
  (*RX_FIFO_TRIG) |= 1 << 4;
  (*RX_FIFO_TRIG) |= 1 << 5;
  (*TX_FIFO_TRIG) |= 1 << 6;
  (*TX_FIFO_TRIG) |= 1 << 7;

  //Set line to 8 bits, no parity, 1 stop bit
  
  //8 bits char length
  (*UART_LCR) |= 1 << 0;
  (*UART_LCR) |= 1 << 1;

  //1 stop bit
  (*UART_LCR) |= 0 << 2;
  (*UART_LCR) |= 0 << 5;

  //restore interrupts do we have to do this?
  (*UART_IER) = saved_ier;
}

/**
 * \brief Prints a single character to a serial port.
 */
void serial_putchar(char c)
{
  // TODO: Wait until FIFO can hold more characters (i.e. TX_FIFO_E == 1)
  while(!CHECK_BIT(*UART_LSR, 5))
    ;

  //Write character
  (*(char *) UART_BASE) = c;
}

