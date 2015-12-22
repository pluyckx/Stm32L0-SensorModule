/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "CIFR.hpp"

#include "clock_private.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace clock
{

extern clock_t r_clock;

uint32_t const CIFR::m_mask = 0x000001BF;

CIFR::CIFR()
		: m_register( Register32Bit( r_clock.cifr, CIFR::m_mask ) )
{
}

bool CIFR::IsFlagSet( Flags flag ) const
{
	uint32_t offset = static_cast<uint32_t>( flag );
	uint32_t value = m_register.Read( 0x1u, offset );

	return static_cast<stm32::Status>( value ) == stm32::Status::Set;
}

}
;
/* namespace Clock */
}
;
/* namespace Stm32 */
