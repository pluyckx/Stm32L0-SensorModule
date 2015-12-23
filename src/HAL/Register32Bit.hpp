/*
 * Register32Bit.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_REGISTER32BIT_HPP_
#define SRC_HAL_REGISTER32BIT_HPP_

#include "stdint.h"

namespace stm32
{

/* Implement the class in the header, this way it is optimized out when
 * optimizations are turned on.
 */

class Register32Bit
{
	public:
		inline Register32Bit( uint32_t &reg, uint32_t mask );

		inline void SetBits( uint32_t value );
		inline void SetBits( uint32_t value, uint32_t mask );
		inline void SetBits( uint32_t value, uint32_t mask, uint32_t offset );
		inline void ClearBits( uint32_t value );
		inline void ClearBits( uint32_t value, uint32_t mask );
		inline void ClearBits( uint32_t value, uint32_t mask, uint32_t offset );

		inline void Set( uint32_t value );
		inline void Set( uint32_t value, uint32_t mask );
		inline void Set( uint32_t value, uint32_t mask, uint32_t offset );

		inline uint32_t GetMask();

		inline uint32_t Read() const;
		inline uint32_t Read( uint32_t mask ) const;
		inline uint32_t Read( uint32_t mask, uint32_t offset ) const;

	private:
		uint32_t const m_mask;
		volatile uint32_t *m_register;
};

Register32Bit::Register32Bit( uint32_t &reg, uint32_t mask )
		: m_mask( mask ), m_register( &reg )
{
}

void Register32Bit::SetBits( uint32_t value )
{
	*m_register |= (value & m_mask);
}

void Register32Bit::SetBits( uint32_t value, uint32_t mask )
{
	SetBits( value & mask );
}

void Register32Bit::SetBits( uint32_t value, uint32_t mask, uint32_t offset )
{
	SetBits( value << offset, mask << offset );
}

void Register32Bit::ClearBits( uint32_t value )
{
	uint32_t old = *m_register;
	old &= ((~value) & m_mask);

	*m_register = old;
}

void Register32Bit::ClearBits( uint32_t value, uint32_t mask )
{
	ClearBits( value & mask );
}

void Register32Bit::ClearBits( uint32_t value, uint32_t mask, uint32_t offset )
{
	ClearBits( value << offset, mask << offset );
}

void Register32Bit::Set( uint32_t value )
{
	*m_register = (value & m_mask);
}

void Register32Bit::Set( uint32_t value, uint32_t mask )
{
	value = Read( ~mask ) | (value & mask);
	Set( value );
}

void Register32Bit::Set( uint32_t value, uint32_t mask, uint32_t offset )
{
	Set( value << offset, mask << offset );
}

uint32_t Register32Bit::GetMask()
{
	return m_mask;
}

uint32_t Register32Bit::Read() const
{
	return Read( m_mask );
}

uint32_t Register32Bit::Read( uint32_t mask ) const
{
	return ((*m_register) & m_mask) & mask;
}

uint32_t Register32Bit::Read( uint32_t mask, uint32_t offset ) const
{
	return Read( mask << offset ) >> offset;
}

} /* namespace stm32 */

#endif /* SRC_HAL_REGISTER32BIT_HPP_ */
