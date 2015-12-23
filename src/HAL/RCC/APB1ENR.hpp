/*
 * APB1ENR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_APB1ENR_H_
#define SRC_HAL_CLOCK_APB1ENR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class APB1ENR
{
	public:
		enum class Flags
		{
			Tim2 = 0u,
			Tim3 = 1u,
			Tim6 = 4u,
			Tim7 = 5u,
			WindowWatchdog = 11u,
			spi2 = 14u,
			Usart2 = 17u,
			LpUart1 = 18u,
			Usart4 = 19u,
			Usart5 = 20u,
			I2c1 = 21u,
			I2c2 = 22u,
			PowerInterface = 28u,
			I2c3 = 30u,
			LpTim1 = 31u
		};

		APB1ENR();

		bool Get( Flags flag );
		void Set( Flags flag );
		void Clear( Flags flag );

	private:
		Register32Bit m_register;

		static uint32_t const m_mask;
};

}
;
/* namespace Clock */
}
;
/* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_CIER_H_ */
