/*
 * SystemTime.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: pluyckx
 */

#include "SystemTime.h"
#include "../HAL/SysTick/SysTick.h"

namespace stm32
{
namespace drivers
{

SystemTime SystemTime::m_systemtime;

SystemTime::SystemTime()
		: m_time( 0 )
{

}

SystemTime::SystemTime(SystemTime &ref)
{
	(void)ref;
}

SystemTime &SystemTime::GetSystemTime()
{
	return m_systemtime;
}

bool SystemTime::Configure( uint32_t cpu_freq )
{
	bool ret = false;

	stm32::hal::SysTick systick = stm32::hal::SysTick::GetSysTick();

	uint32_t reload_value = cpu_freq / 1000;

	ret = systick.SetReloadValue( reload_value );

	if ( ret )
	{
		systick.ConfigureSysTick( stm32::hal::SysTick::ControlStatusBits::InterruptEnabled
		    | stm32::hal::SysTick::ControlStatusBits::ProcessorClock );
	}

	return ret;
}

void SystemTime::Enable()
{
	stm32::hal::SysTick systick = stm32::hal::SysTick::GetSysTick();

	systick.ClearCounter();
	systick.EnableSysTick();
}

uint32_t SystemTime::GetTime()
{
	return m_time;
}


void SystemTime::Sleep(uint32_t ms)
{
	uint32_t start = GetTime();

	while( GetTime() - start < ms)
	{
	}
}

} /* namespace drivers */
} /* namespace stm32 */

extern "C"
{
void NVIC_SysTickHandler()
{
	if ( stm32::hal::SysTick::GetSysTick().HasCountedDown() )
	{
		stm32::drivers::SystemTime::GetSystemTime().m_time += 1;
	}
}
}
