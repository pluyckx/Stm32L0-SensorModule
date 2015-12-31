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

template<typename RegType, typename BitFields, typename FieldMask>
class Register;

/* declare functions that implement the necessary functionality. These
 * functions are used by the classes, declared after further. This setup
 * is used to not copy/paste the code.
 */
template<typename RegType, typename BitFields, typename FieldMask>
inline void setBits( Register<RegType, BitFields, FieldMask> &reg,
                     BitFields bits );

template<typename RegType, typename BitFields, typename FieldMask>
inline void clearBits( Register<RegType, BitFields, FieldMask> &reg,
                       BitFields bits );

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg, RegType value );

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg,
                 RegType value,
                 FieldMask mask );

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg,
                 RegType value,
                 RegType mask );

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg );

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg,
                     FieldMask mask );

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg,
                     RegType mask );

template<typename RegType, typename BitFields, typename FieldMask>
inline BitFields readBits( Register<RegType, BitFields, FieldMask> &reg,
                           BitFields bits );

template<typename RegType, typename BitFields, typename FieldMask>
inline bool areBitsSet( Register<RegType, BitFields, FieldMask> &reg,
                        BitFields bits );

template<typename RegType, typename BitFields, typename FieldMask>
inline bool areBitsCleared( Register<RegType, BitFields, FieldMask> &reg,
                            BitFields bits );

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

		friend void setBits<RegType, BitFields, FieldMask>( Register<RegType,
		                                                        BitFields, FieldMask> &,
		                                                    BitFields );
		friend void clearBits<RegType, BitFields, FieldMask>( Register<RegType,
		                                                          BitFields,
		                                                          FieldMask> &,
		                                                      BitFields );
		friend void set<RegType, BitFields, FieldMask>( Register<RegType, BitFields,
		                                                    FieldMask> &,
		                                                RegType,
		                                                RegType );
		friend RegType read<RegType, BitFields, FieldMask>( Register<RegType,
		                                                        BitFields, FieldMask> &,
		                                                    RegType );
		friend BitFields readBits<RegType, BitFields, FieldMask>( Register<RegType,
		                                                              BitFields,
		                                                              FieldMask> &,
		                                                          BitFields );
		friend bool areBitsSet<RegType, BitFields, FieldMask>( Register<RegType,
		                                                           BitFields,
		                                                           FieldMask> &,
		                                                       BitFields );
		friend bool areBitsCleared<RegType, BitFields, FieldMask>( Register<RegType,
		                                                               BitFields,
		                                                               FieldMask> &,
		                                                           BitFields );
	private:
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

		friend void set<RegType, void, FieldMask>( Register<RegType, void, FieldMask> &,
		                                           RegType,
		                                           RegType );
		friend RegType read<RegType, void, FieldMask>( Register<RegType, void,
		                                                   FieldMask> &,
		                                               RegType );

	private:
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

		friend void setBits<RegType, BitFields, void>( Register<RegType, BitFields,
		                                                   void> &,
		                                               BitFields );
		friend void clearBits<RegType, BitFields, void>( Register<RegType,
		                                                     BitFields, void> &,
		                                                 BitFields );
		friend void set<RegType, BitFields, void>( Register<RegType, BitFields, void> &,
		                                           RegType,
		                                           RegType );
		friend RegType read<RegType, BitFields, void>( Register<RegType, BitFields,
		                                                   void> &,
		                                               RegType );
		friend BitFields readBits<RegType, BitFields, void>( Register<RegType,
		                                                         BitFields, void> &,
		                                                     BitFields );
		friend bool areBitsSet<RegType, BitFields, void>( Register<RegType,
		                                                      BitFields, void> &,
		                                                  BitFields );
		friend bool areBitsCleared<RegType, BitFields, void>( Register<RegType,
		                                                          BitFields, void> &,
		                                                      BitFields );
	private:

		RegType const m_mask;
		volatile RegType *m_register;
};

