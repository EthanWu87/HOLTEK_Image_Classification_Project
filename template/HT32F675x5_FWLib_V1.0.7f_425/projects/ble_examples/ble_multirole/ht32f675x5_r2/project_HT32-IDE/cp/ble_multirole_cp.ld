/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas. */
/******************* !!!!! IMPORTANT !!!!! ********************************/
/* Please modify the memory length according to different specifications. */
/**************************************************************************/
MEMORY
{
  LOAD_CODE (rwx)     : ORIGIN = 0x20003000, LENGTH = 80K
}


/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >LOAD_CODE

  /* The program code and other data goes into FLASH */
  .text ALIGN(4) :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >LOAD_CODE

  /* Constant data goes into FLASH */
  .rodata ALIGN(4) :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >LOAD_CODE

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >LOAD_CODE
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >LOAD_CODE

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >LOAD_CODE
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >LOAD_CODE
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >LOAD_CODE

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >LOAD_CODE


  /* Uninitialized data section */
  . = ALIGN(4);
  .bss ALIGN(4) :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >LOAD_CODE

  .heap ALIGN(8) (COPY):
  {
    __end__ = .;
    PROVIDE(end = .);
    *(.heap*)
    __HeapLimit = .;
  } > LOAD_CODE

  /* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy ALIGN(4):
  {
    *(.stack*)
  } > LOAD_CODE

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(LOAD_CODE) + LENGTH(LOAD_CODE);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);

  __ram_end__ = ORIGIN(LOAD_CODE) + LENGTH(LOAD_CODE) -1 ;

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
