/*
 *  Linker script para la placa STM32F446RE
 */

MEMORY
{
    RAM :  org = 0x20000000,    len = 0x20000 /* 128 Kbytes */
}

ENTRY(_Reset_handler)

SECTIONS
{
    _stack_size =   0x10000;
    _heap_size  =   _stack_bottom - _bss_end;
    PROVIDE(heap_size = _heap_size);
    _ram_limit = ORIGIN(RAM) + LENGTH(RAM);

    .text : ALIGN(4)
    {
		*(.startup*)
        KEEP(*(.isr_vector))
        _text = .;
        *(.text*)
        KEEP (*(.init))
        KEEP (*(.fini))
        _etext = .;
    } > RAM

    .rodata : ALIGN(4)
    {
      _rodata_start = . ;
      *(.rodata*);
      _rodata_end = . ;
    } > RAM

    .data : ALIGN(4)
	{
		_data_start = .;
		*(.data*)
		_data_end = .;

	} >RAM

    .bss : ALIGN(4)
	{
		_bss_start = .;
		*(.bss*)
		_bss_end = .;
	} > RAM

	.heap : ALIGN(4)
	{
      _heap_start = .;
      . += _heap_size;
      _heap_end = .;
	} > RAM

  	.stack _ram_limit - _stack_size : ALIGN(4)
  	{
      _stack_bottom = .;
      . += _stack_size;
      _stack_top = .;
  	} > RAM

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
