#ifndef _XCPM_INTERNAL_H_
#define _XCPM_INTERNAL_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>

extern boolean_t xcpm_is_hwp_enabled(void);

extern void xcpm_mbox_lock(void);
extern void xcpm_mbox_unlock(void);

extern uint32_t xcpm_bios_mbox_cmd_read(uint32_t a);
extern uint32_t xcpm_bios_mbox_cmd_unsafe_read(uint32_t a);
extern void xcpm_bios_mbox_cmd_write(uint32_t a, uint32_t b);

#endif /* _XCPM_INTERNAL_H_ */
