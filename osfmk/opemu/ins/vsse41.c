//
//  vsse41.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/8.
//  Copyright © 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vsse41.h"

/**********************************************/
/**  VSSE4.1  instructions implementation       **/
/**********************************************/
/************* Move *************/
void vmovntdqa_128(XMM src, XMM *res) {
    res->u128 = src.u128;
}
void vmovntdqa_256(YMM src, YMM *res) {
    res->u256 = src.u256;
}

void vpinsrb(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int sel = imm & 15;
    res->u128 = vsrc.u128;
    res->u8[sel] = src.u8[0];
}
void vpinsrd(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int sel = imm & 3;
    res->u128 = vsrc.u128;
    res->u32[sel] = src.u32[0];
}
void vpinsrq(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int sel = imm & 1;
    res->u128 = vsrc.u128;
    res->u64[sel] = src.u64[0];
}
void vinsertps(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int xbit;

    int count_s = (imm >> 6) & 3;
    int count_d = (imm >> 4) & 3;
    int zmask = imm & 15;
    float tmp = src.fa32[count_s];
    XMM tmp2;

    tmp2.u128 = vsrc.u128;
    tmp2.fa32[count_d] = tmp;

    for (i = 0; i < 4; ++i) {
        xbit = (zmask >> i) & 1;
        if (xbit)
            res->fa32[i] = 0;
        else
            res->fa32[i] = tmp2.fa32[i];
    }
}

void vpmovsxbw_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->a16[i] = src.a8[i];
    }
}
void vpmovsxbw_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->a16[i] = src.a8[i];
    }
}

void vpmovsxbd_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a32[i] = src.a8[i];
    }
}
void vpmovsxbd_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->a32[i] = src.a8[i];
    }
}

void vpmovsxbq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->a64[i] = src.a8[i];
    }
}
void vpmovsxbq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a64[i] = src.a8[i];
    }
}

void vpmovsxwd_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a32[i] = src.a16[i];
    }
}
void vpmovsxwd_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->a32[i] = src.a16[i];
    }
}

void vpmovsxwq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->a64[i] = src.a16[i];
    }
}
void vpmovsxwq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a64[i] = src.a16[i];
    }
}

void vpmovsxdq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->a64[i] = src.a32[i];
    }
}
void vpmovsxdq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->a64[i] = src.a32[i];
    }
}

void vpmovzxbw_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->u16[i] = src.u8[i];
    }
}
void vpmovzxbw_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 16; ++i) {
        res->u16[i] = src.u8[i];
    }
}

void vpmovzxbd_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u32[i] = src.u8[i];
    }
}
void vpmovzxbd_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->u32[i] = src.u8[i];
    }
}

void vpmovzxbq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->u64[i] = src.u8[i];
    }
}
void vpmovzxbq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u64[i] = src.u8[i];
    }
}

void vpmovzxwd_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u32[i] = src.u16[i];
    }
}
void vpmovzxwd_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i) {
        res->u32[i] = src.u16[i];
    }
}

void vpmovzxwq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->u64[i] = src.u16[i];
    }
}
void vpmovzxwq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u64[i] = src.u16[i];
    }
}

void vpmovzxdq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i) {
        res->u64[i] = src.u32[i];
    }
}
void vpmovzxdq_256(YMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i) {
        res->u64[i] = src.u32[i];
    }
}

/************* Convert *************/
void vpackusdw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->u16[i] = STUW(vsrc.a32[i]);
        res->u16[i+4] = STUW(src.a32[i]);
    }
}
void vpackusdw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        res->u16[i] = STUW(vsrc.a32[i]);
        res->u16[i+4] = STUW(src.a32[i]);
    }
    for (i = 0; i < 4; ++i) {
        res->u16[i+8] = STUW(vsrc.a32[i+4]);
        res->u16[i+12] = STUW(src.a32[i+4]);
    }
}

/************* Compare *************/
void vpcmpeqq_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 2; ++i) {
        if (vsrc.u64[i] == src.u64[i])
            res->u64[i] = 0xffffffffffffffff;
        else
            res->u64[i] = 0;
    }
}
void vpcmpeqq_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.u64[i] == src.u64[i])
            res->u64[i] = 0xffffffffffffffff;
        else
            res->u64[i] = 0;
    }
}
void vpmaxsb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.a8[i] > src.a8[i])
            res->a8[i] = vsrc.a8[i];
        else
            res->a8[i] = src.a8[i];
    }
}
void vpmaxsb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 32; ++i) {
        if (vsrc.a8[i] > src.a8[i])
            res->a8[i] = vsrc.a8[i];
        else
            res->a8[i] = src.a8[i];
    }
}
void vpmaxsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.a16[i] > src.a16[i])
            res->a16[i] = vsrc.a16[i];
        else
            res->a16[i] = src.a16[i];
    }
}
void vpmaxsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.a16[i] > src.a16[i])
            res->a16[i] = vsrc.a16[i];
        else
            res->a16[i] = src.a16[i];
    }
}
void vpmaxsd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.a32[i] > src.a32[i])
            res->a32[i] = vsrc.a32[i];
        else
            res->a32[i] = src.a32[i];
    }
}
void vpmaxsd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.a32[i] > src.a32[i])
            res->a32[i] = vsrc.a32[i];
        else
            res->a32[i] = src.a32[i];
    }
}

