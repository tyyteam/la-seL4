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

#define UART_REG(x) ((volatile uint32_t *)(UART_PPTR + (x)))
// #define uart_read_reg(reg) (*(UART_REG(reg)))
// #define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

#ifdef CONFIG_PRINTING
void uart_drv_putchar(unsigned char c)
{
    while(!*UART_REG(UART_REG_LSR)&UART_REG_LSR_TFE);
    *UART_REG(UART_REG_DAT) = (c & 0xff);
    // while( (uart_read_reg(UART_REG_LSR) & UART_REG_LSR_TFE) == 0 );
    // uart_write_reg(UART_REG_DAT,c);
}
#endif /* CONFIG_PRINTING */

#ifdef CONFIG_DEBUG_BUILD
unsigned char uart_drv_getchar(void)
{
    while(!(*UART_REG(UART_REG_LSR) & UART_REG_LSR_DR));
    return *UART_REG(UART_REG_DAT);
    // while((uart_read_reg(UART_REG_LSR) & UART_REG_LSR_DR)==0);
    // return uart_read_reg(UART_REG_DAT);
    return 'c';
}
#endif /* CONFIG_DEBUG_BUILD */





