/******************************************************************************
 * File Name        : app_customss.h
 * Disclaimer       : Adapted from onsemi example "ble_peripheral_server".
 * Description      : This header module contains the constants and function
 *                    prototypes for the application-specific Bluetooth
 *                    custom service server.
 *
 * Author           : Pierino Zindel
 * Version          : 1.0.0
 * Last Rev. Date   : November 24, 2022
 ******************************************************************************
 */
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
// Custom service UUIDs and characteristics

// Custom service UUIDs
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
// Battery level
#define CS_CHAR_BATTERY_UUID            { 0x24, 0xdc, 0x0e, 0x6e, 0x02, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// RSL on-board LED state
#define CS_CHAR_LED_UUID                { 0x24, 0xdc, 0x0e, 0x6e, 0x03, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// RSL on-board button state
#define CS_CHAR_BUTTON_UUID             { 0x24, 0xdc, 0x0e, 0x6e, 0x04, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// Vent (motor) state
#define CS_CHAR_VENT_UUID               { 0x24, 0xdc, 0x0e, 0x6e, 0x05, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// Sensor humidity reading
#define CS_CHAR_HUM_UUID                { 0x24, 0xdc, 0x0e, 0x6e, 0x06, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// Sensor temperature reading
#define CS_CHAR_TEMP_UUID               { 0x24, 0xdc, 0x0e, 0x6e, 0x07, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// Vent upper temperature threshold for auto-close
#define CS_CHAR_TEMP_UTHR_UUID          { 0x24, 0xdc, 0x0e, 0x6e, 0x08, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }
// Vent lower temperature threshold for auto-open
#define CS_CHAR_TEMP_LTHR_UUID          { 0x24, 0xdc, 0x0e, 0x6e, 0x09, 0x50, \
                                          0xca, 0x9e, 0xe5, 0xa9, 0xa3, 0x00, \
                                          0xb5, 0xf3, 0x93, 0xe0 }

#define CS_VALUE_MAX_LENGTH          20
#define CS_LONG_VALUE_MAX_LENGTH     40
#define CS_BATTERY_MAX_LENGTH        1
#define CS_LED_BUTTON_MAX_LENGTH     1
#define CS_VENT_STATE_MAX_LENGTH     1
#define CS_TEMPERATURE_MAX_LENGTH    4
#define CS_HUMIDITY_MAX_LENGTH       (CS_TEMPERATURE_MAX_LENGTH)

#define CS_TX_CHAR_NAME            "TX_VALUE"
#define CS_RX_CHAR_NAME            "RX_VALUE"
#define CS_TX_CHAR_LONG_NAME       "TX_VALUE_LONG"
#define CS_RX_CHAR_LONG_NAME       "RX_VALUE_LONG"
#define CS_BATTERY_CHAR_NAME       "BATTERY_LEVEL"
#define CS_LED_CHAR_NAME           "LED_STATE"
#define CS_BUTTON_CHAR_NAME        "BUTTON_STATE"
#define CS_VENT_CHAR_NAME          "VENT_STATE"
#define CS_HUM_CHAR_NAME           "HUMIDITY_VALUE"
#define CS_TEMP_CHAR_NAME          "TEMPERATURE_VALUE"
#define CS_TEMP_UTHR_CHAR_NAME     "TEMP_UPPER_THRESHOLD_VALUE"
#define CS_TEMP_LTHR_CHAR_NAME     "TEMP_LOWER_THRESHOLD_VALUE"

// Uncomment to use indications in the RX_VALUE_LONG characteristic
// #define RX_VALUE_LONG_INDICATION

// Custom service ID
// Used in calculating attribute number for given custom service
enum CUST_SVC_ID
{
    CUST_SVC0,
    CUST_SVC1,
};

enum CS0_att
{
    // Service 0
    CS_SERVICE0,

    // TX Characteristic in Service 0
    CS_TX_VALUE_CHAR0,
    CS_TX_VALUE_VAL0,
    CS_TX_VALUE_CCC0,
    CS_TX_VALUE_USR_DSCP0,

    // RX Characteristic in Service 0
    CS_RX_VALUE_CHAR0,
    CS_RX_VALUE_VAL0,
    CS_RX_VALUE_CCC0,
    CS_RX_VALUE_USR_DSCP0,

    // TX Long Characteristic in Service 0
    CS_TX_LONG_VALUE_CHAR0,
    CS_TX_LONG_VALUE_VAL0,
    CS_TX_LONG_VALUE_CCC0,
    CS_TX_LONG_VALUE_USR_DSCP0,

    // RX Long Characteristic in Service 0
    CS_RX_LONG_VALUE_CHAR0,
    CS_RX_LONG_VALUE_VAL0,
    CS_RX_LONG_VALUE_CCC0,
    CS_RX_LONG_VALUE_USR_DSCP0,

