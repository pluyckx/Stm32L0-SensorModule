/*
 * CCIPR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CCIPR_H_
#define SRC_HAL_RCC_CCIPR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class CCIPR
{
	public:
		enum class Clock
		{
			Apb = 0u, Lsi_SystemClock = 1u, Hsi = 2u, Lse_Reserved = 3u
		};

		enum class Peripheral
		{
			Usart1 = 0u,
			Usart2 = 2u,
			LpUart1 = 10u,
			I2c1 = 12u,
			I2c3 = 16u,
			LpTimer1 = 18u
		};

		CCIPR();

		void SetClock( Peripheral peripheral, Clock clock );
		Clock GetClock( Peripheral peripheral );

	private:
		Register32Bit m_register;

		static uint32_t const m_mask;
};

} /* namespace Clock */
} /* namespace Stm32 */

#endif /* SRC_HAL_RCC_CCIPR_H_ */
