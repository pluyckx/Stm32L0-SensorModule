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
namespace hal
{

namespace apb2enr
{
uint32_t const register_mask = 0x004052A5u;
enum class BitFields
{
	SysCfg = 1u << 0u,
	Tim21 = 1u << 2u,
	Tim22 = 1u << 5u,
	Firewall = 1u << 7u,
	Adc = 1u << 9u,
	Spi1 = 1u << 12u,
	Usart1 = 1u << 14u,
	Dbg = 1u << 22u
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::apb2enr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
