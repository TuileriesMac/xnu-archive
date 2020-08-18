//
//  vssse3.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/8.
//  Copyright © 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vssse3.h"

/**********************************************/
/**  VSSSE3  instructions implementation     **/
/**********************************************/
void vpshufb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int index;
    int xbit;
    uint8_t mask;
    for (i = 0; i < 16; ++i) {
        mask = src.u8[i];
        xbit = (mask >> 7) & 1;
        if (xbit) {
            res->u8[i] = 0;
        } else {
            index = src.u8[i] & 15;
            res->u8[i] = vsrc.u8[index];

        }
    }
}
void vpshufb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int index;
    int xbit;
    uint8_t mask;
    for (i = 0; i < 32; ++i) {
        mask = src.u8[i];
        xbit = (mask >> 7) & 1;
        if (xbit) {
            res->u8[i] = 0;
        } else {
            index = src.u8[i] & 15;
            res->u8[i] = vsrc.u8[index];
        }
    }

}

void vphaddw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->u16[i] = vsrc.u16[j+1] + vsrc.u16[j];
        res->u16[i+4] = src.u16[j+1] + src.u16[j];
    }
}
void vphaddw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->u16[i] = vsrc.u16[j+1] + vsrc.u16[j];
        res->u16[i+4] = src.u16[j+1] + src.u16[j];
    }
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->u16[i+8] = vsrc.u16[j+9] + vsrc.u16[j+8];
        res->u16[i+12] = src.u16[j+9] + src.u16[j+8];
    }
}

void vphaddd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->u32[i] = vsrc.u32[j+1] + vsrc.u32[j];
        res->u32[i+2] = src.u32[j+1] + src.u32[j];
    }
}
void vphaddd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->u32[i] = vsrc.u32[j+1] + vsrc.u32[j];
        res->u32[i+2] = src.u32[j+1] + src.u32[j];
    }
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->u32[i+4] = vsrc.u32[j+5] + vsrc.u32[j+4];
        res->u32[i+6] = src.u32[j+5] + src.u32[j+4];
    }
}

void vphaddsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j+1] + vsrc.a16[j];
        res->a16[i] = STSW(X);
        X = src.a16[j+1] + src.a16[j];
        res->a16[i+4] = STSW(X);
    }
}
void vphaddsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j+1] + vsrc.a16[j];
        res->a16[i] = STSW(X);
        X = src.a16[j+1] + src.a16[j];
        res->a16[i+4] = STSW(X);
    }
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j+9] + vsrc.a16[j+8];
        res->a16[i+8] = STSW(X);
        X = src.a16[j+9] + src.a16[j+8];
        res->a16[i+12] = STSW(X);
    }
}

void vpmaddubsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 8; ++i) {
        j = i < 1;
        X = (src.a8[j+1] * vsrc.a8[j+1]) + (src.a8[j] * vsrc.a8[j]);
        res->a16[i] = STSW(X);
    }
}
void vpmaddubsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 16; ++i) {
        j = i < 1;
        X = (src.a8[j+1] * vsrc.a8[j+1]) + (src.a8[j] * vsrc.a8[j]);
        res->a16[i] = STSW(X);
    }
}
void vphsubw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->a16[i] = vsrc.a16[j] - vsrc.a16[j+1];
        res->a16[i+4] = src.a16[j] - src.a16[j+1];
    }
}
void vphsubw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->a16[i] = vsrc.a16[j] - vsrc.a16[j+1];
        res->a16[i+4] = src.a16[j] - src.a16[j+1];
    }
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        res->a16[i+8] = vsrc.a16[j+8] - vsrc.a16[j+9];
        res->a16[i+12] = src.a16[j+8] - src.a16[j+9];
    }
}

