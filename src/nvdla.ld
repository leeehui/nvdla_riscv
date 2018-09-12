OUTPUT_ARCH("riscv")
ENTRY( reset_handler )

MEMORY {
    ROM (rx): ORIGIN = 0x00000000, LENGTH = 0x100000
    RAM (rwx): ORIGIN = 0x00100000, LENGTH = 0x100000
}


SECTIONS
{
    .vectors : 
    {
        . = ALIGN(4);
        KEEP(*(.vectors))
    } >ROM

    /* text: test code section */
    .text :
    {
        *startup.S.o
        *(.text)
    } >ROM
    
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata.*)
    } >ROM
    
    . = 0x00100000;
    /* data: initialized data segment */
    .data :
    {
        . = ALIGN(4);
        __DATA_RAM_START__ = .;
        *(.data)
        *(.sdata)
        __DATA_RAM_END__ = .;
    } >RAM AT>ROM
    
    .stacks (NOLOAD):
    {
        . = ALIGN(4);
        __STACKS_START__ = .;
        . = . + 5120;
        __STACKS_END__ = .;
    } >RAM
    
    .heap :
    {
        . = ALIGN(4);
        *(heap_lcc);
    } >RAM
    /* bss: uninitialized data segment */
    
    .bss :
    {
        . = ALIGN(4);
        __BSS_START__ = .;
        *(.bss)
        *(.bss.*)
        *(.sbss)
        *(.sbss.*)
        *(COMMON)
        __BSS_END__ = .;
    } >RAM 

    . = ALIGN(8);
    __DATA_ROM_START__ = LOADADDR(.data);
    __DATA_SIZE__ = SIZEOF(.data);

    __ROM_END__ = __DATA_ROM_START__ + __DATA_SIZE__;

    /* End of uninitialized data segment */
    _end = .;
}

