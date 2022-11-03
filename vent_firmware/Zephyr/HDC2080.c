/******************************************************************************
 * File Name        : HDC2080.c
 * Description		: This module handles the HDC2080 interfacing via I2C
 * 					  communication.
 *
 * 					  Designed for the I2C connection with RSL15 with the
 * 					  following pinout:
 *                          HDC_SCL <--> GPIO_11 (I2C_0 Clock) // clock pin
 *                          HDC_SDA <--> GPIO_12 (I2C_0 Data)  // data pin
 *                          HDC_INT <--> GPIO_XX (GPIO Input)  // interrupt pin
 *
 * Author		    : Pierino Zindel
 * Date				: October 06, 2022
 * Version			: 1.1.0
 ******************************************************************************
 */


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include "HDC2080.h"


/* ----------------------------------------------------------------------------
 * Function definitions
 * --------------------------------------------------------------------------*/

double adc_to_humidity(uint16_t data)
{
	return data / (float) ADC_RESOLUTION * HUMIDITY_SCALING + HUMIDITY_OFFSET;
}

double adc_to_temperature(uint16_t data)
{
	return data / (float) ADC_RESOLUTION * TEMPERATURE_SCALING + TEMPERATURE_OFFSET;
}

void change_to_register(uint8_t reg)
{
	// Write slave address (write mode) + new register address
	i2c->MasterTransmit(HDC_ADDRESS, &reg, 1, false);

	// Wait for the transmission to complete and clear the peripheral
    MICRO_DELAY(500);
    i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);

	return;
}

double get_humidity(void)
{
	// Initialize a variable to store the final humidity
	uint16_t buffer = 0;

	// Set the register for the humidity LSB
	change_to_register(HUMIDITY_LOW);

	// Retrieve the low humidity value
	buffer |= read_from_register();

	// Set the register for the humidity MSB
	change_to_register(HUMIDITY_HIGH);

	// Retrieve the high humidity value
	buffer |= read_from_register() << BITS_PER_BYTE;

	// Adjust reading into a proper humidity
	double humidity = adc_to_humidity(buffer);

	return humidity;
}

double get_temperature(void)
{
	// Initialize a variable to store the final temperature
	uint16_t buffer = 0;

	// Set the register for the temp LSB
	change_to_register(TEMPERATURE_LOW);

	// Retrieve the low temp value
	buffer |= read_from_register();

	// Set the register for the temp MSB
	change_to_register(TEMPERATURE_HIGH);

	// Retrieve the high temp value
	buffer |= read_from_register() << BITS_PER_BYTE;

	// Adjust reading into a proper temperature
	double temperature = adc_to_temperature(buffer);

	return temperature;
}


void i2c_callback(uint32_t event)
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
        	uint32_t n = 10;
            while (n-- > 0) {
				Sys_GPIO_Toggle(APP_I2C_EVENT_GPIO);
				Sys_Delay((50 * SystemCoreClock) / 1000);
			}
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

void initialize_hdc2080(void)
{
	// Declare a bytes to store the register value data
	uint8_t reg_value = 0;

	// Setup the Temperature Offset Adjustment register
	reg_value = 0x00;
	write_to_register(TEMP_OFFSET_ADJUST, reg_value);

	// Setup the Humidity Offset Adjustment register
	reg_value = 0x00;
	write_to_register(HUM_OFFSET_ADJUST, reg_value);

	// Setup the Temperature Threshold LOW register
	reg_value = 0x00;
	write_to_register(TEMP_THR_L, reg_value);

	// Setup the Temperature Threshold HIGH register
	reg_value = 0xFF;
	write_to_register(TEMP_THR_H, reg_value);

	// Setup the Humidity Threshold LOW register
	reg_value = 0x00;
	write_to_register(RH_THR_L, reg_value);

	// Setup the Humidity Threshold HIGH register
	reg_value = 0xFF;
	write_to_register(RH_THR_H, reg_value);

	// Setup the Interrupt Configuration register
	reg_value = 0x00;
	write_to_register(INTERRUPT_ENABLE, reg_value);

	// Setup the Reset and DRDY/INT Configuration register
	reg_value = 0x00;
	write_to_register(INTERRUPT_CONFIG, reg_value);

	// Setup the Measurement Configuration register
	reg_value = 0x00;					// Config: 14 bit resolution; temp & humidity
	write_to_register(MEASURE_CONFIG, reg_value);

	return;
}

void initialize_i2c_connection(void)
{
	// Initialize the I2C handler and register the callback function
	i2c = &Driver_I2C0;
	i2c->Initialize(i2c_callback);
	error_check(i2c->PowerControl(ARM_POWER_FULL));

	// Configure the I2C bus speed; if bus is busy, abort transfer and try again
	while (i2c->Control(ARM_I2C_BUS_SPEED, I2C_SPEED) != ARM_DRIVER_OK) {
		i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);
	}

	return;
}

uint8_t read_from_register(void)
{
	// Initialize variable for read data
	uint8_t data;

	// Write START + Slave Address (write mode)
	i2c->MasterReceive(HDC_ADDRESS, &data, 1, false);

	// Wait for the transmission to complete and clear the peripheral
    MICRO_DELAY(500);
    i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);

	return data;
}

void trigger_measurement(void)
{
	// Trigger the measurement bit on the Measurement Configuration register
	write_to_register(MEASURE_CONFIG, HDC_MC_TRIG);
}

void write_to_register(uint8_t reg, uint8_t data)
{
	// Combine the register and data into a single array
	uint8_t buffer[2] = {reg, data};

	// Write slave address (write mode) + register address
	i2c->MasterTransmit(HDC_ADDRESS, buffer, 2, false);

	// Wait for the transmission to complete and clear the peripheral
    MICRO_DELAY(500);
    i2c->Control(ARM_I2C_ABORT_TRANSFER, 0);

	return;
}

