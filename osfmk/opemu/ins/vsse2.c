//
//  vsse2.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/8.
//  Copyright © 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vsse2.h"

/**********************************************/
/**  VSSE2  instructions implementation      **/
/**********************************************/
/************* Move *************/
void vmovdqu_128a(XMM src, XMM *res) {
    res->u128 = src.u128;
}
void vmovdqu_128b(XMM dst, XMM *res) {
    res->u128 = dst.u128;
}

void vmovdqu_256a(YMM src, YMM *res) {
    res->u256 = src.u256;
}
void vmovdqu_256b(YMM dst, YMM *res) {
    res->u256 = dst.u256;
}

void vmovda(XMM src, XMM *res, uint8_t operand_size) {
    if (operand_size == 64) {
        //VMOVQ
        res->u64[0] = src.u64[0];
        res->u64[1] = 0;
    } else {
        //VMOVD
        res->u32[0] = src.u32[0];
        res->u32[1] = 0;
        res->u32[2] = 0;
        res->u32[3] = 0;
    }
}

void vmovdb(XMM dst, XMM *res, uint8_t operand_size) {
    if (operand_size == 64) {
        //VMOVQ
        res->u64[0] = dst.u64[0];
        res->u64[1] = 0;
    } else {
        //VMOVD
        res->u32[0] = dst.u32[0];
        res->u32[1] = 0;
        res->u32[2] = 0;
        res->u32[3] = 0;
    }
}

void vmovupd_128a(XMM src, XMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = src.fa64[1];
}
void vmovupd_128b(XMM dst, XMM *res) {
    res->fa64[0] = dst.fa64[0];
    res->fa64[1] = dst.fa64[1];
}

void vmovupd_256a(YMM src, YMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = src.fa64[1];
    res->fa64[2] = src.fa64[2];
    res->fa64[3] = src.fa64[3];
}
void vmovupd_256b(YMM dst, YMM *res) {
    res->fa64[0] = dst.fa64[0];
    res->fa64[1] = dst.fa64[1];
    res->fa64[2] = dst.fa64[2];
    res->fa64[3] = dst.fa64[3];
}

void vmovsd_128a(XMM src, XMM vsrc, XMM *res) {

    res->fa64[0] = src.fa64[0];
    res->fa64[1] = vsrc.fa64[1];
}
void vmovsd_128b(XMM src, XMM *res) {

    res->fa64[0] = src.fa64[0];
    res->fa64[1] = 0;
}

void vmovlpd_128a(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = vsrc.fa64[1];
}
void vmovlpd_128b(XMM dst, XMM *res) {
    res->fa64[0] = dst.fa64[0];
}

void vmovhpd_128a(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0];
    res->fa64[1] = src.fa64[0];
}
void vmovhpd_128b(XMM dst, XMM *res) {
    res->fa64[0] = dst.fa64[1];
}

//MASK = src
//SRC = dst
//DEST = [RDI]
void vmaskmovdqu(XMM src, XMM dst, XMM *res, XMM var) {
    int i;
    int xbit;
    uint8_t MASK;

    res->u128 = var.u128;

    for (i = 0; i < 16; ++i) {
        MASK = src.u8[i];
        xbit = (MASK >> 7) & 1;
        if (xbit == 1) {
            res->u8[i] = dst.u8[i];
        }
    }
}

void vmovntdq_128(XMM dst, XMM *res) {
    res->u128 = dst.u128;
}
void vmovntdq_256(YMM dst, YMM *res) {
    res->u128[0] = dst.u128[0];
    res->u128[1] = dst.u128[1];
}

void vmovmskpd_128(XMM src, XMM *res) {
    int i;
    int xbit;
    uint64_t mask;
    uint64_t dest = 0;

    for (i = 0; i < 2; ++i) {
        mask = src.u64[i];
        xbit = (mask >> 63) & 1;
        dest |= (xbit << i);
    }
    res->u64[0] = dest;
}
void vmovmskpd_256(YMM src, YMM *res) {
    int i;
    int xbit;
    uint64_t mask;
    uint64_t dest = 0;

    for (i = 0; i < 4; ++i) {
        mask = src.u64[i];
        xbit = (mask >> 63) & 1;
        dest |= (xbit << i);
    }
    res->u64[0] = dest;
}

void vpmovmskb_128(XMM src, XMM *res) {
    int i;
    int xbit;
    uint8_t mask;
    uint64_t dest = 0;

    for (i = 0; i < 16; ++i) {
        mask = src.u8[i];
        xbit = (mask >> 7) & 1;
        dest |= (xbit << i);
    }
    res->u64[0] = dest;
}
void vpmovmskb_256(YMM src, YMM *res) {
    int i;
    int xbit;
    uint8_t mask;
    uint64_t dest = 0;

    for (i = 0; i < 32; ++i) {
        mask = src.u8[i];
        xbit = (mask >> 7) & 1;
        dest |= (xbit << i);
    }
    res->u64[0] = dest;

}

/************* Converts integers byte/word *************/
void vpacksswb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 8; ++i) {
        var = STSB(vsrc.a16[i]);
        TEMP1.a8[i] = var;
    }

    for (i = 0; i < 8; ++i) {
        var = STSB(src.a16[i]);
        TEMP2.a8[i] = var;
    }
    res->a64[0] = TEMP1.a64[0];
    res->a64[1] = TEMP2.a64[0];
}
void vpacksswb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 16; ++i) {
        var = STSB(vsrc.a16[i]);
        TEMP1.a8[i] = var;
    }

    for (i = 0; i < 16; ++i) {
        var = STSB(src.a16[i]);
        TEMP2.a8[i] = var;
    }

    res->a64[0] = TEMP1.a64[0];
    res->a64[1] = TEMP2.a64[0];
    res->a64[2] = TEMP1.a64[1];
    res->a64[3] = TEMP2.a64[1];
}
void vpackuswb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 8; ++i) {
        var = STUB(vsrc.a16[i]);
        TEMP1.u8[i] = var;
    }

    for (i = 0; i < 8; ++i) {
        var = STUB(src.a16[i]);
        TEMP2.u8[i] = var;
    }
    res->u64[0] = TEMP1.u64[0];
    res->u64[1] = TEMP2.u64[0];
}
void vpackuswb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 16; ++i) {
        var = STUB(vsrc.a16[i]);
        TEMP1.u8[i] = var;
    }

    for (i = 0; i < 16; ++i) {
        var = STUB(src.a16[i]);
        TEMP2.u8[i] = var;
    }

    res->u64[0] = TEMP1.u64[0];
    res->u64[1] = TEMP2.u64[0];
    res->u64[2] = TEMP1.u64[1];
    res->u64[3] = TEMP2.u64[1];
}
void vpackssdw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 4; ++i) {
        var = STSW(vsrc.a32[i]);
        TEMP1.a16[i] = var;
    }
    for (i = 0; i < 4; ++i) {
        var = STSW(src.a32[i]);
        TEMP2.a16[i] = var;
    }

    res->a64[0] = TEMP1.a64[0];
    res->a64[1] = TEMP2.a64[0];
}
void vpackssdw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t var = 0;
    XMM TEMP1, TEMP2;

    for (i = 0; i < 8; ++i) {
        var = STSW(vsrc.a32[i]);
        TEMP1.a16[i] = var;
    }
    for (i = 0; i < 8; ++i) {
        var = STSW(src.a32[i]);
        TEMP2.a16[i] = var;
    }

    res->a64[0] = TEMP1.a64[0];
    res->a64[1] = TEMP2.a64[0];
    res->a64[2] = TEMP1.a64[1];
    res->a64[3] = TEMP2.a64[1];
}

/************* Converts floating-point *************/
void vcvtdq2pd_128(XMM src, XMM *res) {
    int i;
    int32_t ix = 0;
    double df = 0;

    for (i = 0; i < 2; ++i) {
        ix = src.a32[i];
        df = ix;
        res->fa64[i] = df;
    }
}
void vcvtdq2pd_256(XMM src, YMM *res) {
    int i;
    int32_t ix = 0;
    double df = 0;

    for (i = 0; i < 4; ++i) {
        ix = src.a32[i];
        df = ix;
        res->fa64[i] = df;
    }
}

void vcvtdq2ps_128(XMM src, XMM *res) {
    int i;
    int32_t ix = 0;
    float f = 0;

    for (i = 0; i < 4; ++i) {
        ix = src.a32[i];
        f = ix;
        res->fa32[i] = f;
    }
}
void vcvtdq2ps_256(YMM src, YMM *res) {
    int i;
    int32_t ix = 0;
    float f = 0;

    for (i = 0; i < 8; ++i) {
        ix = src.a32[i];
        f = ix;
        res->fa32[i] = f;
    }
}

