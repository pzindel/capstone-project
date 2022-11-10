/**
 * @file Driver_PWM.h
 * @brief PWM Driver header file
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

#ifndef DRIVER_PWM_H_
#define DRIVER_PWM_H_

/** @addtogroup CMSISDRVg
 *  @{
 */
/**
 * @defgroup CMSISDRVPWMg CMSIS PWM Driver
 * @brief CMSIS PWM Driver Reference
 * @{
 */

#ifdef  __cplusplus
extern "C"
{
#endif

#include <Driver_Common.h>

#define ARM_PWM_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /**< PWM API version  */

/****** PWM Control Codes *****/

/** PWM Control Codes: PWM Selection */
typedef enum _PWM_SEL_t {
    PWM_0 = 0,                                     /**< PWM module 0 */
    PWM_1 = 1,                                     /**< PWM module 1 */
    PWM_2 = 2,                                     /**< PWM module 2 */
    PWM_3 = 3,                                     /**< PWM module 3 */
    PWM_4 = 4,                                     /**< PWM module 4 */
} PWM_SEL_t;

/*----- PWM Control Codes: Error codes -----*/
#define PWM_ERROR_UNCONFIGURED  (ARM_DRIVER_ERROR_SPECIFIC - 1)     /**< Driver has not been configured yet */

/* Function documentation */
/**
  \fn          ARM_DRIVER_VERSION PWM_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          int32_t PWM_Initialize (void)
  \brief       Initialize PWM driver with default configuration.
  \return      \ref execution_status

  \fn          int32_t PWM_Configure (PWM_SEL_t sel, const PWM_CFG_t *pwm_cfg)
  \brief       Configure PWM common setting.
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   pwm_cfg Pointer to \ref PWM_CFG_t
  \return      \ref execution_status

  \fn          int32_t PWM_SelectClock (uint8_t clock_src, uint8_t slowclk_prescale)
  \brief       Select the PWM clock source.
  \param[in]   clock_src        Clock source for the PWM block
  \param[in]   slowclk_prescale Prescale to divide SYSCLK into SLOWCLK
  \return      \ref execution_status

  \fn          int32_t PWM_Reset (PWM_SEL_t sel)
  \brief       Reset the PWM.
  \param[in]   sel PWM to be reset \ref PWM_SEL_t
  \return      \ref execution_status

  \fn          int32_t PWM_SetDithering (PWM_SEL_t sel, uint8_t dithering)
  \brief       Set the PWM dithering.
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   dithering PWM dithering value
  \return      \ref execution_status

  \fn          int32_t PWM_SetPeriod (PWM_SEL_t sel, uint16_t period)
  \brief       Set the PWM period.
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   period Period value
  \return      \ref execution_status

  \fn          int32_t PWM_SetDutyCycle (PWM_SEL_t sel, uint8_t duty_cycle)
  \brief       Set the PWM duty cycle (expressed in percentage)
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   duty_cycle Duty cycle value (expressed in percentage)
  \return      \ref execution_status

  \fn          int32_t PWM_SetHighPeriod (PWM_SEL_t sel, uint16_t high_period)
  \brief       Set the PWM duty cycle (expressed in cycles).
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   high_period Duty cycle value (expressed in cycles)
  \return      \ref execution_status

  \fn          int32_t PWM_SetOffset (PWM_SEL_t sel, uint16_t offset)
  \brief       Set the offset between PWM.
  \param[in]   sel PWM to be configured \ref PWM_SEL_t
  \param[in]   offset Offset between PWM
  \return      \ref execution_status

  \fn          int32_t PWM_Start (PWM_SEL_t sel)
  \brief       Start the PWM.
  \param[in]   sel PWM to be started \ref PWM_SEL_t
  \return      \ref execution_status

  \fn          int32_t PWM_Stop (PWM_SEL_t sel)
  \brief       Stop the PWM.
  \param[in]   sel PWM to be stopped \ref PWM_SEL_t
  \return      \ref execution_status
*/


/**
\brief PWM Driver configuration.
*/
typedef struct _PWM_CFG_t
{
    uint32_t          period       :12;    /**< Period value     */
    uint32_t          high_cycle   :12;    /**< High cycle value */
    uint32_t          dithering    :8;     /**< Dithering value  */
    uint32_t          offset       :12;    /**< Offset value     */
} PWM_CFG_t;

/**
\brief Access structure of the PWM Driver.
*/
typedef struct _DRIVER_PWM_t {
    ARM_DRIVER_VERSION (*GetVersion)    (void);                                         /**< Pointer to \ref PWM_GetVersion : Get driver version.                */
    int32_t            (*Initialize)    (void);                                         /**< Pointer to \ref PWM_Initialize : Initialize PWM driver.             */
    int32_t            (*Configure)     (PWM_SEL_t sel, const PWM_CFG_t * pwm_cfg);     /**< Pointer to \ref PWM_Configure : Configure PWM common setting.       */
    int32_t            (*SelectClock)   (uint8_t clock_src, uint8_t slowclk_prescale);  /**< Pointer to \ref PWM_SelectClock : Configure PWM clock source.       */
    int32_t			   (*Reset)			(PWM_SEL_t sel);							    /**< Pointer to \ref PWM_Reset : Reset PWM                               */
    int32_t			   (*SetDithering)	(PWM_SEL_t sel, uint8_t dithering);			    /**< Pointer to \ref PWM_SetDithering : Add dithering to PWM channel.    */
    int32_t            (*SetPeriod)     (PWM_SEL_t sel, uint16_t period);               /**< Pointer to \ref PWM_SetPeriod : Set the period.                     */
    int32_t            (*SetDutyCycle)  (PWM_SEL_t sel, uint8_t duty_cycle);            /**< Pointer to \ref PWM_SetDutyCycle : Set the duty cycle (percentage). */
    int32_t            (*SetHighPeriod) (PWM_SEL_t sel, uint16_t high_period);          /**< Pointer to \ref PWM_SetHighPeriod : Set the high cycle period.      */
    int32_t            (*SetOffset) 	(PWM_SEL_t sel, uint16_t offset);               /**< Pointer to \ref PWM_SetOffset : Set offset between PWM.             */
    int32_t            (*Start)         (PWM_SEL_t sel);                                /**< Pointer to \ref PWM_Start : Start the PWM.                          */
    int32_t            (*Stop)          (PWM_SEL_t sel);                                /**< Pointer to \ref PWM_Stop : Stop the PWM.                            */
} const DRIVER_PWM_t;

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of the CMSISDRVPWMg group */
/** @} */ /* End of the CMSISDRVg group */

#endif /* DRIVER_PWM_H_ */
