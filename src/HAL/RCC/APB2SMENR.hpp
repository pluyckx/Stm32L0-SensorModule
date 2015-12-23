/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_APB2SMENR_H_
#define SRC_HAL_CLOCK_APB2SMENR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class APB2SMENR
{
	public:
		enum class Flags
		{
			SysCfg = 0u, Tim21 = 2u, Tim22 = 5u, Adc = 9u, Spi1 = 12u, Usart1 = 14u, Dbg = 22u
		};

		APB2SMENR();

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
