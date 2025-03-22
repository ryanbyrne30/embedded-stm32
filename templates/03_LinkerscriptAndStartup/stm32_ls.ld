/* Firmware's entry point */
ENTRY(Reset_Handler)

/* Detailing available memory */
MEMORY
{
    FLASH(rx) :ORIGIN =0x08000000,LENGTH =64K
    SRAM(rwx) :ORIGIN =0x20000000,LENGTH =20K
}

/* Create a symbol _estack, set it to the end of SRAM memory. Will be used to initialize the stack pointer */
_estack = ORIGIN(SRAM)+LENGTH(SRAM);

/* Specifying the necessary heap and stack sizes */

__max_heap_size = 0x200;
__max_stack_size = 0x400;

/* Defining output sections */
SECTIONS
{
    .text :                 /* Main code */
    {
        . = ALIGN(4);       /* Aligns start of section on a 4-byte boundary (32 bit) */
        *(.isr_vector_tbl)
        *(.text)
        *(.rodata)
        . = ALIGN(4);       /* Ensures the end of the section aligns on a 4-byte boundary */
        _etext = .;         /* Defines a symbol that represents the end of the .text section */
    }>FLASH                 /* Directive to specify this section should be placed in the FLASH memory */

    .data :                 /* Global variables */
    {
        . = ALIGN(4);       /* Aligns start of section on a 4-byte boundary (32 bit) */
        _sdata = .;         /* Creates a symbol _sdata to represent the start of the .data section */
        *(.data)
        . = ALIGN(4);       /* Ensures the end of the section aligns on a 4-byte boundary */
        _edata = .;         /* Defines a symbol that represents the end of the .data section */
    } > SRAM AT> FLASH      /* Specifies the LMA and VMA of the .data section >(vma) AT> (lma) */

    .bss :                  /* Uninitialized global and static variables */
    {
        . = ALIGN(4);       /* Aligns start of section on a 4-byte boundary (32 bit) */
        _sbss = .;          /* Defines a symbol that represents the start of the .bss section */
        *(.bss)
        . = ALIGN(4);       /* Ensures the end of the section aligns on a 4-byte boundary */
        _ebss = .;          /* Defines a symbol that represents the end of the .bss section */
    }> SRAM                 /* Directive to specify this section should be placed in SRAM */
}
