/*
MLOG_ID_RANGE: 0x8000~0x803F
MLOG_ID_USED:  0x8000~0x8019
*/
/*************************************************************************************************************
 * @file    err_debug.c
 * @version V1.0
 * @date    2020-05-08
 * @brief   
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "RegHT32F675x5.h"
#include "err_def.h"
#include "hw_wdt.h"

#include "app_cfg.h"
#include "rom_callback.h"

#if APP_DEBUG_ENABLED
    #include "app_debug.h"
#endif

#if MLOG_DEBUG_ENABLED
    #include "mlog.h"
    #include "mlog_protocol.h"
#endif

/**
 * @brief  EXTERN VARIABLES
 */
extern struct OS_TSK os_tsk;

/**
 * @brief  NMI_Handler_Proc
 * @param  u32ExcReturn:
 * @param  u32Msp:
 * @param  u32Psp:
 */
void NMI_Handler_Proc(uint32_t u32ExcReturn, uint32_t u32Msp, uint32_t u32Psp)
{
#if APP_DEBUG_ENABLED
    app_debug_reinit();
    PRINTF("NMI_Handler: %08X, %08X, %08X\n", u32ExcReturn, u32Msp, u32Psp);
    app_debug_printf();
#endif
    for (;;);
}

/**
 * @brief  HardFault_Handler_Proc
 * @param  u32ExcReturn:
 * @param  u32Msp:
 * @param  u32Psp:
 */
