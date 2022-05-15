/*
 * Copyright 2020, DornerWorks
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <util.h>
#include <api/types.h>
#include <arch/types.h>
#include <arch/model/statedata.h>
#include <arch/object/structures.h>
#include <linker.h>
#include <plat/machine/hardware.h>

/*CY 待修改 */
/* The top level asid mapping table */
asid_pool_t *riscvKSASIDTable[BIT(asidHighBits)];

/* Kernel Page Tables */
pde_t kernel_level0_pd[BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));

/*rv
#if __loongarch_xlen != 32
pte_t kernel_image_level2_pt[BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));
pte_t kernel_image_level2_dev_pt[BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));
#elif defined(CONFIG_KERNEL_LOG_BUFFER)
pte_t kernel_image_level2_log_buffer_pt[BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));
#endif
*/

pde_t kernel_level1_pd[64 * BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));
pte_t kernel_pt[4096 * BIT(PT_INDEX_BITS)] ALIGN_BSS(BIT(seL4_PageTableBits));

/*rv 暂时不知道作用，不用
SMP_STATE_DEFINE(core_map_t, coreMap);
*/