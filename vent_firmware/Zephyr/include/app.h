/******************************************************************************
 * File Name        : app.h
 * Disclaimer       : Adapted from onsemi example "ble_peripheral_server".
 * Description		: Header file for main application.
 *
 * Pinout			: HDC2080 Sensor (I2C peripheral)
 *                          HDC_SCL <--> GPIO_11 (I2C_0 Clock)
 *                          HDC_SDA <--> GPIO_12 (I2C_0 Data)
 *                          HDC_INT <--> GPIO_XX (GPIO Input)
 *                    FS90 Servo Motor (PWM peripheral)
 *                    		FS90_CTRL <--> GPIO_2 (PWM_0 Signal)
 *
 * Author		    : Pierino Zindel
 * Last Rev. Date	: October 25, 2022
 * Version			: 1.0.0
 ******************************************************************************
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
 ******************************************************************************
 */

#ifndef APP_H_
#define APP_H_

#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/

#include <hw.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <swmTrace_api.h>
#include <flash_rom.h>
#include <ble_protocol_support.h>
#include <ble_abstraction.h>

#include <app_init.h>
#include <app_msg_handler.h>
#include <app_customss.h>
#include <app_bass.h>
#include <app_diss.h>
#include <app_temperature_sensor.h>
#include "RTE_Device.h"

#include "i2c_driver.h"
#include "HDC2080.h"
#include "pwm_driver.h"
#include "Servo.h"


/* ----------------------------------------------------------------------------
 * Typedef
 * --------------------------------------------------------------------------*/
typedef union {
    float value;
    uint8_t bytes[CS_TEMPERATURE_MAX_LENGTH];
} EncodedFloat;


/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

// APP Task messages
enum appm_msg
{
    APPM_DUMMY_MSG = TASK_FIRST_MSG(TASK_ID_APP),
    APP_LED_TIMEOUT,
    APP_BATT_LEVEL_READ_TIMEOUT,
    APP_SW1_TIMEOUT,
    APP_SW1LED_TIMEOUT
};

#define VCC_BUCK_LDO_CTRL               VCC_LDO

//#define CONCAT(x, y)                    (x##y)
#define GPIO_SRC(x)                     CONCAT(GPIO_SRC_GPIO_, x)

//**** Temperature threshold defines ****
#define UPPER_TEMP_THRESHOLD            (0)
#define LOWER_TEMP_THRESHOLD            (1)
#define THRESHOLD_OFF_LIMIT             (100)   // if the threshold value exceeds this it will be deactivated
#define THRESHOLD_OFF_DELTA             (1.1)   // an error margin for checking if the threshold is deactivated

//**** Application common BLE parameter defines ****
// Extended Advertising
//  Set this define to 1 to enable extended advertising
#define ADV_EXTENSION                   (0)

#define APP_BLE_DEV_PARAM_SOURCE        APP_PROVIDED    // Or APP_PROVIDED FLASH_PROVIDED_or_DFLT.

// Advertising channel map - 37, 38, 39
#define APP_ADV_CHMAP                   GAPM_DEFAULT_ADV_CHMAP

// Advertising minimum interval - 40ms (64 * 0.625ms)
#define APP_ADV_INT_MIN                 GAPM_DEFAULT_ADV_INTV_MIN

// Advertising maximum interval - 40ms (64*0.625ms)
#define APP_ADV_INT_MAX                 GAPM_DEFAULT_ADV_INTV_MAX

// Location of BLE public address
//	- BLE public address location in MNVR is used as a default value;
//  - Any other valid locations can be used as needed.
//
#define APP_BLE_PUBLIC_ADDR_LOC         BLE_PUBLIC_ADDR_LOC_MNVR

#define GAPM_CFG_ADDR_PUBLIC            (0 << GAPM_PRIV_CFG_PRIV_ADDR_POS)
#define GAPM_CFG_ADDR_PRIVATE           (1 << GAPM_PRIV_CFG_PRIV_ADDR_POS)

