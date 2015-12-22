/*
 * clock_private.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_CLOCK_PRIVATE_HPP_
#define SRC_HAL_CLOCK_CLOCK_PRIVATE_HPP_

#include "stdint.h"

namespace stm32
{

namespace clock
{

typedef struct clock clock_t;
struct clock
{
		uint32_t cr; /* 0x00 */
		uint32_t icscr; /* 0x04 */
		uint32_t reserved1; /* 0x08 */
		uint32_t cfgr; /* 0x0c */
		uint32_t cier; /* 0x10 */
		uint32_t cifr; /* 0x14 */
		uint32_t cicr; /* 0x18 */
		uint32_t ioprstr; /* 0x1c */
		uint32_t ahbrstr; /* 0x20 */
		uint32_t apb2rstr; /* 0x24 */
		uint32_t apb1rstr; /* 0x28 */
		uint32_t iopenr; /* 0x2c */
		uint32_t ahbenr; /* 0x30 */
		uint32_t apb2enr; /* 0x34 */
		uint32_t apb1enr; /* 0x38 */
		uint32_t iopsmenr; /* 0x3c */
		uint32_t ahbsmenr; /* 0x40 */
		uint32_t apb2smenr; /* 0x44 */
		uint32_t apb1smenr; /* 0x48 */
		uint32_t ccipr; /* 0x4c */
		uint32_t csr; /* 0x50 */

};
}
}

#endif /* SRC_HAL_CLOCK_CLOCK_PRIVATE_HPP_ */
