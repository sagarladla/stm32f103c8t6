#include <isr.h>

void isr_default(void)
{
        while (1);
}

void __enable_irq(void)
{
        __asm volatile ("cpsie i"); // Enable interrupts and configurable fault handlers [clear PRIMASK]
        __asm volatile ("cpsie f"); // Enable interrupts and fault handlers [clear FAULTMASK]
        // __asm volatile ("dsb");
        // __asm volatile ("isb");
}

void __disable_irq(void)
{
        __asm volatile ("cpsid i"); // Disable interrupts and configurable fault handlers [set PRIMASK]
        __asm volatile ("cpsid f"); // Disable interrupts and all fault handlers [set FAULTMASK]
        // __asm volatile ("dsb");
        // __asm volatile ("isb");
}

void __push_to_stack(void)
{
        __asm volatile ("push {r4-r11}");
}

void __pop_from_stack(void)
{
        __asm volatile ("pop {r4-r11}");
}

// void __set_pendsv_low_priority(void)
// {
//         SCB_SHPR3 |= (0xf0u << 16u);    // set PendSV low priority
// }

// void __set_pendsv_pending(void)
// {
//         SCB_ICSR |= (0x01u << 28u);     // set pendsvset bit
// }

// void __unset_pendsv_pending(void)
// {
//         SCB_ICSR |= (0x01u << 27u);     // set pendsvclr bit
// }

// void __set_usage_bus_mm_fault_high_priority(void)
// {
//         SCB_SHPR1 |= (0x00u << 4u);     // set MemoryManagementFault high priority
//         SCB_SHPR1 |= (0x00u << 12u);    // set BusFault high priority
//         SCB_SHPR1 |= (0x00u << 20u);    // set UsageFault high priority
// }

// void config_irq(void)
// {
//         SCB_CCR |= (0x01u << 0u);       // set NONBASETHRDENA bit
//         SCB_CCR |= (0x01u << 1u);       // set USERSETMPEND bit
//         SCB_CCR &= ~(0x01u << 2u);      // unset RESERVED bit
//         SCB_CCR |= (0x01u << 3u);       // set UNALIGN_TRP bit
//         SCB_CCR |= (0x01u << 4u);       // set DIV_0_TRP bit
//         SCB_CCR &= ~(0b111u << 5u);     // unset RESERVED bits
//         SCB_CCR &= ~(0x01u << 8u);      // unset BFHFNMIGN bit
//         SCB_CCR &= ~(0x01u << 9u);      // unset STKALIGN bit
//         SCB_CCR &= (0x00000fffu);       // unset reserved bit
// }

// void setup_stk_tim(void)
// {
//         // Configure SysTick timer
//         STK_LOAD = (SystemCoreClock / 1000) - 1; // 1ms tick
//         STK_VAL = 0;
//         STK_CTRL |= (0x01u << 0u) | (0x01u << 1u) | (0x01u << 2u); // Enable SysTick
// }