    // Max number of services and characteristics
    CS_NB0,
};

enum CS1_att
{
    // Service 1
    CS_SERVICE1,

    // Battery Characteristic in Service 1
    CS_BATTERY_VALUE_CHAR1,
    CS_BATTERY_VALUE_VAL1,
    CS_BATTERY_VALUE_CCC1,
    CS_BATTERY_VALUE_USR_DSCP1,

    // LED Characteristic in Service 1
    CS_LED_VALUE_CHAR1,
    CS_LED_VALUE_VAL1,
    CS_LED_VALUE_CCC1,
    CS_LED_VALUE_USR_DSCP1,

    // Button Characteristic in Service 1
    CS_BUTTON_VALUE_CHAR1,
    CS_BUTTON_VALUE_VAL1,
    CS_BUTTON_VALUE_CCC1,
    CS_BUTTON_VALUE_USR_DSCP1,

    // Vent Characteristic in Service 1
    CS_VENT_VALUE_CHAR1,
    CS_VENT_VALUE_VAL1,
    CS_VENT_VALUE_CCC1,
    CS_VENT_VALUE_USR_DSCP1,

    // Humidity Characteristic in Service 1
    CS_HUM_VALUE_CHAR1,
    CS_HUM_VALUE_VAL1,
    CS_HUM_VALUE_CCC1,
    CS_HUM_VALUE_USR_DSCP1,

    // Temperature Characteristic in Service 1
    CS_TEMP_VALUE_CHAR1,
    CS_TEMP_VALUE_VAL1,
    CS_TEMP_VALUE_CCC1,
    CS_TEMP_VALUE_USR_DSCP1,

    // Temperature Upper Threshold Characteristic in Service 1
    CS_TEMP_UTHR_VALUE_CHAR1,
    CS_TEMP_UTHR_VALUE_VAL1,
    CS_TEMP_UTHR_VALUE_CCC1,
    CS_TEMP_UTHR_VALUE_USR_DSCP1,

    // Temperature Lower Threshold Characteristic in Service 1
    CS_TEMP_LTHR_VALUE_CHAR1,
    CS_TEMP_LTHR_VALUE_VAL1,
    CS_TEMP_LTHR_VALUE_CCC1,
    CS_TEMP_LTHR_VALUE_USR_DSCP1,

    // Max number of services and characteristics
    CS_NB1,
};

struct app_env_tag_cs
{
    // To BLE transfer buffer
    uint8_t to_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value[2];

