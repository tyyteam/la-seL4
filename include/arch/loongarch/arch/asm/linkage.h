/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_LINKAGE_H
#define __ASM_LINKAGE_H

#define ALIGN __ALIGN
#define __ALIGN		.align 2
#define __ALIGN_STR	".align 2"
#define SYM_L_GLOBAL(name)			.globl name
#define SYM_A_ALIGN				ALIGN

#ifndef ASM_NL
#define ASM_NL		 ;
#endif

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

#define SYM_T_FUNC				STT_FUNC

#define SYM_END(name, sym_type)				\
	.type name sym_type ASM_NL			\
	.size name, .-name

#define SYM_ENTRY(name, linkage, align...)		\
	linkage(name) ASM_NL				\
	align ASM_NL					\
	name:

#define SYM_START(name, linkage, align...)		\
	SYM_ENTRY(name, linkage, align)

#define SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)	\
	.cfi_startproc;

#define SYM_FUNC_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)	\
	.cfi_startproc;

#define SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_A_ALIGN)	\
	.cfi_startproc;

#define SYM_FUNC_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)	\
	.cfi_startproc;

#define SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_A_ALIGN)	\
	.cfi_startproc;

#define SYM_FUNC_START_WEAK_NOALIGN(name)		\
	SYM_START(name, SYM_L_WEAK, SYM_A_NONE)		\
	.cfi_startproc;

#define SYM_FUNC_END(name)				\
	.cfi_endproc;					\
	SYM_END(name, SYM_T_FUNC)

#endif
