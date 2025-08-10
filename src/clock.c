/**
 * 
 * @file: clock.c
 * @description: Clock configuration and management
 * @author: Sagarrajvarman Ladla
 * @note: This file contains functions to initialize and manage the system clock.
 * 
 */

#include <clock.h>
#include <stm32f1x.h>

// Default HSE/HSI clock frequency
static unsigned int SYSTEM_CLOCK = 8000000;

void sys_clock_init(void)
{
        // Enable HSE (High-Speed External) clock
        RCC_CR |= (0x01u << 16u); // set HSEON bit

        // Wait until HSE is ready
        while (!(RCC_CR & (0x01u << 17u))); // check HSERDY bit

        // Configure Flash prefetch and latency [72 MHz need 2 WS]
        FLASH_ACR |= 0b010; // set LATENCY to 2 wait states
        FLASH_ACR |= (0x01u << 4u); // set PRFTBE bit

        // Configure PLL
        RCC_CFGR &= ~(0x01u << 17u); // set PLLXTPRE bit to 0 [HSE clock not divided]
        RCC_CFGR |= (0x01u << 16u); // set PLLSRC to HSE
        RCC_CFGR |= (0b0111u << 18u); // set PLLMUL to 9

        // Configure AHB prescaler
        RCC_CFGR &= (0b0111u << 4u); // set AHB prescaler to 1 / SYSCLK not divided

        // Configure APB1 prescaler
        RCC_CFGR &= (0b100u << 8u); // set APB1 prescaler to 2 / HCLK divided by 2 [because APB1 should not exceed 36 MHz]

        // Configure APB2 prescaler
        RCC_CFGR &= (0b011u << 11u); // set APB2 prescaler to 1 / HCLK not divided

        // Enable PLL
        RCC_CR |= (0x01u << 24u); // set PLLON bit

        // Wait until PLL is ready
        while (!(RCC_CR & (0x01u << 25u))); // check PLLRDY bit

        // Set the system clock source (SYSCLK) to PLL
        RCC_CFGR |= (0b10 << 0u); // set SW bits to 10 [select PLL as SYSCLK source]

        // Wait until SYSCLK is ready
        while ((RCC_CFGR & (0b10 << 2u)) != (0b10 << 2u)); // check SWS bits not equal to 10 [PLL Source]
}

void periph_clock_init(void)
{
        // Enable peripheral clocks
        RCC_APB2ENR |= (0x01u << 4u); // Enable GPIOC clock
        RCC_APB1ENR |= (0x01u << 0u); // Enable TIM2 clock
}

void sys_clock_update(void)
{
        // Update the system clock frequency

        // TODO: modify later to read system clock from system itself,
        SYSTEM_CLOCK = 72000000; // Update with the current system clock frequency
}
unsigned int get_system_clock(void)
{
        return SYSTEM_CLOCK; // Return the current system clock frequency
}
