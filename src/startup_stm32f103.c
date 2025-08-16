/**
 * @target:     armv7-m3
 * @author:     Sagarvarman Ladla [sagarladla@gmail.com]
 * @file:       startup_stm32f103.c
 * @brief:      STM32F103C8T6 microcontroller startup file.
 *              This program executes:
 *                      - set the vector table entries with ISR address
 *                      - set the initial MSP
 *                      - set initial PC == irq_reset
 *                      - configure the system clock, peripherals and memory
 *                      - configure C runtime
 *                      - branch to main in the C library
 *              After RESET, the Cortex-M3 microcontroller is in Thread mode,
 *              priority is privileged, and the STACK is set to main()
 */

#include <isr.h>
#include <clock.h>
#include <stdint.h>
#include <string.h>
#include <stm32f1x.h>

extern int main(void);
extern uint32_t _estack;

// copy data section
void data_section(void)
{
        extern uint32_t _data;
        extern uint32_t _idata;
        extern uint32_t _edata;
        memcpy(&_data, &_idata, (size_t)(&_edata - &_data));
        return;
}

// clear bss section
void bss_section(void)
{
        extern uint32_t _bss;
        extern uint32_t _ebss;
        memset(&_bss, 0x00, (size_t)(&_ebss - &_bss));
        return;
}

__attribute__((naked, noreturn)) void isr_reset(void)
{
        // __disable_irq();

        data_section();
        bss_section();
        
        sys_clock_init();
        periph_clock_init();

        // __enable_irq();
        
        main();
        
        while (1);
}

void isr_default(void)
{
        while (1);
}

typedef void (*isr_t)(void);
static const isr_t __ivt[] __attribute__((used, section(".ivt"))) =
{
        (isr_t)&_estack,
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
