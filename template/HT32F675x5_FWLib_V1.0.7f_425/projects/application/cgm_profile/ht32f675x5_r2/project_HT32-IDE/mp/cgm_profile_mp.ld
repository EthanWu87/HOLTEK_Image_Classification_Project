/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas. */
/******************* !!!!! IMPORTANT !!!!! ********************************/
/* Please modify the memory length according to different specifications. */
/**************************************************************************/
MEMORY
{
  BOOT2 (rx)          : ORIGIN = 0x10000000, LENGTH = 4K
  FLASH_FW_UPGRADE_INFO (rx): ORIGIN = 0x10001000, LENGTH = 4K
  FLASH (rx)          : ORIGIN = 0x10002000, LENGTH = 200K
  RAM_CP_CODE (rwx)   : ORIGIN = 0x20003000, LENGTH = 156K
  RAM_MP_VECTOR(rwx)  : ORIGIN = 0x20022000, LENGTH = 512
  RAM_MP_CODE (rwx)   : ORIGIN = 0x20022200, LENGTH = 31K+512
  RAM_MP_DATA (rwx)   : ORIGIN = 0x2002A000, LENGTH = 32K
}


/* Define output sections */
SECTIONS
{
  .boot2 :
  {
    . = ALIGN(4);
    KEEP(*(.boot2.code))
    . = ALIGN(4);
  } >BOOT2
  
  .fw_upgrade :
  {
    . = ALIGN(4);
    KEEP(*(.fw.bleota.file.info))
    . = ALIGN(4);
  } >FLASH_FW_UPGRADE_INFO

  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

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
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata ALIGN(4) :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize cp application code */
  _sicp = LOADADDR(.cp.app.code);

  .cp.app.code :
  {
    . = ALIGN(4);
    _scp = .;
    KEEP(*(.cp.app.code))
    . = ALIGN(4);
    _ecp = .;
  } >RAM_CP_CODE AT> FLASH

  .bss.new_vector :
  {
    . = ALIGN(4);
    KEEP(*(.bss.new_vector))
    . = ALIGN(4);
  } >RAM_MP_VECTOR

  /* used by the startup to initialize ram function */
  _siram = LOADADDR(.ram.function);

  .ram.function :
  {
    . = ALIGN(4);
    _sram = .;
    KEEP(*(.ram.function))
    . = ALIGN(4);
    _eram = .;
  } >RAM_MP_CODE AT> FLASH

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
  } >RAM_MP_DATA AT> FLASH


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
  } >RAM_MP_DATA

  .heap ALIGN(8) (COPY):
  {
    __end__ = .;
    PROVIDE(end = .);
    *(.heap*)
    __HeapLimit = .;
  } > RAM_MP_DATA

  /* .stack_dummy section doesn't contains any symbols. It is only
   * used for linker to calculate size of stack sections, and assign
   * values to stack symbols later */
  .stack_dummy ALIGN(4):
  {
    *(.stack*)
  } > RAM_MP_DATA

  /* Set stack top to end of RAM, and stack limit move down by
   * size of stack_dummy section */
  __StackTop = ORIGIN(RAM_MP_DATA) + LENGTH(RAM_MP_DATA);
  __StackLimit = __StackTop - SIZEOF(.stack_dummy);
  PROVIDE(__stack = __StackTop);

  __ram_end__ = ORIGIN(RAM_MP_DATA) + LENGTH(RAM_MP_DATA) -1 ;

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