void vpmaxub_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.u8[i] > src.u8[i])
            res->u8[i] = vsrc.u8[i];
        else
            res->u8[i] = src.u8[i];
    }
}
void vpmaxub_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 32; ++i) {
        if (vsrc.u8[i] > src.u8[i])
            res->u8[i] = vsrc.u8[i];
        else
            res->u8[i] = src.u8[i];
    }
}
void vpmaxuw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.u16[i] > src.u16[i])
            res->u16[i] = vsrc.u16[i];
        else
            res->u16[i] = src.u16[i];
    }
}
void vpmaxuw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.u16[i] > src.u16[i])
            res->u16[i] = vsrc.u16[i];
        else
            res->u16[i] = src.u16[i];
    }
}
void vpmaxud_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.u32[i] > src.u32[i])
            res->u32[i] = vsrc.u32[i];
        else
            res->u32[i] = src.u32[i];
    }
}
void vpmaxud_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.u32[i] > src.u32[i])
            res->u32[i] = vsrc.u32[i];
        else
            res->u32[i] = src.u32[i];
    }
}

void vpminsb_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.a8[i] < src.a8[i])
            res->a8[i] = vsrc.a8[i];
        else
            res->a8[i] = src.a8[i];
    }
}
void vpminsb_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 32; ++i) {
        if (vsrc.a8[i] < src.a8[i])
            res->a8[i] = vsrc.a8[i];
        else
            res->a8[i] = src.a8[i];
    }
}
void vpminsw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.a16[i] < src.a16[i])
            res->a16[i] = vsrc.a16[i];
        else
            res->a16[i] = src.a16[i];
    }
}
void vpminsw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.a16[i] < src.a16[i])
            res->a16[i] = vsrc.a16[i];
        else
            res->a16[i] = src.a16[i];
    }
}
void vpminsd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.a32[i] < src.a32[i])
            res->a32[i] = vsrc.a32[i];
        else
            res->a32[i] = src.a32[i];
    }
}
void vpminsd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.a32[i] < src.a32[i])
            res->a32[i] = vsrc.a32[i];
        else
            res->a32[i] = src.a32[i];
    }
}

void vpminub_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.u8[i] < src.u8[i])
            res->u8[i] = vsrc.u8[i];
        else
            res->u8[i] = src.u8[i];
    }
}
void vpminub_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 32; ++i) {
        if (vsrc.u8[i] < src.u8[i])
            res->u8[i] = vsrc.u8[i];
        else
            res->u8[i] = src.u8[i];
    }
}
void vpminuw_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.u16[i] < src.u16[i])
            res->u16[i] = vsrc.u16[i];
        else
            res->u16[i] = src.u16[i];
    }
}
void vpminuw_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 16; ++i) {
        if (vsrc.u16[i] < src.u16[i])
            res->u16[i] = vsrc.u16[i];
        else
            res->u16[i] = src.u16[i];
    }
}
void vpminud_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.u32[i] < src.u32[i])
            res->u32[i] = vsrc.u32[i];
        else
            res->u32[i] = src.u32[i];
    }
}
void vpminud_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 8; ++i) {
        if (vsrc.u32[i] < src.u32[i])
            res->u32[i] = vsrc.u32[i];
        else
            res->u32[i] = src.u32[i];
    }
}

/************* multiply *************/
void vpmuldq_128(XMM src, XMM vsrc, XMM *res) {
    res->a64[0] = vsrc.a32[0] * src.a32[0];
    res->a64[1] = vsrc.a32[2] * src.a32[2];
}
void vpmuldq_256(YMM src, YMM vsrc, YMM *res) {
    res->a64[0] = vsrc.a32[0] * src.a32[0];
    res->a64[1] = vsrc.a32[2] * src.a32[2];
    res->a64[2] = vsrc.a32[4] * src.a32[4];
    res->a64[3] = vsrc.a32[6] * src.a32[6];
}

