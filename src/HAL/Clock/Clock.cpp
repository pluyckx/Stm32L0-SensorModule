/*
 * Clock.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#include "Clock.hpp"

namespace stm32
{

namespace clock
{

static Clock clock;

Clock::Clock()
{
}

CR *Clock::GetControlRegister()
{
	return &m_cr;
}


Clock &Clock::GetClock()
{
	return clock;
}

}

} /* namespace Stm32 */
