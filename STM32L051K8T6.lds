ENTRY(main)

SEARCH_DIR("/usr/lib/arm-none-eabi/lib/thumb");

MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	ram (rw) : ORIGIN = 0x20000000, LENGTH = 8K
}

__cstack = 0x20000000 + 8K;

SECTIONS
{
	.text :
	{
		KEEP(*(.nvic))
		
		*(.text)
		*(.text*)
	    *(.rodata)
	    *(.rodata*)
	    
	    . = ALIGN(4);
	} > rom
	
	_datasrc = .;
	
	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
		_data_start = .;
		_data_end = . + SIZEOF(.data);
		KEEP(*(.data));
	} > ram
	
	.bss :
	{
		_bss_start = .;
		_bss_end = . + SIZEOF(.bss);
		
		*(.bss)
	} > ram
	
	/* Register locations */	
	r_gpioa =  0x50000000;
	r_gpiob =  0x50000400;
	r_gpioc =  0x50000800;
	r_gpiod =  0x50000c00;
	r_gpioe =  0x50001000;
	r_gpioh =  0x50001C00;
	
	r_clock =  0x40021000;
	
	systick =  0xE000E010;
	nvic =     0xE000E100;
	dbgmcu =   0x40015800;
}