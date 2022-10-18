/**
 * @file timer_driver.h
 * @brief Timer Driver header file
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

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <RTE_Device.h>
#include <hw.h>
#include <Driver_TIMER.h>

#if (!RTE_TIMER)
  #error "TIMER not configured in RTE_Device.h!"
#endif    /* if (!RTE_TIMER) */

/* Timer interrupt callbacks prototypes */
#if (RTE_TIMER0_EN)
void TIMER0_IRQHandler(void);
#endif
#if (RTE_TIMER1_EN)
void TIMER1_IRQHandler(void);
#endif
#if (RTE_TIMER2_EN)
void TIMER2_IRQHandler(void);
#endif
#if (RTE_TIMER3_EN)
void TIMER3_IRQHandler(void);
#endif
#if (RTE_SYSTICK_EN)
void SysTick_Handler(void);
#endif

/* Return TIMER_TYPE */
TIMER_Type * getTimer(TIMER_SEL_t sel);


/* Timers number */
#define TIMER_TIMERS_NUMBER  5


/* Timer flags */
#define TIMER_FLAG_BIT_SET   1U

/* Timer enabled driver mask */
#define TIMER_EN_MSK        ((RTE_TIMER0_EN  << TIMER_0) | \
                             (RTE_TIMER1_EN  << TIMER_1) | \
                             (RTE_TIMER2_EN  << TIMER_2) | \
                             (RTE_TIMER3_EN  << TIMER_3) | \
                             (RTE_SYSTICK_EN << TIMER_SYSTICK))

/* Timer regular enabled driver mask */
#define TIMER_REG_EN_MSK    ((RTE_TIMER0_EN  << TIMER_0) | \
                             (RTE_TIMER1_EN  << TIMER_1) | \
                             (RTE_TIMER2_EN  << TIMER_2) | \
                             (RTE_TIMER3_EN  << TIMER_3))

/* Timer GPIO enabled driver mask */
#define TIMER_GPIO_EN_MSK   ((RTE_GPIO0_EN  << TIMER_0) | \
                             (RTE_GPIO1_EN  << TIMER_1) | \
                             (RTE_GPIO2_EN  << TIMER_2) | \
                             (RTE_GPIO3_EN  << TIMER_3))

/* Timer interrupts info */
typedef struct _TIMER_INT_INFO_t
{
    const IRQn_Type          irqn[TIMER_TIMERS_NUMBER];              /* Timer / SysTick IRQ numbers */
    TIMER_SignalEvent_t      cb;                                     /* Timer / SysTick event callback */
} TIMER_INT_INFO_t;

/* Timer runtime info */
typedef struct _TIMER_INFO_t
{
    const TIMER_CFG_t       *default_cfg[TIMER_TIMERS_NUMBER];       /* Timer default configuration */
    const TIMER_PRI_CFG_t   *default_pri_cfg[TIMER_TIMERS_NUMBER];   /* Timer priorities default configuration */
    uint8_t                  flags;                                  /* Timer state */
} TIMER_INFO_t;

/* Timer Resources definition */
typedef struct
{
    TIMER_INFO_t            *info;                                   /* Run-time info */
    TIMER_INT_INFO_t         intInfo;                                /* IRQs Info */
} TIMER_RESOURCES_t;

#endif /* TIMER_DRIVER_H */
