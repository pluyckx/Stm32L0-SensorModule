/*
 * SystemTime.h
 *
 *  Created on: Dec 31, 2015
 *      Author: pluyckx
 */

#ifndef SRC_DRIVERS_SYSTEMTIME_H_
#define SRC_DRIVERS_SYSTEMTIME_H_

#include <stdint.h>

extern "C"
{
void NVIC_SysTickHandler();
}

namespace stm32
{
namespace drivers
{

class SystemTime
{
	public:
		static SystemTime &GetSystemTime();

		bool Configure( uint32_t cpu_freq );
		void Enable();

		uint32_t GetTime();

		void Sleep(uint32_t ms);

		friend void ::NVIC_SysTickHandler();
	private:
		SystemTime();
		SystemTime(SystemTime &ref);

		volatile uint32_t m_time;

		static SystemTime m_systemtime;
};

} /* namespace drivers */
} /* namespace stm32 */

#endif /* SRC_DRIVERS_SYSTEMTIME_H_ */
