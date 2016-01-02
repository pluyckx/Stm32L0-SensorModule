/*
 * SysTick.h
 *
 *  Created on: Dec 31, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_SYSTICK_SYSTICK_H_
#define SRC_HAL_SYSTICK_SYSTICK_H_

#include "../Register.hpp"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{
uint32_t const reload_value_max = 0x00FFFFFFu;

struct systick_r
{
		uint32_t csr;
		uint32_t rvr;
		uint32_t cvr;
		uint32_t calib;
};

class SysTick
{
	public:

		enum class ControlStatusBits
		{
			CountFlag = 1u << 16,
			ProcessorClock = 1u << 2u,
			InterruptEnabled = 1u << 1u,
			Enable = 1u << 0u
		};

		static SysTick &GetSysTick();

		void ConfigureSysTick( ControlStatusBits configuration );
		void EnableSysTick();
		void DisableSysTick();
		bool HasCountedDown();
		void ClearCounter();

		bool SetReloadValue( uint32_t value );

		uint32_t GetCurrentValue() const;


	private:
		SysTick();

		static SysTick m_systick;
};

} /* namespace hal */
} /* namespace stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::SysTick::ControlStatusBits>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_SYSTICK_SYSTICK_H_ */