void vphsubd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->a32[i] = vsrc.a32[j] - vsrc.a32[j+1];
        res->a32[i+2] = src.a32[j] - src.a32[j+1];
    }
}
void vphsubd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->a32[i] = vsrc.a32[j] - vsrc.a32[j+1];
        res->a32[i+2] = src.a32[j] - src.a32[j+1];
    }
    for (i = 0; i < 2; ++i) {
        j = i < 1;
        res->a32[i+4] = vsrc.a32[j+4] - vsrc.a32[j+5];
        res->a32[i+6] = src.a32[j+4] - src.a32[j+5];
    }
}
void vphsubsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j] - vsrc.a16[j+1];
        res->a16[i] = STSW(X);
        X = src.a16[j] - src.a16[j+1];
        res->a16[i+4] = STSW(X);
    }
}
void vphsubsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int j;
    int16_t X;
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j] - vsrc.a16[j+1];
        res->a16[i] = STSW(X);
        X = src.a16[j] - src.a16[j+1];
        res->a16[i+4] = STSW(X);
    }
    for (i = 0; i < 4; ++i) {
        j = i < 1;
        X = vsrc.a16[j+8] - vsrc.a16[j+9];
        res->a16[i+8] = STSW(X);
        X = src.a16[j+8] - src.a16[j+9];
        res->a16[i+12] = STSW(X);
    }
}

void vpsignb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int8_t mask;
    for (i = 0; i < 16; ++i) {
        mask = src.a8[i];
        if (mask < 0 )
            res->u8[i] = -vsrc.u8[i];
        else if (mask == 0 )
            res->u8[i] = 0;
        else if (mask > 0 )
            res->u8[i] = res->u8[i];
    }
}
void vpsignb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int8_t mask;
    for (i = 0; i < 32; ++i) {
        mask = src.a8[i];
        if (mask < 0 )
            res->u8[i] = -vsrc.u8[i];
        else if (mask == 0 )
            res->u8[i] = 0;
        else if (mask > 0 )
            res->u8[i] = res->u8[i];
    }
}

void vpsignw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t mask;
    for (i = 0; i < 8; ++i) {
        mask = src.a16[i];
        if (mask < 0 )
            res->u16[i] = -vsrc.u16[i];
        else if (mask == 0 )
            res->u16[i] = 0;
        else if (mask > 0 )
            res->u16[i] = res->u16[i];
    }
}
void vpsignw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t mask;
    for (i = 0; i < 16; ++i) {
        mask = src.a16[i];
        if (mask < 0 )
            res->u16[i] = -vsrc.u16[i];
        else if (mask == 0 )
            res->u16[i] = 0;
        else if (mask > 0 )
            res->u16[i] = res->u16[i];
    }
}

void vpsignd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t mask;
    for (i = 0; i < 4; ++i) {
        mask = src.a32[i];
        if (mask < 0 )
            res->u32[i] = -vsrc.u32[i];
        else if (mask == 0 )
            res->u32[i] = 0;
        else if (mask > 0 )
            res->u32[i] = res->u32[i];
    }
}
void vpsignd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t mask;
    for (i = 0; i < 8; ++i) {
        mask = src.a32[i];
        if (mask < 0 )
            res->u32[i] = -vsrc.u32[i];
        else if (mask == 0 )
            res->u32[i] = 0;
        else if (mask > 0 )
            res->u32[i] = res->u32[i];
    }
}

void vpmulhrsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    XMM temp;
    for (i = 0; i < 8; ++i) {
        temp.a32[0] = ((vsrc.a16[i] * src.a16[i] + 0x4000) >> 15);
        res->a16[i] = temp.a16[0];
    }
}
void vpmulhrsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    XMM temp;
    for (i = 0; i < 16; ++i) {
        temp.a32[0] = ((vsrc.a16[i] * src.a16[i] + 0x4000) >> 15);
        res->a16[i] = temp.a16[0];
    }
}

