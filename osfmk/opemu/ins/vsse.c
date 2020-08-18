//
//  vsse.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/2.
//  Copyright (c) 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vsse.h"

/**********************************************/
/**  VSSE  instructions implementation       **/
/**********************************************/
/************* Move *************/
void vmovups_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->fa32[i] = src.fa32[i];
    }
}
void vmovups_256(YMM src, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        res->fa32[i] = src.fa32[i];
    }
}

void vmovss_128a(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    res->fa32[0] = src.fa32[0];
}
void vmovss_128b(XMM src, XMM *res) {
    res->u128 = 0;
    res->fa32[0] = src.fa32[0];
}

void vmovhlps(XMM src, XMM vsrc, XMM *res) {
    res->a64[0] = src.a64[1];
    res->a64[1] = vsrc.a64[1];
}
void vmovlps_128a(XMM src, XMM vsrc, XMM *res) {
    res->a64[0] = src.a64[0];
    res->a64[1] = vsrc.a64[1];
}
void vmovlps_128b(XMM src, XMM *res) {
    res->a64[0] = src.a64[0];
}
void vmovlhps(XMM src, XMM vsrc, XMM *res) {
    res->a64[0] = vsrc.a64[0];
    res->a64[1] = src.a64[0];
}
void vmovhps_128a(XMM src, XMM vsrc, XMM *res) {
    res->a64[0] = vsrc.a64[0];
    res->a64[1] = src.a64[0];
}
void vmovhps_128b(XMM src, XMM *res) {
    res->a64[0] = src.a64[0];
}
void vmovntps_128(XMM dst, XMM *res) {
    res->u128 = dst.u128;
}
void vmovntps_256(YMM dst, YMM *res) {
    res->u128[0] = dst.u128[0];
    res->u128[1] = dst.u128[1];
}
void vmovmskps_128(XMM src, XMM *res) {
    int i;
    int xbit;
    uint32_t mask;
    uint32_t dest = 0;

    for (i = 0; i < 4; ++i) {
        mask = src.u32[i];
        xbit = (mask >> 31) & 1;
        dest |= (xbit << i);
    }
    res->u32[0] = dest;
}
void vmovmskps_256(YMM src, YMM *res) {
    int i;
    int xbit;
    uint32_t mask;
    uint32_t dest = 0;

    for (i = 0; i < 8; ++i) {
        mask = src.u32[i];
        xbit = (mask >> 31) & 1;
        dest |= (xbit << i);
    }
    res->u32[0] = dest;
}
/************* ADD *************/
void vaddps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->fa32[i] = vsrc.fa32[i] + src.fa32[i];
    }
}
void vaddps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        res->fa32[i] = vsrc.fa32[i] + src.fa32[i];
    }
}
void vaddss(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    res->fa32[0] = vsrc.fa32[0] + src.fa32[0];
}

/************* SUB *************/
void vsubps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->fa32[i] = vsrc.fa32[i] - src.fa32[i];
    }
}
void vsubps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        res->fa32[i] = vsrc.fa32[i] - src.fa32[i];
    }
}
void vsubss(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    res->fa32[0] = vsrc.fa32[0] - src.fa32[0];
}
/************* Multiply *************/
void vmulps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->fa32[i] = vsrc.fa32[i] * src.fa32[i];
    }
}
void vmulps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        res->fa32[i] = vsrc.fa32[i] * src.fa32[i];
    }
}
void vmulss(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    res->fa32[0] = vsrc.fa32[0] * src.fa32[0];
}
/************* Divide *************/
void vdivps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->fa32[i] = vsrc.fa32[i] / src.fa32[i];
    }
}
void vdivps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        res->fa32[i] = vsrc.fa32[i] / src.fa32[i];
    }
}
void vdivss(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    res->fa32[0] = vsrc.fa32[0] / src.fa32[0];
}
/************* AND *************/
void vandps_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 4; ++i) {
        tmp.u32[i] = vsrc.u32[i] & src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}
void vandps_256(YMM src, YMM vsrc, YMM *res) {
    YMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.u32[i] = vsrc.u32[i] & src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}

