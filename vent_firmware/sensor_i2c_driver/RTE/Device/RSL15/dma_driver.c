/**
 * @file dma_driver.c
 * @brief DMA Driver implementation
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

#include <dma_driver.h>

#if RTE_DMA

/* Driver Version Macro */
#define ARM_DMA_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(0, 1)

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_DMA_API_VERSION,
    ARM_DMA_DRV_VERSION
};

#if (RTE_DMA0_EN & RTE_DMA0_AUTO_EN)

/* Set default DMA channel 0 configuration */
static const DMA_CFG_t DMA0_DefaultCfg = {                               /* DMA channel 0 default configuration */
    .src_sel         = (DMA_TRG_t)(RTE_DMA0_SRC_SEL_DEFAULT),            /* DMA channel 0 default source target */
    .src_step        = (DMA_SRC_STEP_t)(RTE_DMA0_SRC_STEP_DEFAULT),      /* DMA channel 0 default source step */
    .word_size       = (DMA_WORD_SIZE_t)(RTE_DMA0_SRC_DEST_WORD_SIZE_DEFAULT),
    .dst_sel         = (DMA_TRG_t)(RTE_DMA0_DST_SEL_DEFAULT),            /* DMA channel 0 default destination target */
    .dst_step        = (DMA_DST_STEP_t)(RTE_DMA0_DST_STEP_DEFAULT),      /* DMA channel 0 default destination step */
    .ch_priority     = (DMA_CH_PRI_t)(RTE_DMA0_CHANNEL_PRIORITY_DEFAULT) /* DMA channel 0 default priority */
};
static const DMA_PRI_CFG_t DMA0_DefaultPri = {                           /* DMA channel 0 default interrupt priority configuration */
    .preempt_pri     = RTE_DMA0_INT_PREEMPT_PRI,                         /* DMA channel 0 default pre-empt priority value */
    .subgrp_pri      = RTE_DMA0_INT_SUBGRP_PRI                           /* DMA channel 0 default subgroup priority value */
};
#endif /* if (RTE_DMA0_EN & RTE_DMA0_AUTO_EN) */

#if (RTE_DMA1_EN & RTE_DMA1_AUTO_EN)

/* Set default DMA channel 1 configuration */
static const DMA_CFG_t DMA1_DefaultCfg = {                                   /* DMA channel 1 default configuration */
    .src_sel         = (DMA_TRG_t)(RTE_DMA1_SRC_SEL_DEFAULT),                /* DMA channel 1 default source target */
    .src_step        = (DMA_SRC_STEP_t)(RTE_DMA1_SRC_STEP_DEFAULT),          /* DMA channel 1 default source step*/
    .word_size       = (DMA_WORD_SIZE_t)(RTE_DMA1_SRC_DEST_WORD_SIZE_DEFAULT),
    .dst_sel         = (DMA_TRG_t)(RTE_DMA1_DST_SEL_DEFAULT),                /* DMA channel 1 default destination target */
    .dst_step        = (DMA_DST_STEP_t)(RTE_DMA1_DST_STEP_DEFAULT),          /* DMA channel 1 default destination step */
    .ch_priority     = (DMA_CH_PRI_t)(RTE_DMA1_CHANNEL_PRIORITY_DEFAULT)     /* DMA channel 1 default priority */
};
static const DMA_PRI_CFG_t DMA1_DefaultPri = {                               /* DMA channel 1 default interrupt priority configuration */
    .preempt_pri     = RTE_DMA1_INT_PREEMPT_PRI,                             /* DMA channel 1 default pre-empt priority value */
    .subgrp_pri      = RTE_DMA1_INT_SUBGRP_PRI                               /* DMA channel 1 default subgroup priority value */
};
#endif /* if (RTE_DMA1_EN & RTE_DMA1_AUTO_EN) */

#if (RTE_DMA2_EN & RTE_DMA2_AUTO_EN)

