/******************************************************************************
 * File Name        : HDC2080.h
 * Description		: This header module contains the constants and function
 * 					  prototypes for the HDC2080 temperature & humidity module.
 *
 * 					  Designed for the I2C connection with RSL15 with the
 * 					  following pinout:
 *                          HDC_SCL <--> GPIO_11 (I2C_0 Clock)
 *                          HDC_SDA <--> GPIO_12 (I2C_0 Data)
 *                          HDC_INT <--> GPIO_XX (GPIO Input / Interrupt)
 *
 * Author		    : Pierino Zindel
 * Creation Date	: October 06, 2022
 * Version			: 1.2.0
 * Last Rev. Date   : November 24, 2022
 ******************************************************************************
 */

#ifndef INC_HDC2080_H_
#define INC_HDC2080_H_


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <stdbool.h>
#include "i2c_driver.h"
#include "app.h"


/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/
// General
#define BITS_PER_BYTE			(8)
#ifndef MICRO_DELAY											// microseconds delay function
 #define MICRO_DELAY(x)			Sys_Delay(((x * SystemCoreClock) / 1000000))
#endif

// I2C configuration
#define RSL15_SLAVE_ADDRESS		(5)
/* Supported I2C_SPEED options:
 *  ARM_I2C_BUS_SPEED_STANDARD  = 100kHz
 *  ARM_I2C_BUS_SPEED_FAST      = 400kHz
 *  ARM_I2C_BUS_SPEED_FAST_PLUS = 1MHz */
#define I2C_SPEED				ARM_I2C_BUS_SPEED_STANDARD

// HDC2080 ADC & conversion macros
#define ADC_RESOLUTION			(0xFFFF)
#define TEMPERATURE_SCALING		(165.0)
#define TEMPERATURE_OFFSET		(-40.5)
#define HUMIDITY_SCALING		(100.0)
#define HUMIDITY_OFFSET			(0.0)

// HDC2080 slave address (7-bit)
#define HDC_ADDRESS				(0x40)

#define HDC_WRITE_BYTE			(DEVICE_ADDRESS << 1 | 0x00)
#define HDC_READ_BYTE			(DEVICE_ADDRESS << 1 | 0x01)

// HDC2080 register addresses (i.e. command)
#define TEMPERATURE_LOW			(0x00)
#define TEMPERATURE_HIGH		(0x01)
#define HUMIDITY_LOW			(0x02)
#define HUMIDITY_HIGH			(0x03)
#define INTERRUPT_STATUS		(0x04)
#define TEMPERATUER_MAX			(0x05)
#define HUMIDITY_MAX			(0x06)
#define INTERRUPT_ENABLE		(0x07)
#define TEMP_OFFSET_ADJUST		(0x08)
#define HUM_OFFSET_ADJUST		(0x09)
#define TEMP_THR_L				(0x0A)
#define TEMP_THR_H				(0x0B)
#define RH_THR_L				(0x0C)
#define RH_THR_H				(0x0D)
#define INTERRUPT_CONFIG		(0x0E)
#define MEASURE_CONFIG			(0x0F)
#define MANUFACT_ID_LOW			(0xFC)
#define MANUFACT_ID_HIGH		(0xFD)
#define DEVICE_ID_LOW			(0xFE)
#define DEVICE_ID_HIGH			(0xFF)


/* ----------------------------------------------------------------------------
 * Register maps
 * --------------------------------------------------------------------------*/
