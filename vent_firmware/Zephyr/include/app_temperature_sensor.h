/**
 * @file app_temperature_sensor.h
 * @brief Application temperature sensor header file
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
#ifndef APP_TEMPERATURE_SENSOR_H_
#define APP_TEMPERATURE_SENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* Temperature sensor LSAD channel */
#define TEMP_SENSOR_CHANNEL             0

/* Typical temperature */
#define TTYP                            25.0f

#define DEF_TEMPSENSE                   19.8f    /* LSB/Degrees Celsius. */

/* Default temperature sensor offset */
#define DEF_TEMPOFFSET                  387.0f

/* Default exponential value for IEEE-11073 encoding */
#define EXPO_NEG_TWO                    0xFE

/**
 * @brief Returns the IEEE-11073 32-bit temperature value, defined as a
 * 32-bit value with a 8-bit exponent and a 24-bit mantissa
 */
uint32_t measureTemperature(void);

/**
 * @brief Configure temperature input channels and start conversion
 * @param [in] trim_error indicates if any trim related errors have occurred.
 */
void Temperature_Sensor_Init(uint32_t trim_error);

/**
 * @brief Initialize non hardware related parameters
 * @param [in] trim_error indicates if any trim related errors have occurred.
 */
void Temperature_Offset_Init(uint32_t trim_error);

#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_TEMPERATURE_SENSOR_H_ */
