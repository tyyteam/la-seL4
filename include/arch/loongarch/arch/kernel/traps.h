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

#define VECSIZE 0x200

unsigned long eentry;
unsigned long tlbrentry;
long exception_handlers[VECSIZE * 128 / sizeof(long)] ALIGN(SZ_64K);
