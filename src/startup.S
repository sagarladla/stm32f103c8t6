#include <stdint.h>

extern void kernel_init(void);

/* Top of stack (adjust as needed) */
#define STACK_TOP 0x20005000

/* Vector table */
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
        (void (*)(void))STACK_TOP,   // Initial Stack Pointer
        Reset_Handler,               // Reset Handler
        NMI_Handler,                 // NMI Handler
        HardFault_Handler,           // Hard Fault Handler
        MemManage_Handler,           // MPU Fault Handler
        BusFault_Handler,            // Bus Fault Handler
        UsageFault_Handler,          // Usage Fault Handler
        0, 0, 0, 0,                  // Reserved
        SVC_Handler,                 // SVCall Handler
        DebugMon_Handler,            // Debug Monitor Handler
        0,                           // Reserved
        PendSV_Handler,              // PendSV Handler
        SysTick_Handler              // SysTick Handler
        // Add other IRQ handlers as needed...
};

/* Default handlers */
void NMI_Handler(void)             { while (1); }
void HardFault_Handler(void)       { while (1); }
void MemManage_Handler(void)       { while (1); }
void BusFault_Handler(void)        { while (1); }
void UsageFault_Handler(void)      { while (1); }
void SVC_Handler(void)             { while (1); }
void DebugMon_Handler(void)        { while (1); }
void PendSV_Handler(void)          { while (1); }
void SysTick_Handler(void)         { while (1); }

/* Reset handler */
void Reset_Handler(void) {
        /* Set CONTROL register: unprivileged, use PSP */
        __asm volatile (
                "movs r0, #3      \n"
                "msr CONTROL, r0  \n"
                "isb              \n"
        );

        /* Optionally set PSP to a valid stack if needed */
        // __asm volatile (
        //     "ldr r0, =_psp_stack_top \n"
        //     "msr PSP, r0             \n"
        // );

        kernel_init();

        while (1); // If kernel_init returns, loop forever
}
