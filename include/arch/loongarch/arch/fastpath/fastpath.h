/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include <config.h>
#include <util.h>
#include <linker.h>
#include <api/types.h>
#include <api/syscall.h>
#include <api/types.h>
#include <smp/lock.h>
#include <arch/machine/hardware.h>
#include <machine/fpu.h>

void slowpath(syscall_t syscall)
NORETURN;

static inline
void fastpath_call(word_t cptr, word_t r_msgInfo)
NORETURN;

static inline
#ifdef CONFIG_KERNEL_MCS
void fastpath_reply_recv(word_t cptr, word_t r_msgInfo, word_t reply)
#else
void fastpath_reply_recv(word_t cptr, word_t r_msgInfo)
#endif
NORETURN;

/* Use macros to not break verification */
#define endpoint_ptr_get_epQueue_tail_fp(ep_ptr) TCB_PTR(endpoint_ptr_get_epQueue_tail(ep_ptr))
#define cap_vtable_cap_get_vspace_root_fp(vtable_cap) PTE_PTR(cap_page_table_cap_get_capPTBasePtr(vtable_cap))

static inline void FORCE_INLINE switchToThread_fp(tcb_t *thread, pte_t *vroot, pde_t stored_hw_asid)
{
    asid_t asid = (asid_t)(stored_hw_asid);

    setVSpaceRoot(addrFromPPtr(vroot), asid);

    NODE_STATE(ksCurThread) = thread;
}

static inline void mdb_node_ptr_mset_mdbNext_mdbRevocable_mdbFirstBadged(
    mdb_node_t *node_ptr, word_t mdbNext,
    word_t mdbRevocable, word_t mdbFirstBadged)
{
    node_ptr->words[1] = mdbNext | (mdbRevocable << 1) | mdbFirstBadged;
}

static inline void mdb_node_ptr_set_mdbPrev_np(mdb_node_t *node_ptr, word_t mdbPrev)
{
    node_ptr->words[0] = mdbPrev;
}

static inline bool_t isValidVTableRoot_fp(cap_t vspace_root_cap)
{
    return cap_capType_equals(vspace_root_cap, cap_page_table_cap) &&
           cap_page_table_cap_get_capPTIsMapped(vspace_root_cap);
}

/* This is an accelerated check that msgLength, which appears
   in the bottom of the msgInfo word, is <= 4 and that msgExtraCaps
   which appears above it is zero. We are assuming that n_msgRegisters == 4
   for this check to be useful. By masking out the bottom 3 bits, we are
   really checking that n + 3 <= MASK(3), i.e. n + 3 <= 7 or n <= 4. */
compile_assert(n_msgRegisters_eq_4, n_msgRegisters == 4)
static inline int
fastpath_mi_check(word_t msgInfo)
{
    return (msgInfo & MASK(seL4_MsgLengthBits + seL4_MsgExtraCapBits)) > 4;
}

static inline void fastpath_copy_mrs(word_t length, tcb_t *src, tcb_t *dest)
{
    word_t i;
    register_t reg;

    /* assuming that length < n_msgRegisters */
    for (i = 0; i < length; i ++) {
        /* assuming that the message registers simply increment */
        reg = msgRegisters[0] + i;
        setRegister(dest, reg, getRegister(src, reg));
    }
}

static inline int fastpath_reply_cap_check(cap_t cap)
{
    return cap_capType_equals(cap, cap_reply_cap);
}

/** DONT_TRANSLATE */
static inline void NORETURN FORCE_INLINE fastpath_restore(word_t badge, word_t msgInfo, tcb_t *cur_thread)
{
    NODE_UNLOCK_IF_HELD;

#ifdef ENABLE_SMP_SUPPORT
    word_t sp;
    asm volatile("csrr %0, sscratch" : "=r"(sp));
    sp -= sizeof(word_t);
    *((word_t *)sp) = TCB_REF(cur_thread);
#endif

    c_exit_hook();

#ifdef CONFIG_HAVE_FPU
    lazyFPURestore(NODE_STATE(ksCurThread));
    set_tcb_fs_state(NODE_STATE(ksCurThread), isFpuEnable());
#endif

    register word_t badge_reg asm("a0") = badge;
    register word_t msgInfo_reg asm("a1") = msgInfo;
    register word_t cur_thread_reg asm("$t0") = TCB_REF(cur_thread);

    asm volatile(
        "ld.d  $ra, $t0, 0*%[REGSIZE]  \n"
        "ld.d  $sp, $t0, 1*%[REGSIZE]  \n"
        /* loongarch doesn't have gp register*/
        //"ld.d  $gp, $t0, 2*%[REGSIZE]  \n"
        /* skip tp */
        /* skip x5/$t0 */
        "ld.d  $t2, $t0, 6*%[REGSIZE]  \n"
        "ld.d  $s1, $t0, 7*%[REGSIZE]  \n"
        "ld.d  $s0, $t0, 8*%[REGSIZE]  \n"
        "ld.d  $a2, $t0, 11*%[REGSIZE] \n"
        "ld.d  $a3, $t0, 12*%[REGSIZE] \n"
        "ld.d  $a4, $t0, 13*%[REGSIZE] \n"
        "ld.d  $a5, $t0, 14*%[REGSIZE] \n"
        "ld.d  $a6, $t0, 15*%[REGSIZE] \n"
        "ld.d  $a7, $t0, 16*%[REGSIZE] \n"
        "ld.d  $s1, $t0, 17*%[REGSIZE] \n"
        "ld.d  $s2, $t0, 18*%[REGSIZE] \n"
        "ld.d  $s3, $t0, 19*%[REGSIZE] \n"
        "ld.d  $s4, $t0, 20*%[REGSIZE] \n"
        "ld.d  $s5, $t0, 21*%[REGSIZE] \n"
        "ld.d  $s6, $t0, 22*%[REGSIZE] \n"
        "ld.d  $s7, $t0, 23*%[REGSIZE] \n"
        "ld.d  $s8, $t0, 24*%[REGSIZE] \n"
        "ld.d  $t7, $t0, 25*%[REGSIZE]\n"
        "ld.d  $t8, $t0, 26*%[REGSIZE]\n"
        "ld.d  $t3, $t0, 27*%[REGSIZE] \n"
        "ld.d  $t4, $t0, 28*%[REGSIZE] \n"
        "ld.d  $t5, $t0, 29*%[REGSIZE] \n"
        "ld.d  $t6, $t0, 30*%[REGSIZE] \n"
        /* Get next restored tp */
        "ld.d  $t1, $t0, 3*%[REGSIZE]  \n"
        /* get restored tp */
        "add.d $tp, $t1, $r0  \n"
        /* get badv */  //it is sepc in riscv
        "ld.d  $t1, $t0, 34*%[REGSIZE]\n"
        "csrw $badv, $t1  \n"
#ifndef ENABLE_SMP_SUPPORT
        /* Write back sscratch with cur_thread_reg to get it back on the next trap entry */
        "csrw sscratch, $t0\n"
#endif
        "ld.d  $t1, $t0, 32*%[REGSIZE] \n"
        "csrw sstatus, $t1\n"

        "ld.d  $t1, $t0, 5*%[REGSIZE] \n"
        "ld.d  $t0, $t0, 4*%[REGSIZE] \n"
        "sret"
        : /* no output */
        : "r"(cur_thread_reg),
        [REGSIZE] "i"(sizeof(word_t)),
        "r"(badge_reg),
        "r"(msgInfo_reg)
        : "memory"
    );

    UNREACHABLE();
}

