/**
 * @file dma_driver.h
 * @brief DMA driver header
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

#ifndef DMA_DRIVER_H
#define DMA_DRIVER_H

#include <hw.h>
#include <RTE_Device.h>
#include <Driver_DMA.h>
#include <stdint.h>
#include <stdlib.h>

#if (!RTE_DMA)
  #error "DMA not configured in RTE_Device.h!"
#endif    /* if (!RTE_DMA) */

/* DMA interrupt handlers prototypes */
#if (RTE_DMA0_EN)
void DMA0_IRQHandler(void);
#endif
#if (RTE_DMA1_EN)
void DMA1_IRQHandler(void);
#endif
#if (RTE_DMA2_EN)
void DMA2_IRQHandler(void);
#endif
#if (RTE_DMA3_EN)
void DMA3_IRQHandler(void);
#endif
DMA_Type * DMA_GetChannel(DMA_SEL_t sel);

/* DMA channels number */
#define DMA_CHANNELS_NUMBER     4

/* DMA flags */
#define DMA_FLAG_BIT_SET       1U
#define DMA_FLAG_BIT_CLR       0U


/* DMA address inc mode mask */
#define DMA_ADDR_INC_MSK       1U

/* DMA enabled driver mask */
#define DMA_EN_MSK            ((RTE_DMA0_EN  << DMA_CH_0) | \
                               (RTE_DMA1_EN  << DMA_CH_1) | \
                               (RTE_DMA2_EN  << DMA_CH_2) | \
                               (RTE_DMA3_EN  << DMA_CH_3))

/* DMA auto configuration enabled driver mask */
#define DMA_EN_AUTO_MSK      (((RTE_DMA0_AUTO_EN  << DMA_CH_0)  | \
                               (RTE_DMA1_AUTO_EN  << DMA_CH_1)  | \
                               (RTE_DMA2_AUTO_EN  << DMA_CH_2)  | \
                               (RTE_DMA3_AUTO_EN  << DMA_CH_3)) & \
                                DMA_EN_MSK)

/* DMA interrupts info */
typedef struct _DMA_INT_INFO_t
{
    const IRQn_Type       irqn[DMA_CHANNELS_NUMBER];                  /* DMA irqs numbers */
    DMA_SignalEvent_t     cb[DMA_CHANNELS_NUMBER];                    /* DMA channels handler functions */
} DMA_INT_INFO_t;

/* DMA runtime info */
typedef struct _DMA_INFO_t
{
    const DMA_CFG_t      *const default_cfg[DMA_CHANNELS_NUMBER];     /* DMA default configuration */
    const DMA_PRI_CFG_t  *const default_pri_cfg[DMA_CHANNELS_NUMBER]; /* DMA priorities default configuration */
    uint8_t               flags;                                      /* DMA state */
} DMA_INFO_t;

/* DMA Resources definition */
typedef struct
{
    DMA_INFO_t           *info;                                       /* Run-time info */
    DMA_INT_INFO_t        intInfo;                                    /* IRQs Info */
} DMA_RESOURCES_t;

#endif /* DMA_DRIVER_H */
