//
//  avx.h
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/26.
//  Copyright © 2019 lvs1974. All rights reserved.
//  Made in Taiwan.

#ifndef avx_h
#define avx_h

#include "../opemu.h"

int avx_instruction(x86_saved_state_t *state,
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

#endif /* avx_h */
