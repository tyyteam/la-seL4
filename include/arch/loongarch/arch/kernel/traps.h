/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include <config.h>
#include <util.h>
#include <types.h>

/* This file contains some error handler statements*/

static inline void arch_c_entry_hook(void)
{
    /* Nothing architecture specific to be done. */
}

static inline void arch_c_exit_hook(void)
{
    /* Nothing architecture specific to be done. */
}

//refer to genex.S for definitions
extern void handle_ade(void);
extern void handle_ale(void);
extern void handle_sys(void);
extern void handle_bp(void);
extern void handle_ri(void);
extern void handle_fpu(void);
extern void handle_fpe(void);
extern void handle_lbt(void);
extern void handle_lsx(void);
extern void handle_lasx(void);
extern void handle_reserved(void);
extern void handle_watch(void);
extern void handle_vint(void);

#ifdef CONFIG_KERNEL_MCS
void c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo, word_t reply)
#else
void c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo)
#endif
VISIBLE NORETURN;

void c_handle_fastpath_call(word_t cptr, word_t msgInfo)
VISIBLE NORETURN;

void c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
VISIBLE NORETURN;

void do_vint(void)
VISIBLE NORETURN;

void cache_parity_error(void)
VISIBLE NORETURN;

void do_ade(void)
VISIBLE NORETURN;

void do_ale(void)
VISIBLE NORETURN;

void do_bp(void)
VISIBLE NORETURN;

void do_fpe(void)
VISIBLE NORETURN;

void do_fpu(void)
VISIBLE NORETURN;

void do_lsx(void)
VISIBLE NORETURN;

void do_lasx(void)
VISIBLE NORETURN;

void do_lbt(void)
VISIBLE NORETURN;

void do_ri(void)
VISIBLE NORETURN;

void do_watch(void)
VISIBLE NORETURN;

void do_reserved(void)
VISIBLE NORETURN;

void handle_syscall(void)
VISIBLE NORETURN;

void do_page_fault(void)
VISIBLE NORETURN;

void swapper_pg_dir(void)
VISIBLE NORETURN;






void c_handle_interrupt(void)
VISIBLE NORETURN;

void c_handle_exception(void)
VISIBLE NORETURN;

void restore_user_context(void)
VISIBLE NORETURN;

void handle_exception(void);
