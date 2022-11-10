/**
 * @file app.c
 * @brief Main application source file
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

#include "app.h"

/* Global variables */
DRIVER_PWM_t *pwm;
DRIVER_GPIO_t *gpio;
extern DRIVER_PWM_t Driver_PWM;
extern DRIVER_GPIO_t Driver_GPIO;

/**
 * @brief Initialize the system, including GPIOs and interrupts.
 * @return Zero
 */
void Initialize(void)
{
    /* Interrupts off */
    __set_PRIMASK(PRIMASK_DISABLE_INTERRUPTS);
    __set_FAULTMASK(FAULTMASK_DISABLE_INTERRUPTS);

    /* Disable all existing interrupts, clearing all pending source */
    Sys_NVIC_DisableAllInt();
    Sys_NVIC_ClearAllPendingInt();

	/* Debug Catch Mode
	 * If DEBUG_CATCH_GPIO is low, enter Debug Catch Mode which holds the program execution in a
	 * while loop to make it easier to connect to the debugger.
	 * We suggest retaining this feature during development.
	 */
    SYS_GPIO_CONFIG(DEBUG_CATCH_GPIO, (GPIO_MODE_GPIO_IN | GPIO_LPF_DISABLE |
                                       GPIO_WEAK_PULL_UP | GPIO_6X_DRIVE));

    while ((Sys_GPIO_Read(DEBUG_CATCH_GPIO)) == 0)
    {
        SYS_WATCHDOG_REFRESH();
    }

    /* Load default trim values. */
    uint32_t trim_error __attribute__((unused)) = SYS_TRIM_LOAD_DEFAULT();

    /* Enable the 48MHz XTAL */
    Sys_Clocks_XTALClkConfig(CK_DIV_1_6_PRESCALE_6_BYTE);

    /* Switch to (divided 48 MHz) oscillator clock, and update the
     * SystemCoreClock global variable. */
    Sys_Clocks_SystemClkConfig(SYSCLK_CLKSRC_RFCLK);

    /* Enable/disable buck converter */
#ifdef RSL15_CID
    Sys_ACS_WriteRegister(&ACS->VCC_CTRL, ((ACS->VCC_CTRL & ~VCC_BUCK) | VCC_BUCK_LDO_CTRL));
#else    /* ifdef RSL15_CID */
    ACS->VCC_CTRL = ((ACS->VCC_CTRL & ~VCC_BUCK) | VCC_BUCK_LDO_CTRL);
#endif    /* ifdef RSL15_CID */

    /* Configure clock dividers */
    Sys_Clocks_DividerConfig(UART_CLK, SENSOR_CLK, USER_CLK);

    /* Configure Baseband Controller Interface */
    BBIF->CTRL = (BB_CLK_ENABLE | BBCLK_DIVIDER_8);

    /* Interrupts back on */
    __set_PRIMASK(PRIMASK_ENABLE_INTERRUPTS);
    __set_FAULTMASK(FAULTMASK_ENABLE_INTERRUPTS);
}

/**
 * @brief The main entry point for the program
 */
int main(void)
{

    /* Initialize the system */
    Initialize();

    // Initialize the Servo
    initialize_servo();

    /* Main application spin loop */
    while (1)
    {
    	// Open the vent
    	set_vent_state(VENT_OPEN_STATE);

    	// Wait for 5 seconds
    	SECOND_DELAY(1);

    	/*pwm->Stop(0);

    	SECOND_DELAY(1);

    	pwm->Start(0);*/

    	// Close the vent
    	set_vent_state(VENT_CLOSED_STATE);

    	// Wait for 5 more seconds
    	SECOND_DELAY(1);

        /* Refresh the watchdog timer */
        SYS_WATCHDOG_REFRESH();
    }

    /* Should never be reached */
    return 0;
}
