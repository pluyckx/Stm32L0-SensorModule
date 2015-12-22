/*
 * Clock.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_H_
#define SRC_HAL_CLOCK_H_

#include "CR.hpp"

namespace stm32
{

namespace clock
{

class Clock
{
	public:

		Clock();

		CR *GetControlRegister();

		static Clock &GetClock();
	private:
		CR m_cr;
};

} /* namespace Clock */

} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_H_ */
