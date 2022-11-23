/******************************************************************************
 * File Name        : app.c
 * Description		: Main application source file
 *
 * Pinout			: HDC2080 Sensor (I2C peripheral)
 *                          HDC_SCL <--> GPIO_11 (I2C_0 Clock)
 *                          HDC_SDA <--> GPIO_12 (I2C_0 Data)
 *                          HDC_INT <--> GPIO_XX (GPIO Input)
 *                    FS90 Servo Motor (PWM peripheral)
 *                    		FS90_CTRL <--> GPIO_2 (PWM_0 Signal)
 *
 * Author		    : Pierino Zindel
 * Date				: October 25, 2022
 * Version			: 0.1.0
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

#include <app.h>

/* Global variables */
ARM_DRIVER_I2C *i2c;
double temperature_reading = 0;
double humidity_reading = 0;
uint8_t motor_state = 0;

DRIVER_PWM_t *pwm;
DRIVER_GPIO_t *gpio;
extern DRIVER_PWM_t Driver_PWM;
extern DRIVER_GPIO_t Driver_GPIO;

void error_check(uint32_t status)
{
    /* Otherwise, halt the program */
    if (status != ARM_DRIVER_OK)
    {
        //ToggleGPIO(APP_I2C_EVENT_GPIO, 4, 2);
        while (1)
        {
            SYS_WATCHDOG_REFRESH();
        }
    }
}

void sensor_initialization(void)
{
	// Initialize the HDC2080 I2C connection
	initialize_i2c_connection();
	initialize_hdc2080();

	return;
}

void sensor_measure(void)
{
	// Trigger the sensor and store the results
	trigger_measurement();
	temperature_reading = get_temperature();
	humidity_reading = get_humidity();

	return;
}

void motor_initialization(void)
{
	// Initialize the PWM function and GPIO pins for the servo
	// TODO: implement initialization function in motor driver module
	//initialize_pwm_control();
	//initialize_motor_pins();
	initialize_servo();

	return;
}
void motor_update(void)
{
	// Update the motor to the given state
	// TODO: define a new set of drivers for the motor
	//set_motor_state(motor_state);
	return;
}

void ble_initialization(void)
{
	// TODO: implement

    // Configure RF parameters and initialize BLE stack
    BLESystemInit();

    // Initialize Bluetooth Services */
    BatteryServiceServerInit();
    DeviceInformationServiceServerInit();
    CustomServiceServerInit();

    // Subscribe application callback handlers to BLE events
    AppMsgHandlersInit();

    // Prepare advertising and scan response data (device name + company ID)
    PrepareAdvScanData();

    /* In order to ensure that BLE lower layers are properly configured
     * according to host stack requirement, perform a BLE software reset.
     */
    GAPM_SoftwareReset();    // Step 1 (see details in readme)

    EnableBLEInterrupts();
    EnableAppInterrupts();

	return;
}

int main(void)
{
    // Disable interrupts and exceptions temporarily at startup
    PRIMASK_FAULTMASK_DISABLE_INTERRUPTS();

	/* Initialize main functionalities */
    DeviceInit();
    SWMTraceInit();

    // Print log
    swmLogInfo("__%s has started.\n", "ble_peripheral_server");

    /* Initialize peripherals */

    sensor_initialization();
    motor_initialization();
    ble_initialization();

    // Enable interrupts and exceptions
    PRIMASK_FAULTMASK_ENABLE_INTERRUPTS();

    //* Main application spin loop */
    main_loop();
}

void main_loop(void)
{
    while (1)
    {
        // Refresh the watchdog timer //
        SYS_WATCHDOG_REFRESH();
        BLE_Kernel_Process();

        if (GPIO0_Pressed())
        {
        	for (unsigned int i = 0; i < BLE_CONNECTION_MAX; i++)
            {
        		if(GAPC_IsConnectionActive(i))
        		{
        			ke_msg_send_basic(CUSTOM_BUTTON_NTF, KE_BUILD_ID(TASK_APP, i), KE_BUILD_ID(TASK_APP, i));
        		}
            }
            GPIO0_Pressed_Flag_Clear();
        }

        __WFI();
    }
}
