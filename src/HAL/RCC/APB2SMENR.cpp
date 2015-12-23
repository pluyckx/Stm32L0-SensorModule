/*
 * CIFR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/APB2SMENR.hpp"

#include "../GenericTypes.hpp"
#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const APB2SMENR::m_mask = 0x00405225;

APB2SMENR::APB2SMENR()
		: m_register( Register32Bit( r_clock.apb2smenr, APB2SMENR::m_mask ) )
{
}

bool APB2SMENR::Get( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	stm32::Status status = static_cast<stm32::Status>( m_register.Read( 0x1u,
	                                                                    offset ) );

	return (status == stm32::Status::Set);
}

void APB2SMENR::Clear( Flags flag )
{
	uint32_t offset = static_cast<uint32_t>( flag );
	m_register.SetBits( 0x0u, 0x1u, offset );
}

void APB2SMENR::Set( Flags flag )
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
