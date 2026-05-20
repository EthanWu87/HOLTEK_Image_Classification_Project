;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : utility_asm.s
;  Version          : V1.0
;  Date             : 2020-07-16
;  Description      : 
;-----------------------------------------------------------------------------------------------------------*/

    PRESERVE8
    THUMB

    ; Cortex-M33
    IF  :DEF:__MAIN_PROCESSOR
    AREA |.text|, CODE, READONLY


    ; void delay_cycles(uint32_t cycles)
rom_delay_cycles  PROC
    EXPORT  rom_delay_cycles
    ; cycles /= 4
    LSR R0,R0,#2

    ; if 0 == cycles
    CMP R0,#0
    BEQ RET

LOOP    ;4 cycles
    MOV     R0,R0
    SUBS    R0,#1
    BNE     LOOP

RET
    BX      LR
    ENDP

    ; Cortex-M0P
    ELIF :DEF:__CO_PROCESSOR
    AREA |.text|, CODE, READONLY

    ; void delay_cycles(uint32_t cycles)
rom_delay_cycles  PROC
    EXPORT  rom_delay_cycles

    ; cycles /= 4 
    LSRS    R0,R0,#2

    ; if 0 == cycles
    CMP R0,#0
    BEQ RET

LOOP    ;4 cycles
    MOV     R0,R0
    SUBS    R0,#1
    BNE     LOOP

RET
    BX      LR
    ENDP

    ELSE

    ASSERT  (0>0)  ; unknown core
    
    ENDIF

    END
