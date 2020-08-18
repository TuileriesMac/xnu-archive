//
//  vgather.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/25.
//  Copyright © 2019 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vgather.h"

/**********************************************/
/**  AVX Gather instructions implementation  **/
/**********************************************/
// Integer Values
void vpgatherdq128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u64[i] = *(uint64_t*)&data_addr;
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpgatherdq256(YMM vsrc, XMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u64[i] = *(uint64_t*)&data_addr;
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpgatherdd128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint32_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u32[i] = *(uint32_t*)&data_addr;
        } else {
            res->u32[i] = 0;
        }
    }
}

void vpgatherdd256(YMM vsrc, YMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint32_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 8; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u32[i] = *(uint32_t*)&data_addr;
        } else {
            res->u32[i] = 0;
        }
    }
}

void vpgatherqq128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;

    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u64[i] = *(uint64_t*)&data_addr;
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpgatherqq256(YMM vsrc, YMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u64[i] = *(uint64_t*)&data_addr;
        } else {
            res->u64[i] = 0;
        }
    }
}

void vpgatherqd128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint32_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;

    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u32[i] = *(uint32_t*)&data_addr;
        } else {
            res->u32[i] = 0;
        }
    }
}

void vpgatherqd256(XMM vsrc, YMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint32_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;

    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            res->u32[i] = *(uint32_t*)&data_addr;
        } else {
            res->u32[i] = 0;
        }
    }
}

// Float Values
void vgatherdpd128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;
    XMM tmp;
    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u64[i] = *(uint64_t*)&data_addr;
        } else {
            tmp.u64[i] = 0;
        }
    }
    res->fa64[0] = tmp.fa64[0];
    res->fa64[1] = tmp.fa64[1];
}

void vgatherdpd256(YMM vsrc, XMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;
    YMM tmp;
    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u64[i] = *(uint64_t*)&data_addr;
        } else {
            tmp.u64[i] = 0;
        }
    }
    res->fa64[0] = tmp.fa64[0];
    res->fa64[1] = tmp.fa64[1];
    res->fa64[2] = tmp.fa64[2];
    res->fa64[3] = tmp.fa64[3];
}

void vgatherdps128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;
    XMM tmp;
    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u32[i] = *(uint32_t*)&data_addr;
        } else {
            tmp.u32[i] = 0;
        }
    }
    res->fa32[0] = tmp.fa32[0];
    res->fa32[1] = tmp.fa32[1];
    res->fa32[2] = tmp.fa32[3];
    res->fa32[3] = tmp.fa32[3];
}

void vgatherdps256(YMM vsrc, YMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;
    YMM tmp;
    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 8; ++i) {
        vaddr.a32[0] = vindex.a32[i];
        vaddr.a32[1] = 0xffffffff;
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u32[i] = *(uint32_t*)&data_addr;
        } else {
            tmp.u32[i] = 0;
        }
    }
    res->fa32[0] = tmp.fa32[0];
    res->fa32[1] = tmp.fa32[1];
    res->fa32[2] = tmp.fa32[3];
    res->fa32[3] = tmp.fa32[3];
    res->fa32[4] = tmp.fa32[4];
    res->fa32[5] = tmp.fa32[5];
    res->fa32[6] = tmp.fa32[6];
    res->fa32[7] = tmp.fa32[7];
}

void vgatherqpd128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;
    XMM tmp;
    for (i = 0; i < 2; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u64[i] = *(uint64_t*)&data_addr;
        } else {
            tmp.u64[i] = 0;
        }
    }
    res->fa64[0] = tmp.fa64[0];
    res->fa64[1] = tmp.fa64[1];
}

void vgatherqpd256(YMM vsrc, YMM vindex, YMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    YMM MASK;
    XMM vaddr;
    YMM tmp;
    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u64[i];
        cs = mask_bit >> 63 & 1;
        if (cs == 1) {
            MASK.u64[i] = 0xffffffffffffffff;
        } else {
            MASK.u64[i] = 0x0000000000000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u64[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u64[i] = *(uint64_t*)&data_addr;
        } else {
            tmp.u64[i] = 0;
        }
    }
    res->fa64[0] = tmp.fa64[0];
    res->fa64[1] = tmp.fa64[1];
    res->fa64[2] = tmp.fa64[2];
    res->fa64[3] = tmp.fa64[3];
}

void vgatherqps128(XMM vsrc, XMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;
    XMM tmp;
    for (i = 0; i < 4; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 2; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u32[i] = *(uint32_t*)&data_addr;
        } else {
            tmp.u32[i] = 0;
        }
    }
    res->fa32[0] = tmp.fa32[0];
    res->fa32[1] = tmp.fa32[1];
}