void vandnps_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 4; ++i) {
        tmp.u32[i] = (~(vsrc.u32[i])) & src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}
void vandnps_256(YMM src, YMM vsrc, YMM *res) {
    YMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.u32[i] = (~(vsrc.u32[i])) & src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}

/************* OR/XOR *************/
void vorps_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 4; ++i) {
        tmp.u32[i] = vsrc.u32[i] | src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}
void vorps_256(YMM src, YMM vsrc, YMM *res) {
    YMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.u32[i] = vsrc.u32[i] | src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}
void vxorps_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 4; ++i) {
        tmp.u32[i] = vsrc.u32[i] ^ src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}
void vxorps_256(YMM src, YMM vsrc, YMM *res) {
    YMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.u32[i] = vsrc.u32[i] ^ src.u32[i];
        res->fa32[i] = tmp.fa32[i];
    }
}

/************* Converts *************/
void vcvtsi2ss(XMM src, XMM vsrc, XMM *res, uint8_t operand_size) {
    float f = 0;
    res->u128 = vsrc.u128;

    if (operand_size == 64) {
        int64_t ix = src.a64[0];
        f = ix;
        res->fa32[0] = f;
    } else {
        int32_t ix = src.a32[0];
        f = ix;
        res->fa32[0] = f;
    }
}
void vcvtss2si(XMM src, XMM *res, int rc, uint8_t operand_size) {
    double df = 0;

    if (operand_size == 64) {
        int64_t ix = 0;
        df = round_fp32(src.fa32[0], rc);
        ix= df;
        res->a64[0] = ix;
    } else {
        int32_t ix = 0;
        df = round_fp32(src.fa32[0], rc);
        ix = df;
        res->a32[0] = ix;
        res->a32[1] = 0;
    }
}
/************* MAX/MIN Return *************/
void vminps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int MIN = 0;
    float SRC1, SRC2;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        MIN = minsf(SRC1, SRC2);
        if (MIN)
            res->fa32[i] = vsrc.fa32[i];
        else
            res->fa32[i] = src.fa32[i];
    }
}
void vminps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int MIN = 0;
    float SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        MIN = minsf(SRC1, SRC2);
        if (MIN)
            res->fa32[i] = vsrc.fa32[i];
        else
            res->fa32[i] = src.fa32[i];
    }

}

void vmaxps_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int MAX = 0;
    float SRC1, SRC2;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        MAX = maxsf(SRC1, SRC2);
        if (MAX)
            res->fa32[i] = vsrc.fa32[i];
        else
            res->fa32[i] = src.fa32[i];
    }
}
void vmaxps_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int MAX = 0;
    float SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        MAX = maxsf(SRC1, SRC2);
        if (MAX)
            res->fa32[i] = vsrc.fa32[i];
        else
            res->fa32[i] = src.fa32[i];
    }
}

void vminss(XMM src, XMM vsrc, XMM *res) {
    int MIN = 0;
    res->a128 = vsrc.a128;
    float SRC1 = vsrc.fa32[0];
    float SRC2 = src.fa32[0];
    MIN = minsf(SRC1, SRC2);
    if (MIN)
        res->fa32[0] = vsrc.fa32[0];
    else
        res->fa32[0] = src.fa32[0];
}
void vmaxss(XMM src, XMM vsrc, XMM *res) {
    int MAX = 0;
    res->a128 = vsrc.a128;
    float SRC1 = vsrc.fa32[0];
    float SRC2 = src.fa32[0];
    MAX = maxsf(SRC1, SRC2);
    if (MAX)
        res->fa32[0] = vsrc.fa32[0];
    else
        res->fa32[0] = src.fa32[0];
}

