//
//  vsse42.c
//  OpcodeEmulator
//
//  Created by Kali on 2019/4/8.
//  Copyright © 2019年 lvs1974. All rights reserved.
//  Made in Taiwan.

#include "vsse42.h"

/**********************************************/
/**  VSSE4.2  instructions implementation    **/
/**********************************************/
void vpcmpgtq_128(XMM src, XMM vsrc, XMM *res) {
    int i;
    for (i = 0; i < 2; ++i) {
        if (vsrc.a64[i] > src.a64[i])
            res->u64[i] = 0xFFFFFFFFFFFFFFFF;
        else
            res->u64[i] = 0;
    }
}
void vpcmpgtq_256(YMM src, YMM vsrc, YMM *res) {
    int i;
    for (i = 0; i < 4; ++i) {
        if (vsrc.a64[i] > src.a64[i])
            res->u64[i] = 0xFFFFFFFFFFFFFFFF;
        else
            res->u64[i] = 0;
    }
}

/**********************************************/
/** SSE4.2 / VSSE4.2 Compare Strings         **/
/**********************************************/
void pcmpestrm(XMM src, XMM dst, uint8_t imm, x86_saved_state_t *state) {
    M64 RAX, RDX;
    M32 EAX, EDX;

    int la; //src length
    int lb; //dst length

    if (is_saved_state64(state)) {
        RAX.a64 = saved_state64(state)->rax;
        RDX.a64 = saved_state64(state)->rdx;
        la = RDX.u16[0];
        lb = RAX.u16[0];
    } else {
        EAX.a32 = saved_state32(state)->eax;
        EDX.a32 = saved_state32(state)->edx;
        la = EDX.u16[0];
        lb = EAX.u16[0];
    }

    int flags = 0;

    __int128_t a = src.a128;
    __int128_t b = dst.a128;
    __int128_t mask;
    mask = cmp_em(&a, la, &b, lb, imm, &flags);

    if (is_saved_state64(state)) {
        saved_state64(state)->isf.rflags &= ~ 0b100011010101;
        saved_state64(state)->isf.rflags |= flags;
    } else {
        saved_state32(state)->efl &= ~ 0b100011010101;
        saved_state32(state)->efl |= flags;
    }

    //load mask to xmm0
    XMM res;
    res.a128 = mask;
    asm __volatile__ ("movdqu %0, %%xmm0" :: "m" (res));
}

void pcmpestri(XMM src, XMM dst, uint8_t imm, x86_saved_state_t *state) {
    M64 RAX, RDX;
    M32 EAX, EDX;

    int la; //src length
    int lb; //dst length

    if (is_saved_state64(state)) {
        RAX.a64 = saved_state64(state)->rax;
        RDX.a64 = saved_state64(state)->rdx;
        la = RDX.u16[0];
        lb = RAX.u16[0];
    } else {
        EAX.a32 = saved_state32(state)->eax;
        EDX.a32 = saved_state32(state)->edx;
        la = EDX.u16[0];
        lb = EAX.u16[0];
    }

    int index = 0;
    int flags = 0;
    __int128_t a = src.a128;
    __int128_t b = dst.a128;
    index = cmp_ei(&a, la, &b, lb, imm, &flags);

    if (is_saved_state64(state)) {
        //load index to ecx/rcx
        saved_state64(state)->rcx = index;
        //set flags
        saved_state64(state)->isf.rflags &= ~ 0b100011010101;
        saved_state64(state)->isf.rflags |= flags;
    } else {
        //load index to ecx/rcx
        saved_state32(state)->ecx = index;
        //set flags
        saved_state32(state)->efl &= ~ 0b100011010101;
        saved_state32(state)->efl |= flags;
    }
}

void pcmpistrm(XMM src, XMM dst, uint8_t imm, x86_saved_state_t *state) {

    int flags = 0;
    __int128_t a = src.a128;
    __int128_t b = dst.a128;
    __int128_t mask;
    mask = cmp_im(&a, &b, imm, &flags);

    if (is_saved_state64(state)) {
        saved_state64(state)->isf.rflags &= ~ 0b100011010101;
        saved_state64(state)->isf.rflags |= flags;
    } else {
        saved_state32(state)->efl &= ~ 0b100011010101;
        saved_state32(state)->efl |= flags;
    }

    //load mask to xmm0
    XMM res;
    res.a128 = mask;
    asm __volatile__ ("movdqu %0, %%xmm0" :: "m" (res));
}

void pcmpistri(XMM src, XMM dst, uint8_t imm, x86_saved_state_t *state) {

    int index = 0;
    int flags = 0;
    __int128_t a = src.a128;
    __int128_t b = dst.a128;
    index = cmp_ii(&a, &b, imm, &flags);

    if (is_saved_state64(state)) {
        //load index to ecx/rcx
        saved_state64(state)->rcx = index;
        //set flags
        saved_state64(state)->isf.rflags &= ~ 0b100011010101;
        saved_state64(state)->isf.rflags |= flags;
    } else {
        //load index to ecx/rcx
        saved_state32(state)->ecx = index;
        //set flags
        saved_state32(state)->efl &= ~ 0b100011010101;
        saved_state32(state)->efl |= flags;
    }
}

int vsse42_instruction(x86_saved_state_t *state,
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
        case 0x37:
            //VPCMPGTQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpcmpgtq_128(xmmsrc, xmmvsrc, &xmmres);
                    _load_xmm(num_dst, &xmmres);
                }
            }
            break;

        case 0x60:
            //VPCMPESTRM
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    pcmpestrm(xmmsrc, xmmdst, imm, state);
                    ins_size++;
                }
            }
            break;
        case 0x61:
            //VPCMPESTRI
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    pcmpestri(xmmsrc, xmmdst, imm, state);
                    ins_size++;
                }
            }
            break;
        case 0x62:
            //VPCMPISTRM
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    pcmpistrm(xmmsrc, xmmdst, imm, state);
                    ins_size++;
                }
            }
            break;
        case 0x63:
            //VPCMPISTRI
            if (simd_prefix == 1) { //66
                if (leading_opcode == 3) {//0F3A
                    pcmpistri(xmmsrc, xmmdst, imm, state);
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
        case 0x37:
            //VPCMPGTQ
            if (simd_prefix == 1) { //66
                if (leading_opcode == 2) {//0F38
                    vpcmpgtq_256(ymmsrc, ymmvsrc, &ymmres);
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