#define GAPM_CFG_HOST_PRIVACY           (0 << GAPM_PRIV_CFG_PRIV_EN_POS)
#define GAPM_CFG_CONTROLLER_PRIVACY     (1 << GAPM_PRIV_CFG_PRIV_EN_POS)

#define GAPM_ADDRESS_TYPE               GAPM_CFG_ADDR_PRIVATE

#define GAPM_PRIVACY_TYPE               GAPM_CFG_HOST_PRIVACY
#define GAPM_OWN_ADDR_TYPE              GAPM_STATIC_ADDR    // GAPM_GEN_RSLV_ADDR for Host privacy.

#define APP_BD_RENEW_DUR                (150)    // In seconds.

// BLE private address of local device
#ifndef APP_BLE_PRIVATE_ADDR
#define APP_BLE_PRIVATE_ADDR            { 0x93, 0x11, 0x22, 0xff, 0xbb, 0xD5 }
#endif	 // APP_BLE_PRIVATE_ADDR

// Number of standard profiles and custom services added in this application
#define APP_NUM_STD_PRF                 (2)
#define APP_NUM_CUST_SVC                (2)

// GPIO number that is connected to LED of EVB
#define LED_STATE_GPIO                  GREEN_LED

// GPIO number that is used to determine the number of BLE connections
#define CONNECTION_STATE_GPIO           BLUE_LED

// Advertising data is composed by device name and company identification (ID)
//  Notes: In order to have both device name and company ID included in
//         the advertising, the length of APP_DEVICE_NAME should not exceed 22 bytes.
#define APP_DEVICE_NAME                 "zephyr_ble_vent"
#define APP_DEVICE_NAME_LEN             (sizeof(APP_DEVICE_NAME) - 1)

// Manufacturer info (onsemi Company ID)
#define APP_COMPANY_ID                  { 0x62, 0x3 }
#define APP_COMPANY_ID_LEN              (2)

#define APP_DEVICE_APPEARANCE           (0)
#define APP_PREF_SLV_MIN_CON_INTERVAL   (8)
#define APP_PREF_SLV_MAX_CON_INTERVAL   (10)
#define APP_PREF_SLV_LATENCY            (0)
#define APP_PREF_SLV_SUP_TIMEOUT        (200)

// Application-provided IRK
#define APP_IRK                         { 0x01, 0x23, 0x45, 0x68, 0x78, 0x9a, \
                                          0xbc, 0xde, 0x01, 0x23, 0x45, 0x68, \
                                          0x78, 0x9a, 0xbc, 0xde }

// Application-provided CSRK
#define APP_CSRK                        { 0x01, 0x23, 0x45, 0x68, 0x78, 0x9a, \
                                          0xbc, 0xde, 0x01, 0x23, 0x45, 0x68, \
                                          0x78, 0x9a, 0xbc, 0xde }


// Based on enum gap_phy
#define APP_PREFERRED_PHY_RX            GAP_PHY_LE_CODED
#define APP_PREFERRED_PHY_TX            GAP_PHY_LE_CODED

// Based on enum gapc_phy_option
#define APP_PREFERRED_CODED_PHY_RATE    GAPC_PHY_OPT_LE_CODED_125K_RATE

#define SECURE_CONNECTION               (1)    // set 0 for LEGACY_CONNECTION or 1 for SECURE_CONNECTION.

//**** Application common interface defines  ****
// Enable/disable swmtrace
#define SWMTRACE_ENABLE                 (1)

#define LOW_POWER_CLOCK_ACCURACY        (100)         // ppm
#define TWOSC                           (1200)        // us
#define MAX_SLEEP_DURATION              (0x17700)     // 30s

//**** GPIO definitions ****

// GPIO number that is used for Debug Catch Mode
// to easily connect the device to the debugger
#define DEBUG_CATCH_GPIO                (0)
#define BUTTON_GPIO						0
#define APP_I2C_EVENT_GPIO				(GREEN_LED)

