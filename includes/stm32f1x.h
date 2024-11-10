#pragma once

#define RCC_BASE_ADDR		0x40021000
#define RCC_RC			(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x00))
#define RCC_CFGR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x04))
#define RCC_CIR			(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x08))
#define RCC_APB2RSTR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x0c))
#define RCC_APB1RSTR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x10))
#define RCC_AHBENR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x14))
#define RCC_APB2ENR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x18))
#define RCC_APB1ENR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x1c))
#define RCC_BDCR		(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x20))
#define RCC_CSR			(*(volatile unsigned int *)(RCC_BASE_ADDR + 0x24))

#define GPIOA_BASE_ADDR		0x40010800
#define GPIOA_CRL		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x00))
#define GPIOA_CRH		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x04))
#define GPIOA_IDR		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x08))
#define GPIOA_ODR		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x0c))
#define GPIOA_BSRR		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x10))
#define GPIOA_BRR		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x14))
#define GPIOA_LCKR		(*(volatile unsigned int *)(GPIOA_BASE_ADDR + 0x18))

#define GPIOB_BASE_ADDR		0x40010c00
#define GPIOB_CRL		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x00))
#define GPIOB_CRH		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x04))
#define GPIOB_IDR		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x08))
#define GPIOB_ODR		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x0c))
#define GPIOB_BSRR		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x10))
#define GPIOB_BRR		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x14))
#define GPIOB_LCKR		(*(volatile unsigned int *)(GPIOB_BASE_ADDR + 0x18))

#define GPIOC_BASE_ADDR		0x40011000
#define GPIOC_CRL		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x00))
#define GPIOC_CRH		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x04))
#define GPIOC_IDR		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x08))
#define GPIOC_ODR		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x0c))
#define GPIOC_BSRR		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x10))
#define GPIOC_BRR		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x14))
#define GPIOC_LCKR		(*(volatile unsigned int *)(GPIOC_BASE_ADDR + 0x18))

#define GPIOD_BASE_ADDR		0x40011400
#define GPIOD_CRL		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x00))
#define GPIOD_CRH		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x04))
#define GPIOD_IDR		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x08))
#define GPIOD_ODR		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x0c))
#define GPIOD_BSRR		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x10))
#define GPIOD_BRR		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x14))
#define GPIOD_LCKR		(*(volatile unsigned int *)(GPIOD_BASE_ADDR + 0x18))

#define GPIOE_BASE_ADDR		0x40011800
#define GPIOE_CRL		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x00))
#define GPIOE_CRH		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x04))
#define GPIOE_IDR		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x08))
#define GPIOE_ODR		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x0c))
#define GPIOE_BSRR		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x10))
#define GPIOE_BRR		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x14))
#define GPIOE_LCKR		(*(volatile unsigned int *)(GPIOE_BASE_ADDR + 0x18))

#define GPIOF_BASE_ADDR		0x40011c00
#define GPIOF_CRL		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x00))
#define GPIOF_CRH		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x04))
#define GPIOF_IDR		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x08))
#define GPIOF_ODR		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x0c))
#define GPIOF_BSRR		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x10))
#define GPIOF_BRR		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x14))
#define GPIOF_LCKR		(*(volatile unsigned int *)(GPIOF_BASE_ADDR + 0x18))

#define GPIOG_BASE_ADDR		0x40012000
#define GPIOG_CRL		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x00))
#define GPIOG_CRH		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x04))
#define GPIOG_IDR		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x08))
#define GPIOG_ODR		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x0c))
#define GPIOG_BSRR		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x10))
#define GPIOG_BRR		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x14))
#define GPIOG_LCKR		(*(volatile unsigned int *)(GPIOG_BASE_ADDR + 0x18))
