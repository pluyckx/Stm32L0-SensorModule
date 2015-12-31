/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_APB2ENR_H_
#define SRC_HAL_CLOCK_APB2ENR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace rcc
{

namespace apb2enr
{
uint32_t const register_mask = 0x004052A5u;
enum class BitFields
{
	SysCfg = 0u,
	Tim21 = 2u,
	Tim22 = 5u,
	Firewall = 7u,
	Adc = 9u,
	Spi1 = 12u,
	Usart1 = 14u,
	Dbg = 22u
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::rcc::apb2enr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