void vpmulld_128(XMM src, XMM vsrc, XMM *res) {
    XMM tmp;
    int i;
    for (i = 0; i < 4; ++i) {
        tmp.a64[0] = vsrc.a32[i] * src.a32[i];
        res->a32[i] = tmp.a32[0];
    }
}
void vpmulld_256(YMM src, YMM vsrc, YMM *res) {
    XMM tmp;
    int i;
    for (i = 0; i < 8; ++i) {
        tmp.a64[0] = vsrc.a32[i] * src.a32[i];
        res->a32[i] = tmp.a32[0];
    }
}

void vdpps_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int immvar;
    int imm0var = imm & 15;
    int imm4var = imm >> 4;

    XMM temp1, temp2, temp3, temp4;
    XMM SRC1, SRC2;

    //127:0 bit
    SRC1.u128 = vsrc.u128;
    SRC2.u128 = src.u128;

    for (i = 0; i < 4; ++i) {
        immvar = (imm4var > i) & 1;
        if (immvar == 1)
            temp1.fa32[i] = SRC1.fa32[i] * SRC2.fa32[i];
        else
            temp1.fa32[i] = 0.0;
    }

    temp2.fa32[0] = temp1.fa32[0] + temp1.fa32[1];
    temp3.fa32[0] = temp1.fa32[2] + temp1.fa32[3];
    temp4.fa32[0] = temp2.fa32[0] + temp3.fa32[0];

    for (i = 0; i < 4; ++i) {
        immvar = (imm0var > i) & 1;
        if (immvar == 1)
            res->fa32[i] = temp4.fa32[0];
        else
            res->fa32[i] = 0.0;
    }
}

void vdpps_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int immvar;
    int imm0var = imm & 15;
    int imm4var = imm >> 4;

    XMM temp1, temp2, temp3, temp4;
    XMM SRC1, SRC2;

    //127:0 bit
    SRC1.u128 = vsrc.u128[0];
    SRC2.u128 = src.u128[0];

    for (i = 0; i < 4; ++i) {
        immvar = (imm4var > i) & 1;
        if (immvar == 1)
            temp1.fa32[i] = SRC1.fa32[i] * SRC2.fa32[i];
        else
            temp1.fa32[i] = 0.0;
    }

    temp2.fa32[0] = temp1.fa32[0] + temp1.fa32[1];
    temp3.fa32[0] = temp1.fa32[2] + temp1.fa32[3];
    temp4.fa32[0] = temp2.fa32[0] + temp3.fa32[0];

    for (i = 0; i < 4; ++i) {
        immvar = (imm0var > i) & 1;
        if (immvar == 1)
            res->fa32[i] = temp4.fa32[0];
        else
            res->fa32[i] = 0.0;
    }

    //255:128 bit
    SRC1.u128 = vsrc.u128[1];
    SRC2.u128 = src.u128[1];

    for (i = 0; i < 4; ++i) {
        immvar = (imm4var > i) & 1;
        if (immvar == 1)
            temp1.fa32[i] = SRC1.fa32[i] * SRC2.fa32[i];
        else
            temp1.fa32[i] = 0.0;
    }

    temp2.fa32[0] = temp1.fa32[0] + temp1.fa32[1];
    temp3.fa32[0] = temp1.fa32[2] + temp1.fa32[3];
    temp4.fa32[0] = temp2.fa32[0] + temp3.fa32[0];

    for (i = 0; i < 4; ++i) {
        immvar = (imm0var > i) & 1;
        if (immvar == 1)
            res->fa32[i+4] = temp4.fa32[0];
        else
            res->fa32[i+4] = 0.0;
    }
}

void vdppd(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int immvar;
    int imm0var = imm & 15;
    int imm4var = imm >> 4;

    XMM temp1, temp2;
    XMM SRC1, SRC2;

    //127:0 bit
    SRC1.u128 = vsrc.u128;
    SRC2.u128 = src.u128;

    for (i = 0; i < 2; ++i) {
        immvar = (imm4var > i) & 1;
        if (immvar == 1)
            temp1.fa64[i] = SRC1.fa64[i] * SRC2.fa64[i];
        else
            temp1.fa64[i] = 0.0;
    }

    temp2.fa64[0] = temp1.fa64[0] + temp1.fa64[1];

    for (i = 0; i < 2; ++i) {
        immvar = (imm0var > i) & 1;
        if (immvar == 1)
            res->fa64[i] = temp2.fa64[0];
        else
            res->fa64[i] = 0.0;
    }
}

void vroundps_128(XMM src, XMM *res, uint8_t imm) {
    int i;
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }

    for (i = 0; i < 4; ++i) {
        res->fa32[i] = round_fp32(src.fa32[i], rc);
    }
}

