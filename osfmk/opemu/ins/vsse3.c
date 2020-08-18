//
//  vsse3.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/8.
//  Copyright © 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vsse3.h"

/**********************************************/
/**  VSSE3  instructions implementation       **/
/**********************************************/
void vmovsldup_128(XMM src, XMM *res) {
    res->fa32[0] = src.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = src.fa32[2];
    res->fa32[3] = src.fa32[2];
}
void vmovsldup_256(YMM src, YMM *res) {
    res->fa32[0] = src.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = src.fa32[2];
    res->fa32[3] = src.fa32[2];
    res->fa32[4] = src.fa32[4];
    res->fa32[5] = src.fa32[4];
    res->fa32[6] = src.fa32[6];
    res->fa32[7] = src.fa32[6];
}

void vmovddup_128(XMM src, XMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = src.fa64[0];
}
void vmovddup_256(YMM src, YMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = src.fa64[0];
    res->fa64[2] = src.fa64[2];
    res->fa64[3] = src.fa64[2];
}

void vmovshdup_128(XMM src, XMM *res) {
    res->fa32[0] = src.fa32[1];
    res->fa32[1] = src.fa32[1];
    res->fa32[2] = src.fa32[3];
    res->fa32[3] = src.fa32[3];
}
void vmovshdup_256(YMM src, YMM *res) {
    res->fa32[0] = src.fa32[1];
    res->fa32[1] = src.fa32[1];
    res->fa32[2] = src.fa32[3];
    res->fa32[3] = src.fa32[3];
    res->fa32[4] = src.fa32[5];
    res->fa32[5] = src.fa32[5];
    res->fa32[6] = src.fa32[7];
    res->fa32[7] = src.fa32[7];
}

void vlddqu_128(XMM src, XMM *res) {
    res->u128 = src.u128;
}
void vlddqu_256(YMM src, YMM *res) {
    res->u256 = src.u256;
}

void vhaddpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] + vsrc.fa64[1];
    res->fa64[1] = src.fa64[0] + src.fa64[1];
}
void vhaddpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[0] + vsrc.fa64[1];
    res->fa64[1] = src.fa64[0] + src.fa64[1];
    res->fa64[2] = vsrc.fa64[2] + vsrc.fa64[3];
    res->fa64[3] = src.fa64[2] + src.fa64[3];
}

void vhaddps_128(XMM src, XMM vsrc, XMM *res) {
    res->fa32[0] = vsrc.fa32[0] + vsrc.fa32[1];
    res->fa32[1] = vsrc.fa32[2] + vsrc.fa32[3];
    res->fa32[2] = src.fa32[0] + src.fa32[1];
    res->fa32[3] = src.fa32[2] + src.fa32[3];
}
void vhaddps_256(YMM src, YMM vsrc, YMM *res) {
    res->fa32[0] = vsrc.fa32[0] + vsrc.fa32[1];
    res->fa32[1] = vsrc.fa32[2] + vsrc.fa32[3];
    res->fa32[2] = src.fa32[0] + src.fa32[1];
    res->fa32[3] = src.fa32[2] + src.fa32[3];
    res->fa32[4] = vsrc.fa32[4] + vsrc.fa32[5];
    res->fa32[5] = vsrc.fa32[6] + vsrc.fa32[7];
    res->fa32[6] = src.fa32[4] + src.fa32[5];
    res->fa32[7] = src.fa32[6] + src.fa32[7];
}

void vhsubpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] - vsrc.fa64[1];
    res->fa64[1] = src.fa64[0] - src.fa64[1];
}
void vhsubpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[0] - vsrc.fa64[1];
    res->fa64[1] = src.fa64[0] - src.fa64[1];
    res->fa64[2] = vsrc.fa64[2] - vsrc.fa64[3];
    res->fa64[3] = src.fa64[2] - src.fa64[3];
}

