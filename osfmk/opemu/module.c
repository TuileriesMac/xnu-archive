//
//  module.c
//  OPEMU
//
//  Created by Meowthra on 2017/11/14.
//  Copyright © 2017年 Meowthra. All rights reserved.
//  Made in Taiwan.

#include "module.h"

//=======================================================================================//
int opemu_ktrap(x86_saved_state_t *state, uintptr_t *lo_spp)
{
    vm_offset_t addr;
    x86_saved_state64_t *regs;
    regs = saved_state64(state);
    addr = regs->isf.rip;
    uint8_t *code_buffer = (uint8_t*) addr;
    unsigned int bytes_skip = 0;
    uint64_t recovery_ip = 0;

    /*
    ==== START UDIS86 SECTION =====
    ud_t ud_obj;
    op_t op_obj;

    ud_init(&ud_obj);
    // ud_set_input_buffer(&ud_obj, code_stream, 15);
    ud_set_input_buffer(&ud_obj, code_buffer, sizeof(uint8_t));
    ud_set_mode(&ud_obj, 64);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);
    ud_set_vendor(&ud_obj, UD_VENDOR_ANY);

    bytes_skip = ud_disassemble(&ud_obj);
    ==== END UDIS86 SECTION =====
    */

    // "lock" instruction return
    if (code_buffer[0]==0xF0) {
        goto trap;
    }
    // "ud2" instruction return
    if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x0B) ) {
        goto trap;
    }

    //Enable REX Opcode Emulation
    bytes_skip = rex_ins(code_buffer, state, 1);

    //Enable VEX Opcode Emulation
    if (bytes_skip == 0) {
        bytes_skip = vex_ins(code_buffer, state, 1);
    }

    /* ==== START UDIS86 SECTION =====
    const uint32_t mnemonic = ud_insn_mnemonic(&ud_obj);
    // since this is ring0, it could be an invalid MSR read.
    // Instead of crashing the whole machine, report on it and keep running.
    if (mnemonic == UD_Irdmsr) {
      printf ("OpcodeEmulator: [RDMSR] unknown location 0x%016llx\r\n", regs->rcx);
      regs->rdx = regs->rax = 0;
    } else if (mnemonic == UD_Iwrmsr) {
      printf ("OpcodeEmulator: [WRMSR] unknown location 0x%016llx\r\n", regs->rcx);
    }

    op_obj.state = state;
    op_obj.state64 = saved_state;
    op_obj.state_flavor = SAVEDSTATE_64;
    op_obj.ud_obj = &ud_obj;
    op_obj.ring0 = 1;
    ==== END UDIS86 SECTION ===== */

    recovery_ip = (regs->isf.rip + bytes_skip);
    regs->isf.rip = recovery_ip;

    if (!bytes_skip)
    {
        printf("OpcodeEmulator invalid kernel opcode (64-bit): %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", code_buffer[0], code_buffer[1], code_buffer[2], code_buffer[3], code_buffer[4], code_buffer[5], code_buffer[6], code_buffer[7], code_buffer[8], code_buffer[9]);
        goto trap;
    }

    return 1;
trap:
    return 0;
}

