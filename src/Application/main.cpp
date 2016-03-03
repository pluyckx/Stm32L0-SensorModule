#include <limits>
#include "../HAL/Register.hpp"
#include "../HAL/RCC/RCC.hpp"
#include "../HAL/Gpio/Gpio.h"
#include "../HAL/Dbg/Debug.h"
#include "../Drivers/SystemTime.h"
#include "../HAL/Adc/Adc.hpp"
#include "../HAL/SPI/Spi.h"
#include "startup.hpp"

constexpr uint32_t buf_size = 1000u;

static uint16_t s_min = std::numeric_limits<uint16_t>::max();
static uint16_t s_max = std::numeric_limits<uint16_t>::min();
static uint16_t s_adc_buf[buf_size];
static uint32_t s_index = 0u;
static uint32_t s_start = 0u;
static uint32_t s_end = 0u;
static uint32_t s_diff = 0u;

static uint16_t s_lightAdc = 0u;

static void InitTempModule( void );

int main( void )
{
	stm32::spi::Buffer rx, tx;
	uint8_t rxBuf[256];
	uint8_t txBuf[256];

	rx.m_buff = rxBuf;
	rx.length = sizeof(rxBuf);
	tx.m_buff = txBuf;
	tx.length = sizeof(txBuf);

	InitApplication();

	stm32::hal::Debug::GetApb1FreezeRegister().SetBits( stm32::hal::Debug::Apb1FreezeFields::LpTimerStop
	    | stm32::hal::Debug::Apb1FreezeFields::Tim6Stop
	    | stm32::hal::Debug::Apb1FreezeFields::Timer2Stop
	    | stm32::hal::Debug::Apb1FreezeFields::WwdgStop
	    | stm32::hal::Debug::Apb1FreezeFields::IwdgStop );

	stm32::hal::Debug::GetApb2FreezeRegister().SetBits( stm32::hal::Debug::Apb2FreezeFields::Tim21Stop
	    | stm32::hal::Debug::Apb2FreezeFields::Tim22Stop );

	stm32::hal::RCC &clock = stm32::hal::RCC::GetClock();

	clock.GetControlRegister().SetBits( stm32::hal::cr::BitFields::HsiOutEnabled
	    | stm32::hal::cr::BitFields::HsiOn );
	clock.GetControlRegister().ClearBits( stm32::hal::cr::BitFields::HsiDividerEnabled );

	clock.GetClockConfigurationRegister().Set( static_cast<uint32_t>( stm32::hal::cfgr::SystemClockSwitchSelection::HSI ),
	                                           stm32::hal::cfgr::FieldMasks::SystemClockSwitchSelection );

	clock.GetApb2EnableRegiser().SetBits( stm32::hal::apb2enr::BitFields::Adc
	    | stm32::hal::apb2enr::BitFields::Spi1
	    | stm32::hal::apb2enr::BitFields::SysCfg );

	clock.GetCieRegister().ClearBits( stm32::hal::cier::BitFields::CssLse
	    | stm32::hal::cier::BitFields::HseRdy
	    | stm32::hal::cier::BitFields::HsiRdy
	    | stm32::hal::cier::BitFields::LseRdy
	    | stm32::hal::cier::BitFields::LsiRdy
	    | stm32::hal::cier::BitFields::MsiRdy
	    | stm32::hal::cier::BitFields::PllRdy );

	stm32::drivers::SystemTime &sys_time =
	    stm32::drivers::SystemTime::GetSystemTime();

	sys_time.Configure( 16000000u );
	sys_time.Enable();

	while ( sys_time.GetTime() < 5000 )
	{

	}

	clock.GetIoPortEnableRegiser().SetBits( stm32::hal::iopenr::BitFields::PortA
	    | stm32::hal::iopenr::BitFields::PortB
	    | stm32::hal::iopenr::BitFields::PortC );

	stm32::hal::Gpio *gpioa =
	    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortA );
	stm32::hal::Gpio *gpioc =
	    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortC );
	stm32::hal::Gpio *gpiob =
	    stm32::hal::Gpio::GetGpio( stm32::hal::Gpio::Port::PortB );

	{
		using namespace stm32::hal;

		gpioa->WriteOutput( stm32::hal::Gpio::Pin::Pin15,
		                    false );

		gpioa->WriteOutput( stm32::hal::Gpio::Pin::Pin3,
		                    true );

		gpioa->ConfigureOutput( stm32::hal::Gpio::Pin::Pin3 | stm32::hal::Gpio::Pin::Pin15,
		                        stm32::hal::Gpio::OutputType::OpenDrain,
		                        stm32::hal::Gpio::OutputSpeed::Slow,
		                        stm32::hal::Gpio::PullUpDown::None );

		gpioc->WriteOutput( stm32::hal::Gpio::Pin::Pin14 | stm32::hal::Gpio::Pin::Pin15,
		                    false );

		gpioc->ConfigureOutput( stm32::hal::Gpio::Pin::Pin14 | stm32::hal::Gpio::Pin::Pin15,
		                        stm32::hal::Gpio::OutputType::OpenDrain,
		                        stm32::hal::Gpio::OutputSpeed::Slow,
		                        stm32::hal::Gpio::PullUpDown::None );

		gpiob->WriteOutput( Gpio::Pin::Pin6, false );

		gpiob->ConfigureOutput( Gpio::Pin::Pin6,
		                        Gpio::OutputType::OpenDrain,
		                        Gpio::OutputSpeed::Slow,
		                        Gpio::PullUpDown::None );

		gpiob->WriteOutput( Gpio::Pin::Pin7, true );
		gpiob->ConfigureOutput( Gpio::Pin::Pin7,
		                        Gpio::OutputType::OpenDrain,
		                        Gpio::OutputSpeed::Fastest,
		                        Gpio::PullUpDown::None );

		InitTempModule();

		volatile uint32_t *iser_addr = reinterpret_cast<uint32_t*>( 0xE000E100u );
		*iser_addr &= ~(1 << 7);

		sys_time.Sleep( 1500 );

		gpiob->WriteOutput( Gpio::Pin::Pin7, false );

		sys_time.Sleep( 5 );

		gpiob->WriteOutput( Gpio::Pin::Pin7, true );

		*reinterpret_cast<volatile uint32_t*>( 0x40011400u ) |= 1;

		uint32_t *pr_addr = reinterpret_cast<uint32_t*>( 0X40010414u );
		*pr_addr |= 1 << 7u;
		*iser_addr |= 1 << 7u;
	}

	{
		using namespace stm32::spi;
		using namespace stm32::hal;

		Spi *spi = Spi::GetSpi( SpiSelection::Spi1 );

		spi->SetBuffer( &rx, &tx );

		ControlBits1 cr1 = ControlBits1::Master | ControlBits1::SoftwareSlave
		                   | ControlBits1::InternalSlaveSelect;
		ControlBits2 cr2 = static_cast<ControlBits2>( 0 );
		InterruptBits interrupts = InterruptBits::Error | InterruptBits::RxNotEmpty;

		spi->Config( cr1, cr2, SpiBaudrate::Div16, interrupts );

		gpioa->WriteOutput( Gpio::Pin::Pin5 | Gpio::Pin::Pin7, false );

		gpioa->ConfigureOutput( Gpio::Pin::Pin5 | Gpio::Pin::Pin7,
		                        Gpio::OutputType::PushPull,
		                        Gpio::OutputSpeed::Fastest,
		                        Gpio::PullUpDown::None );

		gpioa->WriteOutput( Gpio::Pin::Pin5 | Gpio::Pin::Pin7, true );

		gpioa->ConfigureInput( Gpio::Pin::Pin6, Gpio::PullUpDown::None );

		gpioa->ConfigureAlternate( Gpio::Pin::Pin5 | Gpio::Pin::Pin6
		                           | Gpio::Pin::Pin7,
		                           Gpio::Alternative::Alt0 );

		gpiob->WriteOutput( Gpio::Pin::Pin0, false );
		gpiob->ConfigureOutput( Gpio::Pin::Pin0,
		                        Gpio::OutputType::PushPull,
		                        Gpio::OutputSpeed::Slow,
		                        Gpio::PullUpDown::None );

		gpioa->WriteOutput( Gpio::Pin::Pin4, true );
		gpioa->ConfigureOutput( Gpio::Pin::Pin4,
		                        Gpio::OutputType::PushPull,
		                        Gpio::OutputSpeed::Slow,
		                        Gpio::PullUpDown::None );

		spi->Enable();
		uint8_t data[] = { 0x0, 0x0 };
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x1;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x2;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x3;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x4;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x5;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x6;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}

		data[0] = 0x7;
		spi->Write( data, sizeof(data) );

		while ( spi->IsBusy() )
		{
		}
	}

	stm32::hal::Adc adc = stm32::hal::Adc::GetInstance();

	{
		using namespace stm32::hal::adc;

		adc.GetInterruptEnableRegister().ClearBits( InterruptFields::All );
		adc.GetConfiguration1Register().ClearBits( Configuration1Fields::WatchdogEnable
		    | Configuration1Fields::ContinuousMode
		    | Configuration1Fields::LeftAlign
		    | Configuration1Fields::DmaEnabled );
		adc.GetConfiguration1Register().Set( static_cast<uint32_t>( Resolution::Bits12 ),
		                                     Configuration1Masks::Resolution );

		adc.GetConfiguration2Register().ClearBits( Configuration2Fields::OversamplerEnabled );
		adc.GetConfiguration2Register().Set( static_cast<uint32_t>( ClockMode::AdcClock ),
		                                     Configuration2Masks::ClockMode );
		adc.GetSampleTimeRegister().Set( static_cast<uint32_t>( SampleTimeSelection::AdcClockCycles160_5 ) );
		adc.GetChannelSelectionRegister().ClearBits( ChannelSelectionFields::All );
		adc.GetChannelSelectionRegister().SetBits( ChannelSelectionFields::Channel0 );

		adc.GetControlRegister().SetBits( ControlFields::Calibrate );

		while ( adc.GetControlRegister().AreBitsSet( ControlFields::Calibrate ) )
		{
		}

		adc.GetControlRegister().SetBits( ControlFields::Enable );

		while ( adc.GetInterruptStatusRegister().AreBitsCleared( InterruptFields::Ready ) )
		{
		}

		adc.GetInterruptStatusRegister().SetBits( InterruptFields::Ready );
	}

	adc.GetControlRegister().SetBits( stm32::hal::adc::ControlFields::StartConvertion );

	uint16_t adcData = 0u;

	for ( ;; )
	{
		if ( s_lightAdc >= 2048 )
		{
			bool new_value = gpiob->ReadInput( stm32::hal::Gpio::Pin::Pin7 );
			gpioa->WriteOutput( stm32::hal::Gpio::Pin::Pin3, new_value );
		}

		{
			using namespace stm32::hal::adc;

			if ( adc.GetInterruptStatusRegister().AreBitsSet( InterruptFields::EndOfConversion ) )
			{
				adc.GetInterruptStatusRegister().SetBits( InterruptFields::EndOfConversion );
				adcData = static_cast<uint16_t>( adc.GetData().Read() );

				if ( adc.GetChannelSelectionRegister().AreBitsSet( ChannelSelectionFields::Channel0 ) )
				{
					s_lightAdc = adcData;
					if ( s_lightAdc < 2048 )
					{
						gpioa->WriteOutput( stm32::hal::Gpio::Pin::Pin3, false );
					}

					adc.GetChannelSelectionRegister().ClearBits( ChannelSelectionFields::Channel0 );
					adc.GetChannelSelectionRegister().SetBits( ChannelSelectionFields::Channel1 );
				}
				else if ( adc.GetChannelSelectionRegister().AreBitsSet( ChannelSelectionFields::Channel1 ) )
				{
					if ( adcData < s_min )
					{
						s_min = adcData;
					}

					if ( adcData > s_max )
					{
						s_max = adcData;
					}

					s_adc_buf[s_index] = adcData;
					s_index += 1;
					if ( s_index == buf_size )
					{
						s_end = sys_time.GetTime();
						s_diff = s_end - s_start;
						s_index = 0u;
						s_start = sys_time.GetTime();
					}

					adc.GetChannelSelectionRegister().ClearBits( ChannelSelectionFields::Channel1 );
					adc.GetChannelSelectionRegister().SetBits( ChannelSelectionFields::Channel0 );
				}
				else
				{
					adc.GetChannelSelectionRegister().ClearBits( ChannelSelectionFields::All );
					adc.GetChannelSelectionRegister().SetBits( ChannelSelectionFields::Channel0 );
				}

				adc.GetControlRegister().SetBits( ControlFields::StartConvertion );
			}
		}
	}

	return 0;
}

