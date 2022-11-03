/**
 * @file app_temperature_sensor.c
 * @brief LSAD operational code
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

#include "app.h"

/* Array containing LSAD gain and offset values from TRIM sector */
static struct F_LSAD_TRIM g_f_lsad_gain_offset[1];

/* Default trim value sector. */
static TRIM_Type *trims = TRIM;

/* Temperature sensor scale */
static float g_tempsense_scale;

/* Temperature sensor offset */
static float g_tempsense_offset;

uint32_t measureTemperature(void)
{
    uint32_t lsad_value = 0;
    uint32_t mantissa = 0;
    uint32_t temperature;
    uint8_t exponent = EXPO_NEG_TWO;

    lsad_value = LSAD->DATA_TRIM_CH[TEMP_SENSOR_CHANNEL];

    mantissa = (uint32_t)((TTYP + ((lsad_value / g_tempsense_scale) - g_tempsense_offset)) * 100);

    temperature = ((exponent << 24 ) & 0xFF000000) |
    		((mantissa << 0) & 0x00FFFFFF);

    return temperature;
}

void Temperature_Offset_Init(uint32_t trim_error)
{
    /* Load trim/offset values from trim sector. */
    if (!(trim_error & ERROR_TEMPERATURE_INVALID))
    {
        /* Using low frequency trims, as we are at max pre-scale */
        Sys_LSAD_TempSensor_Gain_Offset(&(trims->temp_sensor), &g_f_lsad_gain_offset[TEMP_SENSOR_CHANNEL]);
    }

    /* tempsense_scale is typically 25.76/C.
     * Real value calculated here will vary from the typical. */
    if (trims->measured.temp_sensor_high == 0xFFFF || trims->measured.temp_sensor_30C == 0xFFFF)
    {
        /* Use typical tempsense value. */
        g_tempsense_scale = DEF_TEMPSENSE;
        g_tempsense_offset = DEF_TEMPOFFSET;
    }
    else
    {
        uint16_t temp_sensor_high = trims->measured.temp_sensor_high;
        uint16_t temp_sensor_30C  = trims->measured.temp_sensor_30C;
#ifdef RSL15_CID
        g_tempsense_scale = (float)(temp_sensor_high  - temp_sensor_30C) / 60.0f;
#else  /* ifdef RSL15_CID */
        g_tempsense_scale = (float)(temp_sensor_high  - temp_sensor_30C) / 20.0f;
#endif /* ifdef RSL15_CID */
        g_tempsense_offset = (temp_sensor_30C / g_tempsense_scale) - 30.0f;
	}
}

void Temperature_Sensor_Init(uint32_t trim_error)
{
    Temperature_Offset_Init(trim_error);

    Sys_LSAD_InputConfig(TEMP_SENSOR_CHANNEL,
                         LSAD_POS_INPUT_TEMP | LSAD_NEG_INPUT_GND,
                         -1, -1);

#if RSL15_CID == 202
    LSAD->CFG = LSAD_NORMAL               /* Normal mode, all 8 channels sampled */
                | LSAD_PRESCALE_1280H;    /* Sample rate is SLOWCLK/1280 */
#else
    LSAD->CFG = VBAT_DIV2_ENABLE          /* Enable VBAT voltage divider */
                | LSAD_NORMAL             /* Normal mode, all 8 channels sampled */
                | LSAD_PRESCALE_1280H;    /* Sample rate is SLOWCLK/1280 */
#endif

#ifdef RSL15_CID
    Sys_ACS_WriteRegister(&ACS->TEMP_SENSOR_CFG, LSAD_TEMP_SENS_NORMAL | TEMP_SENS_ENABLE);
#else    /* ifdef RSL15_CID */
    ACS->TEMP_SENSOR_CFG = LSAD_TEMP_SENS_NORMAL | TEMP_SENS_ENABLE;
#endif    /* ifdef RSL15_CID */
}
