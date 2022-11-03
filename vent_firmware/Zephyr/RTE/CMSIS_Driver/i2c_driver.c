/**
 * @file i2c_driver.c
 * @brief I2C CMSIS@briefDriver implementation
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
#include <i2c_driver.h>
#include <string.h>
#if (I2C_DMA_CODE_EN)
#include <dma_driver.h>
#include <stdbool.h>
#endif    /* if (I2C_DMA_CODE_EN) */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion =
{
    ARM_I2C_API_VERSION,
    ARM_I2C_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_I2C_CAPABILITIES DriverCapabilities = 
{
    .address_10_bit = 0U,    /* 10-bit addresses not supported */
    .reserved = 0U
};

#if RTE_I2C0_ENABLED

/* I2C0 Run-Time Information */
static I2C_INFO I2C0_Info = { 0U };
static I2C_TRANSFER_INFO I2C0_TransferInfo = { 0U };
static I2C_PINS I2C0_Pins = 
{
    .scl = RTE_I2C0_SCL_PIN,    /* I2C0 default scl pin identifier */
    .sda = RTE_I2C0_SDA_PIN,    /* I2C0 default sda pin identifier */
    .pin_cfg = (RTE_I2C0_GPIO_LPF | RTE_I2C0_GPIO_DRIVE | RTE_I2C0_GPIO_PULL),
#if (RTE_I2C0_DMA_EN_DEFAULT)
	.dma_ch = RTE_I2C0_DMA_CH_DEFAULT,    /* I2C0 default DMA channel */
	.dma_cb = I2C0_DMA_Handler            /* I2C0 default callback function */
#endif    /* if (RTE_I2C0_DMA_CH_DEFAULT) */
};

/* I2C0 Resources */
static const I2C_RESOURCES I2C0_Resources =
{
    .reg = &I2C[0],
    .pins = &I2C0_Pins,
    .irqn = I2C0_IRQn,
    .info = &I2C0_Info,
    .xfer = &I2C0_TransferInfo,
#if (RTE_I2C0_DMA_EN_DEFAULT)
	.dma_trg = DMA_TRG_I2C0,    /* I2C0 default DMA target selection */
#endif    /* if (RTE_I2C0_DMA_EN_DEFAULT) */
};
#endif    /* if (RTE_I2C0_ENABLED) */

#if RTE_I2C1_ENABLED
/* I2C0 Run-Time Information */
static I2C_INFO I2C1_Info = { 0U };
static I2C_TRANSFER_INFO I2C1_TransferInfo = { 0U };
static I2C_PINS I2C1_Pins = 
{
    .scl = RTE_I2C1_SCL_PIN,    /* I2C1 default scl pin identifier */
    .sda = RTE_I2C1_SDA_PIN,    /* I2C1 default sda pin identifier */
    .pin_cfg = (RTE_I2C1_GPIO_LPF | RTE_I2C1_GPIO_DRIVE | RTE_I2C1_GPIO_PULL),
#if (RTE_I2C1_DMA_EN_DEFAULT)
    .dma_ch = RTE_I2C1_DMA_CH_DEFAULT,    /* I2C1 default DMA channel */
	.dma_cb = I2C1_DMA_Handler,           /* I2C1 default callback function */
#endif     /* if (RTE_I2C1_DMA_EN_DEFAULT) */
};

/* I2C1 Resources */
static const I2C_RESOURCES I2C1_Resources =
{
    .reg = &I2C[1],
    .pins = &I2C1_Pins,
    .irqn = I2C1_IRQn,
    .info = &I2C1_Info,
    .xfer = &I2C1_TransferInfo,
#if (RTE_I2C1_DMA_EN_DEFAULT)
	.dma_trg = DMA_TRG_I2C1,    /* I2C1 default DMA target selection */
#endif    /* if (RTE_I2C1_DMA_EN_DEFAULT) */
};
#endif    /* if (RTE_I2C1_ENABLED) */

#if (I2C_DMA_CODE_EN)
/* Prepare DMA driver pointer */
static DRIVER_DMA_t *dma = &Driver_DMA;
#endif    /* if (I2C_DMA_CODE_EN) */

/**
 * @brief       Reconfigure I2C. Should be used after a reset or whenever a
 *              reconfiguration of the I2C block is required.
 * @param[in]   i2c Pointer to I2C resources
 */
static void I2C_Configure(const I2C_RESOURCES *i2c)
{
    /* Reconfigure interrupts, slave address, master and slave prescale.  */
    i2c->reg->CFG = (i2c->info->int_cfg |
                    ((i2c->info->slave_addr << I2C_CFG_SLAVE_ADDRESS_Pos) & I2C_CFG_SLAVE_ADDRESS_Mask) |
                    ((i2c->info->slave_prescale << I2C_CFG_SLAVE_PRESCALE_Pos) & I2C_CFG_SLAVE_PRESCALE_Mask) |
                    ((i2c->info->master_prescale << I2C_CFG_MASTER_PRESCALE_Pos) & I2C_CFG_MASTER_PRESCALE_Mask));

    i2c->reg->CTRL = I2C_ENABLE;
    SYS_WATCHDOG_REFRESH();
    while (!(i2c->reg->CTRL & I2C_STATUS_ENABLED))
    {

    }
}

#if (I2C_CM33_CODE_EN)
/**
 * @brief       Called by hardware ISR when a byte is transferred.
 * @param[in]   i2c Pointer to I2C resources
 */
static void I2Cx_MasterIRQHandler(const I2C_RESOURCES *i2c)
{
	/* Prepare status description */
    uint32_t event = 0U;
    uint32_t i2c_status = i2c->reg->STATUS;

    if (i2c->info->status.busy)
    {
        if ((i2c_status & (1 << I2C_STATUS_BUS_ERROR_Pos)) == I2C_BUS_ERROR)
        {
            i2c->reg->STATUS = I2C_BUS_ERROR_CLEAR;

            i2c->info->status.bus_error = true;
            event |= ARM_I2C_EVENT_BUS_ERROR | ARM_I2C_EVENT_ARBITRATION_LOST;
        }
        else if ((i2c_status & (1 << I2C_STATUS_STOP_DETECTED_Pos)) == I2C_STOP_DETECTED)
        {
            i2c->reg->STATUS |= I2C_STOP_DETECTED_CLEAR;

            /* If finished transfer */
            if(i2c->xfer->cnt == i2c->xfer->num)
            {
                event |= ARM_I2C_EVENT_TRANSFER_DONE;
            }
            else
            {
                event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            }
            i2c->info->status.busy = 0U;
        }
        else if ((i2c_status & (1 << I2C_STATUS_READ_WRITE_Pos)) == I2C_IS_READ)
        {
            /* READ mode, If buffer full put a new data on RX buffer. When receive
             * the number of byte expected, send NACK and Stop. */
            if ((i2c_status & (1 << I2C_STATUS_RX_REQ_Pos)) == I2C_RX_REQ)
            {
                if (i2c->xfer->cnt == (i2c->xfer->num - 1)) /* If last data */
                {
                    if(!i2c->xfer->pending)
                    {
                        i2c->reg->CTRL = (I2C_NACK | I2C_STOP);
                    }
                    else /* Don't generate stop because xfer_pending == true (repeated start condition) */
                    {
                        i2c->reg->CTRL = I2C_ACK;
                        event |= ARM_I2C_EVENT_TRANSFER_DONE;
                        i2c->info->status.busy = 0U;
                    }
                }
                else /* cnt < (num - 1) */
                {
                    i2c->reg->CTRL = I2C_ACK;
                }
                i2c->xfer->data[i2c->xfer->cnt++] = i2c->reg->RX_DATA;
            }

            /* If Data Event is set send an ACK to start the read */
            else if ((i2c_status & (1 << I2C_STATUS_DATA_EVENT_Pos)) == I2C_DATA_EVENT)
            {
                i2c->reg->CTRL = I2C_ACK;
            }
            else
            {
                /* MISRA-C:2004 14:10
                 * Note that this else clause is required, even if the programmer
                 * expects that this clause will never be reached
                 * No change applied in this clause */
            }
        }
        else
        {
            /* If WRITE mode, send the next byte.
             * If all bytes from the buffer are sent, set LAST_DATA bit */
            if ((i2c_status & (1 << I2C_STATUS_ACK_Pos)) == I2C_HAS_ACK)
            {
                if (i2c->xfer->cnt < i2c->xfer->num)
                {
                    i2c->reg->TX_DATA = i2c->xfer->data[i2c->xfer->cnt++];
                }

                if (i2c->xfer->cnt == i2c->xfer->num)
                {
                    if(i2c->xfer->pending) /* doesn't send stop condition */
                    {
                        i2c->info->status.busy = 0;
                        event |= ARM_I2C_EVENT_TRANSFER_DONE;
                    }
                    else /* Send stop condition */
                    {
                        i2c->reg->CTRL = I2C_LAST_DATA;
                    }
                }
            }
        }
    }


    /* If an event happened and the application registered a callback */
    if (event && i2c->info->cb_event)
    {
        i2c->info->cb_event(event);
    }
}

/**
 * @brief       Called by hardware ISR when a byte is transferred.
 * @param[in]   i2c Pointer to I2C resources
 */
static void I2Cx_SlaveIRQHandler(const I2C_RESOURCES *i2c)
{
    uint32_t event = 0U;
    uint32_t i2c_status = i2c->reg->STATUS;

    if (i2c->info->status.busy)
    {
        if ((i2c_status & (1 << I2C_STATUS_BUS_ERROR_Pos)) == I2C_BUS_ERROR)
        {
            i2c->reg->STATUS = I2C_BUS_ERROR_CLEAR;

            i2c->info->status.bus_error = true;
            event |= ARM_I2C_EVENT_BUS_ERROR;
        }
        else if ((i2c_status & (1 << I2C_STATUS_ADDR_DATA_Pos)) ==  I2C_DATA_IS_ADDR)
        {
            /* If direction matches with the operation the application is waiting for */
            if ((i2c_status & (1 << I2C_STATUS_READ_WRITE_Pos)) ^
                (i2c->info->status.direction << I2C_STATUS_READ_WRITE_Pos))
            {
                /* Slave I2C selected. Send an ACK and reset the counter */
                i2c->reg->CTRL = I2C_ACK;

                /* If general call, notify application */
                if (i2c_status & I2C_ADDR_GEN_CALL)
                {
                    event |= ARM_I2C_EVENT_GENERAL_CALL;
                    i2c->info->status.general_call = true;
                }

                i2c->xfer->cnt = 0;

                event |= (i2c_status & I2C_IS_READ) ? ARM_I2C_EVENT_SLAVE_TRANSMIT : ARM_I2C_EVENT_SLAVE_RECEIVE;
            }
            else
            {
                i2c->reg->CTRL = I2C_NACK;
            }
        }
        else if ((i2c_status & (1 << I2C_STATUS_DATA_EVENT_Pos)) == I2C_DATA_EVENT)
        {
            /* Data event:
             *  - When in write mode send an ACK and read data written by Master.
             *  - When in read mode and NACK status not set send a new byte. */
            if ((i2c_status & (1 << I2C_STATUS_READ_WRITE_Pos)) == I2C_IS_WRITE)
            {
                /* Fill buffer with received data */
                i2c->xfer->data[i2c->xfer->cnt++] = i2c->reg->RX_DATA;

                /* Send ACK */
                i2c->reg->CTRL = I2C_ACK;
            }
            else if ((i2c_status & (1 << I2C_STATUS_ACK_Pos)) == I2C_HAS_ACK)
            {
                /* Send next byte */
                i2c->reg->TX_DATA = i2c->xfer->data[i2c->xfer->cnt++];
            }

            if(i2c->xfer->cnt == i2c->xfer->num)
            {
                event |= ARM_I2C_EVENT_TRANSFER_DONE;
                i2c->info->status.busy = 0U;
            }
        }

        if ((i2c_status & (1 << I2C_STATUS_STOP_DETECTED_Pos)) == I2C_STOP_DETECTED)
        {
            i2c->reg->STATUS = I2C_STOP_DETECTED_CLEAR;

            /* Stop detected, finish transfer */
            if(i2c->xfer->cnt == i2c->xfer->num)
            {
                event |= ARM_I2C_EVENT_TRANSFER_DONE;
            }
            else
            {
                event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
            }
            i2c->info->status.busy = 0U;
        }
    }

    /* If an event happened and the application registered a callback */
    if (event && i2c->info->cb_event)
    {
        i2c->info->cb_event(event);
    }
}
#else    /* if (I2C_CM33_CODE_EN) */
/**
 * @brief       Called by DMA driver when a DMA transfer is done.
 * 				Manage flags and counters. Application is notified
 * 				via callback function once the transmission is complete.
 * @param[in]   i2c Pointer to I2C resources
 */
static void I2C_DMAHandler(uint32_t event, const I2C_RESOURCES *i2c)
{
	/* Prepare status description */
	event = 0;

	/* Get the DMA status */
	DMA_STATUS_t dmaStatus = dma->GetStatus((DMA_SEL_t)(i2c->pins->dma_ch));

    /* Check if DMA transmit transfer has finished */
    if (dmaStatus.completed && (dma->GetCounterValue((DMA_SEL_t)(i2c->pins->dma_ch)) == i2c->xfer->num))
    {
	    /* Disable I2C Interrupts */
	    NVIC_DisableIRQ(i2c->irqn);

		/* Stop the DMA */
		dma->Stop((DMA_SEL_t)(i2c->pins->dma_ch));

		/* Clear send active flag */
		i2c->info->status.busy = 0U;

	    /* Notify application */
		if (i2c->info->cb_event)
		{
		    /* Notify application */
			if ((i2c->info->status.mode) == I2C_STATUS_MODE_MASTER)
			{
				/* Added small delay to finish the ongoing transmission */
				Sys_Delay((uint32_t) (SystemCoreClock/7000));
			}

		    i2c->info->cb_event(ARM_I2C_EVENT_TRANSFER_DONE);
		}

		/* Clear pending I2C Interrupts */
	    NVIC_ClearPendingIRQ(i2c->irqn);
    }

    /* Notify application */
    if (event && i2c->info->cb_event)
    {
	    i2c->info->cb_event(event);
	}
}
/**
 * @brief       Called by hardware ISR when a stop condition is detected.
 * @param[in]   i2c Pointer to I2C resources.
 */
static void I2Cx_MasterIRQHandler (const I2C_RESOURCES *i2c)
{
	/* Prepare status description */
    uint32_t event = 0U;

    /* Indicate that i2c is free */
    i2c->info->status.busy = 0U;

    /* Stop the DMA */
    dma->Stop((DMA_SEL_t)(i2c->pins->dma_ch));

    /* Get I2C status */
    uint32_t i2c_status = i2c->reg->STATUS;

    /* Get DMA counter value */
    uint32_t dmaCounterValue = dma->GetCounterValue((DMA_SEL_t)(i2c->pins->dma_ch));

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);

    /* Check if bus error occurred */
    if ((i2c_status & (1 << I2C_STATUS_BUS_ERROR_Pos)) == I2C_BUS_ERROR)
    {
        i2c->reg->STATUS = I2C_BUS_ERROR_CLEAR;

        /* Indicate bus error */
        i2c->info->status.bus_error = true;
        event |= ARM_I2C_EVENT_BUS_ERROR;
    }
    else
    {
        /* Stop detected, finish transfer */
        if (dmaCounterValue == i2c->xfer->num)
        {
            /* Indicate transfer done */
            event |= ARM_I2C_EVENT_TRANSFER_DONE;
        }
        else
        {
            /* Indicate transfer incomplete */
            event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;

            /* Check if dmaCounter == 0 */
            if (dmaCounterValue == 0)
            {
                 /* Indicate address nack event */
                 event |= ARM_I2C_EVENT_ADDRESS_NACK;
            }
        }
    }

    /* Clear pending I2C Interrupts */
    NVIC_ClearPendingIRQ(i2c->irqn);

	/* Notify application */
	if (event && i2c->info->cb_event)
	{
	    i2c->info->cb_event(event);
	}
}
/**
 * @brief       Called by hardware ISR when a data transfer is finished.
 * @param[in]   i2c Pointer to I2C resources.
 */
