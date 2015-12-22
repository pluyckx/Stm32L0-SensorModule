/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "clock_private.hpp"
#include "../GenericTypes.hpp"
#include "CICR.hpp"

namespace stm32
{
namespace clock
{

extern clock_t r_clock;

uint32_t const CICR::m_mask = 0x000001BF;

CICR::CICR()
		: m_register( Register32Bit( r_clock.cicr, CICR::m_mask ) )
{
}

void CICR::ClearFlag( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	m_register.SetBits( 0x1u, 0x1u, offset );
}

}
;
/* namespace Clock */
}
;
/* namespace Stm32 */
