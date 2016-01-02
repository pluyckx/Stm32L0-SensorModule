/*
 * Gpio.h
 *
 *  Created on: Dec 23, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_GPIO_GPIO_H_
#define SRC_HAL_GPIO_GPIO_H_

#include <stdint.h>
#include "../TypeSafeBitmasks.hpp"

namespace stm32
{
namespace hal
{

struct gpio_r
{
		uint32_t mode; /* 0x00 */
		uint32_t output_type; /* 0x04 */
		uint32_t output_speed; /* 0x08 */
		uint32_t pull_up_down; /* 0x0c */
		uint32_t input_data; /* 0x10 */
		uint32_t output_data; /* 0x14 */
		uint32_t output_bits; /* 0x18 */
		uint32_t configuration_lock; /* 0x1c */
		uint32_t alternate_func_low; /* 0x20 */
		uint32_t alternate_func_high; /* 0x24 */
		uint32_t bit_reset; /* 0x28 */
};

class Gpio
{
	public:
		enum class Pin
		{
			Pin0 = 1u << 0u,
			Pin1 = 1u << 1u,
			Pin2 = 1u << 2u,
			Pin3 = 1u << 3u,
			Pin4 = 1u << 4u,
			Pin5 = 1u << 5u,
			Pin6 = 1u << 6u,
			Pin7 = 1u << 7u,
			Pin8 = 1u << 8u,
			Pin9 = 1u << 9u,
			Pin10 = 1u << 10u,
			Pin11 = 1u << 11u,
			Pin12 = 1u << 12u,
			Pin13 = 1u << 13u,
			Pin14 = 1u << 14u,
			Pin15 = 1u << 15u,

			All = 0x0000FFFFu
		};

		enum class Mode
		{
			Input = 0, Output, Alternative, Analog
		};

		enum class OutputType
		{
			PushPull = 0x0, OpenDrain = 0x1
		};

		enum class OutputSpeed
		{
			Slow = 0, Medium, Fast, Fastest
		};

		enum class PullUpDown
		{
			None = 0, PullUp, PullDown
		};

		enum class Alternative
		{
			Alt0 = 0, Alt1, Alt2, Alt3, Alt4, Alt5, Alt6, Alt7
		};

		enum class Port
		{
			PortA = 0, PortB, PortC, PortD, PortE, Count
		};

		static Gpio *GetGpio( Port port );

		void ConfigureInput( Pin pins, PullUpDown pullup_down );
		void ConfigureOutput( Pin pins,
		                      OutputType type,
		                      OutputSpeed speed,
		                      PullUpDown pullup_down );

		uint32_t ReadInput( Pin pins );
		uint32_t ReadOutput( Pin pins );
		bool areInputsSet( Pin pins );
		bool areOutputsSet( Pin pins );
		void WriteOutput( Pin pins, bool value );

	private:
		Gpio( gpio_r * const gpio );

		gpio_r * const m_gpio;

		static Gpio m_gpios[static_cast<uint32_t>( Port::Count )];
};

} /* namespace gpio */
} /* namespace stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::Gpio::Pin>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_GPIO_GPIO_H_ */
