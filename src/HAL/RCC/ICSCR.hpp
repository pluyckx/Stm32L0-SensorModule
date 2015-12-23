/*
 * ControlRegister.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_ICSCR_HPP_
#define SRC_HAL_RCC_ICSCR_HPP_

#include "stdint.h"
#include "../Register32Bit.hpp"

namespace stm32
{
namespace rcc
{

class ICSCR
{
	public:
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

		ICSCR();

		uint8_t GetMsiTrim() const;
		void SetMsiTrim( uint8_t value );

		uint8_t GetMsiCal() const;

		MsiRange GetMsiRange() const;
		void SetMsiRange( MsiRange range );

		uint8_t GetHsiTrim() const;
		void SetHsiTrim( uint8_t value );

		uint8_t GetHsiCal() const;

	private:
		Register32Bit m_register;

		static uint32_t const m_offset_msi_trim;
		static uint32_t const m_offset_msi_cal;
		static uint32_t const m_offset_msi_range;
		static uint32_t const m_offset_hsi_trim;
		static uint32_t const m_offset_hsi_cal;
};
}
} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CONTROLREGISTER_HPP_ */
