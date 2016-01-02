#include "../HAL/RCC/RCC.hpp"
#include "../HAL/Gpio/Gpio.h"
#include "../Drivers/SystemTime.h"
#include "startup.hpp"

int main( void )
{
	InitApplication();
	stm32::rcc::RCC &clock = stm32::rcc::RCC::GetClock();

	clock.GetControlRegister().SetBits( stm32::rcc::cr::BitFields::HsiOutEnabled
	    | stm32::rcc::cr::BitFields::HsiOn );
	clock.GetControlRegister().ClearBits( stm32::rcc::cr::BitFields::HsiDividerEnabled );

	clock.GetClockConfigurationRegister().Set( static_cast<uint32_t>( stm32::rcc::cfgr::SystemClockSwitchSelection::HSI ),
	                                           stm32::rcc::cfgr::FieldMasks::SystemClockSwitchSelection );

	clock.GetCieRegister().ClearBits( stm32::rcc::cier::BitFields::CssLse
	    | stm32::rcc::cier::BitFields::HseRdy
	    | stm32::rcc::cier::BitFields::HsiRdy
	    | stm32::rcc::cier::BitFields::LseRdy
	    | stm32::rcc::cier::BitFields::LsiRdy
	    | stm32::rcc::cier::BitFields::MsiRdy
	    | stm32::rcc::cier::BitFields::PllRdy );

	stm32::drivers::SystemTime &sys_time =
	    stm32::drivers::SystemTime::GetSystemTime();

	sys_time.Configure( 16000000u );
	sys_time.Enable();

	clock.GetIoPortEnableRegiser().SetBits( stm32::rcc::iopenr::BitFields::PortA
	    | stm32::rcc::iopenr::BitFields::PortC );

	stm32::gpio::Gpio *gpio =
	    stm32::gpio::Gpio::GetGpio( stm32::gpio::Port::PortA );

	gpio->WriteOutput( stm32::gpio::Pin::Pin3, true );

	gpio->ConfigureOutput( stm32::gpio::Pin::Pin3,
	                       stm32::gpio::OutputType::OpenDrain,
	                       stm32::gpio::OutputSpeed::Slow,
	                       stm32::gpio::PullUpDown::None );

	stm32::gpio::Gpio *gpioc =
	    stm32::gpio::Gpio::GetGpio( stm32::gpio::Port::PortC );

	gpioc->WriteOutput( stm32::gpio::Pin::Pin14 | stm32::gpio::Pin::Pin15,
	                    false );

	gpioc->ConfigureOutput( stm32::gpio::Pin::Pin14 | stm32::gpio::Pin::Pin15,
	                        stm32::gpio::OutputType::OpenDrain,
	                        stm32::gpio::OutputSpeed::Slow,
	                        stm32::gpio::PullUpDown::None );

	uint32_t start = sys_time.GetTime();

	for ( ;; )
	{
		if ( (sys_time.GetTime() - start) >= 1000u )
		{
			start += 1000u;

			bool new_value = !gpio->areOutputsSet( stm32::gpio::Pin::Pin3 );
			gpio->WriteOutput( stm32::gpio::Pin::Pin3, new_value );
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
