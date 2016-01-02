/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CFGR_HPP_
#define SRC_HAL_RCC_CFGR_HPP_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{

namespace cfgr
{

uint32_t const register_mask = 0x7FFDBFFFu;

enum class McuClockPrescaler
{
	Div1 = 0u << 28u,
	Div2 = 1u << 28u,
	Div4 = 2u << 28u,
	Div8 = 3u << 28u,
	Div16 = 4u << 28u
};

enum class McuClockSelection
{
	Disabled = 0u << 24u,
	SYSCLK = 1u << 24u,
	HSI = 2u << 24u,
	MSI = 3u << 24u,
	HSE = 4u << 24u,
	PLL = 5u << 24u,
	LSI = 6u << 24u,
	LSE = 7u << 24u
};

enum class PllDivision
{
	Div2 = 1u << 22u, Div3 = 2u << 22u, Div4 = 3u << 22u
};

enum class PllMultiplication
{
	Mul3 = 0u << 18u,
	Mul4 = 1u << 18u,
	Mul6 = 2u << 18u,
	Mul8 = 3u << 18u,
	Mul12 = 4u << 18u,
	Mul16 = 5u << 18u,
	Mul24 = 6u << 18u,
	Mul32 = 7u << 18u,
	Mul48 = 8u << 18u
};

enum class BitFields
{
	PllHse = 1u << 16u, WakeUpClockHsi = 1u << 15u
};

enum class ApbHighSpeedPrescaler
{
	Div1 = 0u << 11u,
	Div2 = 4u << 11u,
	Div4 = 5u << 11u,
	Div8 = 6u << 11u,
	Div16 = 7u << 11u
};

enum class ApbLowSpeedPrescaler
{
	Div1 = 0u << 8u, Div2 = 4u << 8u, Div4 = 5u << 8u, Div8 = 6u << 8u, Div16 = 7u
	    << 8u
};

enum class AhbPrescaler
{
	Div1 = 0u << 4u,
	Div2 = 8u << 4u,
	Div4 = 9u << 4u,
	Div8 = 10u << 4u,
	Div16 = 11u << 4u,
	Div64 = 12u << 4u,
	Div128 = 13u << 4u,
	Div256 = 14u << 4u,
	Div512 = 15u << 4u
};

enum class SystemClockSwitch
{
	MSI = 0u << 2u, HSI = 1u << 2u, HSE = 2u << 2u, PLL = 3u << 2u, Mask = 3u
	    << 2u
};

enum class SystemClockSwitchSelection
{
	MSI = 0u << 0u, HSI = 1u << 0u, HSE = 2u << 0u, PLL = 3u << 0u, Mask = 3u
	    << 0u
};

enum class FieldMasks
{
	McoPre = 0x70000000u,
	McoSel = 0x0F000000u,
	PllDiv = 0x00C00000u,
	PllMul = 0x003C0000u,
	ApbHighSpeedPrescaler = 0x00003800u,
	ApbLowSpeedPrescaler = 0x00000700u,
	AhbPrescaler = 0x000000F0u,
	SystemClockSwitch = 0x0000000Cu,
	SystemClockSwitchSelection = 0x00000003u
};
}
}
} /* namespace Stm32 */

/* Enable enum class to use as bitfields */
template<>
struct enable_bitmask_operators<stm32::hal::cfgr::BitFields>
{
		static const bool enable = true;
};

#endif /* SRC_HAL_CLOCK_CONTROLREGISTER_HPP_ */