void vroundps_256(YMM src, YMM *res, uint8_t imm) {
    int i;
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }

    for (i = 0; i < 8; ++i) {
        res->fa32[i] = round_fp32(src.fa32[i], rc);
    }
}

void vroundpd_128(XMM src, XMM *res, uint8_t imm) {
    int i;
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }

    for (i = 0; i < 2; ++i) {
        res->fa64[i] = round_fp64(src.fa64[i], rc);
    }
}
void vroundpd_256(YMM src, YMM *res, uint8_t imm) {
    int i;
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }

    for (i = 0; i < 4; ++i) {
        res->fa64[i] = round_fp64(src.fa64[i], rc);
    }
}

void vroundss(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }
    res->u128 = vsrc.u128;
    res->fa32[0] = round_fp32(src.fa32[0], rc);
}

void vroundsd(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int rc;
    int msi = (imm >> 2) & 1;
    if (msi == 0) {
        rc = imm & 3;
    } else {
        //get mxcsr round control
        rc = getmxcsr();
    }
    res->u128 = vsrc.u128;
    res->fa64[0] = round_fp64(src.fa64[0], rc);
}

/************* Select *************/
void vblendps_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int xbit = 0;
    for (i = 0; i < 4; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->fa32[i] = src.fa32[i];
        else
            res->fa32[i] = vsrc.fa32[i];
    }
}
void vblendps_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int xbit = 0;
    for (i = 0; i < 8; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->fa32[i] = src.fa32[i];
        else
            res->fa32[i] = vsrc.fa32[i];
    }
}

void vblendpd_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int xbit = 0;
    for (i = 0; i < 2; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->fa64[i] = src.fa64[i];
        else
            res->fa64[i] = vsrc.fa64[i];
    }
}
void vblendpd_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int xbit = 0;
    for (i = 0; i < 4; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->fa64[i] = src.fa64[i];
        else
            res->fa64[i] = vsrc.fa64[i];
    }
}

void vpblendw_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int xbit = 0;

    for (i = 0; i < 8; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->u16[i] = src.u16[i];
        else
            res->u16[i] = vsrc.u16[i];
    }
}
void vpblendw_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int xbit = 0;

    for (i = 0; i < 16; ++i) {
        xbit = (imm >> i) & 1;
        if (xbit)
            res->u16[i] = src.u16[i];
        else
            res->u16[i] = vsrc.u16[i];
    }
}

void vblendvps_128(XMM src, XMM vsrc, XMM *res, XMM immsrc) {
    int i;
    int xbit = 0;
    uint32_t mask;

    for (i = 0; i < 4; ++i) {
        mask = immsrc.u32[i];
        xbit = (mask >> 31) & 1;
        if (xbit)
            res->fa32[i] = src.fa32[i];
        else
            res->fa32[i] = vsrc.fa32[i];
    }
}
void vblendvps_256(YMM src, YMM vsrc, YMM *res, YMM immsrc) {
    int i;
    int xbit = 0;
    uint32_t mask;

    for (i = 0; i < 8; ++i) {
        mask = immsrc.u32[i];
        xbit = (mask >> 31) & 1;
        if (xbit)
            res->fa32[i] = src.fa32[i];
        else
            res->fa32[i] = vsrc.fa32[i];
    }
}

void vblendvpd_128(XMM src, XMM vsrc, XMM *res, XMM immsrc) {
    int i;
    int xbit = 0;
    uint64_t mask;

    for (i = 0; i < 2; ++i) {
        mask = immsrc.u64[i];
        xbit = (mask >> 63) & 1;
        if (xbit)
            res->fa64[i] = src.fa64[i];
        else
            res->fa64[i] = vsrc.fa64[i];
    }
}
void vblendvpd_256(YMM src, YMM vsrc, YMM *res, YMM immsrc) {
    int i;
    int xbit = 0;
    uint64_t mask;

    for (i = 0; i < 4; ++i) {
        mask = immsrc.u64[i];
        xbit = (mask >> 63) & 1;
        if (xbit)
            res->fa64[i] = src.fa64[i];
        else
            res->fa64[i] = vsrc.fa64[i];
    }
}