static void I2Cx_SlaveIRQHandler (const I2C_RESOURCES *i2c)
{
	/* Prepare status description */
    uint32_t event = 0U;

    /* Stop the DMA */
    dma->Stop((DMA_SEL_t)(i2c->pins->dma_ch));

    /* Get I2C status */
    uint32_t i2c_status = i2c->reg->STATUS;

    /* Get DMA counter value */
    uint32_t dmaCounterValue = dma->GetCounterValue((DMA_SEL_t)(i2c->pins->dma_ch));

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);

    /* Check of bus error occurred */
    if ((i2c_status & (1 << I2C_STATUS_BUS_ERROR_Pos)) == I2C_BUS_ERROR)
    {
        i2c->reg->STATUS = I2C_BUS_ERROR_CLEAR;

        /* Indicate bus error */
        i2c->info->status.bus_error = true;
        event |= ARM_I2C_EVENT_BUS_ERROR;
    }
    else
    {
        /* Check if entire data was transferred */
        if (dmaCounterValue == i2c->xfer->num)
        {
            /* Indicate transfer done event */
            event |= ARM_I2C_EVENT_TRANSFER_DONE;
        }
        else
        {
            /* Indicate transfer incomplete */
            event |= ARM_I2C_EVENT_TRANSFER_INCOMPLETE;
        }
    }

    /* Indicate that I2C is free */
    i2c->info->status.busy = 0U;

    /* Clear pending I2C Interrupts */
    NVIC_ClearPendingIRQ(i2c->irqn);

    /* Notify application */
    if (event && i2c->info->cb_event)
    {
        i2c->info->cb_event(event);
    }
}
#endif    /* if (I2C_DMA_CODE_EN) */