void vgatherqps256(XMM vsrc, YMM vindex, XMM *res, x86_saved_state_t *state, uint8_t *modrm, uint8_t high_base, uint8_t ins_size) {
    int i;
    int cs;
    uint64_t mask_bit = 0;
    uint64_t data_addr = 0;
    XMM MASK;
    XMM vaddr;
    XMM tmp;
    for (i = 0; i < 8; ++i) {
        mask_bit = vsrc.u32[i];
        cs = mask_bit >> 31 & 1;
        if (cs == 1) {
            MASK.u32[i] = 0xffffffff;
        } else {
            MASK.u32[i] = 0x00000000;
        }
    }

    for (i = 0; i < 4; ++i) {
        vaddr.a64[0] = vindex.a64[i];
        data_addr = vmaddrs(state, modrm, high_base, vaddr, ins_size);

        mask_bit = MASK.u32[i];
        cs = mask_bit & 1;
        if (cs == 1) {
            tmp.u32[i] = *(uint32_t*)&data_addr;
        } else {
            tmp.u32[i] = 0;
        }
    }
    res->fa32[0] = tmp.fa32[0];
    res->fa32[1] = tmp.fa32[1];
    res->fa32[2] = tmp.fa32[3];
    res->fa32[3] = tmp.fa32[3];
}

int vgather_instruction(x86_saved_state_t *state,
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

    //uint8_t imm;
    //uint8_t mod = *modrm >> 6; // ModRM.mod
    //uint8_t modreg = (*modrm >> 3) & 0x7;
    uint8_t num_dst = (*modrm >> 3) & 0x7;
    //uint8_t num_src = *modrm & 0x7;

    //get vindex regs
    uint8_t sib =  *((uint8_t*)&modrm[1]);
    uint8_t index = (sib >> 3) & 0x7; //SIB Index

    if (high_reg) num_dst += 8;
    //if (high_base) num_src += 8;
    if (high_index) index += 8;

    XMM xmmvsrc, xmmindex, xmmres;
    YMM ymmvsrc, ymmindex, ymmres;

    int consumed = get_consumed(modrm);
    ins_size += consumed;

    switch(opcode) {
    case 0x90:
        if (simd_prefix == 1) { //66
            if (leading_opcode == 2) { //0F38
                if (operand_size == 64) { //W1
                    if (reg_size == 128) { //VEX.128
                        //VPGATHERDQ 128 xmm1, vm32x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vpgatherdq128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);

                    } else { //VEX.256
                        //VPGATHERDQ 256 ymm1, vm32x, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_xmm(index, &xmmindex);
                        vpgatherdq256(ymmvsrc, xmmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                } else { //W0
                    if (reg_size == 128) { //VEX.128
                        //VPGATHERDD 128 xmm1, vm32x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vpgatherdd128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VPGATHERDD 256 ymm1, vm32y, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_ymm(index, &ymmindex);
                        vpgatherdd256(ymmvsrc, ymmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
        }
        break;

    case 0x91:
        if (simd_prefix == 1) { //66
            if (leading_opcode == 2) { //0F38
                if (operand_size == 64) { //W1
                    if (reg_size == 128) { //VEX.128
                        //VPGATHERQQ 128 xmm1, vm64x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vpgatherqq128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VPGATHERQQ 256 ymm1, vm64y, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_ymm(index, &ymmindex);
                        vpgatherqq256(ymmvsrc, ymmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                } else { //W0
                    if (reg_size == 128) { //VEX.128
                        //VPGATHERQD 128 xmm1, vm64x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vpgatherqd128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VPGATHERQD 256 xmm1, vm64y, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_ymm(index, &ymmindex);
                        vpgatherqd256(xmmvsrc, ymmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
        }
        break;

    case 0x92:
        if (simd_prefix == 1) { //66
            if (leading_opcode == 2) { //0F38
                if (operand_size == 64) { //W1
                    if (reg_size == 128) { //VEX.128
                        //VGATHERDPD 128 xmm1, vm32x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vgatherdpd128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VGATHERDPD 256 ymm1, vm32x, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_xmm(index, &xmmindex);
                        vgatherdpd256(ymmvsrc, xmmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                } else { //W0
                    if (reg_size == 128) { //VEX.128
                        //VGATHERDPS 128 xmm1, vm32x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vgatherdps128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VGATHERDPS 256 ymm1, vm32y, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_ymm(index, &ymmindex);
                        vgatherdps256(ymmvsrc, ymmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                }
            }
        }
        break;

    case 0x93:
        if (simd_prefix == 1) { //66
            if (leading_opcode == 2) { //0F38
                if (operand_size == 64) { //W1
                    if (reg_size == 128) { //VEX.128
                        //VGATHERQPD 128 xmm1, vm64x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vgatherqpd128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VGATHERQPD 256 ymm1, vm64y, ymm2
                        //_store_ymm(num_dst, &ymmdst);
                        _store_ymm(vexreg, &ymmvsrc);
                        _store_ymm(index, &ymmindex);
                        vgatherqpd256(ymmvsrc, ymmindex, &ymmres, state, modrm, high_base, ins_size);
                        _load_ymm(num_dst, &ymmres);
                    }
                } else { //W0
                    if (reg_size == 128) { //VEX.128
                        //VGATHERQPS 128 xmm1, vm64x, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_xmm(index, &xmmindex);
                        vgatherqps128(xmmvsrc, xmmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    } else { //VEX.256
                        //VGATHERQPS 256 xmm1, vm64y, xmm2
                        //_store_xmm(num_dst, &xmmdst);
                        _store_xmm(vexreg, &xmmvsrc);
                        _store_ymm(index, &ymmindex);
                        vgatherqps256(xmmvsrc, ymmindex, &xmmres, state, modrm, high_base, ins_size);
                        _load_xmm(num_dst, &xmmres);
                    }
                }
            }
        }
        break;

    default:
        return 0;
    }

    return ins_size;
}
