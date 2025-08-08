/**
 * @target:     armv7-m3
 * @author:     Sagarvarman Ladla [sagarladla@gmail.com]
 * @file:       stm32f103.ld
 * @brief:      STM32F103C8T6 microcontroller linker script file.
 *              This program handles:
 *                      - set FLASH memory from 0x08000000 address with 64KB space
 *                      - set SRAM  memory from 0x20000000 address with 20KB space
 *                      - define sections of memory
 */

ENTRY(isr_reset)

MEMORY
{
        flash(rx)       :       ORIGIN = 0x08000000, LENGTH = 64K,
        sram(rwx)       :       ORIGIN = 0x20000000, LENGTH = 20K
}

_eram	= ORIGIN(sram) + LENGTH(sram);
_stack	= _eram;

SECTIONS
{
        .ivt    :       ALIGN(0x4)
        {
                KEEP(*(.ivt))
                . = ALIGN(0x4);
        } > flash

        .text   :       ALIGN(0x4)
        {
                *(.text*)
                . = ALIGN(4);
                PROVIDE(_etext = .);
        } > flash

        .const :       ALIGN(0x4)
        {
                *(.const*)
                . = ALIGN(0x4);
        } > flash

        .init_array     :       ALIGN(0x4)
        {
                PROVIDE_HIDDEN (__init_array_start = .);
                KEEP (*(.init_array*))
                PROVIDE_HIDDEN (__init_array_end = .);
                . = ALIGN(0x04);
        } > flash

        _idata = LOADADDR(.data);
        .data   :       ALIGN(0x4)
        {
                PROVIDE(_data = .);
                *(.data*)
                . = ALIGN(4);
                PROVIDE(_edata = .);
        } > sram AT > flash

        .bss    :       ALIGN(0x4)
        {
                PROVIDE(_bss = .);
                *(.bss*)
                . = ALIGN(4);
                PROVIDE(_ebss = .);
        } > sram

	.heap   :       ALIGN(0x4)
	{
		PROVIDE(_heap_start = .);
		. = . + 0x1000; // 4KB heap size
		PROVIDE(_heap_end = .);
	} > sram

	.stack :       ALIGN(0x4)
	{
		PROVIDE(_stack_start = .);
		. = _stack; // Stack starts at the end of SRAM
		PROVIDE(_stack_end = .);
	} > sram (HIGH)

        /DISCARD/ :
        {
                libc.a(*)
                libm.a(*)
                libgcc.a(*)
        }
}
