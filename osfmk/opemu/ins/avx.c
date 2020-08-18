//
//  avx.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/26.
//  Copyright © 2019 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "avx.h"

/**********************************************/
/**  AVX instructions implementation         **/
/**********************************************/
void vbroadcastss_128(XMM src, XMM *res) {
    res->fa32[0] = src.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = src.fa32[0];
    res->fa32[3] = src.fa32[0];
}

void vbroadcastss_256(XMM src, YMM *res) {
    res->fa32[0] = src.fa32[0];
    res->fa32[1] = src.fa32[0];
    res->fa32[2] = src.fa32[0];
    res->fa32[3] = src.fa32[0];
    res->fa32[4] = src.fa32[0];
    res->fa32[5] = src.fa32[0];
    res->fa32[6] = src.fa32[0];
    res->fa32[7] = src.fa32[0];

}

void vbroadcastsd(XMM src, YMM *res) {
    res->fa64[0] = src.fa64[0];
    res->fa64[1] = src.fa64[0];
    res->fa64[2] = src.fa64[0];
    res->fa64[3] = src.fa64[0];

}

void vbroadcastf128(XMM src, YMM *res) {
    res->a128[0] = src.a128;
    res->a128[1] = src.a128;
}

void vpbroadcastb_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 16; ++i)
        res->u8[i] = src.u8[0];
}
void vpbroadcastb_256(XMM src, YMM *res) {
    int i;

    for (i = 0; i < 32; ++i)
        res->u8[i] = src.u8[0];
}

void vpbroadcastw_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 8; ++i)
        res->u16[i] = src.u16[0];
}
void vpbroadcastw_256(XMM src, YMM *res) {
    int i;

    for (i = 0; i < 16; ++i)
        res->u16[i] = src.u16[0];
}

void vpbroadcastd_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 4; ++i)
        res->u32[i] = src.u32[0];
}
void vpbroadcastd_256(XMM src, YMM *res) {
    int i;

    for (i = 0; i < 8; ++i)
        res->u32[i] = src.u32[0];
}

void vpbroadcastq_128(XMM src, XMM *res) {
    int i;

    for (i = 0; i < 2; ++i)
        res->u64[i] = src.u64[0];
}
void vpbroadcastq_256(XMM src, YMM *res) {
    int i;

    for (i = 0; i < 4; ++i)
        res->u64[i] = src.u64[0];
}

void vbroadcasti128(XMM src, YMM *res) {
    int i;

    for (i = 0; i < 2; ++i)
        res->u128[i] = src.u128;
}

void vextractf128(YMM dst, XMM *res, uint8_t imm) {
    int IMM0 = imm & 1;

    if (IMM0 == 1) {
        res->fa64[0] = dst.fa64[2];
        res->fa64[1] = dst.fa64[3];
    } else {
        res->fa64[0] = dst.fa64[0];
        res->fa64[1] = dst.fa64[1];
    }
}

void vextracti128(YMM dst, XMM *res, uint8_t imm) {
    int IMM0 = imm & 1;

    if (IMM0 == 1)
        res->u128 = dst.u128[1];
    else
        res->u128 = dst.u128[0];
}

void vinsertf128(XMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int IMM0 = imm & 1;

    YMM TEMP;
    TEMP.u256 = vsrc.u256;

    if (IMM0 == 1)
        TEMP.u128[1] = src.u128;
    else
        TEMP.u128[0] = src.u128;

    res->fa64[0] = TEMP.fa64[0];
    res->fa64[1] = TEMP.fa64[1];
    res->fa64[2] = TEMP.fa64[2];
    res->fa64[3] = TEMP.fa64[3];
}

void vinserti128(XMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int IMM0 = imm & 1;

    YMM TEMP;
    TEMP.u256 = vsrc.u256;

    if (IMM0 == 1)
        TEMP.u128[1] = src.u128;
    else
        TEMP.u128[0] = src.u128;

    res->u256 = TEMP.u256;
}

void vmaskmovps_load_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->fa32[i] = src.fa32[i];
        } else {
            res->u32[i] = 0;
        }
    }
}

