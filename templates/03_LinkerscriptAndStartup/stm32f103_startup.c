// Declare external symbols from linker script
extern uint32_t _estack; // top of statck
extern uint32_t _etext;  // end of executable code section & beginning of data section stored in FLASH
extern uint32_t _sdata;  // start of initialized data section
extern uint32_t _edata;  // end of initialized data section
extern uint32_t _sbss;   // start of uninitialized data section
extern uint32_t _ebss;   // end of unintialized data section

/*
    Declare function prototypes and attributes
    __attribute__((weak, alias("Default_Handler"))) makes each handler
    weakly linked and aliased to a function named Default_Handler. This
    allows these handlers to be overridden by explicitly defined handlers
    with the same name elsewhere in the application.
*/
void Reset_Handler(void);
int main(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));

/*
    Defines microprocessors interrupt handlers placed in the .isr_vector_tbl
    section defined in the linker script. Order and placement of these interrupt
    handlers is defined in the microprocessor's Reference Manual (see Interrupt Vectors)
*/
uint32_t vector_tbl[] __attribute__((section(".isr_vector_tbl"))) = {
    (uint32_t)&_estack, // First word must be the initial value of the main stack pointer (MSP)
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
};

void Default_Handler(void)
{
    while (1)
    {
    }
}

void Reset_Handler(void)
{
    // Calculate the sizes of .data and .bss
    uint32_t data_mem_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint32_t bss_mem_size = (uint32_t)&_ebss - (uint32_t)&_sbss;

    // Initialize pointers to the source and destination of .data
    uint32_t *p_src_mem = (uint32_t *)&_etext;
    uint32_t *p_dest_mem = (uint32_t *)&_sdata;

    /* Copy .data section from FLASH to SRAM */
    for (uint32_t i = 0; i < data_mem_size; i++)
    {
        *p_dest_mem++ = *p_src_mem++;
    }

    /* Initialize the .bss section to zero in SRAM */
    p_dest_mem = (uint32_t *)&_sbss;

    for (uint32_t i = 0; i < bss_mem_size; i++)
    {
        /* Set .bss section to zero */
        *p_dest_mem++ = 0;
    }

    // Call application's main function
    main();
}
