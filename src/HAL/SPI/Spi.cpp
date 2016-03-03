/*
 * Spi.cpp

 *
 *  Created on: Feb 21, 2016
 *      Author: pluyckx
 */

#include <stdint.h>
#include "Spi.h"
#include "../Gpio/Gpio.h"
#include "../../Drivers/SystemTime.h"
#include "../Register.hpp"

namespace stm32
{
namespace spi
{
struct SpiRegisters
{
		uint32_t CR1; /* 0x00 */
		uint32_t CR2; /* 0x04 */
		uint32_t SR; /* 0x08 */
		uint32_t DR; /* 0x0C */
		uint32_t CRCPR; /* 0x10 */
		uint32_t RXCRCR; /* 0x14 */
		uint32_t TXCRCR; /* 0x18 */
		uint32_t I2SCFGR; /* 0x1C */
		uint32_t SPI_I2SPR; /* 0x20 */
};
}
}

extern stm32::spi::SpiRegisters r_spi1;

extern volatile uint32_t r_nvic;

namespace stm32
{
namespace spi
{

Spi Spi::m_interfaces[] = { Spi( &r_spi1 ) };

Spi::Spi( void *registers )
		: m_rxBuff( 0 ), m_txBuff( 0 ), m_registers( registers )
{
}

Spi *Spi::GetSpi( SpiSelection spi )
{
	Spi *interface = 0;

	if ( spi < SpiSelection::Count )
	{
		interface = &Spi::m_interfaces[static_cast<uint32_t>( spi )];
	}

	return interface;
}

void Spi::SetBuffer( Buffer *rxBuff, Buffer *txBuff )
{
	m_rxBuff = rxBuff;
	m_txBuff = txBuff;

	m_rxBuff->pos = m_txBuff->pos = m_rxBuff->idx = m_txBuff->idx = 0u;
}

void Spi::Config( ControlBits1 cr1,
                  ControlBits2 cr2,
                  SpiBaudrate baudrate,
                  InterruptBits interrupts )
{
	Register<uint32_t, ControlBits1, ControlRegisterMasks> cr1Reg( static_cast<SpiRegisters*>( m_registers )
	                                                                   ->CR1,
	                                                               cr1_mask );
	Register<uint32_t, ControlBits2, void> cr2Config( static_cast<SpiRegisters*>( m_registers )
	                                                      ->CR2,
	                                                  cr2_mask );
	Register<uint32_t, InterruptBits, void> cr2Interrupts( static_cast<SpiRegisters*>( m_registers )
	                                                           ->CR2,
	                                                       cr2_mask );

	cr1Reg.Set( static_cast<uint32_t>( baudrate ) << 3,
	            ControlRegisterMasks::Baudrate );
	cr1Reg.SetBits( cr1 );

	cr2Config.SetBits( cr2 );
	cr2Interrupts.SetBits( interrupts );
}

void Spi::Interrupts( InterruptBits interrupts, bool enabled )
{
	Register<uint32_t, InterruptBits, void> reg( static_cast<SpiRegisters*>( m_registers )
	                                                 ->CR2,
	                                             cr2_mask );

	if ( enabled )
	{
		reg.SetBits( interrupts );
	}
	else
	{
		reg.ClearBits( interrupts );
	}
}

void Spi::Enable()
{
	Register<uint32_t, ControlBits1, void> cr1Reg( static_cast<SpiRegisters*>( m_registers )
	                                                   ->CR1,
	                                               cr1_mask );

	cr1Reg.SetBits( ControlBits1::EnablePeripheral );

	r_nvic |= 1 << 25;
}

void Spi::Disable()
{
	Register<uint32_t, ControlBits1, void> cr1Reg( static_cast<SpiRegisters*>( m_registers )
	                                                   ->CR1,
	                                               cr1_mask );

	cr1Reg.ClearBits( ControlBits1::EnablePeripheral );
}

void Spi::CrcNext()
{
	Register<uint32_t, ControlBits1, void> cr1Reg( static_cast<SpiRegisters*>( m_registers )
	                                                   ->CR1,
	                                               cr1_mask );

	cr1Reg.SetBits( ControlBits1::CrcTransferNext );
}

uint32_t Spi::Read( uint8_t buff[], uint32_t length )
{
	uint32_t toCopy = (length < m_rxBuff->pos) ? length : m_rxBuff->pos;

	for ( uint32_t i = 0; i < toCopy; i++ )
	{
		buff[i] = m_rxBuff->m_buff[i];
	}

	for ( uint32_t i = toCopy; i < m_rxBuff->pos; i++ )
	{
		m_rxBuff->m_buff[i - toCopy] = m_rxBuff->m_buff[i];
	}

	m_rxBuff->pos -= toCopy;

	return toCopy;
}

bool Spi::Write( uint8_t buff[], uint32_t length )
{
	bool ret = false;

	if ( !IsBusy() && (length < m_txBuff->length) )
	{
		stm32::hal::Gpio *gpio =
		    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortB );
		stm32::drivers::SystemTime &systime =
		    stm32::drivers::SystemTime::GetSystemTime();

		for ( uint32_t i = 0; i < length; i++ )
		{
			m_txBuff->m_buff[i] = buff[i];
		}

		m_txBuff->pos = length;
		m_txBuff->idx = 0;

		gpio->WriteOutput( stm32::hal::Gpio::Pin::Pin0, true );
		uint32_t start = systime.GetTime();

		while ( systime.GetTime() - start < 1 )
		{
		}
		gpio->WriteOutput( stm32::hal::Gpio::Pin::Pin0, false );
		while ( systime.GetTime() - start < 1 )
		{
		}

		Interrupts( InterruptBits::TxEmpty, true );
	}

