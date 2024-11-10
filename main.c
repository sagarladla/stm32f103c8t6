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

// led on stm32f103c8t6 is connected to PC13 pin
void set_led_gpio(void)
{
	// GPIOC port clock enable
	RCC_APB2ENR |= (1 << 4);

	// set up CNF13 bits as general purpose output push pull mode
	GPIOC_CRH &= ~(1 << 23);
	GPIOC_CRH &= ~(1 << 22);

	// set up MODE13 bits for max 2 MHz output speed
	GPIOC_CRH &= ~(1 << 21);
	GPIOC_CRH |= (1 << 20);
}

void delay()
{
	int i = 100000;
	int j = 100000;
	while (i--)
		__asm__("nop");
	while (j--)
		__asm__("nop");
	return;
}

int main(void)
{
	set_led_gpio();
	__asm__("mov r8, #0x01");
	while (1)
	{
		GPIOC_ODR &= ~(1 << 13);
		delay();
		GPIOC_ODR |= (1 << 13);
		delay();
	}
	return 0;
}