void vpblendvb_128(XMM src, XMM vsrc, XMM *res, XMM immsrc) {
    int i;
    int xbit = 0;
    uint8_t mask;

    for (i = 0; i < 16; ++i) {
        mask = immsrc.u8[i];
        xbit = (mask >> 7) & 1;
        if (xbit)
            res->u8[i] = src.u8[i];
        else
            res->u8[i] = vsrc.u8[i];
    }
}
void vpblendvb_256(YMM src, YMM vsrc, YMM *res, YMM immsrc) {
    int i;
    int xbit = 0;
    uint8_t mask;

    for (i = 0; i < 32; ++i) {
        mask = immsrc.u8[i];
        xbit = (mask >> 7) & 1;
        if (xbit)
            res->u8[i] = src.u8[i];
        else
            res->u8[i] = vsrc.u8[i];
    }
}

/************* Extract *************/
void vpextrb(XMM dst, XMM *res, uint8_t imm) {
    int sel = imm & 15;
    res->u128 = 0;
    res->u8[0] = dst.u8[sel];
}
void vpextrw(XMM dst, XMM *res, uint8_t imm) {
    int sel = imm & 7;
    res->u128 = 0;
    res->u16[0] = dst.u16[sel];
}
void vpextrd(XMM dst, XMM *res, uint8_t imm) {
    int sel = imm & 3;
    res->u128 = 0;
    res->u32[0] = dst.u32[sel];
}
void vpextrq(XMM dst, XMM *res, uint8_t imm) {
    int sel = imm & 1;
    res->u128 = 0;
    res->u64[0] = dst.u64[sel];
}
void vextractps(XMM dst, XMM *res, uint8_t imm) {
    int sel = imm & 3;
    res->u128 = 0;
    res->fa32[0] = dst.fa32[sel];
}

/************* Other *************/
void vphminposuw(XMM src, XMM *res) {
    int i;
    int index = 0;
    uint16_t min = src.u16[0];

    for (i = 1; i < 8; ++i) {
        if (src.u16[i] < min)
            index = i;
    }
    min = src.u16[index];

    res->u128 = 0;
    res->u16[0] = min;
    res->u16[1] = index;
}

void vptest_128(XMM src, XMM dst, x86_saved_state_t *state) {
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

    XMM AND1, AND2;

    AND1.u128 = src.u128 & dst.u128;
    AND2.u128 = src.u128 & ~(dst.u128);

    if (AND1.u128 == 0) {
        FLAGS |= 0x00000040; //set ZF = 1
    } else {
        FLAGS = (FLAGS | 0x00000040) ^ 0x00000040;  //set ZF = 0
    }

    if (AND2.u128 == 0) {
        FLAGS |= 0x00000001; //set CF = 1
    } else {
        FLAGS = (FLAGS | 0x00000001) ^ 0x00000001;  //set CF = 0
    }

    FLAGS = (FLAGS | 0x00000800) ^ 0x00000800;  //set OF = 0
    FLAGS = (FLAGS | 0x00000010) ^ 0x00000010;  //set AF = 0
    FLAGS = (FLAGS | 0x00000080) ^ 0x00000080;  //set SF = 0
    FLAGS = (FLAGS | 0x00000004) ^ 0x00000004;  //set PF = 0

    if (is_saved_state64(state)) {
        saved_state64(state)->isf.rflags = FLAGS;
    } else {
        EFLAGS = FLAGS & 0xFFFFFFFF;
        saved_state32(state)->efl = EFLAGS;
    }
}

void vptest_256(YMM src, YMM dst, x86_saved_state_t *state) {
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

    XMM AND11, AND12, AND21, AND22;

    AND11.u128 = src.u128[0] & dst.u128[0];
    AND12.u128 = src.u128[0] & dst.u128[0];

    AND21.u128 = src.u128[1] & ~(dst.u128[1]);
    AND22.u128 = src.u128[1] & ~(dst.u128[1]);

    if ( (AND11.u128 == 0) && (AND12.u128 == 0) ) {
        FLAGS |= 0x00000040; //set ZF = 1
    } else {
        FLAGS = (FLAGS | 0x00000040) ^ 0x00000040;  //set ZF = 0
    }

    if  ( (AND21.u128 == 0) && (AND22.u128 == 0) )  {
        FLAGS |= 0x00000001; //set CF = 1
    } else {
        FLAGS = (FLAGS | 0x00000001) ^ 0x00000001;  //set CF = 0
    }

    FLAGS = (FLAGS | 0x00000800) ^ 0x00000800;  //set OF = 0
    FLAGS = (FLAGS | 0x00000010) ^ 0x00000010;  //set AF = 0
    FLAGS = (FLAGS | 0x00000080) ^ 0x00000080;  //set SF = 0
    FLAGS = (FLAGS | 0x00000004) ^ 0x00000004;  //set PF = 0

    if (is_saved_state64(state)) {
        saved_state64(state)->isf.rflags = FLAGS;
    } else {
        EFLAGS = FLAGS & 0xFFFFFFFF;
        saved_state32(state)->efl = EFLAGS;
    }
}

