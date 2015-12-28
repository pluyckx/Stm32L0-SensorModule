/*
 * AHBRSTR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_AHBRSTR_H_
#define SRC_HAL_CLOCK_AHBRSTR_H_

#include "stdint.h"
#include "../GenericTypes.hpp"
#include "../Register.hpp"

namespace stm32
{
namespace rcc
{

class AHBRSTR
{
	public:
		enum class Flags
		{
			Dma = 0u, MemoryInterface = 8u, Crc = 12u, CryptoModule = 24u
		};

		AHBRSTR();

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