/************* Compare *************/
void vucomiss(XMM src, XMM dst, x86_saved_state_t *state) {
    uint64_t FLAGS = 0;
    uint64_t RFLAGS = 0;
    uint32_t EFLAGS = 0;

    if (is_saved_state64(state)) {
        RFLAGS = saved_state64(state)->isf.rflags;
        FLAGS = RFLAGS;
    } else {
        EFLAGS = saved_state32(state)->efl;
        FLAGS = EFLAGS;
    }

    float SRC1 = dst.fa32[0];
    float SRC2 = src.fa32[0];

    //UNORDERED
    if ((isNaN_f32(SRC1)) || (isNaN_f32(SRC1))) {
        FLAGS |= 0x00000040; //set ZF = 1
        FLAGS |= 0x00000004; //set PF = 1
        FLAGS |= 0x00000001; //set CF = 1
    }
    //GREATER_THAN
    if (SRC1 > SRC2) {
        FLAGS = (FLAGS | 0x00000040) ^ 0x00000040;  //set ZF = 0
        FLAGS = (FLAGS | 0x00000004) ^ 0x00000004;  //set PF = 0
        FLAGS = (FLAGS | 0x00000001) ^ 0x00000001;  //set CF = 0
    }
    //LESS_THAN
    if (SRC1 < SRC2) {
        FLAGS = (FLAGS | 0x00000040) ^ 0x00000040;  //set ZF = 0
        FLAGS = (FLAGS | 0x00000004) ^ 0x00000004;  //set PF = 0
        FLAGS |= 0x00000001; //set CF = 1
    }
    //EQUAL
    if (SRC1 == SRC2) {
        FLAGS |= 0x00000040; //set ZF = 1
        FLAGS = (FLAGS | 0x00000004) ^ 0x00000004;  //set PF = 0
        FLAGS = (FLAGS | 0x00000001) ^ 0x00000001;  //set CF = 0
    }

    FLAGS = (FLAGS | 0x00000800) ^ 0x00000800;  //set OF = 0
    FLAGS = (FLAGS | 0x00000010) ^ 0x00000010;  //set AF = 0
    FLAGS = (FLAGS | 0x00000080) ^ 0x00000080;  //set SF = 0

    if (is_saved_state64(state)) {
        saved_state64(state)->isf.rflags = FLAGS;
    } else {
        EFLAGS = FLAGS & 0xFFFFFFFF;
        saved_state32(state)->efl = EFLAGS;
    }
}
void vcmpps_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int CMP = 0;
    float SRC1, SRC2;
    uint8_t immvar = imm & 31;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        CMP = cmpoptsf(SRC1, SRC2, immvar);
        if (CMP)
            res->u32[i] = 0xFFFFFFFF;
        else
            res->u32[i] = 0;
    }
}
void vcmpps_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int CMP = 0;
    float SRC1, SRC2;
    uint8_t immvar = imm & 31;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.fa32[i];
        SRC2 = src.fa32[i];
        CMP = cmpoptsf(SRC1, SRC2, immvar);
        if (CMP)
            res->u32[i] = 0xFFFFFFFF;
        else
            res->u32[i] = 0;
    }
}
void vcmpss(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int CMP = 0;
    uint8_t immvar = imm & 31;
    res->u128 = vsrc.u128;
    float SRC1 = vsrc.fa32[0];
    float SRC2 = src.fa32[0];
    CMP = cmpoptsf(SRC1, SRC2, immvar);
    if (CMP)
        res->u32[0] = 0xFFFFFFFF;
    else
        res->u32[0] = 0;
}

