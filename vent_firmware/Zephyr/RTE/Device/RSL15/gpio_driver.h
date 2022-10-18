/**
 * @file gpio_driver.h
 * @brief GPIO Driver implementation
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

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <hw.h>
#include "RTE_Device.h"
#include <Driver_GPIO.h>

#if (!RTE_GPIO)
  #error "GPIO not configured in RTE_Device.h!"
#endif    /* if (!RTE_GPIO) */

/* GPIO interrupt handlers prototypes */
#if (RTE_GPIO_GPIO0_INT_EN)
void GPIO0_IRQHandler(void);
#endif
#if (RTE_GPIO_GPIO1_INT_EN)
void GPIO1_IRQHandler(void);
#endif
#if (RTE_GPIO_GPIO2_INT_EN)
void GPIO2_IRQHandler(void);
#endif
#if (RTE_GPIO_GPIO3_INT_EN)
void GPIO3_IRQHandler(void);
#endif

/* GPIO flags */
#define GPIO_FLAG_INITIALIZED      ((uint8_t)(1U))
#define GPIO_FLAG_POWERED          ((uint8_t)(1U << 1))
#define GPIO_FLAG_CONFIGURED       ((uint8_t)(1U << 2))

/* GPIO PADs number */
#define GPIO_PADS_NUMBER         16

/* GPIO interrupts number */
#define GPIO_INT_NUMBER          4

/* GPIO alternative function registers number */
#define GPIO_ALT_FUNC_REG_NUMBER (GPIO_FUNC_REG_JTAG_SW_PAD - GPIO_FUNC_REG_SPI0)

/* GPIO flags */
#define GPIO_FLAG_BIT_SET        1U

/* GPIO input mode mask */
#define GPIO_INPUT_MODE_MASK     (0xF00)

/* GPIO SPI1 bit-band alias */
#define GPIO_SRC_SPI1             (GPIO_SRC_SPI + 1)

/* GPIO SPI1 bit-band alias */
#define GPIO_SRC_I2C1             (GPIO_SRC_I2C + 1)

/* GPIO enabled driver mask */
#define GPIO_EN_MSK      ((RTE_GPIO0_EN    << GPIO_0)  | \
                          (RTE_GPIO1_EN    << GPIO_1)  | \
                          (RTE_GPIO2_EN    << GPIO_2)  | \
                          (RTE_GPIO3_EN    << GPIO_3)  | \
                          (RTE_GPIO4_EN    << GPIO_4)  | \
                          (RTE_GPIO5_EN    << GPIO_5)  | \
                          (RTE_GPIO6_EN    << GPIO_6)  | \
                          (RTE_GPIO7_EN    << GPIO_7)  | \
                          (RTE_GPIO8_EN    << GPIO_8)  | \
                          (RTE_GPIO9_EN    << GPIO_9)  | \
                          (RTE_GPIO10_EN   << GPIO_10) | \
                          (RTE_GPIO11_EN   << GPIO_11) | \
                          (RTE_GPIO12_EN   << GPIO_12) | \
                          (RTE_GPIO13_EN   << GPIO_13) | \
                          (RTE_GPIO14_EN   << GPIO_14) | \
                          (RTE_GPIO15_EN   << GPIO_15))

/* GPIO INT enabled driver mask */
#define GPIO_INT_EN_MSK  ((RTE_GPIO_GPIO0_INT_EN    << GPIO_INT_0) | \
                          (RTE_GPIO_GPIO1_INT_EN    << GPIO_INT_1) | \
                          (RTE_GPIO_GPIO2_INT_EN    << GPIO_INT_2) | \
                          (RTE_GPIO_GPIO3_INT_EN    << GPIO_INT_3))


/* GPIO interrupts info */
typedef struct _GPIO_INT_INFO_t
{
    const IRQn_Type         irqn[GPIO_INT_NUMBER];                /* GPIO irq numbers */
    GPIO_SignalEvent_t      cb;                                   /* GPIO event callback */
} GPIO_INT_INFO_t;

/* GPIO run-time info */
typedef const struct _GPIO_INFO_t
{
    const GPIO_CFG_t        *default_cfg;                         /* GPIO default main configuration */
    const GPIO_PAD_CFG_t    *default_pad_cfg[GPIO_PADS_NUMBER];   /* GPIO default configuration */
    const GPIO_INT_CFG_t    *default_int_cfg[GPIO_INT_NUMBER];    /* GPIO interrupts default configuration */
    const GPIO_PRI_CFG_t    *default_pri_cfg[GPIO_INT_NUMBER];    /* GPIO int priority default configuration */
    const GPIO_EXTCLK_CFG_t *default_extclk_cfg;                  /* GPIO default external clock configuration */
    const GPIO_JTAG_SW_CFG_t *default_jtag_sw_cfg;                /* GPIO default SWJ-DP configuration */
} GPIO_INFO_t;

/* GPIO Resources definition */
typedef struct
{
    GPIO_INFO_t             *info;                                /* Run-time info */
    GPIO_INT_INFO_t          intInfo;                             /* IRQs Info */
} GPIO_RESOURCES;

#endif    /* GPIO_DRIVER_H */
