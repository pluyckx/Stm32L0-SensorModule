/*
 * ControlRegister.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#include "../RCC/CR.hpp"

#include "../RCC/clock_private.hpp"
#include "../Register32Bit.hpp"

namespace stm32
{

namespace rcc
{

extern clock_t r_clock;

uint32_t const CR::m_offset_pll_rdy = 25u;
uint32_t const CR::m_offset_pll_on = 24u;
uint32_t const CR::m_offset_rtc_prescaler = 20u;
uint32_t const CR::m_offset_css_hse_on = 19u;
uint32_t const CR::m_offset_hse_bypass = 18u;
uint32_t const CR::m_offset_hse_rdy = 17u;
uint32_t const CR::m_offset_hse_on = 16u;
uint32_t const CR::m_offset_msi_rdy = 9u;
uint32_t const CR::m_offset_msi_on = 8u;
uint32_t const CR::m_offset_hsi_enabled = 5u;
uint32_t const CR::m_offset_hsi_div_flag = 4u;
uint32_t const CR::m_offset_hsi_div_enabled = 3u;
uint32_t const CR::m_offset_hsi_rdy = 2u;
uint32_t const CR::m_offset_hsi_force_on = 1u;
uint32_t const CR::m_offset_hsi_on = 0u;

uint32_t const CR::m_mask = 0x033F033F;

CR::CR()
		: m_register( Register32Bit( r_clock.cr, CR::m_mask ) )
{
}

void CR::Configure( stm32::Status pll_on,
                    RtcPrescaler rtc_prescaler,
                    stm32::Status css_hse_on,
                    stm32::Status hse_bypass,
                    stm32::Status hse_on,
                    stm32::Status msi_on,
                    stm32::Status hsi_enabled,
                    stm32::Status hsi_divided,
                    stm32::Status hsi_force_on,
                    stm32::Status hsi_on )
{
	uint32_t value = (static_cast<uint32_t>( pll_on ) << CR::m_offset_pll_on)
	    | (static_cast<uint32_t>( rtc_prescaler ) << CR::m_offset_rtc_prescaler)
	    | (static_cast<uint32_t>( css_hse_on ) << CR::m_offset_css_hse_on)
	    | (static_cast<uint32_t>( hse_bypass ) << CR::m_offset_hse_bypass)
	    | (static_cast<uint32_t>( hse_on ) << CR::m_offset_hse_on)
	    | (static_cast<uint32_t>( msi_on ) << CR::m_offset_msi_on)
	    | (static_cast<uint32_t>( hsi_enabled ) << CR::m_offset_hsi_enabled)
	    | (static_cast<uint32_t>( hsi_divided ) << CR::m_offset_hsi_div_enabled)
	    | (static_cast<uint32_t>( hsi_force_on ) << CR::m_offset_hsi_force_on)
	    | (static_cast<uint32_t>( hsi_on ) << CR::m_offset_hsi_on);

	m_register.Set( value );
}

bool CR::IsPllReady() const
{
	uint32_t value = m_register.Read( 1, m_offset_pll_rdy );

	return (value == static_cast<uint32_t>( stm32::Status::Ready ));
}

void CR::SetPllOn( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_pll_on );
}

bool CR::IsPllOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_pll_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

void CR::SetRtcPrescaler( RtcPrescaler prescaler )
{
	uint32_t value = static_cast<uint32_t>( prescaler );
	uint32_t mask = static_cast<uint32_t>( RtcPrescaler::Mask );

	m_register.Set( value, mask, m_offset_rtc_prescaler );
}

CR::RtcPrescaler CR::GetRtcPrescaler() const
{
	uint32_t mask = static_cast<uint32_t>( RtcPrescaler::Mask );
	uint32_t value = m_register.Read( mask, m_offset_rtc_prescaler );

	return static_cast<RtcPrescaler>( value );
}

void CR::SetCssHse( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_css_hse_on );
}

bool CR::IsCssHseOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_css_hse_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

void CR::SetHseBypass( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hse_bypass );
}

bool CR::IsHseBypassOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_hse_bypass );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

bool CR::IsHseReady() const
{
	uint32_t value = m_register.Read( 1, m_offset_hse_rdy );

	return (value == static_cast<uint32_t>( stm32::Status::Ready ));
}

void CR::SetHseOn( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hse_on );
}

bool CR::IsHseOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_hse_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

bool CR::IsMsiReady() const
{
	uint32_t value = m_register.Read( 1, m_offset_msi_rdy );

	return (value == static_cast<uint32_t>( stm32::Status::Ready ));
}

void CR::SetMsiOn( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_msi_on );
}

bool CR::IsMsiOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_msi_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

void CR::SetHsiEnabled( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hsi_enabled );
}

bool CR::IsHsiEnabled() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_enabled );

	return (value == static_cast<uint32_t>( stm32::Status::Enabled ));
}

bool CR::IsHsiDivided() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_div_flag );

	return (value == static_cast<uint32_t>( stm32::Status::True ));
}

void CR::RequestHsiDivision( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hsi_div_enabled );
}

bool CR::IsHsiDivisionRequested() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_div_enabled );

	return (value == static_cast<uint32_t>( stm32::Status::True ));
}

bool CR::IsHsiReady() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_rdy );

	return (value == static_cast<uint32_t>( stm32::Status::Ready ));
}

void CR::ForceHsiOn( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hsi_force_on );
}

bool CR::IsHsiForcedOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_force_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

void CR::SetHsiOn( stm32::Status status )
{
	uint32_t value = static_cast<uint32_t>( status );

	m_register.Set( value, 1, CR::m_offset_hsi_on );
}

bool CR::IsHsiOn() const
{
	uint32_t value = m_register.Read( 1, m_offset_hsi_on );

	return (value == static_cast<uint32_t>( stm32::Status::On ));
}

} /* namespace Clock */

} /* namespace Stm32 */
