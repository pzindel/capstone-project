/**
 * @file app_customss.h
 * @brief Application-specific Bluetooth custom service server header file
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

#ifndef APP_CUSTOMSS_H
#define APP_CUSTOMSS_H

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <gattc_task.h>

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* Custom service UUIDs and characteristics */

/* Custom service UUIDs */
#define CS_SVC_UUID                     { 0x24, 0xdc, 0x0e, 0x6e, 0x01, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_TX_UUID                 { 0x24, 0xdc, 0x0e, 0x6e, 0x02, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_RX_UUID                 { 0x24, 0xdc, 0x0e, 0x6e, 0x03, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_LONG_TX_UUID            { 0x24, 0xdc, 0x0e, 0x6e, 0x04, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_LONG_RX_UUID            { 0x24, 0xdc, 0x0e, 0x6e, 0x05, 0x40, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }

#define CS_BLT_SVC_UUID                 { 0x24, 0xdc, 0x0e, 0x6e, 0x01, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_TEMP_UUID               { 0x24, 0xdc, 0x0e, 0x6e, 0x02, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_LED_UUID                { 0x24, 0xdc, 0x0e, 0x6e, 0x03, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
#define CS_CHAR_BUTTON_UUID             { 0x24, 0xdc, 0x0e, 0x6e, 0x04, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }

#define CS_VALUE_MAX_LENGTH          20
#define CS_LONG_VALUE_MAX_LENGTH     40
#define CS_LED_BUTTON_MAX_LENGTH     1
#define CS_TEMPERATURE_MAX_LENGTH    4

#define CS_TX_CHAR_NAME            "TX_VALUE"
#define CS_RX_CHAR_NAME            "RX_VALUE"
#define CS_TX_CHAR_LONG_NAME       "TX_VALUE_LONG"
#define CS_RX_CHAR_LONG_NAME       "RX_VALUE_LONG"
#define CS_TEMP_CHAR_NAME          "TEMPERATURE_VALUE"
#define CS_LED_CHAR_NAME           "LED_STATE"
#define CS_BUTTON_CHAR_NAME        "BUTTON_STATE"

/* Uncomment to use indications in the RX_VALUE_LONG characteristic */
/* #define RX_VALUE_LONG_INDICATION */

/* Custom service ID */
/* Used in calculating attribute number for given custom service */
enum CUST_SVC_ID
{
    CUST_SVC0,
    CUST_SVC1,
};

enum CS0_att
{
    /* Service 0 */
    CS_SERVICE0,

    /* TX Characteristic in Service 0 */
    CS_TX_VALUE_CHAR0,
    CS_TX_VALUE_VAL0,
    CS_TX_VALUE_CCC0,
    CS_TX_VALUE_USR_DSCP0,

    /* RX Characteristic in Service 0 */
    CS_RX_VALUE_CHAR0,
    CS_RX_VALUE_VAL0,
    CS_RX_VALUE_CCC0,
    CS_RX_VALUE_USR_DSCP0,

    /* TX Long Characteristic in Service 0 */
    CS_TX_LONG_VALUE_CHAR0,
    CS_TX_LONG_VALUE_VAL0,
    CS_TX_LONG_VALUE_CCC0,
    CS_TX_LONG_VALUE_USR_DSCP0,

    /* RX Long Characteristic in Service 0 */
    CS_RX_LONG_VALUE_CHAR0,
    CS_RX_LONG_VALUE_VAL0,
    CS_RX_LONG_VALUE_CCC0,
    CS_RX_LONG_VALUE_USR_DSCP0,

    /* Max number of services and characteristics */
    CS_NB0,
};

enum CS1_att
{
    /* Service 1 */
    CS_SERVICE1,

    /* Temperature Characteristic in Service 1 */
    CS_TEMP_VALUE_CHAR1,
    CS_TEMP_VALUE_VAL1,
    CS_TEMP_VALUE_CCC1,
    CS_TEMP_VALUE_USR_DSCP1,

    /* LED Characteristic in Service 1 */
    CS_LED_VALUE_CHAR1,
    CS_LED_VALUE_VAL1,
    CS_LED_VALUE_CCC1,
    CS_LED_VALUE_USR_DSCP1,

    /* Button Characteristic in Service 1 */
    CS_BUTTON_VALUE_CHAR1,
    CS_BUTTON_VALUE_VAL1,
    CS_BUTTON_VALUE_CCC1,
    CS_BUTTON_VALUE_USR_DSCP1,

    /* Max number of services and characteristics */
    CS_NB1,
};

struct app_env_tag_cs
{
    /* To BLE transfer buffer */
    uint8_t to_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value[2];

    /* From BLE transfer buffer */
    uint8_t from_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value[2];

    /* To BLE long transfer buffer */
    uint8_t to_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value_long[2];

    /* From BLE long transfer buffer */
    uint8_t from_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value_long[2];

    /* To BLE Temperature transfer buffer */
    uint8_t temp_to_air_buffer[CS_TEMPERATURE_MAX_LENGTH];
    uint8_t temp_to_air_cccd_value[2];

    /* From BLE transfer buffer */
    uint8_t led_from_air_buffer[CS_LED_BUTTON_MAX_LENGTH];
    uint8_t led_from_air_cccd_value[2];

    /* To BLE Button transfer buffer */
    uint8_t button_to_air_buffer[CS_LED_BUTTON_MAX_LENGTH];
    uint8_t button_to_air_cccd_value[2];
};

enum custom_app_msg_id
{
    CUSTOMSS_NTF_TIMEOUT = TASK_FIRST_MSG(TASK_ID_APP) + 60,
    CUSTOM_BUTTON_NTF
};

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------
 * Function prototype definitions
 * --------------------------------------------------------------------------*/
const struct att_db_desc * CUSTOMSS_GetDatabaseDescription(uint8_t att_db_cs_svc_number);

void CUSTOMSS_Initialize(void);

void CUSTOMSS_NotifyOnTimeout(uint32_t timeout);

void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id);

void GPIO0_IRQHandler(void);

uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *to, const uint8_t *from,
                                uint16_t length, uint16_t operation, uint8_t hl_status);

uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                    uint8_t *to, const uint8_t *from,
                                    uint16_t length, uint16_t operation, uint8_t hl_status);

uint8_t CUSTOMSS_LEDCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status);

uint8_t GPIO0_Pressed(void);

void GPIO0_Pressed_Flag_Clear(void);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* BLE_CUSTOMSS_H */
