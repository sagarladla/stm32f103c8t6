/**
 * @target:	armv7-m3
 * @author:	Sagar Ladla [sagarladla@gmail.com]
 * @file:	startup.c
 * @brief:	STM32F103C8T6 microcontroller startup file.
 * 		This program executes:
 * 			- set the initial SP
 * 			- set initial PC == Reset_Handler
 * 			- set the vector table entries with ISR address
 * 			- configure the system clock
 * 			- branch to main in the C library
 * 		After RESET, the Cortex-M3 microcontroller is in Thread mode,
 * 		priority is privileged, and the STACK is set to main()
*/

#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (20U * 1024U) // 20KB
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

/* function prototypes of STM32F103C8T6 medium density system exception and irq handlers */

void Reset_Handler(void);
void NMI_Handler(void)			__attribute__((weak, alias ("default_handler")));
void HardFault_Handler(void)		__attribute__((weak, alias ("default_handler")));
void MemManage_Handler(void)		__attribute__((weak, alias ("default_handler")));
void BusFault_Handler(void)		__attribute__((weak, alias ("default_handler")));
void UsageFault_Handler(void)		__attribute__((weak, alias ("default_handler")));
void SVCall_Handler(void)		__attribute__((weak, alias ("default_handler")));
void DebugMonitor_Handler(void)		__attribute__((weak, alias ("default_handler")));
void PendSV_Handler(void)		__attribute__((weak, alias ("default_handler")));
void SysTick_Handler(void)		__attribute__((weak, alias ("default_handler")));
void WWDG_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void PVD_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TAMPER_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void RTC_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void FLASH_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void RCC_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI0_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI1_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI2_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI3_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI4_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void DMA1_Channel1_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel2_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel3_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel4_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel5_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel6_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA1_Channel7_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void ADC1_2_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void USB_HP_CAN_TX_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void USB_LP_CAN_RX0_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void CAN_RX1_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void CAN_SCE_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI9_5_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM1_BRK_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM1_UP_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM1_TRG_COM_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void TIM1_CC_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM2_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM3_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM4_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void I2C1_EV_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void I2C1_ER_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void I2C2_EV_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void I2C2_ER_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void SPI1_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void SPI2_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void USART1_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void USART2_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void USART3_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void EXTI15_10_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void RTCAlarm_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void USBWakeup_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM8_BRK_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM8_UP_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM8_TRG_COM_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void TIM8_CC_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void ADC3_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void FSMC_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void SDIO_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM5_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void SPI3_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void UART4_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void UART5_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM6_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void TIM7_IRQHandler(void)		__attribute__((weak, alias ("default_handler")));
void DMA2_Channel1_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA2_Channel2_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA2_Channel3_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));
void DMA2_Channel4_5_IRQHandler(void)	__attribute__((weak, alias ("default_handler")));

uint32_t __vector_table[]		__attribute__((section (".isr_vector"))) = {
	STACK_START,
	(uint32_t)&Reset_Handler,
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	(uint32_t)&MemManage_Handler,
	(uint32_t)&BusFault_Handler,
	(uint32_t)&UsageFault_Handler,
	0,
	0,
	0,
	0,
	(uint32_t)&SVCall_Handler,
	(uint32_t)&DebugMonitor_Handler,
	0,
	(uint32_t)&PendSV_Handler,
	(uint32_t)&SysTick_Handler,
	(uint32_t)&WWDG_IRQHandler,
	(uint32_t)&PVD_IRQHandler,
	(uint32_t)&TAMPER_IRQHandler,
	(uint32_t)&RTC_IRQHandler,
	(uint32_t)&FLASH_IRQHandler,
	(uint32_t)&RCC_IRQHandler,
	(uint32_t)&EXTI0_IRQHandler,
	(uint32_t)&EXTI1_IRQHandler,
	(uint32_t)&EXTI2_IRQHandler,
	(uint32_t)&EXTI3_IRQHandler,
	(uint32_t)&EXTI4_IRQHandler,
	(uint32_t)&DMA1_Channel1_IRQHandler,
	(uint32_t)&DMA1_Channel2_IRQHandler,
	(uint32_t)&DMA1_Channel3_IRQHandler,
	(uint32_t)&DMA1_Channel4_IRQHandler,
	(uint32_t)&DMA1_Channel5_IRQHandler,
	(uint32_t)&DMA1_Channel6_IRQHandler,
	(uint32_t)&DMA1_Channel7_IRQHandler,
	(uint32_t)&ADC1_2_IRQHandler,
	(uint32_t)&USB_HP_CAN_TX_IRQHandler,
	(uint32_t)&USB_LP_CAN_RX0_IRQHandler,
	(uint32_t)&CAN_RX1_IRQHandler,
	(uint32_t)&CAN_SCE_IRQHandler,
	(uint32_t)&EXTI9_5_IRQHandler,
	(uint32_t)&TIM1_BRK_IRQHandler,
	(uint32_t)&TIM1_UP_IRQHandler,
	(uint32_t)&TIM1_TRG_COM_IRQHandler,
	(uint32_t)&TIM1_CC_IRQHandler,
	(uint32_t)&TIM2_IRQHandler,
	(uint32_t)&TIM3_IRQHandler,
	(uint32_t)&TIM4_IRQHandler,
	(uint32_t)&I2C1_EV_IRQHandler,
	(uint32_t)&I2C1_ER_IRQHandler,
	(uint32_t)&I2C2_EV_IRQHandler,
	(uint32_t)&I2C2_ER_IRQHandler,
	(uint32_t)&SPI1_IRQHandler,
	(uint32_t)&SPI2_IRQHandler,
	(uint32_t)&USART1_IRQHandler,
	(uint32_t)&USART2_IRQHandler,
	(uint32_t)&USART3_IRQHandler,
	(uint32_t)&EXTI15_10_IRQHandler,
	(uint32_t)&RTCAlarm_IRQHandler,
	(uint32_t)&USBWakeup_IRQHandler,
	(uint32_t)&TIM8_BRK_IRQHandler,
	(uint32_t)&TIM8_UP_IRQHandler,
	(uint32_t)&TIM8_TRG_COM_IRQHandler,
	(uint32_t)&TIM8_CC_IRQHandler,
	(uint32_t)&ADC3_IRQHandler,
	(uint32_t)&FSMC_IRQHandler,
	(uint32_t)&SDIO_IRQHandler,
	(uint32_t)&TIM5_IRQHandler,
	(uint32_t)&SPI3_IRQHandler,
	(uint32_t)&UART4_IRQHandler,
	(uint32_t)&UART5_IRQHandler,
	(uint32_t)&TIM6_IRQHandler,
	(uint32_t)&TIM7_IRQHandler,
	(uint32_t)&DMA2_Channel1_IRQHandler,
	(uint32_t)&DMA2_Channel2_IRQHandler,
	(uint32_t)&DMA2_Channel3_IRQHandler,
	(uint32_t)&DMA2_Channel4_5_IRQHandler,
};

void default_handler(void)
{
	while(1);
}

void Reset_Handler(void)
{
	/* copy .data section to SRAM */
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	uint8_t *src = (uint8_t*)&_etext;
	uint8_t *dst = (uint8_t*)&_sdata;
	while (size--)
	{
		*dst++ = *src++;
	}
	/* init .bss section to zero */
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	dst = (uint8_t*)&_sbss;
	while (size--)
	{
		*dst++ = 0x00;
	}
	/* call main() */
	main();
}
