/*
 * Adc.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: pluyckx
 */

#ifndef SRC_HAL_ADC_ADC_HPP_
#define SRC_HAL_ADC_ADC_HPP_

#include "stdint.h"
#include "../TypeSafeBitmasks.hpp"
#include "../Register.hpp"

namespace stm32
{
namespace hal
{

namespace adc
{

constexpr uint32_t isr_mask = 0x0000089F;
constexpr uint32_t ier_mask = 0x0000089F;
constexpr uint32_t cr_mask = 0x90000017;
constexpr uint32_t cfgr1_mask = 0x7CC1FDFF;
constexpr uint32_t cfgr2_mask = 0xC00003FD;
constexpr uint32_t smpr_mask = 0x00000007;
constexpr uint32_t tr_mask = 0x0FFF0FFF;
constexpr uint32_t chselr_mask = 0x0007FFFF;
constexpr uint32_t dr_mask = 0x0000FFFF;
constexpr uint32_t calfact_mask = 0x0000007F;
constexpr uint32_t ccr_mask = 0x02FC0000;

struct adc_t
{
		volatile uint32_t isr;         /* 0x00 */
		volatile uint32_t ier;         /* 0x04 */
		volatile uint32_t cr;          /* 0x08 */
		volatile uint32_t cfgr1;       /* 0x0C */
		volatile uint32_t cfgr2;       /* 0x10 */
		volatile uint32_t smpr;        /* 0x14 */
		volatile uint32_t res1[2];     /* 0x18 0x1C */
		volatile uint32_t tr;          /* 0x20 */
		volatile uint32_t res2;        /* 0x24 */
		volatile uint32_t chselr;      /* 0x28 */
		volatile uint32_t res3[5];     /* 0x2C 0x30 0x34 0x38 0x3C */
		volatile uint32_t dr;          /* 0x40 */
		volatile uint32_t res4;        /* 0x44 */
		volatile uint32_t calfact;     /* 0x48 */
		volatile uint32_t res5[147];   /* 0x4C - 0x304 */
		volatile uint32_t ccr;         /* 0x308 */
};

extern "C"
{
extern stm32::hal::adc::adc_t r_adc;
}

enum class InterruptFields
{
	Ready = 1u << 0u,
	EndOfSampling = 1u << 1u,
	EndOfConversion = 1u << 2u,
	EndOfSequence = 1u << 3u,
	Overrun = 1u << 4u,
	Watchdog = 1u << 7u,
	EndOfCalibration = 1u << 11u,

