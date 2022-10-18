/**
 * @file Driver_TIMER.h
 * @brief CMSIS Timer Driver header file
 *
 * @copyright @parblock
 * Copyright (c) 2021 Semiconductor Components Industries, LLC (d/b/a
 * onsemi), All Rights Reserved
 *
 * This code is the property of onsemi and may not be redistributed
 * in any form without prior written permission from onsemi.
 * The terms of use and warranty for this code are covered by contractual
 * agreements between onsemi and the licensee.
 *
 * This is Reusable Code.
 * @endparblock
 */

#ifndef DRIVER_TIMER_H_
#define DRIVER_TIMER_H_

/** @addtogroup CMSISDRVg
 *  @{
 */
/**
 * @defgroup CMSISDRVTIMERg CMSIS Timer Driver
 * @brief CMSIS Timer Driver Reference
 * @{
 */
#ifdef  __cplusplus
extern "C"
{
#endif

#include <Driver_Common.h>

#define ARM_TIMER_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /**< Timer API version */

/****** Timer Control Codes *****/

/**
 * @brief Timer selection.
 */
typedef enum _TIMER_SEL_t {
    TIMER_0                       = 0,              /**< Timer module 0.       */
    TIMER_1                       = 1,              /**< Timer module 1.       */
    TIMER_2                       = 2,              /**< Timer module 2.       */
    TIMER_3                       = 3,              /**< Timer module 3.       */
    TIMER_SYSTICK                 = 4               /**< Timer module SysTick. */
} TIMER_SEL_t;

/**
 * @brief Timer mode selection.
 */
typedef enum _TIMER_MODE_t {
     TIMER_MODE_SHOT              = 0x0U,           /**< Timer mode = TIMER_SHOT_MODE_BITBAND. */
     TIMER_MODE_FREE_RUN          = 0x1U            /**< Timer mode = TIMER_FREE_RUN_BITBAND.  */
} TIMER_MODE_t;

/**
 * @brief Timer clock source selection.
 */
typedef enum _TIMER_CLKSRC_t {
    TIMER_SLOWCLOCK_DIV32         = 0x0U,           /**< Timer src = SLOWCLOCK DIV32. */
    TIMER_SLOWCLOCK_DIV2          = 0x1U            /**< Timer src = SLOWCLOCK DIV2.  */
} TIMER_CLKSRC_t;

/**
 * @brief Timer prescale values selection.
 */
typedef enum _TIMER_PRESCALE_t {
    TIMER_PRESCALE_VAL_1          = 0x0U,           /**< Timer prescale = 1.   */
    TIMER_PRESCALE_VAL_2          = 0x1U,           /**< Timer prescale = 2.   */
    TIMER_PRESCALE_VAL_4          = 0x2U,           /**< Timer prescale = 4.   */
    TIMER_PRESCALE_VAL_8          = 0x3U,           /**< Timer prescale = 8.   */
    TIMER_PRESCALE_VAL_16         = 0x4U,           /**< Timer prescale = 16.  */
    TIMER_PRESCALE_VAL_32         = 0x5U,           /**< Timer prescale = 32.  */
    TIMER_PRESCALE_VAL_64         = 0x6U,           /**< Timer prescale = 64.  */
    TIMER_PRESCALE_VAL_128        = 0x7U            /**< Timer prescale = 128. */
} TIMER_PRESCALE_t;

/**
 * @brief Timer multi-count values selection.
 */
typedef enum _TIMER_MULTI_COUNT_t {
    TIMER_MULTI_COUNT_VAL_1       = 0x0U,           /**< Timer multiCount = 1. */
    TIMER_MULTI_COUNT_VAL_2       = 0x1U,           /**< Timer multiCount = 2. */
    TIMER_MULTI_COUNT_VAL_3       = 0x2U,           /**< Timer multiCount = 3. */
    TIMER_MULTI_COUNT_VAL_4       = 0x3U,           /**< Timer multiCount = 4. */
    TIMER_MULTI_COUNT_VAL_5       = 0x4U,           /**< Timer multiCount = 5. */
    TIMER_MULTI_COUNT_VAL_6       = 0x5U,           /**< Timer multiCount = 6. */
    TIMER_MULTI_COUNT_VAL_7       = 0x6U,           /**< Timer multiCount = 7. */
    TIMER_MULTI_COUNT_VAL_8       = 0x7U            /**< Timer multiCount = 8. */
} TIMER_MULTI_COUNT_t;

/**
 * @brief Timer GPIO status.
 */
typedef enum _TIMER_GPIO_STATUS_t {
	TIMER_GPIO_INT_DISABLE_STATUS = 0x0U,           /**< Timer GPIO status = disable. */
	TIMER_GPIO_INT_ENABLE_STATUS  = 0x1U            /**< Timer GPIO status = enable.  */
} TIMER_GPIO_STATUS_t;

/**
 * @brief Timer GPIO capture mode.
 */
typedef enum _TIMER_GPIO_INT_MODE_t {
	TIMER_GPIO_SINGLE_MODE        = 0x0U,           /**< Timer capture mode = single.     */
	TIMER_GPIO_CONTINUOUS_MODE    = 0x1U            /**< Timer capture mode = continuous. */
} TIMER_GPIO_INT_MODE_t;

/**
 * @brief Timer GPIO interrupt selection.
 */
typedef enum _TIMER_GPIO_t {
    TIMER_GPIO_0                  = 0x0U,            /**< Timer GPIO interrupt 0. */
    TIMER_GPIO_1                  = 0x1U,            /**< Timer GPIO interrupt 1. */
    TIMER_GPIO_2                  = 0x2U,            /**< Timer GPIO interrupt 2. */
    TIMER_GPIO_3                  = 0x3U,            /**< Timer GPIO interrupt 3. */
} TIMER_GPIO_t;

/**
 * @brief Timer SysTick Clock sources.
 */
typedef enum _TIMER_SYSTICK_CLKSRC_t {
    SYSTICK_CLKSOURCE_EXTREFCLK   = 0x0U,           /**< SysTick Timer CLK src = external ref. */
    SYSTICK_CLKSOURCE_CORECLK     = 0x1U            /**< SysTick Timer CLK src = core CLK.     */
} TIMER_SYSTICK_CLKSRC_t;

/**
 * @brief Timer interrupt events selection.
 */
typedef enum _ADC_EVENT_t {
    TIMER_TIMER0_EVENT   = 1 << TIMER_0,            /**< Timer0 event.  */
    TIMER_TIMER1_EVENT   = 1 << TIMER_1,            /**< Timer1 event.  */
    TIMER_TIMER2_EVENT   = 1 << TIMER_2,            /**< Timer2 event.  */
    TIMER_TIMER3_EVENT   = 1 << TIMER_3,            /**< Timer3 event.  */
    TIMER_SYSTICK_EVENT  = 1 << TIMER_SYSTICK       /**< SysTick event. */
} ADC_EVENT_t;

/*----- Timer Control Codes: Error codes -----*/
#define TIMER_ERROR_UNCONFIGURED  (ARM_DRIVER_ERROR_SPECIFIC - 1) /**< Driver has not been configured yet. */

/* Function documentation */
/**
  \fn          ARM_DRIVER_VERSION TIMER_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          int32_t TIMER_Initialize (TIMER_SignalEvent_t cb)
  \brief       Initialize Timer driver with default configuration.
  \param[in]   cb Pointer to \ref TIMER_SignalEvent
  \return      \ref execution_status

  \fn          int32_t TIMER_Configure (TIMER_SEL_t sel, const TIMER_CFG_t * cfg)
  \brief       Configure particular Timer.
  \param[in]   sel Timer to be configured (\ref TIMER_SEL_t)
  \param[in]   cfg Pointer to \ref TIMER_CFG_t
  \return      \ref execution_status

  \fn          int32_t TIMER_SetInterruptPriority (TIMER_SEL_t sel, const TIMER_PRI_CFG_t * cfg)
  \brief       Configure the Timer interrupt priority
  \param[in]   sel  Timer to be configured (\ref TIMER_SEL_t)
  \param[in]   cfg  Pointer to \ref TIMER_PRI_CFG_t
  \return      \ref execution_status

  \fn          int32_t TIMER_Start (TIMER_SEL_t sel)
  \brief       Starts the Timer.
  \param[in]   sel Timer number to be started (\ref TIMER_SEL_t)
  \return      \ref execution_status

  \fn          int32_t TIMER_Stop (TIMER_SEL_t sel)
  \brief       Stops the Timer.
  \param[in]   sel Timer number to be stopped (\ref TIMER_SEL_t)
  \return      \ref execution_status

  \fn          int32_t TIMER_SetValue (TIMER_SEL_t sel, uint32_t val)
  \brief       Sets the timeout / reload value of the selected Timer
  \param[in]   sel Timer value to be read (\ref TIMER_SEL_t)
  \param[in]   val Timer value to be set
  \return      \ref execution_status of error status

  \fn          uint32_t TIMER_GetValue (TIMER_SEL_t sel)
  \brief       Returns the current value of Timer
  \param[in]   sel Timer value to be read (\ref TIMER_SEL_t)
  \return      Timer value or 0 if Timer was not enabled

  \fn          uint32_t TIMER_GetValueCapture (TIMER_SEL_t sel)
  \brief       Returns the current value of Timer
  \param[in]   sel Timer value to be read (\ref TIMER_SEL_t)
  \return      Timer capture value or 0 if Timer was not enabled

  \fn          uint32_t TIMER_GetSysTickState (void)
  \brief       Returns 1 if SysTick has already reached 0
  \return      SysTick status or 0 if SysTick was not enabled

  \fn          void TIMER_SignalEvent (uint32_t event)
  \brief       Signal Timer events.
  \param[in]   event Notification mask
  \return      none

  \fn          int32_t TIMER_SetGPIOInterrupt(TIMER_SEL_t sel)
  \brief       Set GPIO interrupt capture status
  \param[in]   sel Timer value to be read (\ref TIMER_SEL_t)
  \return      \ref execution_status
*/

typedef void (*TIMER_SignalEvent_t) (uint32_t event);  /**< Pointer to \ref TIMER_SignalEvent : Signal Timer event. */

/**
\brief Timer Driver configuration.
*/
typedef struct _TIMER_t
{
    TIMER_MODE_t           mode         :1;   /**< Timer mode to be used.        */
    TIMER_CLKSRC_t         clk_src      :1;   /**< Clock source to be used.      */
    TIMER_GPIO_INT_MODE_t  gpio_mode    :1;   /**< GPIO capture mode to be used. */
    uint32_t                            :5;   /**< Reserved.                     */
    TIMER_PRESCALE_t       prescale_val :8;   /**< Timer prescale value.         */
    TIMER_MULTI_COUNT_t    multi_cnt    :4;   /**< Multi count value.            */
    uint32_t                            :4;   /**< Reserved.                     */
    TIMER_GPIO_t           gpio_int     :4;   /**< GPIO value.                   */
    uint32_t               timeout_val;       /**< Timer timeout value.          */
} TIMER_t;

/**
\brief SysTick Driver configuration.
*/
typedef struct _SYSTICK_t
{
    TIMER_SYSTICK_CLKSRC_t clk_src      :1;   /**< Clock source to be used. */
    uint32_t                            :7;   /**< Reserved.                */
    uint32_t               reload_val   :24;  /**< SysTick value.           */
} SYSTICK_t;

/**
\brief Common TIMER driver configuration.
*/
typedef union _TIMER_CFG_t
{
    TIMER_t                timer_cfg;         /**< Timer configuration.   */
    SYSTICK_t              systick_cfg;       /**< SysTick configuration. */
} TIMER_CFG_t;

/**
\brief Timer interrupt priority configuration.
*/
typedef struct _TIMER_PRI_CFG_t
{
    uint32_t               preempt_pri  :3;   /**< Preempt priority.  */
    uint32_t                            :13;  /**< Reserved.          */
    uint32_t               subgrp_pri   :3;   /**< Subgroup priority. */
    uint32_t                            :13;  /**< Reserved.          */
} TIMER_PRI_CFG_t;

/**
\brief Access structure of the TIMER Driver.
*/
typedef struct _DRIVER_TIMER_t {
    ARM_DRIVER_VERSION (*GetVersion)           (void);                                         /**< Pointer to \ref TIMER_GetVersion : Get driver version.                               */
    int32_t            (*Initialize)           (TIMER_SignalEvent_t cb);                       /**< Pointer to \ref TIMER_Initialize : Initialize Timer driver.                          */
    int32_t            (*Configure)            (TIMER_SEL_t sel, const TIMER_CFG_t * cfg);     /**< Pointer to \ref TIMER_Configure : Configure driver.                                  */
    int32_t            (*SetInterruptPriority) (TIMER_SEL_t sel, const TIMER_PRI_CFG_t * pri); /**< Pointer to \ref TIMER_SetInterruptPriority : Configure Timer interrupt priority.     */
    int32_t            (*Start)                (TIMER_SEL_t sel);                              /**< Pointer to \ref TIMER_Start : Start particular Timer.                                */
    int32_t            (*Stop)                 (TIMER_SEL_t sel);                              /**< Pointer to \ref TIMER_Stop : Stop particular Timer.                                  */
    int32_t            (*SetValue)             (TIMER_SEL_t sel, uint32_t value);              /**< Pointer to \ref TIMER_SetValue : Set the particular Timer value.                     */
    int32_t            (*SetGPIOInterrupt)     (TIMER_SEL_t sel);                              /**< Pointer to \ref TIMER_SetGPIOInterrupt : Set GPIO interrupt capture status.          */
    uint32_t           (*GetValue)             (TIMER_SEL_t sel);                              /**< Pointer to \ref TIMER_GetValue : Get the particular Timer value.                     */
    uint32_t           (*GetValueCapture)      (TIMER_SEL_t sel);                              /**< Pointer to \ref TIMER_GetValueCapture : Get the Timer GPIO Interrupt Captured Value. */
    uint32_t           (*GetSysTickState)      (void);                                         /**< Pointer to \ref TIMER_GetSysTickState : Returns 1 if SysTick has already reached 0.  */
} const DRIVER_TIMER_t;

#ifdef  __cplusplus
}
#endif
/** @} */ /* End of the CMSISDRVTIMERg group */
/** @} */ /* End of the CMSISDRVg group */
#endif /* DRIVER_TIMER_H_ */
