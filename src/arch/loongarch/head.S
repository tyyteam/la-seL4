/*
 * Copyright 2022, tyyteam(Qingtao Liu, Yang Lei and Yang Chen)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <config.h>
#include <util.h>

#include <arch/asm/asm.h>
#include <arch/asm/regdef.h>
#include <arch/asm/addrspace.h>
#include <arch/machine.h>


.section .boot.text, "ax"
.global _start
.extern kernel_stack_alloc


_start:                   # kernel entry point

	/* Config direct window and set PG */
	li.d		t0, CSR_DMW1_INIT	# CA, PLV0, 0x9000 xxxx xxxx xxxx
	csrwr		t0, LOONGARCH_CSR_DMWIN1

	/* Enable PG */
	li.w		t0, 0xb0		# PLV=0, IE=0, PG=1
	csrwr		t0, LOONGARCH_CSR_CRMD
	li.w		t0, 0x04		# PLV=0, PIE=1, PWE=0
	csrwr		t0, LOONGARCH_CSR_PRMD
	li.w		t0, 0x00		# FPE=0, SXE=0, ASXE=0, BTE=0
	csrwr		t0, LOONGARCH_CSR_EUEN

	/* We might not get launched at the address the kernel is linked to,
	 * so we jump there.  */
	la.abs		t0, 0f
	jirl		zero, t0, 0
0:
	la		t0, __bss_start		# clear .bss
	st.d		zero, t0, 0
	# la		t1, __bss_stop - LONGSIZE
	la 		t1, __bss_stop
	move    t2, zero
	addi.d    t2, t2, LONGSIZE
	sub.d     t1, t1, t2
1:
	addi.d		t0, t0, LONGSIZE
	st.d		zero, t0, 0
	bne		t0, t1, 1b

	la sp, kernel_stack_alloc
	addi.w t0, zero, 1
	slli.w t0, t0, CONFIG_KERNEL_STACK_BITS
	add.d sp, sp, t0
	csrwr zero, 0x30 /* zero LOONGARCH_CSR_KS0 for the init task */

	bl		init_kernel

	la ra, restore_user_context
	jirl zero, ra, 0