void vcvtpd2dq_128(XMM src, XMM *res, int rc) {
    int i;
    int32_t ix = 0;
    double df = 0;

    for (i = 0; i < 2; ++i) {
        df = round_fp64(src.fa64[i], rc);
        ix = df;
        res->a32[i] = ix;
    }
}
void vcvtpd2dq_256(YMM src, XMM *res, int rc) {
    int i;
    int32_t ix = 0;
    double df = 0;

    for (i = 0; i < 4; ++i) {
        df = round_fp64(src.fa64[i], rc);
        ix = df;
        res->a32[i] = ix;
    }
}

void vcvtpd2ps_128(XMM src, XMM *res) {
    int i;
    float f = 0;

    for (i = 0; i < 2; ++i) {
        f = src.fa64[i];
        res->fa32[i] = f;
    }
}
void vcvtpd2ps_256(YMM src, YMM *res) {
    int i;
    float f = 0;

    for (i = 0; i < 4; ++i) {
        f = src.fa64[i];
        res->fa32[i] = f;
    }
}

void vcvtps2dq_128(XMM src, XMM *res, int rc) {
    int i;
    int32_t ix = 0;
    float f = 0;

    for (i = 0; i < 4; ++i) {
        f = round_fp32(src.fa32[i], rc);
        ix = f;
        res->a32[i] = ix;
    }
}
void vcvtps2dq_256(YMM src, YMM *res, int rc) {
    int i;
    int32_t ix = 0;
    float f = 0;

    for (i = 0; i < 8; ++i) {
        f = round_fp32(src.fa32[i], rc);
        ix = f;
        res->a32[i] = ix;
    }
}

void vcvtps2pd_128(XMM src, XMM *res) {
    int i;
    float f = 0;

    for (i = 0; i < 2; ++i) {
        f = src.fa32[i];
        res->fa64[i] = f;
    }
}
void vcvtps2pd_256(XMM src, YMM *res) {
    int i;
    float f = 0;

    for (i = 0; i < 4; ++i) {
        f = src.fa32[i];
        res->fa64[i] = f;
    }
}

void vcvtsd2si(XMM src, XMM *res, int rc, uint8_t operand_size) {
    double df = 0;

    if (operand_size == 64) {
        int64_t ix = 0;
        df = round_fp64(src.fa64[0], rc);
        ix= df;
        res->a64[0] = ix;
    } else {
        int32_t ix = 0;
        df = round_fp64(src.fa64[0], rc);
        ix = df;
        res->a32[0] = ix;
        res->a32[1] = 0;
    }
}
void vcvtsd2ss(XMM src, XMM vsrc, XMM *res) {
    double df = 0;
    float f = 0;
    res->u128 = vsrc.u128;

    df = src.fa64[0];
    f = df;
    res->fa32[0] = f;
}

void vcvtsi2sd(XMM src, XMM vsrc, XMM *res, uint8_t operand_size) {
    double df = 0;
    res->u128 = vsrc.u128;

    if (operand_size == 64) {
        int64_t ix = src.a64[0];
        df = ix;
        res->fa64[0] = df;
    } else {
        int32_t ix = src.a32[0];
        df = ix;
        res->fa64[0] = df;
    }
}
void vcvtss2sd(XMM src, XMM vsrc, XMM *res) {
    double df = 0;
    float f = 0;
    res->u128 = vsrc.u128;

    f = src.fa32[0];
    df = f;
    res->fa64[0] = df;
}

/************* Computes *************/
void vpsadbw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int8_t y = 0;
    uint8_t x = 0;
    uint16_t sum = 0;
    XMM tmp;

    for (i = 0; i < 16; ++i) {
        y = vsrc.a8[i] - src.a8[i];
        x = ABS(y);
        tmp.u8[i] = x;
    }
    sum = tmp.u8[0] + tmp.u8[1] + tmp.u8[2] + tmp.u8[3] + tmp.u8[4] + tmp.u8[5] + tmp.u8[6] + tmp.u8[7];
    res->u16[0] = sum;
    res->u16[1] = 0;
    res->u16[2] = 0;
    res->u16[3] = 0;
    sum = tmp.u8[8] + tmp.u8[9] + tmp.u8[10] + tmp.u8[11] + tmp.u8[12] + tmp.u8[13] + tmp.u8[14] + tmp.u8[15];
    res->u16[4] = sum;
    res->u16[5] = 0;
    res->u16[6] = 0;
    res->u16[7] = 0;
}

void vpsadbw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int8_t y = 0;
    uint8_t x = 0;
    uint16_t sum = 0;
    YMM tmp;

    for (i = 0; i < 32; ++i) {
        y = vsrc.a8[i] - src.a8[i];
        x = ABS(y);
        tmp.u8[i] = x;
    }
    sum = tmp.u8[0] + tmp.u8[1] + tmp.u8[2] + tmp.u8[3] + tmp.u8[4] + tmp.u8[5] + tmp.u8[6] + tmp.u8[7];
    res->u16[0] = sum;
    res->u16[1] = 0;
    res->u16[2] = 0;
    res->u16[3] = 0;
    sum = tmp.u8[8] + tmp.u8[9] + tmp.u8[10] + tmp.u8[11] + tmp.u8[12] + tmp.u8[13] + tmp.u8[14] + tmp.u8[15];
    res->u16[4] = sum;
    res->u16[5] = 0;
    res->u16[6] = 0;
    res->u16[7] = 0;
    sum = tmp.u8[16] + tmp.u8[17] + tmp.u8[18] + tmp.u8[19] + tmp.u8[20] + tmp.u8[21] + tmp.u8[22] + tmp.u8[23];
    res->u16[8] = sum;
    res->u16[9] = 0;
    res->u16[10] = 0;
    res->u16[11] = 0;
    sum = tmp.u8[24] + tmp.u8[25] + tmp.u8[16] + tmp.u8[27] + tmp.u8[28] + tmp.u8[29] + tmp.u8[30] + tmp.u8[31];
    res->u16[12] = sum;
    res->u16[13] = 0;
    res->u16[14] = 0;
    res->u16[15] = 0;

}

void vsqrtpd_128(XMM src, XMM *res) {
    int i;
    double df;

    for (i = 0; i < 2; ++i) {
        df = sqrt_df(src.fa64[i]);
        res->fa64[i] = df;
    }
}

void vsqrtpd_256(YMM src, YMM *res) {
    int i;
    double df;

    for (i = 0; i < 4; ++i) {
        df = sqrt_df(src.fa64[i]);
        res->fa64[i] = df;
    }
}

void vsqrtsd(XMM src, XMM vsrc, XMM *res) {
    double df;
    df = sqrt_df(src.fa64[0]);
    res->fa64[0] = df;
    res->fa64[1] = vsrc.fa64[1];
}

/************* Insert *************/
void vpinsrw(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int sel = imm & 7;
    uint16_t word = src.u16[0];

    res->u128 = vsrc.u128;
    res->u16[sel] = word;
}

/************* ADD *************/
void vpaddb_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->u8[i] = vsrc.u8[i] + src.u8[i];
    }
}
void vpaddb_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 32; ++i) {
        res->u8[i] = vsrc.u8[i] + src.u8[i];
    }
}

void vpaddw_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->u16[i] = vsrc.u16[i] + src.u16[i];
    }
}
void vpaddw_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->u16[i] = vsrc.u16[i] + src.u16[i];
    }
}

void vpaddd_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u32[i] = vsrc.u32[i] + src.u32[i];
    }
}
void vpaddd_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->u32[i] = vsrc.u32[i] + src.u32[i];
    }
}

void vpaddq_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->u64[i] = vsrc.u64[i] + src.u64[i];
    }
}
void vpaddq_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u64[i] = vsrc.u64[i] + src.u64[i];
    }
}

