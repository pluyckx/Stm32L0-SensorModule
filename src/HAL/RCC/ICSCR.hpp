/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_ICSCR_HPP_
#define SRC_HAL_RCC_ICSCR_HPP_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{

namespace icscr
{

uint32_t const register_mask = 0xFFFFFFFF;

enum class MsiRange
{
	Range65kHz535 = 0u,
	Range131kHz072 = 1u,
	Range262kHz144 = 2u,
	Range524kHz288 = 3u,
	Range1MHz048 = 4u,
	Range2MHz097 = 5u,
	Range4MHz194 = 6u,

	Mask = 0x7u
};

enum class FieldMasks : uint32_t
{
	MsiTrim = 0xFF000000u,
	MsiCal = 0x00FF0000u,
	MsiRange = 0x0000E000u,
	HsiTrim = 0x00001F00u,
	HsiCal = 0x000000FFu
};

}
}
} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CONTROLREGISTER_HPP_ */
