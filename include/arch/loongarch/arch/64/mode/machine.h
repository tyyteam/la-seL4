/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include <util.h>
#include <arch/model/smp.h>
#include <stdint.h>

static inline uint64_t loongarch_read_time(void)
{
    /*
    word_t n;
    asm volatile("rdtime %0" : "=r"(n));
    return n;
    */
    int rID = 0;
	uint64_t val = 0;

	__asm__ __volatile__(
		"rdtime.d %0, %1 \n\t"
		: "=r"(val), "=r"(rID)
		:
		);
	return val;
}

static inline uint64_t loongarch_read_cycle(void)
{
    int rID = 0;
	uint64_t val = 0;

	__asm__ __volatile__(
		"rdtime.d %0, %1 \n\t"
		: "=r"(val), "=r"(rID)
		:
		);
	return val;
}
