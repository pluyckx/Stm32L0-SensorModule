/*
 * CCIPR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/CCIPR.h"

#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const CCIPR::m_mask = 0x000F3C0F;

CCIPR::CCIPR()
		: m_register( r_clock.ccipr, m_mask )
{
}

void CCIPR::SetClock( Peripheral peripheral, Clock clock )
{
	uint32_t mask = 0x3u;
	uint32_t value = static_cast<uint32_t>( clock );
	uint32_t offset = static_cast<uint32_t>( peripheral );

	m_register.Set( 0x3, mask, offset );
}

CCIPR::Clock CCIPR::GetClock( Peripheral peripheral )
{
	uint32_t mask = 0x3u;
	uint32_t offset = static_cast<uint32_t>( peripheral );
	uint32_t value = m_register.Read( mask, offset );

	return static_cast<Clock>( value );
}

} /* namespace Clock */
} /* namespace Stm32 */