    // From BLE transfer buffer
    uint8_t from_air_buffer[CS_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value[2];

    // To BLE long transfer buffer
    uint8_t to_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t to_air_cccd_value_long[2];

    // From BLE long transfer buffer
    uint8_t from_air_buffer_long[CS_LONG_VALUE_MAX_LENGTH];
    uint8_t from_air_cccd_value_long[2];

    // To BLE Battery transfer buffer
    uint8_t battery_to_air_buffer[CS_BATTERY_MAX_LENGTH];
    uint8_t battery_to_air_cccd_value[2];

    // From BLE LED transfer buffer
    uint8_t led_from_air_buffer[CS_LED_BUTTON_MAX_LENGTH];
    uint8_t led_from_air_cccd_value[2];

    // To BLE Button transfer buffer
    uint8_t button_to_air_buffer[CS_LED_BUTTON_MAX_LENGTH];
    uint8_t button_to_air_cccd_value[2];

    // From BLE Vent transfer buffer
    uint8_t vent_from_air_buffer[CS_LED_BUTTON_MAX_LENGTH];
    uint8_t vent_from_air_cccd_value[2];

    // To BLE Humidity transfer buffer
    uint8_t hum_to_air_buffer[CS_HUMIDITY_MAX_LENGTH];
    uint8_t hum_to_air_cccd_value[2];

    // To BLE Temperature transfer buffer
    uint8_t temp_to_air_buffer[CS_TEMPERATURE_MAX_LENGTH];
    uint8_t temp_to_air_cccd_value[2];

    // From BLE Temperature Upper Threshold transfer buffer
    uint8_t temp_uthr_from_air_buffer[CS_TEMPERATURE_MAX_LENGTH];
    uint8_t temp_uthr_from_air_cccd_value[2];

    // From BLE Temperature Lower Threshold transfer buffer
    uint8_t temp_lthr_from_air_buffer[CS_TEMPERATURE_MAX_LENGTH];
    uint8_t temp_lthr_from_air_cccd_value[2];
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
 * Function prototypes
 * --------------------------------------------------------------------------*/

/* Function      : CUSTOMSS_GetDatabaseDescription
 *
 * Description   : Return attribute database related to custom service
 *
 * Parameters    : uint8_t att_db_cs_svc_number : Custom service id
 *
 * Returns       : const struct att_db_desc * : Custom service attribute database
 */
const struct att_db_desc * CUSTOMSS_GetDatabaseDescription(uint8_t att_db_cs_svc_number);

/* Function      : CUSTOMSS_Initialize
 *
 * Description   : Initialize custom service environment
 *
 * Parameters    : None
 *
 * Returns       : None
 */
void CUSTOMSS_Initialize(void);

/* Function      : CUSTOMSS_NotifyOnTimeout
 *
 * Description   : Configure custom service to send periodic notifications.
 *
 * Parameters    : uint32_t timeout : in units of 10ms. If set to 0, periodic
 *                                    notifications are disabled.
 *
 * Returns       : None
 */
void CUSTOMSS_NotifyOnTimeout(uint32_t timeout);

/* Function      : void CUSTOMSS_MsgHandler
 *
 * Description   : Handle all events related to the custom service
 *
 * Parameters    : ke_msg_id_t const msg_id   : Kernel message ID number
 *                 void const *param          : Message parameter
 *                 ke_task_id_t const dest_id : Destination task ID number
 *                 ke_task_id_t const src_id  : Source task ID number
 *
 * Returns       : None : Indicate if the message was consumed; compare with KE_MSG_CONSUMED
 */
void CUSTOMSS_MsgHandler(ke_msg_id_t const msg_id, void const *param,
                         ke_task_id_t const dest_id, ke_task_id_t const src_id);


/* Function      : GPIO0_Pressed
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns       : None
 */
uint8_t GPIO0_Pressed(void);

/* Function      : GPIO0_Pressed_Flag_Clear
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns       : None
 */
void GPIO0_Pressed_Flag_Clear(void);

/* Function      : GPIO0_IRQHandler
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns       : None
 */
void GPIO0_IRQHandler(void);

/* Function      : CUSTOMSS_RXCharCallback
 *
 * Description   : User callback data access function for the RX
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                                   "to" and "from" may be a pointer to the
 *                                   'att_db' characteristic buffer or the BLE
 *                                   stack buffer, depending if the "operation" is
 *                                   a write or a read.
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_RXCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                uint8_t *to, const uint8_t *from,
                                uint16_t length, uint16_t operation, uint8_t hl_status);

/* Function      : CUSTOMSS_RXLongCharCallback
 *
 * Description   : User callback data access function for the RX Long
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction. See att_db.
 *                 When a read occurs in the RX long characteristic, this function
 *                 updates the RX Long characteristic value with the complement of
 *                 TX long value.
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                                   "to" and "from" may be a pointer to the
 *                                   'att_db' characteristic buffer or the BLE
 *                                   stack buffer, depending if the "operation" is
 *                                   a write or a read.
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_RXLongCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                    uint8_t *to, const uint8_t *from,
                                    uint16_t length, uint16_t operation, uint8_t hl_status);

/* Function      : CUSTOMSS_LEDCharCallback
 *
 * Description   : User callback data access function for the LED
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                                   "to" and "from" may be a pointer to the
 *                                   'att_db' characteristic buffer or the BLE
 *                                   stack buffer, depending if the "operation" is
 *                                   a write or a read.
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_LEDCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status);

/* Function      : CUSTOMSS_TempUTHRCharCallback
 *
 * Description   : User callback data access function for the Temperature Upper
 *                 Threshold characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_TempUTHRCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status);

/* Function      : CUSTOMSS_TempLTHRCharCallback
 *
 * Description   : User callback data access function for the Temperature Lower
 *                 Threshold characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_TempLTHRCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status);

/* Function      : CUSTOMSS_VentCharCallback
 *
 * Description   : User callback data access function for the Vent State
 *                 characteristic. This function is called by the BLE
 *                 abstraction whenever a ReadReqInd or WriteReqInd occurs in
 *                 the specified attribute. The callback is linked to the
 *                 attribute in the database construction (see att_db).
 *
 * Parameters    : uint8_t conidx  : connection index
 *                 uint16_t attidx : attribute index in the user defined database
 *                 uint16_t handle : attribute handle allocated in the BLE stack
 *                 uint8_t *to     : pointer to destination buffer
 *                 uint8_t *from   : pointer to source buffer
 *                 uint16_t length : length of data to be copied
 *                 uint16_t operation : GATTC_ReadReqInd or GATTC_WriteReqInd
 *                 uint8_t hl_status  : HL error code
 *
 * Returns       : uint8_t : ATT_ERR_NO_ERROR if hl_status is equal to GAP_ERR_NO_ERROR,
 *                           hl_status otherwise
 */
uint8_t CUSTOMSS_VentCharCallback(uint8_t conidx, uint16_t attidx, uint16_t handle,
                                 uint8_t *to, const uint8_t *from,
                                 uint16_t length, uint16_t operation, uint8_t hl_status);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* BLE_CUSTOMSS_H */
