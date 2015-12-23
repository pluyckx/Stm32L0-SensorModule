/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CFGR_HPP_
#define SRC_HAL_RCC_CFGR_HPP_

#include "stdint.h"
#include "../Register32Bit.hpp"

namespace stm32
{
namespace rcc
{

class CFGR
{
	public:
		enum class McuClockPrescaler
		{
			Div1 = 0u, Div2 = 1u, Div4 = 2u, Div8 = 3u, Div16 = 4u, Mask = 7u
		};

		enum class McuClockSelection
		{
			Disabled = 0u,
			SYSCLK = 1u,
			HSI = 2u,
			MSI = 3u,
			HSE = 4u,
			PLL = 5u,
			LSI = 6u,
			LSE = 7u,

			Mask = 0xFu
		};

		enum class PllDivision
		{
			Div2 = 1u, Div3 = 2u, Div4 = 3u, Mask = 3u
		};

		enum class PllMultiplication
		{
			Mul3 = 0u,
			Mul4 = 1u,
			Mul6 = 2u,
			Mul8 = 3u,
			Mul12 = 4u,
			Mul16 = 5u,
			Mul24 = 6u,
			Mul32 = 7u,
			Mul48 = 8u,
			Mask = 0xFu
		};

		enum class PllSource
		{
			HSI = 0u, HSE = 1u, Mask = 0x1u
		};

		enum class StopWakeUpClock
		{
			MSI = 0u, HSI = 1u, Mask = 0x1u
		};

		enum class ApbHighSpeedPrescaler
		{
			Div1 = 0u, Div2 = 4u, Div4 = 5u, Div8 = 6u, Div16 = 7u, Mask = 0x7u
		};

		enum class ApbLowSpeedPrescaler
		{
			Div1 = 0u, Div2 = 4u, Div4 = 5u, Div8 = 6u, Div16 = 7u, Mask = 0x7u,
		};

		enum class AhbPrescaler
		{
			Div1 = 0u,
			Div2 = 8u,
			Div4 = 9u,
			Div8 = 10u,
			Div16 = 11u,
			Div64 = 12u,
			Div128 = 13u,
			Div256 = 14u,
			Div512 = 15u,

			Mask = 0xFu
		};

		enum class SystemClockSwitch
		{
			MSI = 0u, HSI = 1u, HSE = 2u, PLL = 3u, Mask = 3u
		};

		CFGR();

		void Configure( McuClockPrescaler mcu_clk_prescaler,
		                McuClockSelection mcu_clk_sel,
		                PllDivision pll_div,
		                PllMultiplication pll_mul,
		                PllSource pll_src,
		                StopWakeUpClock wu_clk,
		                ApbHighSpeedPrescaler apb_high_pre,
		                ApbLowSpeedPrescaler apb_low_pre,
		                AhbPrescaler ahb_pre,
		                SystemClockSwitch scs );

		McuClockPrescaler GetMcuClockOutputPrescaler() const;
		void SetMcuClockOutputPrescaler( McuClockPrescaler prescaler );

		McuClockSelection GetMcuClockSelection() const;
		void SetMcuClockSelection( McuClockSelection selection );

		PllDivision GetPllOutputDivision() const;
		void SetPllOutputDivision( PllDivision division );

		PllMultiplication GetPllOutputMultiplication() const;
		void SetPllOutputMultiplication( PllMultiplication mul );

		PllSource GetPllSource() const;
		void SetPllSource( PllSource source );

		StopWakeUpClock GetStopWakeUpClock() const;
		void SetStopWakeUpClock( StopWakeUpClock clock );

		ApbHighSpeedPrescaler GetApbHighSpeedPrescaler() const;
		void SetApbHighSpeedPrescaler( ApbHighSpeedPrescaler prescaler );

		ApbLowSpeedPrescaler GetApbLowSpeedPrescaler() const;
		void SetApbLowSpeedPrescaler( ApbLowSpeedPrescaler prescaler );

		AhbPrescaler GetAhbPrescaler() const;
		void SetAhbPrescaler( AhbPrescaler prescaler );

		SystemClockSwitch GetSystemClockSwitchStatus() const;

		SystemClockSwitch GetSystemClockSwitch() const;
		void SetSystemClockSwitch( SystemClockSwitch clock_switch );
	private:
		Register32Bit m_register;

		static uint32_t const m_offset_mcu_clock_prescaler;
		static uint32_t const m_offset_mcu_clock_selection;
		static uint32_t const m_offset_pll_output_division;
		static uint32_t const m_offset_pll_output_mul;
		static uint32_t const m_offset_pll_source;
		static uint32_t const m_offset_stop_wakup_clock;
		static uint32_t const m_offset_apb_high_speed_pres;
		static uint32_t const m_offset_apb_low_speed_pres;
		static uint32_t const m_offset_ahb_prescaler;
		static uint32_t const m_offset_sws;
		static uint32_t const m_offset_sw;

		static uint32_t const m_mask;
};
}
} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CONTROLREGISTER_HPP_ */
