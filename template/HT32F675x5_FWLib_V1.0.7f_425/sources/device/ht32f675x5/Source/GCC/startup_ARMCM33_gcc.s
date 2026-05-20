/**************************************************************************//**
 * @file     startup_ARMCM33_gcc.s
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM33 Device
 * @version  V5.4.0
 * @date     12. December 2018
 ******************************************************************************/
/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
*/
/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------

;//this file has been modified
*/
  .syntax unified
  .cpu cortex-m33
  .fpu softvfp
  .thumb

/* start address for the initialization values of the .data section. defined in linker script               */
.word  _sidata

/* start address for the .data section. defined in linker script                                            */
.word  _sdata

/* end address for the .data section. defined in linker script                                              */
.word  _edata

/* start address for the .bss section. defined in linker script                                             */
.word  _sbss

/* end address for the .bss section. defined in linker script                                               */
.word  _ebss

/*
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
*/
    .equ    Stack_Size, 0x00001000
    .section ".stack", "w"
    .align  3
    .globl  __StackTop
    .globl  __StackLimit
    .globl  __HT_check_sp
__HT_check_sp:
__StackLimit:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

/*
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
*/
    .equ    Heap_Size, 0x00000000
    .section ".heap", "w"
    .align  3
    .globl  __HeapBase
    .globl  _end
    .globl  __HeapLimit
    .globl  __HT_check_heap
__HT_check_heap:
__HeapBase:
_end:
    .if     Heap_Size
    .space  Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .equ    _RESERVED, 0xFFFFFFFF

/*
; Vector Table Mapped to Address 0 at Reset
*/

                    .section  .isr_vector,"a",%progbits
                    .global  __Vectors
                    .type  __Vectors, %object
__Vectors:
                .long  __StackTop                          /*      Top of Stack              */
                .long  Reset_Handler                       /*      Reset Handler             */
                .long  NMI_Handler                         /*  -14 NMI Handler               */
                .long  HardFault_Handler                   /*  -13 Hard Fault Handler        */
                .long  MemoryManagement_Handler            /*  -12 MPU Fault Handler         */
                .long  BusFault_Handler                    /*  -11 Bus Fault Handler         */
                .long  UsageFault_Handler                  /*  -10 Usage Fault Handler       */
                .long  0                                   /*   -9 Secure Fault Handler      */
                .long  0                                   /*      Reserved                  */
                .long  0                                   /*      Reserved                  */
                .long  0                                   /*      Reserved                  */
                .long  SVC_Handler                         /*   -5 SVCall Handler            */
                .long  DebugMon_Handler                    /*   -4 Debug Monitor Handler     */
                .long  0                                   /*      Reserved                  */
                .long  PendSV_Handler                      /*   -2 PendSV Handler            */
                .long  SysTick_Handler                     /*   -1 SysTick Handler           */

                /*; Interrupts                                                               */
                .long  RTC_CH0_IRQ_Handler
                .long  GPADC0_IRQ_Handler
                .long  LLC_IRQ_Handler
                .long  I2S_IRQ_Handler
                .long  QDEC_IRQ_Handler
                .long  AUDIO0_IRQ_Handler
                .long  CRYPT0_IRQ_Handler
                .long  TRNG_IRQ_Handler
                .long  RF_CAL_IRQ_Handler
                .long  UART0_IRQ_Handler
                .long  UART1_IRQ_Handler
                .long  UART2_IRQ_Handler
                .long  SPI0_IRQ_Handler
                .long  SPI1_IRQ_Handler
                .long  I2C0_IRQ_Handler
                .long  I2C1_IRQ_Handler
                .long  I2C2_IRQ_Handler
                .long  DMA_IRQ0_Handler
                .long  DMA_IRQ4_Handler
                .long  TIMER0_IRQ_Handler
                .long  GPIO_IRQ0_Handler
                .long  GPIO_IRQ1_Handler
                .long  GPIO_IRQ2_Handler
                .long  PMU_IRQ_Handler
                .long  QSPI0_IRQ_Handler
                .long  QSPI1_IRQ_Handler
                .long  QSPI2_IRQ_Handler
                .long  QSPI3_IRQ_Handler
                .long  SW_IRQ0_Handler
                .long  SW_IRQ1_Handler
                .long  USB_IRQ_Handler
                .long  RTC_CH3_IRQ_Handler
                .long  DMA_IRQ1_Handler
                .long  DMA_IRQ2_Handler
                .long  DMA_IRQ3_Handler
                .long  DMA_IRQ5_Handler
                .long  DMA_IRQ6_Handler
                .long  DMA_IRQ7_Handler
                .long  TIMER1_IRQ_Handler
                .long  TIMER2_IRQ_Handler
                .long  TIMER3_IRQ_Handler
                .long  SW_IRQ2_Handler
                .long  FP_IRQ_Handler
                .long  RTC_CH1_IRQ_Handler
                .long  RTC_CH2_IRQ_Handler
                .long  AUDIO1_IRQ_Handler
                .long  GPADC1_IRQ_Handler
                .long  I2C3_IRQ_Handler
                .long  USB_PHY_IRQ_Handler
                .long  STIM0_IRQ0_Handler
                .long  STIM0_IRQ1_Handler
                .long  STIM0_IRQ2_Handler
                .long  STIM0_IRQ3_Handler
                .long  STIM1_IRQ0_Handler
                .long  STIM1_IRQ1_Handler
                .long  STIM1_IRQ2_Handler
                .long  STIM1_IRQ3_Handler
                .long  WDT1_IRQ_Handler
                .long  CRYPT1_IRQ_Handler

    .size   __Vectors, . - __Vectors


    .thumb