void vpaddsb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.a8[i] + src.a8[i];
        res->a8[i] = STSB(var);
    }
}
void vpaddsb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t var;

    for (i = 0; i < 32; ++i) {
        var = vsrc.a8[i] + src.a8[i];
        res->a8[i] = STSB(var);
    }
}
void vpaddsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t var;

    for (i = 0; i < 8; ++i) {
        var = vsrc.a16[i] + src.a16[i];
        res->a16[i] = STSW(var);
    }
}
void vpaddsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.a16[i] + src.a16[i];
        res->a16[i] = STSW(var);
    }
}
void vpaddusb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint16_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.u8[i] + src.u8[i];
        res->u8[i] = STUB(var);
    }
}
void vpaddusb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint16_t var;

    for (i = 0; i < 32; ++i) {
        var = vsrc.u8[i] + src.u8[i];
        res->u8[i] = STUB(var);
    }
}
void vpaddusw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint32_t var;

    for (i = 0; i < 8; ++i) {
        var = vsrc.u16[i] + src.u16[i];
        res->u16[i] = STUW(var);
    }
}
void vpaddusw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint32_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.u16[i] + src.u16[i];
        res->u16[i] = STUW(var);
    }
}
/************* SUB *************/
void vpsubb_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->a8[i] = vsrc.a8[i] - src.a8[i];
    }
}
void vpsubb_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 32; ++i) {
        res->a8[i] = vsrc.a8[i] - src.a8[i];
    }
}
void vpsubw_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->a16[i] = vsrc.a16[i] - src.a16[i];
    }
}
void vpsubw_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->a16[i] = vsrc.a16[i] - src.a16[i];
    }
}
void vpsubd_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a32[i] = vsrc.a32[i] - src.a32[i];
    }
}
void vpsubd_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->a32[i] = vsrc.a32[i] - src.a32[i];
    }
}
void vpsubq_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->a64[i] = vsrc.a64[i] - src.a64[i];
    }
}
void vpsubq_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a64[i] = vsrc.a64[i] - src.a64[i];
    }
}
void vpsubsb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int8_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.a8[i] - src.a8[i];
        res->a8[i] = STSB(var);
    }
}
void vpsubsb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int8_t var;

    for (i = 0; i < 32; ++i) {
        var = vsrc.a8[i] - src.a8[i];
        res->a8[i] = STSB(var);
    }
}
void vpsubsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t var;

    for (i = 0; i < 8; ++i) {
        var = vsrc.a16[i] - src.a16[i];
        res->a16[i] = STSW(var);
    }
}
void vpsubsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.a16[i] - src.a16[i];
        res->a16[i] = STSW(var);
    }
}
void vpsubusb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint8_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.u8[i] - src.u8[i];
        res->u8[i] = STUB(var);
    }
}
void vpsubusb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint8_t var;

    for (i = 0; i < 32; ++i) {
        var = vsrc.u8[i] - src.u8[i];
        res->u8[i] = STUB(var);
    }
}
void vpsubusw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint16_t var;

    for (i = 0; i < 8; ++i) {
        var = vsrc.u16[i] - src.u16[i];
        res->u16[i] = STUW(var);
    }
}
void vpsubusw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint16_t var;

    for (i = 0; i < 16; ++i) {
        var = vsrc.u16[i] - src.u16[i];
        res->u16[i] = STUW(var);
    }
}
void vsubpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->fa64[i] = vsrc.fa64[i] - src.fa64[i];
    }
}
void vsubpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->fa64[i] = vsrc.fa64[i] - src.fa64[i];
    }
}
void vsubsd(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] - src.fa64[0];
    res->fa64[1] = vsrc.fa64[1];
}
/************* Multiply *************/
void vmulpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] * src.fa64[0];
    res->fa64[1] = vsrc.fa64[1] * src.fa64[1];

}
void vmulpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->fa64[i] = vsrc.fa64[i] * src.fa64[i];
    }
}
void vmulsd(XMM src, XMM vsrc, XMM *res) {
    res->fa64[1] = vsrc.fa64[1];
    res->fa64[0] = vsrc.fa64[0] * src.fa64[0];
}
void vpmaddwd_128(XMM src, XMM vsrc, XMM *res) {
    res->u32[0] = (vsrc.u16[0] * src.u16[0]) + (vsrc.u16[1] * src.u16[1]);
    res->u32[1] = (vsrc.u16[2] * src.u16[2]) + (vsrc.u16[3] * src.u16[3]);
    res->u32[2] = (vsrc.u16[4] * src.u16[4]) + (vsrc.u16[5] * src.u16[5]);
    res->u32[3] = (vsrc.u16[6] * src.u16[6]) + (vsrc.u16[7] * src.u16[7]);
}
void vpmaddwd_256(YMM src, YMM vsrc, YMM *res) {
    res->u32[0] = (vsrc.u16[0] * src.u16[0]) + (vsrc.u16[1] * src.u16[1]);
    res->u32[1] = (vsrc.u16[2] * src.u16[2]) + (vsrc.u16[3] * src.u16[3]);
    res->u32[2] = (vsrc.u16[4] * src.u16[4]) + (vsrc.u16[5] * src.u16[5]);
    res->u32[3] = (vsrc.u16[6] * src.u16[6]) + (vsrc.u16[7] * src.u16[7]);
    res->u32[4] = (vsrc.u16[8] * src.u16[8]) + (vsrc.u16[9] * src.u16[9]);
    res->u32[5] = (vsrc.u16[10] * src.u16[10]) + (vsrc.u16[11] * src.u16[11]);
    res->u32[6] = (vsrc.u16[12] * src.u16[12]) + (vsrc.u16[13] * src.u16[13]);
    res->u32[7] = (vsrc.u16[14] * src.u16[14]) + (vsrc.u16[15] * src.u16[15]);
}
void vpmulhuw_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.u32[0] = vsrc.u16[i] * src.u16[i];
        res->u16[i] = tmp.u16[1];
    }
}
void vpmulhuw_256(YMM src, YMM vsrc, YMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 16; ++i) {
        tmp.u32[0] = vsrc.u16[i] * src.u16[i];
        res->u16[i] = tmp.u16[1];
    }
}
void vpmulhw_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.a32[0] = vsrc.a16[i] * src.a16[i];
        res->a16[i] = tmp.a16[1];
    }
}
void vpmulhw_256(YMM src, YMM vsrc, YMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 16; ++i) {
        tmp.a32[0] = vsrc.a16[i] * src.a16[i];
        res->a16[i] = tmp.a16[1];
    }
}
void vpmullw_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 8; ++i) {
        tmp.a32[0] = vsrc.a16[i] * src.a16[i];
        res->a16[i] = tmp.a16[0];
    }
}
void vpmullw_256(YMM src, YMM vsrc, YMM *res) {
    XMM tmp;
    int i;

    for (i = 0; i < 16; ++i) {
        tmp.a32[0] = vsrc.a16[i] * src.a16[i];
        res->a16[i] = tmp.a16[0];
    }
}
void vpmuludq_128(XMM src, XMM vsrc, XMM *res) {
    res->u64[0] = vsrc.u32[0] * src.u32[0];
    res->u64[1] = vsrc.u32[2] * src.u32[2];
}
void vpmuludq_256(YMM src, YMM vsrc, YMM *res) {
    res->u64[0] = vsrc.u32[0] * src.u32[0];
    res->u64[1] = vsrc.u32[2] * src.u32[2];
    res->u64[2] = vsrc.u32[4] * src.u32[4];
    res->u64[3] = vsrc.u32[6] * src.u32[6];
}

/************* Divide *************/
void vdivpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] / src.fa64[0];
    res->fa64[1] = vsrc.fa64[1] / src.fa64[1];
}
void vdivpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[0] / src.fa64[0];
    res->fa64[1] = vsrc.fa64[1] / src.fa64[1];
    res->fa64[2] = vsrc.fa64[2] / src.fa64[2];
    res->fa64[3] = vsrc.fa64[3] / src.fa64[3];
}
void vdivsd(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0] / src.fa64[0];
    res->fa64[1] = vsrc.fa64[1];
}

/************* AND *************/
void vandpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 2; ++i) {
        tmp.u64[0] = vsrc.u64[i] & src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vandpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 4; ++i) {
        tmp.u64[0] = vsrc.u64[i] & src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vandnpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 2; ++i) {
        tmp.u64[0] = (~(vsrc.u64[i])) & src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vandnpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 4; ++i) {
        tmp.u64[0] = (~(vsrc.u64[i])) & src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vpand_128(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128 & src.u128;
}
void vpand_256(YMM src, YMM vsrc, YMM *res) {
    res->u128[0] = vsrc.u128[0] & src.u128[0];
    res->u128[1] = vsrc.u128[1] & src.u128[1];
}
void vpandn_128(XMM src, XMM vsrc, XMM *res) {
    res->u128 = (~(vsrc.u128)) & src.u128;
}
void vpandn_256(YMM src, YMM vsrc, YMM *res) {
    res->u128[0] = (~(vsrc.u128[0])) & src.u128[0];
    res->u128[1] = (~(vsrc.u128[1])) & src.u128[1];
}

/************* OR/XOR *************/
void vorpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 2; ++i) {
        tmp.u64[0] = vsrc.u64[i] | src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vorpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 4; ++i) {
        tmp.u64[0] = vsrc.u64[i] | src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vxorpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 2; ++i) {
        tmp.u64[0] = vsrc.u64[i] ^ src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vxorpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    XMM tmp;

    for (i = 0; i < 4; ++i) {
        tmp.u64[0] = vsrc.u64[i] ^ src.u64[i];
        res->fa64[i] = tmp.fa64[0];
    }
}
void vpor_128(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128 | src.u128;
}
void vpor_256(YMM src, YMM vsrc, YMM *res) {
    res->u128[0] = vsrc.u128[0] | src.u128[0];
    res->u128[1] = vsrc.u128[1] | src.u128[1];
}
void vpxor_128(XMM src, XMM vsrc, XMM *res) {
    res->u128 = vsrc.u128 ^ src.u128;
}
void vpxor_256(YMM src, YMM vsrc, YMM *res) {
    res->u128[0] = vsrc.u128[0] ^ src.u128[0];
    res->u128[1] = vsrc.u128[1] ^ src.u128[1];
}

