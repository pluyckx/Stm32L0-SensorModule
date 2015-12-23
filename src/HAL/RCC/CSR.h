/*
 * CCIPR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CCIPR_H_
#define SRC_HAL_CLOCK_CCIPR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class CSR
{
	public:
		enum class RtcClock
		{
			NoClock = 0u, Lse = 1u, Lsi = 2u, Hse = 3u, Mask = 3u
		};

		enum class LseDriving
		{
			Lowest = 0u, MediumLow = 1u, MediumHigh = 2u, Highest = 3u, Mask = 3u
		};

		enum class Flags
		{
			LsiOn = 0u,
			LsiReady = 1u,
			LsiIwdgLowPowerMode = 2u,
			LseOn = 8u,
			LseReady = 9u,
			LseBypass = 10u,
			CssLseOn = 13u,
			CssLseFailDet = 14u,
			RtcEnabled = 18u,
			RtcReset = 19u,
			RemoveRstFlag = 23u,
			FirewallRst = 24u,
			OptByteRst = 25u,
			PinRst = 26u,
			PorRst = 27u,
			SoftwareRst = 28u,
			IwdgRst = 29u,
			WwdgRst = 30u,
			LowPowerRst = 31u
		};

		enum class Settings
		{
			LseDrive = 11u, RtcSel = 16u
		};

		CSR();

		bool GetFlag( Flags flag ) const;
		void ClearResetFlags();

		void ResetRtc();
		bool GetResetRtc() const;

		void EnableRtc( stm32::Status status );
		bool IsRtcEnabled() const;

		void SetRtcClock( RtcClock clock );
		RtcClock GetRtcClock() const;

		void SetLseDrive( LseDriving drive );
		LseDriving GetLseDrive() const;

	private:
		Register32Bit m_register;

		static uint32_t const m_mask;
};

} /* namespace Clock */
} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CCIPR_H_ */