void vhsubps_128(XMM src, XMM vsrc, XMM *res) {
    res->fa32[0] = vsrc.fa32[0] - vsrc.fa32[1];
    res->fa32[1] = vsrc.fa32[2] - vsrc.fa32[3];
    res->fa32[2] = src.fa32[0] - src.fa32[1];
    res->fa32[3] = src.fa32[2] - src.fa32[3];
}
void vhsubps_256(YMM src, YMM vsrc, YMM *res) {
    res->fa32[0] = vsrc.fa32[0] - vsrc.fa32[1];
    res->fa32[1] = vsrc.fa32[2] - vsrc.fa32[3];
    res->fa32[2] = src.fa32[0] - src.fa32[1];
    res->fa32[3] = src.fa32[2] - src.fa32[3];
    res->fa32[4] = vsrc.fa32[4] - vsrc.fa32[5];
    res->fa32[5] = vsrc.fa32[6] - vsrc.fa32[7];
    res->fa32[6] = src.fa32[4] - src.fa32[5];
    res->fa32[7] = src.fa32[6] - src.fa32[7];
}

void vaddsubpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] - src.fa64[0];
    res->fa64[1] = vsrc.fa64[1] + src.fa64[1];
}
void vaddsubpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[0] - src.fa64[0];
    res->fa64[1] = vsrc.fa64[1] + src.fa64[1];
    res->fa64[2] = vsrc.fa64[2] - src.fa64[2];
    res->fa64[3] = vsrc.fa64[3] + src.fa64[3];
}

void vaddsubps_128(XMM src, XMM vsrc, XMM *res) {
    res->fa32[0] = vsrc.fa32[0] - src.fa32[0];
    res->fa32[1] = vsrc.fa32[1] + src.fa32[1];
    res->fa32[2] = vsrc.fa32[2] - src.fa32[2];
    res->fa32[3] = vsrc.fa32[3] + src.fa32[3];
}
void vaddsubps_256(YMM src, YMM vsrc, YMM *res) {
    res->fa32[0] = vsrc.fa32[0] - src.fa32[0];
    res->fa32[1] = vsrc.fa32[1] + src.fa32[1];
    res->fa32[2] = vsrc.fa32[2] - src.fa32[2];
    res->fa32[3] = vsrc.fa32[3] + src.fa32[3];
    res->fa32[4] = vsrc.fa32[4] - src.fa32[4];
    res->fa32[5] = vsrc.fa32[5] + src.fa32[5];
    res->fa32[6] = vsrc.fa32[6] - src.fa32[6];
    res->fa32[7] = vsrc.fa32[7] + src.fa32[7];
}

int vsse3_instruction(x86_saved_state_t *state,
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
                      int kernel_trap)
{
    uint8_t imm;
    //uint8_t mod = *modrm >> 6; // ModRM.mod
    //uint8_t modreg = (*modrm >> 3) & 0x7;
    uint8_t num_dst = (*modrm >> 3) & 0x7;
    uint8_t num_src = *modrm & 0x7;

    if (high_reg) num_dst += 8;
    if (high_base) num_src += 8;

    uint64_t rmaddrs = 0;

    if (reg_size == 128) {
        XMM xmmsrc, xmmvsrc, xmmdst, xmmres;
        uint16_t rm_size = reg_size;

        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

        int consumed = get_consumed(modrm);
        imm = *((uint8_t*)&bytep[consumed]);
        ins_size += consumed;

        switch(opcode) {
        case 0x12:
            //VMOVSLDUP
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmovsldup_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMOVDDUP
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vmovddup_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x16:
            //VMOVSHDUP
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmovshdup_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF0:
            //VLDDQU
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vlddqu_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x7C:
            //VHADDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vhaddpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VHADDPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vhaddps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x7D:
            //VHSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vhsubpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VHSUBPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vhsubps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD0:
            //VADDSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vaddsubpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VADDSUBPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vaddsubps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        default:
            return 0;
        }

    } else if (reg_size == 256) {
        YMM ymmsrc, ymmvsrc, ymmdst, ymmres;
        uint16_t rm_size = reg_size;

        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

        int consumed = get_consumed(modrm);
        imm = *((uint8_t*)&bytep[consumed]);
        ins_size += consumed;

        switch(opcode) {
        case 0x12:
            //VMOVSLDUP
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmovsldup_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VMOVDDUP
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vmovddup_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x16:
            //VMOVSHDUP
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmovshdup_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF0:
            //VLDDQU
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vlddqu_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x7C:
            //VHADDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vhaddpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VHADDPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vhaddps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x7D:
            //VHSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vhsubpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VHSUBPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vhsubps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD0:
            //VADDSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vaddsubpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VADDSUBPS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vaddsubps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        default:
            return 0;
        }

    } else {
        return 0;
    }

    return ins_size;
}
