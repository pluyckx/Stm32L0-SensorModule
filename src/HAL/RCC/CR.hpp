/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CR_HPP_
#define SRC_HAL_RCC_CR_HPP_

#include "stdint.h"
#include "../GenericTypes.hpp"
#include "../Register.hpp"

#include "../TypeSafeBitmasks.hpp"

namespace stm32
{

namespace rcc
{

namespace cr
{

uint32_t const register_mask = 0x033F033Fu;

enum RtcPrescaler
{
	Div2 = 0u, Div4 = 1u, Div8 = 2u, Div16 = 3u, Mask = 0x3u
};

enum class BitFields
{
		HsiOn = (1u << 0u),
		HsiForceOn = (1u << 1u),
		HsiReady = (1u << 2u),
		HsiDividerEnabled = (1u << 3u),
		HsiDividerFlag = (1u << 4u),
		HsiOutEnabled = (1 << 5u),
		MsiOn = (1u << 8u),
		MsiReady = (1u << 9u),
		HseOn = (1u << 16u),
		HseReady = (1u << 17u),
		HseBypass = (1u << 18u),
		HseCssOn = (1u << 19u),
		PllOn = (1u << 24u),
		PllReady = (1u << 25u)
};

enum FieldMasks
{
		RtcPrescaler = (3u << 20u),
};

}

} /* namespace Clock */

} /* namespace Stm32 */


/* Enable enum class to use as bitfields */
template<>
struct enable_bitmask_operators<stm32::rcc::cr::BitFields>{
    static const bool enable=true;
};

#endif /* SRC_HAL_RCC_CR_HPP_ */
