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
#include <stdint.h>
#include <string.h>
#include <stm32f1x.h>

extern int main(void);
extern uint32_t _stack;


tcb_t thread_pool;
tcb_t *exec_queue;
tcb_t *curr_thread;
tcb_t *next_thread;

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
        data_section();
        bss_section();
        sys_init();

        main();
        while (1);
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

void set_pendsv_low_priority(void)
{
        SCB_SHPR3 |= (0xf0u << 16u);    // set PendSV low priority
}

void set_pendsv_pending(void)
{
        SCB_ICSR |= (0x01u << 28u);     // set pendsvset bit
}

void unset_pendsv_pending(void)
{
        SCB_ICSR |= (0x01u << 27u);     // set pendsvclr bit
}

void set_usage_bus_mm_fault_high_priority(void)
{
        SCB_SHPR1 |= (0x00u << 4u);     // set MemoryManagementFault high priority
        SCB_SHPR1 |= (0x00u << 12u);    // set BusFault high priority
        SCB_SHPR1 |= (0x00u << 20u);    // set UsageFault high priority
}

void config_irq(void)
{
        SCB_CCR |= (0x01u << 0u);       // set NONBASETHRDENA bit
        SCB_CCR |= (0x01u << 1u);       // set USERSETMPEND bit
        SCB_CCR &= ~(0x01u << 2u);      // unset RESERVED bit
        SCB_CCR |= (0x01u << 3u);       // set UNALIGN_TRP bit
        SCB_CCR |= (0x01u << 4u);       // set DIV_0_TRP bit
        SCB_CCR &= ~(0b111u << 5u);     // unset RESERVED bits
        SCB_CCR &= ~(0x01u << 8u);      // unset BFHFNMIGN bit
        SCB_CCR &= ~(0x01u << 9u);      // unset STKALIGN bit
        SCB_CCR &= (0x00000fffu);       // unset reserved bit
}

void setup_stk_tim(void)
{
        // Configure SysTick timer
        STK_LOAD = (SystemCoreClock / 1000) - 1; // 1ms tick
        STK_VAL = 0;
        STK_CTRL |= (1 << 0) | (1 << 1) | (1 << 2); // Enable SysTick
}

void create_thread(funcptr task)
{
        __disable_irq();
        unsigned int *sp;
        tcb_t *tasks = &thread_pool;
        return;
}