/* Reset Handler */

    .section .text.Reset_Handler
    .weak  Reset_Handler
    .type  Reset_Handler, %function

Reset_Handler:
                    LDR     R0, =__StackTop      /* set stack pointer */
                    MSR     MSP, R0
                    LDR     R0, =__StackLimit
                    MSR     MSPLIM, R0

                    LDR     R0, =SystemInit
                    BLX     R0

                    /* Copy the data segment initializers from flash to SRAM */
                    MOVS    R1, #0
                    B       LoopCopyCPInit

CopyCPInit:
                    LDR     R3, =_sicp
                    LDR     R3, [R3, R1]
                    STR     R3, [R0, R1]
                    ADDS    R1, R1, #4
LoopCopyCPInit:
                    LDR     R0, =_scp
                    LDR     R3, =_ecp
                    ADDS    R2, R0, R1
                    CMP     R2, R3
                    BCC     CopyCPInit

                    /* Copy the data segment initializers from flash to SRAM */
                    MOVS    R1, #0
                    B       LoopCopyFunctionInit

CopyFunctionInit:
                    LDR     R3, =_siram
                    LDR     R3, [R3, R1]
                    STR     R3, [R0, R1]
                    ADDS    R1, R1, #4
LoopCopyFunctionInit:
                    LDR     R0, =_sram
                    LDR     R3, =_eram
                    ADDS    R2, R0, R1
                    CMP     R2, R3
                    BCC     CopyFunctionInit

                    /* Copy the data segment initializers from flash to SRAM */
                    MOVS    R1, #0
                    B       LoopCopyDataInit

CopyDataInit:
                    LDR     R3, =_sidata
                    LDR     R3, [R3, R1]
                    STR     R3, [R0, R1]
                    ADDS    R1, R1, #4

LoopCopyDataInit:
                    LDR     R0, =_sdata
                    LDR     R3, =_edata
                    ADDS    R2, R0, R1
                    CMP     R2, R3
                    BCC     CopyDataInit
                    LDR     R2, =_sbss
                    B       LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
                    MOVS    R3, #0
                    STR     R3, [R2]
                    ADDS    R2, R2, #4

LoopFillZerobss:
                    LDR     R3, =_ebss
                    CMP     R2, R3
                    BCC     FillZerobss

                    /* Call static constructors */
                    BL      __libc_init_array

                    /* Call the application entry point. */
                    BL      main

LoopForever:
                    B LoopForever

    .size  Reset_Handler, .-Reset_Handler

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function

NMI_Handler:
                MOVS    R0, LR
                MRS     R1, MSP
                MRS     R2, PSP
                
                LDR     R3, =NMI_Handler_Proc
                BLX     R3
                
                B        .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
                MOVS    R0, LR
                MRS     R1, MSP
                MRS     R2, PSP
                
                LDR     R3, =HardFault_Handler_Proc
                BLX     R3
                    B       .
    .size   HardFault_Handler, . - HardFault_Handler
