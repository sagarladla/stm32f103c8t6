#include "os.h"

static tcb_t *current_tcb = NULL;

void __enable_irq(void)
{
        __asm volatile ("cpsie i");
}

void __disable_irq(void)
{
        __asm volatile ("cpsid i");
}

void sys_init(void)
{
        // Disable interrupts
        __disable_irq();

        // Configure the system clock
        clock_init();

        // Enable interrupts
        __enable_irq();
}

void create_thread(funcptr task)
{
        // Create a new thread
}
