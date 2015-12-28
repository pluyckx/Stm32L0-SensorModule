/*
 * Clock.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_H_
#define SRC_HAL_CLOCK_H_

#include "CR.hpp"
#include "ICSCR.hpp"
#include "CFGR.hpp"
#include "CICR.hpp"
#include "CIER.hpp"
#include "CIFR.hpp"
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
		/*
		 AdvancedRegister<uint32_t, cr::FieldMasks> GetAhbEnableRegiser()
		 {
		 return AdvancedRegister<uint32_t, cr::FieldMasks>(clock_r.cr, cr::register_mask);
		 }

		 AHBRSTR *GetAhbRstRegister()
		 {
		 return &m_ahb_reset;
		 }

		 AHBSMENR *GetAhbStopModeRegister()
		 {
		 return &m_ahb_stopmode;
		 }

		 APB1ENR *GetApb1EnableRegiser()
		 {
		 return &m_apb1_enable;
		 }

		 APB1RSTR *GetApb1RstRegister()
		 {
		 return &m_apb1_reset;
		 }

		 APB1SMENR *GetApb1StopModeRegister()
		 {
		 return &m_apb1_stopmode;
		 }

		 APB2ENR *GetApb2EnableRegiser()
		 {
		 return &m_apb2_enable;
		 }

		 APB2RSTR *GetApb2RstRegister()
		 {
		 return &m_apb2_reset;
		 }

		 APB2SMENR *GetApb2StopModeRegister()
		 {
		 return &m_apb2_stopmode;
		 }

		 CCIPR *GetCcipRegister()
		 {
		 return &m_ccipr;
		 }
		 */
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
		/*
		 IOPENR *GetIoPortEnableRegiser()
		 {
		 return &io_port_enable;
		 }

		 IOPRSTR *GetIoPortRstRegister()
		 {
		 return &io_port_reset;
		 }

		 IOPSMENR *GetIoPortStopModeRegister()
		 {
		 return &io_port_stopmode;
		 }
		 */

		static RCC &GetClock();
	private:
};

} /* namespace Clock */

} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_H_ */
