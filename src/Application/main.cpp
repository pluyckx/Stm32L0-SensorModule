#include "../HAL/RCC/RCC.hpp"
#include "startup.hpp"


int main( void )
{
	InitApplication();
	stm32::rcc::RCC clock = stm32::rcc::RCC::GetClock();

	for ( ;; )
	{

	}

	return 0;
}
