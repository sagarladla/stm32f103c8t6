#include <isr.h>

extern void isr_reset(void);

void isr_default(void)
{
        asm ("mov r8, #0x01");
        while (1);
}

typedef void (*isr_t)(void);
static const isr_t __ivt[] __attribute__((used, section(".ivt"))) =
{
        (isr_t)&_stack,
        isr_reset,
        isr_nmi,
        isr_hardfault,
        isr_memmanage,
        isr_busfault,
        isr_usagefault,
        0,0,0,0,
        isr_svcall,
        isr_debugmonitor,
        0,
        isr_pendsv,
        isr_systick
};
