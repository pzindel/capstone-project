/**
 * @file app.h
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

#ifndef APP_H_
#define APP_H_

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
#include <hw.h>
#include <string.h>
#include <stdio.h>
#include "RTE_Device.h"
#include "i2c_driver.h"
#include "HDC2080.h"

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/
#if (!RTE_I2C0_ENABLED)
    #error "Please configure I2C in RTE_Device.h"
#endif    /* if (!RTE_I2C0) */

/* GPIO definitions */

/* GPIO number that is used for Debug Catch Mode
 * to easily connect the device to the debugger */
#define DEBUG_CATCH_GPIO                0
#define BUTTON_GPIO                     0
#define APP_I2C_EVENT_GPIO              GREEN_LED

/* Set UART peripheral clock */
#define UART_CLK                        8000000

/* Set sensor clock */
#define SENSOR_CLK                      32768

/* Set user clock */
#define USER_CLK                        1000000

/* Enable/disable buck converter
 * Options: VCC_BUCK or VCC_LDO
 */
#define VCC_BUCK_LDO_CTRL               VCC_LDO

#define CONCAT(x, y)                    (x##y)
#define GPIO_SRC(x)                     CONCAT(GPIO_SRC_GPIO_, x)

/* De-bounce definition */
#define MAX_DEBOUNCE                    255

/* I2C GPIOs defined in RTE_Device.h */

/* I2C related definitions. TX/RX pins are configured in RTE_Device.h */
#define I2C_DATA                        "onsemi I2C"
#define I2C_BUFFER_SIZE                 (sizeof I2C_DATA)
#define I2C_OWN_SLAVE_ADDR              5

/* Supported I2C_SPEED options:
 *  ARM_I2C_BUS_SPEED_STANDARD  = 100kHz
 *  ARM_I2C_BUS_SPEED_FAST      = 400kHz
 *  ARM_I2C_BUS_SPEED_FAST_PLUS = 1MHz */
#define I2C_SPEED                       ARM_I2C_BUS_SPEED_STANDARD

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
extern ARM_DRIVER_I2C Driver_I2C0;
extern ARM_DRIVER_I2C *i2c;
extern uint8_t buffer[I2C_BUFFER_SIZE];

/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/
/**
 * @brief       This function is a callback registered by the function
 *              Initialize. The parameter event indicates one or more events
 *              that occurred during driver operation.
 * @param[in]   event I2C Events notification mask
 */
extern void I2C_CallBack(uint32_t event);

/**
 * @brief       Toggle the specified GPIO 'n' times, delayed by 'delay_s'
 *              seconds.
 * @param[in]   gpio GPIO number
 * @param[in]   n  Number of toggles
 * @param[in]   delay_s  Delay between each toggle
 */
extern void ToggleGPIO(uint32_t gpio, uint32_t n, uint32_t delay_ms);

/**
 * @brief       Interrupt handler triggered by a button press. Cancel any
 *              ongoing transfers, switch to Master mode and start a
 *              MasterTransmit operation through I2C.
 */
extern void GPIO0_IRQHandler(void);

/**
 * @brief       Checks the return of the I2C->Control function for errors.
 *              if errors exist, exit program by running infinite loop.
 */
extern void error_check(uint32_t status);

/**
 * @brief Initialize the system, including GPIOs and interrupts.
 * @return Zero
 */
void Initialize(void);

/**
 * @brief The main entry point for the program
 */
int main(void);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_H_ */
