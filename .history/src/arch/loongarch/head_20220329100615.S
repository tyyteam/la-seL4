/*
 * Copyright 2021, tyyteam(Qingtao Liu,Yang Lei and Yang Chen)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

 #include <config.h>
 #include <util.h>

.global _stext;
;
_stext:
.section ".ref.text", "ax"
.global kernel_entry;
.align 2;
kernel_entry:
    /* We might not get launched at the address the kernel is linked to,
	   so we jump there.  */
    la.abs		t0, 0f
	jirl		zero, t0, 0
0:
	la		t0, __bss_start		# clear .bss
	st.d		zero, t0, 0
	la		t1, __bss_stop - LONGSIZE
1:
	addi.d		t0, t0, LONGSIZE
	st.d		zero, t0, 0
	bne		t0, t1, 1b

	la		t0, fw_arg0
	st.d		a0, t0, 0		# firmware arguments
	la		t0, fw_arg1
	st.d		a1, t0, 0
	la		t0, fw_arg2
	st.d		a2, t0, 0
	la		t0, fw_arg3
	st.d		a3, t0, 0

	/* Config direct window and set PG */
	li.d		t0, CSR_DMW0_INIT	# UC, PLV0, 0x8000 xxxx xxxx xxxx
	csrwr		t0, LOONGARCH_CSR_DMWIN0
	li.d		t0, CSR_DMW1_INIT	# CA, PLV0, 0x9000 xxxx xxxx xxxx
	csrwr		t0, LOONGARCH_CSR_DMWIN1
	/* Enable PG */
	li.w		t0, 0xb0		# PLV=0, IE=0, PG=1
	csrwr		t0, LOONGARCH_CSR_CRMD
	li.w		t0, 0x04		# PLV=0, PIE=1, PWE=0
	csrwr		t0, LOONGARCH_CSR_PRMD
	li.w		t0, 0x00		# FPE=0, SXE=0, ASXE=0, BTE=0
	csrwr		t0, LOONGARCH_CSR_EUEN

	/* KScratch3 used for percpu base, initialized as 0 */
	csrwr		zero, PERCPU_BASE_KS
	/* GPR21 used for percpu base (runtime), initialized as 0 */
	or		u0, zero, zero

	la		tp, init_thread_union
	/* Set the SP after an empty pt_regs.  */
	PTR_LI		sp, (_THREAD_SIZE - 32 - PT_SIZE)
	PTR_ADDU	sp, sp, tp
	set_saved_sp	sp, t0, t1
	PTR_ADDIU	sp, sp, -4 * SZREG	# init stack pointer

	bl		start_kernel