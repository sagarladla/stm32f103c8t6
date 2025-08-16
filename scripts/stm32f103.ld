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

MEMORY
{
        flash(rx)  : ORIGIN = 0x08000000, LENGTH = 64K,
        sram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

_estack	= ORIGIN(sram) + LENGTH(sram);
STACK_SIZE = 0x1; /* 4KB stack size */
HEAP_SIZE  = 0x1; /* 4KB heap size */

SECTIONS
{
        .ivt     :
        {
                KEEP(*(.ivt))
        } > flash

        .startup :
        {
                PROVIDE(_sstartup = .);
                *(.startup)
                *(.startup.*)
                PROVIDE(_estartup = .);
        } > flash

        .ramkernel :
        {
                PROVIDE(_sramkernel = .);
                *(.ramkernel)
                *(.ramkernel.*)
                PROVIDE(_eramkernel = .);
        } > sram AT > flash

        .text      :
        {
                PROVIDE(_stext = .);
                *(.text)
                *(.text.*)
                PROVIDE(_etext = .);
        } > flash

        .rodata :
        {
                PROVIDE(_srodata = .);
                *(.rodata*)
                *(.rodata.*)
                PROVIDE(_erodata = .);
        } > flash

        _idata = LOADADDR(.data);
        .data   :
        {
                PROVIDE(_data = .);
                *(.data)
                *(.data.*)
                PROVIDE(_edata = .);
        } > sram AT > flash

        .ramkernel_data :
        {
                PROVIDE(_sramkernel_data = .);
                *(.ramkernel_data)
                *(.ramkernel_data.*)
                PROVIDE(_eramkernel_data = .);
        } > sram AT > flash

        .bss (NOLOAD)   :
        {
                PROVIDE(_bss = .);
                *(.bss)
                *(.bss.*)
                PROVIDE(_ebss = .);
        } > sram

        .heap (NOLOAD)   :
        {
                PROVIDE(_sheap = .);
                . = . + HEAP_SIZE;
                PROVIDE(_eheap = .);
        } > sram

        /**
         * descending stack section
         */
        .stack (NOLOAD)   :
        {
                . = (_estack - STACK_SIZE);
                PROVIDE(_sstack = .);
                /* estack provided at top */
        } > sram

        /DISCARD/ :
        {
                libc.a(*)
                libm.a(*)
                libgcc.a(*)
                *(.note.GNU-stack)
        }
}

ivt_size = SIZEOF(.ivt);
startup_size = SIZEOF(.startup);
ramkernel_size = SIZEOF(.ramkernel);
text_size = SIZEOF(.text);
rodata_size = SIZEOF(.rodata);
data_size = SIZEOF(.data);
ramkernel_data_size = SIZEOF(.ramkernel_data);
bss_size = SIZEOF(.bss);
heap_size = SIZEOF(.heap);
stack_size = SIZEOF(.stack);