void vmpsadbw_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int8_t X;
    int blk1 = (imm >> 2) & 1 ;  //imm8[2]
    int blk2 = imm & 3;          //imm8[1:0]
    XMM src1_byte, src2_byte;
    uint8_t temp0, temp1, temp2, temp3;

    src1_byte.u32[0] = vsrc.u32[blk1];
    src1_byte.u32[0] = vsrc.u32[blk1+1];
    src1_byte.u32[0] = vsrc.u32[blk1+2];

    src2_byte.u32[0] = src.u32[blk2];

    for (i = 0; i < 8; ++i) {
        X = src1_byte.a8[i] - src2_byte.a8[0];
        temp0 = ABS(X);
        X = src1_byte.a8[1+i] - src2_byte.a8[1];
        temp1 = ABS(X);
        X = src1_byte.a8[2+i] - src2_byte.a8[2];
        temp2 = ABS(X);
        X = src1_byte.a8[3+i] - src2_byte.a8[3];
        temp3 = ABS(X);
        res->u16[i] = temp0 + temp1 + temp2 + temp3;
    }
}

void vmpsadbw_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int8_t X;
    int blk1;
    int blk2;
    XMM src1, src2, src1_byte, src2_byte;
    XMM dest;
    uint8_t temp0, temp1, temp2, temp3;

    //[127:0] bit
    blk1 = (imm >> 2) & 1; //imm8[2]
    blk2 = imm & 3;        //imm8[1:0]
    src1.u128 = vsrc.u128[0];
    src2.u128 = src.u128[0];

    src1_byte.u32[0] = src1.u32[blk1];
    src1_byte.u32[0] = src1.u32[blk1+1];
    src1_byte.u32[0] = src1.u32[blk1+2];

    src2_byte.u32[0] = src2.u32[blk2];

    for (i = 0; i < 8; ++i) {
        X = src1_byte.a8[i] - src2_byte.a8[0];
        temp0 = ABS(X);
        X = src1_byte.a8[i+1] - src2_byte.a8[1];
        temp1 = ABS(X);
        X = src1_byte.a8[i+2] - src2_byte.a8[2];
        temp2 = ABS(X);
        X = src1_byte.a8[i+3] - src2_byte.a8[3];
        temp3 = ABS(X);
        dest.u16[i] = temp0 + temp1 + temp2 + temp3;
    }

    res->u128[0] = dest.u128;

    //[255:128] bit
    blk1 = (imm >> 5) & 1; //imm8[5]
    blk2 = (imm >> 3) & 3; //imm8[4:3]

    src1.u128 = vsrc.u128[1];
    src2.u128 = src.u128[1];

    src1_byte.u32[0] = src1.u32[blk1];
    src1_byte.u32[0] = src1.u32[blk1+1];
    src1_byte.u32[0] = src1.u32[blk1+2];

    src2_byte.u32[0] = src2.u32[blk2];

    for (i = 0; i < 8; ++i) {
        X = src1_byte.a8[i] - src2_byte.a8[0];
        temp0 = ABS(X);
        X = src1_byte.a8[i+1] - src2_byte.a8[1];
        temp1 = ABS(X);
        X = src1_byte.a8[i+2] - src2_byte.a8[2];
        temp2 = ABS(X);
        X = src1_byte.a8[i+3] - src2_byte.a8[3];
        temp3 = ABS(X);
        dest.u16[i] = temp0 + temp1 + temp2 + temp3;
    }

    res->u128[1] = dest.u128;
}

