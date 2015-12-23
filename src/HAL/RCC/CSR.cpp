/*
 * CSR.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#include "../RCC/CSR.h"

#include "../RCC/clock_private.hpp"

namespace stm32
{
namespace rcc
{

extern clock_t r_clock;

uint32_t const CSR::m_mask = 0xFF8F7F07;

CSR::CSR()
		: m_register( r_clock.csr, m_mask )
{
}

bool CSR::GetFlag( Flags flag ) const
{
	uint32_t offset = static_cast<uint32_t>( flag );
	uint32_t mask = 0x1u;
	uint32_t value = m_register.Read( mask, offset );

	return (static_cast<stm32::Status>( value ) == stm32::Status::Set);
}

void CSR::ClearResetFlags()
{
	uint32_t value = 1u;
	uint32_t offset = static_cast<uint32_t>( Flags::RemoveRstFlag );
	uint32_t mask = 0x1u;

	m_register.Set( value, mask, offset );
}

void CSR::ResetRtc()
{
	uint32_t value = 1u;
	uint32_t offset = static_cast<uint32_t>( Flags::RtcReset );
	uint32_t mask = 0x1u;

	m_register.Set( value, mask, offset );
}

bool CSR::GetResetRtc() const
{
	uint32_t offset = static_cast<uint32_t>( Flags::RtcReset );
	uint32_t mask = 0x1u;
	uint32_t value = m_register.Read( mask, offset );

	return (static_cast<stm32::Status>( value ) == stm32::Status::Set);
}

void CSR::EnableRtc( stm32::Status status )
{
	uint32_t offset = static_cast<uint32_t>( Flags::RtcEnabled );
	uint32_t mask = 0x1u;
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, mask, offset );
}

bool CSR::IsRtcEnabled() const
{
	uint32_t offset = static_cast<uint32_t>( Flags::RtcEnabled );
	uint32_t mask = 0x1u;
	uint32_t value = m_register.Read( mask, offset );

	return (static_cast<stm32::Status>( value ) == stm32::Status::Set);
}

void CSR::SetRtcClock( RtcClock clock )
{
	uint32_t offset = static_cast<uint32_t>( Settings::RtcSel );
	uint32_t mask = static_cast<uint32_t>( RtcClock::Mask );
	uint32_t value = static_cast<uint32_t>( clock );

	m_register.Set( value, mask, offset );
}

CSR::RtcClock CSR::GetRtcClock() const
{
	uint32_t offset = static_cast<uint32_t>( Settings::RtcSel );
	uint32_t mask = static_cast<uint32_t>( RtcClock::Mask );
	uint32_t value = m_register.Read( mask, offset );

	return static_cast<RtcClock>( value );
}

void CSR::SetLseDrive( LseDriving drive )
{
	uint32_t offset = static_cast<uint32_t>( Settings::LseDrive );
	uint32_t mask = static_cast<uint32_t>( LseDriving::Mask );
	uint32_t value = static_cast<uint32_t>( drive );

	m_register.Set( value, mask, offset );
}

CSR::LseDriving CSR::GetLseDrive() const
{
	uint32_t offset = static_cast<uint32_t>( Settings::LseDrive );
	uint32_t mask = static_cast<uint32_t>( LseDriving::Mask );
	uint32_t value = m_register.Read( mask, offset );

	return static_cast<LseDriving>( value );
}

} /* namespace Clock */
} /* namespace Stm32 */
