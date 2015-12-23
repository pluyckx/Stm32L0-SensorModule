/*
 * CIFR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CIFR_H_
#define SRC_HAL_CLOCK_CIFR_H_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class CIFR
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

		CIFR();

		bool IsFlagSet( Flags flag ) const;

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