void opemu_utrap(x86_saved_state_t *state)
{
    unsigned int bytes_skip = 0;

    if (is_saved_state64(state)) {
        vm_offset_t addr;
        x86_saved_state64_t *regs;
        regs = saved_state64(state);
        addr = regs->isf.rip;

        uint8_t *code_buffer = (uint8_t*) addr;
        uint64_t recovery_ip = 0;

        /*
        ==== START UDIS86 SECTION =====
        ud_t ud_obj;
        op_t op_obj;

        ud_init(&ud_obj);
        // ud_set_input_buffer(&ud_obj, code_stream, 15);
        ud_set_input_buffer(&ud_obj, code_buffer, sizeof(uint8_t));
        ud_set_mode(&ud_obj, 64);
        ud_set_syntax(&ud_obj, UD_SYN_INTEL);
        ud_set_vendor(&ud_obj, UD_VENDOR_ANY);

        bytes_skip = ud_disassemble(&ud_obj);
        ==== END UDIS86 SECTION =====
        */

        // "lock" instruction return
        if (code_buffer[0]==0xF0) {
            goto trap64;
        }
        // "ud2" instruction return
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x0B) ) {
            goto trap64;
        }

        /* ==== START NON-UDIS86-ADAPTED SECTION ===== */
        // sysenter
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x34) ) {
            regs->isf.rip = regs->rdx;
            regs->isf.rsp = regs->rcx;

            if ((signed int)regs->rax < 0) {
                mach_call_munger64(state);
            } else {
                unix_syscall64(state);
            }
            //return;
            thread_exception_return();
        }
        // sysexit
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x35) ) {
            regs->isf.rip = regs->rdx;
            regs->isf.rsp = regs->rcx;
            //return;
            thread_exception_return();
        }
        /* ==== END NON-UDIS86-ADAPTED SECTION ===== */

        //Enable REX Opcode Emulation
        bytes_skip = rex_ins(code_buffer, state, 0);

        //Enable VEX Opcode Emulation
        if (bytes_skip == 0) {
            bytes_skip = vex_ins(code_buffer, state, 0);
        }

        /*
        ==== START UDIS86 SECTION =====
        // It could be a sysenter instruction, which translates to a system call
        if (mnemonic == UD_Isysenter) {
              if (is_saved_state64(state))
              {
                  saved_state64(state)->isf.rip = saved_state64(state)->rdx;
                  saved_state64(state)->isf.rsp = saved_state64(state)->rcx;

                  if ((signed) saved_state64(state)->rax < 0) {
                      mach_call_munger64(state);
                  } else {
                      unix_syscall64(state);
                  }
              } else {
                  saved_state32(state)->eip = saved_state32(state)->edx;
                  saved_state32(state)->uesp = saved_state32(state)->ecx;

                  if ((signed) saved_state32(state)->eax < 0) {
                      mach_call_munger(state);
                  } else {
                      unix_syscall(state);
                  }
              }
        }

        // It could be a sysexit instruction, which translates to a specific return
          if (mnemonic == UD_Isysexit) {
              if (is_saved_state64(state))
              {
                  saved_state64(state)->isf.rip = saved_state64(state)->rdx;
                  saved_state64(state)->isf.rsp = saved_state64(state)->rcx;

                  thread_exception_return();
              } else {
                  saved_state32(state)->eip = saved_state32(state)->edx;
                  saved_state32(state)->uesp = saved_state32(state)->ecx;

                  thread_exception_return();
              }
          }

        // fill in the opemu object
        op_obj.state = state;
        op_obj.state64 = saved_state64(state);
        op_obj.state32 = saved_state32(state);
        op_obj.state_flavor = (is_saved_state64(state)) ? SAVEDSTATE_64 : SAVEDSTATE_32;
        op_obj.ud_obj = &ud_obj;
        op_obj.ring0 = 0;
        ==== END UDIS86 SECTION =====
        */
