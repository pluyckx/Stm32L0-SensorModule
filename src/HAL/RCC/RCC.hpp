/*
 * Clock.h
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_CLOCK_H_
#define SRC_HAL_CLOCK_H_

#include "../RCC/AHBENR.hpp"
#include "../RCC/AHBRSTR.hpp"
#include "../RCC/AHBSMENR.hpp"
#include "../RCC/APB1ENR.hpp"
#include "../RCC/APB1RSTR.hpp"
#include "../RCC/APB1SMENR.hpp"
#include "../RCC/APB2ENR.hpp"
#include "../RCC/APB2RSTR.hpp"
#include "../RCC/APB2SMENR.hpp"
#include "../RCC/CCIPR.h"
#include "../RCC/CFGR.hpp"
#include "../RCC/CICR.hpp"
#include "../RCC/CIER.hpp"
#include "../RCC/CIFR.hpp"
#include "../RCC/CR.hpp"
#include "../RCC/ICSCR.hpp"
#include "../RCC/IOPENR.hpp"
#include "../RCC/IOPRSTR.hpp"
#include "../RCC/IOPSMENR.hpp"

namespace stm32
{

namespace rcc
{

class RCC
{
	public:

		RCC();

		AHBENR *GetAhbEnableRegiser()
		{
			return &m_ahb_enable;
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

		CICR *GetCicRegistger()
		{
			return &m_cicr;
		}

		CIER *GetCieRegister()
		{
			return &m_cier;
		}

		CIFR *GetCifRegister()
		{
			return &m_cifr;
		}

		CR *GetControlRegister()
		{
			return &m_cr;
		}

		ICSCR *GetIcscRegister()
		{
			return &m_icscr;
		}

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

		static RCC &GetClock();
	private:
		AHBENR m_ahb_enable;
		AHBRSTR m_ahb_reset;
		AHBSMENR m_ahb_stopmode;

		APB1ENR m_apb1_enable;
		APB1RSTR m_apb1_reset;
		APB1SMENR m_apb1_stopmode;

		APB2ENR m_apb2_enable;
		APB2RSTR m_apb2_reset;
		APB2SMENR m_apb2_stopmode;

		CCIPR m_ccipr;
		CICR m_cicr;
		CIER m_cier;
		CIFR m_cifr;
		CR m_cr;
		ICSCR m_icscr;

		IOPENR io_port_enable;
		IOPRSTR io_port_reset;
		IOPSMENR io_port_stopmode;
};

} /* namespace Clock */

} /* namespace Stm32 */

#endif /* SRC_HAL_CLOCK_H_ */