/* Set default DMA channel 2 configuration */
static const DMA_CFG_t DMA2_DefaultCfg = {                                   /* DMA channel 2 default configuration */
    .src_sel         = (DMA_TRG_t)(RTE_DMA2_SRC_SEL_DEFAULT),                /* DMA channel 2 default source target */
    .src_step        = (DMA_SRC_STEP_t)(RTE_DMA2_SRC_STEP_DEFAULT),          /* DMA channel 2 default source step*/
    .word_size       = (DMA_WORD_SIZE_t)(RTE_DMA2_SRC_DEST_WORD_SIZE_DEFAULT),
    .dst_sel         = (DMA_TRG_t)(RTE_DMA2_DST_SEL_DEFAULT),                /* DMA channel 2 default destination target */
    .dst_step        = (DMA_DST_STEP_t)(RTE_DMA2_DST_STEP_DEFAULT),          /* DMA channel 2 default destination step */
    .ch_priority     = (DMA_CH_PRI_t)(RTE_DMA2_CHANNEL_PRIORITY_DEFAULT)     /* DMA channel 2 default priority */
};
static const DMA_PRI_CFG_t DMA2_DefaultPri = {                               /* DMA channel 2 default interrupt priority configuration */
    .preempt_pri     = RTE_DMA2_INT_PREEMPT_PRI,                             /* DMA channel 2 default pre-empt priority value */
    .subgrp_pri      = RTE_DMA2_INT_SUBGRP_PRI                               /* DMA channel 2 default subgroup priority value */
};
#endif /* if (RTE_DMA2_EN & RTE_DMA2_AUTO_EN) */

#if (RTE_DMA3_EN & RTE_DMA3_AUTO_EN)

/* Set default DMA channel 3 configuration */
static const DMA_CFG_t DMA3_DefaultCfg = {                                   /* DMA channel 3 default configuration */
    .src_sel         = (DMA_TRG_t)(RTE_DMA3_SRC_SEL_DEFAULT),                /* DMA channel 3 default source target */
    .src_step        = (DMA_SRC_STEP_t)(RTE_DMA3_SRC_STEP_DEFAULT),            /* DMA channel 3 default source step*/
    .word_size       = (DMA_WORD_SIZE_t)(RTE_DMA3_SRC_DEST_WORD_SIZE_DEFAULT),
    .dst_sel         = (DMA_TRG_t)(RTE_DMA3_DST_SEL_DEFAULT),                /* DMA channel 3 default destination target */
    .dst_step        = (DMA_DST_STEP_t)(RTE_DMA3_DST_STEP_DEFAULT),          /* DMA channel 3 default destination step */
    .ch_priority     = (DMA_CH_PRI_t)(RTE_DMA3_CHANNEL_PRIORITY_DEFAULT)     /* DMA channel 3 default priority */
};
static const DMA_PRI_CFG_t DMA3_DefaultPri = {                /* DMA channel 3 default interrupt priority configuration */
    .preempt_pri     = RTE_DMA3_INT_PREEMPT_PRI,              /* DMA channel 3 default pre-empt priority value */
    .subgrp_pri      = RTE_DMA3_INT_SUBGRP_PRI                /* DMA channel 3 default subgroup priority value */
};
#endif /* if (RTE_DMA3_EN & RTE_DMA3_AUTO_EN) */

/* DMA run-time information */
static DMA_INFO_t DMA_Info = {
    .flags = 0,                                             /* DMA flags */
#if (RTE_DMA0_EN & RTE_DMA0_AUTO_EN)
    .default_cfg[DMA_CH_0]     = &DMA0_DefaultCfg,          /* DMA channel 0 default configuration */
    .default_pri_cfg[DMA_CH_0] = &DMA0_DefaultPri,          /* DMA channel 0 default interrupt priorities */
#endif /* if (RTE_DMA0_EN & RTE_DMA0_AUTO_EN) */
#if (RTE_DMA1_EN & RTE_DMA1_AUTO_EN)
    .default_cfg[DMA_CH_1]     = &DMA1_DefaultCfg,          /* DMA channel 1 default configuration */
    .default_pri_cfg[DMA_CH_1] = &DMA1_DefaultPri,          /* DMA channel 1 default interrupt priorities */
#endif /* if (RTE_DMA1_EN & RTE_DMA1_AUTO_EN) */
#if (RTE_DMA2_EN & RTE_DMA2_AUTO_EN)
    .default_cfg[DMA_CH_2]     = &DMA2_DefaultCfg,          /* DMA channel 2 default configuration */
    .default_pri_cfg[DMA_CH_2] = &DMA2_DefaultPri,          /* DMA channel 2 default interrupt priorities */
#endif /* if (RTE_DMA2_EN & RTE_DMA2_AUTO_EN) */
#if (RTE_DMA3_EN & RTE_DMA3_AUTO_EN)
    .default_cfg[DMA_CH_3]     = &DMA3_DefaultCfg,          /* DMA channel 3 default configuration */
    .default_pri_cfg[DMA_CH_3] = &DMA3_DefaultPri,          /* DMA channel 3 default interrupt priorities */
#endif /* if (RTE_DMA3_EN & RTE_DMA3_AUTO_EN) */
};