void vmaskmovps_load_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->fa32[i] = src.fa32[i];
        } else {
            res->u32[i] = 0;
        }
    }

}

void vmaskmovps_store_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->fa32[i] = src.fa32[i];
        }
    }
}

void vmaskmovps_store_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->fa32[i] = src.fa32[i];
        }
    }
}

void vmaskmovpd_load_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[i];
        } else {
            res->u64[i] = 0;
        }
    }
}

void vmaskmovpd_load_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[i];
        } else {
            res->u64[i] = 0;
        }
    }
}

void vmaskmovpd_store_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[i];
        }
    }
}

void vmaskmovpd_store_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[i];
        }
    }
}

void vpblendd_128(XMM src, XMM vsrc, XMM *res, uint8_t imm) {
    int i;
    int cs;

    for (i = 0; i < 4; ++i) {
        cs = (imm >> i) & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        } else {
            res->u32[i] = vsrc.u32[i];
        }
    }
}
void vpblendd_256(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int i;
    int cs;

    for (i = 0; i < 8; ++i) {
        cs = (imm >> i) & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        } else {
            res->u32[i] = vsrc.u32[i];
        }
    }
}

void vpermilpd_128a(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask = 0;

    for (i = 0; i < 2; ++i) {
        mask = src.u64[i];
        cs = (mask >> 1) & 1;
        if (cs == 1) {
            res->fa64[i] = vsrc.fa64[1];
        } else {
            res->fa64[i] = vsrc.fa64[0];
        }
    }
}
void vpermilpd_256a(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask = 0;

    for (i = 0; i < 2; ++i) {
        mask = src.u64[i];
        cs = (mask >> 1) & 1;
        if (cs == 1) {
            res->fa64[i] = vsrc.fa64[1];
        } else {
            res->fa64[i] = vsrc.fa64[0];
        }
    }
    for (i = 2; i < 4; ++i) {
        mask = src.u64[i];
        cs = (mask >> 1) & 1;
        if (cs == 1) {
            res->fa64[i] = vsrc.fa64[3];
        } else {
            res->fa64[i] = vsrc.fa64[2];
        }
    }

}

void vpermilpd_128b(XMM src, XMM *res, uint8_t imm) {
    int i;
    int cs;
    int mask = imm & 3;

    for (i = 0; i < 2; ++i) {
        cs = (mask >> i) & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[1];
        } else {
            res->fa64[i] = src.fa64[0];
        }
    }
}
void vpermilpd_256b(YMM src, YMM *res, uint8_t imm) {
    int i;
    int cs;
    int mask = imm & 15;

    for (i = 0; i < 2; ++i) {
        cs = (mask >> i) & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[1];
        } else {
            res->fa64[i] = src.fa64[0];
        }
    }
    for (i = 2; i < 4; ++i) {
        cs = (mask >> i) & 1;
        if (cs == 1) {
            res->fa64[i] = src.fa64[3];
        } else {
            res->fa64[i] = src.fa64[2];
        }
    }
}

void vpermilps_128a(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask = 0;

    for (i = 0; i < 4; ++i) {
        mask = src.u32[i];
        cs = mask & 3;
        res->fa32[i] = vsrc.fa32[cs];
    }
}
void vpermilps_256a(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask = 0;

    for (i = 0; i < 4; ++i) {
        mask = src.u32[i];
        cs = mask & 3;
        res->fa32[i] = vsrc.fa32[cs];
    }
    for (i = 4; i < 8; ++i) {
        mask = src.u32[i];
        cs = mask & 3;
        res->fa32[i] = vsrc.fa32[cs+4];
    }

}

void vpermilps_128b(XMM src, XMM *res, uint8_t imm) {
    int i;
    int cs;
    int rof = 0;

    for (i = 0; i < 4; ++i) {
        rof = i * 2;
        cs = (imm >> rof) & 3;

        res->fa32[i] = src.fa32[cs];
    }
}

void vpermilps_256b(YMM src, YMM *res, uint8_t imm) {
    int i;
    int cs;
    int rof = 0;

    for (i = 0; i < 4; ++i) {
        rof = i * 2;
        cs = (imm >> rof) & 3;

        res->fa32[i] = src.fa32[cs];
    }
    for (i = 4; i < 8; ++i) {
        rof = (i - 4) * 2;
        cs = (imm >> rof) & 3;

        res->fa32[i] = src.fa32[cs+4];
    }
}