trap64:
        recovery_ip = (regs->isf.rip + bytes_skip);
        regs->isf.rip = recovery_ip;
        if (!bytes_skip) {
            printf("OpcodeEmulator invalid user opcode (64-bit): %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", code_buffer[0], code_buffer[1], code_buffer[2], code_buffer[3], code_buffer[4], code_buffer[5], code_buffer[6], code_buffer[7], code_buffer[8], code_buffer[9]);
        }
        thread_exception_return();
    } else {
        vm_offset_t addr;
        x86_saved_state32_t *regs;
        regs = saved_state32(state);
        addr = regs->eip;

        uint8_t *code_buffer = (uint8_t*) addr;
        uint64_t recovery_ip = 0;

        /*
        ==== START UDIS86 SECTION =====
        ud_t ud_obj;
        op_t op_obj;

        ud_init(&ud_obj);
        // ud_set_input_buffer(&ud_obj, code_stream, 15);
        ud_set_input_buffer(&ud_obj, code_buffer, sizeof(uint8_t));
        ud_set_mode(&ud_obj, 64);
        ud_set_syntax(&ud_obj, UD_SYN_INTEL);
        ud_set_vendor(&ud_obj, UD_VENDOR_ANY);

        bytes_skip = ud_disassemble(&ud_obj);
        ==== END UDIS86 SECTION =====
        */

        // "lock" instruction return
        if (code_buffer[0]==0xF0) {
            goto trap;
        }
        // "ud2" instruction return
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x0B) ) {
            goto trap;
        }

        // sysenter/sysexit for AMD Machines 32-bit Mode
        // sysenter
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x34) ) {
            regs->eip = regs->edx;
            regs->uesp = regs->ecx;

            if ((signed int)regs->eax < 0) {
                mach_call_munger(state);
            } else {
                unix_syscall(state);
            }
            //return;
            thread_exception_return();
        }
        // sysexit
        if ( (code_buffer[0]==0x0F) && (code_buffer[1]==0x35) ) {
            regs->eip = regs->edx;
            regs->uesp = regs->ecx;
            //return;
            thread_exception_return();
        }
        //Enable REX Opcode Emulation
        bytes_skip = rex_ins(code_buffer, state, 0);

        //Enable VEX Opcode Emulation
        if (bytes_skip == 0) {
            bytes_skip = vex_ins(code_buffer, state, 0);
        }

        /*
        ==== START UDIS86 SECTION =====
        // It could be a sysenter instruction, which translates to a system call
        if (mnemonic == UD_Isysenter) {
              if (is_saved_state64(state))
              {
                  saved_state64(state)->isf.rip = saved_state64(state)->rdx;
                  saved_state64(state)->isf.rsp = saved_state64(state)->rcx;

                  if ((signed) saved_state64(state)->rax < 0) {
                      mach_call_munger64(state);
                  } else {
                      unix_syscall64(state);
                  }
              } else {
                  saved_state32(state)->eip = saved_state32(state)->edx;
                  saved_state32(state)->uesp = saved_state32(state)->ecx;

                  if ((signed) saved_state32(state)->eax < 0) {
                      mach_call_munger(state);
                  } else {
                      unix_syscall(state);
                  }
              }
        }

        // It could be a sysexit instruction, which translates to a specific return
          if (mnemonic == UD_Isysexit) {
              if (is_saved_state64(state))
              {
                  saved_state64(state)->isf.rip = saved_state64(state)->rdx;
                  saved_state64(state)->isf.rsp = saved_state64(state)->rcx;

                  thread_exception_return();
              } else {
                  saved_state32(state)->eip = saved_state32(state)->edx;
                  saved_state32(state)->uesp = saved_state32(state)->ecx;

                  thread_exception_return();
              }
          }

        // fill in the opemu object
        op_obj.state = state;
        op_obj.state64 = saved_state64(state);
        op_obj.state32 = saved_state32(state);
        op_obj.state_flavor = (is_saved_state64(state)) ? SAVEDSTATE_64 : SAVEDSTATE_32;
        op_obj.ud_obj = &ud_obj;
        op_obj.ring0 = 0;
        ==== END UDIS86 SECTION =====
        */

trap:
        recovery_ip = (regs->eip + bytes_skip);
        regs->eip = recovery_ip;
        if (!bytes_skip) {
            printf("OpcodeEmulator invalid user opcode (32-bit): %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", code_buffer[0], code_buffer[1], code_buffer[2], code_buffer[3], code_buffer[4], code_buffer[5], code_buffer[6], code_buffer[7], code_buffer[8], code_buffer[9]);
        }
        thread_exception_return();
    }
    thread_exception_return();     // unreachable
    //return;
}
