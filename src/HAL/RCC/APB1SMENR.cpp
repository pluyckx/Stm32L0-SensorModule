/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/APB1SMENR.hpp"

#include "../GenericTypes.hpp"
#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const APB1SMENR::m_mask = 0xD07E4833;

APB1SMENR::APB1SMENR()
		: m_register( Register32Bit( r_clock.apb1smenr, APB1SMENR::m_mask ) )
{
}

bool APB1SMENR::Get( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	stm32::Status status = static_cast<stm32::Status>( m_register.Read( 0x1u,
	                                                                    offset ) );

	return (status == stm32::Status::Set);
}

void APB1SMENR::Clear( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	m_register.SetBits( 0x0u, 0x1u, offset );
}

void APB1SMENR::Set( Flags flag )
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
