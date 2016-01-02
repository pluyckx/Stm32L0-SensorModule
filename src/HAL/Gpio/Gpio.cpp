/*
 * Gpio.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: pluyckx
 */

#include "Gpio.h"

extern stm32::hal::gpio_r r_gpioa;
extern stm32::hal::gpio_r r_gpiob;
extern stm32::hal::gpio_r r_gpioc;
extern stm32::hal::gpio_r r_gpiod;
extern stm32::hal::gpio_r r_gpioe;

namespace stm32
{
namespace hal
{

static uint32_t const s_mode_mask = 0x3u;
static uint32_t const s_pullup_down_mask = 0x3u;
static uint32_t const s_output_speed_mask = 0x3u;

Gpio Gpio::m_gpios[static_cast<uint32_t>( Port::Count )] = { Gpio( &r_gpioa ),
                                                             Gpio( &r_gpiob ),
                                                             Gpio( &r_gpioc ),
                                                             Gpio( &r_gpiod ),
                                                             Gpio( &r_gpioe ) };

Gpio::Gpio( gpio_r * const gpio )
		: m_gpio( gpio )
{

}

Gpio *Gpio::GetGpio( Port port )
{
	if ( port < Port::Count )
	{
		return &m_gpios[static_cast<uint32_t>( port )];
	}
	else
	{
		return 0;
	}
}

void Gpio::ConfigureInput( Pin pins, PullUpDown pullup_down )
{
	uint32_t selected_pins = static_cast<uint32_t>( pins );
	uint32_t pin_pos = 0u;

	uint32_t mode = static_cast<uint32_t>( Mode::Input );
	uint32_t mode_value = 0u;
	uint32_t mode_mask = 0u;

	uint32_t pullup_down_bits = static_cast<uint32_t>( pullup_down );
	uint32_t pullup_down_value = 0u;
	uint32_t pullup_down_mask = 0u;

	while ( selected_pins != 0 )
	{
		if ( (selected_pins & 1) == 1 )
		{
			mode_value |= (mode << (pin_pos * 2u));
			mode_mask |= (s_mode_mask << (pin_pos * 2u));

			pullup_down_value |= (pullup_down_bits << (pin_pos * 2u));
			pullup_down_mask |= (s_pullup_down_mask << (pin_pos * 2u));
		}

		selected_pins >>= 1;
		pin_pos += 1;
	}

	uint32_t tmp_mode = m_gpio->mode & ~mode_mask;
	uint32_t tmp_pullup_down = m_gpio->pull_up_down & ~mode_mask;

	tmp_mode |= mode_value;
	tmp_pullup_down |= pullup_down_value;

	m_gpio->mode = tmp_mode;
	m_gpio->pull_up_down = pullup_down_value;
}

void Gpio::ConfigureOutput( Pin pins,
                            OutputType type,
                            OutputSpeed speed,
                            PullUpDown pullup_down )
{
	uint32_t selected_pins = static_cast<uint32_t>( pins );
	uint32_t pin_pos = 0u;

	uint32_t mode = static_cast<uint32_t>( Mode::Output );
	uint32_t mode_value = 0u;
	uint32_t mode_mask = 0u;

	uint32_t pullup_down_bits = static_cast<uint32_t>( pullup_down );
	uint32_t pullup_down_value = 0u;
	uint32_t pullup_down_mask = 0u;

	uint32_t output_speed_bits = static_cast<uint32_t>( speed );
	uint32_t output_speed_value = 0u;
	uint32_t output_speed_mask = 0u;

	while ( selected_pins != 0 )
	{
		if ( (selected_pins & 1) == 1 )
		{
			mode_value |= (mode << (pin_pos * 2u));
			mode_mask |= (s_mode_mask << (pin_pos * 2u));

			pullup_down_value |= (pullup_down_bits << (pin_pos * 2u));
			pullup_down_mask |= (s_pullup_down_mask << (pin_pos * 2u));

			output_speed_value |= (output_speed_bits << (pin_pos * 2u));
			output_speed_mask |= (s_output_speed_mask << (pin_pos * 2u));
		}

		selected_pins >>= 1;
		pin_pos += 1;
	}

	uint32_t tmp_mode = m_gpio->mode & ~mode_mask;
	uint32_t tmp_pullup_down = m_gpio->pull_up_down & ~mode_mask;
	uint32_t output_type_value = m_gpio->output_type
	    & ~static_cast<uint32_t>( pins );
	uint32_t output_speed = m_gpio->output_speed
	    & ~static_cast<uint32_t>( pins );

	tmp_mode |= mode_value;
	tmp_pullup_down |= pullup_down_value;

	if ( type == OutputType::OpenDrain )
	{
		output_type_value |= static_cast<uint32_t>( pins );
	}

	m_gpio->mode = tmp_mode;
	m_gpio->output_type = output_type_value;
	m_gpio->pull_up_down = pullup_down_value;
	m_gpio->output_speed = output_speed;
}

uint32_t Gpio::ReadInput( Pin pins )
{
	return m_gpio->input_data & static_cast<uint32_t>( pins );
}

uint32_t Gpio::ReadOutput( Pin pins )
{
	return m_gpio->output_data & static_cast<uint32_t>( pins );
}

bool Gpio::areInputsSet( Pin pins )
{
	uint32_t tmp = static_cast<uint32_t>( pins );

	return (ReadInput( pins ) == tmp);
}

bool Gpio::areOutputsSet( Pin pins )
{
	uint32_t tmp = static_cast<uint32_t>( pins );

	return (ReadOutput( pins ) == tmp);
}

void Gpio::WriteOutput( Pin pins, bool value )
{
	uint32_t tmp = static_cast<uint32_t>( pins );
	uint32_t new_value = ReadOutput( Pin::All );

	if(value)
	{
		new_value |= tmp;
	}
	else
	{
		new_value &= ~tmp;
	}

	m_gpio->output_data = new_value;
}

}
/* namespace gpio */
} /* namespace stm32 */
