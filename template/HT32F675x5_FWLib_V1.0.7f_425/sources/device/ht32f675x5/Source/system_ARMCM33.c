/**************************************************************************//**
 * @file     system_ARMCM33.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM33 Device
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//this file has been modified


#include "ARMCM33_DSP_FP.h"


/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  extern uint32_t __VECTOR_TABLE;
#endif


/*----------------------------------------------------------------------------
  Local Variables
 *----------------------------------------------------------------------------*/
#define MP_REMAP_ENABLE   1
#define PERI_IRQ_NUM_MAX  59

uint32_t __NEW_VECTOR_TABLE[PERI_IRQ_NUM_MAX + 16] __attribute__((aligned(512), section(".bss.new_vector")));


/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemInit (void)
{
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
    #if MP_REMAP_ENABLE
        uint32_t u32VectorIndex = 0;
        volatile uint32_t *pu32VectorTable = 0;

        pu32VectorTable = (volatile uint32_t *) &__VECTOR_TABLE;

        for(u32VectorIndex = 0; u32VectorIndex < PERI_IRQ_NUM_MAX + 16; u32VectorIndex++) //+16:internal irq
        {
            __NEW_VECTOR_TABLE[u32VectorIndex] = pu32VectorTable[u32VectorIndex];
        }

        SCB->VTOR = (uint32_t) __NEW_VECTOR_TABLE;
    #else
        SCB->VTOR = (uint32_t) &__VECTOR_TABLE;
    #endif
#else
#endif

///already enabled in ROM
#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U*2U) |           /* enable CP10 Full Access */
                 (3U << 11U*2U)  );         /* enable CP11 Full Access */
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
  SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  TZ_SAU_Setup();
#endif

  /* enable MemManageFault handler*/
  //NVIC_SetPriority(MemoryManagement_IRQn,0);
  //SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* enable BusFault handler*/
  //NVIC_SetPriority(BusFault_IRQn,0);
  //SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;

  /* enable UsageFault handler*/
  //NVIC_SetPriority(UsageFault_IRQn,0);
  //SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;

  /* UNALIGN access NOT allowed*/
  //SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;

  ///already enabled in ROM
  /* enable DIVBYZERO fault */
  SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
  
  ///already enabled in ROM
  /* ignore Precise bus faults in error handlers */
  SCB->CCR |= SCB_CCR_BFHFNMIGN_Msk;
}


