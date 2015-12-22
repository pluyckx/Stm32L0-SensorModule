/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CR_HPP_
#define SRC_HAL_CLOCK_CR_HPP_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{

namespace clock
{

class CR
{
	public:
		enum class RtcPrescaler
		{
			Div2 = 0u, Div4 = 1u, Div8 = 2u, Div16 = 3u, Mask = 0x3u
		};

		CR();

		void Configure( stm32::Status pll_on,
		                RtcPrescaler rtc_prescaler,
		                stm32::Status css_hse_on,
		                stm32::Status hse_bypass,
		                stm32::Status hse_on,
		                stm32::Status msi_on,
		                stm32::Status hsi_enabled,
		                stm32::Status hsi_divided,
		                stm32::Status hsi_force_on,
		                stm32::Status hsi_on );

		bool IsPllReady() const;

		void SetPllOn( stm32::Status status );
		bool IsPllOn() const;

		void SetRtcPrescaler( RtcPrescaler prescaler );
		RtcPrescaler GetRtcPrescaler() const;

		void SetCssHse( stm32::Status status );
		bool IsCssHseOn() const;

		void SetHseBypass( stm32::Status status );
		bool IsHseBypassOn() const;

		bool IsHseReady() const;

		void SetHseOn( stm32::Status status );
		bool IsHseOn() const;

		bool IsMsiReady() const;

		void SetMsiOn( stm32::Status status );
		bool IsMsiOn() const;

		void SetHsiEnabled( stm32::Status status );
		bool IsHsiEnabled() const;

		bool IsHsiDivided() const;

		void RequestHsiDivision( stm32::Status status );
		bool IsHsiDivisionRequested() const;

		bool IsHsiReady() const;

		void ForceHsiOn( stm32::Status status );
		bool IsHsiForcedOn() const;

		void SetHsiOn( stm32::Status status );
		bool IsHsiOn() const;

	private:
		Register32Bit m_register;

		static uint32_t const m_mask;
		static uint32_t const m_offset_pll_rdy;
		static uint32_t const m_offset_pll_on;
		static uint32_t const m_offset_rtc_prescaler;
		static uint32_t const m_offset_css_hse_on;
		static uint32_t const m_offset_hse_bypass;
		static uint32_t const m_offset_hse_rdy;
		static uint32_t const m_offset_hse_on;
		static uint32_t const m_offset_msi_rdy;
		static uint32_t const m_offset_msi_on;
		static uint32_t const m_offset_hsi_enabled;
		static uint32_t const m_offset_hsi_div_flag;
		static uint32_t const m_offset_hsi_div_enabled;
		static uint32_t const m_offset_hsi_rdy;
		static uint32_t const m_offset_hsi_force_on;
		static uint32_t const m_offset_hsi_on;
};

} /* namespace Clock */

} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CR_HPP_ */