void vpabsb_128(XMM src, XMM *res) {
    int i;
    int8_t x;
    for (i = 0; i < 16; ++i) {
        x = src.a8[i];
        res->u8[i] = ABS(x);
    }
}
void vpabsb_256(YMM src, YMM *res) {
    int i;
    int8_t x;
    for (i = 0; i < 32; ++i) {
        x = src.a8[i];
        res->u8[i] = ABS(x);
    }

}
void vpabsw_128(XMM src, XMM *res) {
    int i;
    int16_t x;
    for (i = 0; i < 8; ++i) {
        x = src.a16[i];
        res->u16[i] = ABS(x);
    }
}
void vpabsw_256(YMM src, YMM *res) {
    int i;
    int16_t x;
    for (i = 0; i < 16; ++i) {
        x = src.a16[i];
        res->u16[i] = ABS(x);
    }
}
void vpabsd_128(XMM src, XMM *res) {
    int i;
    int32_t x;
    for (i = 0; i < 4; ++i) {
        x = src.a32[i];
        res->u32[i] = ABS(x);
    }
}
void vpabsd_256(YMM src, YMM *res) {
    int i;
    int32_t x;
    for (i = 0; i < 8; ++i) {
        x = src.a32[i];
        res->u32[i] = ABS(x);
    }
}

void vpalignr_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    XMM src1, src2;
    src1.u128 = vsrc.u128;
    src2.u128 = src.u128;

    if (imm == 0) {
        res->u128 = src2.u128;
    } else if (imm < 16) {
        res->u128 = (src1.u128 << (128 - (imm * 8))) | (src2.u128 >> (imm * 8));
    } else if (imm == 16) {
        res->u128 = src1.u128;
    } else if (imm < 32) {
        res->u128 = src1.u128 >> ((imm - 16) * 8);
    } else if (imm > 31) {
        res->u128 = 0;
    }
}
void vpalignr_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    XMM src1, src2;

    //127:0 bit
    src1.u128 = vsrc.u128[0];
    src2.u128 = src.u128[0];

    if (imm == 0) {
        res->u128[0] = src2.u128;
    } else if (imm < 16) {
        res->u128[0] = (src1.u128 << (128 - (imm * 8))) | (src2.u128 >> (imm * 8));
    } else if (imm == 16) {
        res->u128[0] = src1.u128;
    } else if (imm < 32) {
        res->u128[0] = src1.u128 >> ((imm - 16) * 8);
    } else if (imm > 31) {
        res->u128[0] = 0;
    }

    //255:128 bit
    src1.u128 = vsrc.u128[1];
    src2.u128 = src.u128[1];

    if (imm == 0) {
        res->u128[1] = src2.u128;
    } else if (imm < 16) {
        res->u128[1] = (src1.u128 << (128 - (imm * 8))) | (src2.u128 >> (imm * 8));
    } else if (imm == 16) {
        res->u128[1] = src1.u128;
    } else if (imm < 32) {
        res->u128[1] = src1.u128 >> ((imm - 16) * 8);
    } else if (imm > 31) {
        res->u128[1] = 0;
    }
}

int vssse3_instruction(x86_saved_state_t *state,
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
        case 0x00:
            //VPSHUFB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpshufb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x01:
            //VPHADDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x02:
            //VPHADDD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x03:
            //VPHADDSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x04:
            //VPMADDUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaddubsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x05:
            //VPHSUBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x06:
            //VPHSUBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x07:
            //VPHSUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x08:
            //VPSIGNB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    xmmres = xmmdst;
                    vpsignb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x09:
            //VPSIGNW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    xmmres = xmmdst;
                    vpsignw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x0A:
            //VPSIGND
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    xmmres = xmmdst;
                    vpsignd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x0B:
            //VPMULHRSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmulhrsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x1C:
            //VPABSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsb_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x1D:
            //VPABSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsw_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x1E:
            //VPABSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x0F:
            //VPALIGNR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpalignr_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
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
        case 0x00:
            //VPSHUFB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpshufb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x01:
            //VPHADDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x02:
            //VPHADDD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x03:
            //VPHADDSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphaddsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x04:
            //VPMADDUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaddubsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x05:
            //VPHSUBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x06:
            //VPHSUBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x07:
            //VPHSUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vphsubsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x08:
            //VPSIGNB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    ymmres = ymmdst;
                    vpsignb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x09:
            //VPSIGNW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    ymmres = ymmdst;
                    vpsignw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x0A:
            //VPSIGND
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    ymmres = ymmdst;
                    vpsignd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x0B:
            //VPMULHRSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmulhrsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x1C:
            //VPABSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsb_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x1D:
            //VPABSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsw_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x1E:
            //VPABSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpabsd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x0F:
            //VPALIGNR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpalignr_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
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
