/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CIFR_H_
#define SRC_HAL_CLOCK_CIFR_H_

#include "stdint.h"
#include "../GenericTypes.hpp"
#include "../Register.hpp"

namespace stm32
{
namespace rcc
{

namespace cifr
{

uint32_t const register_mask = 0x000001BFu;

enum class BitFields
{
	CssHse = 1u << 8u,
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
struct enable_bitmask_operators<stm32::rcc::cifr::BitFields>
{
		static const bool enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