/* DMA resources */
static DMA_RESOURCES_t DMA_Resources =
{
    .info = &DMA_Info,                                      /* DMA run-time information */
    .intInfo = {                                            /* DMA interrupt info */
        .irqn[DMA_CH_0]    = DMA0_IRQn,                     /* DMA channel 0 interrupt number */
        .irqn[DMA_CH_1]    = DMA1_IRQn,                     /* DMA channel 1 interrupt number */
        .irqn[DMA_CH_2]    = DMA2_IRQn,                     /* DMA channel 2 interrupt number */
        .irqn[DMA_CH_3]    = DMA3_IRQn,                     /* DMA channel 3 interrupt number */

        .cb[DMA_CH_0]      = 0,                             /* DMA channel 0 interrupt handler */
        .cb[DMA_CH_1]      = 0,                             /* DMA channel 1 interrupt handler */
        .cb[DMA_CH_2]      = 0,                             /* DMA channel 2 interrupt handler */
        .cb[DMA_CH_3]      = 0,                             /* DMA channel 3 interrupt handler */
    }
};

/**
 * @brief      Driver version
 * @return     ARM_DRIVER_VERSION
 */
static ARM_DRIVER_VERSION DMA_GetVersion (void)
{
    return DriverVersion;
}

/**
 * @brief       Get DMA channel
 * @param[in]   sel DMA channel to be configured
 * @return      DMA_CHANNEL
 */
DMA_Type * DMA_GetChannel(DMA_SEL_t sel){
	DMA_Type * dma;
	switch(sel){
	case DMA_CH_0:
		dma = DMA0;
		break;
	case DMA_CH_1:
		dma = DMA1;
		break;
	case DMA_CH_2:
		dma = DMA2;
		break;
	default:
        dma = DMA3;
        break;
	}
	return dma;
}

/**
 * @brief       Prepare configuration word which can be used for quick DMA
 *              configuration update.
 * @param[in]   cfg DMA channel configuration
 * @return      configuration word
 */
static uint32_t DMA_CreateConfigWord (const DMA_CFG_t *cfg)
{
    /* Configuration word to be returned */
    uint32_t cfgWord;

    /* Set the rest of the configuration word */
    cfgWord = (DMA_COMPLETE_INT_ENABLE | DMA_CNT_INT_ENABLE)        |
    		   (cfg->src_sel<< DMA_CFG0_SRC_SELECT_Pos)             |
			   (cfg->src_step<< DMA_CFG0_SRC_ADDR_STEP_Pos)         |
			   (cfg->dst_sel<< DMA_CFG0_DEST_SELECT_Pos)            |
			   (cfg->dst_step<< DMA_CFG0_DEST_ADDR_STEP_Pos)        |
               (cfg->word_size << DMA_CFG0_SRC_DEST_WORD_SIZE_Pos)  |
               (cfg->ch_priority   << DMA_CFG0_CHANNEL_PRIORITY_Pos);
    /* Return configuration word */
    return cfgWord;
}

/**
 * @brief       Quickly update the DMA configuration.
 * @param[in]   sel DMA channel to be configured
 * @param[in]   cfg DMA channel configuration
 */
