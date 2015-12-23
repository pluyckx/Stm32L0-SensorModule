/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/APB1RSTR.hpp"

#include "../GenericTypes.hpp"
#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const APB1RSTR::m_mask = 0xD87E4833;

APB1RSTR::APB1RSTR()
		: m_register( Register32Bit( r_clock.apb1rstr, APB1RSTR::m_mask ) )
{
}

bool APB1RSTR::Get( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	stm32::Status status = static_cast<stm32::Status>( m_register.Read( 0x1u,
	                                                                    offset ) );

	return (status == stm32::Status::Set);
}

void APB1RSTR::Clear( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	m_register.SetBits( 0x0u, 0x1u, offset );
}

void APB1RSTR::Set( Flags flag )
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