/************* Average *************/
void vpavgb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint16_t tmp;
    for (i = 0; i < 16; ++i) {
        tmp = (vsrc.u8[i] + src.u8[i] + 1) >> 1;
        res->u8[i] = tmp & 0xff;
    }
}
void vpavgb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint16_t tmp;
    for (i = 0; i < 32; ++i) {
        tmp = (vsrc.u8[i] + src.u8[i] + 1) >> 1;
        res->u8[i] = tmp & 0xff;
    }
}
void vpavgw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint32_t tmp;
    for (i = 0; i < 8; ++i) {
        tmp = (vsrc.u16[i] + src.u16[i] + 1) >> 1;
        res->u16[i] = tmp & 0xffff;
    }
}
void vpavgw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint32_t tmp;
    for (i = 0; i < 16; ++i) {
        tmp = (vsrc.u16[i] + src.u16[i] + 1) >> 1;
        res->u16[i] = tmp & 0xffff;
    }
}
/************* Shuffle *************/
void vpshufd_128(XMM src, XMM *res, uint8_t imm) {
    int i;
    int order;

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        res->u32[i] = src.u32[order];
    }
}
void vpshufd_256(YMM src, YMM *res, uint8_t imm) {
    int i;
    int order;

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        res->u32[i] = src.u32[order];
    }
    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        res->u32[i+4] = src.u32[order];
    }
}
void vpshufhw_128(XMM src, XMM *res, uint8_t imm) {
    int i;
    int order;

    XMM TMP, SRC;
    SRC.u64[0] = src.u64[1];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP.u16[i] = SRC.u16[order];
    }
    res->u64[0] = src.u64[0];
    res->u64[1] = TMP.u64[0];
}
void vpshufhw_256(YMM src, YMM *res, uint8_t imm) {
    int i;
    int order;

    XMM TMP1, TMP2, SRC;
    SRC.u64[0] = src.u64[1];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP1.u16[i] = SRC.u16[order];
    }
    SRC.u64[0] = src.u64[3];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP2.u16[i] = SRC.u16[order];
    }

    res->u64[0] = src.u64[0];
    res->u64[1] = TMP1.u64[0];
    res->u64[2] = src.u64[2];
    res->u64[3] = TMP2.u64[0];
}
void vpshuflw_128(XMM src, XMM *res, uint8_t imm) {
    int i;
    int order;

    XMM TMP, SRC;
    SRC.u64[0] = src.u64[0];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP.u16[i] = SRC.u16[order];
    }
    res->u64[0] = TMP.u64[0];
    res->u64[1] = src.u64[1];
}
void vpshuflw_256(YMM src, YMM *res, uint8_t imm) {
    int i;
    int order;

    XMM TMP1, TMP2, SRC;
    SRC.u64[0] = src.u64[0];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP1.u16[i] = SRC.u16[order];
    }
    SRC.u64[0] = src.u64[2];

    for (i = 0; i < 4; ++i) {
        order = (imm >> (i * 2)) & 3;
        TMP2.u16[i] = SRC.u16[order];
    }

    res->u64[0] = TMP1.u64[0];
    res->u64[1] = src.u64[1];
    res->u64[2] = TMP2.u64[0];
    res->u64[3] = src.u64[3];
}

// Left Logical
void vpsllw_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 8; ++i) {
        tmp = src.u16[i];
        res->u16[i] = tmp << count;
    }
}

void vpsllw_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 16; ++i) {
        tmp = src.u16[i];
        res->u16[i] = tmp << count;
    }
}

void vpslld_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 4; ++i) {
        tmp = src.u32[i];
        res->u32[i] = tmp << count;
    }
}
void vpslld_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 8; ++i) {
        tmp = src.u32[i];
        res->u32[i] = tmp << count;
    }
}

void vpsllq_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint64_t tmp = 0;
    if (count > 63) count = 64;

    for (i = 0; i < 2; ++i) {
        tmp = src.u64[i];
        res->u64[i] = tmp << count;
    }
}
void vpsllq_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint64_t tmp = 0;
    if (count > 63) count = 64;

    for (i = 0; i < 4; ++i) {
        tmp = src.u64[i];
        res->u64[i] = tmp << count;
    }
}

// Right Logical
void vpsrlw_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 8; ++i) {
        tmp = src.u16[i];
        res->u16[i] = tmp >> count;
    }
}

void vpsrlw_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 16; ++i) {
        tmp = src.u16[i];
        res->u16[i] = tmp >> count;
    }
}

void vpsrld_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 4; ++i) {
        tmp = src.u32[i];
        res->u32[i] = tmp >> count;
    }
}
void vpsrld_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 8; ++i) {
        tmp = src.u32[i];
        res->u32[i] = tmp >> count;
    }
}

void vpsrlq_128(XMM src, XMM *res, uint8_t count) {
    int i;
    uint64_t tmp = 0;
    if (count > 63) count = 64;

    for (i = 0; i < 2; ++i) {
        tmp = src.u64[i];
        res->u64[i] = tmp >> count;
    }
}
void vpsrlq_256(YMM src, YMM *res, uint8_t count) {
    int i;
    uint64_t tmp = 0;
    if (count > 63) count = 64;

    for (i = 0; i < 4; ++i) {
        tmp = src.u64[i];
        res->u64[i] = tmp >> count;
    }
}

// Right Logical (Sign Bits)
void vpsraw_128(XMM src, XMM *res, uint8_t count) {
    int i;
    int16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 8; ++i) {
        tmp = src.a16[i];
        res->a16[i] = tmp >> count;
    }
}

void vpsraw_256(YMM src, YMM *res, uint8_t count) {
    int i;
    int16_t tmp = 0;
    if (count > 15) count = 16;

    for (i = 0; i < 16; ++i) {
        tmp = src.a16[i];
        res->a16[i] = tmp >> count;
    }
}

void vpsrad_128(XMM src, XMM *res, uint8_t count) {
    int i;
    int32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 4; ++i) {
        tmp = src.a32[i];
        res->a32[i] = tmp >> count;
    }
}
void vpsrad_256(YMM src, YMM *res, uint8_t count) {
    int i;
    int32_t tmp = 0;
    if (count > 31) count = 32;

    for (i = 0; i < 8; ++i) {
        tmp = src.a32[i];
        res->a32[i] = tmp >> count;
    }
}

// Left Logical
void vpslldq_128(XMM src, XMM *res, uint8_t count) {
    if (count > 15) count = 16;
    res->u128 = src.u128 << (count * 8);
}
void vpslldq_256(YMM src, YMM *res, uint8_t count) {
    int i;
    XMM tmp;
    if (count > 15) count = 16;

    for (i = 0; i < 2; ++i) {
        tmp.u128 = src.u128[i];
        res->u128[i] = tmp.u128 << (count * 8);
    }
}

// Right Logical
void vpsrldq_128(XMM src, XMM *res, uint8_t count) {
    if (count > 15) count = 16;
    res->u128 = src.u128 >> (count * 8);
}
void vpsrldq_256(YMM src, YMM *res, uint8_t count) {
    int i;
    XMM tmp;
    if (count > 15) count = 16;

    for (i = 0; i < 2; ++i) {
        tmp.u128 = src.u128[i];
        res->u128[i] = tmp.u128 >> (count * 8);
    }
}

void vshufpd_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int imm0 = imm & 1;
    int imm1 = (imm >> 1) & 1;

    if (imm0 == 0)
        res->fa64[0] = vsrc.fa64[0];
    else
        res->fa64[0] = vsrc.fa64[1];

    if (imm1 == 0)
        res->fa64[1] = src.fa64[0];
    else
        res->fa64[1] = src.fa64[1];
}

void vshufpd_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int imm0 = imm & 1;
    int imm1 = (imm >> 1) & 1;
    int imm2 = (imm >> 2) & 1;
    int imm3 = (imm >> 3) & 1;

    if (imm0 == 0)
        res->fa64[0] = vsrc.fa64[0];
    else
        res->fa64[0] = vsrc.fa64[1];

    if (imm1 == 0)
        res->fa64[1] = src.fa64[0];
    else
        res->fa64[1] = src.fa64[1];

    if (imm2 == 0)
        res->fa64[2] = vsrc.fa64[2];
    else
        res->fa64[2] = vsrc.fa64[3];

    if (imm3 == 0)
        res->fa64[3] = src.fa64[2];
    else
        res->fa64[3] = src.fa64[3];
}

