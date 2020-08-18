//
//  opemu.h
//  OPEMU
//
//  Created by Meowthra on 2017/11/16.
//  Copyright © 2017年 Meowthra. All rights reserved.
//  Made in Taiwan.

#ifndef opemu_h
#define opemu_h

#include "module.h"

//SaturateToSignedByte
#define STSB(x) ((x > 127)? 127 : ((x < -128)? -128 : x) )
//SaturateToSignedWord
#define STSW(x) ((x > 32767)? 32767 : ((x < -32768)? -32768 : x) )
//SaturateToUnsignedByte
#define STUB(x) ((x > 255)? 255 : ((x < 0)? 0 : x) )
//SaturateToUnsignedWord
#define STUW(x) ((x > 65535)? 65535 : ((x < 0)? 0 : x) )

//Absolute value
#define ABS(x) ((x < 0)? -x : x )

// Get Bit field
#define bit(n)        (1ULL << (n))
#define bitmask(h,l)    ((bit(h)|(bit(h)-1)) & ~(bit(l)-1))
#define bitfield(x,h,l)    (((x) & bitmask(h,l)) >> l)
//for example:
//uint8_t XX = 0xAA;
//int xbit = bitfield(XX,7,0);

struct __int256_t {
    int64_t word[4];
};
typedef struct __int256_t __int256_t;

struct __uint256_t {
    uint64_t word[4];
};
typedef struct __uint256_t __uint256_t;

union __attribute__((__packed__)) YMM_u {
    int8_t a8[32];
    int16_t a16[16];
    int32_t a32[8];
    int64_t a64[4];
    __int128_t a128[2];
    __int256_t a256;

    uint8_t u8[32];
    uint16_t u16[16];
    uint32_t u32[8];
    uint64_t u64[4];
    __uint128_t u128[2];
    __uint256_t u256;
    double fa64[4];
    float fa32[8];
};

typedef union YMM_u YMM;

union __attribute__((__packed__)) XMM_u {
    int8_t a8[16];
    int16_t a16[8];
    int32_t a32[4];
    int64_t a64[2];
    __int128_t a128;
    uint8_t u8[16];
    uint16_t u16[8];
    uint32_t u32[4];
    uint64_t u64[2];
    __uint128_t u128;
    double fa64[2];
    float fa32[4];
};
typedef union XMM_u XMM;

union __attribute__((__packed__)) MM_u {
    int8_t a8[8];
    int16_t a16[4];
    int32_t a32[2];
    int64_t a64;
    uint8_t u8[8];
    uint16_t u16[4];
    uint32_t u32[2];
    uint64_t u64;
};
typedef union MM_u MM;


union __attribute__((__packed__)) M64_u {
    int8_t a8[8];
    int16_t a16[4];
    int32_t a32[2];
    int64_t a64;
    uint8_t u8[8];
    uint16_t u16[4];
    uint32_t u32[2];
    uint64_t u64;
};
typedef union M64_u M64;

union __attribute__((__packed__)) M32_u {
    int8_t a8[4];
    int16_t a16[2];
    int32_t a32;
    uint8_t u8[4];
    uint16_t u16[2];
    uint32_t u32;
};
typedef union M32_u M32;

/**************************
 * Virtual YMM Register
 *************************/
static YMM VYMM0;
static YMM VYMM1;
static YMM VYMM2;
static YMM VYMM3;
static YMM VYMM4;
static YMM VYMM5;
static YMM VYMM6;
static YMM VYMM7;
static YMM VYMM8;
static YMM VYMM9;
static YMM VYMM10;
static YMM VYMM11;
static YMM VYMM12;
static YMM VYMM13;
static YMM VYMM14;
static YMM VYMM15;

