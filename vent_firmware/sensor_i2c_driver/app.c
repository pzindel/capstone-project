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
ARM_DRIVER_I2C *i2c;
uint8_t buffer[I2C_BUFFER_SIZE];
uint8_t orig_text_buffer[I2C_BUFFER_SIZE] = I2C_DATA;
double temperature_reading = 0;
double humidity_reading = 0;

void error_check(uint32_t status)
{
    /* Otherwise, halt the program */
    if (status != ARM_DRIVER_OK)
    {
        ToggleGPIO(APP_I2C_EVENT_GPIO, 4, 2);
        while (1)
        {
            SYS_WATCHDOG_REFRESH();
        }
    }
}

void GPIO0_IRQHandler(void)
{
    static bool ignore_next_gpio_int = false;
    if (ignore_next_gpio_int)
    {
        ignore_next_gpio_int = false;
    }

    /* Check if button pressed. */
    else if ((Sys_GPIO_Read(BUTTON_GPIO) == 0) && (i2c->GetStatus().mode == 0))
    {
        /* Button is pressed: Ignore next interrupt.
         * This is required to deal with the debounce circuit limitations. */
        ignore_next_gpio_int = true;

        /* Abort current transfer */
        i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);

        // Take a measurement
        trigger_measurement();
        temperature_reading = get_temperature();
        humidity_reading = get_humidity();
    }

    return;
}

void ToggleGPIO(uint32_t gpio, uint32_t n, uint32_t delay_ms)
{
    while (n-- > 0)
    {
        Sys_GPIO_Toggle(gpio);
        Sys_Delay((delay_ms * SystemCoreClock) / 1000);
    }
}

void I2C_CallBack(uint32_t event)
{
    if (event & ARM_I2C_EVENT_TRANSFER_DONE)
    {
    	i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);
    }
    /* If we hit an error state, signal via GPIO that an error occurred and
     * abort the current transfer.
     */
    else if ((event & ARM_I2C_EVENT_TRANSFER_INCOMPLETE) ||
             (event & ARM_I2C_EVENT_ADDRESS_NACK) ||
             (event & ARM_I2C_EVENT_ARBITRATION_LOST) ||
             (event & ARM_I2C_EVENT_BUS_ERROR))
    {
        // Abort current transfer
        i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);

        // Go back to SlaveReceive default mode
        //i2c->SlaveReceive(buffer, I2C_BUFFER_SIZE);

        /* To signal error, toggle GPIO state very fast
         * (10 times for 0.05 seconds each).
         * Only signal bus errors to the user. */
        if (event & ARM_I2C_EVENT_BUS_ERROR)
        {
            // Toggle GPIO 10 times, with 50ms period.
            ToggleGPIO(APP_I2C_EVENT_GPIO, 10, 50);
        }
    }
    else
    {
        /* if other event received, do nothing */
        /* Other possible events that are ignored here:
         * ARM_I2C_EVENT_SLAVE_TRANSMIT
         * ARM_I2C_EVENT_SLAVE_RECEIVE
         * ARM_I2C_EVENT_GENERAL_CALL
         * ARM_I2C_EVENT_BUS_CLEAR
         */
    }
}

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

    SYS_GPIO_CONFIG(BUTTON_GPIO, (GPIO_MODE_GPIO_IN | GPIO_WEAK_PULL_UP |
                                  GPIO_LPF_DISABLE));
    Sys_GPIO_IntConfig(0, GPIO_EVENT_TRANSITION | GPIO_SRC(BUTTON_GPIO) |
                       GPIO_DEBOUNCE_ENABLE,
                       GPIO_DEBOUNCE_SLOWCLK_DIV1024, MAX_DEBOUNCE);

    SYS_GPIO_CONFIG(APP_I2C_EVENT_GPIO, GPIO_MODE_GPIO_OUT);

    /* Disable JTAG TDI, TDO, and TRST connections to GPIO 2, 3, and 4 */
    GPIO->JTAG_SW_PAD_CFG &= ~(CM33_JTAG_DATA_ENABLED | CM33_JTAG_TRST_ENABLED);

    /* Enable BUTTON_GPIO interrupt */
    NVIC_EnableIRQ(GPIO0_IRQn);

    // Initialize the HDC2080 I2C connection
    initialize_i2c_connection();
    //initialize_hdc2080();

    /* Wait for new transfer as slave */
    error_check(i2c->SlaveReceive(buffer, I2C_BUFFER_SIZE));

    /* Main application spin loop */
    while (1)
    {
        /* Refresh the watchdog timer */
        SYS_WATCHDOG_REFRESH();
    }

    /* Should never be reached */
    return 0;
}