	All = Ready | EndOfSampling | EndOfConversion | EndOfSequence | Overrun
	      | Watchdog | EndOfCalibration
};

enum class ControlFields
	: uint32_t
	{
		Enable = 1u << 0u,
	Disasble = 1u << 1u,
	StartConvertion = 1u << 2u,
	StopConvertion = 1u << 4u,
	EnableRegulator = 1u << 28u,
	Calibrate = 1u << 31u
};

enum class Configuration1Fields
{
	DmaEnabled = 1u << 0u,
	DmaCircular = 1u << 1u,
	BackwardScan = 1u << 2u,
	LeftAlign = 1u << 5u,
	OverwriteData = 1u << 12u,
	ContinuousMode = 1u << 13u,
	WaitMode = 1u << 14u,
	AutoOff = 1u << 15u,
	DiscontinuousMode = 1u << 16u,
	WatchdogSingleChannel = 1u << 22u,
	WatchdogEnable = 1u << 23u
};

enum class Configuration1Masks
{
	WatchdogChannel = 0x70000000,
	ExternalTriggerPrio = 0x00000C00,
	ExternalTrigger = 0x000001C0,
	Resolution = 0x00000018
};

enum class WatchdogChannel
{
	Channel0 = 0,
	Channel1,
	Channel2,
	Channel3,
	Channel4,
	Channel5,
	Channel6,
	Channel7,
	Channel8,
	Channel9,
	Channel10,
	Channel11,
	Channel12,
	Channel13,
	Channel14,
	Channel15,
	Channel16,
	Channel17,
	Channel18
};

enum class ExternalTriggerPrio
{
	Disabled = 0, RisingEdge, FallingEdge, BothEdge
};

enum class ExternalTrigger
{
	Trigger0 = 0,
	Trigger1,
	Trigger2,
	Trigger3,
	Trigger4,
	Trigger5,
	Trigger6,
	Trigger7
};

enum class Resolution
{
	Bits12 = 0, Bits10, Bits8, Bits6
};

enum class Configuration2Fields
{
	TriggeredOversampling = 1u << 9u, OversamplerEnabled = 1u << 0u
};

enum class Configuration2Masks : uint32_t
{
	ClockMode = 0xC0000000, OversamplingShift = 0xF << 5, OversamplingRatio = 0x7
	    << 2
};

enum class ClockMode
{
	AdcClock = 0, PClock_2, PClock_4, PClock
};

enum class OversamplingShift
{
	NoShift = 0,
	Shift1Bit,
	Shift2Bit,
	Shift3Bit,
	Shift4Bit,
	Shift5Bit,
	Shift6Bit,
	Shift7Bit,
	Shift8Bit,
};

enum class OversamplingRatio
{
	Time2 = 0, Time4, Time8, Time16, Time32, Time64, Time128, Time256
};

enum class SampleTimeMasks
{
	SampleTimeSelection = 0x7 << 0
};

enum class SampleTimeSelection
{
	AdcClockCycles1_5 = 0,
	AdcClockCycles3_5,
	AdcClockCycles7_5,
	AdcClockCycles12_5,
	AdcClockCycles19_5,
	AdcClockCycles39_5,
	AdcClockCycles79_5,
	AdcClockCycles160_5,
};

enum class WatchdogThresholdMasks
{
	HigherThreshold = 0xFFF << 16, LowerThreashold = 0xFFF << 0
};

enum class ChannelSelectionFields
{
	Channel0 = 1 << 0,
	Channel1 = 1 << 1,
	Channel2 = 1 << 2,
	Channel3 = 1 << 3,
	Channel4 = 1 << 4,
	Channel5 = 1 << 5,
	Channel6 = 1 << 6,
	Channel7 = 1 << 7,
	Channel8 = 1 << 8,
	Channel9 = 1 << 9,
	Channel10 = 1 << 10,
	Channel11 = 1 << 11,
	Channel12 = 1 << 12,
	Channel13 = 1 << 13,
	Channel14 = 1 << 14,
	Channel15 = 1 << 15,
	Channel16 = 1 << 16,
	Channel17 = 1 << 17,
	Channel18 = 1 << 18,

	All = 0x0007FFFF
};

enum class DataMasks
{
	Data = 0xFFFF << 0
};

enum class CalibrationMasks
{
	CalibrationFactor = 0x7F << 0
};

enum class CommonConfigurationFields
{
	LowFrequencyModeEnable = 1 << 25,
	TemperatureSensorEnable = 1 << 23,
	VrefEnable = 1 << 22
};

enum class CommonConfigurationMasks
{
	AdcPrescaler = 0xF << 18
};

enum class AdcPrescaler
{
	Div1 = 0,
	Div2,
	Div4,
	Div6,
	Div8,
	Div10,
	Div12,
	Div16,
	Div32,
	Div64,
	Div128,
	Div256
};
}

class Adc
{
	public:
		static Adc &GetInstance();

		inline Register<uint32_t, adc::InterruptFields, void> GetInterruptStatusRegister() const;
		inline Register<uint32_t, adc::InterruptFields, void> GetInterruptEnableRegister() const;
		inline Register<uint32_t, adc::ControlFields, void> GetControlRegister() const;
		inline Register<uint32_t, adc::Configuration1Fields,
		    adc::Configuration1Masks> GetConfiguration1Register() const;
		inline Register<uint32_t, adc::Configuration2Fields,
		    adc::Configuration2Masks> GetConfiguration2Register() const;
		inline Register<uint32_t, void, adc::SampleTimeMasks> GetSampleTimeRegister() const;
		inline Register<uint32_t, void, adc::WatchdogThresholdMasks> GetWatchdogThresholdRegister() const;
		inline Register<uint32_t, adc::ChannelSelectionFields, void> GetChannelSelectionRegister() const;
		inline Register<uint32_t, void, adc::DataMasks> GetData() const;
		inline Register<uint32_t, void, adc::CalibrationMasks> GetCalibratorFactorRegister() const;
		inline Register<uint32_t, adc::CommonConfigurationFields,
		    adc::CommonConfigurationMasks> GetCommonConfigurationRegister() const;

