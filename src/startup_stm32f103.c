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

#include <os.h>
#include <isr.h>
#include <stm32f1x.h>

extern int main(void);
extern void __libc_init_array(void);
extern unsigned int _stack;
extern unsigned int _idata;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;


tcb_t thread_pool;
tcb_t *exec_queue;
tcb_t *curr_thread;
tcb_t *next_thread;

// copy data section
void data_section(void)
{
        unsigned int *src_data = &_idata;
        unsigned int *dst_data = &_data;
        while (dst_data < &_edata)
                *dst_data++ = *src_data++;
        return;
}

// clear bss section
void bss_section(void)
{
        unsigned int *bss = &_bss;
        while (bss < &_ebss)
                *bss++ = 0x00;
        return;
}

/**
 * System Hardware Initialization
 * @brief configure system clock, set up peripherals, memory,  */ 
void sys_init(void)
{
        // check if high speed internal clock is ready
        if ((RCC_CR >> 1) == 1)
        {
                // HSI clock enable
                RCC_CR |= 0x01;
        }
        // check if high speed external clock is ready
        else if ((RCC_CR >> 17) == 1)
        {
                // HSE clock enable
                RCC_CR |= (1 << 16);
        }
        return;
}


void _init(void) {}

__attribute__((naked, noreturn)) void isr_reset(void)
{
        data_section();
        bss_section();
        // __libc_init_array();
        main();

        while (1);
}

typedef void (*isr_t)(void);
static const isr_t __ivt[]	__attribute__((used, section(".ivt"))) =
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

void isr_default(void)
{
        asm ("mov r8, #0x01");
        while (1);
}

void intr_en(void)
{
        asm ("CPSIE I");
}

void intr_di(void)
{
        asm ("CPSID I");
}

void create_thread(funcptr task)
{
        intr_di();
        unsigned int *sp;
        tcb_t *tasks = &thread_pool;
        return;
}
