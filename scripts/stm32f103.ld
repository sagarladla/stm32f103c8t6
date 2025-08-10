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
        sram (rwx)      :       ORIGIN = 0x20000000, LENGTH = 20K
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

        .rodata :       ALIGN(0x4)
        {
                *(.rodata*)
                . = ALIGN(0x4);
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

        /DISCARD/ :
        {
                libc.a(*)
                libm.a(*)
                libgcc.a(*)
        }
}