// Interrupt / DRDY Status Register
//  ==> register address == 0x04 == INTERRUPT_STATUS
#define HDC_IS_HTHL_Pos			(3U)
#define HDC_IS_HTHL_Msk			(0x1U << HDC_IS_HTHL_Pos)	// 0x08
#define HDC_IS_HTHL				HDC_IS_HTHL_Msk				// Humidity threshold LOW interrupt status
#define HDC_IS_HTHH_Pos			(4U)
#define HDC_IS_HTHH_Msk			(0x1U << HDC_IS_HTHH_Pos)	// 0x10
#define HDC_IS_HTHH				HDC_IS_HTHH_Msk				// Humidity threshold HIGH interrupt status
#define HDC_IS_TTHL_Pos			(5U)
#define HDC_IS_TTHL_Msk			(0x1U << HDC_IS_TTHL_Pos)	// 0x20
#define HDC_IS_TTHL				HDC_IS_TTHL_Msk				// Temperature threshold LOW interrupt status
#define HDC_IS_TTHH_Pos			(6U)
#define HDC_IS_TTHH_Msk			(0x1U << HDC_IS_TTHH_Pos)	// 0x40
#define HDC_IS_TTHH				HDC_IS_TTHH_Msk				// Temperature threshold HIGH interrupt status
#define HDC_IS_DRDY_Pos			(7U)
#define HDC_IS_DRDY_Msk			(0x1U << HDC_IS_DRDY_Pos)	// 0x80
#define HDC_IS_DRDY				HDC_IS_DRDY_Msk				// DataReady bit status

// Interrupt Enable Register
//  ==> register address == 0x07 == INTERRUPT_ENABLE
#define HDC_IE_HTHL_EN_Pos		(3U)
#define HDC_IE_HTHL_EN_Msk		(0x1U << HDC_IE_HTHL_EN_Pos)	// 0x08
#define HDC_IE_HTHL_EN			HDC_IE_HTHL_EN_Msk				// Humidity threshold LOW interrupt enable
#define HDC_IE_HTHH_EN_Pos		(4U)
#define HDC_IE_HTHH_EN_Msk		(0x1U << HDC_IE_HTHH_EN_Pos)	// 0x10
#define HDC_IE_HTHH_EN			HDC_IE_HTHH_EN_Msk				// Humidity threshold HIGH interrupt enable
#define HDC_IE_TTHL_EN_Pos		(5U)
#define HDC_IE_TTHL_EN_Msk		(0x1U << HDC_IE_TTHL_EN_Pos)	// 0x20
#define HDC_IE_TTHL_EN			HDC_IE_TTHL_EN_Msk				// Temperature threshold LOW interrupt enable
#define HDC_IE_TTHH_EN_Pos		(6U)
#define HDC_IE_TTHH_EN_Msk		(0x1U << HDC_IE_TTHH_EN_Pos)	// 0x40
#define HDC_IE_TTHH_EN			HDC_IE_TTHH_EN_Msk				// Temperature threshold HIGH interrupt enable
#define HDC_IE_DRDY_EN_Pos		(7U)
#define HDC_IE_DRDY_EN_Msk		(0x1U << HDC_IE_DRDY_EN_Pos)	// 0x80
#define HDC_IE_DRDY_EN			HDC_IE_DRDY_EN_Msk				// DataReady interrupt enable

// Interrupt Configuration Register
//  ==> register address == 0x0E == INTERRUPT_CONFIG
#define HDC_IC_INT_MODE_Pos		(0U)
#define HDC_IC_INT_MODE_Msk		(0x1U << HDC_IC_INT_MODE_Pos)	// 0x01
#define HDC_IC_INT_MODE			HDC_IC_INT_MODE_Msk				// Interrupt mode (0=level sensitive; 1=comparator mode)
#define HDC_IC_INT_POL_Pos		(1U)
#define HDC_IC_INT_POL_Msk		(0x1U << HDC_IC_INT_POL_Pos)	// 0x02
#define HDC_IC_INT_POL			HDC_IC_INT_POL_Msk				// Interrupt polarity (0=active low; 1=active high)
#define HDC_IC_INT_EN_Pos		(2U)
#define HDC_IC_INT_EN_Msk		(0x1U << HDC_IC_INT_EN_Pos)	// 0x04
#define HDC_IC_INT_EN			HDC_IC_INT_EN_Msk				// DRDY / INT_EN pin configuration (0=high Z; 1=enable)
#define HDC_IC_HEAT_EN_Pos		(3U)
#define HDC_IC_HEAT_EN_Msk		(0x1U << HDC_IC_HEAT_EN_Pos)	// 0x08
#define HDC_IC_HEAT_EN			HDC_IC_HEAT_EN_Msk				// Heater enable (0=off; 1=on)
/* AMM Description (sampling frequency)
 *  000 == disabled (measurement manual triggering)
 *  001 == (1/120) Hz
 *  010 == (1/60) Hz
 *  011 == (1/10) Hz
 *  100 == (1/5) Hz
 *  101 == 1 Hz
 *  110 == 2 Hz
 *  111 == 5 Hz */
