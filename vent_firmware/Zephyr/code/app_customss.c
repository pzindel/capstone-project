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

#include <ble_abstraction.h>
#include <string.h>
#include <swmTrace_api.h>
#include <app_customss.h>
#include <app.h>

/* Global variable definition */
static struct app_env_tag_cs app_env_cs;

static const struct att_db_desc att_db_cs_svc0[] =
{
    /**** Service 0 ****/
    CS_SERVICE_UUID_128(CS_SERVICE0, CS_SVC_UUID),

    /* To the BLE transfer */
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

    /* From the BLE transfer */
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

    /* To the BLE long transfer */
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

    /* From the BLE long transfer */
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
    /* Client Characteristic Configuration descriptor */
    CS_CHAR_CCC(CS_RX_LONG_VALUE_CCC0,                           /* attidx */
                app_env_cs.from_air_cccd_value_long,             /* data */
                NULL),                                           /* callback */
    /* Characteristic User Description descriptor */
    CS_CHAR_USER_DESC(CS_RX_LONG_VALUE_USR_DSCP0,                /* attidx */
                      sizeof(CS_RX_CHAR_LONG_NAME) - 1,          /* length */
                      CS_RX_CHAR_LONG_NAME,                      /* data */
                      NULL),                                     /* callback */
};

static const struct att_db_desc att_db_cs_svc1[] =
{
    /**** Service 1 ****/
    CS_SERVICE_UUID_128(CS_SERVICE1, CS_BLT_SVC_UUID),

    /* To the BLE Temperature transfer */
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

    /* From the BLE LED Transfer */
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

    /* To the BLE Button transfer */
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

    /* From the BLE Vent Transfer */
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
};

static uint32_t notifyOnTimeout;
static uint8_t val_notif = 0;
static uint8_t button_value = 0;
static uint8_t gpio0_pressed = 0;

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_GetDatabaseDescription(uint8_t att_db_cs_svc_number)
 * ----------------------------------------------------------------------------
 * Description   : Return attribute database related to custom service
 * Inputs        : Custom service id
 * Outputs       : Custom service attribute database
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
const struct att_db_desc * CUSTOMSS_GetDatabaseDescription(uint8_t att_db_cs_svc_id)
{
    switch (att_db_cs_svc_id)
    {
        case 0:
        {
            return att_db_cs_svc0;
        }

        case 1:
        {
            return att_db_cs_svc1;
        }

        default:
            return NULL;
    }
}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_Initialize(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize custom service environment
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void CUSTOMSS_Initialize(void)
{
    memset(&app_env_cs, '\0', sizeof(struct app_env_tag_cs));

    app_env_cs.temp_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.temp_to_air_cccd_value[1] = 0x00;

    app_env_cs.button_to_air_cccd_value[0] = ATT_CCC_START_NTF;
    app_env_cs.button_to_air_cccd_value[1] = 0x00;

    notifyOnTimeout = 0;

    MsgHandler_Add(GATTM_ADD_SVC_RSP, CUSTOMSS_MsgHandler);
    MsgHandler_Add(CUSTOMSS_NTF_TIMEOUT, CUSTOMSS_MsgHandler);
    MsgHandler_Add(CUSTOM_BUTTON_NTF, CUSTOMSS_MsgHandler);
    MsgHandler_Add(GATTC_CMP_EVT, CUSTOMSS_MsgHandler);
}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_NotifyOnTimeout(uint32_t timeout)
 * ----------------------------------------------------------------------------
 * Description   : Configure custom service to send periodic notifications.
 * Inputs        : timeout       - in units of 10ms. If set to 0, periodic
 *                                 notifications are disabled.
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void CUSTOMSS_NotifyOnTimeout(uint32_t timeout)
{
    notifyOnTimeout = timeout;

    for (uint8_t i = 0; i < BLE_CONNECTION_MAX; i++)
    {
        if (GATT_GetEnv()->cust_svc_db[0].cust_svc_start_hdl && timeout)
        {
            ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, i),
                         timeout);
        }
    }
}

