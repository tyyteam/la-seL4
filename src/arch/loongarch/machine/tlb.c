/*
 * Copyright 2022, tyyteam
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#include <arch/machine.h>
#include <machine/tlb.h>
#include <linker.h>
#include <string.h>
#include <arch/kernel/traps.h>
#include <arch/machine/cache.h>

void local_flush_tlb_all(void)
{
	invtlb_all(INVTLB_CURRENT_ALL, 0, 0);
}

void setup_tlb_handler(void)
{
	static int run_once = 0;

	/* The tlb handlers are generated only once */
	if (!run_once) {
		memcpy((void *)tlbrentry, handle_tlb_refill, 0x80);
		local_flush_icache_range(tlbrentry, tlbrentry + 0x80);
		set_handler(EXCCODE_TLBI * VECSIZE, handle_tlb_load, VECSIZE);
		set_handler(EXCCODE_TLBL * VECSIZE, handle_tlb_load, VECSIZE);
		set_handler(EXCCODE_TLBS * VECSIZE, handle_tlb_store, VECSIZE);
		set_handler(EXCCODE_TLBM * VECSIZE, handle_tlb_modify, VECSIZE);
		set_handler(EXCCODE_TLBNR * VECSIZE, handle_tlb_protect, VECSIZE);
		set_handler(EXCCODE_TLBNX * VECSIZE, handle_tlb_protect, VECSIZE);
		set_handler(EXCCODE_TLBPE * VECSIZE, handle_tlb_protect, VECSIZE);
		run_once++;
	}
}

BOOT_CODE void init_tlb(void)
{
    write_csr_pagesize(PS_DEFAULT_SIZE);
    write_csr_stlbpgsize(PS_DEFAULT_SIZE);
    write_csr_tlbrefill_pagesize(PS_DEFAULT_SIZE);

    if (read_csr_pagesize() != PS_DEFAULT_SIZE)
        printf("MMU doesn't support PAGE_SIZE\n");

    setup_tlb_handler();
    local_flush_tlb_all();
}