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

//refer to genex.S for definitions
extern asmlinkage void handle_ade(void);
extern asmlinkage void handle_ale(void);
extern asmlinkage void handle_sys(void);
extern asmlinkage void handle_bp(void);
extern asmlinkage void handle_ri(void);
extern asmlinkage void handle_fpu(void);
extern asmlinkage void handle_fpe(void);
extern asmlinkage void handle_lbt(void);
extern asmlinkage void handle_lsx(void);
extern asmlinkage void handle_lasx(void);
extern asmlinkage void handle_reserved(void);
extern asmlinkage void handle_watch(void);
extern asmlinkage void handle_vint(void);
