/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_APB1SMENR_H_
#define SRC_HAL_CLOCK_APB1SMENR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace rcc
{

namespace apb1smenr
{

uint32_t const register_mask = 0xD87E4833u;

enum class BitFields
{
	Tim2 = 0u,
	Tim3 = 1u,
	Tim6 = 4u,
	Tim7 = 5u,
	WindowWatchdog = 11u,
	spi2 = 14u,
	Usart2 = 17u,
	LpUart1 = 18u,
	Usart4 = 19u,
	Usart5 = 20u,
	I2c1 = 21u,
	I2c2 = 22u,
	crs = 27u,
	PowerInterface = 28u,
	I2c3 = 30u,
	LpTim1 = 31u
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::rcc::apb1smenr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