void vpmaskmovd_load_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        } else {
            res->u32[i] = 0;
        }
    }
}
void vpmaskmovd_load_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        } else {
            res->u32[i] = 0;
        }
    }
}

void vpmaskmovq_load_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->u64[i] = src.u64[i];
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpmaskmovq_load_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->u64[i] = src.u64[i];
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpmaskmovd_store_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        }
    }
}
void vpmaskmovd_store_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint32_t mask_bit = 0;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            res->u32[i] = src.u32[i];
        }
    }
}

void vpmaskmovq_store_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->u64[i] = src.u64[i];
        }
    }
}

void vpmaskmovq_store_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int cs;
    uint64_t mask_bit = 0;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            res->u64[i] = src.u64[i];
        }
    }
}

void vpsllvd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint32_t ZeroExtend = 0;
    uint32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.u32[i];
        COUNT = src.u32[i];
        ZeroExtend = SRC1 << COUNT;
        res->u32[i] = ZeroExtend;
    }
}
void vpsllvd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint32_t ZeroExtend = 0;
    uint32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.u32[i];
        COUNT = src.u32[i];
        ZeroExtend = SRC1 << COUNT;
        res->u32[i] = ZeroExtend;
    }
}

void vpsllvq_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint64_t ZeroExtend = 0;
    uint64_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.u64[i];
        COUNT = src.u64[i];
        ZeroExtend = SRC1 << COUNT;
        res->u64[i] = ZeroExtend;
    }
}
void vpsllvq_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint64_t ZeroExtend = 0;
    uint64_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.u64[i];
        COUNT = src.u64[i];
        ZeroExtend = SRC1 << COUNT;
        res->u64[i] = ZeroExtend;
    }
}

void vpsravd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    int32_t SignExtend;
    int32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.a32[i];
        COUNT = src.a32[i];
        SignExtend = SRC1 << COUNT;
        res->a32[i] = SignExtend;
    }
}
void vpsravd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    int32_t SignExtend;
    int32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.a32[i];
        COUNT = src.a32[i];
        SignExtend = SRC1 >> COUNT;
        res->a32[i] = SignExtend;
    }
}

void vpsrlvd_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint32_t ZeroExtend = 0;
    uint32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.u32[i];
        COUNT = src.u32[i];
        ZeroExtend = SRC1 >> COUNT;
        res->u32[i] = ZeroExtend;
    }
}
void vpsrlvd_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint32_t ZeroExtend = 0;
    uint32_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 8; ++i) {
        SRC1 = vsrc.u32[i];
        COUNT = src.u32[i];
        ZeroExtend = SRC1 >> COUNT;
        res->u32[i] = ZeroExtend;
    }
}

void vpsrlvq_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    uint64_t ZeroExtend = 0;
    uint64_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 2; ++i) {
        SRC1 = vsrc.u64[i];
        COUNT = src.u64[i];
        ZeroExtend = SRC1 >> COUNT;
        res->u64[i] = ZeroExtend;
    }
}
void vpsrlvq_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    uint64_t ZeroExtend = 0;
    uint64_t SRC1 = 0, COUNT = 0;

    for (i = 0; i < 4; ++i) {
        SRC1 = vsrc.u64[i];
        COUNT = src.u64[i];
        ZeroExtend = SRC1 >> COUNT;
        res->u64[i] = ZeroExtend;
    }
}

