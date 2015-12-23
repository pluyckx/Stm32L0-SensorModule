/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/AHBSMENR.hpp"

#include "../GenericTypes.hpp"
#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const AHBSMENR::m_mask = 0x01001301;

AHBSMENR::AHBSMENR()
		: m_register( Register32Bit( r_clock.ahbsmenr, AHBSMENR::m_mask ) )
{
}

bool AHBSMENR::Get( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	stm32::Status status = static_cast<stm32::Status>( m_register.Read( 0x1u,
	                                                                    offset ) );

	return (status == stm32::Status::Set);
}

void AHBSMENR::Clear( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	m_register.SetBits( 0x0u, 0x1u, offset );
}

void AHBSMENR::Set( Flags flag )
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
