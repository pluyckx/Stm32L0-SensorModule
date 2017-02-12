/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32l0xx.h"

int main(void) {
	/* select HSI */
	RCC->CR |= 0b100001;

	/* wait for HSI */
	while ((RCC->CR & 0b100) == 0) {

	}

	/* Select HSI as sysclock*/
	RCC->CFGR |= 0b01;

	/* Enable SysClk */
	RCC->APB2ENR = (RCC->APB2ENR & ~0x1) | 0x1;

	HAL_InitTick(0);
	HAL_NVIC_EnableIRQ(SysTick_IRQn);

	/* Enable GPIOA and GPIOB */
	RCC->IOPENR |= 0b11;

	/* init port A: LED */
	{
		constexpr uint32_t pin15 = 15u;
		constexpr uint32_t pin8 = 8u;
		constexpr uint32_t mask = (0b11 << (pin15 * 2u))
				| (0b11 << (pin8 * 2u));

		uint32_t tmp;

		tmp = GPIOA->OTYPER & ~((0b1 << pin15) | (0b1 << pin8));
		tmp |= (0b1 << pin15) | (0b1 << pin8);
		GPIOA->OTYPER = tmp;

		GPIOA->ODR |= 1 << pin8;

		tmp = GPIOA->MODER & ~mask;
		tmp |= (0b01 << (pin15 * 2u)) | (0b01 << (pin8 * 2u));
		GPIOA->MODER = tmp;

		GPIOA->ODR &= ~(1 << pin8);
	}

	/* init port B: I2C */
	{
		constexpr uint32_t pin6 = 6u;
		constexpr uint32_t pin7 = 7u;
		constexpr uint32_t mask = (0b11 << (pin6 * 2u)) | (0b11 << (pin7 * 2u));
		constexpr uint32_t maskAF = 0b11111111 << 24;

		uint32_t tmp;

		tmp = GPIOB->OTYPER & ~((0b1 << pin6) | (0b1 << pin7));
		tmp |= (0b1 << pin6) | (0b1 << pin7);
		GPIOB->OTYPER = tmp;

		GPIOB->OSPEEDR = (0b11 << (pin6*2)) | (0b11 << (pin7*2));

		tmp = GPIOB->MODER & ~mask;
		tmp |= (0b10 << (pin6 * 2u)) | (0b10 << (pin7 * 2u));
		GPIOB->MODER = tmp;

		tmp = GPIOB->AFR[1] & ~maskAF;
		tmp |= 0b00010001 << 24;
		GPIOB->AFR[0] = tmp;
	}

	/* Init I2C */
	{
		RCC->APB1ENR |= 1 << 21; // enable clock
		RCC->CCIPR |= 0b01 << 12; // select system clock for I2C
		I2C1->TIMINGR = (3 << 28) | (0x4 << 20) | (0x02 << 16) | (0xC3 << 8)
				| (0xC7 << 0);

		/*I2C1->TIMINGR = (3 << 28) | (0x4 << 20) | (0x02 << 16) | (0xF << 8)
						| (0x13 << 0);*/

		// 10kHz
		// presc 28   -> 3
		// scldel 20  -> 0x4
		// sdadel 16  -> 0x02
		// sclh 8     -> 0xC3
		// scll 0     -> 0xC7

		// 100kHz
		// presc  0x3
		// scldel 0x0x4
		// sdadel 0x2
		// sclh 0xF
		// scll 0x13

		I2C1->CR1 = 0x00000001;
	}

	uint8_t receivedData[3] = { 0 };

	/* Test I2C */
	{
		constexpr uint32_t addrMask = 0x3FF;
		const uint8_t trigger[] = { 0x40, 0xE3 };
		const uint8_t read[] = { 0x40 };

		uint32_t tmp;

		/* set slave address */
		tmp = I2C1->CR2 & ~(addrMask | (1 << 10));
		tmp |= trigger[0] << 1;

		/* set NBYTES */
		tmp = tmp & 0xFF00FFFF;
		tmp |= (1 << 16);
		I2C1->CR2 = tmp;

		I2C1->CR2 |= 1 << 13;

		uint32_t isr;
		do {
			isr = I2C1->ISR;
		} while ((isr & 0x2) == 0);

		I2C1->TXDR = trigger[1];

		do {
			isr = I2C1->ISR;
		} while ((isr & (1<<6)) == 0);

		tmp = I2C1->CR2 & ~(addrMask | (1 << 10));
		tmp |= read[0] << 1;
		tmp |= (1 << 10);
		I2C1->CR2 = tmp;


		tmp = I2C1->CR2 & 0xFF00FFFF;
		tmp |= (3 << 16);
		I2C1->CR2 = tmp;
		I2C1->CR2 |= 1 << 13;

		uint32_t received = 0;

		while (received < 3) {
			do {
				isr = I2C1->ISR;
			} while ((isr & (1 << 2)) == 0);

			uint32_t ch = I2C1->RXDR;
			receivedData[received] = ch;
			received += 1;

			if (received == 2) {
				I2C1->CR2 |= 1 << 14;
			}
		}
	}

	while (true) {
		constexpr uint32_t pin = 15u;

		uint32_t const value = GPIOA->ODR & (0b1 << pin);
		uint32_t const newValue = (~value) & (0b1 << pin);
		GPIOA->ODR = (GPIOA->ODR & ~(0b1 << pin)) | newValue;

		HAL_Delay(5000);
	}
}
