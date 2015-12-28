#include "../HAL/RCC/RCC.hpp"
#include "startup.hpp"

int main( void )
{
	InitApplication();
	stm32::rcc::RCC clock = stm32::rcc::RCC::GetClock();

	clock.GetControlRegister().SetBits( stm32::rcc::cr::BitFields::HsiOutEnabled
	    | stm32::rcc::cr::BitFields::HsiOn );

	clock.GetCieRegister().ClearBits( stm32::rcc::cier::BitFields::CssLse
	    | stm32::rcc::cier::BitFields::HseRdy
	    | stm32::rcc::cier::BitFields::HsiRdy
	    | stm32::rcc::cier::BitFields::LseRdy
	    | stm32::rcc::cier::BitFields::LsiRdy
	    | stm32::rcc::cier::BitFields::MsiRdy
	    | stm32::rcc::cier::BitFields::PllRdy );

	for ( ;; )
	{

	}

	return 0;
}
