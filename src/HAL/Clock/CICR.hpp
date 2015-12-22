/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CIER_H_
#define SRC_HAL_CLOCK_CIER_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace clock
{

class CICR
{
	public:
		enum class Flags
		{
			HseCss = 8u,
			LseCss = 7u,
			MsiRdy = 5u,
			PllRdy = 4u,
			HseRdy = 3u,
			HsiRdy = 2u,
			LseRdy = 1u,
			LsiRdy = 0u
		};

		CICR();

		void ClearFlag( Flags flag );

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
