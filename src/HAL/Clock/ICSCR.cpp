/*
 * ControlRegister.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#include "../Register32Bit.hpp"
#include "clock_private.hpp"
#include "ICSCR.hpp"

namespace stm32
{

namespace clock
{

extern clock_t r_clock;

uint32_t const ICSCR::m_offset_msi_trim = 24u;
uint32_t const ICSCR::m_offset_msi_cal = 16u;
uint32_t const ICSCR::m_offset_msi_range = 13u;
uint32_t const ICSCR::m_offset_hsi_trim = 8u;
uint32_t const ICSCR::m_offset_hsi_cal = 0u;

ICSCR::ICSCR()
		: m_register( Register32Bit( r_clock.icscr, 0xFFFFFFFFu ) )
{
}

uint8_t ICSCR::GetMsiTrim() const
{
	return static_cast<uint8_t>( m_register.Read( 0xFF, ICSCR::m_offset_msi_trim ) );
}

void ICSCR::SetMsiTrim( uint8_t value )
{
	m_register.SetRegister( value, 0xFF, ICSCR::m_offset_msi_trim );
}

uint8_t ICSCR::GetMsiCal() const
{
	return static_cast<uint8_t>( m_register.Read( 0xFF, ICSCR::m_offset_msi_cal ) );
}

ICSCR::MsiRange ICSCR::GetMsiRange() const
{
	uint32_t mask = static_cast<uint32_t>( MsiRange::Mask );
	return static_cast<MsiRange>( m_register.Read( mask,
	                                               ICSCR::m_offset_msi_range ) );
}

void ICSCR::SetMsiRange( MsiRange range )
{
	uint32_t value = static_cast<uint32_t>( range );
	uint32_t mask = static_cast<uint32_t>( MsiRange::Mask );

	m_register.SetRegister( value, mask, ICSCR::m_offset_msi_range );
}

uint8_t ICSCR::GetHsiTrim() const
{
	return static_cast<uint8_t>( m_register.Read( 0x1F, ICSCR::m_offset_hsi_trim ) );
}

void ICSCR::SetHsiTrim( uint8_t value )
{
	m_register.SetRegister( value, 0x1F, ICSCR::m_offset_msi_trim );
}

uint8_t ICSCR::GetHsiCal() const
{
	return static_cast<uint8_t>( m_register.Read( 0xFF, ICSCR::m_offset_hsi_cal ) );
}
}
} /* namespace Stm32 */
