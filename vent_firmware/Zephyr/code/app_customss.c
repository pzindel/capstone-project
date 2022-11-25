/******************************************************************************
 * File Name        : app_customss.c
 * Disclaimer       : Adapted from onsemi example "ble_peripheral_server".
 * Description      : This module handles the application-specific Bluetooth
 *                    custom service server.
 *
 * Author           : Pierino Zindel
 * Version          : 1.0.0
 * Last Rev. Date   : November 24, 2022
 ******************************************************************************
 */
/**
 * @file app_customss.c
 * @brief Application-specific Bluetooth custom service server source file
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


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <ble_abstraction.h>
#include <string.h>
#include <swmTrace_api.h>
#include <app_customss.h>
#include <app.h>


/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
static struct app_env_tag_cs app_env_cs;

static const struct att_db_desc att_db_cs_svc0[] =
{
    //**** Service 0 ****
    CS_SERVICE_UUID_128(CS_SERVICE0, CS_SVC_UUID),

    // To the BLE transfer
    CS_CHAR_UUID_128(CS_TX_VALUE_CHAR0,
                     CS_TX_VALUE_VAL0,
                     CS_CHAR_TX_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE) | PERM(RP, SEC_CON),
                     sizeof(app_env_cs.to_air_buffer),
                     app_env_cs.to_air_buffer, NULL),
    CS_CHAR_CCC(CS_TX_VALUE_CCC0,
                app_env_cs.to_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_TX_VALUE_USR_DSCP0,
                      sizeof(CS_TX_CHAR_NAME) - 1,
                      CS_TX_CHAR_NAME,
                      NULL),

    // From the BLE transfer
    CS_CHAR_UUID_128(CS_RX_VALUE_CHAR0,
                     CS_RX_VALUE_VAL0,
                     CS_CHAR_RX_UUID,
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),
                     sizeof(app_env_cs.from_air_buffer),
                     app_env_cs.from_air_buffer,
                     CUSTOMSS_RXCharCallback),
    CS_CHAR_CCC(CS_RX_VALUE_CCC0,
                app_env_cs.from_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_RX_VALUE_USR_DSCP0,
                      sizeof(CS_RX_CHAR_NAME) - 1,
                      CS_RX_CHAR_NAME,
                      NULL),

    // To the BLE long transfer
    CS_CHAR_UUID_128(CS_TX_LONG_VALUE_CHAR0,
                     CS_TX_LONG_VALUE_VAL0,
                     CS_CHAR_LONG_TX_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                     sizeof(app_env_cs.to_air_buffer_long),
                     app_env_cs.to_air_buffer_long,
                     NULL),
    CS_CHAR_CCC(CS_TX_LONG_VALUE_CCC0,
                app_env_cs.to_air_cccd_value_long,
                NULL),
    CS_CHAR_USER_DESC(CS_TX_LONG_VALUE_USR_DSCP0,
                      sizeof(CS_TX_CHAR_LONG_NAME) - 1,
                      CS_TX_CHAR_LONG_NAME,
                      NULL),

    // From the BLE long transfer
    CS_CHAR_UUID_128(CS_RX_LONG_VALUE_CHAR0,                     /* attidx_char */
                     CS_RX_LONG_VALUE_VAL0,                      /* attidx_val */
                     CS_CHAR_LONG_RX_UUID,                       /* uuid */
#ifdef RX_VALUE_LONG_INDICATION
                     PERM(RD, ENABLE) | PERM(IND, ENABLE),       /* perm, use indication */
#else  /* ifdef RX_VALUE_LONG_INDICATION */
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),       /* perm, use notification */
#endif /* ifdef RX_VALUE_LONG_INDICATION */
                     sizeof(app_env_cs.from_air_buffer_long),    /* length */
                     app_env_cs.from_air_buffer_long,            /* data */
                     CUSTOMSS_RXLongCharCallback),               /* callback */
    // Client Characteristic Configuration descriptor
    CS_CHAR_CCC(CS_RX_LONG_VALUE_CCC0,                           /* attidx */
                app_env_cs.from_air_cccd_value_long,             /* data */
                NULL),                                           /* callback */
    // Characteristic User Description descriptor
    CS_CHAR_USER_DESC(CS_RX_LONG_VALUE_USR_DSCP0,                /* attidx */
                      sizeof(CS_RX_CHAR_LONG_NAME) - 1,          /* length */
                      CS_RX_CHAR_LONG_NAME,                      /* data */
                      NULL),                                     /* callback */
};

