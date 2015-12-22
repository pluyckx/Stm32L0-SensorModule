/*
 * startup.c
 *
 *  Created on: Jan 9, 2015
 *      Author: pluyckx
 */

#include <stdint.h>

extern uint32_t _datasrc;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;

void InitApplication( void )
{
	char *datasrc = reinterpret_cast<char*>( &_datasrc );
	char *data_dst = reinterpret_cast<char*>( &_data_start );
	char *data_end = reinterpret_cast<char*>( &_data_end );
	char *bss_dst = reinterpret_cast<char*>( &_bss_start );
	char *bss_end = reinterpret_cast<char*>( &_bss_end );

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
}
