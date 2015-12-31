/*
 * CCIPR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CCIPR_H_
#define SRC_HAL_RCC_CCIPR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace rcc
{

namespace ccipr
{

uint32_t const register_mask = 0x000F3C0Fu;

uint32_t const offset_lptimer1 = 18u;
uint32_t const offset_i2c3 = 16u;
uint32_t const offset_i2c1 = 12u;
uint32_t const offset_lpuart1 = 10u;
uint32_t const offset_usart2 = 2u;
uint32_t const offset_usart1 = 0u;

enum class ClockLpTimer1
{
	Apb = 0u << offset_lptimer1, Lsi = 1u << offset_lptimer1, Hsi = 2u
	    << offset_lptimer1,
	Lse = 3u << offset_lptimer1
};

enum class ClockI2c3
{
	Apb = 0u << offset_i2c3, SystemClock = 1u << offset_i2c3, Hsi = 2u
	    << offset_i2c3
};

enum class ClockI2c1
{
	Apb = 0u << offset_i2c1, SystemClock = 1u << offset_i2c1, Hsi = 2u
	    << offset_i2c1
};

enum class ClockLpUart1
{
	Apb = 0u << offset_lpuart1, SystemClock = 1u << offset_lpuart1, Hsi = 2u
	    << offset_lpuart1,
	Lse = 3u << offset_lpuart1
};

enum class ClockUsart2
{
	Apb = 0u << offset_usart2, SystemClock = 1u << offset_usart2, Hsi = 2u
	    << offset_usart2,
	Lse = 3u << offset_usart2
};

enum class ClockUsart1
{
	Apb = 0u << offset_usart1, SystemClock = 1u << offset_usart1, Hsi = 2u
	    << offset_usart1,
	Lse = 3u << offset_usart1
};

enum class FieldMasks
{
	LpTimer1 = 0x3u << offset_lptimer1,
	I2c3 = 0x3u << offset_i2c3,
	I1c1 = 0x3u << offset_i2c1,
	LpUart1 = 0x3u << offset_lpuart1,
	Usart2 = 0x3u << offset_usart2,
	Usart1 = 0x3u << offset_usart1
};

}

} /* namespace Clock */
} /* namespace Stm32 */

#endif /* SRC_HAL_RCC_CCIPR_H_ */
