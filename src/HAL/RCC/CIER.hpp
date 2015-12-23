/*
 * CIER.h
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_RCC_CIER_HPP_
#define SRC_HAL_RCC_CIER_HPP_

#include "stdint.h"
#include "../Register32Bit.hpp"
#include "../GenericTypes.hpp"

namespace stm32
{
namespace rcc
{

class CIER
{
	public:
		CIER();

		void Configure( stm32::Status lse_css,
		                stm32::Status msi_rdy,
		                stm32::Status pll_rdy,
		                stm32::Status hse_rdy,
		                stm32::Status hsi_rdy,
		                stm32::Status lse_rdy,
		                stm32::Status lsi_rdy );

		bool IsLseCssSet() const;
		bool IsMsiRdySet() const;
		bool IsPllRdySet() const;
		bool IsHseRdySet() const;
		bool IsHsiRdySet() const;
		bool IsLseRdySet() const;
		bool IsLsiRdySet() const;

		void SetLseCss( stm32::Status status );
		void SetMsiRdy( stm32::Status status );
		void SetPllRdy( stm32::Status status );
		void SetHseRdy( stm32::Status status );
		void SetHsiRdy( stm32::Status status );
		void SetLseRdy( stm32::Status status );
		void SetLsiRdy( stm32::Status status );

	private:
		inline void SetStatusBit( stm32::Status, uint32_t offset );

	private:
		Register32Bit m_register;

		static uint32_t const m_offset_lse_css;
		static uint32_t const m_offset_msi_rdy;
		static uint32_t const m_offset_pll_rdy;
		static uint32_t const m_offset_hse_rdy;
		static uint32_t const m_offset_hsi_rdy;
		static uint32_t const m_offset_lse_rdy;
		static uint32_t const m_offset_lsi_rdy;

		static uint32_t const m_mask;
};

}; /* namespace Clock */
}; /* namespace Stm32 */

#endif /* SRC_HAL_RCC_CIER_HPP_ */