	return ret;
}

bool Spi::HasDataReceived()
{
	return m_rxBuff->pos > 0;
}

bool Spi::IsBusy()
{
	Register<uint32_t, Status, void> reg( static_cast<SpiRegisters*>( m_registers )
	                                          ->SR,
	                                      sr_mask );

	return (m_txBuff->pos > 0) || (reg.AreBitsSet( Status::Busy ));
}

void Spi::HandleInterrupt()
{
	SpiRegisters *regs = static_cast<SpiRegisters*>( m_registers );
	uint32_t status = regs->SR;
	int32_t ch = -1;

	if ( status & static_cast<uint32_t>( Status::Overrun ) )
	{
		ch = static_cast<SpiRegisters*>( m_registers )->DR;
		volatile uint32_t dummy = regs->SR;
		(void) dummy;
	}

	if ( status & static_cast<uint32_t>( Status::CrcError ) )
	{
		regs->SR = 0;
	}

	if ( status & static_cast<uint32_t>( Status::TxEmpty ) )
	{
		if ( m_txBuff->idx < m_txBuff->pos )
		{
			regs->DR = m_txBuff->m_buff[m_txBuff->idx];
			m_txBuff->idx += 1;
		}
		else
		{
			Interrupts( InterruptBits::TxEmpty, false );
			m_txBuff->idx = m_txBuff->pos = 0u;
		}
	}

	if ( status & static_cast<uint32_t>( Status::RxNotEmpyt ) )
	{
		ch = (int32_t) regs->DR;
	}

	if ( ch != -1 )
	{
		if ( m_rxBuff->pos < m_rxBuff->length )
		{
			m_rxBuff->m_buff[m_rxBuff->idx] = (uint8_t) ch;
			m_rxBuff->idx += 1;
			m_rxBuff->pos = m_rxBuff->idx;
		}
	}
}

} /* namespace spi */
} /* namespace stm32 */

extern "C"
{
void NVIC_Spi1Handler( void )
{
	{
		using namespace stm32::spi;

		Spi *spi = Spi::GetSpi( SpiSelection::Spi1 );

		if ( spi )
		{
			spi->HandleInterrupt();
		}
	}
}
}