static const struct att_db_desc att_db_cs_svc1[] =
{
    //**** Service 1 ****
    CS_SERVICE_UUID_128(CS_SERVICE1, CS_BLT_SVC_UUID),

    // To the BLE Battery transfer
    CS_CHAR_UUID_128(CS_BATTERY_VALUE_CHAR1,
                     CS_BATTERY_VALUE_VAL1,
                     CS_CHAR_BATTERY_UUID,
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),
                     sizeof(app_env_cs.battery_to_air_buffer),
                     app_env_cs.battery_to_air_buffer, NULL),
    CS_CHAR_CCC(CS_BATTERY_VALUE_CCC1,
                app_env_cs.battery_to_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_BATTERY_VALUE_USR_DSCP1,
                      sizeof(CS_BATTERY_CHAR_NAME) - 1,
                      CS_BATTERY_CHAR_NAME,
                      NULL),

    // From the BLE LED Transfer
    CS_CHAR_UUID_128(CS_LED_VALUE_CHAR1,
                     CS_LED_VALUE_VAL1,
                     CS_CHAR_LED_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                     sizeof(app_env_cs.led_from_air_buffer),
                     app_env_cs.led_from_air_buffer,
                     CUSTOMSS_LEDCharCallback),
    CS_CHAR_CCC(CS_LED_VALUE_CCC1,
                app_env_cs.led_from_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_LED_VALUE_USR_DSCP1,
                      sizeof(CS_LED_CHAR_NAME) - 1,
                      CS_LED_CHAR_NAME,
                      NULL),

    // To the BLE Button transfer
    CS_CHAR_UUID_128(CS_BUTTON_VALUE_CHAR1,
                     CS_BUTTON_VALUE_VAL1,
                     CS_CHAR_BUTTON_UUID,
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),
                     sizeof(app_env_cs.button_to_air_buffer),
                     app_env_cs.button_to_air_buffer, NULL),
    CS_CHAR_CCC(CS_BUTTON_VALUE_CCC1,
                app_env_cs.button_to_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_BUTTON_VALUE_USR_DSCP1,
                      sizeof(CS_BUTTON_CHAR_NAME) - 1,
                      CS_BUTTON_CHAR_NAME,
                      NULL),

    // From the BLE Vent Transfer
    CS_CHAR_UUID_128(CS_VENT_VALUE_CHAR1,
                     CS_VENT_VALUE_VAL1,
                     CS_CHAR_VENT_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                     sizeof(app_env_cs.vent_from_air_buffer),
                     app_env_cs.vent_from_air_buffer,
                     CUSTOMSS_VentCharCallback),
    CS_CHAR_CCC(CS_VENT_VALUE_CCC1,
                app_env_cs.vent_from_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_VENT_VALUE_USR_DSCP1,
                      sizeof(CS_VENT_CHAR_NAME) - 1,
                      CS_VENT_CHAR_NAME,
                      NULL),

    // To the BLE Humidity transfer
    CS_CHAR_UUID_128(CS_HUM_VALUE_CHAR1,
                     CS_HUM_VALUE_VAL1,
                     CS_CHAR_HUM_UUID,
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),
                     sizeof(app_env_cs.hum_to_air_buffer),
                     app_env_cs.hum_to_air_buffer, NULL),
    CS_CHAR_CCC(CS_HUM_VALUE_CCC1,
                app_env_cs.hum_to_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_HUM_VALUE_USR_DSCP1,
                      sizeof(CS_HUM_CHAR_NAME) - 1,
                      CS_HUM_CHAR_NAME,
                      NULL),

    // To the BLE Temperature transfer
    CS_CHAR_UUID_128(CS_TEMP_VALUE_CHAR1,
                     CS_TEMP_VALUE_VAL1,
                     CS_CHAR_TEMP_UUID,
                     PERM(RD, ENABLE) | PERM(NTF, ENABLE),
                     sizeof(app_env_cs.temp_to_air_buffer),
                     app_env_cs.temp_to_air_buffer, NULL),
    CS_CHAR_CCC(CS_TEMP_VALUE_CCC1,
                app_env_cs.temp_to_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_TEMP_VALUE_USR_DSCP1,
                      sizeof(CS_TEMP_CHAR_NAME) - 1,
                      CS_TEMP_CHAR_NAME,
                      NULL),

    // From the BLE Temperature Upper Threshold transfer
    CS_CHAR_UUID_128(CS_TEMP_UTHR_VALUE_CHAR1,
                     CS_TEMP_UTHR_VALUE_VAL1,
                     CS_CHAR_TEMP_UTHR_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                     sizeof(app_env_cs.temp_uthr_from_air_buffer),
                     app_env_cs.temp_uthr_from_air_buffer,
                     CUSTOMSS_TempUTHRCharCallback),
    CS_CHAR_CCC(CS_TEMP_UTHR_VALUE_CCC1,
                app_env_cs.temp_uthr_from_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_TEMP_UTHR_VALUE_USR_DSCP1,
                      sizeof(CS_TEMP_UTHR_CHAR_NAME) - 1,
                      CS_TEMP_UTHR_CHAR_NAME,
                      NULL),

    // From the BLE Temperature Lower Threshold transfer
    CS_CHAR_UUID_128(CS_TEMP_LTHR_VALUE_CHAR1,
                     CS_TEMP_LTHR_VALUE_VAL1,
                     CS_CHAR_TEMP_LTHR_UUID,
                     PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE),
                     sizeof(app_env_cs.temp_lthr_from_air_buffer),
                     app_env_cs.temp_lthr_from_air_buffer,
                     CUSTOMSS_TempLTHRCharCallback),
    CS_CHAR_CCC(CS_TEMP_LTHR_VALUE_CCC1,
                app_env_cs.temp_lthr_from_air_cccd_value,
                NULL),
    CS_CHAR_USER_DESC(CS_TEMP_LTHR_VALUE_USR_DSCP1,
                      sizeof(CS_TEMP_LTHR_CHAR_NAME) - 1,
                      CS_TEMP_LTHR_CHAR_NAME,
                      NULL),
};