// Default LSAD channel for SetTxPower
#define LSAD_TXPWR_DEF                  (1)

// Default TX power setting
#define DEF_TX_POWER                    (0)

// Set UART peripheral clock
#define UART_CLK                        (8000000)

// Set sensor clock
#define SENSOR_CLK                      (32768)

// Set user clock
#define USER_CLK                        (1000000)

// Enable/disable buck converter
//#define VCC_BUCK_LDO_CTRL               VCC_BUCK    // Or VCC_LDO

// The GPIO pin to use for TX when using the UART mode
#define UART_TX_GPIO                    (6)

// The GPIO pin to use for RX when using the UART mode
#define UART_RX_GPIO                    (5)

// The selected baud rate for the application when using UART mode
#define UART_BAUD                       (115200)


//**** Application specific other defines ****
// Timer setting in units of 1ms (kernel timer resolution)
#define TIMER_SETTING_MS(MS)            MS
#define TIMER_SETTING_S(S)              (S * 1000)

// Hold duration required to trigger bond list clear (in seconds)
#define CLR_BONDLIST_HOLD_DURATION_S    5

// Set 0 for default permission or 1 to require a secure connection link
#define BUTTON_SECURE_ATTRIBUTE			(0)

// Delay between each toggle in clear bond list (in milliseconds)
#define CLR_BONDLIST_LED_TOGGLE_INTERVAL_MS    100

// De-bounce definition
#define MAX_DEBOUNCE					(255)

// I2C GPIOs defined in RTE_Device.h


/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
// I2C driver handler
extern ARM_DRIVER_I2C Driver_I2C0;
extern ARM_DRIVER_I2C *i2c;
// PWM driver handler
extern DRIVER_PWM_t Driver_PWM;
extern DRIVER_PWM_t *pwm;
// GPIO driver handler
extern DRIVER_GPIO_t Driver_GPIO;
extern DRIVER_GPIO_t *gpio;

// Sensor value storage
extern EncodedFloat temperature_reading;
extern EncodedFloat humidity_reading;
extern EncodedFloat temperature_upper_threshold;
extern EncodedFloat temperature_lower_threshold;
// Motor value storage
extern uint8_t *vent_state;
// Battery level value storage
extern uint8_t battery_level;


/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/

/* Function      : ToggleGPIO
 *
 * Description   : Toggle the specified GPIO 'n' times, delayed by 'delay_s'
 *                 seconds.
 *
 * Parameters    : uint32_t gpio     : GPIO number
 *                 uint32_t n        : Number of toggles
 *                 uint32_t delay_ms : Delay between each toggle
 *
 * Returns       : None
 */
//extern void ToggleGPIO(uint32_t gpio, uint32_t n, uint32_t delay_ms);

/* Function      : GPIO0_IRQHandler
 *
 * Description   : Interrupt handler triggered by a button press. Cancel any
 *                 ongoing transfers, switch to Master mode and start a
 *                 MasterTransmit operation through I2C.
 *
 * Parameters    : None
 *
 * Returns       : None
 */
//extern void GPIO0_IRQHandler(void);

/* Function      : ble_initialization
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void ble_initialization(void);

/* Function      : error_check
 *
 * Description   : Checks the return of the I2C->Control function for errors.
 *                 if errors exist, exit program by running infinite loop.
 *
 * Parameters    : uint32_t status :
 *
 * Returns		 : None
 */
extern void error_check(uint32_t status);

/* Function      : main
 *
 * Description   : The main entry point for the program.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
int main(void);

/* Function      : main_loop
 *
 * Description   : This function contains the application spin loop for main.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void main_loop(void);

/* Function      : vent_initialization
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void vent_initialization(void);

/* Function      : vent_update
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void vent_update(void);

/* Function      : vent_update
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns       : None
 */
void vent_threshold_check(void);

/* Function      : sensor_initialization
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void sensor_initialization(void);

/* Function      : sensor_measurement
 *
 * Description   :
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void sensor_measurement(void);


#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_H_ */
