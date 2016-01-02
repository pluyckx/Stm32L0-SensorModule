/*
 * SysTick.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: pluyckx
 */

#include "SysTick.h"

extern stm32::hal::systick::systick_r r_systick;

namespace stm32
{
namespace hal
{
namespace systick
{

uint32_t const csr_mask = 0x00010007u;

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

} /* namespace systick */
} /* namespace hal */
} /* namespace stm32 */
