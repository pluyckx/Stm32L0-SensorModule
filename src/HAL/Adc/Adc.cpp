/*
 * Adc.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: pluyckx
 */

#include "Adc.hpp"

namespace stm32
{
namespace hal
{

Adc Adc::m_adc;

Adc::Adc()
{
	// TODO Auto-generated constructor stub

}

Adc &Adc::GetInstance()
{
	return m_adc;
}

} /* namespace hal */
} /* namespace stm32 */
