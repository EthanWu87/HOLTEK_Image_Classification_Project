/*
 * HT32F67595 Final Linker Script
 */

ENTRY(Reset_Handler)

MEMORY
{
  BOOT2 (rx)     : ORIGIN = 0x10000000, LENGTH = 4K
  FLASH (rx)     : ORIGIN = 0x10002000, LENGTH = 504K
  RAM_VECTOR(rwx): ORIGIN = 0x20003000, LENGTH = 512
  RAM_CODE (rwx) : ORIGIN = 0x20003200, LENGTH = 31K+512
  RAM_DATA (rwx) : ORIGIN = 0x2000B000, LENGTH = 20K
}

_Min_Heap_Size = 0x200;
_Min_Stack_Size = 0x400;

SECTIONS
{
  _sicp = LOADADDR(.isr_vector);
   _scp = .;
    _ecp = .;

  
    .boot2 :
  {
    . = ALIGN(4);
    KEEP(*(.boot2.code))
    . = ALIGN(4);
  } >BOOT2

  /* 1. 中斷向量表 */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* 2. 程式碼 */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* 3. Read-only Data */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH

  /* ==================================================== */
  /* [關鍵修正] 定義 Exception Handling Table             */
  /* 解決 undefined reference to __exidx_start 錯誤        */
  /* ==================================================== */
  .ARM.extab : 
  { 
    *(.ARM.extab* .gnu.linkonce.armextab.*) 
  } >FLASH

  .ARM.exidx :
  {
    __exidx_start = .;
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    __exidx_end = .;
  } >FLASH

  /* 4. 初始化陣列 */
  .preinit_array :
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

  /* 5. RAM Functions */
  _siram = LOADADDR(.ram.function);
  .ram.function :
  {
    . = ALIGN(4);
    _sram = .;
    KEEP(*(.ram.function))
    . = ALIGN(4);
    _eram = .;
  } >RAM_CODE AT> FLASH

  /* 6. Data Section */
  _sidata = LOADADDR(.data);
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM_DATA AT> FLASH

  /* 7. BSS Section */
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM_DATA

  /* 8. Heap & Stack Check */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM_DATA

  /* Holtek Startup File 相容性 */
  PROVIDE(_scp  = ADDR(.data));
  PROVIDE(_ecp  = ADDR(.data) + SIZEOF(.data));
  
  /* Stack Top */
  __StackTop = ORIGIN(RAM_DATA) + LENGTH(RAM_DATA);
  PROVIDE(__stack = __StackTop);
}