/************* Interleave *************/
void vpunpcklbw_128(XMM src, XMM vsrc, XMM *res) {
    res->u8[0] = vsrc.u8[0];
    res->u8[1] = src.u8[0];
    res->u8[2] = vsrc.u8[1];
    res->u8[3] = src.u8[1];
    res->u8[4] = vsrc.u8[2];
    res->u8[5] = src.u8[2];
    res->u8[6] = vsrc.u8[3];
    res->u8[7] = src.u8[3];
    res->u8[8] = vsrc.u8[4];
    res->u8[9] = src.u8[4];
    res->u8[10] = vsrc.u8[5];
    res->u8[11] = src.u8[5];
    res->u8[12] = vsrc.u8[6];
    res->u8[13] = src.u8[6];
    res->u8[14] = vsrc.u8[7];
    res->u8[15] = src.u8[7];
}
void vpunpcklbw_256(YMM src, YMM vsrc, YMM *res) {
    res->u8[0] = vsrc.u8[0];
    res->u8[1] = src.u8[0];
    res->u8[2] = vsrc.u8[1];
    res->u8[3] = src.u8[1];
    res->u8[4] = vsrc.u8[2];
    res->u8[5] = src.u8[2];
    res->u8[6] = vsrc.u8[3];
    res->u8[7] = src.u8[3];
    res->u8[8] = vsrc.u8[4];
    res->u8[9] = src.u8[4];
    res->u8[10] = vsrc.u8[5];
    res->u8[11] = src.u8[5];
    res->u8[12] = vsrc.u8[6];
    res->u8[13] = src.u8[6];
    res->u8[14] = vsrc.u8[7];
    res->u8[15] = src.u8[7];
    res->u8[16] = vsrc.u8[16];
    res->u8[17] = src.u8[16];
    res->u8[18] = vsrc.u8[17];
    res->u8[19] = src.u8[17];
    res->u8[20] = vsrc.u8[18];
    res->u8[21] = src.u8[18];
    res->u8[22] = vsrc.u8[19];
    res->u8[23] = src.u8[19];
    res->u8[24] = vsrc.u8[20];
    res->u8[25] = src.u8[20];
    res->u8[26] = vsrc.u8[21];
    res->u8[27] = src.u8[21];
    res->u8[28] = vsrc.u8[22];
    res->u8[29] = src.u8[22];
    res->u8[30] = vsrc.u8[23];
    res->u8[31] = src.u8[23];
}
void vpunpcklwd_128(XMM src, XMM vsrc, XMM *res) {
    res->u16[0] = vsrc.u16[0];
    res->u16[1] = src.u16[0];
    res->u16[2] = vsrc.u16[1];
    res->u16[3] = src.u16[1];
    res->u16[4] = vsrc.u16[2];
    res->u16[5] = src.u16[2];
    res->u16[6] = vsrc.u16[3];
    res->u16[7] = src.u16[3];
}

void vpunpcklwd_256(YMM src, YMM vsrc, YMM *res) {
    res->u16[0] = vsrc.u16[0];
    res->u16[1] = src.u16[0];
    res->u16[2] = vsrc.u16[1];
    res->u16[3] = src.u16[1];
    res->u16[4] = vsrc.u16[2];
    res->u16[5] = src.u16[2];
    res->u16[6] = vsrc.u16[3];
    res->u16[7] = src.u16[3];
    res->u16[8] = vsrc.u16[8];
    res->u16[9] = src.u16[8];
    res->u16[10] = vsrc.u16[9];
    res->u16[11] = src.u16[9];
    res->u16[12] = vsrc.u16[10];
    res->u16[13] = src.u16[10];
    res->u16[14] = vsrc.u16[11];
    res->u16[15] = src.u16[11];
}
void vpunpckldq_128(XMM src, XMM vsrc, XMM *res) {
    res->u32[0] = vsrc.u32[0];
    res->u32[1] = src.u32[0];
    res->u32[2] = vsrc.u32[1];
    res->u32[3] = src.u32[1];
}
void vpunpckldq_256(YMM src, YMM vsrc, YMM *res) {
    res->u32[0] = vsrc.u32[0];
    res->u32[1] = src.u32[0];
    res->u32[2] = vsrc.u32[1];
    res->u32[3] = src.u32[1];

    res->u32[4] = vsrc.u32[4];
    res->u32[5] = src.u32[4];
    res->u32[6] = vsrc.u32[5];
    res->u32[7] = src.u32[5];
}
void vpunpcklqdq_128(XMM src, XMM vsrc, XMM *res) {
    res->u64[0] = vsrc.u64[0];
    res->u64[1] = src.u64[0];
}
void vpunpcklqdq_256(YMM src, YMM vsrc, YMM *res) {
    res->u64[0] = vsrc.u64[0];
    res->u64[1] = src.u64[0];
    res->u64[2] = vsrc.u64[2];
    res->u64[3] = src.u64[2];
}

void vpunpckhbw_128(XMM src, XMM vsrc, XMM *res) {
    res->u8[0] = vsrc.u8[8];
    res->u8[1] = src.u8[8];
    res->u8[2] = vsrc.u8[9];
    res->u8[3] = src.u8[9];
    res->u8[4] = vsrc.u8[10];
    res->u8[5] = src.u8[10];
    res->u8[6] = vsrc.u8[11];
    res->u8[7] = src.u8[11];
    res->u8[8] = vsrc.u8[12];
    res->u8[9] = src.u8[12];
    res->u8[10] = vsrc.u8[13];
    res->u8[11] = src.u8[13];
    res->u8[12] = vsrc.u8[14];
    res->u8[13] = src.u8[14];
    res->u8[14] = vsrc.u8[15];
    res->u8[15] = src.u8[15];
}
void vpunpckhbw_256(YMM src, YMM vsrc, YMM *res) {
    res->u8[0] = vsrc.u8[8];
    res->u8[1] = src.u8[8];
    res->u8[2] = vsrc.u8[9];
    res->u8[3] = src.u8[9];
    res->u8[4] = vsrc.u8[10];
    res->u8[5] = src.u8[10];
    res->u8[6] = vsrc.u8[11];
    res->u8[7] = src.u8[11];
    res->u8[8] = vsrc.u8[12];
    res->u8[9] = src.u8[12];
    res->u8[10] = vsrc.u8[13];
    res->u8[11] = src.u8[13];
    res->u8[12] = vsrc.u8[14];
    res->u8[13] = src.u8[14];
    res->u8[14] = vsrc.u8[15];
    res->u8[15] = src.u8[15];
    res->u8[16] = vsrc.u8[24];
    res->u8[17] = src.u8[24];
    res->u8[18] = vsrc.u8[25];
    res->u8[19] = src.u8[25];
    res->u8[20] = vsrc.u8[26];
    res->u8[21] = src.u8[26];
    res->u8[22] = vsrc.u8[27];
    res->u8[23] = src.u8[27];
    res->u8[24] = vsrc.u8[28];
    res->u8[25] = src.u8[28];
    res->u8[26] = vsrc.u8[29];
    res->u8[27] = src.u8[29];
    res->u8[28] = vsrc.u8[30];
    res->u8[29] = src.u8[30];
    res->u8[30] = vsrc.u8[31];
    res->u8[31] = src.u8[31];
}
void vpunpckhwd_128(XMM src, XMM vsrc, XMM *res) {
    res->u16[0] = vsrc.u16[4];
    res->u16[1] = src.u16[4];
    res->u16[2] = vsrc.u16[5];
    res->u16[3] = src.u16[5];
    res->u16[4] = vsrc.u16[6];
    res->u16[5] = src.u16[6];
    res->u16[6] = vsrc.u16[7];
    res->u16[7] = src.u16[7];
}
void vpunpckhwd_256(YMM src, YMM vsrc, YMM *res) {
    res->u16[0] = vsrc.u16[4];
    res->u16[1] = src.u16[4];
    res->u16[2] = vsrc.u16[5];
    res->u16[3] = src.u16[5];
    res->u16[4] = vsrc.u16[6];
    res->u16[5] = src.u16[6];
    res->u16[6] = vsrc.u16[7];
    res->u16[7] = src.u16[7];
    res->u16[8] = vsrc.u16[12];
    res->u16[9] = src.u16[12];
    res->u16[10] = vsrc.u16[13];
    res->u16[11] = src.u16[13];
    res->u16[12] = vsrc.u16[14];
    res->u16[13] = src.u16[14];
    res->u16[14] = vsrc.u16[15];
    res->u16[15] = src.u16[15];
}
void vpunpckhdq_128(XMM src, XMM vsrc, XMM *res) {
    res->u32[0] = vsrc.u32[2];
    res->u32[1] = src.u32[2];
    res->u32[2] = vsrc.u32[3];
    res->u32[3] = src.u32[3];
}
void vpunpckhdq_256(YMM src, YMM vsrc, YMM *res) {
    res->u32[0] = vsrc.u32[2];
    res->u32[1] = src.u32[2];
    res->u32[2] = vsrc.u32[3];
    res->u32[3] = src.u32[3];
    res->u32[4] = vsrc.u32[6];
    res->u32[5] = src.u32[6];
    res->u32[6] = vsrc.u32[7];
    res->u32[7] = src.u32[7];
}
void vpunpckhqdq_128(XMM src, XMM vsrc, XMM *res) {
    res->u64[0] = vsrc.u64[1];
    res->u64[1] = src.u64[1];
}
void vpunpckhqdq_256(YMM src, YMM vsrc, YMM *res) {
    res->u64[0] = vsrc.u64[1];
    res->u64[1] = src.u64[1];
    res->u64[2] = vsrc.u64[3];
    res->u64[3] = src.u64[3];
}

void vunpcklpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[0];
    res->fa64[1] = src.fa64[0];
}
void vunpcklpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[0];
    res->fa64[1] = src.fa64[0];
    res->fa64[2] = vsrc.fa64[2];
    res->fa64[3] = src.fa64[2];
}
void vunpckhpd_128(XMM src, XMM vsrc, XMM *res) {
    res->fa64[0] = vsrc.fa64[1];
    res->fa64[1] = src.fa64[1];
}
void vunpckhpd_256(YMM src, YMM vsrc, YMM *res) {
    res->fa64[0] = vsrc.fa64[1];
    res->fa64[1] = src.fa64[1];
    res->fa64[2] = vsrc.fa64[3];
    res->fa64[3] = src.fa64[3];
}

/************* MAX/MIN Return *************/
void vminpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int MIN = 0;
    double SRC1, SRC2;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        MIN = mindf(SRC1, SRC2);
        if (MIN)
            res->fa64[i] = vsrc.fa64[i];
        else
            res->fa64[i] = src.fa64[i];
    }
}
void vminpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int MIN = 0;
    double SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        MIN = mindf(SRC1, SRC2);
        if (MIN)
            res->fa64[i] = vsrc.fa64[i];
        else
            res->fa64[i] = src.fa64[i];
    }

}

void vmaxpd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int MAX = 0;
    double SRC1, SRC2;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        MAX = maxdf(SRC1, SRC2);
        if (MAX)
            res->fa64[i] = vsrc.fa64[i];
        else
            res->fa64[i] = src.fa64[i];
    }
}
void vmaxpd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int MAX = 0;
    double SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        MAX = maxdf(SRC1, SRC2);
        if (MAX)
            res->fa64[i] = vsrc.fa64[i];
        else
            res->fa64[i] = src.fa64[i];
    }
}

void vminsd(XMM src, XMM vsrc, XMM *res) {
    int MIN = 0;
    double SRC1 = vsrc.fa64[0];
    double SRC2 = src.fa64[0];
    MIN = mindf(SRC1, SRC2);
    if (MIN)
        res->fa64[0] = vsrc.fa64[0];
    else
        res->fa64[0] = src.fa64[0];

    res->fa64[1] = vsrc.fa64[1];
}
void vmaxsd(XMM src, XMM vsrc, XMM *res) {
    int MAX = 0;
    double SRC1 = vsrc.fa64[0];
    double SRC2 = src.fa64[0];
    MAX = maxdf(SRC1, SRC2);
    if (MAX)
        res->fa64[0] = vsrc.fa64[0];
    else
        res->fa64[0] = src.fa64[0];

    res->fa64[1] = vsrc.fa64[1];
}

/************* Compare *************/
void vucomusd(XMM src, XMM dst, x86_saved_state_t *state) {
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

    double SRC1 = dst.fa64[0];
    double SRC2 = src.fa64[0];

    //UNORDERED
    if ((isNaN_f64(SRC1)) || (isNaN_f64(SRC1))) {
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

void vpcmpgtb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int8_t SRC1, SRC2;

    for (i = 0; i < 16; ++i) {
        SRC1 = vsrc.a8[i];
        SRC2 = src.a8[i];
        if (SRC1 > SRC2)
            res->a8[i] = 0xFF;
        else
            res->a8[i] = 0;
    }
}
void vpcmpgtb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int8_t SRC1, SRC2;

    for (i = 0; i < 32; ++i) {
        SRC1 = vsrc.a8[i];
        SRC2 = src.a8[i];
        if (SRC1 > SRC2)
            res->a8[i] = 0xFF;
        else
            res->a8[i] = 0;
    }
}

void vpcmpgtw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t SRC1, SRC2;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.a16[i];
        SRC2 = src.a16[i];
        if (SRC1 > SRC2)
            res->a16[i] = 0xFFFF;
        else
            res->a16[i] = 0;
    }
}

void vpcmpgtw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t SRC1, SRC2;

    for (i = 0; i < 16; ++i) {
        SRC1 = vsrc.a16[i];
        SRC2 = src.a16[i];
        if (SRC1 > SRC2)
            res->a16[i] = 0xFFFF;
        else
            res->a16[i] = 0;
    }
}

void vpcmpgtd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.a32[i];
        SRC2 = src.a32[i];
        if (SRC1 > SRC2)
            res->a32[i] = 0xFFFFFFFF;
        else
            res->a32[i] = 0;
    }
}
void vpcmpgtd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t SRC1, SRC2;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.a32[i];
        SRC2 = src.a32[i];
        if (SRC1 > SRC2)
            res->a32[i] = 0xFFFFFFFF;
        else
            res->a32[i] = 0;
    }
}

void vpcmpeqb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int8_t SRC1, SRC2;

    for (i = 0; i < 16; ++i) {
        SRC1 = vsrc.a8[i];
        SRC2 = src.a8[i];
        if (SRC1 == SRC2)
            res->a8[i] = 0xFF;
        else
            res->a8[i] = 0;
    }
}
void vpcmpeqb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int8_t SRC1, SRC2;

    for (i = 0; i < 32; ++i) {
        SRC1 = vsrc.a8[i];
        SRC2 = src.a8[i];
        if (SRC1 == SRC2)
            res->a8[i] = 0xFF;
        else
            res->a8[i] = 0;
    }
}

void vpcmpeqw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int16_t SRC1, SRC2;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.a16[i];
        SRC2 = src.a16[i];
        if (SRC1 == SRC2)
            res->a16[i] = 0xFFFF;
        else
            res->a16[i] = 0;
    }
}

void vpcmpeqw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int16_t SRC1, SRC2;

    for (i = 0; i < 16; ++i) {
        SRC1 = vsrc.a16[i];
        SRC2 = src.a16[i];
        if (SRC1 == SRC2)
            res->a16[i] = 0xFFFF;
        else
            res->a16[i] = 0;
    }
}

void vpcmpeqd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t SRC1, SRC2;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.a32[i];
        SRC2 = src.a32[i];
        if (SRC1 == SRC2)
            res->a32[i] = 0xFFFFFFFF;
        else
            res->a32[i] = 0;
    }
}
void vpcmpeqd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t SRC1, SRC2;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.a32[i];
        SRC2 = src.a32[i];
        if (SRC1 == SRC2)
            res->a32[i] = 0xFFFFFFFF;
        else
            res->a32[i] = 0;
    }
}

void vcmppd_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int CMP = 0;
    double SRC1, SRC2;
    uint8_t immvar = imm & 31;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        CMP = cmpoptdf(SRC1, SRC2, immvar);
        if (CMP)
            res->u64[i] = 0xFFFFFFFFFFFFFFFF;
        else
            res->u64[i] = 0;
    }
}
void vcmppd_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int CMP = 0;
    double SRC1, SRC2;
    uint8_t immvar = imm & 31;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.fa64[i];
        SRC2 = src.fa64[i];
        CMP = cmpoptdf(SRC1, SRC2, immvar);
        if (CMP)
            res->u64[i] = 0xFFFFFFFFFFFFFFFF;
        else
            res->u64[i] = 0;
    }
}
void vcmpsd(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int CMP = 0;
    uint8_t immvar = imm & 31;
    double SRC1 = vsrc.fa64[0];
    double SRC2 = src.fa64[0];
    CMP = cmpoptdf(SRC1, SRC2, immvar);
    if (CMP)
        res->u64[0] = 0xFFFFFFFFFFFFFFFF;
    else
        res->u64[0] = 0;

    res->u64[1] = vsrc.u64[1];
}

