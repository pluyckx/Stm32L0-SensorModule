/*
 * AHBENR.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_AHBENR_H_
#define SRC_HAL_CLOCK_AHBENR_H_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace rcc
{

namespace ahbenr
{
uint32_t const register_mask = 0x01001101u;

enum class BitFields
{
	Dma = 0u, MemoryInterface = 8u, Crc = 12u, CryptoModule = 24u
};
}

} /* namespace Clock */
} /* namespace Stm32 */

template<>
struct enable_bitmask_operators<stm32::rcc::ahbenr::BitFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_CLOCK_CIER_H_ */
