;/**************************************************************************//**
; * @file     startup_ARMCM33.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM33 Device
; * @version  V5.4.0
; * @date     12. December 2018
; ******************************************************************************/
;/*
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
; */

;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------

;//this file has been modified

;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Stack_Size      EQU      0x00001000

                AREA     STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE    Stack_Size
__initial_sp


;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Heap_Size       EQU      0x00000000

                IF       Heap_Size != 0                      ; Heap is provided
                AREA     HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE    Heap_Size
__heap_limit
                ENDIF


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA     RESET, DATA, READONLY
                EXPORT   __Vectors
                EXPORT   __Vectors_End
                EXPORT   __Vectors_Size

__Vectors       DCD      __initial_sp                        ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      MemoryManagement_Handler            ; -12 MPU Fault Handler
                DCD      BusFault_Handler                    ; -11 Bus Fault Handler
                DCD      UsageFault_Handler                  ; -10 Usage Fault Handler
                DCD      0                                   ;  -9 Secure Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      DebugMon_Handler                    ;  -4 Debug Monitor Handler
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD      RTC_CH0_IRQ_Handler
                DCD      GPADC0_IRQ_Handler
                DCD      LLC_IRQ_Handler
                DCD      I2S_IRQ_Handler
                DCD      QDEC_IRQ_Handler
                DCD      AUDIO0_IRQ_Handler
                DCD      CRYPT0_IRQ_Handler
                DCD      TRNG_IRQ_Handler
                DCD      RF_CAL_IRQ_Handler
                DCD      UART0_IRQ_Handler
                DCD      UART1_IRQ_Handler
                DCD      UART2_IRQ_Handler
                DCD      SPI0_IRQ_Handler
                DCD      SPI1_IRQ_Handler
                DCD      I2C0_IRQ_Handler
                DCD      I2C1_IRQ_Handler
                DCD      I2C2_IRQ_Handler
                DCD      DMA_IRQ0_Handler
                DCD      DMA_IRQ4_Handler
                DCD      TIMER0_IRQ_Handler
                DCD      GPIO_IRQ0_Handler
                DCD      GPIO_IRQ1_Handler
                DCD      GPIO_IRQ2_Handler
                DCD      PMU_IRQ_Handler
                DCD      QSPI0_IRQ_Handler
                DCD      QSPI1_IRQ_Handler
                DCD      QSPI2_IRQ_Handler
                DCD      QSPI3_IRQ_Handler
                DCD      SW_IRQ0_Handler
                DCD      SW_IRQ1_Handler
                DCD      USB_IRQ_Handler
                DCD      RTC_CH3_IRQ_Handler
                DCD      DMA_IRQ1_Handler
                DCD      DMA_IRQ2_Handler
                DCD      DMA_IRQ3_Handler
                DCD      DMA_IRQ5_Handler
                DCD      DMA_IRQ6_Handler
                DCD      DMA_IRQ7_Handler
                DCD      TIMER1_IRQ_Handler
                DCD      TIMER2_IRQ_Handler
                DCD      TIMER3_IRQ_Handler
                DCD      SW_IRQ2_Handler
                DCD      FP_IRQ_Handler
                DCD      RTC_CH1_IRQ_Handler
                DCD      RTC_CH2_IRQ_Handler
                DCD      AUDIO1_IRQ_Handler
                DCD      GPADC1_IRQ_Handler
                DCD      I2C3_IRQ_Handler
                DCD      USB_PHY_IRQ_Handler
                DCD      STIM0_IRQ0_Handler
                DCD      STIM0_IRQ1_Handler
                DCD      STIM0_IRQ2_Handler
                DCD      STIM0_IRQ3_Handler
                DCD      STIM1_IRQ0_Handler
                DCD      STIM1_IRQ1_Handler
                DCD      STIM1_IRQ2_Handler
                DCD      STIM1_IRQ3_Handler
                DCD      WDT1_IRQ_Handler
                DCD      CRYPT1_IRQ_Handler

                SPACE    (5 * 4)                           ; Interrupts 59 .. 63 are left out
__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors


                AREA     |.text|, CODE, READONLY

; Reset_Handler
Reset_Handler   PROC
                EXPORT   Reset_Handler
                IMPORT   SystemInit
                IMPORT   __main

                LDR      R0, =__initial_sp
                MSR      MSP, R0
                LDR      R0, =__stack_limit
                MSR      MSPLIM, R0                          ; Non-secure version of MSPLIM is RAZ/WI

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX       R0
                ENDP

; NMI_Handler
NMI_Handler PROC
                EXPORT  NMI_Handler
                IMPORT  NMI_Handler_Proc
                
                MOVS    R0, LR
                MRS     R1, MSP
                MRS     R2, PSP
                
                LDR     R3, =NMI_Handler_Proc
                BLX     R3
                
                B        .
                ENDP

; HardFault_Handler
HardFault_Handler PROC
                EXPORT  HardFault_Handler
                IMPORT  HardFault_Handler_Proc
                
                MOVS    R0, LR
                MRS     R1, MSP
                MRS     R2, PSP
                
                LDR     R3, =HardFault_Handler_Proc
                BLX     R3
                
                B        .
                ENDP



; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND

                ; Default exception/interrupt handler
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

                ALIGN


; User setup Stack & Heap

                IF       :LNOT::DEF:__MICROLIB
                IMPORT   __use_two_region_memory
                ENDIF

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END
