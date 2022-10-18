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
#include <RTE_Device.h>
#include <gpio_driver.h>

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

/* GPIO definitions */

/* GPIO number that is used for Debug Catch Mode
 * to easily connect the device to the debugger */
#define DEBUG_CATCH_GPIO                0

/* GPIO number that is acting as LED of EVB */
#define TIMER0_STATES_GPIO              GREEN_LED
#define SYSTICK_STATES_GPIO             BLUE_LED

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

/* To set Timer0 interrupt interval to 200 ms
 * Assumptions:
 *    - SYSCLK = 8 MHz
 *    - Slow Clock Prescale = 8
 *    - Timer0 Clock Source = SLOWCLK32
 *    - Timer0 Prescale = 8
 */
#define TIMER0_TIMEOUT_VAL_SETTING      781

/* To set SysTick interrupt interval to 100 ms (+/- 16 us)
 * Assumptions:
 *    - SYSCLK = 8 MHz
 *    - Slow Clock Prescale = 8
 *    - SysTick Clock Source = SLOWCLK32
 * Notes: 32 us/step: 3125 => 100 ms (+/- 16 us)
 */
#define SYSTICK_RELOAD_VAL_SETTING      3125

/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
extern DRIVER_GPIO_t Driver_GPIO;

/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/
/**
 * @brief   Toggle the global toggle status flag.
 */
extern void Button_EventCallback(uint32_t event);

/**
 * @brief    Timer0 Interrupt Handler
 */
extern void TIMER0_IRQHandler(void);

/**
 * @brief    SysTick Interrupt Handler
 */
extern void SysTick_Handler(void);


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