static uint32_t notifyOnTimeout;
static uint8_t val_notif = 0;
static uint8_t button_value = 0;
static uint8_t gpio0_pressed = 0;

/* ----------------------------------------------------------------------------
 * Function definitions
 * --------------------------------------------------------------------------*/

const struct att_db_desc * CUSTOMSS_GetDatabaseDescription(uint8_t att_db_cs_svc_id)
{
    switch (att_db_cs_svc_id) {
        case 0: {
            return att_db_cs_svc0;
        }
        case 1: {
            return att_db_cs_svc1;
        }
        default:
            return NULL;
    }
}

void CUSTOMSS_Initialize(void)
{
    memset(&app_env_cs, '\0', sizeof(struct app_env_tag_cs));

    app_env_cs.battery_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.battery_to_air_cccd_value[1] = 0x00;

    app_env_cs.button_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.button_to_air_cccd_value[1] = 0x00;

    app_env_cs.hum_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.hum_to_air_cccd_value[1] = 0x00;

    app_env_cs.temp_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.temp_to_air_cccd_value[1] = 0x00;

    notifyOnTimeout = 0;

    MsgHandler_Add(GATTM_ADD_SVC_RSP, CUSTOMSS_MsgHandler);
    MsgHandler_Add(CUSTOMSS_NTF_TIMEOUT, CUSTOMSS_MsgHandler);
    MsgHandler_Add(CUSTOM_BUTTON_NTF, CUSTOMSS_MsgHandler);
    MsgHandler_Add(GATTC_CMP_EVT, CUSTOMSS_MsgHandler);
}

void CUSTOMSS_NotifyOnTimeout(uint32_t timeout)
{
    notifyOnTimeout = timeout;

    for (uint8_t i = 0; i < BLE_CONNECTION_MAX; i++) {
        if (GATT_GetEnv()->cust_svc_db[0].cust_svc_start_hdl && timeout) {
            ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, i),
                         timeout);
        }
    }
}

