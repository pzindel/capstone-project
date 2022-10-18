/**
 * @file Driver_DMA.h
 * @brief DMA driver header file for RSLxx family of devices
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

#ifndef DRIVER_DMA_H_
#define DRIVER_DMA_H_

/** @addtogroup CMSISDRVg
 *  @{
 */
/**
 * @defgroup CMSISDRVDMAg CMSIS DMA Driver
 * @brief CMSIS DMA Driver Reference
 * @{
 */

#ifdef  __cplusplus
extern "C"
{
#endif

#include <Driver_Common.h>

#define ARM_DMA_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0) /**< DMA API version. */

/****** DMA Control Codes *****/

/**
 * @brief Selects the DMA channel.
 */
typedef enum _DMA_SEL_t {
    DMA_CH_0          = 0,                /**< DMA channel 0. */
    DMA_CH_1          = 1,                /**< DMA channel 1. */
    DMA_CH_2          = 2,                /**< DMA channel 2. */
    DMA_CH_3          = 3,                /**< DMA channel 3. */
} DMA_SEL_t;

/**
 * @brief Selects the DMA src/dst target interface.
 */
typedef enum _DMA_TRG_t {
    DMA_TRG_MEM       = 0,
    DMA_TRG_SPI0      = 1,                /**< Source / destination target = SPI0. */
    DMA_TRG_SPI1      = 2,                /**< Source / destination target = SPI1. */
    DMA_TRG_I2C0      = 3,                /**< Source / destination target = I2C0. */
    DMA_TRG_I2C1      = 4,                /**< Source / destination target = I2C1. */
    DMA_TRG_UART      = 5,                /**< Source / destination target = UART. */
    DMA_TRG_PCM       = 6,                /**< Source / destination target = PCM.  */
    DMA_TRG_TOF       = 7                 /**< Source / destination target = TOF.  */
} DMA_TRG_t;

/**
 * @brief Selects the step size increment to the DMA channel source address.
 */
typedef enum _DMA_SRC_STEP_t {
    DMA_CFG0_SRC_ADDR_STATIC = 0x00, /**< Do not increment the source address used by DMA channel.       */
    DMA_CFG0_SRC_ADDR_INCR_1 = 0x01, /**< Set the step size of DMA channel source address to 1.          */
    DMA_CFG0_SRC_ADDR_INCR_2 = 0x02, /**< Set the step size of DMA channel source address to 2.          */
    DMA_CFG0_SRC_ADDR_INCR_3 = 0x03, /**< Set the step size of DMA channel source address to 3.          */
    DMA_CFG0_SRC_ADDR_INCR_4 = 0x04, /**< Set the step size of DMA channel source address to 4.          */
    DMA_CFG0_SRC_ADDR_INCR_5 = 0x05, /**< Set the step size of DMA channel source address to 5.          */
    DMA_CFG0_SRC_ADDR_INCR_6 = 0x06, /**< Set the step size of DMA channel source address to 6.          */
    DMA_CFG0_SRC_ADDR_INCR_7 = 0x07, /**< Set the step size of DMA channel source address to 7.          */
    DMA_CFG0_SRC_ADDR_DECR_8 = 0x08, /**< Set the step size of DMA channel source address to negative 8. */
    DMA_CFG0_SRC_ADDR_DECR_7 = 0x09, /**< Set the step size of DMA channel source address to negative 7. */
    DMA_CFG0_SRC_ADDR_DECR_6 = 0x0A, /**< Set the step size of DMA channel source address to negative 6. */
    DMA_CFG0_SRC_ADDR_DECR_5 = 0x0B, /**< Set the step size of DMA channel source address to negative 5. */
    DMA_CFG0_SRC_ADDR_DECR_4 = 0x0C, /**< Set the step size of DMA channel source address to negative 4. */
    DMA_CFG0_SRC_ADDR_DECR_3 = 0x0D, /**< Set the step size of DMA channel source address to negative 3. */
    DMA_CFG0_SRC_ADDR_DECR_2 = 0x0E, /**< Set the step size of DMA channel source address to negative 2. */
    DMA_CFG0_SRC_ADDR_DECR_1 = 0x0F, /**< Set the step size of DMA channel source address to negative 1. */
} DMA_SRC_STEP_t;

/**
 * @brief Selects the step size increment to the DMA channel destination address.
 */
typedef enum _DMA_DST_STEP_t {
    DMA_CFG0_DEST_ADDR_STATIC = 0x00, /**< Do not increment the destination address used by DMA channel.       */
    DMA_CFG0_DEST_ADDR_INCR_1 = 0x01, /**< Set the step size of DMA channel destination address to 1.          */
    DMA_CFG0_DEST_ADDR_INCR_2 = 0x02, /**< Set the step size of DMA channel destination address to 2.          */
    DMA_CFG0_DEST_ADDR_INCR_3 = 0x03, /**< Set the step size of DMA channel destination address to 3.          */
    DMA_CFG0_DEST_ADDR_INCR_4 = 0x04, /**< Set the step size of DMA channel destination address to 4.          */
    DMA_CFG0_DEST_ADDR_INCR_5 = 0x05, /**< Set the step size of DMA channel destination address to 5.          */
    DMA_CFG0_DEST_ADDR_INCR_6 = 0x06, /**< Set the step size of DMA channel destination address to 6.          */
    DMA_CFG0_DEST_ADDR_INCR_7 = 0x07, /**< Set the step size of DMA channel destination address to 7.          */
    DMA_CFG0_DEST_ADDR_DECR_8 = 0x08, /**< Set the step size of DMA channel destination address to negative 8. */
    DMA_CFG0_DEST_ADDR_DECR_7 = 0x09, /**< Set the step size of DMA channel destination address to negative 7. */
    DMA_CFG0_DEST_ADDR_DECR_6 = 0x0A, /**< Set the step size of DMA channel destination address to negative 6. */
    DMA_CFG0_DEST_ADDR_DECR_5 = 0x0B, /**< Set the step size of DMA channel destination address to negative 5. */
    DMA_CFG0_DEST_ADDR_DECR_4 = 0x0C, /**< Set the step size of DMA channel destination address to negative 4. */
    DMA_CFG0_DEST_ADDR_DECR_3 = 0x0D, /**< Set the step size of DMA channel destination address to negative 3. */
    DMA_CFG0_DEST_ADDR_DECR_2 = 0x0E, /**< Set the step size of DMA channel destination address to negative 2. */
    DMA_CFG0_DEST_ADDR_DECR_1 = 0x0F, /**< Set the step size of DMA channel destination address to negative 1. */
} DMA_DST_STEP_t;

/**
 *  @brief Selects whether the transfer length counter depends on either the source word counts or the destination word count.
 */
typedef enum _DMA_SRC_DST_TRANS_LENGHT_SEL_t
{
    DMA_CFG0_DEST_TRANS_LENGTH_SEL = 0x00, /**< Transfer length counter depends on the destination word count. */
    DMA_CFG0_SRC_TRANS_LENGTH_SEL  = 0x01, /**< Transfer length counter depends on the size word count.        */
} DMA_SRC_DST_TRANS_LENGHT_SEL_t;

/**
 * @brief Selects how often data is transferred.
 */
typedef enum _DMA_DATA_MODE_t {
    DMA_REPEAT        = 0x0U,             /**< Data to be transfered repeatedly. */
    DMA_SINGLE        = 0x1U,             /**< Single data transfer.             */
} DMA_DATA_MODE_t;

/**
 * @brief Selects the order of the data bytes.
 */
typedef enum _DMA_BYTE_ORDER_t {
    DMA_ENDIANNESS_LITTLE = 0x0U,         /**< Little endian to be used. */
	DMA_ENDIANNESS_BIG    = 0x1U          /**< Big endian to be used.    */
} DMA_BYTE_ORDER_t;

/**
 * @brief Selects the src/dst data word size.
 */
typedef enum _DMA_WORD_SIZE_t {
    DMA_CFG0_DEST_WORD_SIZE_32BITS_TO_32BITS = 0x00, /**< Source data uses 32-bit word and destination data uses 32-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_32BITS_TO_4BITS  = 0x01, /**< Source data uses 32-bit word and destination data uses 4-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_32BITS_TO_8BITS  = 0x02, /**< Source data uses 32-bit word and destination data uses 8-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_32BITS_TO_16BITS = 0x04, /**< Source data uses 32-bit word and destination data uses 16-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_4BITS_TO_32BITS  = 0x08, /**< Source data uses 4-bit word and destination data uses 32-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_4BITS_TO_4BITS   = 0x09, /**< Source data uses 4-bit word and destination data uses 4-bit word.   */
    DMA_CFG0_DEST_WORD_SIZE_4BITS_TO_8BITS   = 0x0A, /**< Source data uses 4-bit word and destination data uses 8-bit word.   */
    DMA_CFG0_DEST_WORD_SIZE_4BITS_TO_16BITS  = 0x0C, /**< Source data uses 4-bit word and destination data uses 16-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_4BITS_TO_24BITS  = 0x0E, /**< Source data uses 4-bit word and destination data uses 24-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_32BITS  = 0x10, /**< Source data uses 8-bit word and destination data uses 32-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_4BITS   = 0x11, /**< Source data uses 8-bit word and destination data uses 4-bit word.   */
    DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_8BITS   = 0x12, /**< Source data uses 8-bit word and destination data uses 8-bit word.   */
    DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_16BITS  = 0x14, /**< Source data uses 8-bit word and destination data uses 16-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_8BITS_TO_24BITS  = 0x16, /**< Source data uses 8-bit word and destination data uses 24-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_16BITS_TO_32BITS = 0x20, /**< Source data uses 16-bit word and destination data uses 32-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_16BITS_TO_4BITS  = 0x21, /**< Source data uses 16-bit word and destination data uses 4-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_16BITS_TO_8BITS  = 0x22, /**< Source data uses 16-bit word and destination data uses 8-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_16BITS_TO_16BITS = 0x24, /**< Source data uses 16-bit word and destination data uses 16-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_16BITS_TO_24BITS = 0x26, /**< Source data uses 16-bit word and destination data uses 24-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_24BITS_TO_4BITS  = 0x31, /**< Source data uses 24-bit word and destination data uses 4-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_24BITS_TO_8BITS  = 0x32, /**< Source data uses 24-bit word and destination data uses 8-bit word.  */
    DMA_CFG0_DEST_WORD_SIZE_24BITS_TO_16BITS = 0x34, /**< Source data uses 24-bit word and destination data uses 16-bit word. */
    DMA_CFG0_DEST_WORD_SIZE_24BITS_TO_24BITS = 0x36, /**< Source data uses 24-bit word and destination data uses 24-bit word. */
} DMA_WORD_SIZE_t;

/**
 * @brief Selects priority of DMA channels.
 */
typedef enum _DMA_CH_PRI_t {
    DMA_CH_PRI_0      = 0x0U,             /**< Channel priority = 0. */
    DMA_CH_PRI_1      = 0x1U,             /**< Channel priority = 1. */
    DMA_CH_PRI_2      = 0x2U,             /**< Channel priority = 2. */
    DMA_CH_PRI_3      = 0x3U              /**< Channel priority = 3. */
} DMA_CH_PRI_t;

/**
 * @brief Selects DMA interrupt channel source.
 */
typedef enum _ADC_EVENT_SRC_t {
    DMA_DMA0_EVENT     = 1 << DMA_CH_0,   /**< DMA channel 0 event. */
    DMA_DMA1_EVENT     = 1 << DMA_CH_1,   /**< DMA channel 1 event. */
    DMA_DMA2_EVENT     = 1 << DMA_CH_2,   /**< DMA channel 2 event. */
    DMA_DMA3_EVENT     = 1 << DMA_CH_3,   /**< DMA channel 3 event. */
} ADC_EVENT_SRC_t;

/*----- DMA Control Codes: Error codes -----*/
#define DMA_ERROR_UNCONFIGURED  (ARM_DRIVER_ERROR_SPECIFIC - 1) /**< DMA channel has not been configured yet. */

/* Function documentation */
/**
  \fn          ARM_DRIVER_VERSION DMA_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          int32_t DMA_Initialize (DMA_SignalEvent_t cb_event)
  \brief       Initialize DMA driver with default configuration.
  \param[in]   cb_event Pointer to \ref DMA_SignalEvent
  \return      \ref execution_status

  \fn          int32_t DMA_Configure (DMA_SEL_t sel, const DMA_CFG_t *cfg, DMA_SignalEvent_t cb)
  \brief       Configure particular DMA channel.
  \param[in]   sel DMA channel to be configured (\ref DMA_SEL_t)
  \param[in]   cfg Pointer to \ref DMA_CFG_t
  \param[in]   cb Pointer to \ref DMA_SignalEvent_t
  \return      \ref execution_status

  \fn          int32_t DMA_ConfigureWord (DMA_SEL_t sel, uint32_t cfg, DMA_SignalEvent_t cb)
  \brief       Configure particular DMA channel.
  \param[in]   sel DMA channel to be configured (\ref DMA_SEL_t)
  \param[in]   cfg Configuration word
  \param[in]   cb Pointer to \ref DMA_SignalEvent_t
  \return      \ref execution_status

  \fn          int32_t DMA_ConfigureAddr (DMA_SEL_t sel, const DMA_ADDR_CFG_t *cfg)
  \brief       Configure DMA channel source and destination addresses.
  \param[in]   sel DMA to be configured (\ref DMA_SEL_t)
  \param[in]   cfg Pointer to \ref DMA_ADDR_CFG_t
  \return      \ref execution_status

  \fn          int32_t DMA_SetInterruptPriority (DMA_SEL_t sel, const DMA_PRI_CFG_t *cfg)
  \brief       Configure the DMA interrupt priority.
  \param[in]   sel DMA channel to be configured (\ref DMA_SEL_t)
  \param[in]   cfg Pointer to \ref DMA_PRI_CFG_t
  \return      \ref execution_status

  \fn          uint32_t DMA_CreateConfigWord (const DMA_CFG_t *cfg)
  \brief       Create DMA channel configuration word
  \param[in]   cfg Pointer to \ref DMA_CFG_t
  \return      configuration word

  \fn          int32_t DMA_SetConfigWord (DMA_SEL_t sel, uint32_t cfg)
  \brief       Quickly updates the DMA channel configuration
  \param[in]   sel DMA channel to be configured (\ref DMA_SEL_t)
  \param[in]   cfg configuration word
  \return      none

  \fn          int32_t DMA_Start (DMA_SEL_t sel, uint32_t trigger, uint32_t trigger_source)
  \brief       Starts the DMA transfer.
  \param[in]   sel DMA channel number to be used (\ref DMA_SEL_t)
  \param[in]   trigger DMA trigger type to be used
  \param[in]   trigger_source DMA trigger source to be used
  \return      \ref execution_status

  \fn          int32_t DMA_Stop (DMA_SEL_t sel)
  \brief       Stops the DMA transfer.
  \param[in]   sel DMA channel number to be used(\ref DMA_SEL_t)
  \return      \ref execution_status

  \fn          uint32_t DMA_GetCounterValue (DMA_SEL_t sel)
  \brief       Returns the current counter value of DMA channel.
  \param[in]   sel DMA channel value to be read (\ref DMA_SEL_t)
  \return      DMA channel counter value

  \fn          DMA_STATUS_t DMA_GetStatus (DMA_SEL_t sel)
  \brief       Returns the DMA channel status. Clears the status register
               on read.
  \param[in]   sel DMA channel value to be read (\ref DMA_SEL_t)
  \return      DMA channel status (\ref DMA_STATUS_t)

  \fn          void DMA_SignalEvent (uint32_t event)
  \brief       Signal DMA events.
  \param[in]   event Notification mask (\ref _ADC_EVENT_SRC_t)
  \return      None
*/

typedef void (*DMA_SignalEvent_t) (uint32_t event);  /**< Pointer to \ref DMA_SignalEvent : Signal Timer event. */

/**
\brief DMA channel configuration.
*/
typedef struct _DMA_CFG_t
{
    DMA_TRG_t            src_sel       :4;    /**< DMA source target.      */
    DMA_SRC_STEP_t       src_step      :4;    /**< Source step mode.       */
    DMA_WORD_SIZE_t      word_size     :6;    /**< Source word size.       */
    DMA_TRG_t            dst_sel       :4;    /**< DMA destination target. */
    DMA_DST_STEP_t       dst_step      :4;    /**< Destination step mode.  */
    DMA_CH_PRI_t         ch_priority   :2;    /**< Channel priority.       */
    uint32_t                           :8;    /**< Reserved.               */
} DMA_CFG_t;

/**
\brief DMA src/dst address configuration.
*/
typedef struct _DMA_ADDR_CFG_t
{
    volatile const void *src_addr;             /**< Source address.                                      */
    volatile const void *dst_addr;             /**< Destination address.                                 */
    uint32_t             counter_len    :16;   /**< Value which when reached triggers the counter event. */
    uint32_t             transfer_len   :16;   /**< DMA transfer length.                                 */
} DMA_ADDR_CFG_t;

/**
\brief DMA interrupt priority configuration.
*/
typedef struct _DMA_PRI_CFG_t
{
    uint32_t             preempt_pri     :3;   /**< Preempt priority.  */
    uint32_t                             :13;  /**< Reserved.          */
    uint32_t             subgrp_pri      :3;   /**< Subgroup priority. */
    uint32_t                             :13;  /**< Reserved.          */
} DMA_PRI_CFG_t;

/**
\brief DMA status.
*/
typedef struct _DMA_STATUS_t
{
    uint32_t             active          :1;   /**< Transfer was started.      */
    uint32_t             completed       :1;   /**< Transfer was completed.    */
    uint32_t             counter_reached :1;   /**< Counter value was reached. */
    uint32_t             buffer_fill_lvl :1;   /**< Error occurred.            */
    uint32_t                             :28;  /**< Reserved.                  */
} DMA_STATUS_t;

/**
\brief Access structure of the DMA Driver.
*/
typedef struct _DRIVER_DMA_t {
    ARM_DRIVER_VERSION (*GetVersion)           (void);                                      /**< Pointer to \ref DMA_GetVersion : Get driver version.                               */
    int32_t            (*Initialize)           (DMA_SignalEvent_t cb_event);                /**< Pointer to \ref DMA_Initialize : Initialize DMA driver.                            */
    int32_t            (*Configure)            (DMA_SEL_t sel, const DMA_CFG_t * cfg,
                                                DMA_SignalEvent_t cb);                      /**< Pointer to \ref DMA_Configure : Configure DMA channel.                             */
    int32_t            (*ConfigureWord)        (DMA_SEL_t sel, uint32_t cfg,
                                                DMA_SignalEvent_t cb);                      /**< Pointer to \ref DMA_ConfigureWord : Configure DMA channel.                         */
    int32_t            (*ConfigureAddr)        (DMA_SEL_t sel, const DMA_ADDR_CFG_t * pri); /**< Pointer to \ref DMA_ConfigureAddr : Configure DMA interrupt priority.              */
    int32_t            (*SetInterruptPriority) (DMA_SEL_t sel, const DMA_PRI_CFG_t * pri);  /**< Pointer to \ref DMA_SetInterruptPriority : Configure DMA interrupt priority.       */
    uint32_t           (*CreateConfigWord)     (const DMA_CFG_t * cfg);                     /**< Pointer to \ref DMA_CreateConfigWord : Create DMA channel configuration word.      */
    void               (*SetConfigWord)        (DMA_SEL_t sel, uint32_t cfg);               /**< Pointer to \ref DMA_SetConfigWord : Quickly update DMA channel configuration word. */
    int32_t            (*Start)                (DMA_SEL_t sel, uint32_t trigger, uint32_t trigger_source);  /**< Pointer to \ref DMA_Start : Start DMA transfer.                                      */
    int32_t            (*Stop)                 (DMA_SEL_t sel);                             /**< Pointer to \ref DMA_Stop : Stop DMA transfer.                                      */
    uint32_t           (*GetCounterValue)      (DMA_SEL_t sel);                             /**< Pointer to \ref DMA_GetCounterValue : Get the current channel transfer counter.    */
    DMA_STATUS_t       (*GetStatus)            (DMA_SEL_t sel);                             /**< Pointer to \ref DMA_GetStatus : Returns DMA channel status.                        */
} const DRIVER_DMA_t;

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of the CMSISDRVDMAg group */
/** @} */ /* End of the CMSISDRVg group */

#endif /* DRIVER_DMA_H_ */