#define HDC_IC_AMM_Pos			(4U)
#define HDC_IC_AMM_Msk			(0x7U << HDC_IC_AMM_Pos)		// 0x70
#define HDC_IC_AMM				HDC_IC_AMM_Msk					// Auto Measurement Mode (AMM[2:0]) bits
#define HDC_IC_AMM_0			(0x1U << HDC_IC_AMM_Pos)		// 0x10
#define HDC_IC_AMM_1			(0x2U << HDC_IC_AMM_Pos)		// 0x20
#define HDC_IC_AMM_2			(0x4U << HDC_IC_AMM_Pos)		// 0x40
#define HDC_IC_SOFT_RES_Pos		(7U)
#define HDC_IC_SOFT_RES_Msk		(0x1U << HDC_IC_SOFT_RES_Pos)	// 0x80
#define HDC_IC_SOFT_RES			HDC_IC_SOFT_RES_Msk				// Soft reset (0=normal operation; 1=soft reset)

// Measurement Configuration Register
//  ==> register address == 0x0F == MEASURE_CONFIG
#define HDC_MC_TRIG_Pos			(0U)
#define HDC_MC_TRIG_Msk			(0x1U << HDC_MC_TRIG_Pos)		// 0x01
#define HDC_MC_TRIG				HDC_MC_TRIG_Msk					// Measurement trigger (0=no action; 1=start measurement)
#define HDC_MC_CONFIG_Pos		(1U)
#define HDC_MC_CONFIG_Msk		(0x1U << HDC_MC_CONFIG_Pos)	// 0x02
#define HDC_MC_CONFIG			HDC_MC_CONFIG_Msk				// Measurement configuration (0=hum & temp; 1=temp only)
/* HRES Description (ADC resolution)
 *  00 == 14 bit
 *  01 == 11 bit
 *  10 == 9 bit
 *  11 == N/A */
#define HDC_MC_HRES_Pos			(4U)
#define HDC_MC_HRES_Msk			(0x3U << HDC_MC_HRES_Pos)		// 0x30
#define HDC_MC_HRES				HDC_MC_HRES_Msk					// Humidity resolution
#define HDC_MC_HRES_0			(0x1U << HDC_MC_HRES_Pos)		// 0x10
#define HDC_MC_HRES_1			(0x2U << HDC_MC_HRES_Pos)		// 0x20
/* TRES Description (ADC resolution)
 *  00 == 14 bit
 *  01 == 11 bit
 *  10 == 9 bit
 *  11 == N/A */
#define HDC_MC_TRES_Pos			(6U)
#define HDC_MC_TRES_Msk			(0x3U << HDC_MC_TRES_Pos)		// 0xC0
#define HDC_MC_TRES				HDC_MC_TRES_Msk					// Temperature resolution
#define HDC_MC_TRES_0			(0x1U << HDC_MC_TRES_Pos)		// 0x40
#define HDC_MC_TRES_1			(0x2U << HDC_MC_TRES_Pos)		// 0x80


/* ----------------------------------------------------------------------------
 * Global variables
 * --------------------------------------------------------------------------*/
// Import the handler for the I2C connection
extern ARM_DRIVER_I2C Driver_I2C0;
extern ARM_DRIVER_I2C *i2c;


/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/

