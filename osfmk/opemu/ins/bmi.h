//
//  bmi.h
//  OpcodeEmulator
//
//  Created by Meowthra on 2019/1/29.
//  Copyright © 2019年 Meowthra. All rights reserved.
//  Made in Taiwan.

#ifndef bmi_h
#define bmi_h

#include "../opemu.h"

int bmi_instruction(x86_saved_state_t *state,
                    uint8_t vexreg,
                    uint8_t opcode,
                    uint8_t *modrm,
                    uint8_t high_reg,
                    uint8_t high_index,
                    uint8_t high_base,
                    uint8_t operand_size,
                    uint8_t leading_opcode,
                    uint8_t simd_prefix,
                    uint8_t *bytep,
                    uint8_t ins_size,
                    uint8_t modbyte,
                    int kernel_trap);

#endif /* bmi_h */
