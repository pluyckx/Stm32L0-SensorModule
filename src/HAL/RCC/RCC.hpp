/*
 * Clock.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_H_
#define SRC_HAL_CLOCK_H_

#include "AHBENR.hpp"
#include "AHBRSTR.hpp"
#include "AHBSMENR.hpp"

#include "APB1ENR.hpp"
#include "APB1RSTR.hpp"
#include "APB1SMENR.hpp"

#include "APB2ENR.hpp"
#include "APB2RSTR.hpp"
#include "APB2SMENR.hpp"

#include "CCIPR.h"
#include "CFGR.hpp"

#include "CICR.hpp"
#include "CIER.hpp"
#include "CIFR.hpp"

#include "CR.hpp"
#include "CSR.h"
#include "ICSCR.hpp"

#include "IOPENR.hpp"
#include "IOPRSTR.hpp"
#include "IOPSMENR.hpp"

#include "../Register.hpp"
#include "clock_private.hpp"

extern stm32::rcc::clock_t r_clock;

namespace stm32
{

namespace rcc
{

class RCC
{
	public:

		RCC();

		Register<uint32_t, ahbenr::BitFields, void> GetAhbEnableRegiser()
		{
			return Register<uint32_t, ahbenr::BitFields, void>( r_clock.ahbenr,
			                                                    ahbenr::register_mask );
		}

		Register<uint32_t, ahbrstr::BitFields, void> GetAhbRstRegister()
		{
			return Register<uint32_t, ahbrstr::BitFields, void>( r_clock.ahbrstr,
			                                                     ahbrstr::register_mask );
		}

		Register<uint32_t, ahbsmenr::BitFields, void> GetAhbStopModeRegister()
		{
			return Register<uint32_t, ahbsmenr::BitFields, void>( r_clock.ahbsmenr,
			                                                      ahbsmenr::register_mask );
		}

		Register<uint32_t, apb1enr::BitFields, void> GetApb1EnableRegiser()
		{
			return Register<uint32_t, apb1enr::BitFields, void>( r_clock.apb1enr,
			                                                     apb1enr::register_mask );
		}

		Register<uint32_t, apb1rstr::BitFields, void> GetApb1RstRegister()
		{
			return Register<uint32_t, apb1rstr::BitFields, void>( r_clock.apb1rstr,
			                                                      apb1rstr::register_mask );
		}

		Register<uint32_t, apb1rstr::BitFields, void> GetApb1StopModeRegister()
		{
			return Register<uint32_t, apb1rstr::BitFields, void>( r_clock.apb1smenr,
			                                                      apb1smenr::register_mask );
		}

		Register<uint32_t, apb2enr::BitFields, void> GetApb2EnableRegiser()
		{
			return Register<uint32_t, apb2enr::BitFields, void>( r_clock.apb2enr,
			                                                     apb2enr::register_mask );
		}

		Register<uint32_t, apb2rstr::BitFields, void> GetApb2RstRegister()
		{
			return Register<uint32_t, apb2rstr::BitFields, void>( r_clock.apb2rstr,
			                                                      apb2rstr::register_mask );
		}

		Register<uint32_t, apb2smenr::BitFields, void> GetApb2StopModeRegister()
		{
			return Register<uint32_t, apb2smenr::BitFields, void>( r_clock.apb2smenr,
			                                                       apb2smenr::register_mask );
		}

		Register<uint32_t, void, ccipr::FieldMasks> GetCcipRegister()
		{
			return Register<uint32_t, void, ccipr::FieldMasks>( r_clock.ccipr,
			                                                    ccipr::register_mask );
		}

		Register<uint32_t, cicr::BitFields, void> GetCicRegister()
		{
			return Register<uint32_t, cicr::BitFields, void>( r_clock.cicr,
			                                                  cicr::register_mask );
		}

		Register<uint32_t, cier::BitFields, void> GetCieRegister()
		{
			return Register<uint32_t, cier::BitFields, void>( r_clock.cier,
			                                                  cier::register_mask );
		}

		Register<uint32_t, cifr::BitFields, void> GetCifRegister()
		{
			return Register<uint32_t, cifr::BitFields, void>( r_clock.cifr,
			                                                  cifr::register_mask );
		}

		Register<uint32_t, cr::BitFields, cr::FieldMasks> GetControlRegister()
		{
			return Register<uint32_t, cr::BitFields, cr::FieldMasks>( r_clock.cr,
			                                                          cr::register_mask );
		}

		Register<uint32_t, void, icscr::FieldMasks> GetIcscRegister()
		{
			return Register<uint32_t, void, icscr::FieldMasks>( r_clock.icscr,
			                                                    icscr::register_mask );
		}

		Register<uint32_t, cfgr::BitFields, cfgr::FieldMasks> GetClockConfigurationRegister()
		{
			return Register<uint32_t, cfgr::BitFields, cfgr::FieldMasks>( r_clock.cfgr,
			                                                              cfgr::register_mask );
		}

		Register<uint32_t, iopenr::BitFields, void> GetIoPortEnableRegiser()
		{
			return Register<uint32_t, iopenr::BitFields, void>( r_clock.iopenr,
			                                                    iopenr::register_mask );
		}

		Register<uint32_t, ioprstr::BitFields, void> GetIoPortRstRegister()
		{
			return Register<uint32_t, ioprstr::BitFields, void>( r_clock.ioprstr,
			                                                     ioprstr::register_mask );
		}

		Register<uint32_t, iopsmenr::BitFields, void> GetIoPortStopModeRegister()
		{
			return Register<uint32_t, iopsmenr::BitFields, void>( r_clock.iopsmenr,
			                                                      iopsmenr::register_mask );
		}

		static RCC &GetClock();
	private:
};

} /* namespace Clock */

} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_H_ */