void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    switch (msg_id) {
        case GATTM_ADD_SVC_RSP: {
            const struct gattm_add_svc_rsp *p = param;

            // If service has been added successfully, start periodic notification timer
            if (p->status == ATT_ERR_NO_ERROR && notifyOnTimeout) {
                for (unsigned int i = 0; i < BLE_CONNECTION_MAX; i++) {
                    ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, i),
                                 notifyOnTimeout);
                }
            }
        }
        break;
        case CUSTOMSS_NTF_TIMEOUT: {
            uint8_t conidx = KE_IDX_GET(dest_id);
            memset(&app_env_cs.from_air_buffer[0], val_notif, CS_VALUE_MAX_LENGTH);

            // Update the sensor variables
            sensor_measurement();

            // Update the buffers
            memset(&app_env_cs.battery_to_air_buffer[0], battery_level, CS_BATTERY_MAX_LENGTH);
            memcpy(app_env_cs.temp_to_air_buffer, temperature_reading.bytes, CS_TEMPERATURE_MAX_LENGTH);
            memcpy(app_env_cs.hum_to_air_buffer, humidity_reading.bytes, CS_HUMIDITY_MAX_LENGTH);

            if ((app_env_cs.from_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.from_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                // Send notification to peer device
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_VALUE_VAL0),
                                 CS_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer);
                val_notif++;
                swmLogInfo("\n__CUSTOMSS notifying peer device %d\r\n", conidx);
            }

            if (app_env_cs.from_air_cccd_value_long[1] == 0x00 && GAPC_IsConnectionActive(conidx)) {
                // Update RX long characteristic with the inverted version of
                // TX long characteristic
                for (uint8_t i = 0; i < CS_LONG_VALUE_MAX_LENGTH; i++) {
                    app_env_cs.from_air_buffer_long[i] = 0xFF ^ app_env_cs.to_air_buffer_long[i];
                }

                if (app_env_cs.from_air_cccd_value_long[0] == ATT_CCC_START_IND) {
                    // Send indication to peer device
                    GATTC_SendEvtCmd(conidx, GATTC_INDICATE, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_LONG_VALUE_VAL0),
                                     CS_LONG_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer_long);
                }

                if (app_env_cs.from_air_cccd_value_long[0] == ATT_CCC_START_NTF) {
                    // Send notification to peer device
                    GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_LONG_VALUE_VAL0),
                                     CS_LONG_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer_long);
                }
            }

            // Transmit the Battery Level data
            if ((app_env_cs.battery_to_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.battery_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                // Send notification to peer device
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC1, CS_BATTERY_VALUE_VAL1),
                                 CS_BATTERY_MAX_LENGTH, app_env_cs.battery_to_air_buffer);
            }

            // Transmit the Humidity data
            if ((app_env_cs.hum_to_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.hum_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                // Send notification to peer device
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC1, CS_HUM_VALUE_VAL1),
                                 CS_HUMIDITY_MAX_LENGTH, app_env_cs.hum_to_air_buffer);
            }

            // Transmit the Temperature data
            if ((app_env_cs.temp_to_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.temp_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                // Send notification to peer device
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC1, CS_TEMP_VALUE_VAL1),
                                 CS_TEMPERATURE_MAX_LENGTH, app_env_cs.temp_to_air_buffer);
            }

            if (notifyOnTimeout) {   // Restart timer
                ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, conidx),
                             notifyOnTimeout);
            }
        }
        break;
        case CUSTOM_BUTTON_NTF: {
            uint8_t conidx = KE_IDX_GET(dest_id);
            memset(&app_env_cs.button_to_air_buffer[0], button_value,
                   CS_LED_BUTTON_MAX_LENGTH);
            if ((app_env_cs.button_to_air_cccd_value[0] == ATT_CCC_START_NTF
                 && app_env_cs.button_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                // Send notification to peer device
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0,
                                 GATTM_GetHandle(CUST_SVC1, CS_BUTTON_VALUE_VAL1),
                                 CS_LED_BUTTON_MAX_LENGTH,
                                 app_env_cs.button_to_air_buffer);
            }
        }
        break;
    }
}

void GPIO0_Pressed_Flag_Clear(void)
{
	gpio0_pressed = 0;
}

uint8_t GPIO0_Pressed(void)
{
	return gpio0_pressed;
}

void GPIO0_IRQHandler(void)
{
    static uint8_t button_pressed = 0;
    static uint8_t LED_state = 0;

    if (button_pressed == 1) {
        // If GPIO0 has just been disconnected from the ground
        // (SW1 pushbutton on the evaluation board has just been released)

        button_pressed = 0;
        button_value = 0;

        // Clear timers and restore LED state when button is released
        ke_timer_clear(APP_SW1_TIMEOUT, TASK_APP);
        ke_timer_clear(APP_SW1LED_TIMEOUT, TASK_APP);

        LED_state = app_env_cs.led_from_air_buffer[0];

        if (LED_state == 0) {
            // Turn off LED
            Sys_GPIO_Set_High(LED_STATE_GPIO);
        } else {
            // Turn on LED
            Sys_GPIO_Set_Low(LED_STATE_GPIO);
        }
    } else if (Sys_GPIO_Read(BUTTON_GPIO) == 0) {
        // If GPIO0 has just been connected to the ground
        // (SW1 pushbutton on the evaluation board has just been pressed)

        button_pressed = 1;
        button_value = 1;

        // Clear bond list after CLR_BDLST_HOLD_DURATION_S seconds
        ke_timer_set(APP_SW1_TIMEOUT, TASK_APP, TIMER_SETTING_S(CLR_BONDLIST_HOLD_DURATION_S));
    }
    gpio0_pressed = 1;
}

