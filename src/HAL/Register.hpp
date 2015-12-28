/*
 * Register32Bit.hpp
 *
 *  Created on: Oct 18, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_REGISTER_HPP_
#define SRC_HAL_REGISTER_HPP_

#include "stdint.h"

namespace stm32
{

/* Implement the class in the header, this way it is optimized out when
 * optimizations are turned on.
 */

template<typename RegType, typename BitFields, typename FieldMask>
class Register
{
	public:
		inline Register( RegType &reg, RegType mask );

		inline void SetBits( BitFields value );
		inline void ClearBits( BitFields value );

		inline void Set( RegType value );
		inline void Set( RegType value, FieldMask mask );

		inline RegType GetMask();

		inline RegType Read() const;
		inline RegType Read( FieldMask mask ) const;
		inline BitFields ReadBits( BitFields fields ) const;
		inline bool AreBitsSet( BitFields fields ) const;
		inline bool AreBitsCleared( BitFields fields ) const;

	private:
		inline void SetHelper( RegType value, RegType mask );
		inline RegType ReadHelper( RegType mask ) const;

		RegType const m_mask;
		volatile RegType *m_register;
};

/* No bitfields available */
template<typename RegType, typename FieldMask>
class Register<RegType, void, FieldMask>
{
	public:
		inline Register( RegType &reg, RegType mask );

		inline void Set( RegType value );
		inline void Set( RegType value, FieldMask mask );

		inline RegType GetMask();

		inline RegType Read() const;
		inline RegType Read( FieldMask mask ) const;

	private:
		inline void SetHelper( RegType value, RegType mask );
		inline RegType ReadHelper( RegType mask ) const;

		RegType const m_mask;
		volatile RegType *m_register;
};

/* No FieldMask available */
template<typename RegType, typename BitFields>
class Register<RegType, BitFields, void>
{
	public:
		inline Register( RegType &reg, RegType mask );

		inline void SetBits( BitFields value );
		inline void ClearBits( BitFields value );

		inline void Set( RegType value );

		inline RegType GetMask();

		inline RegType Read() const;
		inline BitFields ReadBits( BitFields fields ) const;
		inline bool AreBitsSet( BitFields fields ) const;
		inline bool AreBitsCleared( BitFields fields ) const;

	private:
		inline void SetHelper( RegType value, RegType mask );
		inline RegType ReadHelper( RegType mask ) const;

		RegType const m_mask;
		volatile RegType *m_register;
};

template<typename RegType, typename BitFields, typename FieldMask>
Register<RegType, BitFields, FieldMask>::Register( RegType &reg, RegType mask )
		: m_mask( mask ), m_register( &reg )
{
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::SetBits( BitFields value )
{
	*m_register |= static_cast<RegType>( value ) & m_mask;
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::ClearBits( BitFields value )
{
	*m_register &= ~static_cast<RegType>( value );
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::Set( RegType value )
{
	SetHelper( value, m_mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::Set( RegType value,
                                                   FieldMask mask )
{
	SetHelper( value, static_cast<RegType>( mask ) );
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::GetMask()
{
	return m_mask;
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::Read() const
{
	return ReadHelper( m_mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::Read( FieldMask mask ) const
{
	return ReadHelper( static_cast<RegType>( mask ) );
}

template<typename RegType, typename BitFields, typename FieldMask>
BitFields Register<RegType, BitFields, FieldMask>::ReadBits( BitFields fields ) const
{
	return static_cast<BitFields>( ReadHelper( static_cast<RegType>( fields ) ) );
}

template<typename RegType, typename BitFields, typename FieldMask>
bool Register<RegType, BitFields, FieldMask>::AreBitsSet( BitFields fields ) const
{
	return (static_cast<BitFields>( ReadHelper( static_cast<RegType>( fields ) ) )
	    == fields);
}

template<typename RegType, typename BitFields, typename FieldMask>
bool Register<RegType, BitFields, FieldMask>::AreBitsCleared( BitFields fields ) const
{
	return (static_cast<BitFields>( ReadHelper( static_cast<RegType>( fields ) ) )
	    == 0u);
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::SetHelper( RegType value,
                                                         RegType mask )
{
	mask = mask & static_cast<RegType>( m_mask );

	value = ReadHelper( ~mask ) | (value & mask);
	*m_register = value;
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::ReadHelper( RegType mask ) const
{
	mask = static_cast<uint32_t>( m_mask ) & mask;

	return (*m_register) & mask;
}

} /* namespace stm32 */

#endif /* SRC_HAL_REGISTER_HPP_ */
