/*
 * C linker script file for LPC1224
 */

MEMORY
{
	sram (rwx) : ORIGIN = 0x10000000, LENGTH = 4k
	flash (rx) : ORIGIN = 0x00000000, LENGTH = 32k
	info  (rx) : ORIGIN = 0x00040200, LENGTH = 1536
}

_sram_size = 4k;
_sram_base = 0x10000000;
/* Leave 32 bytes for IAP functions, see UM10441 Chapter 20, section 20.8 */
_end_stack = (_sram_base + _sram_size - 32);

_start_info = 0x00040200;
_end_info = (_start_info + 1536);


ENTRY(Reset_Handler)

SECTIONS {
	. = ORIGIN(flash);

	.text :
	{
		FILL(0xFF);
		KEEP(*(.vectors))
		*(.text.Reset_Handler .text.SystemInit)
		. = 0x000002FC;
		KEEP(*(.crp))
		*(.text*)
		*(.rodata*)
		*(.got*)
		_end_text = .;
	} >flash

	. = ALIGN(4);

	.data :
	{
		_start_data = .;
		*(.data*)
		_end_data = .;
	} >sram AT >flash

	. = ALIGN(4);

	.bss :
	{
		_start_bss = .;
		*(.bss*)
		*(COMMON)
		_end_bss = .;
	} >sram
}

_end = .;
PROVIDE(end = .);
