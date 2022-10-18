/**
 * @file pwm_driver.h
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

#ifndef PWM_RSLXX_H
#define PWM_RSLXX_H

#include <RTE_Device.h>
#include <Driver_GPIO.h>
#include <Driver_PWM.h>
#include <hw.h>

#if (!RTE_PWM)
  #error "PWM not configured in RTE_Device.h!"
#endif    /* if (!RTE_PWM) */

/* Extern GPIO driver */
extern DRIVER_GPIO_t Driver_GPIO;

/* PWM flags */
#define PWM_FLAG_BIT_SET      1U

/* PWM enabled driver mask */
#define PWM_EN_MSK            ((RTE_PWM0_EN << PWM_0) | \
                               (RTE_PWM1_EN << PWM_1) | \
							   (RTE_PWM2_EN << PWM_2) | \
							   (RTE_PWM3_EN << PWM_3) | \
							   (RTE_PWM4_EN << PWM_4))

/* PWM max values */
#define PWM_MAX_PERCENTAGE     100UL
#define PWM_MAX_DITHERING      256

/* PWM number */
#define PWM_PWMS_NUMBER        5

/* PWM module GPIO default configuration */
typedef struct _PWM_GPIO_DEFAULT_CFG_t
{
    uint8_t                   GPIO_pin     :8;                      /* GPIO selection */
} PWM_GPIO_DEFAULT_CFG_t;

/* PWM default configuration */
typedef const struct _PWM_DEFAULT_CFG_t
{
    PWM_CFG_t                  pwm_default_cfg;                     /* PWM default configuration */
    PWM_GPIO_DEFAULT_CFG_t     pwm_default_GPIO_cfg;                /* PWM GPIO default configuration */
} PWM_DEFAULT_CFG_t;

/* PWM interrupt info */
typedef struct _PWM_INFO_t
{
    uint8_t                   flags;                               /* Current PWM flags */
    const PWM_DEFAULT_CFG_t  *const default_cfg[PWM_PWMS_NUMBER];  /* PWM default configuration */
} PWM_INFO_t;

/* PWM Resources definition */
typedef struct
{
    PWM_INFO_t               *info;                                /* Run-time information */
} PWM_RESOURCES_t;

#endif /* PWM_RSLXX_H */
