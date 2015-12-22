#include "startup.hpp"

#include "../HAL/Clock/Clock.hpp"

int main( void )
{
	InitApplication();
	stm32::clock::Clock clock = stm32::clock::Clock::GetClock();

	for ( ;; )
	{

	}

	return 0;
}