void vtestps_128(XMM src, XMM dst, x86_saved_state_t *state) {
    int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
    XMM TEMP;
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

    TEMP.u128 = src.u128 & dst.u128;
    tmp0 = (TEMP.u32[0] >> 31) & 1;
    tmp1 = (TEMP.u32[1] >> 31) & 1;
    tmp2 = (TEMP.u32[2] >> 31) & 1;
    tmp3 = (TEMP.u32[3] >> 31) & 1;

    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0)) {
        //ZF = 1
        FLAGS = FLAGS | 0x0040;
    } else {
        //ZF = 0
        FLAGS = (FLAGS | 0x0040) ^ 0x0040;
    }
    TEMP.u128 = src.u128 & ~dst.u128;
    tmp0 = (TEMP.u32[0] >> 31) & 1;
    tmp1 = (TEMP.u32[1] >> 31) & 1;
    tmp2 = (TEMP.u32[2] >> 31) & 1;
    tmp3 = (TEMP.u32[3] >> 31) & 1;

    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0)) {
        //CF = 1
        FLAGS = FLAGS | 0x0001;
    } else {
        //CF = 0
        FLAGS = (FLAGS | 0x0001) ^ 0x0001;
    }
    //AF←OF←PF←SF←0
    FLAGS = (FLAGS | 0x0010) ^ 0x0010;
    FLAGS = (FLAGS | 0x0800) ^ 0x0800;
    FLAGS = (FLAGS | 0x0004) ^ 0x0004;
    FLAGS = (FLAGS | 0x0080) ^ 0x0080;

    if (is_saved_state64(state)) {
        RFLAGS = FLAGS;
        saved_state64(state)->isf.rflags = RFLAGS;
    } else {
        EFLAGS = FLAGS & 0xffffffff;
        saved_state32(state)->efl = EFLAGS;
    }
}
void vtestps_256(YMM src, YMM dst, x86_saved_state_t *state) {
    int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0, tmp6 = 0, tmp7 = 0;
    YMM TEMP;

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

    TEMP.u128[0] = src.u128[0] & dst.u128[0];
    TEMP.u128[1] = src.u128[1] & dst.u128[1];
    tmp0 = (TEMP.u32[0] >> 31) & 1;
    tmp1 = (TEMP.u32[1] >> 31) & 1;
    tmp2 = (TEMP.u32[2] >> 31) & 1;
    tmp3 = (TEMP.u32[3] >> 31) & 1;
    tmp4 = (TEMP.u32[4] >> 31) & 1;
    tmp5 = (TEMP.u32[5] >> 31) & 1;
    tmp6 = (TEMP.u32[6] >> 31) & 1;
    tmp7 = (TEMP.u32[7] >> 31) & 1;


    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0) && (tmp4 = 0) && (tmp5 = 0) && (tmp6 = 0) && (tmp7 = 0)) {
        //ZF = 1
        FLAGS = FLAGS | 0x0040;
    } else {
        //ZF = 0
        FLAGS = (FLAGS | 0x0040) ^ 0x0040;
    }

    TEMP.u128[0] = src.u128[0] & ~dst.u128[0];
    TEMP.u128[1] = src.u128[1] & ~dst.u128[1];
    tmp0 = (TEMP.u32[0] >> 31) & 1;
    tmp1 = (TEMP.u32[1] >> 31) & 1;
    tmp2 = (TEMP.u32[2] >> 31) & 1;
    tmp3 = (TEMP.u32[3] >> 31) & 1;
    tmp4 = (TEMP.u32[4] >> 31) & 1;
    tmp5 = (TEMP.u32[5] >> 31) & 1;
    tmp6 = (TEMP.u32[6] >> 31) & 1;
    tmp7 = (TEMP.u32[7] >> 31) & 1;

    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0) && (tmp4 = 0) && (tmp5 = 0) && (tmp6 = 0) && (tmp7 = 0)) {
        //CF = 1
        FLAGS = FLAGS | 0x0001;
    } else {
        //CF = 0
        FLAGS = (FLAGS | 0x0001) ^ 0x0001;
    }
    //AF←OF←PF←SF←0
    FLAGS = (FLAGS | 0x0010) ^ 0x0010;
    FLAGS = (FLAGS | 0x0800) ^ 0x0800;
    FLAGS = (FLAGS | 0x0004) ^ 0x0004;
    FLAGS = (FLAGS | 0x0080) ^ 0x0080;

    if (is_saved_state64(state)) {
        RFLAGS = FLAGS;
        saved_state64(state)->isf.rflags = RFLAGS;
    } else {
        EFLAGS = FLAGS & 0xffffffff;
        saved_state32(state)->efl = EFLAGS;
    }

}