int vsse2_instruction(x86_saved_state_t *state,
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
    uint8_t mod = *modrm >> 6;
    uint8_t modreg = (*modrm >> 3) & 0x7;
    uint8_t num_dst = (*modrm >> 3) & 0x7;
    uint8_t num_src = *modrm & 0x7;

    if (high_reg) num_dst += 8;
    if (high_base) num_src += 8;

    uint64_t rmaddrs = 0;

    //get mxcsr round control
    int mxcsr_rc = getmxcsr();

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
            //VMOVUPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_128a(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMOVSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    if (mod == 3) {
                        vmovsd_128a(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    } else {
                        vmovsd_128b(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x11:
            //VMOVUPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_128b(xmmsrc, &xmmres);
                    if (mod == 3) {
                        _load_xmm(num_src, &xmmres);
                    } else {
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            //VMOVSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    if (mod == 3) {
                        vmovsd_128a(xmmdst, xmmvsrc, &xmmres);
                        _load_xmm(num_src, &xmmres);
                    } else {
                        vmovsd_128b(xmmdst, &xmmres);
                        rm_size = 64;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x12: //VMOVLPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovlpd_128a(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x13: //VMOVLPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovlpd_128b(xmmdst, &xmmres);
                    rm_size = 64;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
            break;

        case 0x16: //VMOVHPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovhpd_128a(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x17: //VMOVHPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovhpd_128b(xmmdst, &xmmres);
                    rm_size = 64;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
            break;

        case 0x28: //VMOVAPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_128a(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x29: //VMOVAPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_128b(xmmsrc, &xmmres);
                    if (mod == 3) {
                        _load_xmm(num_src, &xmmres);
                    } else {
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x6E: //VMOVD/VMOVQ DST <- SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    M64 tmp;
                    _store_m64(num_src, &tmp, state);
                    xmmsrc.u64[0] = tmp.u64;
                    vmovda(xmmsrc, &xmmres, operand_size);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x7E: //VMOVD/VMOVQ SRC <- DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovdb(xmmdst, &xmmres, operand_size);
                    if (mod == 3) {
                        M64 r64res;
                        r64res.u64 = xmmres.u64[0];
                        _load_m64(num_src, &r64res, state);
                    } else {
                        rm_size = operand_size;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x6F: //VMOVDQU/VMOVDQA DST <- SRC
            if ((simd_prefix == 1) || (simd_prefix == 2)) { //66 or F3
                if (leading_opcode == 1) {//0F
                    vmovdqu_128a(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x7F: //VMOVDQU/VMOVDQA SRC <- DST
            if ((simd_prefix == 1) || (simd_prefix == 2)) { //66 or F3
                if (leading_opcode == 1) {//0F
                    vmovdqu_128b(xmmdst, &xmmres);
                    if (mod == 3) {
                        _load_xmm(num_src, &xmmres);
                    } else {
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0xF7: //VMASKMOVDQU
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint64_t dest = saved_state64(state)->rdi; //Memory location
                    XMM var;
                    copyin(dest, (char*) &var.u128, 16);
                    vmaskmovdqu(xmmsrc, xmmdst, &xmmres, var);
                    rm_size = 128;
                    _load_maddr_from_xmm(dest, &xmmres, rm_size, state);
                }
            }
            break;

        case 0x2B: //VMOVNTPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovntdq_128(xmmdst, &xmmres);
                    rm_size = 128;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
            break;
        case 0xE7: //VMOVNTDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovntdq_128(xmmdst, &xmmres);
                    rm_size = 128;
                    _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                }
            }
            break;

        case 0x50: //VMOVMSKPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovmskpd_128(xmmsrc, &xmmres);
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
        case 0xD7: //VPMOVMSKB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmovmskb_128(xmmsrc, &xmmres);
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

        /************* Converts integers byte/word *************/
        case 0x63: //VPACKSSWB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpacksswb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x67: //VPACKUSWB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpackuswb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x6B: //VPACKSSWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpackssdw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        /************* Converts floating-point *************/
        case 0x2A:
            //VCVTSI2SD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    if (mod == 3) {
                        M64 r64src;
                        _store_m64(num_src, &r64src, state);
                        xmmsrc.u64[0] = r64src.u64;
                    }
                    vcvtsi2sd(xmmsrc, xmmvsrc, &xmmres, operand_size);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x2C:
            //VCVTTSD2SI
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vcvtsd2si(xmmsrc, &xmmres, 3, operand_size);
                    M64 m64res;
                    m64res.u64 = xmmres.u64[0];
                    _load_m64(num_dst, &m64res, state);
                }
            }
            break;
        case 0x2D:
            //VCVTSD2SI
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vcvtsd2si(xmmsrc, &xmmres, mxcsr_rc, operand_size);
                    M64 m64res;
                    m64res.u64 = xmmres.u64[0];
                    _load_m64(num_dst, &m64res, state);
                }
            }
            break;
        case 0xE6:
            //VCVTTPD2DQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcvtpd2dq_128(xmmsrc, &xmmres, 3);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTDQ2PD
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtdq2pd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTPD2DQ
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vcvtpd2dq_128(xmmsrc, &xmmres, mxcsr_rc);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5A:
            //VCVTPS2PD
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vcvtps2pd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTPD2PS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcvtpd2ps_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTSS2SD
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtss2sd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTSD2SS
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vcvtsd2ss(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5B:
            //VCVTDQ2PS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vcvtdq2ps_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTPS2DQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcvtps2dq_128(xmmsrc, &xmmres, mxcsr_rc);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTTPS2DQ
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtps2dq_128(xmmsrc, &xmmres, 3);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        /************* Computes *************/
        case 0x51:
            //VSQRTPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vsqrtpd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VSQRTSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vsqrtsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF6: //VPSADBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsadbw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Insert *************/
        case 0xC4: //VPINSRW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    if (operand_size == 32) { //W0
                        if (mod == 3) {
                            M64 r64src;
                            _store_m64(num_src, &r64src, state);
                            xmmsrc.u64[0] = r64src.u64;
                        }
                        vpinsrw(xmmsrc, xmmvsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;

        /************* ADD *************/
        case 0xFC: //VPADDB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xFD: //VPADDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xFE: //VPADDD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD4: //VPADDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xEC: //VPADDSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddsb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xED: //VPADDSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xDC: //VPADDUSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddusb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xDD: //VPADDUSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddusw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* SUB *************/
        case 0xF8: //VPSUBB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF9: //VPSUBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xFA: //VPSUBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xFB: //VPSUBQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0xE8: //VPSUBSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubsb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE9: //VPSUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD8: //VPSUBUSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubusb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD9: //VPSUBUSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubusw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5C:
            //VSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vsubpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VSUBSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vsubsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Multiply *************/
        case 0x59: //VMULPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmulpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMULSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vmulsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF5: //VPMADDWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaddwd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE4: //VPMULHUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmulhuw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE5: //VPMULHW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmulhw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD5: //VPMULLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmullw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF4: //VPMULUDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmuludq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Divide *************/
        case 0x5E:
            //VDIVPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vdivpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VDIVSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vdivsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* AND *************/
        case 0x54: //VANDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vandpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x55: //VANDNPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vandnpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xDB: //VPAND
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpand_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xDF: //VPANDN
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpandn_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* OR/XOR *************/
        case 0x56: //VORPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vorpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x57: //VXORPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vxorpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xEB: //VPOR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpor_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xEF: //VPXOR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpxor_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Average *************/
        case 0xE0: //VPAVGB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpavgb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE3: //VPAVGB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpavgw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Shuffle *************/
        case 0x70:
            //VPSHUFD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpshufd_128(xmmsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            //VPSHUFHW
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vpshufhw_128(xmmsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            //VPSHUFLW
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vpshuflw_128(xmmsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x71:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLW
                    if (modreg == 2) {
                        vpsrlw_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSRAW
                    if (modreg == 4) {
                        vpsraw_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSLLW
                    if (modreg == 6) {
                        vpsllw_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0x72:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLD
                    if (modreg == 2) {
                        vpsrld_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSRAD
                    if (modreg == 4) {
                        vpsrad_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSLLD
                    if (modreg == 6) {
                        vpslld_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0x73:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLQ
                    if (modreg == 2) {
                        vpsrlq_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSRLDQ
                    if (modreg == 3) {
                        vpsrldq_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSLLQ
                    if (modreg == 6) {
                        vpsllq_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                    //VPSLLDQ
                    if (modreg == 7) {
                        vpslldq_128(xmmsrc, &xmmres, imm);
                        _load_xmm(vexreg, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0xC6: //VSHUFPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vshufpd_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;

        case 0xD1: //VPSRLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsrlw_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD2: //VPSRLD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsrld_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xD3: //VPSRLQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsrlq_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE1: //VPSRAW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsraw_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xE2: //VPSRAD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsrad_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF1: //VPSLLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsllw_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF2: //VPSLLD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpslld_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xF3: //VPSLLQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = xmmsrc.u8[0];
                    vpsllq_128(xmmvsrc, &xmmres, count);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Interleave *************/
        case 0x60: //VPUNPCKLBW Byte
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklbw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x61: //VPUNPCKLWD Words
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklwd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x62: //VPUNPCKLDQ Doublewords
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckldq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x6C: //VPUNPCKLQDQ Quadword
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklqdq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x68: //VPUNPCKHBW Byte
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhbw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x69: //VPUNPCKHWD Words
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhwd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x6A: //VPUNPCKHDQ Doublewords
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhdq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x6D: //VPUNPCKHQDQ Quadword
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhqdq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x14: //VUNPCKLPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vunpcklpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x15: //VUNPCKHPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vunpckhpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* MAX/MIN Return *************/
        case 0x5D:
            //VMINPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vminpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMINSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vminsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5F:
            //VMAXPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmaxpd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VMAXSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vmaxsd(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Compare *************/
        case 0x2E: //VUCOMISD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vucomusd(xmmsrc, xmmdst, state);
                }
            }
            break;
        case 0x2F: //VCOMISD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vucomusd(xmmsrc, xmmdst, state);
                }
            }
            break;
        case 0x64: //VPCMPGTB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x65: //VPCMPGTW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x66: //VPCMPGTD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x74: //VPCMPEQB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x75: //VPCMPEQW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x76: //VPCMPEQD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xC2:
            //VCMPPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcmppd_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            //VCMPSD
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vcmpsd(xmmsrc, xmmvsrc, &xmmres, imm);
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
        /************* Move *************/
        case 0x10: //VMOVUPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_256a(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x11: //VMOVUPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_256b(ymmsrc, &ymmres);
                    if (mod == 3) {
                        _load_ymm(num_src, &ymmres);
                    } else {
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x28: //VMOVAPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_256a(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x29: //VMOVAPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovupd_256b(ymmsrc, &ymmres);
                    if (mod == 3) {
                        _load_ymm(num_src, &ymmres);
                    } else {
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x6F: //VMOVDQU/VMOVDQA DST <- SRC
            if ((simd_prefix == 1) || (simd_prefix == 2)) { //66 or F3
                if (leading_opcode == 1) {//0F
                    vmovdqu_256a(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x7F: //VMOVDQU/VMOVDQA SRC <- DST
            if ((simd_prefix == 1) || (simd_prefix == 2)) { //66 or F3
                if (leading_opcode == 1) {//0F
                    vmovdqu_256b(ymmdst, &ymmres);
                    if (mod == 3) {
                        _load_ymm(num_src, &ymmres);
                    } else {
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x2B: //VMOVNTPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovntdq_256(ymmdst, &ymmres);
                    rm_size = 256;
                    _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                }
            }
            break;
        case 0xE7: //VMOVNTDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovntdq_256(ymmdst, &ymmres);
                    rm_size = 256;
                    _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                }
            }
            break;

        case 0x50: //VMOVMSKPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmovmskpd_256(ymmsrc, &ymmres);
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
        case 0xD7: //VPMOVMSKB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmovmskb_256(ymmsrc, &ymmres);
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

        /************* Converts integers byte/word *************/
        case 0x63: //VPACKSSWB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpacksswb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x67: //VPACKUSWB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpackuswb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x6B: //VPACKSSWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpackssdw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* Converts floating-point *************/
        case 0xE6:
            //VCVTTPD2DQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    XMM xmmres;
                    vcvtpd2dq_256(ymmsrc, &xmmres, 3);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            //VCVTDQ2PD
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    XMM xmmsrc;
                    rm_size = 128;
                    get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);
                    vcvtdq2pd_256(xmmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VCVTPD2DQ
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    XMM xmmres;
                    vcvtpd2dq_256(ymmsrc, &xmmres, mxcsr_rc);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x5A:
            //VCVTPS2PD
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    XMM xmmsrc;
                    rm_size = 128;
                    get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                    vcvtps2pd_256(xmmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VCVTPD2PS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcvtpd2ps_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x5B:
            //VCVTDQ2PS
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) {//0F
                    vcvtdq2ps_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VCVTPS2DQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcvtps2dq_256(ymmsrc, &ymmres, mxcsr_rc);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            //VCVTTPS2DQ
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vcvtps2dq_256(ymmsrc, &ymmres, 3);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* Converts floating-point *************/
        case 0x51:
            //VSQRTPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vsqrtpd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
        case 0xF6: //VPSADBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsadbw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* ADD *************/
        case 0xD4: //VPADDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xFC: //VPADDB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xFD: //VPADDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xFE: //VPADDD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xEC: //VPADDSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddsb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xED: //VPADDSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xDC: //VPADDUSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddusb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xDD: //VPADDUSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpaddusw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* SUB *************/
        case 0xF8: //VPSUBB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF9: //VPSUBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xFA: //VPSUBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xFB: //VPSUBQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE8: //VPSUBSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubsb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE9: //VPSUBSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD8: //VPSUBUSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubusb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD9: //VPSUBUSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpsubusw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x5C: //VSUBPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vsubpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Multiply *************/
        case 0x59: //VMULPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmulpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF5: //VPMADDWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaddwd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE4: //VPMULHUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmulhuw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE5: //VPMULHW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmulhw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD5: //VPMULLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmullw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF4: //VPMULUDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmuludq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Divide *************/
        case 0x5E: //VDIVPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vdivpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* AND *************/
        case 0x54: //VANDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vandpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x55: //VANDNPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vandnpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xDB: //VPAND
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpand_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xDF: //VPANDN
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpandn_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* OR/XOR *************/
        case 0x56: //VORPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vorpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x57: //VXORPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vxorpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xEB: //VPOR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpor_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xEF: //VPXOR
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpxor_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Average *************/
        case 0xE0: //VPAVGB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpavgb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE3: //VPAVGB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpavgw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Shuffle *************/
        case 0x70:
            //VPSHUFD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpshufd_256(ymmsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            //VPSHUFHW
            if (simd_prefix == 2) { //F3
                if (leading_opcode == 1) {//0F
                    vpshufhw_256(ymmsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            //VPSHUFLW
            if (simd_prefix == 3) { //F2
                if (leading_opcode == 1) {//0F
                    vpshuflw_256(ymmsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x71:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLW
                    if (modreg == 2) {
                        vpsrlw_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSRAW
                    if (modreg == 4) {
                        vpsraw_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSLLW
                    if (modreg == 6) {
                        vpsllw_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0x72:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLD
                    if (modreg == 2) {
                        vpsrld_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSRAD
                    if (modreg == 4) {
                        vpsrad_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSLLD
                    if (modreg == 6) {
                        vpslld_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0x73:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    //VPSRLQ
                    if (modreg == 2) {
                        vpsrlq_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSRLDQ
                    if (modreg == 3) {
                        vpsrldq_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSLLQ
                    if (modreg == 6) {
                        vpsllq_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                    //VPSLLDQ
                    if (modreg == 7) {
                        vpslldq_256(ymmsrc, &ymmres, imm);
                        _load_ymm(vexreg, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0xC6: //VSHUFPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vshufpd_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0xD1: //VPSRLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsrlw_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD2: //VPSRLD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsrld_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xD3: //VPSRLQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsrlq_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE1: //VPSRAW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsraw_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xE2: //VPSRAD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsrad_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF1: //VPSLLW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsllw_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF2: //VPSLLD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpslld_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xF3: //VPSLLQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    uint8_t count = ymmsrc.u8[0];
                    vpsllq_256(ymmvsrc, &ymmres, count);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Interleave *************/
        case 0x60: //VPUNPCKLBW Byte
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklbw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x61: //VPUNPCKLWD Words
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklwd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x62: //VPUNPCKLDQ Doublewords
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckldq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x6C: //VPUNPCKLQDQ Quadword
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpcklqdq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
        case 0x68: //VPUNPCKHBW Byte
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhbw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x69: //VPUNPCKHWD Words
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhwd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x6A: //VPUNPCKHDQ Doublewords
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhdq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x6D: //VPUNPCKHQDQ Quadword
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpunpckhqdq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x14: //VUNPCKLPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vunpcklpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x15: //VUNPCKHPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vunpckhpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* MAX/MIN Return *************/
        case 0x5D: //VMINPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vminpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x5F: //VMAXPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vmaxpd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Compare *************/
        case 0x64: //VPCMPGTB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x65: //VPCMPGTW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x66: //VPCMPGTD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpgtd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x74: //VPCMPEQB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x75: //VPCMPEQW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x76: //VPCMPEQD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpcmpeqd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xC2: //VCMPPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vcmppd_256(ymmsrc, ymmvsrc, &ymmres, imm);
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


/*********************************************************/
int maxdf(double SRC1, double SRC2) {
    //return 1 is SRC1
    //return 0 is SRC2
    if ((SRC1 == 0.0) && (SRC2 == 0.0)) return 0;
    if (isNaN_f64(SRC1)) return 0;
    if (isNaN_f64(SRC2)) return 0;
    if (SRC1 > SRC2) return 1;

    return 0;
}

int mindf(double SRC1, double SRC2) {
    //return 1 is SRC1
    //return 0 is SRC2
    if ((SRC1 == 0.0) && (SRC2 == 0.0)) return 0;
    if (isNaN_f64(SRC1)) return 0;
    if (isNaN_f64(SRC2)) return 0;
    if (SRC1 < SRC2) return 1;

    return 0;
}

//comparison predicate operand
int cmpoptdf(double SRC1, double SRC2, uint8_t immvar) {
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
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 4:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 5:
        if (SRC1 >= SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 6:
        if (SRC1 > SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 7:
        opt = 1;
        if (isNaN_f64(SRC1)) opt = 0;
        if (isNaN_f64(SRC2)) opt = 0;
        break;
    case 8:
        if (SRC1 == SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 9:
        if (SRC1 < SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 10:
        if (SRC1 <= SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 11:
        opt = 0;
        break;
    case 12:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 0;
        if (isNaN_f64(SRC2)) opt = 0;
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
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 20:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 21:
        if (SRC1 >= SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 22:
        if (SRC1 > SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 23:
        opt = 1;
        if (isNaN_f64(SRC1)) opt = 0;
        if (isNaN_f64(SRC2)) opt = 0;
        break;
    case 24:
        if (SRC1 == SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 25:
        if (SRC1 < SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 26:
        if (SRC1 <= SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 1;
        if (isNaN_f64(SRC2)) opt = 1;
        break;
    case 27:
        opt = 0;
        break;
    case 28:
        if (SRC1 != SRC2) opt = 1;
        if (isNaN_f64(SRC1)) opt = 0;
        if (isNaN_f64(SRC2)) opt = 0;
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
