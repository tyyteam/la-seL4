/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <config.h>
#include <model/statedata.h>
#include <arch/fastpath/fastpath.h>
#include <arch/kernel/traps.h>
#include <machine/debug.h>
#include <api/syscall.h>
#include <util.h>
#include <arch/machine/hardware.h>
#include <arch/machine.h>
#include <machine/fpu.h>

#include <benchmark/benchmark_track.h>
#include <benchmark/benchmark_utilisation.h>

/** DONT_TRANSLATE */
void VISIBLE NORETURN restore_user_context(void)
{
    word_t cur_thread_reg = (word_t) NODE_STATE(ksCurThread)->tcbArch.tcbContext.registers;
    c_exit_hook();
    NODE_UNLOCK_IF_HELD;

#ifdef ENABLE_SMP_SUPPORT
    word_t sp;
    asm volatile("csrrd %0, LOONGARCH_CSR_KS0" : "=r"(sp));//using LOONGARCH_CSR_KS0
    sp -= sizeof(word_t);
    *((word_t *)sp) = cur_thread_reg;
#endif


#ifdef CONFIG_HAVE_FPU
    lazyFPURestore(NODE_STATE(ksCurThread));
    set_tcb_fs_state(NODE_STATE(ksCurThread), isFpuEnable());
#endif

    asm volatile(
        "move $t0, %[cur_thread]        \n"
        "ld.d  $ra, $t0, 0*%[REGSIZE]   \n"
        /* skip tp */
        "ld.d  $sp, $t0, 2*%[REGSIZE]   \n"
        "ld.d  $a0, $t0, 3*%[REGSIZE]   \n"
        "ld.d  $a1, $t0, 4*%[REGSIZE]   \n"
        "ld.d  $a2, $t0, 5*%[REGSIZE]   \n"
        "ld.d  $a3, $t0, 6*%[REGSIZE]   \n"
        "ld.d  $a4, $t0, 7*%[REGSIZE]   \n"
        "ld.d  $a5, $t0, 8*%[REGSIZE]   \n"
        "ld.d  $a6, $t0, 9*%[REGSIZE]   \n"
        "ld.d  $a7, $t0, 10*%[REGSIZE]  \n"
        /* skip $r12/$t0 */
        /* no-op store conditional to clear monitor state */
        /* this may succeed in implementations with very large reservations, but the saved ra is dead */
        "sc.w  $zero, $t0, 0    \n"
        /* skip $r13/$t1 */
        "ld.d  $t2, $t0, 13*%[REGSIZE]  \n"
        "ld.d  $t3, $t0, 14*%[REGSIZE]  \n"
        "ld.d  $t4, $t0, 15*%[REGSIZE]  \n"
        "ld.d  $t5, $t0, 16*%[REGSIZE]  \n"
        "ld.d  $t6, $t0, 17*%[REGSIZE]  \n"
        "ld.d  $t7, $t0, 18*%[REGSIZE]  \n"
        "ld.d  $t8, $t0, 19*%[REGSIZE]  \n"
        "ld.d  $r21, $t0, 20*%[REGSIZE] \n"
        "ld.d  $fp, $t0, 21*%[REGSIZE]  \n"
        "ld.d  $s0, $t0, 22*%[REGSIZE]  \n"
        "ld.d  $s1, $t0, 23*%[REGSIZE]  \n"
        "ld.d  $s2, $t0, 24*%[REGSIZE]  \n"
        "ld.d  $s3, $t0, 25*%[REGSIZE]  \n"
        "ld.d  $s4, $t0, 26*%[REGSIZE]  \n"
        "ld.d  $s5, $t0, 27*%[REGSIZE]  \n"
        "ld.d  $s6, $t0, 28*%[REGSIZE]  \n"
        "ld.d  $s7, $t0, 29*%[REGSIZE]  \n"
        "ld.d  $s8, $t0, 30*%[REGSIZE]  \n"
        
        /* Get next restored tp */
        "ld.d  $t1, $t0, 1*%[REGSIZE]   \n"
        /* get restored tp */
        "add.d $tp, $t1, $r0    \n"

#ifndef ENABLE_SMP_SUPPORT
        /* Write back LOONGARCH_CSR_KS0 with cur_thread_reg to get it back on the next trap entry */
        "csrwr $t0, LOONGARCH_CSR_KS0   \n"
#endif
        //load [38*%[REGSIZE]+$t0] to LOONGARCH_CSR_ERA instead of 31*%[REGSIZE]

        "ld.d  $t1, $t0, 32*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_BADV  \n"

        "ld.d  $t1, $t0, 33*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_CRMD  \n"

        "ld.d  $t1, $t0, 34*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_PRMD  \n"        

        "ld.d  $t1, $t0, 35*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_EUEN  \n"    

        "ld.d  $t1, $t0, 36*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_ECFG  \n"               

        "ld.d  $t1, $t0, 37*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_ESTAT \n"

        "ld.d  $t1, $t0, 38*%[REGSIZE]  \n"
        "csrwr $t1, LOONGARCH_CSR_ERA   \n"

        "ld.d  $t1, $t0, 12*%[REGSIZE]  \n"
        "ld.d  $t0, $t0, 11*%[REGSIZE]  \n"
        "ertn"
        : /* no output */
        : [REGSIZE] "i"(sizeof(word_t)),
        [cur_thread] "r"(cur_thread_reg)
        : "memory"
    );

    UNREACHABLE();
}