/* Implementation for primary template */
template<typename RegType, typename BitFields, typename FieldMask>
Register<RegType, BitFields, FieldMask>::Register( RegType &reg, RegType mask )
		: m_mask( mask ), m_register( &reg )
{
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::SetBits( BitFields value )
{
	setBits( *this, value );
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::ClearBits( BitFields value )
{
	clearBits( *this, value );
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::Set( RegType value )
{
	set( *this, value );
}

template<typename RegType, typename BitFields, typename FieldMask>
void Register<RegType, BitFields, FieldMask>::Set( RegType value,
                                                   FieldMask mask )
{
	set( *this, value, mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::GetMask()
{
	return m_mask;
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::Read() const
{
	return read( *this );
}

template<typename RegType, typename BitFields, typename FieldMask>
RegType Register<RegType, BitFields, FieldMask>::Read( FieldMask mask ) const
{
	return read( *this, mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
BitFields Register<RegType, BitFields, FieldMask>::ReadBits( BitFields fields ) const
{
	return readBits( *this, fields );
}

template<typename RegType, typename BitFields, typename FieldMask>
bool Register<RegType, BitFields, FieldMask>::AreBitsSet( BitFields fields ) const
{
	return areBitsSet( *this, fields );
}

template<typename RegType, typename BitFields, typename FieldMask>
bool Register<RegType, BitFields, FieldMask>::AreBitsCleared( BitFields fields ) const
{
	return AreBitsCleared( fields );
}

/* Implementation for masked register template */

template<typename RegType, typename FieldMask>
Register<RegType, void, FieldMask>::Register( RegType &reg, RegType mask )
		: m_mask( mask ), m_register( &reg )
{
}

template<typename RegType, typename FieldMask>
void Register<RegType, void, FieldMask>::Set( RegType value )
{
	set( *this, value );
}

template<typename RegType, typename FieldMask>
void Register<RegType, void, FieldMask>::Set( RegType value, FieldMask mask )
{
	set( *this, value, mask );
}

template<typename RegType, typename FieldMask>
RegType Register<RegType, void, FieldMask>::GetMask()
{
	return m_mask;
}

template<typename RegType, typename FieldMask>
RegType Register<RegType, void, FieldMask>::Read() const
{
	return read( *this );
}

template<typename RegType, typename FieldMask>
RegType Register<RegType, void, FieldMask>::Read( FieldMask mask ) const
{
	return read( *this, mask );
}

/* Implementation for bitfield register */

template<typename RegType, typename BitFields>
Register<RegType, BitFields, void>::Register( RegType &reg, RegType mask )
		: m_mask( mask ), m_register( &reg )
{
}

template<typename RegType, typename BitFields>
void Register<RegType, BitFields, void>::SetBits( BitFields value )
{
	setBits( *this, value );
}

template<typename RegType, typename BitFields>
void Register<RegType, BitFields, void>::ClearBits( BitFields value )
{
	clearBits( *this, value );
}

template<typename RegType, typename BitFields>
void Register<RegType, BitFields, void>::Set( RegType value )
{
	set( *this, value );
}

template<typename RegType, typename BitFields>
RegType Register<RegType, BitFields, void>::GetMask()
{
	return m_mask;
}

template<typename RegType, typename BitFields>
RegType Register<RegType, BitFields, void>::Read() const
{
	return read( *this );
}

template<typename RegType, typename BitFields>
BitFields Register<RegType, BitFields, void>::ReadBits( BitFields fields ) const
{
	return readBits( *this, fields );
}

template<typename RegType, typename BitFields>
bool Register<RegType, BitFields, void>::AreBitsSet( BitFields fields ) const
{
	return areBitsSet( *this, fields );
}

template<typename RegType, typename BitFields>
bool Register<RegType, BitFields, void>::AreBitsCleared( BitFields fields ) const
{
	return AreBitsCleared( fields );
}

/* Implement the helper functions */

template<typename RegType, typename BitFields, typename FieldMask>
inline void setBits( Register<RegType, BitFields, FieldMask> &reg,
                     BitFields bits )
{
	RegType value = static_cast<RegType>( bits ) & reg.m_mask;
	*reg.m_register |= value;
}

template<typename RegType, typename BitFields, typename FieldMask>
inline void clearBits( Register<RegType, BitFields, FieldMask> &reg,
                       BitFields bits )
{
	RegType value = static_cast<RegType>( bits ) & reg.m_mask;
	*reg.m_register &= ~value;
}

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg, RegType value )
{
	set( reg, value, reg.m_mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg,
                 RegType value,
                 FieldMask mask )
{
	set( reg, value, static_cast<RegType>( mask ) );
}

template<typename RegType, typename BitFields, typename FieldMask>
inline void set( Register<RegType, BitFields, FieldMask> &reg,
                 RegType value,
                 RegType mask )
{
	RegType tmp = *reg.m_register;
	mask &= reg.m_mask;
	tmp &= ~mask;

	tmp |= (value & mask);

	*reg.m_register = tmp;
}

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg )
{
	return read( reg, reg.m_mask );
}

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg,
                     FieldMask mask )
{
	return read( reg, static_cast<RegType>( mask ) );
}

template<typename RegType, typename BitFields, typename FieldMask>
inline RegType read( Register<RegType, BitFields, FieldMask> &reg,
                     RegType mask )
{
	mask &= reg.m_mask;

	return (*reg.m_register) & mask;
}

template<typename RegType, typename BitFields, typename FieldMask>
inline BitFields readBits( Register<RegType, BitFields, FieldMask> &reg,
                           BitFields bits )
{
	RegType mask = static_cast<RegType>( bits );
	RegType value = *reg.m_register & mask;

	return static_cast<BitFields>( value );
}

template<typename RegType, typename BitFields, typename FieldMask>
inline bool areBitsSet( Register<RegType, BitFields, FieldMask> &reg,
                        BitFields bits )
{
	RegType value = *reg.m_register & reg.m_mask;
	RegType mask = static_cast<RegType>( bits );

	return (value & mask) == mask;
}

template<typename RegType, typename BitFields, typename FieldMask>
inline bool areBitsCleared( Register<RegType, BitFields, FieldMask> &reg,
                            BitFields bits )
{
	RegType value = *reg.m_register & reg.m_mask;
	RegType mask = static_cast<RegType>( bits );

	return (value & mask) == 0;
}

} /* namespace stm32 */

#endif /* SRC_HAL_REGISTER_HPP_ */
