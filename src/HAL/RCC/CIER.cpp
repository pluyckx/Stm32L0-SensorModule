/*
 * CIER.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/CIER.hpp"

#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const CIER::m_offset_lse_css = 7u;
uint32_t const CIER::m_offset_msi_rdy = 5u;
uint32_t const CIER::m_offset_pll_rdy = 4u;
uint32_t const CIER::m_offset_hse_rdy = 3u;
uint32_t const CIER::m_offset_hsi_rdy = 2u;
uint32_t const CIER::m_offset_lse_rdy = 1u;
uint32_t const CIER::m_offset_lsi_rdy = 0u;

uint32_t const CIER::m_mask = 0x000000BF;

CIER::CIER()
		: m_register( Register32Bit( r_clock.cier, CIER::m_mask ) )
{
}

void CIER::Configure( stm32::Status lse_css,
                      stm32::Status msi_rdy,
                      stm32::Status pll_rdy,
                      stm32::Status hse_rdy,
                      stm32::Status hsi_rdy,
                      stm32::Status lse_rdy,
                      stm32::Status lsi_rdy )
{
	uint32_t value = (static_cast<uint32_t>( lse_css ) << m_offset_lse_css)
	    | (static_cast<uint32_t>( msi_rdy ) << m_offset_msi_rdy)
	    | (static_cast<uint32_t>( pll_rdy ) << m_offset_pll_rdy)
	    | (static_cast<uint32_t>( hse_rdy ) << m_offset_hse_rdy)
	    | (static_cast<uint32_t>( hsi_rdy ) << m_offset_hsi_rdy)
	    | (static_cast<uint32_t>( lse_rdy ) << m_offset_lse_rdy)
	    | (static_cast<uint32_t>( lsi_rdy ) << m_offset_lsi_rdy);

	m_register.Set( value, m_mask );
}

bool CIER::IsLseCssSet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_lse_css ) )
	    == stm32::Status::Set);
}
bool CIER::IsMsiRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_msi_rdy ) )
	    == stm32::Status::Set);
}
bool CIER::IsPllRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_pll_rdy ) )
	    == stm32::Status::Set);
}
bool CIER::IsHseRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_hse_rdy ) )
	    == stm32::Status::Set);
}
bool CIER::IsHsiRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_hsi_rdy ) )
	    == stm32::Status::Set);
}
bool CIER::IsLseRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_lse_rdy ) )
	    == stm32::Status::Set);
}
bool CIER::IsLsiRdySet() const
{
	return (static_cast<stm32::Status>( m_register.Read( 0x1u, m_offset_lsi_rdy ) )
	    == stm32::Status::Set);
}

void CIER::SetLseCss( stm32::Status status )
{
	SetStatusBit( status, m_offset_lse_css );
}

void CIER::SetMsiRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_msi_rdy );
}

void CIER::SetPllRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_pll_rdy );
}

void CIER::SetHseRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_hse_rdy );
}

void CIER::SetHsiRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_hsi_rdy );
}

void CIER::SetLseRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_lse_rdy );
}

void CIER::SetLsiRdy( stm32::Status status )
{
	SetStatusBit( status, m_offset_lsi_rdy );
}

inline void CIER::SetStatusBit( stm32::Status status, uint32_t offset )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 0x1u, offset );
}

}
;
/* namespace Clock */
}
;
/* namespace Stm32 */
