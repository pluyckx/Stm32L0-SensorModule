

SEARCH_DIR("/usr/lib/arm-none-eabi/lib/thumb");

MEMORY
{
	flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	ram (rw) : ORIGIN = 0x20000000, LENGTH = 8K
}

__cstack = 0x20000000 + 8K;

SECTIONS
{	
	.text :
	{
		_start_isr_vector = .;
		KEEP(*(.isr_vector))
		ASSERT( . != _start_isr_vector, "No isr vector defined" );
		. = ALIGN(4);
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		
        _ctors_begin_ = .;
        KEEP(*(SORT(.init_array.*)));
        KEEP(*(.init_array*));
        _ctors_end_ = .;
	} > flash
	
	/*
     * Newlib and Eglibc (at least) need these for C++ support.
     *
     * (Copied from Sourcery CodeBench Lite: arm-none-eabi-gcc -V)
     */
    .preinit_array :
    {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*));
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } >flash
    
    .fini_array :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)));
        KEEP(*(.fini_array*));
        PROVIDE_HIDDEN(__fini_array_end = .);
    } >flash
	
	_data_flash = .;
	
	.data : AT(_data_flash)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*.data
		*.data*
		. = ALIGN(4);
		__data_end__ = .;
	} > ram
	
	.bss :
	{
		__bss_start__ = .;
		*.bss
		*.bss*
		*COMMON
		. = ALIGN(4);
		__bss_end__ = .;
	} > ram
	
	.eh_frame :
	{
		*.eh_frame
		*.eh_frame*
	} > ram
	
	stack_size = 1K;
	stack_end = ORIGIN(ram) + LENGTH(ram);
	_stack_begin = stack_end - stack_size;
	
	. = _stack_begin;
	._stack :
	{
		. = . + stack_size;
	} > ram
	
	/* Register locations */	
	r_gpioa =  0x50000000;
	r_gpiob =  0x50000400;
	r_gpioc =  0x50000800;
	r_gpiod =  0x50000c00;
	r_gpioe =  0x50001000;
	/* r_gpioh =  0x50001C00; */ /* TODO: check if h is also available! */
	
	r_clock =  0x40021000;
	
	r_systick =  0xE000E010;
	r_nvic =     0xE000E100;
	r_dbgmcu =   0x40015800;
}