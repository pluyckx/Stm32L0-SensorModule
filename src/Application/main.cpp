#include "../HAL/RCC/RCC.hpp"
#include "../HAL/Gpio/Gpio.h"
#include "../HAL/Dbg/Debug.h"
#include "../Drivers/SystemTime.h"
#include "startup.hpp"

int main( void )
{
	InitApplication();

	stm32::hal::Debug::GetApb1FreezeRegister().SetBits( stm32::hal::Debug::Apb1FreezeFields::LpTimerStop
	    | stm32::hal::Debug::Apb1FreezeFields::Tim6Stop
	    | stm32::hal::Debug::Apb1FreezeFields::Timer2Stop
	    | stm32::hal::Debug::Apb1FreezeFields::WwdgStop
	    | stm32::hal::Debug::Apb1FreezeFields::IwdgStop );

	stm32::hal::Debug::GetApb2FreezeRegister().SetBits( stm32::hal::Debug::Apb2FreezeFields::Tim21Stop
	    | stm32::hal::Debug::Apb2FreezeFields::Tim22Stop );

	stm32::hal::RCC &clock = stm32::hal::RCC::GetClock();

	clock.GetControlRegister().SetBits( stm32::hal::cr::BitFields::HsiOutEnabled
	    | stm32::hal::cr::BitFields::HsiOn );
	clock.GetControlRegister().ClearBits( stm32::hal::cr::BitFields::HsiDividerEnabled );

	clock.GetClockConfigurationRegister().Set( static_cast<uint32_t>( stm32::hal::cfgr::SystemClockSwitchSelection::HSI ),
	                                           stm32::hal::cfgr::FieldMasks::SystemClockSwitchSelection );

	clock.GetCieRegister().ClearBits( stm32::hal::cier::BitFields::CssLse
	    | stm32::hal::cier::BitFields::HseRdy
	    | stm32::hal::cier::BitFields::HsiRdy
	    | stm32::hal::cier::BitFields::LseRdy
	    | stm32::hal::cier::BitFields::LsiRdy
	    | stm32::hal::cier::BitFields::MsiRdy
	    | stm32::hal::cier::BitFields::PllRdy );

	stm32::drivers::SystemTime &sys_time =
	    stm32::drivers::SystemTime::GetSystemTime();

	sys_time.Configure( 16000000u );
	sys_time.Enable();

	clock.GetIoPortEnableRegiser().SetBits( stm32::hal::iopenr::BitFields::PortA
	    | stm32::hal::iopenr::BitFields::PortC );

	stm32::hal::Gpio *gpio =
	    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortA );

	gpio->WriteOutput( stm32::hal::Gpio::Pin::Pin3 | stm32::hal::Gpio::Pin::Pin15,
	                   false );

	gpio->ConfigureOutput( stm32::hal::Gpio::Pin::Pin3 | stm32::hal::Gpio::Pin::Pin15,
	                       stm32::hal::Gpio::OutputType::OpenDrain,
	                       stm32::hal::Gpio::OutputSpeed::Slow,
	                       stm32::hal::Gpio::PullUpDown::None );

	stm32::hal::Gpio *gpioc =
	    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortC );

	gpioc->WriteOutput( stm32::hal::Gpio::Pin::Pin14 | stm32::hal::Gpio::Pin::Pin15,
	                    false );

	gpioc->ConfigureOutput( stm32::hal::Gpio::Pin::Pin14 | stm32::hal::Gpio::Pin::Pin15,
	                        stm32::hal::Gpio::OutputType::OpenDrain,
	                        stm32::hal::Gpio::OutputSpeed::Slow,
	                        stm32::hal::Gpio::PullUpDown::None );

	uint32_t start = sys_time.GetTime();

	for ( ;; )
	{
		if ( (sys_time.GetTime() - start) >= 1000u )
		{
			start += 1000u;

			bool new_value = !gpio->areOutputsSet( stm32::hal::Gpio::Pin::Pin3 );
			gpio->WriteOutput( stm32::hal::Gpio::Pin::Pin3, new_value );
		}
	}

	return 0;
}

extern "C"
{
void exit( void )
{
	while ( true )
	{
	}
}
}
