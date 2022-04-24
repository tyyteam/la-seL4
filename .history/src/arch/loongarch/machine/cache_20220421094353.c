/*
 * Copyright 2022, tyyteam
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * LoongArch maintains ICache/DCache coherency by hardware,
 * we just need "ibar" to avoid instruction hazard here.
 */
void local_flush_icache_range(unsigned long start, unsigned long end)
{
	asm volatile ("\tibar 0\n"::);
}