int vsse41_instruction(x86_saved_state_t *state,
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
        /************* Move *************/
        case 0x2A:
            //VMOVNTDQA
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vmovntdqa_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x20:
            if (simd_prefix == 1) { //66
                //VPMOVSXBW
                if (leading_opcode == 2) {//0F38
                    vpmovsxbw_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
                //VPINSRB
                if (leading_opcode == 3) {//0F3A
                    if(mod == 3) {
                        M64 r64;
                        _store_m64(num_src, &r64, state);
                        xmmsrc.u64[0] = r64.u64;
                    }
                    vpinsrb(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x21:
            //VPMOVSXBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxbd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
                //VINSERTPS
                if (leading_opcode == 3) {//0F3A
                    vinsertps(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x22:
            if (simd_prefix == 1) { //66
                //VPMOVSXBQ
                if (leading_opcode == 2) {//0F38
                    vpmovsxbq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
                //VPINSRD / VPINSRQ
                if (leading_opcode == 3) {//0F3A
                    if(mod == 3) {
                        M64 r64;
                        _store_m64(num_src, &r64, state);
                        xmmsrc.u64[0] = r64.u64;
                    }
                    if (operand_size == 32) {
                        vpinsrd(xmmsrc, xmmvsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    } else {
                        vpinsrq(xmmsrc, xmmvsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;
        case 0x23:
            //VPMOVSXWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxwd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x24:
            //VPMOVSXWQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxwq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x25:
            //VPMOVSXDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxdq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x30:
            //VPMOVZXBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbw_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x31:
            //VPMOVZXBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x32:
            //VPMOVZXBQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x33:
            //VPMOVZXWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxwd_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x34:
            //VPMOVZXWQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxwq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x35:
            //VPMOVZXDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxdq_128(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Convert *************/
        case 0x2B:
            //VPACKUSDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpackusdw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Compare *************/
        case 0x29:
            //VPCMPEQQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpcmpeqq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3C:
            //VPMAXSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxsb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xEE:
            //VPMAXSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaxsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3D:
            //VPMAXSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxsd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0xDE:
            //VPMAXUB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaxub_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3E:
            //VPMAXUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxuw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3F:
            //VPMAXUD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxud_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x38:
            //VPMINSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminsb_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0xEA:
            //VPMINSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpminsw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x39:
            //VPMINSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminsd_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0xDA:
            //VPMINUB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpminub_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3A:
            //VPMINUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminuw_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x3B:
            //VPMINUD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminud_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* multiply *************/
        case 0x28:
            //VPMULDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmuldq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        case 0x40:
            if (simd_prefix == 1) { //66
                //VPMULLD
                if (leading_opcode == 2) {//0F38
                    vpmulld_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
                //VDPPS
                if (leading_opcode == 3) {//0F3A
                    vdpps_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x41:
            if (simd_prefix == 1) { //66
                //VDPPD
                if (leading_opcode == 3) {//0F3A
                    vdppd(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
                //VPHMINPOSUW
                if (leading_opcode == 2) {//0F38
                    vphminposuw(xmmsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;
        /************* Round *************/
        case 0x08:
            //VROUNDPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundps_128(xmmsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x09:
            //VROUNDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundpd_128(xmmsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x0A:
            //VROUNDSS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundss(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x0B:
            //VROUNDSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundsd(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        /************* Select *************/
        case 0x0C:
            //VBLENDPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vblendps_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x0D:
            //VBLENDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vblendpd_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x0E:
            //VPBLENDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpblendw_128(xmmsrc, xmmvsrc, &xmmres, imm);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x4A:
            //VBLENDVPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    XMM immsrc;
                    _store_xmm(immreg, &immsrc);
                    vblendvps_128(xmmsrc, xmmvsrc, &xmmres, immsrc);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x4B:
            //VBLENDVPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    XMM immsrc;
                    _store_xmm(immreg, &immsrc);
                    vblendvpd_128(xmmsrc, xmmvsrc, &xmmres, immsrc);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        case 0x4C:
            //VPBLENDVB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    XMM immsrc;
                    _store_xmm(immreg, &immsrc);
                    vpblendvb_128(xmmsrc, xmmvsrc, &xmmres, immsrc);
                    _load_xmm(num_dst, &xmmres);
                    ins_size++;
                }
            }
            break;
        /************* Extract *************/
        case 0x14:
            //VPEXTRB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpextrb(xmmdst, &xmmres, imm);
                    if(mod == 3) {
                        M64 r64;
                        r64.u64 = xmmres.u64[0];
                        _load_m64(num_src, &r64, state);
                    } else {
                        rm_size = operand_size;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                    ins_size++;
                }
            }
            break;
        case 0x15:
            //VPEXTRW DST -> SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpextrw(xmmdst, &xmmres, imm);
                    if(mod == 3) {
                        M64 r64;
                        r64.u64 = xmmres.u64[0];
                        _load_m64(num_src, &r64, state);
                    } else {
                        rm_size = operand_size;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                    ins_size++;
                }
            }
            break;
        case 0x16:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    //VPEXTRD / VPEXTRQ
                    if (operand_size == 32) { //VPEXTRD
                        vpextrd(xmmdst, &xmmres, imm);
                        if(mod == 3) {
                            M64 r64;
                            r64.u64 = xmmres.u64[0];
                            _load_m64(num_src, &r64, state);
                        } else {
                            rm_size = operand_size;
                            _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                        }
                        ins_size++;
                    } else { //VPEXTRQ
                        vpextrq(xmmdst, &xmmres, imm);
                        if(mod == 3) {
                            M64 r64;
                            r64.u64 = xmmres.u64[0];
                            _load_m64(num_src, &r64, state);
                        } else {
                            rm_size = operand_size;
                            _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                        }
                        ins_size++;

                    }
                }
            }
            break;
        case 0xC5:
            //VPEXTRW SRC -> DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpextrw(xmmsrc, &xmmres, imm);
                    M64 r64;
                    r64.u64 = xmmres.u64[0];
                    _load_m64(num_dst, &r64, state);
                    ins_size++;
                }
            }
            break;
        case 0x17:
            if (simd_prefix == 1) { //66
                //VEXTRACTPS DST -> SRC
                if (leading_opcode == 3) {//0F3A
                    vextractps(xmmdst, &xmmres, imm);
                    if(mod == 3) {
                        M64 r64;
                        r64.u64 = xmmres.u64[0];
                        _load_m64(num_src, &r64, state);
                    } else {
                        rm_size = operand_size;
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                    ins_size++;
                }
                //VPTEST
                if (leading_opcode == 2) {//0F38
                    vptest_128(xmmsrc, xmmdst, state);
                }
            }
            break;
        /************* Other *************/
        case 0x42:
            //VMPSADBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vmpsadbw_128(xmmsrc, xmmvsrc, &xmmres, imm);
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
        case 0x2A:
            //VMOVNTDQA
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vmovntdqa_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x20:
            //VPMOVSXBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxbw_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x21:
            //VPMOVSXBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxbd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x22:
            //VPMOVSXBQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxbq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x23:
            //VPMOVSXWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxwd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x24:
            //VPMOVSXWQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxwq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x25:
            //VPMOVSXDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovsxdq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x30:
            //VPMOVZXBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbw_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x31:
            //VPMOVZXBD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x32:
            //VPMOVZXBQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxbq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x33:
            //VPMOVZXWD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxwd_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x34:
            //VPMOVZXWQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxwq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x35:
            //VPMOVZXDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmovzxdq_256(ymmsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        /************* Convert *************/
        case 0x2B:
            //VPACKUSDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpackusdw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* Compare *************/
        case 0x29:
            //VPCMPEQQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpcmpeqq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3C:
            //VPMAXSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxsb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xEE:
            //VPMAXSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaxsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3D:
            //VPMAXSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxsd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0xDE:
            //VPMAXUB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpmaxub_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3E:
            //VPMAXUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxuw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3F:
            //VPMAXUD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmaxud_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0x38:
            //VPMINSB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminsb_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0xEA:
            //VPMINSW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpminsw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x39:
            //VPMINSD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminsd_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;

        case 0xDA:
            //VPMINUB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 1) {//0F
                    vpminub_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3A:
            //VPMINUW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminuw_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x3B:
            //VPMINUD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpminud_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        /************* multiply *************/
        case 0x28:
            //VPMULDQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpmuldq_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
            }
            break;
        case 0x40:
            if (simd_prefix == 1) { //66
                //VPMULLD
                if (leading_opcode == 2) {//0F38
                    vpmulld_256(ymmsrc, ymmvsrc, &ymmres);
                    _load_ymm(num_dst, &ymmres);
                }
                //VDPPS
                if (leading_opcode == 3) {//0F3A
                    vdpps_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;

        /************* Round *************/
        case 0x08:
            //VROUNDPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundps_256(ymmsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x09:
            //VROUNDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vroundpd_256(ymmsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        /************* Select *************/
        case 0x0C:
            //VBLENDPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vblendps_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x0D:
            //VBLENDPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vblendpd_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x0E:
            //VPBLENDW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vpblendw_256(ymmsrc, ymmvsrc, &ymmres, imm);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x4A:
            //VBLENDVPS
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    YMM immsrc;
                    _store_ymm(immreg, &immsrc);
                    vblendvps_256(ymmsrc, ymmvsrc, &ymmres, immsrc);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x4B:
            //VBLENDVPD
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    YMM immsrc;
                    _store_ymm(immreg, &immsrc);
                    vblendvpd_256(ymmsrc, ymmvsrc, &ymmres, immsrc);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        case 0x4C:
            //VPBLENDVB
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    int immreg = (imm >> 4) & 15;
                    YMM immsrc;
                    _store_ymm(immreg, &immsrc);
                    vpblendvb_256(ymmsrc, ymmvsrc, &ymmres, immsrc);
                    _load_ymm(num_dst, &ymmres);
                    ins_size++;
                }
            }
            break;
        /************* Other *************/
        case 0x17:
            //VPTEST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vptest_256(ymmsrc, ymmdst, state);
                }
            }
            break;
        case 0x42:
            //VMPSADBW
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    vmpsadbw_256(ymmsrc, ymmvsrc, &ymmres, imm);
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