/* ----------------------------------------------------------------------------
 * Function      : void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id,
 *                                          void const *param,
 *                                          ke_task_id_t const dest_id,
 *                                          ke_task_id_t const src_id)
 * ----------------------------------------------------------------------------
 * Description   : Handle all events related to the custom service
 * Inputs        : - msg_id     - Kernel message ID number
 *                 - param      - Message parameter
 *                 - dest_id    - Destination task ID number
 *                 - src_id     - Source task ID number
 * Outputs       : return value - Indicate if the message was consumed;
 *                                compare with KE_MSG_CONSUMED
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    switch (msg_id)
    {
        case GATTM_ADD_SVC_RSP:
        {
            const struct gattm_add_svc_rsp *p = param;

            /* If service has been added successfully, start periodic notification timer */
            if (p->status == ATT_ERR_NO_ERROR && notifyOnTimeout)
            {
                for (unsigned int i = 0; i < BLE_CONNECTION_MAX; i++)
                {
                    ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, i),
                                 notifyOnTimeout);
                }
            }
        }
        break;

        case CUSTOMSS_NTF_TIMEOUT:
        {
            uint8_t conidx = KE_IDX_GET(dest_id);
            uint32_t encoded_temp = measureTemperature();
            memset(&app_env_cs.from_air_buffer[0], val_notif, CS_VALUE_MAX_LENGTH);
            app_env_cs.temp_to_air_buffer[0] = (uint8_t)((encoded_temp & 0x000000FF) >> 0);
            app_env_cs.temp_to_air_buffer[1] = (uint8_t)((encoded_temp & 0x0000FF00) >> 8);
            app_env_cs.temp_to_air_buffer[2] = (uint8_t)((encoded_temp & 0x00FF0000) >> 16);
            app_env_cs.temp_to_air_buffer[3] = (uint8_t)((encoded_temp & 0xFF000000) >> 24);

            if ((app_env_cs.from_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.from_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                /* Send notification to peer device */
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_VALUE_VAL0),
                                 CS_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer);
                val_notif++;
                swmLogInfo("\n__CUSTOMSS notifying peer device %d\r\n", conidx);
            }

            if (app_env_cs.from_air_cccd_value_long[1] == 0x00 && GAPC_IsConnectionActive(conidx))
            {
                /* Update RX long characteristic with the inverted version of
                 * TX long characteristic */
                for (uint8_t i = 0; i < CS_LONG_VALUE_MAX_LENGTH; i++)
                {
                    app_env_cs.from_air_buffer_long[i] = 0xFF ^ app_env_cs.to_air_buffer_long[i];
                }

                if (app_env_cs.from_air_cccd_value_long[0] == ATT_CCC_START_IND)
                {
                    /* Send indication to peer device */
                    GATTC_SendEvtCmd(conidx, GATTC_INDICATE, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_LONG_VALUE_VAL0),
                                     CS_LONG_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer_long);
                }

                if (app_env_cs.from_air_cccd_value_long[0] == ATT_CCC_START_NTF)
                {
                    /* Send notification to peer device */
                    GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC0, CS_RX_LONG_VALUE_VAL0),
                                     CS_LONG_VALUE_MAX_LENGTH, app_env_cs.from_air_buffer_long);
                }
            }

            if ((app_env_cs.temp_to_air_cccd_value[0] == ATT_CCC_START_NTF &&
                 app_env_cs.temp_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                /* Send notification to peer device */
                GATTC_SendEvtCmd(conidx, GATTC_NOTIFY, 0, GATTM_GetHandle(CUST_SVC1, CS_TEMP_VALUE_VAL1),
                                 CS_TEMPERATURE_MAX_LENGTH, app_env_cs.temp_to_air_buffer);
            }

            if (notifyOnTimeout)    /* Restart timer */
            {
                ke_timer_set(CUSTOMSS_NTF_TIMEOUT, KE_BUILD_ID(TASK_APP, conidx),
                             notifyOnTimeout);
            }
        }
        break;

        case CUSTOM_BUTTON_NTF:
        {
            uint8_t conidx = KE_IDX_GET(dest_id);
            memset(&app_env_cs.button_to_air_buffer[0], button_value,
                   CS_LED_BUTTON_MAX_LENGTH);
            if ((app_env_cs.button_to_air_cccd_value[0] == ATT_CCC_START_NTF
                 && app_env_cs.button_to_air_cccd_value[1] == 0x00)
                && GAPC_IsConnectionActive(conidx))
            {
                /* Send notification to peer device */
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

    if (button_pressed == 1)
    {
        /* If GPIO0 has just been disconnected from the ground
         * (SW1 pushbutton on the evaluation board has just been released) */

        button_pressed = 0;
        button_value = 0;

        /* Clear timers and restore LED state when button is released */
        ke_timer_clear(APP_SW1_TIMEOUT, TASK_APP);
        ke_timer_clear(APP_SW1LED_TIMEOUT, TASK_APP);

        LED_state = app_env_cs.led_from_air_buffer[0];

        if (LED_state == 0)
        {
            /* Turn off LED */
            Sys_GPIO_Set_High(LED_STATE_GPIO);
        }
        else
        {
            /* Turn on LED */
            Sys_GPIO_Set_Low(LED_STATE_GPIO);
        }
    }
    else if (Sys_GPIO_Read(BUTTON_GPIO) == 0)
    {
        /* If GPIO0 has just been connected to the ground
         * (SW1 pushbutton on the evaluation board has just been pressed) */

        button_pressed = 1;
        button_value = 1;

        /* Clear bond list after CLR_BDLST_HOLD_DURATION_S seconds */
        ke_timer_set(APP_SW1_TIMEOUT, TASK_APP, TIMER_SETTING_S(CLR_BONDLIST_HOLD_DURATION_S));
    }
    gpio0_pressed = 1;
}

/* ----------------------------------------------------------------------------
 * Function      : static void print_large_buffer(const uint8_t *buffer,
 *                                          uint16_t length)
 * ----------------------------------------------------------------------------
 * Description   : Use swmLogInfo for 10 Bytes of data at time.
 *                 remaining byte/s will be printed in string format to avoid
 *                 use of swmLogInfo for individual byte
 *                 This will result in reduce overhead for UART
 * Inputs        : - buffer     - data buffer
 *                 - length     - length of data
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
static void print_large_buffer(const uint8_t *buffer, uint16_t length)
{
    unsigned int num_of_blocks = (length / 10);
    unsigned int rem_bytes = ((num_of_blocks) ? (length % 10) : length);

    for (int i = 0; i < num_of_blocks; i++)
    {
        int j = (i * 10);
        swmLogInfo("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x ", buffer[j],
                   buffer[j + 1], buffer[j + 2], buffer[j + 3],
                   buffer[j + 4], buffer[j + 5], buffer[j + 6],
                   buffer[j + 7], buffer[j + 8], buffer[j + 9]);
    }

    if (rem_bytes)
    {
        int j = (num_of_blocks * 10);
        char temp_string[28] = { 0 };
        uint8_t index = 0;

        for (int i = j; i < length; i++)
        {
            sprintf(&temp_string[index], "%02x", buffer[i]);
            index += 2;

            /* put space before next data */
            temp_string[index] = 0x20;
            index += 1;
        }

        swmLogInfo("%s ", temp_string);
    }

    swmLogInfo("\r\n");
}