static void DMA_SetConfigWord (DMA_SEL_t sel, uint32_t cfg)
{
	DMA_Type * dma = DMA_GetChannel(sel);
    /* Set the configuration word */

    dma->CFG0 =  cfg &
                (((uint32_t)0x1U << DMA_CFG0_BYTE_ORDER_Pos) |
                 ((uint32_t)0x1U << DMA_CFG0_SRC_DEST_TRANS_LENGTH_SEL_Pos) |
                 DMA_CFG0_CHANNEL_PRIORITY_Mask |
                 DMA_CFG0_SRC_SELECT_Mask |
                 DMA_CFG0_DEST_SELECT_Mask |
                 DMA_CFG0_SRC_DEST_WORD_SIZE_Mask |
                 DMA_CFG0_SRC_ADDR_STEP_Mask |
                 DMA_CFG0_DEST_ADDR_STEP_Mask |
                 ((uint32_t)0x1U << DMA_CFG0_SRC_ADDR_LSB_TOGGLE_Pos) |
                 ((uint32_t)0x1U << DMA_CFG0_DEST_ADDR_LSB_TOGGLE_Pos) |
                 ((uint32_t)0x1U << DMA_CFG0_CNT_INT_ENABLE_Pos) |
                 ((uint32_t)0x1U << DMA_CFG0_COMPLETE_INT_ENABLE_Pos));
}

/**
 * @brief       Configure DMA channel
 * @param[in]   sel DMA channel to be configured
 * @param[in]   cfg  DMA channel configuration
 * @param[in]   cb  DMA channel event callback function
 * @return      ARM Driver return code
 */
