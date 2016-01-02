/*
 * CIER.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CIER_HPP_
#define SRC_HAL_RCC_CIER_HPP_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{

namespace cier
{

uint32_t const register_mask = 0x000000BFu;

enum class BitFields
{
	CssLse = 1u << 7u,
	MsiRdy = 1u << 5u,
	PllRdy = 1u << 4u,
	HseRdy = 1u << 3u,
	HsiRdy = 1u << 2u,
	LseRdy = 1u << 1u,
	LsiRdy = 1u << 0u,
};
}

} /* namespace Clock */
} /* namespace Stm32 */

/* Enable enum class to use as bitfields */
template<>
struct enable_bitmask_operators<stm32::hal::cier::BitFields>
{
		static const bool enable = true;
};

#endif /* SRC_HAL_RCC_CIER_HPP_ */