void vtestpd_128(XMM src, XMM dst, x86_saved_state_t *state) {
    int tmp0 = 0, tmp1 = 0;
    XMM TEMP;
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

    TEMP.u128 = src.u128 & dst.u128;
    tmp0 = (TEMP.u64[0] >> 63) & 1;
    tmp1 = (TEMP.u64[1] >> 63) & 1;

    if ((tmp0 = 0) && (tmp1 = 0)) {
        //ZF = 1
        FLAGS = FLAGS | 0x0040;
    } else {
        //ZF = 0
        FLAGS = (FLAGS | 0x0040) ^ 0x0040;
    }
    TEMP.u128 = src.u128 & ~dst.u128;
    tmp0 = (TEMP.u64[0] >> 63) & 1;
    tmp1 = (TEMP.u64[1] >> 63) & 1;

    if ((tmp0 = 0) && (tmp1 = 0)) {
        //CF = 1
        FLAGS = FLAGS | 0x0001;
    } else {
        //CF = 0
        FLAGS = (FLAGS | 0x0001) ^ 0x0001;
    }
    //AF←OF←PF←SF←0
    FLAGS = (FLAGS | 0x0010) ^ 0x0010;
    FLAGS = (FLAGS | 0x0800) ^ 0x0800;
    FLAGS = (FLAGS | 0x0004) ^ 0x0004;
    FLAGS = (FLAGS | 0x0080) ^ 0x0080;

    if (is_saved_state64(state)) {
        RFLAGS = FLAGS;
        saved_state64(state)->isf.rflags = RFLAGS;
    } else {
        EFLAGS = FLAGS & 0xffffffff;
        saved_state32(state)->efl = EFLAGS;
    }
}
void vtestpd_256(YMM src, YMM dst, x86_saved_state_t *state) {
    int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;
    YMM TEMP;

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

    TEMP.u128[0] = src.u128[0] & dst.u128[0];
    TEMP.u128[1] = src.u128[1] & dst.u128[1];
    tmp0 = (TEMP.u64[0] >> 63) & 1;
    tmp1 = (TEMP.u64[1] >> 63) & 1;
    tmp2 = (TEMP.u64[2] >> 63) & 1;
    tmp3 = (TEMP.u64[3] >> 63) & 1;


    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0)) {
        //ZF = 1
        FLAGS = FLAGS | 0x0040;
    } else {
        //ZF = 0
        FLAGS = (FLAGS | 0x0040) ^ 0x0040;
    }

    TEMP.u128[0] = src.u128[0] & ~dst.u128[0];
    TEMP.u128[1] = src.u128[1] & ~dst.u128[1];
    tmp0 = (TEMP.u64[0] >> 63) & 1;
    tmp1 = (TEMP.u64[1] >> 63) & 1;
    tmp2 = (TEMP.u64[2] >> 63) & 1;
    tmp3 = (TEMP.u64[3] >> 63) & 1;

    if ((tmp0 = 0) && (tmp1 = 0) && (tmp2 = 0) && (tmp3 = 0)) {
        //CF = 1
        FLAGS = FLAGS | 0x0001;
    } else {
        //CF = 0
        FLAGS = (FLAGS | 0x0001) ^ 0x0001;
    }
    //AF←OF←PF←SF←0
    FLAGS = (FLAGS | 0x0010) ^ 0x0010;
    FLAGS = (FLAGS | 0x0800) ^ 0x0800;
    FLAGS = (FLAGS | 0x0004) ^ 0x0004;
    FLAGS = (FLAGS | 0x0080) ^ 0x0080;

    if (is_saved_state64(state)) {
        RFLAGS = FLAGS;
        saved_state64(state)->isf.rflags = RFLAGS;
    } else {
        EFLAGS = FLAGS & 0xffffffff;
        saved_state32(state)->efl = EFLAGS;
    }

}

