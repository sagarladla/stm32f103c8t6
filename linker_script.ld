/**
 * @target:	armv7-m3
 * @author:	Sagar Ladla [sagarladla@gmail.com]
 * @file:	linker_script.ld
 * @brief:	STM32F103C8T6 microcontroller linker script file.
 * 		This program handles:
 * 			- set FLASH memory from 0x08000000 address with 64KB space
 * 			- set SRAM  memory from 0x20000000 address with 20KB space
 * 			- define sections of memory
*/

ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rw):	ORIGIN = 0x08000000,	LENGTH = 64K
	SRAM(rwx):	ORIGIN = 0x20000000,	LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		_stext = .;
		*(.isr_vector)
		*(.text)
		*(.rodata)
		_etext = .;
	} > FLASH
	.data :
	{
		_sdata = .;
		*(.data)
		_edata = .;
	} > SRAM AT > FLASH
	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} > SRAM
}
