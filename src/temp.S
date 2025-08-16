.syntax unified
.cpu cortex-m3
.thumb

.section .isr_vector, "a", %progbits
.type   g_pfnVectors, %object
.size   g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
.word   _estack                 /* Initial Stack Pointer */
.word   Reset_Handler           /* Reset Handler */
.word   NMI_Handler             /* NMI Handler */
.word   HardFault_Handler       /* Hard Fault Handler */
.word   MemManage_Handler       /* MPU Fault Handler */
.word   BusFault_Handler        /* Bus Fault Handler */
.word   UsageFault_Handler      /* Usage Fault Handler */
.word   0                       /* Reserved */
.word   0                       /* Reserved */
.word   0                       /* Reserved */
.word   0                       /* Reserved */
.word   SVC_Handler             /* SVCall Handler */
.word   DebugMon_Handler        /* Debug Monitor Handler */
.word   0                       /* Reserved */
.word   PendSV_Handler          /* PendSV Handler */
.word   SysTick_Handler         /* SysTick Handler */

/* Add other IRQ handlers as needed... */

.section .text.Reset_Handler
.weak   Reset_Handler
.type   Reset_Handler, %function
Reset_Handler:
/* Set up stack pointer if necessary (already set by hardware) */

/* Set CONTROL register to unprivileged thread mode, use PSP */
/* CONTROL = 0x03: unprivileged, use PSP */
movs    r0, #3
msr     CONTROL, r0
isb

/* Optionally set PSP to a valid stack if needed */
/* ldr   r0, =_psp_stack_top
   msr   PSP, r0 */

/* Jump to kernel_init */
bl      kernel_init

/* If kernel_init returns, loop forever */
1:  b       1b

.size   Reset_Handler, .-Reset_Handler

/* Default handlers */
.section .text.Default_Handler,"ax",%progbits
.weak   NMI_Handler
.weak   HardFault_Handler
.weak   MemManage_Handler
.weak   BusFault_Handler
.weak   UsageFault_Handler
.weak   SVC_Handler
.weak   DebugMon_Handler
.weak   PendSV_Handler
.weak   SysTick_Handler

NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
b       .

.section .stack
.word   0x20005000              /* _estack: top of stack (adjust as needed) */

.extern kernel_init