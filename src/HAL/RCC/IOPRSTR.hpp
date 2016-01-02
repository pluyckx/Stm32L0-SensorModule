/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_IOPRSTR_H_
#define SRC_HAL_CLOCK_IOPRSTR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{

namespace ioprstr
{

uint32_t const register_mask = 0x0000009Fu;

enum class BitFields
{
	PortA = 1u << 0u,
	PortB = 1u << 1u,
	PortC = 1u << 2u,
	PortD = 1u << 3u,
	PortE = 1u << 4u,
	PortH = 1u << 7u
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::ioprstr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