	private:
		Adc();

		static Adc m_adc;
};

inline Register<uint32_t, adc::InterruptFields, void> Adc::GetInterruptStatusRegister() const
{
	Register<uint32_t, adc::InterruptFields, void> reg( adc::r_adc.isr,
	                                                    adc::isr_mask );
	return reg;
}

inline Register<uint32_t, adc::InterruptFields, void> Adc::GetInterruptEnableRegister() const
{
	Register<uint32_t, adc::InterruptFields, void> reg( adc::r_adc.ier,
	                                                    adc::ier_mask );
	return reg;
}

inline Register<uint32_t, adc::ControlFields, void> Adc::GetControlRegister() const
{
	Register<uint32_t, adc::ControlFields, void> reg( adc::r_adc.cr,
	                                                  adc::cr_mask );
	return reg;
}

inline Register<uint32_t, adc::Configuration1Fields, adc::Configuration1Masks> Adc::GetConfiguration1Register() const
{
	Register<uint32_t, adc::Configuration1Fields, adc::Configuration1Masks> reg( adc::r_adc
	                                                                                 .cfgr1,
	                                                                             adc::cfgr1_mask );
	return reg;
}

inline Register<uint32_t, adc::Configuration2Fields, adc::Configuration2Masks> Adc::GetConfiguration2Register() const
{
	Register<uint32_t, adc::Configuration2Fields, adc::Configuration2Masks> reg( adc::r_adc
	                                                                                 .cfgr2,
	                                                                             adc::cfgr2_mask );
	return reg;
}

inline Register<uint32_t, void, adc::SampleTimeMasks> Adc::GetSampleTimeRegister() const
{
	Register<uint32_t, void, adc::SampleTimeMasks> reg( adc::r_adc.smpr,
	                                                    adc::smpr_mask );
	return reg;
}

inline Register<uint32_t, void, adc::WatchdogThresholdMasks> Adc::GetWatchdogThresholdRegister() const
{
	Register<uint32_t, void, adc::WatchdogThresholdMasks> reg( adc::r_adc.tr,
	                                                           adc::tr_mask );
	return reg;
}

inline Register<uint32_t, adc::ChannelSelectionFields, void> Adc::GetChannelSelectionRegister() const
{
	Register<uint32_t, adc::ChannelSelectionFields, void> reg( adc::r_adc.chselr,
	                                                           adc::chselr_mask );
	return reg;
}

inline Register<uint32_t, void, adc::DataMasks> Adc::GetData() const
{
	Register<uint32_t, void, adc::DataMasks> reg( adc::r_adc.dr, adc::dr_mask );
	return reg;
}

inline Register<uint32_t, void, adc::CalibrationMasks> Adc::GetCalibratorFactorRegister() const
{
	Register<uint32_t, void, adc::CalibrationMasks> reg( adc::r_adc.calfact,
	                                                     adc::calfact_mask );
	return reg;
}

inline Register<uint32_t, adc::CommonConfigurationFields,
    adc::CommonConfigurationMasks> Adc::GetCommonConfigurationRegister() const
{
	Register<uint32_t, adc::CommonConfigurationFields,
	    adc::CommonConfigurationMasks> reg( adc::r_adc.ccr, adc::ccr_mask );

	return reg;
}

} /* namespace hal */
} /* namespace stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::adc::InterruptFields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::adc::ChannelSelectionFields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::adc::CommonConfigurationFields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::adc::Configuration1Fields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::adc::Configuration2Fields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::adc::ControlFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_ADC_ADC_HPP_ */