static void InitTempModule( void )
{
	using namespace stm32;
	uint32_t *cr1_addr = reinterpret_cast<uint32_t*>( 0x40011400u );
	uint32_t *cr2_addr = reinterpret_cast<uint32_t*>( 0x40011404u );
	uint32_t *smcr_addr = reinterpret_cast<uint32_t*>( 0x40011408u );
	uint32_t *dier_addr = reinterpret_cast<uint32_t*>( 0x4001140Cu );
	uint32_t *sr_addr = reinterpret_cast<uint32_t*>( 0x40011410u );
	uint32_t *egr_addr = reinterpret_cast<uint32_t*>( 0x40011414u );
	uint32_t *ccmr1_addr = reinterpret_cast<uint32_t*>( 0x40011418u );
	uint32_t *ccer_addr = reinterpret_cast<uint32_t*>( 0x40011420u );
	uint32_t *cnt_addr = reinterpret_cast<uint32_t*>( 0x40011424u );
	uint32_t *psc_addr = reinterpret_cast<uint32_t*>( 0x40011428u );
	uint32_t *arr_addr = reinterpret_cast<uint32_t*>( 0x4001142Cu );
	uint32_t *ccr1_addr = reinterpret_cast<uint32_t*>( 0x40011434u );
	uint32_t *ccr2_addr = reinterpret_cast<uint32_t*>( 0x40011438u );
	uint32_t *orr_addr = reinterpret_cast<uint32_t*>( 0x40011450u );

	uint32_t *iser_addr = reinterpret_cast<uint32_t*>( 0xE000E100u );
	uint32_t *exticr2_addr = reinterpret_cast<uint32_t*>( 0x4001000Cu );
	uint32_t *imr_addr = reinterpret_cast<uint32_t*>( 0X40010400u );
	uint32_t *rtsr_addr = reinterpret_cast<uint32_t*>( 0X40010408u );
	uint32_t *ftsr_addr = reinterpret_cast<uint32_t*>( 0x4001040Cu );

	Register<uint32_t, void, void> cr1( *cr1_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> cr2( *cr2_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> smcr( *smcr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> dier( *dier_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> sr( *sr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> egr( *egr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> ccmr1( *ccmr1_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> ccer( *ccer_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> cnt( *cnt_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> psc( *psc_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> arr( *arr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> ccr1( *ccr1_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> ccr2( *ccr2_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> orr( *orr_addr, 0xFFFFFFFFu );

	Register<uint32_t, void, void> iser( *iser_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> exticr2( *exticr2_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> imr( *imr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> rtsr( *rtsr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> ftsr( *ftsr_addr, 0xFFFFFFFFu );

	cr2.Set( 0 );
	dier.Set( 0 );
	sr.Set( 0 );
	egr.Set( 0 );
	ccmr1.Set( 0 );
	ccer.Set( 0 );
	cnt.Set( 0 );
	psc.Set( 15 );
	arr.Set( 0 );
	cr1.Set( 0 );

	exticr2.Set( 1 << 12 );
	imr.Set( 1 << 7 );
	rtsr.Set( 1 << 7 );
	ftsr.Set( 1 << 7 );

	iser.Set( 1 << 7 );
}

static uint32_t s_buff[200];
static uint32_t s_idx = 0u;

extern "C"
{
void NVIC_EXTI2Handler( void );
void NVIC_EXTI2Handler( void )
{
	using namespace stm32;

	uint32_t *cnt_addr = reinterpret_cast<uint32_t*>( 0x40011424u );
	uint32_t *pr_addr = reinterpret_cast<uint32_t*>( 0X40010414u );
	Register<uint32_t, void, void> pr( *pr_addr, 0xFFFFFFFFu );
	Register<uint32_t, void, void> cnt( *cnt_addr, 0xFFFFFFFFu );

	uint32_t value = pr.Read();

	if ( value & (1 << 7) )
	{
		pr.Set( 1 << 7 );
		s_buff[s_idx] = cnt.Read();

		if( (s_idx + 1) < (sizeof(s_buff)/sizeof(s_buff[0])) )
		{
			s_idx += 1;
		}
	}
}
}

extern "C"
{
void exit( void )
{
	while ( true )
	{
	}
}
}
