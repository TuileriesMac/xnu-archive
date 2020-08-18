//
//  vsse.h
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/2.
//  Copyright (c) 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#ifndef vsse_h
#define vsse_h

#include "fpins.h"

#include "../opemu.h"

int vsse_instruction(x86_saved_state_t *state,
                     uint8_t vexreg,
                     uint8_t opcode,
                     uint8_t *modrm,
                     uint8_t high_reg,
                     uint8_t high_index,
                     uint8_t high_base,
                     uint16_t reg_size,
                     uint8_t operand_size,
                     uint8_t leading_opcode,
                     uint8_t simd_prefix,
                     uint8_t *bytep,
                     uint8_t ins_size,
                     uint8_t modbyte,
                     int kernel_trap);

int maxsf(float SRC1, float SRC2);
int minsf(float SRC1, float SRC2);
int cmpoptsf(float SRC1, float SRC2, uint8_t immvar);
float rcp_sf(float fp32);
float rsqrt_sf(float fp32);

#endif /* vsse_h */
