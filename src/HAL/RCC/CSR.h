/*
 * CCIPR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CCIPR_H_
#define SRC_HAL_CLOCK_CCIPR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace rcc
{

namespace csr
{

uint32_t const register_mask = 0xFF8F7F07u;

uint32_t const offset_rtc_clock = 16u;
uint32_t const offset_lse_driving = 11u;

enum class RtcClock
{
	NoClock = 0u << offset_rtc_clock, Lse = 1u << offset_rtc_clock, Lsi = 2u
	    << offset_rtc_clock,
	Hse = 3u << offset_rtc_clock, Mask = 3u << offset_rtc_clock
};

enum class LseDriving
{
	Lowest = 0u << offset_lse_driving,
	MediumLow = 1u << offset_lse_driving,
	MediumHigh = 2u << offset_lse_driving,
	Highest = 3u << offset_lse_driving,
	Mask = 3u << offset_lse_driving
};

enum class BitFields : uint32_t
{
	LsiOn = 1u << 0u,
	LsiReady = 1u << 1u,
	LsiIwdgLowPowerMode = 1u << 2u,
	LseOn = 1u << 8u,
	LseReady = 1u << 9u,
	LseBypass = 1u << 10u,
	CssLseOn = 1u << 13u,
	CssLseFailDet = 1u << 14u,
	RtcEnabled = 1u << 18u,
	RtcReset = 1u << 19u,
	RemoveRstFlag = 1u << 23u,
	FirewallRst = 1u << 24u,
	OptByteRst = 1u << 25u,
	PinRst = 1u << 26u,
	PorRst = 1u << 27u,
	SoftwareRst = 1u << 28u,
	IwdgRst = 1u << 29u,
	WwdgRst = 1u << 30u,
	LowPowerRst = 1u << 31u
};

enum class FieldMasks
{
	LseDrv = 0x3u << offset_lse_driving, RtcSel = 0x3u << offset_rtc_clock
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::rcc::csr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CCIPR_H_ */