void vperm2f128(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    YMM tmp;
    int imm1_0 = imm & 3;
    int imm5_4 = (imm >> 4) & 3;
    int imm3 = (imm >> 3) & 1;
    int imm7 = (imm >> 7) & 1;

    if (imm1_0 == 0) {
        tmp.u128[0] = vsrc.u128[0];
    } else if (imm1_0 == 1) {
        tmp.u128[0] = vsrc.u128[1];
    } else if (imm1_0 == 2) {
        tmp.u128[0] = src.u128[0];
    } else if (imm1_0 == 3) {
        tmp.u128[0] = src.u128[1];
    }

    if (imm5_4 == 0) {
        tmp.u128[1] = vsrc.u128[0];
    } else if (imm1_0 == 1) {
        tmp.u128[1] = vsrc.u128[1];
    } else if (imm1_0 == 2) {
        tmp.u128[1] = src.u128[0];
    } else if (imm1_0 == 3) {
        tmp.u128[1] = src.u128[1];
    }

    if (imm3 == 1) {
        tmp.u128[0] = 0;
    }
    if (imm7 == 1) {
        tmp.u128[1] = 0;
    }

    res->fa64[0] = tmp.fa64[0];
    res->fa64[1] = tmp.fa64[1];
    res->fa64[2] = tmp.fa64[2];
    res->fa64[3] = tmp.fa64[3];
}

void vperm2i128(YMM src, YMM vsrc, YMM *res, uint8_t imm) {
    int imm1_0 = imm & 3;
    int imm5_4 = (imm >> 4) & 3;
    int imm3 = (imm >> 3) & 1;
    int imm7 = (imm >> 7) & 1;

    if (imm1_0 == 0) {
        res->u128[0] = vsrc.u128[0];
    } else if (imm1_0 == 1) {
        res->u128[0] = vsrc.u128[1];
    } else if (imm1_0 == 2) {
        res->u128[0] = src.u128[0];
    } else if (imm1_0 == 3) {
        res->u128[0] = src.u128[1];
    }

    if (imm5_4 == 0) {
        res->u128[1] = vsrc.u128[0];
    } else if (imm1_0 == 1) {
        res->u128[1] = vsrc.u128[1];
    } else if (imm1_0 == 2) {
        res->u128[1] = src.u128[0];
    } else if (imm1_0 == 3) {
        res->u128[1] = src.u128[1];
    }

    if (imm3 == 1) {
        res->u128[0] = 0;
    }
    if (imm7 == 1) {
        res->u128[1] = 0;
    }
}

void vpermd(YMM src, YMM vsrc, YMM *res) {
    int i;
    int idx = 0;

    for (i = 0; i < 8; ++i) {
        idx = vsrc.u32[i] & 7;
        res->u32[i] = src.u32[idx];
    }
}

void vpermps(YMM src, YMM vsrc, YMM *res) {
    int i;
    int idx = 0;

    for (i = 0; i < 8; ++i) {
        idx = vsrc.u32[i] & 7;
        res->fa32[i] = src.fa32[idx];
    }
}

void vpermq(YMM src, YMM *res, uint8_t imm) {
    int i;
    int j = 0;
    int idx = 0;

    for (i = 0; i < 4; ++i) {
        j = i * 2;
        idx = (imm >> j) & 3;
        res->u64[i] = src.u64[idx];
    }
}

void vpermpd(YMM src, YMM *res, uint8_t imm) {
    int i;
    int j = 0;
    int idx = 0;

    for (i = 0; i < 4; ++i) {
        j = i * 2;
        idx = (imm >> j) & 3;
        res->fa64[i] = src.fa64[idx];
    }
}

