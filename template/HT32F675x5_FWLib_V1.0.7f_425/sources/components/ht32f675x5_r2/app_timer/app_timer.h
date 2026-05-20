/*************************************************************************************************************
 * @file    app_timer.h
 * @version V1.0
 * @date    2022-11-01
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


#ifndef __APP_TIMER_H__
#define __APP_TIMER_H__

/**
 * @brief  Enumeration and struct definition.
 */
typedef enum
{
    APP_TIMER_MODE_ONCE,
    APP_TIMER_MODE_REPEAT

} EN_APP_TIMER_MODE_T;

#define IS_VALID_APP_TIMER_MODE(MODE) ((MODE) <= APP_TIMER_MODE_REPEAT)

typedef enum
{
    APP_TIMER_STATUS_IDLE    = 0,
    APP_TIMER_STATUS_READY   = 1,
    APP_TIMER_STATUS_RUNNING = 2

} EN_APP_TIMER_STATUS_T;

typedef void (*app_timer_timeout_handler_t)(void *pContext);

typedef struct stAppTimerNode
{
    uint32_t              u32CurrentTimeout;
    uint32_t              u32ChangedTimeout;
    uint32_t              u32Compare;
    uint32_t              u32Base;
    uint32_t              u32ChangedBase;
    bool                  bIsContextChanged;
    bool                  bIsStatusChanged;
    EN_APP_TIMER_STATUS_T enCurrentStatus;
    EN_APP_TIMER_STATUS_T enChangedStatus;
    EN_APP_TIMER_MODE_T   enMode;

    app_timer_timeout_handler_t pfnHandler;

    void                  *pCurrentContext;
    void                  *pChangedContext;
    struct stAppTimerNode *pstNext;
    struct stAppTimerNode *pstLast;

} stAppTimerNode_t;

/**
 * @brief  Timer RTC interrupt handler.
 */
extern void timer_rtc_int_handlder(void);

/**
 * @brief  App timer initialize function, before use rtc timer, please call this function.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T app_timer_init(void);

/**
 * @brief  Create a timer.
 * @param  pstTimer: If create the timer successed, this point will save the new timer id.
 * @param  enMode: Work mode, @ref EN_APP_TIMER_MODE_T.
 * @param  pfnHandler: Function to be executed when the timer expires.
 * @return HW status: @ref EN_ERR_STA_T
 */
extern EN_ERR_STA_T app_timer_create(stAppTimerNode_t *pstTimer, EN_APP_TIMER_MODE_T enMode,
                                     app_timer_timeout_handler_t pfnHandler);

/**
 * @brief  Start the timer.
 * @param  pstTimer: Point that the timer should be initialized.
 * @param  u32Time: timer out value unit ms, 0~131072000ms.
 * @param  pContext: point to the parameter when the timerout happened will send to the timerout handler.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T app_timer_start(stAppTimerNode_t *pstTimer, uint32_t u32Time, void *pContext);

/**
 * @brief  Stop a specified timer.
 * @param  pstTimer: point to the timer will be stop.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T app_timer_stop(stAppTimerNode_t *pstTimer);

/**
 * @brief  Stop one timer. after this, the timer can be restart.
 * @param  pstTimer: point to the timer will be stop.
 * @return HW status: @ref EN_ERR_STA_T.
 */
extern EN_ERR_STA_T app_timer_delete(stAppTimerNode_t *pstTimer);

#endif /* __APP_TIMER_H__ */
