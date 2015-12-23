/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_IOPRSTR_H_
#define SRC_HAL_CLOCK_IOPRSTR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class IOPRSTR
{
	public:
		enum class Flags
		{
			PortA = 0u, PortB = 1u, PortC = 2u, PortD = 3u, PortE = 4u, PortH = 7u
		};

		IOPRSTR();

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
