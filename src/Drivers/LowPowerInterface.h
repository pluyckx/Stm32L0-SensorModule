/*
 * LowPowerInterface.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_DRIVERS_LOWPOWERINTERFACE_H_
#define SRC_DRIVERS_LOWPOWERINTERFACE_H_

#include "stdint.h"
#include "../HAL/user_assert.hpp"

namespace Stm32
{
namespace Clock
{

class LowPowerInterface
{
	public:
		LowPowerInterface();
		virtual ~LowPowerInterface();

		virtual bool EnterLowPower() = 0;
		virtual bool ExitLowPower() = 0;

	protected:
		bool IsInUse() const
		{
			return m_use_counter > 0;
		}

		void Use()
		{
			m_use_counter += 1;
		}

		void Release()
		{
			m_use_counter -= 1;

			assert( m_use_counter >= 0 );
		}

	private:
		int32_t m_use_counter;
};

} /* namespace Clock */
} /* namespace Stm32 */

#endif /* SRC_DRIVERS_LOWPOWERINTERFACE_H_ */
