/*
 * tyyteam
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <config.h>
#include <stdint.h>
#include <util.h>
#include <machine/io.h>

#define UART_REG_DAT 0x00
#define UART_REG_IER 0x01
#define UART_REG_IIR 0x02
#define UART_REG_FCR 0x02
#define UART_REG_LCR 0x03
#define UART_REG_MCR 0x04
#define UART_REG_LSR 0x05
#define UART_REG_MSR 0x06

#define UART_REG_LSR_TFE BIT(5)
#define UART_REG_LSR_DR BIT(0)

#define UART0 (0x1fe001e0L)

#define UART_REG(reg) ((volatile uint8_t *) (UART0 + (reg)))
#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

#ifdef CONFIG_PRINTING
void uart_drv_putchar(unsigned char c)
{
    while((uart_read_reg(UART_REG_LSR) & UART_REG_LSR_TFE) == 0 );
    //while(!(*((volatile uint32_t *)0x1fe001e5L) & UART_REG_LSR_TFE));
    //while(!(*UART_REG(UART_REG_LSR) & UART_REG_LSR_TFE));
    //*UART_REG(UART_REG_DAT) = (c & 0xff);
    uart_write_reg(UART_REG_DAT,c);
}
#endif /* CONFIG_PRINTING */

#ifdef CONFIG_DEBUG_BUILD
unsigned char uart_drv_getchar(void)
{
    // while((uart_read_reg(UART_REG_LSR) & UART_REG_LSR_DR)==0);
    // return uart_read_reg(UART_REG_DAT);
    return 'c';
}
#endif /* CONFIG_DEBUG_BUILD */





