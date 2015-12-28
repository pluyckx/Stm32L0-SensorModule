/*
 * Gpio.h
 *
 *  Created on: Dec 23, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_GPIO_GPIO_H_
#define SRC_HAL_GPIO_GPIO_H_

#include <stdint.h>

namespace stm32
{
namespace gpio
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
		enum class OutputType
		{
			Input = 0u, Output = 1u, Alternate = 2u, Analog = 3u
		};

		Gpio();

	private:

};

} /* namespace gpio */
} /* namespace stm32 */

#endif /* SRC_HAL_GPIO_GPIO_H_ */