/************* Interleave *************/
void vunpcklps_128(XMM src, XMM vsrc, XMM *res) {
    res->fa32[0] = vsrc.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = vsrc.fa32[1];
    res->fa32[3] = src.fa32[1];
}
void vunpcklps_256(YMM src, YMM vsrc, YMM *res) {
    res->fa32[0] = vsrc.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = vsrc.fa32[1];
    res->fa32[3] = src.fa32[1];
    res->fa32[4] = vsrc.fa32[4];
    res->fa32[5] = src.fa32[4];
    res->fa32[6] = vsrc.fa32[5];
    res->fa32[7] = src.fa32[5];
}
void vunpckhps_128(XMM src, XMM vsrc, XMM *res) {
    res->fa32[0] = vsrc.fa32[2];
    res->fa32[1] = src.fa32[2];
    res->fa32[2] = vsrc.fa32[3];
    res->fa32[3] = src.fa32[3];
}
void vunpckhps_256(YMM src, YMM vsrc, YMM *res) {
    res->fa32[0] = vsrc.fa32[2];
    res->fa32[1] = src.fa32[2];
    res->fa32[2] = vsrc.fa32[3];
    res->fa32[3] = src.fa32[3];
    res->fa32[4] = vsrc.fa32[6];
    res->fa32[5] = src.fa32[6];
    res->fa32[6] = vsrc.fa32[7];
    res->fa32[7] = src.fa32[7];
}
/************* Select *************/
void vshufps_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int imm0 = imm & 3;
    int imm1 = (imm >> 2) & 3;
    int imm2 = (imm >> 4) & 3;
    int imm3 = (imm >> 6) & 3;

    res->fa32[0] = vsrc.fa32[imm0];
    res->fa32[1] = vsrc.fa32[imm1];
    res->fa32[2] = src.fa32[imm2];
    res->fa32[3] = src.fa32[imm3];
}

void vshufps_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int imm0 = imm & 3;
    int imm1 = (imm >> 2) & 3;
    int imm2 = (imm >> 4) & 3;
    int imm3 = (imm >> 6) & 3;

    res->fa32[0] = vsrc.fa32[imm0];
    res->fa32[1] = vsrc.fa32[imm1];
    res->fa32[2] = src.fa32[imm2];
    res->fa32[3] = src.fa32[imm3];
    res->fa32[4] = vsrc.fa32[imm0];
    res->fa32[5] = vsrc.fa32[imm1];
    res->fa32[6] = src.fa32[imm2];
    res->fa32[7] = src.fa32[imm3];
}

/************* Computes *************/
void vrcpps_128(XMM src, XMM *res) {
    int i;
    float fp32;
    for (i = 0; i < 4; ++i) {
        fp32 = rcp_sf(src.fa32[i]);
        res->fa32[i] = fp32;
    }
}
void vrcpps_256(YMM src, YMM *res) {
    int i;
    float fp32;
    for (i = 0; i < 8; ++i) {
        fp32 = rcp_sf(src.fa32[i]);
        res->fa32[i] = fp32;
    }
}
void vrcpss(XMM src, XMM vsrc,XMM *res) {
    res->u128 = vsrc.u128;
    float fp32 = rcp_sf(src.fa32[0]);
    res->fa32[0] = fp32;
}

void vrsqrtps_128(XMM src, XMM *res) {
    int i;
    float fp32;
    for (i = 0; i < 4; ++i) {
        fp32 = rsqrt_sf(src.fa32[i]);
        res->fa32[i] = fp32;
    }
}
void vrsqrtps_256(YMM src, YMM *res) {
    int i;
    float fp32;
    for (i = 0; i < 8; ++i) {
        fp32 = rsqrt_sf(src.fa32[i]);
        res->fa32[i] = fp32;
    }
}
void vrsqrtss(XMM src, XMM vsrc,XMM *res) {
    res->u128 = vsrc.u128;
    float fp32 = rsqrt_sf(src.fa32[0]);
    res->fa32[0] = fp32;
}

void vsqrtps_128(XMM src, XMM *res) {
    int i;
    float f;

    for (i = 0; i < 4; ++i) {
        f = sqrt_sf(src.fa32[i]);
        res->fa32[i] = f;
    }
}

void vsqrtps_256(YMM src, YMM *res) {
    int i;
    float f;

    for (i = 0; i < 8; ++i) {
        f = sqrt_sf(src.fa32[i]);
        res->fa32[i] = f;
    }
}

void vsqrtss(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128;
    float f = sqrt_sf(src.fa32[0]);
    res->fa32[0] = f;
}

/************* MXCSR register *************/
void vldmxcsr(XMM src) {
    uint32_t mxcsr = src.u32[0];
    __asm__ __volatile__ ("ldmxcsr %0" :: "m" (mxcsr));
}

