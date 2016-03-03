/*
 * Spi.h
 *
 *  Created on: Feb 21, 2016
 *      Author: pluyckx
 */

#ifndef SRC_HAL_SPI_SPI_H_
#define SRC_HAL_SPI_SPI_H_

#include "../TypeSafeBitmasks.hpp"

extern "C"
{
void NVIC_Spi1Handler( void );
}

namespace stm32
{
namespace spi
{

constexpr uint32_t cr1_mask = 0x0000FFFF;
constexpr uint32_t cr2_mask = 0x000000F7;
constexpr uint32_t sr_mask = 0x000001FF;
constexpr uint32_t dr_mask = 0x0000FFFF;
constexpr uint32_t crcpr_mask = 0x0000FFFF;
constexpr uint32_t rxcrcr_mask = 0x0000FFFF;
constexpr uint32_t txcrcr_mask = 0x0000FFFF;
constexpr uint32_t i2scfgr_mask = 0x00000FBF;
constexpr uint32_t i2spr_mask = 0x000003FF;

enum class SpiSelection
{
	Spi1 = 0, Count
};

enum class ControlBits1
{
	BidirectionalMode = 1 << 15,
	BidirectionOutputEnabled = 1 << 14,
	CrcEnabled = 1 << 13,
	CrcTransferNext = 1 << 12,
	DataFrame16Bit = 1 << 11,
	ReceiveOnly = 1 << 10,
	SoftwareSlave = 1 << 9,
	InternalSlaveSelect = 1 << 8,
	LsbFirst = 1 << 7,
	EnablePeripheral = 1 << 6,
	Master = 1 << 2,
	ClockTo1Idle = 1 << 1,
	SecondClockIsData = 1 << 0
};

enum class InterruptBits
{
	TxEmpty = 1 << 7, RxNotEmpty = 1 << 6, Error = 1 << 5
};

enum class ControlBits2
{
	TiMode = 1 << 4,
	SsOutputEnabled = 1 << 2,
	TxDmaEnabled = 1 << 1,
	RxDmaEnabled = 1 << 0
};

enum class Status
{
	FrameError = 1 << 8,
	Busy = 1 << 7,
	Overrun = 1 << 6,
	ModeFault = 1 << 5,
	CrcError = 1 << 4,
	Underrun = 1 << 3,
	ChannelRight = 1 << 2,
	TxEmpty = 1 << 1,
	RxNotEmpyt = 1 << 0
};

enum class ControlRegisterMasks
{
	Baudrate = 0x7 << 3
};

enum class SpiBaudrate
{
	Div2 = 0, Div4, Div8, Div16, Div32, Div64, Div128, Div256, Count
};

/* TODO: add I2S */

struct Buffer
{
		uint8_t *m_buff;
		uint32_t length;
		uint32_t pos;
		uint32_t idx;
};

class Spi
{
	public:
		static Spi *GetSpi( SpiSelection spi );

		void SetBuffer( Buffer *rx_buff, Buffer *tx_buff );

		void Config( ControlBits1 cr1,
		             ControlBits2 cr2,
		             SpiBaudrate baudrate,
		             InterruptBits interrupts );

		void Interrupts( InterruptBits interrupts, bool enabled );

		void Enable();
		void Disable();

		void CrcNext();

		uint32_t Read( uint8_t buff[], uint32_t length );
		bool Write( uint8_t buff[], uint32_t length );

		bool HasDataReceived();

		bool IsBusy();

		void HandleInterrupt();

	private:
		Spi( void *registers );

		Buffer *m_rxBuff;
		Buffer *m_txBuff;
		void *m_registers;

		static Spi m_interfaces[];
};

} /* namespace spi */
} /* namespace stm32 */

template<>
struct enable_bitmask_operators<stm32::spi::ControlBits1>
{
		static bool const enable = true;
};
template<>
struct enable_bitmask_operators<stm32::spi::ControlBits2>
{
		static bool const enable = true;
};
template<>
struct enable_bitmask_operators<stm32::spi::InterruptBits>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_SPI_SPI_H_ */
