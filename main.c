/**
 * @author:	Sagar Ladla [sagarladla@gmail.com]
 * @file:	main.c
 * @brief:	main entry file after bootloader startup or system reset.
*/

#include <stm32f1x.h>

__attribute__((constructor)) void before_main(void)
{
	while (1);
}

int main(void)
{
	GPIOC_ODR |= (1 << 13);
	__asm__("mov r8, #0x01");
	while (1)
	{
		/*
		GPIOC_BSRR |= (1 << 13);
		for (volatile uint32_t i = 0; i < 25000; i++);
		GPIOC_BSRR &= ~(1 << 13);
		for (volatile uint32_t i = 0; i < 25000; i++);*/
	}
	return 0;
}
