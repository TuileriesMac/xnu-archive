//
//  fma.h
//  OpcodeEmulator
//
//  Created by Kali on 2019/5/1.
//  Copyright © 2019 lvs1974. All rights reserved.
//  Made in Taiwan.

#ifndef fma_h
#define fma_h

#include "fpins.h"
#include "../opemu.h"

int fma_instruction(x86_saved_state_t *state,
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

#endif /* fma_h */
