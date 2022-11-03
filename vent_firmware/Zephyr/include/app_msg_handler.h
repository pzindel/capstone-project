/**
 * @file app_msg_handler.h
 * @brief Header file for main application
 *
 * @copyright @parblock
 * Copyright (c) 2022 Semiconductor Components Industries, LLC (d/b/a
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

#ifndef APP_MSG_HANDLER_H_
#define APP_MSG_HANDLER_H_

#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

#include <ke_msg.h>

/**
 * @brief Callback handler for BLE configuration events
 *
 * Callback Function handler for BLE configuration request and related events.
 * When received from BLE stack.
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void BLE_ConfigHandler(ke_msg_id_t const msg_id, void const *param,
                       ke_task_id_t const dest_id,
                       ke_task_id_t const src_id);

/**
 * @brief Callback handler for BLE activity events
 *
 * Callback Function handler for BLE activities request and related events.
 * When received from BLE stack.
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void BLE_ActivityHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id,
                         ke_task_id_t const src_id);

/**
 * @brief Callback handler for BLE connection events
 *
 * Callback Function handler for BLE connection request and related events.
 * When received from BLE stack.
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void BLE_ConnectionHandler(ke_msg_id_t const msg_id, void const *param,
                           ke_task_id_t const dest_id,
                           ke_task_id_t const src_id);

/**
 * @brief Callback handler for BLE pairing events
 *
 * Callback Function handler for BLE pairing request and related events.
 * When received from BLE stack.
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void BLE_PairingHandler(ke_msg_id_t const msg_id, void const *param,
                        ke_task_id_t const dest_id,
                        ke_task_id_t const src_id);

/**
 * @brief Prepare data for advertising
 *
 * This function fills advertising data and scan response data buffer for BLE
 */
void PrepareAdvScanData(void);

/**
 * @brief Send connection confirmation
 *
 * This function sends GAPC connection confirmation
 */
void APP_SendConCfm(uint8_t conidx);

/**
 * @brief Callback handler for BLE pairing events
 *
 * Callback Function handler for BLE pairing request and related events.
 * When received from BLE stack.
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void LEDHandler(ke_msg_id_t const msg_id, void const *param,
                    ke_task_id_t const dest_id, ke_task_id_t const src_id);

/**
 * @brief Callback handler for SW1 button
 *
 * Callback handler for SW1 button. When called it will clear
 * bond list and if clearing is successful it will start APP_SW1LED_TIMEOUT
 * timer
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void SW1Handler(ke_msg_id_t const msg_id, void const *param,
                    ke_task_id_t const dest_id, ke_task_id_t const src_id);

/**
 * @brief Callback handler for handling LED_STATE_GPIO toggling
 *
 * Callback Function handler for handling LED_STATE_GPIO toggling once
 * bond list is cleared successfully
 *
 * @param [in] msg_id   Kernel message identifier
 * @param [in] param    Pointer to constant parameter
 * @param [in] dest_id  Destination identifier
 * @param [in] src_id   Source identifier
 */
void SW1LEDHandler(ke_msg_id_t const msg_id, void const *param,
                    ke_task_id_t const dest_id, ke_task_id_t const src_id);


#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_MSG_HANDLER_H */