void HardFault_Handler_Proc(uint32_t u32ExcReturn, uint32_t u32Msp, uint32_t u32Psp)
{
#if APP_DEBUG_ENABLED
    app_debug_reinit();
#endif

    PRINTF("[HardFault_Handler]Current msp: 0x%08X\n", __get_MSP());

    volatile uint32_t *u32Sp = NULL;

    if (u32ExcReturn & 0x08)
    {
        PRINTF("Occured in task.\n");
    }
    else
    {
        PRINTF("Occured in interrupt.\n");
    }

    if (u32ExcReturn & 0x04)
    {
        PRINTF("Using u32Psp.\n");
        u32Sp = (volatile uint32_t *)u32Psp;
    }
    else
    {
        PRINTF("Using u32Msp.\n");
        u32Sp = (volatile uint32_t *)u32Msp;
    }

    PRINTF("Stack frame:\n");
    PRINTF("R0  : 0x%08X\n", u32Sp[0]);
    PRINTF("R1  : 0x%08X\n", u32Sp[1]);
    PRINTF("R2  : 0x%08X\n", u32Sp[2]);
    PRINTF("R3  : 0x%08X\n", u32Sp[3]);
    PRINTF("R12 : 0x%08X\n", u32Sp[4]);
    PRINTF("LR  : 0x%08X\n", u32Sp[5]);
    PRINTF("PC  : 0x%08X\n", u32Sp[6]);
    PRINTF("xPSR: 0x%08X\n", u32Sp[7]);

#ifdef __MAIN_PROCESSOR
    volatile uint32_t PC = u32Sp[6];

    if (SCB->HFSR & SCB_HFSR_VECTTBL_Msk)
    {
        PRINTF("Vector Fault\r\n");
    }

    if (SCB->HFSR & SCB_HFSR_DEBUGEVT_Msk)
    {
        PRINTF("Debug Event Fault\r\n");
    }

    if (SCB->HFSR & SCB_HFSR_FORCED_Msk)
    {
        PRINTF("Configurable Fault\r\n");
        if (SCB->CFSR & SCB_CFSR_MEMFAULTSR_Msk)
        {
            PRINTF("MemManage Fault\r\n");
            if (SCB->CFSR & SCB_CFSR_IACCVIOL_Msk)
            {
                PRINTF(
                    "[IACCVIOL]The processor attempted an instruction fetch from a location that "
                    "does not permit execution, PC : 0x%08x\r\n",
                    PC);
            }

            if (SCB->CFSR & SCB_CFSR_DACCVIOL_Msk)
            {
                PRINTF(
                    "[DACCVIOL] The processor attempted a load or store at a location that "
                    "does not permit the operation, PC : 0x%08x\r\n",
                    PC);
                if (SCB->CFSR & SCB_CFSR_MMARVALID_Msk)
                {
                    PRINTF("AT :0x%08x\r\n", SCB->MMFAR);
                }
            }

            if (SCB->CFSR & SCB_CFSR_MUNSTKERR_Msk)
            {
                PRINTF("[MUNSTKERR]Unstack for an exception return has caused one or more access violations\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_MSTKERR_Msk)
            {
                PRINTF("[MSTKERR]Stacking for an exception entry has caused one or more access violations\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_MLSPERR_Msk)
            {
                PRINTF("[MLSPERR]A MemManage fault occurred during floating-point lazy state preservation\r\n");
            }
        }

        if (SCB->CFSR & SCB_CFSR_BUSFAULTSR_Msk)
        {
            PRINTF("Bus Fault\r\n");
            if (SCB->CFSR & SCB_CFSR_IBUSERR_Msk)
            {
                PRINTF("[IBUSERR]instruction bus error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_PRECISERR_Msk)
            {
                PRINTF("[PRECISERR] data bus error has occurred, PC : 0x%08x\r\n", PC);
                if (SCB->CFSR & SCB_CFSR_BFARVALID_Msk)
                {
                    PRINTF("AT :0x%08x\r\n", SCB->BFAR);
                }
            }

            if (SCB->CFSR & SCB_CFSR_IMPRECISERR_Msk)
            {
                PRINTF("[IMPRECISERR]Imprecise data access error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_UNSTKERR_Msk)
            {
                PRINTF("[UNSTKERR]Unstack for an exception return has caused one or more BusFaults\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_STKERR_Msk)
            {
                PRINTF("[STKERR]Stacking for an exception entry has caused one or more BusFaults\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_LSPERR_Msk)
            {
                PRINTF("[LSPERR]A bus fault occurred during floating-point lazy state preservation\r\n");
            }
        }

        if (SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk)
        {
            PRINTF("Usage Fault\r\n");
            if (SCB->CFSR & SCB_CFSR_UNDEFINSTR_Msk)
            {
                PRINTF("[UNDEFINSTR]an undefined instruction error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_INVSTATE_Msk)
            {
                PRINTF("[INVSTATE] an EPSR.T or EPSR.IT validity error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_INVPC_Msk)
            {
                PRINTF("[INVPC]an integrity check error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_NOCP_Msk)
            {
                PRINTF("[NOCP]a coprocessor disabled or not present error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_STKOF_Msk)
            {
                PRINTF("[STKOF]a stack overflow error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_UNALIGNED_Msk)
            {
                PRINTF("[UNALIGNED]an unaligned access error has occurred\r\n");
            }

            if (SCB->CFSR & SCB_CFSR_DIVBYZERO_Msk)
            {
                PRINTF("[DIVBYZERO]an integer division by zero error has occurred\r\n");
            }
        }
    }
#endif

#if APP_DEBUG_ENABLED
    app_debug_printf();
#endif

#if MLOG_DEBUG_ENABLED
    // MUST print mlog first to clear remain data
    // printed data may be corrupted because of reentry of "mlog_protocol_print()"
    mlog_protocol_print();

    MLOG32E(0x8000, "HardFault_Handler, current u32Msp:0x%08X", __get_MSP());
    MLOG32E(0x8001, "u32ExcReturn: 0x%08X\n", u32ExcReturn);
    MLOG32E(0x8002, "u32Msp:        0x%08X\n", u32Msp);
    MLOG32E(0x8003, "u32Psp:        0x%08X\n", u32Psp);
    if (u32ExcReturn & 0x08)
    {
        MLOG0E(0x8004, "Occured in task.\n");
    }
    else
    {
        MLOG0E(0x8005, "Occured in interrupt.\n");
    }

    if (u32ExcReturn & 0x04)
    {
        MLOG0E(0x8006, "Using u32Psp.\n");
        u32Sp = (volatile uint32_t *)u32Psp;
    }
    else
    {
        MLOG0E(0x8007, "Using u32Msp.\n");
        u32Sp = (volatile uint32_t *)u32Msp;
    }
    MLOG32E(0x8008, "R0  : 0x%08X\n", u32Sp[0]);
    MLOG32E(0x8009, "R1  : 0x%08X\n", u32Sp[1]);
    MLOG32E(0x800a, "R2  : 0x%08X\n", u32Sp[2]);
    MLOG32E(0x800b, "R3  : 0x%08X\n", u32Sp[3]);
    MLOG32E(0x800c, "R12 : 0x%08X\n", u32Sp[4]);
    MLOG32E(0x800d, "LR  : 0x%08X\n", u32Sp[5]);
    MLOG32E(0x800e, "PC  : 0x%08X\n", u32Sp[6]);
    MLOG32E(0x800f, "xPSR: 0x%08X\n", u32Sp[7]);
    mlog_protocol_print();
#endif
    for (;;);
}

/**
 * @brief  os_error_handler
 * @param  u32Code:
 *         osRtxErrorStackUnderflow     1U  ///< Stack overflow, i.e. stack pointer below its lower memory limit for descending stacks.
 *         osRtxErrorISRQueueOverflow   2U  ///< ISR Queue overflow detected when inserting object.
 *         osRtxErrorTimerQueueOverflow 3U  ///< User Timer Callback Queue overflow detected for timer.
 *         osRtxErrorClibSpace          4U  ///< Standard C/C++ library libspace not available: increase OS_THREAD_LIBSPACE_NUM.
 *         osRtxErrorClibMutex          5U  ///< Standard C/C++ library mutex initialization failed.
 * @param  pObjectId: 
 * @return 
 */
uint32_t os_error_handler(uint32_t u32Code, void *pObjectId)
{
#if APP_DEBUG_ENABLED
    app_debug_reinit();
#endif

    PRINTF("os err occurs\n");

    PRINTF("code     : 0x%08X\n", u32Code);
    PRINTF("object_id: 0x%08X\n", (uint32_t)pObjectId);

#if APP_DEBUG_ENABLED
    app_debug_printf();
#endif

#if MLOG_DEBUG_ENABLED
    // MUST print mlog first to clear remain data
    // printed data may be corrupted because of reentry of "mlog_protocol_print()"
    mlog_protocol_print();
    MLOG0E(0x8010, "os err occurs\n");
    MLOG32E(0x8011, "code     : 0x%08X\n", u32Code);
    MLOG32E(0x8012, "object_id: 0x%08X\n", (uint32_t)pObjectId);
    mlog_protocol_print();
#endif

    for (;;);
}

/**
 * @brief  Show the error of system assert.
 * @param  adr:
 * @param  info:
 */
void system_assert_debug(uint16_t adr, uint32_t info)
{
    PRINTF("addr: 0x%04X\n", adr);
    PRINTF("info: 0x%08X\n", info);

#if APP_DEBUG_ENABLED
    app_debug_printf();
#endif

#if MLOG_DEBUG_ENABLED
    MLOG3232W(0x8013, "SYSTEM ASSERT ERR : addr:0x%04x info:0x%08x", adr, info);
#endif
}

/**
 * @brief
 * @param  u16ErrModule:
 * @param  u16ErrLine:
 * @param  u32ErrInfo1:
 * @param  u32ErrInfo2:
 */
void system_error_handler(uint16_t u16ErrModule, uint16_t u16ErrLine, uint32_t u32ErrInfo1, uint32_t u32ErrInfo2)
{
#if APP_DEBUG_ENABLED
    app_debug_reinit();

    PRINTF("system error occurs\n");
    PRINTF("u16ErrModule:%u u16ErrLine:%u\n", u16ErrModule, u16ErrLine);
    PRINTF("u32ErrInfo1:%u u32ErrInfo2:%u\n", u32ErrInfo1, u32ErrInfo2);
    app_debug_printf();
#endif

#if MLOG_DEBUG_ENABLED
    // MUST print mlog first to clear remain data
    // printed data may be corrupted because of reentry of "mlog_protocol_print()"
    mlog_protocol_print();
    MLOG0E(0x8014, "system error occurs");
    MLOG1616E(0x8015, "u16ErrModule:%u u16ErrLine:%u", u16ErrModule, u16ErrLine);
    MLOG3232E(0x8016, "u32ErrInfo1:%u u32ErrInfo2:%u", u32ErrInfo1, u32ErrInfo2);
    mlog_protocol_print();

#endif
    ////todo : reboot
    for (;;);
}

void err_debug_init(void)
{
    g_libOsErrorCallback     = os_error_handler;
    g_libSystemErrorCallback = system_error_handler;
}