/* 
; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
*/

/* Set_Default_Handler Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
                    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  Set_Default_Handler handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

                Set_Default_Handler MemoryManagement_Handler
                Set_Default_Handler BusFault_Handler
                Set_Default_Handler UsageFault_Handler
                Set_Default_Handler SVC_Handler
                Set_Default_Handler DebugMon_Handler
                Set_Default_Handler PendSV_Handler
                Set_Default_Handler SysTick_Handler

                Set_Default_Handler RTC_CH0_IRQ_Handler
                Set_Default_Handler GPADC0_IRQ_Handler
                Set_Default_Handler LLC_IRQ_Handler
                Set_Default_Handler I2S_IRQ_Handler
                Set_Default_Handler QDEC_IRQ_Handler
                Set_Default_Handler AUDIO0_IRQ_Handler
                Set_Default_Handler CRYPT0_IRQ_Handler
                Set_Default_Handler TRNG_IRQ_Handler
                Set_Default_Handler RF_CAL_IRQ_Handler
                Set_Default_Handler UART0_IRQ_Handler
                Set_Default_Handler UART1_IRQ_Handler
                Set_Default_Handler UART2_IRQ_Handler
                Set_Default_Handler SPI0_IRQ_Handler
                Set_Default_Handler SPI1_IRQ_Handler
                Set_Default_Handler I2C0_IRQ_Handler
                Set_Default_Handler I2C1_IRQ_Handler
                Set_Default_Handler I2C2_IRQ_Handler
                Set_Default_Handler DMA_IRQ0_Handler
                Set_Default_Handler DMA_IRQ4_Handler
                Set_Default_Handler TIMER0_IRQ_Handler
                Set_Default_Handler GPIO_IRQ0_Handler
                Set_Default_Handler GPIO_IRQ1_Handler
                Set_Default_Handler GPIO_IRQ2_Handler
                Set_Default_Handler PMU_IRQ_Handler
                Set_Default_Handler QSPI0_IRQ_Handler
                Set_Default_Handler QSPI1_IRQ_Handler
                Set_Default_Handler QSPI2_IRQ_Handler
                Set_Default_Handler QSPI3_IRQ_Handler
                Set_Default_Handler SW_IRQ0_Handler
                Set_Default_Handler SW_IRQ1_Handler
                Set_Default_Handler USB_IRQ_Handler
                Set_Default_Handler RTC_CH3_IRQ_Handler
                Set_Default_Handler DMA_IRQ1_Handler
                Set_Default_Handler DMA_IRQ2_Handler
                Set_Default_Handler DMA_IRQ3_Handler
                Set_Default_Handler DMA_IRQ5_Handler
                Set_Default_Handler DMA_IRQ6_Handler
                Set_Default_Handler DMA_IRQ7_Handler
                Set_Default_Handler TIMER1_IRQ_Handler
                Set_Default_Handler TIMER2_IRQ_Handler
                Set_Default_Handler TIMER3_IRQ_Handler
                Set_Default_Handler SW_IRQ2_Handler
                Set_Default_Handler FP_IRQ_Handler
                Set_Default_Handler RTC_CH1_IRQ_Handler
                Set_Default_Handler RTC_CH2_IRQ_Handler
                Set_Default_Handler AUDIO1_IRQ_Handler
                Set_Default_Handler GPADC1_IRQ_Handler
                Set_Default_Handler I2C3_IRQ_Handler
                Set_Default_Handler USB_PHY_IRQ_Handler
                Set_Default_Handler STIM0_IRQ0_Handler
                Set_Default_Handler STIM0_IRQ1_Handler
                Set_Default_Handler STIM0_IRQ2_Handler
                Set_Default_Handler STIM0_IRQ3_Handler
                Set_Default_Handler STIM1_IRQ0_Handler
                Set_Default_Handler STIM1_IRQ1_Handler
                Set_Default_Handler STIM1_IRQ2_Handler
                Set_Default_Handler STIM1_IRQ3_Handler
                Set_Default_Handler WDT1_IRQ_Handler
                Set_Default_Handler CRYPT1_IRQ_Handler

    .end