void vzeroupper(x86_saved_state_t *state) {
    int i;
    int limit = 0;
    YMM TEMP;

    if (is_saved_state64(state)) {
        limit = 16;
    } else {
        limit = 8;
    }

    for (i = 0; i < limit; ++i) {
        _store_ymm(i, &TEMP);
        TEMP.u128[1] = 0;
        _load_ymm(i, &TEMP);
    }
}
void __vzeroall(x86_saved_state_t *state) {
    int i;
    int limit = 0;
    YMM TEMP;

    if (is_saved_state64(state)) {
        limit = 16;
    } else {
        limit = 8;
    }

    for (i = 0; i < limit; ++i) {
        _store_ymm(i, &TEMP);
        TEMP.u128[0] = 0;
        TEMP.u128[1] = 0;
        _load_ymm(i, &TEMP);
    }
}

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
                    int kernel_trap)
{
    uint8_t imm;
    uint8_t mod = *modrm >> 6; // ModRM.mod
    uint8_t num_dst = (*modrm >> 3) & 0x7;
    uint8_t num_src = *modrm & 0x7;

    if (high_reg) num_dst += 8;
    if (high_base) num_src += 8;

    uint64_t rmaddrs = 0;

    if (reg_size == 128) {
        XMM xmmsrc, xmmvsrc, xmmdst, xmmres;

        int consumed = get_consumed(modrm);
        imm = *((uint8_t*)&bytep[consumed]);
        ins_size += consumed;

        switch(opcode) {
        case 0x02: //vpblendd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpblendd_128(xmmsrc, xmmvsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x04: //vpermilps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilps_128b(xmmsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x05: //vpermilpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilpd_128b(xmmsrc, &xmmres, imm);
                        _load_xmm(num_dst, &xmmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x0C: //vpermilps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilps_128a(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x0D: //vpermilpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilpd_128a(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x0E: //vtestps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vtestps_128(xmmsrc, xmmdst, state);
                    }
                }
            }
            break;

        case 0x0F: //vtestpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vtestpd_128(xmmsrc, xmmdst, state);
                    }
                }
            }
            break;

        case 0x18: //vbroadcastss
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vbroadcastss_128(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x2C: //vmaskmovps SRC -> MASK -> DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vmaskmovps_load_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x2E: //vmaskmovps DST -> MASK -> SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        xmmres = xmmsrc;
                        vmaskmovps_store_128(xmmdst, xmmvsrc, &xmmres);
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x2D: //vmaskmovpd SRC -> MASK -> DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vmaskmovpd_load_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x2F: //vmaskmovpd DST -> MASK -> SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        xmmres = xmmsrc;
                        vmaskmovpd_store_128(xmmdst, xmmvsrc, &xmmres);
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x45:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsrlvd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsrlvd_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                    //vpsrlvq
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsrlvq_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x46:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsravd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsravd_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x47:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsllvd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsllvd_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                    //vpsllvq
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsllvq_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x78: //vpbroadcastb
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastb_128(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x79: //vpbroadcastw
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastw_128(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x58: //vpbroadcastd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastd_128(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x59: //vpbroadcastq
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastq_128(xmmsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x77: //vzeroupper
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) { //0F
                    vzeroupper(state);
                }
            }
            break;

        case 0x8C:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpmaskmovd SRC -> MASK -> DST
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpmaskmovd_load_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                    //vpmaskmovq SRC -> MASK -> DST
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpmaskmovq_load_128(xmmsrc, xmmvsrc, &xmmres);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
            break;

        case 0x8E:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpmaskmovd DST -> MASK -> SRC
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        xmmres = xmmsrc;
                        vpmaskmovd_store_128(xmmdst, xmmvsrc, &xmmres);
                        _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                    }
                    //vpmaskmovq DST -> MASK -> SRC
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &xmmvsrc, &xmmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        xmmres = xmmsrc;
                        vpmaskmovq_store_128(xmmdst, xmmvsrc, &xmmres);
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
        XMM xmmsrc, xmmres;

        int consumed = get_consumed(modrm);
        imm = *((uint8_t*)&bytep[consumed]);
        ins_size += consumed;

        switch(opcode) {
        case 0x00: //vpermq
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermq(ymmsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x01: //vpermpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermpd(ymmsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x02: //vpblendd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpblendd_256(ymmsrc, ymmvsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x04: //vpermilps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilps_256b(ymmsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x05: //vpermilpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilpd_256b(ymmsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x06: //vperm2f128
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vperm2f128(ymmsrc, ymmvsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x0C: //vpermilps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilps_256a(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x0D: //vpermilpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermilpd_256a(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x0E: //vtestps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vtestps_256(ymmsrc, ymmdst, state);
                    }
                }
            }
            break;

        case 0x0F: //vtestpd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vtestpd_256(ymmsrc, ymmdst, state);
                    }
                }
            }
            break;

        case 0x16: //vpermps
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermps(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x18:
            if (simd_prefix == 1) { //66
                //vbroadcastss
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vbroadcastss_256(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
                //vinsertf128
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vinsertf128(xmmsrc, ymmvsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x19:
            if (simd_prefix == 1) { //66
                //vbroadcastsd
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vbroadcastsd(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
                //vextractf128 DST256 -> SRC128
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vextractf128(ymmdst, &xmmres, imm);
                        if (mod == 3) {
                            _load_xmm(num_src, &xmmres);
                        } else {
                            uint16_t rm_size = reg_size / 2;
                            _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                        }
                        ins_size++;
                    }

                }
            }
            break;

        case 0x1A: //vbroadcastf128
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vbroadcastf128(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x2C: //vmaskmovps SRC -> MASK -> DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vmaskmovps_load_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x2E: //vmaskmovps DST -> MASK -> SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);
                        ymmres = ymmsrc;
                        vmaskmovps_store_256(ymmdst, ymmvsrc, &ymmres);
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x2D: //vmaskmovpd SRC -> MASK -> DST
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vmaskmovpd_load_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x2F: //vmaskmovpd DST -> MASK -> SRC
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);
                        ymmres = ymmsrc;
                        vmaskmovpd_store_256(ymmdst, ymmvsrc, &ymmres);
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                }
            }
            break;

        case 0x36: //vpermd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpermd(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x38:
            if (simd_prefix == 1) { //66
                //vinserti128
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vinserti128(xmmsrc, ymmvsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x39:
            if (simd_prefix == 1) { //66
                //vextracti128 DST256 -> SRC128
                if (leading_opcode == 3) { //0F3A
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vextracti128(ymmdst, &xmmres, imm);
                        if (mod == 3) {
                            _load_xmm(num_src, &xmmres);
                        } else {
                            uint16_t rm_size = reg_size / 2;
                            _load_maddr_from_xmm(rmaddrs, &xmmres, rm_size, state);
                        }
                        ins_size++;
                    }
                }
            }
            break;

        case 0x45:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsrlvd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsrlvd_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                    //vpsrlvq
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsrlvq_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x46:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsravd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsravd_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
                if (leading_opcode == 3) { //0F3A
                    //vpsravd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vperm2i128(ymmsrc, ymmvsrc, &ymmres, imm);
                        _load_ymm(num_dst, &ymmres);
                        ins_size++;
                    }
                }
            }
            break;

        case 0x47:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpsllvd
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsllvd_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                    //vpsllvq
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpsllvq_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x77: //vzeroall
            if (simd_prefix == 0) { //None
                if (leading_opcode == 1) { //0F
                    __vzeroall(state);
                }
            }
            break;

        case 0x78: //vpbroadcastb
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastb_256(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x79: //vpbroadcastw
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastw_256(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x58: //vpbroadcastd
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastd_256(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x59: //vpbroadcastq
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpbroadcastq_256(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x5A: //vbroadcasti128
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size / 2;
                        get_vexregs(modrm, high_reg, high_index, high_base, &xmmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vbroadcasti128(xmmsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x8C:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpmaskmovd SRC -> MASK -> DST
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpmaskmovd_load_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                    //vpmaskmovq SRC -> MASK -> DST
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);

                        vpmaskmovq_load_256(ymmsrc, ymmvsrc, &ymmres);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
            break;

        case 0x8E:
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) { //0F38
                    //vpmaskmovd DST -> MASK -> SRC
                    if (operand_size == 32) { //W0
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);
                        ymmres = ymmsrc;
                        vpmaskmovd_store_256(ymmdst, ymmvsrc, &ymmres);
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);
                    }
                    //vpmaskmovq DST -> MASK -> SRC
                    if (operand_size == 64) { //W1
                        uint16_t rm_size = reg_size;
                        get_vexregs(modrm, high_reg, high_index, high_base, &ymmsrc, &ymmvsrc, &ymmdst, vexreg, state, kernel_trap, reg_size, rm_size, modbyte, &rmaddrs);
                        ymmres = ymmsrc;
                        vpmaskmovq_store_256(ymmdst, ymmvsrc, &ymmres);
                        _load_maddr_from_ymm(rmaddrs, &ymmres, rm_size, state);

                    }
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
