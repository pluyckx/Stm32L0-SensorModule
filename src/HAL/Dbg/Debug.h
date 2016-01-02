/*
 * Debug.h
 *
 *  Created on: Jan 2, 2016
 *      Author: pluyckx
 */

#ifndef SRC_HAL_DBG_DEBUG_H_
#define SRC_HAL_DBG_DEBUG_H_

#include <stdint.h>
#include "../TypeSafeBitmasks.hpp"
#include "../Register.hpp"

namespace stm32
{
namespace hal
{

struct debug_r
{
		uint32_t id_code;
		uint32_t control_register;
		uint32_t apb1_freeze_register;
		uint32_t apb2_freeze_register;
};

extern "C"
{
extern debug_r r_dbgmcu;
}

class Debug
{
	public:
		enum class ControlRegisterFields
		{
			Sleep = 1u << 0u, Stop = 1u << 1u, Standby = 1u << 2u,
		};

		enum class Apb1FreezeFields
			: uint32_t
			{
				Timer2Stop = 1u << 0u,
			Tim6Stop = 1u << 4u,
			RtcStop = 1u << 10u,
			WwdgStop = 1u << 11u,
			IwdgStop = 1u << 12u,
			I2c1Stop = 1u << 21u,
			I2c3Stop = 1u << 30u,
			LpTimerStop = 1u << 31u
		};

		enum class Apb2FreezeFields
		{
			Tim21Stop = 1u << 2u, Tim22Stop = 1u << 5u
		};

		static Register<uint32_t, ControlRegisterFields, void> GetControlRegister()
		{
			return Register<uint32_t, ControlRegisterFields, void>( r_dbgmcu
			                                                            .control_register,
			                                                        m_control_mask );
		}

		static Register<uint32_t, Apb1FreezeFields, void> GetApb1FreezeRegister()
		{
			return Register<uint32_t, Apb1FreezeFields, void>( r_dbgmcu
			                                                       .apb1_freeze_register,
			                                                   m_apb1frz_mask );
		}

		static Register<uint32_t, Apb2FreezeFields, void> GetApb2FreezeRegister()
		{
			return Register<uint32_t, Apb2FreezeFields, void>( r_dbgmcu
			                                                       .apb2_freeze_register,
			                                                   m_apb2frz_mask );
		}
	private:
		Debug();

		static uint32_t const m_control_mask = 0x00000007u;
		static uint32_t const m_apb1frz_mask = 0xC0201C11u;
		static uint32_t const m_apb2frz_mask = 0x00000024u;
};

} /* namespace hal */
} /* namespace stm32 */

template<>
struct enable_bitmask_operators<stm32::hal::Debug::ControlRegisterFields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::Debug::Apb1FreezeFields>
{
		static bool const enable = true;
};

template<>
struct enable_bitmask_operators<stm32::hal::Debug::Apb2FreezeFields>
{
		static bool const enable = true;
};

#endif /* SRC_HAL_DBG_DEBUG_H_ */