/**
 * @brief       Driver version
 * @return      ARM_DRIVER_VERSION
 */
static ARM_DRIVER_VERSION I2Cx_GetVersion(void)
{
    return DriverVersion;
}

/**
 * @brief       Get I2Cx driver capabilities
 * @return      ARM_I2C_CAPABILITIES
 */
static ARM_I2C_CAPABILITIES I2Cx_GetCapabilities(void)
{
    return DriverCapabilities;
}

/**
 * @brief       Initialize I2C flags, GPIO pins and reference to
 *              callback function.
 * @param[in]   cb_event Pointer to callback function (optional)
 * @param[in]   i2c  Pointer to I2C resources
 * @return      ARM_DRIVER_OK
 */
static int32_t I2C_Initialize(ARM_I2C_SignalEvent_t cb_event,
                              const I2C_RESOURCES *i2c)
{
    /* Configure the GPIOs for I2C operation */
    Sys_I2C_GPIOConfig(i2c->reg, i2c->pins->pin_cfg,
                       i2c->pins->scl, i2c->pins->sda);

    /* Enable interrupts */
    NVIC_ClearPendingIRQ(i2c->irqn);
    NVIC_EnableIRQ(i2c->irqn);

    /* Reset Run-Time information structure */
    memset(i2c->info, 0, sizeof(I2C_INFO));

    /* Initialize I2C Run-Time Resources */
    i2c->info->cb_event = cb_event;

#if (I2C_CM33_CODE_EN)
    i2c->info->int_cfg  = (I2C_TX_INT_ENABLE | I2C_RX_INT_ENABLE |
                           I2C_BUS_ERROR_INT_ENABLE | I2C_STOP_INT_ENABLE |
                           I2C_OVERRUN_INT_ENABLE | I2C_AUTO_ACK_DISABLE);
#else
    i2c->info->int_cfg = (I2C_TX_DMA_ENABLE | I2C_RX_DMA_ENABLE |
    		               I2C_BUS_ERROR_INT_ENABLE | I2C_STOP_INT_DISABLE |
    		               I2C_OVERRUN_INT_ENABLE | I2C_AUTO_ACK_ENABLE);
#endif

    /* Indicate that initialization is done */
    i2c->info->state = I2C_INITIALIZED;

#if (I2C_DMA_CODE_EN)
    DMA_CFG_t dmaCfgR, dmaCfgT;

    /* Prepare receiver mode DMA configuration */
    dmaCfgR.src_sel       = i2c->dma_trg;
    dmaCfgR.src_step      = DMA_CFG0_SRC_ADDR_STATIC;
    dmaCfgR.dst_sel       = DMA_TRG_MEM;
    dmaCfgR.dst_step      = DMA_CFG0_DEST_ADDR_INCR_1;
    dmaCfgR.ch_priority   = DMA_CH_PRI_0;
    dmaCfgR.word_size     = DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_8BITS;

    /* Prepare transmitter mode DMA configuration */
    dmaCfgT.src_sel       = DMA_TRG_MEM;
    dmaCfgT.src_step      = DMA_CFG0_SRC_ADDR_INCR_1;
    dmaCfgT.dst_sel       = i2c->dma_trg;
    dmaCfgT.dst_step      = DMA_CFG0_DEST_ADDR_STATIC;
    dmaCfgT.ch_priority   = DMA_CH_PRI_0;
    dmaCfgT.word_size     = DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_8BITS;

    /* Configure the DMA channel */
    dma->Configure(((DMA_SEL_t)(i2c->pins->dma_ch)), &dmaCfgR , i2c->pins->dma_cb);

    /* Store the RX DMA configuration */
    i2c->info->dma_rx_cfg = dma->CreateConfigWord(&dmaCfgR);

    /* Store the TX_DMA configuration */
    i2c->info->dma_tx_cfg = dma->CreateConfigWord(&dmaCfgT);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Uninitialize I2C flags, GPIO pins and removes reference to
 *              callback function.
 * @param[in]   i2c Pointer to I2C resources
 * @return      ARM_DRIVER_OK
 */
static int32_t I2C_Uninitialize(const I2C_RESOURCES *i2c)
{
#if (I2C_DMA_CODE_EN)

    /* Stop the DMA data transfer */
    dma->Stop((DMA_SEL_t)(i2c->pins->dma_ch));
#endif    /* if (I2C_DMA_CODE_EN) */

    uint8_t i2c_instance = i2c->irqn - I2C0_IRQn;

    /* Disable and clear pending I2C interrupts */
    NVIC_DisableIRQ(i2c->irqn);
    NVIC_ClearPendingIRQ(i2c->irqn);

    /* Disable I2C */
    i2c->reg->CTRL = I2C_DISABLE;
    SYS_WATCHDOG_REFRESH();
    while((i2c->reg->CTRL & (1 << I2C_CTRL_ENABLE_STATUS_Pos)) !=
            I2C_STATUS_DISABLED)
    {

    }

    /* Reset pin configuration */
    GPIO->CFG[i2c->pins->scl] = GPIO_MODE_DISABLE;
    GPIO->CFG[i2c->pins->sda] = GPIO_MODE_DISABLE;

    /* Reset GPIO_SRC_I2C configuration */
    GPIO_SRC_I2C[i2c_instance].SDA_BYTE = (uint8_t)I2C_SDA_SRC_CONST_HIGH_BYTE;
    GPIO_SRC_I2C[i2c_instance].SCL_BYTE = (uint8_t)I2C_SCL_SRC_CONST_HIGH_BYTE;

    /* Clear I2C state */
    i2c->info->state = 0U;

    /* Remove reference to callback function */
    i2c->info->cb_event = NULL;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Operates the power modes of the I2C interface
 * @param[in]   state ARM_POWER_FULL or ARM_POWER_OFF
 * @param[in]   i2c  Pointer to I2C resources
 * @return      ARM_DRIVER_OK if the operation is successful
 * @return      ARM_DRIVER_ERROR_UNSUPPORTED  if argument is invalid
 */
static int32_t I2C_PowerControl(ARM_POWER_STATE state,
                                const I2C_RESOURCES *i2c)
{
    switch (state)
    {
        case ARM_POWER_OFF:
        {
            /* Disable I2C */
            i2c->reg->CTRL = I2C_DISABLE;

            /* Clear status flags */
            i2c->info->status = (const ARM_I2C_STATUS) {
                0
            };

            /* Clear powered flag */
            i2c->info->state &= ~I2C_POWERED;
        }
        break;

        case ARM_POWER_FULL:
        {
        	/* Check if i2c was initialized */
            if ((i2c->info->state & I2C_INITIALIZED) == 0U)
            {
            	/* Return error */
                return ARM_DRIVER_ERROR;
            }
            /* Check if i2c was already powered up */
            if ((i2c->info->state & I2C_POWERED) != 0U)
            {
            	/* Return OK */
                return ARM_DRIVER_OK;
            }

            /* Clear status flags */
            i2c->info->status = (const ARM_I2C_STATUS) {
                0
            };

            /* Set powered flag */
            i2c->info->state |= I2C_POWERED;
        }
        break;

        case ARM_POWER_LOW:
        default:
        	/* Return unsupported operation error */
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start transmitting data as I2C Master.
 * @param[in]   addr Slave address (7-bit)
 * @param[in]   data  Pointer to data buffer to send to I2C Slave
 * @param[in]   num  Number of data bytes to send
 * @param[in]   xfer_pending  Transfer operation is pending (Stop
 *                                 condition will not be generated)
 * @param[in]   i2c  Pointer to I2C resources
 * @return      Execution status
 */
static int32_t I2C_MasterTransmit(uint32_t addr, const uint8_t *data,
                                  uint32_t num, bool xfer_pending,
                                  const I2C_RESOURCES *i2c)
{
	/* Check input parameters */
    if ((data == NULL) || (num == 0U) ||
        ((addr & ~ARM_I2C_ADDRESS_GC) > 0x7FU))
    {
        /* Invalid parameters */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Check if driver was configured */
    if ((i2c->info->state & I2C_CONFIGURED) == 0U)
    {
        /* Driver not yet configured */
        return ARM_DRIVER_ERROR;
    }

    /* Check if I2C is busy */
    if (i2c->info->status.busy)
    {
        /* Transfer operation in progress */
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Reset status */
    i2c->info->status = (const ARM_I2C_STATUS) {
        0
    };
    i2c->info->status.busy             = true;
    i2c->info->status.mode             = I2C_STATUS_MODE_MASTER;
    i2c->info->status.direction        = I2C_STATUS_DIRECTION_TX;
    i2c->reg->STATUS = (I2C_STOP_DETECTED_CLEAR |
                        I2C_BUS_ERROR_CLEAR     |
                        I2C_OVERRUN_CLEAR);

    /* Set transfer info */
    i2c->xfer->num     = num;
    i2c->xfer->cnt     = 0U;
    i2c->xfer->data    = (uint8_t *)data;
    i2c->xfer->addr    = (uint8_t)(addr);
    i2c->xfer->pending = xfer_pending;

    /* Disable slave mode */
    i2c->reg->CFG = i2c->reg->CFG & ~I2C_SLAVE_ENABLE;

#if (I2C_DMA_CODE_EN)

    /* Disable and clear pending I2C interrupts */
    NVIC_ClearPendingIRQ(i2c->irqn);
    NVIC_EnableIRQ(i2c->irqn);

    /* Prepare DMA for transmission */
    dma->SetConfigWord((DMA_SEL_t)(i2c->pins->dma_ch), i2c->info->dma_tx_cfg);

    /* Prepare DMA buffer configuration */
    DMA_ADDR_CFG_t buffCfg = {
        .src_addr     = (uint8_t *)data,
        .dst_addr     = &i2c->reg->TX_DATA,
        .counter_len  = 0,
        .transfer_len = num
    };

    /* Configure the DMA channel */
    dma->ConfigureAddr((DMA_SEL_t)(i2c->pins->dma_ch), &buffCfg);

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Generate start condition for specified slave */
    Sys_I2C_StartWrite(i2c->reg, i2c->xfer->addr);

#if (I2C_DMA_CODE_EN)

    /* Start the DMA transfer */
    dma->Start((DMA_SEL_t)(i2c->pins->dma_ch), DMA_ENABLE, 0);
#endif    /* if (I2C_DMA_CODE_EN) */

     /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start receiving data as I2C Master.
 * @param[in]   addr Slave address (7-bit)
 * @param[in]   data  Pointer to data buffer to store received data
 * @param[in]   num  Number of data bytes to receive
 * @param[in]   xfer_pending  Transfer operation is pending (Stop
 *              condition will not be generated)
 * @param[in]   i2c  Pointer to I2C resources
 * @return      Execution status
 */
static int32_t I2C_MasterReceive(uint32_t addr, uint8_t *data,
                                 uint32_t num, bool xfer_pending,
                                 const I2C_RESOURCES *i2c)
{
	/* Check input parameters */
    if ((data == NULL) || (num == 0U) ||
        ((addr & ~ARM_I2C_ADDRESS_GC) > 0x7FU))
    {
        /* Invalid parameters */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Check if driver was configured */
    if ((i2c->info->state & I2C_CONFIGURED) == 0U)
    {
        /* Driver not yet configured */
        return ARM_DRIVER_ERROR;
    }

    /* Check if I2C is busy */
    if (i2c->info->status.busy)
    {
        /* Transfer operation in progress */
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Reset status */
    i2c->info->status = (const ARM_I2C_STATUS) {
        0
    };
    i2c->info->status.busy             = true;
    i2c->info->status.mode             = I2C_STATUS_MODE_MASTER;
    i2c->info->status.direction        = I2C_STATUS_DIRECTION_RX;
    i2c->reg->STATUS = (I2C_STOP_DETECTED_CLEAR |
                        I2C_BUS_ERROR_CLEAR     |
                        I2C_OVERRUN_CLEAR);

    /* Set transfer info */
    i2c->xfer->num     = num;
    i2c->xfer->cnt     = 0U;
    i2c->xfer->data    = (uint8_t *)data;
    i2c->xfer->addr    = (uint8_t)(addr);
    i2c->xfer->pending = xfer_pending;

    /* Disable slave mode */
    i2c->reg->CFG = i2c->reg->CFG & ~I2C_SLAVE_ENABLE;

#if (I2C_DMA_CODE_EN)

    /* Clear pending I2C interrupts and enable interrupt */
    NVIC_ClearPendingIRQ(i2c->irqn);
    NVIC_EnableIRQ(i2c->irqn);

    /* Prepare DMA for transmission */
    dma->SetConfigWord((DMA_SEL_t)(i2c->pins->dma_ch), i2c->info->dma_rx_cfg);

    /* Prepare DMA buffer configuration */
    DMA_ADDR_CFG_t buffCfg = {
        .src_addr     = &i2c->reg->RX_DATA,
        .dst_addr     = (uint8_t *)data,
        .counter_len  = 0,
        .transfer_len = num
    };

    /* Configure the DMA channel */
    dma->ConfigureAddr((DMA_SEL_t)(i2c->pins->dma_ch), &buffCfg);

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);

    /* Start the DMA transfer */
    dma->Start((DMA_SEL_t)(i2c->pins->dma_ch), DMA_ENABLE, 0);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Generate start condition for specified slave */
    i2c->reg->ADDR_START = (i2c->xfer->addr << I2C_ADDR_START_ADDRESS_Pos) |
                           I2C_START_READ;

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start transmitting data as I2C Slave.
 * @param[in]   data Pointer to data buffer
 * @param[in]   num  Number of data bytes to transmit
 * @param[in]   i2c  Pointer to I2C resources
 * @return      Execution status
 */
static int32_t I2C_SlaveTransmit(const uint8_t *data, uint32_t num,
                                 const I2C_RESOURCES *i2c)
{
	/* Check input parameters */
    if ((data == NULL) || (num == 0U))
    {
        /* Invalid parameters */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Check if driver was configured */
    if ((i2c->info->state & I2C_POWERED) == 0U)
    {
        /* Driver not yet configured */
        return ARM_DRIVER_ERROR;
    }

    /* Check if I2C is busy */
    if (i2c->info->status.busy)
    {
        /* Transfer operation in progress */
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Reset status */
    i2c->info->status = (const ARM_I2C_STATUS) {
        0
    };
    i2c->info->status.busy             = true;
    i2c->info->status.mode             = I2C_STATUS_MODE_SLAVE;
    i2c->info->status.direction        = I2C_STATUS_DIRECTION_TX;
    i2c->reg->STATUS = (I2C_STOP_DETECTED_CLEAR |
                        I2C_BUS_ERROR_CLEAR     |
                        I2C_OVERRUN_CLEAR);

    /* Set transfer info */
    i2c->xfer->num  = num;
    i2c->xfer->cnt  = 0U;
    i2c->xfer->data = (uint8_t *)data;

#if (I2C_DMA_CODE_EN)

    /* Disable and clear pending I2C interrupts */
    NVIC_ClearPendingIRQ(i2c->irqn);
    NVIC_EnableIRQ(i2c->irqn);

    /* Prepare DMA for transmission */
    dma->SetConfigWord((DMA_SEL_t)(i2c->pins->dma_ch), i2c->info->dma_tx_cfg);

    /* Prepare DMA buffer configuration */
    DMA_ADDR_CFG_t buffCfg = {
    	.src_addr     = (uint8_t *)data,
    	.dst_addr     = &i2c->reg->TX_DATA,
        .counter_len  = 0,
        .transfer_len = num
    };

    /* Configure the DMA channel */
    dma->ConfigureAddr((DMA_SEL_t)(i2c->pins->dma_ch), &buffCfg);

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Enable slave mode */
    i2c->reg->CFG = i2c->reg->CFG | I2C_SLAVE_ENABLE;

#if (I2C_DMA_CODE_EN)

    /* Start the DMA transfer */
    dma->Start((DMA_SEL_t)(i2c->pins->dma_ch), DMA_ENABLE, 0);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Start receiving data as I2C Slave.
 * @param[in]   data Pointer to data buffer to store received data
 * @param[in]   num  Number of data bytes to receive
 * @param[in]   i2c  Pointer to I2C resources
 * @return      Execution status
 */
static int32_t I2C_SlaveReceive(uint8_t *data, uint32_t num,
                                const I2C_RESOURCES *i2c)
{
    if ((data == NULL) || (num == 0U))
    {
        /* Invalid parameters */
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    if ((i2c->info->state & I2C_POWERED) == 0U)
    {
        /* Driver not yet configured */
        return ARM_DRIVER_ERROR;
    }

    if (i2c->info->status.busy)
    {
        /* Transfer operation in progress */
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Reset status */
    i2c->info->status = (const ARM_I2C_STATUS) {
        0
    };
    i2c->info->status.busy             = true;
    i2c->info->status.mode             = I2C_STATUS_MODE_SLAVE;
    i2c->info->status.direction        = I2C_STATUS_DIRECTION_RX;
    i2c->reg->STATUS = (I2C_STOP_DETECTED_CLEAR |
                        I2C_BUS_ERROR_CLEAR     |
                        I2C_OVERRUN_CLEAR);

    /* Set transfer info */
    i2c->xfer->num  = num;
    i2c->xfer->cnt  = 0U;
    i2c->xfer->data = data;

#if (I2C_DMA_CODE_EN)

    /* Clear pending I2C interrupts in nvic */
    NVIC_ClearPendingIRQ(i2c->irqn);

    /* Enable i2c interrupts */
    NVIC_EnableIRQ(i2c->irqn);

    /* Prepare DMA for transmission */
    dma->SetConfigWord((DMA_SEL_t)(i2c->pins->dma_ch), i2c->info->dma_rx_cfg);

    /* Prepare DMA buffer configuration */
    DMA_ADDR_CFG_t buffCfg = {
        .src_addr     = &i2c->reg->RX_DATA,
    	.dst_addr     = data,
        .counter_len  = 0,
        .transfer_len = i2c->xfer->num = num
    };

    /* Configure the DMA channel */
    dma->ConfigureAddr((DMA_SEL_t)(i2c->pins->dma_ch), &buffCfg);

    /* Reset and reconfigure I2C block */
    i2c->reg->CTRL = I2C_RESET;
    I2C_Configure(i2c);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Enable slave mode */
    i2c->reg->CFG = i2c->reg->CFG | I2C_SLAVE_ENABLE;

#if (I2C_DMA_CODE_EN)

    /* Start the DMA transfer */
    dma->Start((DMA_SEL_t)(i2c->pins->dma_ch), DMA_ENABLE, 0);
#endif    /* if (I2C_DMA_CODE_EN) */

    /* Return OK */
    return ARM_DRIVER_OK;
}

/**
 * @brief       Get transferred data count.
 * @param[in]   i2c Pointer to I2C resources
 * @return      number of data bytes transferred; -1 when Slave is not
 *              addressed by Master
 */
static int32_t I2C_GetDataCount(const I2C_RESOURCES *i2c)
{
#if (I2C_DMA_CODE_EN)

	/* Return DMA counter value */
	return dma->GetCounterValue((DMA_SEL_t)(i2c->pins->dma_ch));
#else    /* if (I2C_DMA_CODE_EN) */

	/* Return counter value */
    return ((int32_t)i2c->xfer->cnt);
#endif    /* if (I2C_DMA_CODE_EN) */
}

/**
 * @brief       Control I2C Interface
 * @param[in]   control Control operation
 * @param[in]   arg  Argument of operation (optional)
 * @param[in]   i2c  Pointer to I2C resources
 * @return      Execution status
 */
static int32_t I2C_Control(uint32_t control, uint32_t arg,
                           const I2C_RESOURCES *i2c)
{
    uint32_t bus_speed, delay_cycles;

    if ((i2c->info->state & I2C_POWERED) == 0U)
    {
        /* I2C not powered */
        return ARM_DRIVER_ERROR;
    }

    switch (control)
    {
        case ARM_I2C_OWN_ADDRESS:
        {
            /* If transfer operation in progress */
            if (i2c->info->status.busy)
            {
                return ARM_DRIVER_ERROR_BUSY;
            }

            /* Wait until bus is free */
            SYS_WATCHDOG_REFRESH();
            while (!(i2c->reg->STATUS & I2C_BUS_FREE))
            {

            }

            /* Set slave address */
            i2c->info->slave_addr = arg;
            i2c->reg->CFG = ((i2c->reg->CFG & ~I2C_CFG_SLAVE_ADDRESS_Mask) |
                             ((arg << I2C_CFG_SLAVE_ADDRESS_Pos) &
                             I2C_CFG_SLAVE_ADDRESS_Mask));
        }
        break;

        case ARM_I2C_BUS_SPEED:
        {
            if (i2c->info->status.busy)
            {
                /* Transfer operation in progress */
                return ARM_DRIVER_ERROR_BUSY;
            }

            /* Set Bus Speed */
            switch (arg)
            {
                case ARM_I2C_BUS_SPEED_STANDARD:
                {
                    /* Standard Speed (100kHz) */
                    bus_speed = 100000;
                }
                break;

                case ARM_I2C_BUS_SPEED_FAST:
                {
                    /* Fast Speed     (400kHz) */
                    bus_speed = 400000;
                }
                break;

                case ARM_I2C_BUS_SPEED_FAST_PLUS:
                {
                    /* Fast+ Speed    (  1MHz) */
                    bus_speed = 1000000;
                }
                break;

                case ARM_I2C_BUS_SPEED_HIGH:

                /* High Speed     (3.4MHz) not supported */
                default:
                    return ARM_DRIVER_ERROR_UNSUPPORTED;
            }

            /* If system clock is not fast enough */
            if (SystemCoreClock < SYSCLOCK_I2C_MIN_RATIO * bus_speed)
            {
                return ARM_DRIVER_ERROR_UNSUPPORTED;
            }

            /* Calculate I2C Master prescale */
            i2c->info->master_prescale = SystemCoreClock / (3 * bus_speed) - 1;

            /* Calculate I2C slave prescale */
            if(SystemCoreClock < 4000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_1;
            }
            else if(SystemCoreClock >= 4000000 && SystemCoreClock < 8000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_2;
            }
            else if(SystemCoreClock >= 8000000 && SystemCoreClock < 12000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_3;
            }
            else if(SystemCoreClock >= 12000000 && SystemCoreClock < 16000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_4;
            }
            else if(SystemCoreClock >= 16000000 && SystemCoreClock < 20000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_5;
            }
            else if(SystemCoreClock >= 20000000 && SystemCoreClock < 24000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_6;
            }
            else if(SystemCoreClock >= 24000000 && SystemCoreClock < 48000000)
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_7;
            }
            else /* SystemCoreClock >= 48000000 */
            {
                i2c->info->slave_prescale = I2C_SLAVE_PRESCALE_14;
            }

            /* Reset and reconfigure I2C block */
            i2c->reg->CTRL = I2C_RESET;
            I2C_Configure(i2c);

            i2c->info->state |= I2C_CONFIGURED;
        }
        break;

        case ARM_I2C_BUS_CLEAR:
        {
            uint8_t i2c_instance = i2c->irqn - I2C0_IRQn;

            i2c->reg->CTRL = I2C_DISABLE;

            /* Reset GPIO_I2C_SRC configuration */
            GPIO_SRC_I2C[i2c_instance].SDA_BYTE = (uint8_t)I2C_SDA_SRC_CONST_HIGH;
            GPIO_SRC_I2C[i2c_instance].SCL_BYTE = (uint8_t)I2C_SCL_SRC_CONST_HIGH;

            /* Configure I2C pins as GPIO output */
            GPIO->CFG[i2c->pins->scl] = GPIO_MODE_GPIO_OUT;
            GPIO->CFG[i2c->pins->sda] = GPIO_MODE_GPIO_OUT;
            NVIC_DisableIRQ(i2c->irqn);

            /* Delay cycles for the standard 100KHz speed */
            delay_cycles = SystemCoreClock / 100000;

            /* Issue 9 clock pulses on SCL line */
            for (uint8_t i = 0U; i < 9U; i++)
            {
                /* Clock high */
                Sys_GPIO_Set_High(i2c->pins->scl);
                Sys_Delay(delay_cycles);

                /* Clock low */
                Sys_GPIO_Set_Low(i2c->pins->scl);
                Sys_Delay(delay_cycles);
            }

            /* Manually generates STOP condition - SDA goes high while SCL is
             * high, in order to end transaction. */
            Sys_GPIO_Set_Low(i2c->pins->sda);
            Sys_Delay(delay_cycles);
            Sys_GPIO_Set_High(i2c->pins->scl);
            Sys_Delay(delay_cycles);
            Sys_GPIO_Set_High(i2c->pins->sda);

            /* Reconfigure SCL and SDA Pins as I2C peripheral pins */
            Sys_I2C_GPIOConfig(i2c->reg, i2c->pins->pin_cfg,
                               i2c->pins->scl, i2c->pins->sda);

            /* Reset and reconfigure I2C block */
            i2c->reg->CTRL = I2C_RESET;
            I2C_Configure(i2c);

            /* Clear Pending and Enable i2c interrupts */
            NVIC_ClearPendingIRQ(i2c->irqn);
            NVIC_EnableIRQ(i2c->irqn);

            /* Send event */
            if (i2c->info->cb_event)
            {
                i2c->info->cb_event(ARM_I2C_EVENT_BUS_CLEAR);
            }
        }
        break;

        case ARM_I2C_ABORT_TRANSFER: 
        {
            if (i2c->info->status.busy)
            {
                /* Disable IRQ temporarily */
                NVIC_DisableIRQ(i2c->irqn);

                /* If master, send stop */
                if (i2c->info->status.mode == I2C_STATUS_MODE_MASTER)
                {
                    i2c->reg->CTRL = I2C_STOP;

                    /* Wait for stop to be issued */
                    SYS_WATCHDOG_REFRESH();
                    while ((i2c->reg->STATUS & I2C_STOP_DETECTED)
                            != I2C_STOP_DETECTED)
                    {

                    }

                    i2c->reg->STATUS |= I2C_STOP_DETECTED_CLEAR;
                }
                else
                {
                	/* Disable slave mode */
                	i2c->reg->CFG &= ~I2C_SLAVE_ENABLE;

                	/* Reset and reconfigure I2C block */
                	i2c->reg->CTRL = I2C_RESET;
                	I2C_Configure(i2c);
                }

                /* Clear transfer info */
                i2c->xfer->num  = 0U;
                i2c->xfer->cnt  = 0U;
                i2c->xfer->data = NULL;
                i2c->xfer->addr = 0U;

                /* Clear statuses */
                i2c->info->status.busy             = 0U;
                i2c->info->status.general_call     = 0U;
                i2c->info->status.arbitration_lost = 0U;
                i2c->info->status.bus_error        = 0U;

                /* Clear Pending and Enable i2c interrupts */
                NVIC_ClearPendingIRQ(i2c->irqn);
                NVIC_EnableIRQ(i2c->irqn);
            }
        }
        break;

        default:
            return ARM_DRIVER_ERROR;
    }
    return ARM_DRIVER_OK;
}

/**
 * @brief       Get I2Cx status
 * @param[in]   i2c I2C resources
 * @return      Return I2Cx status as an ARM_I2C_STATUS structure
 */
static ARM_I2C_STATUS I2C_GetStatus(const I2C_RESOURCES *i2c)
{
    return (i2c->info->status);
}

/* I2C0 Driver Wrapper functions. See functions above for usage */
#if RTE_I2C0_ENABLED
static int32_t I2C0_Initialize (ARM_I2C_SignalEvent_t cb_event)
{
    return I2C_Initialize(cb_event, &I2C0_Resources);
}

static int32_t I2C0_Uninitialize (void)
{
    return I2C_Uninitialize(&I2C0_Resources);
}

static int32_t I2C0_PowerControl (ARM_POWER_STATE state)
{
    return I2C_PowerControl(state, &I2C0_Resources);
}

static int32_t I2C0_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_MasterTransmit(addr, data, num, xfer_pending, &I2C0_Resources);
}

static int32_t I2C0_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_MasterReceive(addr, data, num, xfer_pending, &I2C0_Resources);
}

static int32_t I2C0_SlaveTransmit (const uint8_t *data, uint32_t num)
{
    return I2C_SlaveTransmit(data, num, &I2C0_Resources);
}

static int32_t I2C0_SlaveReceive (uint8_t *data, uint32_t num)
{
    return I2C_SlaveReceive(data, num, &I2C0_Resources);
}

static int32_t I2C0_GetDataCount (void)
{
    return I2C_GetDataCount(&I2C0_Resources);
}

static int32_t I2C0_Control (uint32_t control, uint32_t arg)
{
    return I2C_Control(control, arg, &I2C0_Resources);
}

static ARM_I2C_STATUS I2C0_GetStatus (void)
{
    return I2C_GetStatus(&I2C0_Resources);
}

void I2C0_IRQHandler(void)
{
	/* Check if driver is in master or slave mode */
    if (I2C0_Resources.info->status.mode == I2C_STATUS_MODE_MASTER)
    {
    	/* Execute master interrupt handler */
        I2Cx_MasterIRQHandler(&I2C0_Resources);
    }
    else
    {
        /* Execute slave interrupt handler */
        I2Cx_SlaveIRQHandler(&I2C0_Resources);
    }
}

#if (RTE_I2C0_DMA_EN_DEFAULT)
void I2C0_DMA_Handler(uint32_t event)
{
    I2C_DMAHandler(event, &I2C0_Resources);
}
#endif   /* if (RTE_I2C0_DMA_EN_DEFAULT) */

/* I2C0 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C0 =
{
    I2Cx_GetVersion,
    I2Cx_GetCapabilities,
    I2C0_Initialize,
    I2C0_Uninitialize,
    I2C0_PowerControl,
    I2C0_MasterTransmit,
    I2C0_MasterReceive,
    I2C0_SlaveTransmit,
    I2C0_SlaveReceive,
    I2C0_GetDataCount,
    I2C0_Control,
    I2C0_GetStatus
};
#endif    /* if RTE_I2C0_ENABLED */

/* I2C1 Driver Wrapper functions. See functions above for usage */
#if RTE_I2C1_ENABLED
static int32_t I2C1_Initialize (ARM_I2C_SignalEvent_t cb_event)
{
    return I2C_Initialize(cb_event, &I2C1_Resources);
}

static int32_t I2C1_Uninitialize (void)
{
    return I2C_Uninitialize(&I2C1_Resources);
}

static int32_t I2C1_PowerControl (ARM_POWER_STATE state)
{
    return I2C_PowerControl(state, &I2C1_Resources);
}

static int32_t I2C1_MasterTransmit (uint32_t addr, const uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_MasterTransmit(addr, data, num, xfer_pending, &I2C1_Resources);
}

static int32_t I2C1_MasterReceive (uint32_t addr, uint8_t *data, uint32_t num, bool xfer_pending)
{
    return I2C_MasterReceive(addr, data, num, xfer_pending, &I2C1_Resources);
}

static int32_t I2C1_SlaveTransmit (const uint8_t *data, uint32_t num)
{
    return I2C_SlaveTransmit(data, num, &I2C1_Resources);
}

static int32_t I2C1_SlaveReceive (uint8_t *data, uint32_t num)
{
    return I2C_SlaveReceive(data, num, &I2C1_Resources);
}

static int32_t I2C1_GetDataCount (void)
{
    return I2C_GetDataCount(&I2C1_Resources);
}

static int32_t I2C1_Control (uint32_t control, uint32_t arg)
{
    return I2C_Control(control, arg, &I2C1_Resources);
}

static ARM_I2C_STATUS I2C1_GetStatus (void)
{
    return I2C_GetStatus(&I2C1_Resources);
}

void I2C1_IRQHandler(void)
{
	/* Check if driver is in master or slave mode */
    if (I2C1_Resources.info->status.mode == I2C_STATUS_MODE_MASTER)
    {
    	/* Execute master interrupt handler */
        I2Cx_MasterIRQHandler(&I2C1_Resources);
    }
    else
    {
        /* Execute slave interrupt handler */
        I2Cx_SlaveIRQHandler(&I2C1_Resources);
    }
}

#if (RTE_I2C1_DMA_EN_DEFAULT)
void I2C1_DMA_Handler(uint32_t event)
{
	I2C_DMAHandler(event, &I2C1_Resources);
}
#endif    /* if (RTE_I2C1_DMA_CH_DEFAULT) */

/* I2C1 Driver Control Block */
ARM_DRIVER_I2C Driver_I2C1 =
{
    I2Cx_GetVersion,
    I2Cx_GetCapabilities,
    I2C1_Initialize,
    I2C1_Uninitialize,
    I2C1_PowerControl,
    I2C1_MasterTransmit,
    I2C1_MasterReceive,
    I2C1_SlaveTransmit,
    I2C1_SlaveReceive,
    I2C1_GetDataCount,
    I2C1_Control,
    I2C1_GetStatus
};
#endif    /* if RTE_I2C1_ENABLED */
