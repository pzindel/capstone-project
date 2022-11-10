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
#include "pwm_driver.h"
#include "Servo.h"

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* GPIO definitions */

/* GPIO number that is used for Debug Catch Mode
 * to easily connect the device to the debugger */
#define DEBUG_CATCH_GPIO                0

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


/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/

/**
 * @brief Set all PWM channels to a known state.
 * @return Zero
 */
void init_pwm_registers(void);

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