void vstmxcsr(XMM *res) {
    uint32_t mxcsr = 0;
    __asm__ __volatile__ ("stmxcsr %0" : "=m" (mxcsr));
    res->u32[0] = mxcsr;
}

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
                     int kernel_trap)
{
    uint8_t imm;
    uint8_t mod = *modrm >> 6; // ModRM.mod
    uint8_t modreg = (*modrm >> 3) & 0x7;
    uint8_t num_dst = (*modrm >> 3) & 0x7;
    uint8_t num_src = *modrm & 0x7;

    //get mxcsr round control
    int mxcsr_rc = getmxcsr();

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
        /************* Move *************/
        case 0x10:
            //VMOVUPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            // VMOVSS SRC -> DST
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    if (mod == 3)
                        vmovss_128a(xmmsrc, xmmvsrc, &xmmres);
                    else
                        vmovss_128b(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x11:
            //VMOVUPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_128(xmmdst, &xmmres);
                    if (mod == 3) {
                        _load_xmm(num_src, &xmmres);
                    } else {
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            // VMOVSS DST -> SRC
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    if (mod == 3) {
                        vmovss_128a(xmmdst, xmmvsrc, &xmmres);
                        _load_xmm(num_src, &xmmres);
                    } else {
                        vmovss_128b(xmmdst, &xmmres);
                        rm_size = 32;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;
        case 0x12:
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    //VMOVLPS SRC -> DST
                    if (mod == 0)
                        vmovlps_128a(xmmsrc, xmmvsrc, &xmmres);
                    //VMOVHLPS
                    if (mod == 3)
                        vmovhlps(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
        case 0x13: //VMOVLPS DST -> SRC
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovlps_128b(xmmdst, &xmmres);
                    rm_size = 64;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
        case 0x16:
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    //VMOVHPS SRC -> DST
                    if (mod == 0)
                        vmovhps_128a(xmmsrc, xmmvsrc, &xmmres);
                    //VMOVLHPS
                    if (mod == 3)
                        vmovlhps(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
        case 0x17: //VMOVHPS DST -> SRC
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovhps_128b(xmmdst, &xmmres);
                    rm_size = 64;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }

        case 0x28: //VMOVAPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x29: //VMOVAPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_128(xmmsrc, &xmmres);
                    if (mod == 3) {
                        _load_xmm(num_src, &xmmres);
                    } else {
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;
        case 0x2B: //VMOVNTPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovntps_128(xmmdst, &xmmres);
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
            break;
        case 0x50: //VMOVMSKPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovmskps_128(xmmsrc, &xmmres);
                    if (is_saved_state64(state)) {
                        M64 r64res;
                        r64res.u64 = xmmres.u64[0];
                        _load_m64(num_dst, &r64res, state);
                    } else {
                        M32 r32res;
                        r32res.u32 = xmmres.u32[0];
                        _load_m32(num_dst, &r32res, state);
                    }
                }
            }
            break;
        /************* ADD *************/
        case 0x58:
            //VADDPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vaddps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VADDSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vaddss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* SUB *************/
        case 0x5C:
            //VSUBPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vsubps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VSUBSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vsubss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Multiply *************/
        case 0x59:
            //VMULPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmulps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMULSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmulss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Divide *************/
        case 0x5E:
            //VDIVPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vdivps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VDIVSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vdivss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* AND *************/
        case 0x54: //VANDPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vandps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x55: //VANDNPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vandnps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* OR/XOR *************/
        case 0x56: //VORPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vorps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x57: //VXORPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vxorps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Converts *************/
        case 0x2A:
            //VCVTSI2SS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    if (mod == 3) {
                        M64 r64src;
                        _store_m64(num_src, &r64src, state);
                        xmmsrc.u64[0] = r64src.u64;
                    }
                    vcvtsi2ss(xmmsrc, xmmvsrc, &xmmres, operand_size);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x2C:
            //VCVTTSS2SI
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtss2si(xmmsrc, &xmmres, 3, operand_size);
                    M64 m64res;
                    m64res.u64 = xmmres.u64[0];
                    _load_m64(num_dst, &m64res, state);
                }
            }
            break;
        case 0x2D:
            //VCVTSS2SI
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtss2si(xmmsrc, &xmmres, mxcsr_rc, operand_size);
                    M64 m64res;
                    m64res.u64 = xmmres.u64[0];
                    _load_m64(num_dst, &m64res, state);
                }
            }
            break;
        /************* MAX/MIN Return *************/
        case 0x5D:
            //VMINPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vminps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMINSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vminss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5F:
            //VMAXPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmaxps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMAXSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vmaxss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Compare *************/
        case 0x2E: //VUCOMISS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vucomiss(xmmsrc, xmmdst, state);
                }
            }
            break;
        case 0x2F: //VCOMISS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vucomiss(xmmsrc, xmmdst, state);
                }
            }
            break;
        case 0xC2:
            //VCMPPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vcmpps_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            //VCMPSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcmpss(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        /************* Interleave *************/
        case 0x14: //VUNPCKLPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vunpcklps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x15: //VUNPCKHPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vunpckhps_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Select *************/
        case 0xC6: //VSHUFPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vshufps_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;

        /************* Computes *************/
        case 0x53:
            //VRCPPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vrcpps_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VRCPSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vrcpss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x52:
            //VRSQRTPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vrsqrtps_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VRSQRTSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vrsqrtss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x51:
            //VSQRTPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vsqrtps_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VSQRTSS
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vsqrtss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* MXCSR register *************/
        case 0xAE:
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    //VLDMXCSR
                    if (modreg == 2) {
                        vldmxcsr(xmmsrc);
                    }
                    //VSTMXCSR
                    if (modreg == 3) {
                        vstmxcsr(&xmmres);
                        rm_size = 32;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
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
        /************* Move *************/
        case 0x10:
            //VMOVUPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x11:
            //VMOVUPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_256(ymmsrc, &ymmres);
                    if (mod == 3) {
                        _load_ymm(num_src, &ymmres);
                    } else {
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x28: //VMOVAPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x29: //VMOVAPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovups_256(ymmsrc, &ymmres);
                    if (mod == 3) {
                        _load_ymm(num_src, &ymmres);
                    } else {
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;
        case 0x2B: //VMOVNTPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovntps_256(ymmdst, &ymmres);
                    _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                }
            }
            break;
        case 0x50: //VMOVMSKPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmovmskps_256(ymmsrc, &ymmres);
                    if (is_saved_state64(state)) {
                        M64 r64res;
                        r64res.u64 = ymmres.u64[0];
                        _load_m64(num_dst, &r64res, state);
                    } else {
                        M32 r32res;
                        r32res.u32 = ymmres.u32[0];
                        _load_m32(num_dst, &r32res, state);
                    }
                }
            }
            break;
        /************* ADD *************/
        case 0x58: //VADDPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vaddps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* SUB *************/
        case 0x5C: //VSUBPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vsubps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Multiply *************/
        case 0x59: //VMULPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmulps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Divide *************/
        case 0x5E: //VDIVPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vdivps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* AND *************/
        case 0x54: //VANDPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vandps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x55: //VANDNPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vandnps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* OR/XOR *************/
        case 0x56: //VORPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vorps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x57: //VXORPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vxorps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* MAX/MIN Return *************/
        case 0x5D:
            //VMINPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vminps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x5F:
            //VMAXPS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vmaxps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Compare *************/
        case 0xC2: //VCMPPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vcmpps_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        /************* Interleave *************/
        case 0x14: //VUNPCKLPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vunpcklps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x15: //VUNPCKHPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vunpckhps_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Select *************/
        case 0xC6: //VSHUFPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vshufps_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        /************* Computes *************/
        case 0x53: //VRCPPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vrcpps_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x52: //VRSQRTPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vrsqrtps_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x51: //VSQRTPS
            if (simd_prefix == 0) { //none
                if (leading_opcode == 1) {//0F
                    vsqrtps_256(ymmsrc, &ymmres);
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

/*********************************************************/
int maxsf(float SRC1, float SRC2) {
    //return 1 is SRC1
    //return 0 is SRC2
    if ((SRC1 == 0.0) && (SRC2 == 0.0)) return 0;
    if (isNaN_f32(SRC1)) return 0;
    if (isNaN_f32(SRC2)) return 0;
    if (SRC1 > SRC2) return 1;

    return 0;
}

int minsf(float SRC1, float SRC2) {
    //return 1 is SRC1
    //return 0 is SRC2
    if ((SRC1 == 0.0) && (SRC2 == 0.0)) return 0;
    if (isNaN_f32(SRC1)) return 0;
    if (isNaN_f32(SRC2)) return 0;
    if (SRC1 < SRC2) return 1;

    return 0;
}

//comparison predicate operand
int cmpoptsf(float SRC1, float SRC2, uint8_t immvar) {
    int opt = 0;

    switch(immvar) {
    case 0:
        if (SRC1 == SRC2) opt = 1;
        break;
    case 1:
        if (SRC1 < SRC2) opt = 1;
        break;
    case 2:
        if (SRC1 <= SRC2) opt = 1;
        break;
    case 3:
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 4:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 5:
        if (SRC1 >= SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 6:
        if (SRC1 > SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 7:
        opt = 1;
        if (isNaN_f32(SRC1)) opt = 0;
        if (isNaN_f32(SRC2)) opt = 0;
        break;
    case 8:
        if (SRC1 == SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 9:
        if (SRC1 < SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 10:
        if (SRC1 <= SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 11:
        opt = 0;
        break;
    case 12:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 0;
        if (isNaN_f32(SRC2)) opt = 0;
        break;
    case 13:
        if (SRC1 >= SRC2) opt = 1;
        break;
    case 14:
        if (SRC1 > SRC2) opt = 1;
        break;
    case 15:
        opt = 1;
        break;
    case 16:
        if (SRC1 == SRC2) opt = 1;
        break;
    case 17:
        if (SRC1 < SRC2) opt = 1;
        break;
    case 18:
        if (SRC1 <= SRC2) opt = 1;
        break;
    case 19:
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 20:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 21:
        if (SRC1 >= SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 22:
        if (SRC1 > SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 23:
        opt = 1;
        if (isNaN_f32(SRC1)) opt = 0;
        if (isNaN_f32(SRC2)) opt = 0;
        break;
    case 24:
        if (SRC1 == SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 25:
        if (SRC1 < SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 26:
        if (SRC1 <= SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 1;
        if (isNaN_f32(SRC2)) opt = 1;
        break;
    case 27:
        opt = 0;
        break;
    case 28:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f32(SRC1)) opt = 0;
        if (isNaN_f32(SRC2)) opt = 0;
        break;
    case 29:
        if (SRC1 >= SRC2) opt = 1;
        break;
    case 30:
        if (SRC1 > SRC2) opt = 1;
        break;
    case 31:
        opt = 1;
        break;
    default:
        return 0;
    }

    return opt;
}

/****** get approximate ******/
float rcp_sf(float fp32) {
    XMM BAK;
    XMM SRC;
    XMM RES;

    //backup xmm
    asm __volatile__ ("movdqu %%xmm0, %0" : "=m" (BAK));

    //get approximate rcp_sf
    SRC.fa32[0] = fp32;
    asm __volatile__ ("rcpss %0, %%xmm0" :: "m" (SRC));
    asm __volatile__ ("movdqu %%xmm0, %0" : "=m" (RES));
    float f = RES.fa32[0];

    //restore xmm
    asm __volatile__ ("movdqu %0, %%xmm0" :: "m" (BAK));

    return f;
}

/****** get approximate(sqrt) ******/
float rsqrt_sf(float fp32) {
    XMM BAK;
    XMM SRC;
    XMM RES;

    //backup xmm
    asm __volatile__ ("movdqu %%xmm0, %0" : "=m" (BAK));

    //get approximate(sqrt) rsqrt_sf
    SRC.fa32[0] = fp32;
    asm __volatile__ ("rsqrtss %0, %%xmm0" :: "m" (SRC));
    asm __volatile__ ("movdqu %%xmm0, %0" : "=m" (RES));
    float f = RES.fa32[0];

    //restore xmm
    asm __volatile__ ("movdqu %0, %%xmm0" :: "m" (BAK));

    return f;
}
