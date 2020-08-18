//
//  module.h
//  OPEMU
//
//  Created by Meowthra on 2017/11/14.
//  Copyright © 2017年 Meowthra. All rights reserved.
//  Made in Taiwan.

#ifndef kern_opemu_h
#define kern_opemu_h

#include <stdint.h>
#include <i386/trap.h>
#include <kern/sched_prim.h>

#include "../mach/i386/thread_status.h"

/*
==== START UDIS86 PATCH =====
#include "udis86/libudis86/extern.h"

struct op {
    // one of either. order here matters.
    union {
        x86_saved_state64_t *state64;
        x86_saved_state32_t *state32;
    };

    enum {
        SAVEDSTATE_64,
        SAVEDSTATE_32,
    } state_flavor;

    // just another version of the above
    x86_saved_state_t *state;

    // disassembly object
    ud_t		*ud_obj;

    // boolean flag
    uint8_t		ring0;
};

typedef struct op op_t;
==== END UDIS86 PATCH =====
*/

/**
 * Trap handlers, analogous to a program's entry point
 * @param state: xnu's trap.c saved thread state
 */
int opemu_ktrap(x86_saved_state_t *state, uintptr_t *lo_spp);
void opemu_utrap(x86_saved_state_t *state);

/**
 * Forward declarations of private xnu functions
 */
extern void mach_call_munger(x86_saved_state_t *state);
extern void unix_syscall(x86_saved_state_t *);
extern void mach_call_munger64(x86_saved_state_t *state);
extern void unix_syscall64(x86_saved_state_t *);

#endif /* kern_opemu_h */
