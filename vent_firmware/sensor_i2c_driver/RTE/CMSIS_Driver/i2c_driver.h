/**
 * @file i2c_driver.h
 * @brief I2C CMSIS Driver header
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

#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

/* DMA / CM3 code switches */
#define I2C_DMA_CODE_EN (RTE_I2C0_DMA_EN_DEFAULT || RTE_I2C1_DMA_EN_DEFAULT)
#define I2C_CM33_CODE_EN !((RTE_I2C0_DMA_EN_DEFAULT) || (RTE_I2C1_DMA_EN_DEFAULT))

#include <hw.h>
#include "Driver_I2C.h"
#include "RTE_Device.h"
#if (I2C_DMA_CODE_EN)
#include <Driver_DMA.h>
#endif    /* if (I2C_DMA_CODE_EN) */

#if (!RTE_I2C0_ENABLED)
    #warning "I2C0 not configured in RTE_Device.h!"
#endif    /* if (!RTE_I2C0_ENABLED) */

#if (!RTE_I2C1_ENABLED)
#warning "I2C1 not configured in RTE_Device.h!"
#endif    /* if (!RTE_I2C1_ENABLED) */

/* Driver version */
#define ARM_I2C_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

/* Driver status flag definition */
#define I2C_INITIALIZED           ((uint8_t)(1U))
#define I2C_POWERED               ((uint8_t)(1U << 1))
#define I2C_CONFIGURED            ((uint8_t)(1U << 2))

#if (I2C_DMA_CODE_EN)
/* Extern DMA driver */
extern DRIVER_DMA_t Driver_DMA;

/* Extern DMA buffer and DMA channel configurations */
extern DMA_ADDR_CFG_t buffRCfg;
extern DMA_ADDR_CFG_t buffTCfg;
extern DMA_CFG_t dmaCfgR, dmaCfgT;
#endif    /* if (I2C_DMA_CODE_EN) */

/* Constants used to improve code readability */
#define I2C_STATUS_MODE_MASTER           1U
#define I2C_STATUS_MODE_SLAVE            0U
#define I2C_STATUS_DIRECTION_TX          0U
#define I2C_STATUS_DIRECTION_RX          1U

/* Minimum allowed ration between SYSCLK and I2CCLK */
#define SYSCLOCK_I2C_MIN_RATIO           2.5

/* I2C interrupt handler function */
#if (I2C_CM33_CODE_EN)
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
#else    /* if (I2C_CM33_CODE_EN) */
void I2C0_DMA_Handler(uint32_t event);    //I2C0 DMA Channel
void I2C1_DMA_Handler(uint32_t event);    //I2C1 DMA Channel
#endif    /* if (I2C_DMA_CODE_EN) */

/* I2C Pins Configuration */
typedef const struct _I2C_PINS
{
    uint8_t scl;         /* SCL IO Pin number */
    uint8_t sda;         /* SDA IO Pin number */
    uint32_t pin_cfg;    /* LPF, Drive and Pull configuration */
#if (I2C_DMA_CODE_EN)
    uint8_t dma_ch;      /* defines which DMA channel should be used for data transmission */
    DMA_SignalEvent_t dma_cb;    /* defines I2C callback function */
#endif    /* if (I2C_DMA_CODE_EN) */
} I2C_PINS;

/* I2C Transfer Information (Run-Time) */
typedef struct _I2C_TRANSFER_INFO
{
    uint32_t num;        /* Total number of data to transfer */
    uint32_t cnt;        /* Number of data transferred */
    uint8_t  *data;      /* Pointer to data buffer */
    uint8_t  addr;       /* Device address */
    bool     pending;    /* If transfer is pending */
} I2C_TRANSFER_INFO;

/* I2C Information (Run-time) */
typedef struct _I2C_INFO
{
    ARM_I2C_SignalEvent_t cb_event;    /* Event Callback */
    ARM_I2C_STATUS status;             /* Status flags */
    uint8_t state;                     /* Current I2C state */
    uint32_t slave_prescale;           /* I2C slave prescale */
    uint32_t master_prescale;          /* I2C master prescale */
    uint8_t  slave_addr;               /* Slave address */
    uint32_t int_cfg;                  /* I2C interrupt configuration */
#if (I2C_DMA_CODE_EN)
    uint32_t  dma_rx_cfg;              /* DMA channel receiver configuration */
    uint32_t  dma_tx_cfg;              /* DMA channel transmitter configuration */
#endif    /* if (I2C_DMA_CODE_EN) */
} I2C_INFO;

/* I2C Resources definition */
typedef struct
{
    I2C_Type               *reg;       /* I2C peripheral pointer */
    I2C_PINS               *pins;      /* I2C Input/Output pins */
    IRQn_Type              irqn;       /* I2C IRQ Number */
    I2C_INFO               *info;      /* Run-Time Information */
    I2C_TRANSFER_INFO      *xfer;      /* I2C transfer information */
#if (I2C_DMA_CODE_EN)
    DMA_TRG_t              dma_trg;    /* DMA target selection */
#endif    /* if (I2C_DMA_CODE_EN) */
} I2C_RESOURCES;

#endif    /* I2C_DRIVER_H */