/* Function      : print_large_buffer
 *
 * Description   : Use swmLogInfo for 10 Bytes of data at time.
 *                 remaining byte/s will be printed in string format to avoid
 *                 use of swmLogInfo for individual byte
 *                 This will result in reduce overhead for UART
 *
 * Parameters    : const uint8_t *buffer : data buffer
 *                 uint16_t length       : length of data
 *
 * Returns       : None
 */
static void print_large_buffer(const uint8_t *buffer, uint16_t length)
{
    unsigned int num_of_blocks = (length / 10);
    unsigned int rem_bytes = ((num_of_blocks) ? (length % 10) : length);

    for (int i = 0; i < num_of_blocks; i++) {
        int j = (i * 10);
        swmLogInfo("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", buffer[j],
                   buffer[j + 1], buffer[j + 2], buffer[j + 3],
                   buffer[j + 4], buffer[j + 5], buffer[j + 6],
                   buffer[j + 7], buffer[j + 8], buffer[j + 9]);
    }

    if (rem_bytes) {
        int j = (num_of_blocks * 10);
        char temp_string[28] = { 0 };
        uint8_t index = 0;

        for (int i = j; i < length; i++) {
            sprintf(&temp_string[index], "%02x", buffer[i]);
            index += 2;

            // put space before next data
            temp_string[index] = 0x20;
            index += 1;
        }

        swmLogInfo("%s ", temp_string);
    }

    swmLogInfo("\r\n");
}


uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *to, const uint8_t *from,
                                uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        swmLogInfo("\nRXCharCallback (%d):(%d) ", conidx, length);
        print_large_buffer(app_env_cs.from_air_buffer, length);
        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nRXCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}


uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                    uint8_t *to, const uint8_t *from,
                                    uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        swmLogInfo("\nRXLongCharCallback (%d):(%d) ", conidx, length);

        // Update RX long characteristic with the inverted version of
        // TX long characteristic just received
        if (operation == GATTC_READ_REQ_IND) {
            for (uint8_t i = 0; i < CS_LONG_VALUE_MAX_LENGTH; i++) {
                app_env_cs.from_air_buffer_long[i] = 0xFF ^ app_env_cs.to_air_buffer_long[i];
            }
        }

        print_large_buffer(app_env_cs.from_air_buffer_long, length);
        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nRXLongCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}


uint8_t CUSTOMSS_LEDCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        // TODO: remove this from the function after testing is complete
        // Store buffer to global variable
        *vent_state = app_env_cs.vent_from_air_buffer[0];

        // Update the vent with the new state
        vent_update();

        if (app_env_cs.led_from_air_buffer[0] == 0) {
            set_vent_state(VENT_OPEN_STATE);
            Sys_GPIO_Set_High(LED_STATE_GPIO);    // Turn LED off
        } else if (app_env_cs.led_from_air_buffer[0] == 1) {
            set_vent_state(VENT_CLOSED_STATE);
            Sys_GPIO_Set_Low(LED_STATE_GPIO);    // Turn LED on
        }
        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}



uint8_t CUSTOMSS_TempUTHRCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                      uint8_t *to, const uint8_t *from,
                                      uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        // Store buffer to global variable
        memcpy(temperature_upper_threshold.bytes, app_env_cs.temp_uthr_from_air_buffer, CS_TEMPERATURE_MAX_LENGTH);

        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}

uint8_t CUSTOMSS_TempLTHRCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                      uint8_t *to, const uint8_t *from,
                                      uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        // Store buffer to global variable
        memcpy(temperature_lower_threshold.bytes, app_env_cs.temp_lthr_from_air_buffer, CS_TEMPERATURE_MAX_LENGTH);

        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}

uint8_t CUSTOMSS_VentCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                  uint8_t *to, const uint8_t *from,
                                  uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR) {
        memcpy(to, from, length);
        // Store buffer to global variable
        *vent_state = app_env_cs.vent_from_air_buffer[0];

        // Update the vent with the new state
        vent_update();

        return ATT_ERR_NO_ERROR;
    } else {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}
