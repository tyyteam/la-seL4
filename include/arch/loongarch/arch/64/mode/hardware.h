/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include <util.h>

// #if CONFIG_PT_LEVELS == 3

/*CY seL4_UserTop哪里来的？ */
/* last accessible virtual address in user space */
#define USER_TOP seL4_UserTop

/* The first physical address to map into the kernel's physical memory
 * window */
#define PADDR_BASE UL_CONST(0x0)

/* The base address in virtual memory to use for the 1:1 physical memory
 * mapping */
#define PPTR_BASE UL_CONST(0x0000900000000000)

/* Top of the physical memory window */
#define PPTR_TOP UL_CONST(0x000090FF80000000)

/* The physical memory address to use for mapping the kernel ELF */
/* This represents the physical address that the kernel image will be linked to. This needs to
 * be on a 1gb boundary as we currently require being able to creating a mapping to this address
 * as the largest frame size */
/*CY physBase好像是python生成的 */
#define KERNEL_ELF_PADDR_BASE (physBase + UL_CONST(0x4000000))

/* The base address in virtual memory to use for the kernel ELF mapping */
#define KERNEL_ELF_BASE (PPTR_TOP + (KERNEL_ELF_PADDR_BASE & MASK(30)))

/* The base address in virtual memory to use for the kernel device
 * mapping region. These are mapped in the kernel page table. */
#define KDEV_BASE UL_CONST(0x000090FFC0000000)

/* Place the kernel log buffer at the end of the kernel device page table */
/*CY 但是没考虑这个，暂定这个数 */
#define KS_LOG_PPTR UL_CONST(0x000090FFFFE00000)

// #else
// #error Only PT_LEVELS == 3 is supported
// #endif

#define LOAD  ld
#define STORE sd
