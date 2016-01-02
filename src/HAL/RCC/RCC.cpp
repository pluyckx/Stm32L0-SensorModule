/*
 * Clock.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#include "../RCC/RCC.hpp"

namespace stm32
{

namespace hal
{

static RCC clock;

RCC::RCC()
{
}


RCC &RCC::GetClock()
{
	return clock;
}

}

} /* namespace Stm32 */
