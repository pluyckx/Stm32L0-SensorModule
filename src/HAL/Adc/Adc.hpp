/*
 * Adc.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: pluyckx
 */

#ifndef SRC_HAL_ADC_ADC_HPP_
#define SRC_HAL_ADC_ADC_HPP_

#include "stdint.h"

namespace stm32
{
namespace hal
{

namespace adc
{
enum class InterruptFields
{
	Ready = 1u << 0u,
	EndOfSampling = 1u << 1u,
	EndOfConversion = 1u << 2u,
	EndOfSequence = 1u << 3u,
	Overrun = 1u << 4u,
	Watchdog = 1u << 7u,
	EndOfCalibration = 1u << 11u
};

enum class ControlFields : uint32_t
{
	Enable = 1u << 0u,
	Disasble = 1u << 1u,
	StartConvertion = 1u << 2u,
	StopConvertion = 1u << 4u,
	EnableRegulator = 1u << 28u,
	Calibrate = 1u << 31u
};

enum class Configuration1
{
	DmaEnabled = 1u << 0u,
	DmaCircular = 1u << 1u,
	BackwardScan = 1u << 2u,
	LeftAliogn = 1u << 5u,
	OverwriteData = 1u << 12u,
	ContinuousMode = 1u << 13u,
	WaitMode = 1u << 14u,
	AutoOff = 1u << 15u,
	DiscontinuousMode = 1u << 16u,
	WatchdogSingleChannel = 1u << 22u,
	WatchdogEnable = 1u << 23u
};
}

class Adc
{
	public:

	private:
		Adc();
};

} /* namespace hal */
} /* namespace stm32 */

#endif /* SRC_HAL_ADC_ADC_HPP_ */
