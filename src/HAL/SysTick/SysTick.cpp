/*
 * SysTick.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: pluyckx
 */

#include "SysTick.h"

namespace stm32
{
namespace hal
{

extern "C"
{
systick_r r_systick;
}

uint32_t const csr_mask = 0x00010007u;
uint32_t const cvr_mask = 0x00FFFFFFu;

SysTick SysTick::m_systick;

SysTick::SysTick()
{

}

SysTick &SysTick::GetSysTick()
{
	return m_systick;
}

void SysTick::ConfigureSysTick( ControlStatusBits configuration )
{
	Register<uint32_t, ControlStatusBits, void> reg( r_systick.csr, csr_mask );
	reg.SetBits( configuration );
}

void SysTick::EnableSysTick()
{
	Register<uint32_t, ControlStatusBits, void> reg( r_systick.csr, csr_mask );
	reg.SetBits( ControlStatusBits::Enable );
}

void SysTick::DisableSysTick()
{
	Register<uint32_t, ControlStatusBits, void> reg( r_systick.csr, csr_mask );
	reg.ClearBits( ControlStatusBits::Enable );
}

bool SysTick::HasCountedDown()
{
	Register<uint32_t, ControlStatusBits, void> reg( r_systick.csr, csr_mask );
	return reg.AreBitsSet( ControlStatusBits::CountFlag );
}

void SysTick::ClearCounter()
{
	Register<uint32_t, void, void> reg( r_systick.cvr, cvr_mask );
	reg.Set( 0u );
}

bool SysTick::SetReloadValue( uint32_t value )
{
	if ( value < reload_value_max )
	{
		r_systick.rvr = value;
		return true;
	}
	else
	{
		return false;
	}
}

uint32_t SysTick::GetCurrentValue() const
{
	return r_systick.cvr;
}

} /* namespace hal */
} /* namespace stm32 */