/* ----------------------------------------------------------------------------
 * Function      : uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx,
 *                         uint16_t attidx, uint16_t handle, uint8_t *to,
 *                         uint8_t *from, uint16_t length,
 *                         uint16_t operation, uint8_t hl_status)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the RX
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 * Inputs        : - conidx    - connection index
 *                 - attidx    - attribute index in the user defined database
 *                 - handle    - attribute handle allocated in the BLE stack
 *                 - to        - pointer to destination buffer
 *                 - from      - pointer to source buffer
 *                               "to" and "from" may be a pointer to the
 *                               'att_db' characteristic buffer or the BLE
 *                               stack buffer, depending if the "operation" is
 *                               a write or a read.
 *                 - length    - length of data to be copied
 *                 - operation - GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 - hl_status - HL error code
 * Outputs       : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                 hl_status otherwise
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *to, const uint8_t *from,
                                uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR)
    {
        memcpy(to, from, length);
        swmLogInfo("\nRXCharCallback (%d):(%d) ", conidx, length);
        print_large_buffer(app_env_cs.from_air_buffer, length);
        return ATT_ERR_NO_ERROR;
    }
    else
    {
        swmLogInfo("\nRXCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}

/* ----------------------------------------------------------------------------
 * Function      : uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx,
 *                          uint16_t attidx, uint16_t handle, uint8_t *to,
 *                          uint8_t *from, uint16_t length, uint16_t operation,
 *                          uint8_t hl_status)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the RX Long
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction. See att_db.
 *                 When a read occurs in the RX long characteristic, this function
 *                 updates the RX Long characteristic value with the complement of
 *                 TX long value.
 * Inputs        : - conidx    - connection index
 *                 - attidx    - attribute index in the user defined database
 *                 - handle    - attribute handle allocated in the BLE stack
 *                 - to        - pointer to destination buffer
 *                 - from      - pointer to source buffer
 *                               "to" and "from" may be a pointer to the
 *                               'att_db' characteristic buffer or the BLE
 *                               stack buffer, depending if the "operation" is
 *                               a write or a read.
 *                 - length    - length of data to be copied
 *                 - operation - GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 - hl_status - HL error code
 * Outputs       : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                 hl_status otherwise
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                    uint8_t *to, const uint8_t *from,
                                    uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR)
    {
        memcpy(to, from, length);
        swmLogInfo("\nRXLongCharCallback (%d):(%d) ", conidx, length);

        /* Update RX long characteristic with the inverted version of
         * TX long characteristic just received */
        if (operation == GATTC_READ_REQ_IND)
        {
            for (uint8_t i = 0; i < CS_LONG_VALUE_MAX_LENGTH; i++)
            {
                app_env_cs.from_air_buffer_long[i] = 0xFF ^ app_env_cs.to_air_buffer_long[i];
            }
        }

        print_large_buffer(app_env_cs.from_air_buffer_long, length);
        return ATT_ERR_NO_ERROR;
    }
    else
    {
        swmLogInfo("\nRXLongCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}

/* ----------------------------------------------------------------------------
 * Function      : uint8_t CUSTOMSS_LEDCharCallback(uint8_t conidx,
 *                         uint16_t attidx, uint16_t handle, uint8_t *to,
 *                         uint8_t *from, uint16_t length,
 *                         uint16_t operation, uint8_t hl_status)
 * ----------------------------------------------------------------------------
 * Description   : User callback data access function for the LED
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 * Inputs        : - conidx    - connection index
 *                 - attidx    - attribute index in the user defined database
 *                 - handle    - attribute handle allocated in the BLE stack
 *                 - to        - pointer to destination buffer
 *                 - from      - pointer to source buffer
 *                               "to" and "from" may be a pointer to the
 *                               'att_db' characteristic buffer or the BLE
 *                               stack buffer, depending if the "operation" is
 *                               a write or a read.
 *                 - length    - length of data to be copied
 *                 - operation - GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 - hl_status - HL error code
 * Outputs       : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                 hl_status otherwise
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
uint8_t CUSTOMSS_LEDCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR)
    {
        memcpy(to, from, length);
        if (app_env_cs.led_from_air_buffer[0] == 0)
        {
//            Sys_GPIO_Set_High(LED_STATE_GPIO);    /* Turn LED off */
        	set_vent_state(VENT_CLOSED_STATE);
            swmLogInfo("\nReceived LED OFF");
        }
        else if (app_env_cs.led_from_air_buffer[0] == 1)
        {
//            Sys_GPIO_Set_Low(LED_STATE_GPIO);    /* Turn LED on */
        	set_vent_state(VENT_OPEN_STATE);
        	swmLogInfo("\nReceived LED ON");
        }
        return ATT_ERR_NO_ERROR;
    }
    else
    {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}


uint8_t CUSTOMSS_VentCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status)
{
    if (hl_status == GAP_ERR_NO_ERROR)
    {
        memcpy(to, from, length);
        if (app_env_cs.vent_from_air_buffer[0] == 0)
        {
        	set_vent_state(VENT_CLOSED_STATE);    /* Turn LED off */
//            swmLogInfo("\nReceived LED OFF");
        }
        else if (app_env_cs.vent_from_air_buffer[0] == 1)
        {
        	set_vent_state(VENT_OPEN_STATE);    /* Turn LED on */
//            swmLogInfo("\nReceived LED ON");
        }
        return ATT_ERR_NO_ERROR;
    }
    else
    {
        swmLogInfo("\nLEDCharCallback (%d): operation (%d): error(%d) \r\n", conidx, operation, hl_status);
        return hl_status;
    }
}
