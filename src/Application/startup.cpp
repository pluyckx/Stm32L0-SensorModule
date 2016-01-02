/*
 * startup.c
 *
 *  Created on: Jan 9, 2015
 *      Author: pluyckx
 */

#include <stdint.h>

#include "startup.hpp"

typedef void (*ctor)( void );

extern uint32_t _data_flash;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern ctor _ctors_begin_;
extern ctor _ctors_end_;

extern "C"
{
extern void __libc_init_array( void );
}

void InitApplication( void )
{
	char *datasrc = reinterpret_cast<char*>( &_data_flash );
	char *data_dst = reinterpret_cast<char*>( &__data_start__ );
	char *data_end = reinterpret_cast<char*>( &__data_end__ );
	char *bss_dst = reinterpret_cast<char*>( &__bss_start__ );
	char *bss_end = reinterpret_cast<char*>( &__bss_end__ );

	while ( (data_dst + 4) <= data_end )
	{
		*(reinterpret_cast<uint32_t*>( data_dst )) =
		    *(reinterpret_cast<uint32_t*>( datasrc ));
		data_dst += 4;
		datasrc += 4;
	}

	while ( data_dst < data_end )
	{
		*((uint8_t*) data_dst) = *((uint8_t*) datasrc);
		data_dst += 1;
		datasrc += 1;
	}

	while ( bss_dst + 4 <= bss_end )
	{
		*reinterpret_cast<uint32_t*>( bss_dst ) = 0;
		bss_dst += 4;
	}

	while ( bss_dst + 1 <= bss_end )
	{
		*reinterpret_cast<uint8_t*>( bss_dst ) = 0;
		bss_dst++;
	}


	/* Iterate static constructors */
	/* Are we also calling functions for global vars like:
	 * uint32_t global_var = func();
	 */
	ctor *current = &_ctors_begin_;

	while ( reinterpret_cast<uint32_t>( current )
	    < reinterpret_cast<uint32_t>( &_ctors_end_ ) )
	{
		(*current)();
		current = reinterpret_cast<ctor*>( reinterpret_cast<uint32_t>( current )
		    + sizeof(ctor) );
	}

}