/** XNU TRAP HANDLERS **/
//unsigned char opemu_ktrap(x86_saved_state_t *state);
//void opemu_utrap(x86_saved_state_t *state);
//int ud_ins(uint8_t *code_buffer);
int rex_ins(uint8_t *instruction, x86_saved_state_t *state, int kernel_trap);
int vex_ins(uint8_t *instruction, x86_saved_state_t *state, int kernel_trap);

int get_consumed(uint8_t *ModRM);

void get_x64regs(uint8_t *modrm,
                 uint8_t high_reg,
                 uint8_t high_index,
                 uint8_t high_base,
                 void *src,
                 void *vsrc,
                 void *dst,
                 uint8_t vexreg,
                 x86_saved_state_t *saved_state,
                 int kernel_trap,
                 uint8_t modbyte,
                 uint64_t *rmaddrs);

void get_rexregs(uint8_t *modrm,
                 uint8_t high_reg,
                 uint8_t high_index,
                 uint8_t high_base,
                 void *src,
                 void *dst,
                 x86_saved_state_t *saved_state,
                 int kernel_trap,
                 uint16_t reg_size,
                 uint16_t rm_size,
                 uint8_t modbyte,
                 uint64_t *rmaddrs
                );

void get_vexregs(uint8_t *modrm,
                 uint8_t high_reg,
                 uint8_t high_index,
                 uint8_t high_base,
                 void *src,
                 void *vsrc,
                 void *dst,
                 uint8_t vexreg,
                 x86_saved_state_t *saved_state,
                 int kernel_trap,
                 uint16_t reg_size,
                 uint16_t rm_size,
                 uint8_t modbyte,
                 uint64_t *rmaddrs);

uint64_t addressing64(
    x86_saved_state_t *saved_state,
    uint8_t *modrm,
    uint8_t mod,
    uint8_t num_src,
    uint8_t high_index,
    uint8_t high_base,
    uint8_t modbyte,
    uint8_t bytelen);

uint32_t addressing32(
    x86_saved_state_t *saved_state,
    uint8_t *modrm,
    uint8_t mod,
    uint8_t num_src,
    uint8_t high_index,
    uint8_t high_base,
    uint8_t modbyte,
    uint8_t bytelen);

uint64_t vmaddrs(x86_saved_state_t *saved_state,
                 uint8_t *modrm,
                 uint8_t high_base,
                 XMM vaddr,
                 uint8_t ins_size
                );

#define storedqu_template(n, where)                 \
do {                                \
asm __volatile__ ("movdqu %%xmm" #n ", %0" : "=m" (*(where)));  \
} while (0);

#define loaddqu_template(n, where)                  \
do {                                \
asm __volatile__ ("movdqu %0, %%xmm" #n :: "m" (*(where))); \
} while (0);

#define storeq_template(n, where)                   \
do {                                \
asm __volatile__ ("movq %%mm" #n ", %0" : "=m" (*(where))); \
} while (0);

#define loadq_template(n, where)                    \
do {                                \
asm __volatile__ ("movq %0, %%mm" #n :: "m" (*(where)));    \
} while (0);

void _store_xmm (uint8_t n, XMM *where);
void _load_xmm (uint8_t n, XMM *where);
void _store_mmx (uint8_t n, MM *where);
void _load_mmx (uint8_t n, MM *where);
void _load_maddr_from_ymm (uint64_t rmaddrs, YMM *where, uint16_t rm_size, x86_saved_state_t *state);
void _load_maddr_from_xmm (uint64_t rmaddrs, XMM *where, uint16_t rm_size, x86_saved_state_t *state);
void _store_ymm (uint8_t n, YMM *where);
void _load_ymm (uint8_t n, YMM *where);
void _store_m64 (uint8_t n, M64 *where, x86_saved_state_t *state);
void _load_m64 (uint8_t n, M64 *where, x86_saved_state_t *state);
void _store_m32 (uint8_t n, M32 *where, x86_saved_state_t *state);
void _load_m32 (uint8_t n, M32 *where, x86_saved_state_t *state);

#endif /* opemu_h */