static int32_t DMA_Configure (DMA_SEL_t sel, const DMA_CFG_t *cfg, DMA_SignalEvent_t cb)
{
    /* Check if correct DMA channel was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        /* Return error - channel is unsupported */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Set the configuration word */
    DMA_SetConfigWord(sel, DMA_CreateConfigWord(cfg));

    /* Set the callback function */
    DMA_Resources.intInfo.cb[sel] = cb;

    /* Indicate that DMAx was Initialized */
    DMA_Resources.info->flags |= DMA_FLAG_BIT_SET << sel;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Configure DMA channel using prepared configuration word
 * @param[in]   sel DMA channel to be configured
 * @param[in]   cfg  DMA channel configuration word
 * @param[in]   cb  DMA channel event callback function
 * @return      ARM Driver return code
 */
static int32_t DMA_ConfigureWord (DMA_SEL_t sel, uint32_t cfg, DMA_SignalEvent_t cb)
{
    /* Check if correct DMA channel was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        /* Return error - channel is unsupported */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Set the configuration word */
    DMA_SetConfigWord(sel, cfg);

    /* Set the callback function */
    DMA_Resources.intInfo.cb[sel] = cb;

    /* Indicate that DMAx was Initialized */
    DMA_Resources.info->flags |= DMA_FLAG_BIT_SET << sel;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Configure DMA channel source and destination address configuration
 * @param[in]   sel DMA channel to be configured
 * @param[in]   cfg  source and destination address configuration configuration
 * @return      ARM Driver return code
 */
static int32_t DMA_ConfigureAddr (DMA_SEL_t sel, const DMA_ADDR_CFG_t *cfg)
{
    /* Check if correct DMA channel was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        /* Return error - channel is unsupported */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Configuration word to be used */
    uint32_t cfgWord;

    /* Prepare the configuration word */
    cfgWord = (((cfg->transfer_len << DMA_CFG1_TRANSFER_LENGTH_Pos) &
                      DMA_CFG1_TRANSFER_LENGTH_Mask) |
                     ((cfg->counter_len << DMA_CFG1_INT_TRANSFER_LENGTH_Pos) &
                      DMA_CFG1_INT_TRANSFER_LENGTH_Mask));
    DMA_Type * dma = DMA_GetChannel(sel);
    /* Set the configuration word */
    dma->CFG1 = cfgWord;

    /* Set the source address */
    dma->SRC_ADDR = (uint32_t)cfg->src_addr;

    /* Set the destination address */
    dma->DEST_ADDR = (uint32_t)cfg->dst_addr;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Configure DMA interrupt priority.
 * @param[in]   sel  DMA channel to be configured
 * @param[in]   cfg interrupt priority configuration
 * @return      ARM_DRIVER_OK
 */
static int32_t DMA_SetInterruptPriority(DMA_SEL_t sel, const DMA_PRI_CFG_t *cfg)
{
    /* Encoded priority value */
    uint32_t encodedPri = 0;

    /* Encode priority configuration word */
    encodedPri = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), cfg->preempt_pri, cfg->subgrp_pri);

    /* Set the DMA priority */
    NVIC_SetPriority(DMA_Resources.intInfo.irqn[sel], encodedPri);

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Initialize the DMA driver
 * @param[in]   cb callback function to be called on DMA event
 * @return      ARM_DRIVER_OK
 */
static int32_t DMA_Initialize(DMA_SignalEvent_t cb)
{
    /* Configure each enabled DMA channel */
    for (int i = 0; i < DMA_CHANNELS_NUMBER; ++i)
    {
        /* Check if particular DMA channel should be initialized */
        if ((DMA_FLAG_BIT_SET << i) & DMA_EN_AUTO_MSK)
        {
            /* Check if DMA channel was already configured */
            if (DMA_Resources.info->flags & (DMA_FLAG_BIT_SET << i))
            {
                continue;
            }

            /* Configure particular DMA */
            DMA_Configure((DMA_SEL_t)(i), DMA_Resources.info->default_cfg[i], cb);

            /* Set the particuar DMA interrupts priority */
            DMA_SetInterruptPriority((DMA_SEL_t)(i), DMA_Resources.info->default_pri_cfg[i]);

            /* Set the callback function */
            DMA_Resources.intInfo.cb[i] = cb;

            /* Indicate that DMA was Initialized */
            DMA_Resources.info->flags |= DMA_FLAG_BIT_SET << i;
        }
    }

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start the particular DMA channel data transfer
 * @param[in]   sel DMA channel to be used
 * @return      Execution status
 */
static int32_t DMA_Start(DMA_SEL_t sel, uint32_t trigger, uint32_t trigger_source)
{
    /* Check if correct DMA channel was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        /* Return unsupported error */
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Check if DMA channel was already configured */
    if (!(DMA_Resources.info->flags & (DMA_FLAG_BIT_SET << sel)))
    {
        /* Return unconfigured error */
        return DMA_ERROR_UNCONFIGURED;
    }
    DMA_Type * dma = DMA_GetChannel(sel);
	
    /* Clear DMA status register */
    dma->STATUS = DMA_COMPLETE_INT_CLEAR;
    dma->CTRL |= DMA_CLEAR_BUFFER | DMA_CLEAR_CNTS;

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(DMA_Resources.intInfo.irqn[sel]);

    /* Enable the interrupt */
    NVIC_EnableIRQ(DMA_Resources.intInfo.irqn[sel]);

    /* Start the DMA */
    dma->CTRL = ((dma->CTRL & ~(DMA_CTRL_MODE_ENABLE_Mask | DMA_CTRL_TRIGGER_SOURCE_Mask)) |
                 (trigger & DMA_CTRL_MODE_ENABLE_Mask) | (trigger_source & DMA_CTRL_TRIGGER_SOURCE_Mask));

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Stop the particular DMA channel data transfer
 * @param[in]   sel DMA channel to be used
 * @return      Execution status
 */
static int32_t DMA_Stop(DMA_SEL_t sel)
{
    /* Check if correct DMA was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Disable the interrupt */
    NVIC_DisableIRQ(DMA_Resources.intInfo.irqn[sel]);

    /* Clear pending flag */
    NVIC_ClearPendingIRQ(DMA_Resources.intInfo.irqn[sel]);
    DMA_Type * dma = DMA_GetChannel(sel);
    /* Stop the DMA */
    dma->CTRL = ((dma->CTRL & ~DMA_CTRL_MODE_ENABLE_Mask) |
                 (DMA_DISABLE & DMA_CTRL_MODE_ENABLE_Mask));

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Return the current counter value of DMA channel
 * @param[in]   sel channel to be read.
 * @return      Channel counter value
 */
static uint32_t DMA_GetCounterValue(DMA_SEL_t sel)
{
    /* Check if correct DMA was selected */
    if (!((DMA_FLAG_BIT_SET << sel) & DMA_EN_MSK))
    {
        /* Return 0 as incorrect DMA channel was selected */
        return 0;
    }
    DMA_Type * dma = DMA_GetChannel(sel);
	
    /* Return DMA channel counter value */
    return (dma->CNTS);
}

/**
 * @brief       Return the DMA channel status. Clear the status register
 *              on read
 * @param[in]   sel Channel number to be read
 * @return      DMA channel status
 */
static DMA_STATUS_t DMA_GetStatus(DMA_SEL_t sel)
{
	DMA_Type * dma = DMA_GetChannel(sel);
	
    /* Get DMA register status value */
    uint32_t reg = dma->STATUS;

    /* Prepare DMA status */
    DMA_STATUS_t status = {
            .active         = (reg >> DMA_STATUS_ACTIVE_Pos)
                               & DMA_FLAG_BIT_SET,
            .completed       = (reg >> DMA_STATUS_COMPLETE_INT_Pos)
                               & DMA_FLAG_BIT_SET,
            .counter_reached = (reg >> DMA_STATUS_CNT_INT_Pos)
                               & DMA_FLAG_BIT_SET,
            .buffer_fill_lvl   = (reg >> DMA_STATUS_SRC_BUFFER_FILL_LVL_Pos)
                               & DMA_FLAG_BIT_SET
    };

    /* Return DMA status */
    return status;
}

#if (RTE_DMA0_EN | RTE_DMA1_EN | RTE_DMA2_EN | RTE_DMA3_EN)

/**
 * @brief       Function called by interrupt handler. Perform requested operations
 *              when interrupt occurs.
 * @param[in]   sel channel selection \ref DMA_SEL_t
 */
static void DMA_IRQHandler(DMA_SEL_t sel)
{
    /* Clear pending flag */
    NVIC_ClearPendingIRQ(DMA_Resources.intInfo.irqn[sel]);

    /* Check if callback was set */
    if (DMA_Resources.intInfo.cb[sel])
    {
        /* Execute application callback */
        DMA_Resources.intInfo.cb[sel] (1 << sel);
    }
}
#endif

#if (RTE_DMA0_EN)
/**
 * @brief       Called by hardware ISR when a DMA event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void DMA0_IRQHandler(void)
{
    /* Call the DMA irq handler */
    DMA_IRQHandler(DMA_CH_0);
}
#endif /* if (RTE_DMA0_EN) */

#if (RTE_DMA1_EN)
/**
 * @brief       Called by hardware ISR when a DMA event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void DMA1_IRQHandler(void)
{
    /* Call the DMA irq handler */
    DMA_IRQHandler(DMA_CH_1);
}
#endif /* if (RTE_DMA1_EN) */

#if (RTE_DMA2_EN)
/**
 * @brief       Called by hardware ISR when a DMA event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void DMA2_IRQHandler(void)
{
    /* Call the DMA irq handler */
    DMA_IRQHandler(DMA_CH_2);
}
#endif /* if (RTE_DMA2_EN) */

#if (RTE_DMA3_EN)
/**
 * @brief       Called by hardware ISR when a DMA event occurs. Application
 *              is notified via callback function once the interrupt occurs.
 */
void DMA3_IRQHandler(void)
{
    /* Call the DMA irq handler */
    DMA_IRQHandler(DMA_CH_3);
}
#endif /* if (RTE_DMA3_EN) */

/* DMA Driver Control Block */
DRIVER_DMA_t Driver_DMA =
{
    DMA_GetVersion,
    DMA_Initialize,
    DMA_Configure,
    DMA_ConfigureWord,
    DMA_ConfigureAddr,
    DMA_SetInterruptPriority,
    DMA_CreateConfigWord,
    DMA_SetConfigWord,
    DMA_Start,
    DMA_Stop,
    DMA_GetCounterValue,
    DMA_GetStatus
};

#endif    /* RTE_DMA */