/* Function      : adc_to_humidity
 *
 * Description   : Returns a relative humidity value (between 0% and 100%)
 * 				   converted from the 16-bit ADC output.
 *
 * Parameters    : uint16_t data : The 16-bit ADC value.
 *
 * Returns		 : float : The relative humidity (0-100%).
 */
float adc_to_humidity(uint16_t data);

/* Function      : adc_to_temperature
 *
 * Description   : Returns a temperature value (between -40.5 and 124.5
 * 				   Celsius) converted from the 16-bit ADC output.
 *
 * Parameters    : uint16_t data : The 16-bit ADC value.
 *
 * Returns		 : float : The temperature output.
 */
float adc_to_temperature(uint16_t data);

/* Function      : change_to_register
 *
 * Description   : Sends a command to the HDC2080 slave module to change the
 * 				   accessible register to the one provided.
 *
 * Parameters    : uint8_t reg : The register address to make accessible.
 *
 * Returns		 : None
 */
void change_to_register(uint8_t reg);

/* Function      : get_humidity
 *
 * Description   : Requests a humidity ADC value from the HDC2080 slave module
 *                 and returns a relative humidity value (between 0% and 100%).
 *
 * Parameters    : None
 *
 * Returns       : float : The relative humidity (0-100%).
 */
float get_humidity(void);

/* Function      : get_raw_humidity
 *
 * Description   : Requests a humidity ADC value from the HDC2080 slave module
 * 				   and returns the raw 16-bit value from the registers.
 *
 * Parameters    : None
 *
 * Returns		 : uint16_t : The relative humidity in raw ADC output format.
 */
uint16_t get_raw_humidity(void);

/* Function      : get_temperature
 *
 * Description   : Requests a temperature ADC value from the HDC2080 slave
 * 				   module and returns a temperature value (between -40.5 and
 * 				   124.5 Celsius).
 *
 * Parameters    : None
 *
 * Returns		 : float : The temperature output.
 */
float get_temperature(void);

/* Function      : get_raw_temperature
 *
 * Description   : Requests a humidity ADC value from the HDC2080 slave module
 *                 and returns the raw 16-bit value from the registers.
 *
 * Parameters    : None
 *
 * Returns       : uint16_t : The temperature in raw ADC output format.
 */
uint16_t get_raw_temperature(void);

/* Function      : i2c_callback
 *
 * Description   : A callback registered to the I2C->Initialize function.
 * 				   Handles various callback events that can occur during
 * 				   the I2C driver operation.
 * 				   connection.
 *
 * Parameters    : uint32_t event : The ARM I2C event notification mask which
 * 									details under which event it was called.
 *
 * Returns		 : None
 */
void i2c_callback(uint32_t event);

/* Function      : initialize_hdc2080
 *
 * Description   : Configures the registers of the HDC2080 module (via I2C).
 * 				   The I2C connection must be initialized before the HDC2080
 * 				   can be initialized and configured.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void initialize_hdc2080(void);

/* Function      : initialize_i2c_connection
 *
 * Description   : Configures the I2C connection to the HDC2080 module.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void initialize_i2c_connection(void);

/* Function      : read_from_register
 *
 * Description   : Sends a command to the HDC2080 to trigger a measurement
 * 				   to be taken.
 *
 * Parameters    : None
 *
 * Returns		 : uint8_t : The value stored in the HDC2080's accessible
 *                           register.
 */
uint8_t read_from_register(void);

/* Function      : trigger_measurement
 *
 * Description   : Sends a command to the HDC2080 slave module to retrieve the
 * 				   value currently stored in the accessible register.
 * 				   This function requires the register pointer already be set
 * 				   (which can be done with the change_to_register() function).
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void trigger_measurement(void);

/* Function      : write_to_register
 *
 * Description   : Sends a command to the HDC2080 slave module to write a new
 * 				   byte of data to a given register.
 *
 * Parameters    : uint8_t reg  : The address of the register to update.
 *                 uint8_t data : The data to write to the register.
 *
 * Returns		 : None
 */
void write_to_register(uint8_t reg, uint8_t data);

#endif