void VISIBLE NORETURN c_handle_interrupt(void)
{
    NODE_LOCK_IRQ_IF(getActiveIRQ() != irq_remote_call_ipi);

    c_entry_hook();

    handleInterruptEntry();

    restore_user_context();
    UNREACHABLE();
}

// void VISIBLE NORETURN c_handle_exception(void)
// {
//     NODE_LOCK_SYS;

//     c_entry_hook();

//     word_t scause = read_scause();
//     switch (scause) {
//     case RISCVInstructionAccessFault:
//     case RISCVLoadAccessFault:
//     case RISCVStoreAccessFault:
//     case RISCVLoadPageFault:
//     case RISCVStorePageFault:
//     case RISCVInstructionPageFault:
//         handleVMFaultEvent(scause);
//         break;
//     default:
// #ifdef CONFIG_HAVE_FPU
//         if (!isFpuEnable()) {
//             /* we assume the illegal instruction is caused by FPU first */
//             handleFPUFault();
//             setNextPC(NODE_STATE(ksCurThread), getRestartPC(NODE_STATE(ksCurThread)));
//             break;
//         }
// #endif
//         handleUserLevelFault(scause, 0);
//         break;
//     }

//     restore_user_context();
//     UNREACHABLE();
// }

void VISIBLE NORETURN slowpath(syscall_t syscall)
{
    if (unlikely(syscall < SYSCALL_MIN || syscall > SYSCALL_MAX)) {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.path = Entry_UnknownSyscall;
#endif /* TRACK_KERNEL_ENTRIES */
        /* Contrary to the name, this handles all non-standard syscalls used in
         * debug builds also.
         */
        handleUnknownSyscall(syscall);
    } else {
#ifdef TRACK_KERNEL_ENTRIES
        ksKernelEntry.is_fastpath = 0;
#endif /* TRACK KERNEL ENTRIES */
        handleSyscall(syscall);
    }

    restore_user_context();
    UNREACHABLE();
}

#ifdef CONFIG_FASTPATH
ALIGN(L1_CACHE_LINE_SIZE)
#ifdef CONFIG_KERNEL_MCS
void VISIBLE c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo, word_t reply)
#else
void VISIBLE c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo)
#endif
{
    NODE_LOCK_SYS;

    c_entry_hook();
#ifdef TRACK_KERNEL_ENTRIES
    benchmark_debug_syscall_start(cptr, msgInfo, SysReplyRecv);
    ksKernelEntry.is_fastpath = 1;
#endif /* DEBUG */
#ifdef CONFIG_KERNEL_MCS
    fastpath_reply_recv(cptr, msgInfo, reply);
#else
    fastpath_reply_recv(cptr, msgInfo);
#endif
    UNREACHABLE();
}

ALIGN(L1_CACHE_LINE_SIZE)
void VISIBLE c_handle_fastpath_call(word_t cptr, word_t msgInfo)
{
    NODE_LOCK_SYS;

    c_entry_hook();
#ifdef TRACK_KERNEL_ENTRIES
    benchmark_debug_syscall_start(cptr, msgInfo, SysCall);
    ksKernelEntry.is_fastpath = 1;
#endif /* DEBUG */

    fastpath_call(cptr, msgInfo);

    UNREACHABLE();
}
#endif

void VISIBLE NORETURN c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
{
    NODE_LOCK_SYS;

    c_entry_hook();
#ifdef TRACK_KERNEL_ENTRIES
    benchmark_debug_syscall_start(cptr, msgInfo, syscall);
    ksKernelEntry.is_fastpath = 0;
#endif /* DEBUG */
    slowpath(syscall);

    UNREACHABLE();
}

// Code below will be modified or cleared later.

// void VISIBLE NORETURN do_vint(void){
//     //TODO interrupts related
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN cache_parity_error(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_ade(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_ale(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_bp(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_fpe(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_fpu(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_lsx(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_lasx(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_lbt(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_ri(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_watch(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_reserved(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN handle_syscall(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN do_page_fault(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }

// void VISIBLE NORETURN swapper_pg_dir(void){
//     //TODO
//     printf("not supported yet, will be supported soon.");
//     UNREACHABLE();
// }