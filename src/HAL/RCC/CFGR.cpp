/*
 * ControlRegister.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#include "../RCC/CFGR.hpp"

#include "../RCC/clock_private.hpp"
#include "../Register32Bit.hpp"

namespace stm32
{

namespace rcc
{

extern clock_t r_clock;

uint32_t const CFGR::m_offset_mcu_clock_prescaler = 28u;
uint32_t const CFGR::m_offset_mcu_clock_selection = 24u;
uint32_t const CFGR::m_offset_pll_output_division = 22u;
uint32_t const CFGR::m_offset_pll_output_mul = 18u;
uint32_t const CFGR::m_offset_pll_source = 16u;
uint32_t const CFGR::m_offset_stop_wakup_clock = 15u;
uint32_t const CFGR::m_offset_apb_high_speed_pres = 11u;
uint32_t const CFGR::m_offset_apb_low_speed_pres = 8u;
uint32_t const CFGR::m_offset_ahb_prescaler = 4u;
uint32_t const CFGR::m_offset_sws = 2u;
uint32_t const CFGR::m_offset_sw = 0u;

uint32_t const CFGR::m_mask = 0x7FFDBFFF;

CFGR::CFGR()
		: m_register( Register32Bit( r_clock.cfgr, CFGR::m_mask ) )
{

}

void CFGR::Configure( McuClockPrescaler mcu_clk_prescaler,
                      McuClockSelection mcu_clk_sel,
                      PllDivision pll_div,
                      PllMultiplication pll_mul,
                      PllSource pll_src,
                      StopWakeUpClock wu_clk,
                      ApbHighSpeedPrescaler apb_high_pre,
                      ApbLowSpeedPrescaler apb_low_pre,
                      AhbPrescaler ahb_pre,
                      SystemClockSwitch scs )
{
	uint32_t value =
	    (static_cast<uint32_t>( mcu_clk_prescaler ) << CFGR::m_offset_mcu_clock_prescaler) | (static_cast<uint32_t>( mcu_clk_sel )
	        << CFGR::m_offset_mcu_clock_selection)
	    | (static_cast<uint32_t>( pll_div ) << CFGR::m_offset_pll_output_division)
	    | (static_cast<uint32_t>( pll_mul ) << CFGR::m_offset_pll_output_mul)
	    | (static_cast<uint32_t>( pll_src ) << CFGR::m_offset_pll_source)
	    | (static_cast<uint32_t>( wu_clk ) << CFGR::m_offset_stop_wakup_clock)
	    | (static_cast<uint32_t>( apb_high_pre ) << CFGR::m_offset_apb_high_speed_pres)
	    | (static_cast<uint32_t>( apb_low_pre ) << CFGR::m_offset_apb_low_speed_pres)
	    | (static_cast<uint32_t>( ahb_pre ) << CFGR::m_offset_ahb_prescaler)
	    | (static_cast<uint32_t>( scs ) << CFGR::m_offset_sw);
}

CFGR::McuClockPrescaler CFGR::GetMcuClockOutputPrescaler() const
{
	uint32_t mask = static_cast<uint32_t>( McuClockPrescaler::Mask );

	return static_cast<McuClockPrescaler>( m_register.Read( mask,
	                                                        CFGR::m_offset_mcu_clock_prescaler ) );
}

void CFGR::SetMcuClockOutputPrescaler( McuClockPrescaler prescaler )
{
	uint32_t mask = static_cast<uint32_t>( McuClockPrescaler::Mask );
	uint32_t value = static_cast<uint32_t>( prescaler );

	m_register.Set( value, mask, CFGR::m_offset_mcu_clock_prescaler );
}

CFGR::McuClockSelection CFGR::GetMcuClockSelection() const
{
	uint32_t mask = static_cast<uint32_t>( McuClockSelection::Mask );

	return static_cast<McuClockSelection>( m_register.Read( mask,
	                                                        CFGR::m_offset_mcu_clock_selection ) );
}

void CFGR::SetMcuClockSelection( McuClockSelection selection )
{
	uint32_t mask = static_cast<uint32_t>( McuClockPrescaler::Mask );
	uint32_t value = static_cast<uint32_t>( selection );

	m_register.Set( value, mask, CFGR::m_offset_mcu_clock_selection );
}

CFGR::PllDivision CFGR::GetPllOutputDivision() const
{
	uint32_t mask = static_cast<uint32_t>( PllDivision::Mask );

	return static_cast<PllDivision>( m_register.Read( mask,
	                                                  CFGR::m_offset_pll_output_division ) );
}

void CFGR::SetPllOutputDivision( PllDivision division )
{
	uint32_t mask = static_cast<uint32_t>( PllDivision::Mask );
	uint32_t value = static_cast<uint32_t>( division );

	m_register.Set( value, mask, CFGR::m_offset_pll_output_division );
}

CFGR::PllMultiplication CFGR::GetPllOutputMultiplication() const
{
	uint32_t mask = static_cast<uint32_t>( PllMultiplication::Mask );

	return static_cast<PllMultiplication>( m_register.Read( mask,
	                                                        CFGR::m_offset_pll_output_mul ) );
}

void CFGR::SetPllOutputMultiplication( PllMultiplication mul )
{
	uint32_t mask = static_cast<uint32_t>( PllMultiplication::Mask );
	uint32_t value = static_cast<uint32_t>( mul );

	m_register.Set( value, mask, CFGR::m_offset_pll_output_mul );
}

CFGR::PllSource CFGR::GetPllSource() const
{
	uint32_t mask = static_cast<uint32_t>( PllSource::Mask );

	return static_cast<PllSource>( m_register.Read( mask,
	                                                CFGR::m_offset_pll_source ) );
}

void CFGR::SetPllSource( PllSource source )
{
	uint32_t mask = static_cast<uint32_t>( PllSource::Mask );
	uint32_t value = static_cast<uint32_t>( source );

	m_register.Set( value, mask, CFGR::m_offset_pll_source );
}

CFGR::StopWakeUpClock CFGR::GetStopWakeUpClock() const
{
	uint32_t mask = static_cast<uint32_t>( StopWakeUpClock::Mask );

	return static_cast<StopWakeUpClock>( m_register.Read( mask,
	                                                      CFGR::m_offset_stop_wakup_clock ) );
}

void CFGR::SetStopWakeUpClock( StopWakeUpClock clock )
{
	uint32_t mask = static_cast<uint32_t>( StopWakeUpClock::Mask );
	uint32_t value = static_cast<uint32_t>( clock );

	m_register.Set( value, mask, CFGR::m_offset_stop_wakup_clock );
}

CFGR::ApbHighSpeedPrescaler CFGR::GetApbHighSpeedPrescaler() const
{
	uint32_t mask = static_cast<uint32_t>( ApbHighSpeedPrescaler::Mask );

	return static_cast<ApbHighSpeedPrescaler>( m_register.Read( mask,
	                                                            CFGR::m_offset_apb_high_speed_pres ) );
}
void CFGR::SetApbHighSpeedPrescaler( ApbHighSpeedPrescaler prescaler )
{
	uint32_t mask = static_cast<uint32_t>( ApbHighSpeedPrescaler::Mask );
	uint32_t value = static_cast<uint32_t>( prescaler );

	m_register.Set( value, mask, CFGR::m_offset_apb_high_speed_pres );
}

CFGR::ApbLowSpeedPrescaler CFGR::GetApbLowSpeedPrescaler() const
{
	uint32_t mask = static_cast<uint32_t>( ApbLowSpeedPrescaler::Mask );

	return static_cast<ApbLowSpeedPrescaler>( m_register.Read( mask,
	                                                           CFGR::m_offset_apb_low_speed_pres ) );
}

void CFGR::SetApbLowSpeedPrescaler( ApbLowSpeedPrescaler prescaler )
{
	uint32_t mask = static_cast<uint32_t>( ApbLowSpeedPrescaler::Mask );
	uint32_t value = static_cast<uint32_t>( prescaler );

	m_register.Set( value, mask, CFGR::m_offset_apb_low_speed_pres );
}

CFGR::AhbPrescaler CFGR::GetAhbPrescaler() const
{
	uint32_t mask = static_cast<uint32_t>( AhbPrescaler::Mask );

	return static_cast<AhbPrescaler>( m_register.Read( mask,
	                                                   CFGR::m_offset_ahb_prescaler ) );
}

void CFGR::SetAhbPrescaler( AhbPrescaler prescaler )
{
	uint32_t mask = static_cast<uint32_t>( AhbPrescaler::Mask );
	uint32_t value = static_cast<uint32_t>( prescaler );

	m_register.Set( value, mask, CFGR::m_offset_ahb_prescaler );
}

CFGR::SystemClockSwitch CFGR::GetSystemClockSwitchStatus() const
{
	uint32_t mask = static_cast<uint32_t>( SystemClockSwitch::Mask );

	return static_cast<SystemClockSwitch>( m_register.Read( mask,
	                                                        CFGR::m_offset_sws ) );
}

CFGR::SystemClockSwitch CFGR::GetSystemClockSwitch() const
{
	uint32_t mask = static_cast<uint32_t>( SystemClockSwitch::Mask );

	return static_cast<SystemClockSwitch>( m_register.Read( mask,
	                                                        CFGR::m_offset_sw ) );
}

void CFGR::SetSystemClockSwitch( SystemClockSwitch clock_switch )
{
	uint32_t mask = static_cast<uint32_t>( SystemClockSwitch::Mask );
	uint32_t value = static_cast<uint32_t>( clock_switch );

	m_register.Set( value, mask, CFGR::m_offset_sw );
}
}
} /* namespace Stm32 */
