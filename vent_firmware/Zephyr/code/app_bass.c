/**
 * @file app_bass.c
 * @brief BASS Application-specific source file
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

#include <app.h>
#include <app_bass.h>
#include <hw.h>
#include <swmTrace_api.h>
#include <ble_bass.h>

/* Global variable definitions */

/* Struct containing values needed for battery level calculation */
static struct app_batt_read_t app_batt_read;

/* Array containing LSAD gain and offset values from TRIM sector */
static struct F_LSAD_TRIM g_f_lsad_gain_offset[LSAD_CHANNEL_NUM];

/* Default trim value sector. */
static TRIM_Type *trims = TRIM;

/* ----------------------------------------------------------------------------
 * Function      : void APP_BASS_ReadBattLevel(uint8_t bas_nb)
 * ----------------------------------------------------------------------------
 * Description   : Calculate the current battery level by mapping the measured
 *                 voltage from [MIN_VOLTAGE_MV, MAX_VOLTAGE_MV] to [0, 100]
 * Inputs        : uint8_t bas_nb   - Battery instance. Note that the
 *                                    ble_peripheral_server sample code is
 *                                    only designed to work with one battery
 *                                    instance. bas_nb is a parameter to this
 *                                    function in order to match the
 *                                    parameters defined for the
 *                                    readBattLevelCallback function in the
 *                                    BLE abstraction layer.
 * Outputs       : An integer in the [0, 100] range.
 * Assumptions   : Return the same battery value for any bas_nb argument.
 * ------------------------------------------------------------------------- */

__attribute__((weak)) uint8_t APP_BASS_ReadBattLevel(uint8_t bas_nb)
{
    uint8_t batt_lvl_percent;
    uint32_t batt_lvl_mV;

    if (app_batt_read.read_cnt == LSAD_READS_NUM)
    {
        /* Average reads */
        batt_lvl_mV = (uint32_t)(app_batt_read.lsad_sum_mV / LSAD_READS_NUM);

        /* If batt_lvl_mV is less than MIN_VOLTAGE_MV then set bat_lvl_percent to 0, since
         * the value would overflow otherwise */
        if (batt_lvl_mV < MIN_VOLTAGE_MV)
        {
            batt_lvl_percent = 0;
        }
        else
        {
            /* Calculating bat_lvl_percent using average voltage measured. The
             * voltage is scaled from [MIN_VOLTAGE_MV, MAX_VOLTAGE_MV] to [0, 100] */
            batt_lvl_percent = (uint8_t)(((batt_lvl_mV - MIN_VOLTAGE_MV) * 100) /
                                         (MAX_VOLTAGE_MV - MIN_VOLTAGE_MV));

            /* If measured voltage is less than MIN_VOLTAGE_MV set bat_lvl_percent to 100 */
            batt_lvl_percent = (batt_lvl_percent <= 100) ? batt_lvl_percent : 100;
        }

        app_batt_read.prev_batt_lvl_percent = batt_lvl_percent;

        /* Set to 0 before next set of LSAD readings are taken in BattLevelReadHandler */
        app_batt_read.lsad_sum_mV = 0;

        /* Set to 0 to begin next set of LSAD readings in BattLevelReadHandler */
        app_batt_read.read_cnt = 0;
    }
    else
    {
        /* Return the last battery level calculated if a set of LSAD readings has not been
         * completed since the last time the function was called */
        batt_lvl_percent = app_batt_read.prev_batt_lvl_percent;
    }

    return batt_lvl_percent;
}

/* ----------------------------------------------------------------------------
 * Function      : void BattLevelReadHandler(ke_msg_id_t const msg_id,
 *                                           void const *param,
 *                                           ke_task_id_t const dest_id,
 *                                           ke_task_id_t const src_id)
 * ----------------------------------------------------------------------------
 * Description   : Handles APP_BATT_LEVEL_READ_TIMEOUT event
 * Inputs        : - msg_id     - Kernel message ID number
 *                 - param      - Message parameter
 *                 - dest_id    - Destination task ID number
 *                 - src_id     - Source task ID number
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */

void BattLevelReadHandler(ke_msg_id_t const msg_id,
                          void const *param,
                          ke_task_id_t const dest_id,
                          ke_task_id_t const src_id)
{
    struct F_LSAD_TRIM *gain_offset = &g_f_lsad_gain_offset[LSAD_VBAT_CHANNEL];
    float lsad_result = 0.0f;
    uint32_t voltage;

    /* Set timer to call BattLevelReadHandler to take another LSAD reading if needed */
    ke_timer_set(APP_BATT_LEVEL_READ_TIMEOUT,
                 TASK_APP,
                 TIMER_SETTING_MS(LSAD_READ_INTERVAL_MS));

    if (app_batt_read.read_cnt < LSAD_READS_NUM)
    {
        /* Calculating voltage using gain and offset and multiplying by 2 since
         * VBAT is divided by 2 when measured by the LSAD. */
        if (gain_offset->hf_gain != 0)
        {
            /* Computing LSAD result using the LSAD full scale of 2.0V and LSAD resolution
             * of 14 bits */
            lsad_result = CONVERT(LSAD->DATA_TRIM_CH[LSAD_VBAT_CHANNEL]) / V_TO_MV_F;

            /* Applying offset and gain compensation to calculated voltage value */
            voltage = (uint32_t)(((lsad_result - gain_offset->hf_offset) /
                                  gain_offset->hf_gain * V_TO_MV) * LSAD_VBAT_FACTOR);
        }

        /* Calculating voltage using only reference voltage and LSAD data if gain is 0 */
        else
        {
            voltage = ((LSAD_VOLTAGE_RANGE_MV * LSAD_VBAT_FACTOR *
                        LSAD->DATA_TRIM_CH[LSAD_VBAT_CHANNEL]) / (LSAD_MAX_SIZE));
        }

        app_batt_read.lsad_sum_mV += voltage;

        app_batt_read.read_cnt++;
    }
}

/* ----------------------------------------------------------------------------
 * Function      : void APP_BASS_ReadBattLevelInit(unit32_t trim_error)
 * ----------------------------------------------------------------------------
 * Description   : Initializes app_batt_read and g_f_lsad_gain_offset structs
 * Inputs        : - trim_error     - indicates if any trim related errors have
 *                                    occurred
 * Outputs       : None
 * Assumptions   : None
 * --------------------------------------------------------------------------- */

void APP_BASS_ReadBattLevelInit(uint32_t trim_error)
{
    if (!(trim_error & ERROR_LSAD_INVALID))
    {
        /* Using low frequency trims, as we are at max pre-scale */
        Sys_LSAD_Gain_Offset(&(trims->lsad_trim), &g_f_lsad_gain_offset[LSAD_VBAT_CHANNEL]);
    }

    app_batt_read.lsad_sum_mV = 0;
    app_batt_read.prev_batt_lvl_percent = 0;
    app_batt_read.read_cnt = 0;
}

/* ----------------------------------------------------------------------------
 * Function      : void LSAD_Channel_Init(unit32_t trim_error)
 * ----------------------------------------------------------------------------
 * Description   : Initializes LSAD input channels
 * Inputs        : - trim_error     - indicates if any trim related errors have
 *                                    occurred
 * Outputs       : None
 * Assumptions   : None
 * --------------------------------------------------------------------------- */

void LSAD_ChannelInit(uint32_t trim_error)
{
    APP_BASS_ReadBattLevelInit(trim_error);

    /* Disable the LSAD and connect all inputs to default values */
    LSAD->CFG = LSAD_DISABLE;

    /* Configure input channel 3 in single ended configuration by connecting
     * the LSAD negative input to ground, connect the positive input to VBAT. */
#if RSL15_CID == 202
    Sys_LSAD_InputConfig(LSAD_VBAT_CHANNEL,
                         LSAD_POS_INPUT_VBAT_DIV2 | LSAD_NEG_INPUT_GND,
                         -1, -1);
#else  /* if RSL15_CID == 202 */
    Sys_LSAD_InputConfig(LSAD_VBAT_CHANNEL,
                         LSAD_POS_INPUT_VBAT | LSAD_NEG_INPUT_GND,
                         -1, -1);
#endif /* if RSL15_CID == 202 */

    /* Configure input channel 7 on both ends to VBAT, to disable automatic offset
     * compensation. */
#if RSL15_CID == 202
    Sys_LSAD_InputConfig(LSAD_COMPENSATION_CHANNEL,
                         LSAD_POS_INPUT_VBAT_DIV2 | LSAD_NEG_INPUT_VBAT_DIV2,
                         -1, -1);
#else  /* if RSL15_CID == 202 */
    Sys_LSAD_InputConfig(LSAD_COMPENSATION_CHANNEL,
                         LSAD_POS_INPUT_VBAT | LSAD_NEG_INPUT_VBAT,
                         -1, -1);
#endif /* if RSL15_CID == 202 */

#if RSL15_CID == 202
    LSAD->CFG = LSAD_NORMAL               /* Normal mode, all 8 channels sampled */
                | LSAD_PRESCALE_1280H;    /* Sample rate is SLOWCLK/1280 */
#else  /* if RSL15_CID == 202 */
    LSAD->CFG = VBAT_DIV2_ENABLE          /* Enable VBAT voltage divider */
                | LSAD_NORMAL             /* Normal mode, all 8 channels sampled */
                | LSAD_PRESCALE_1280H;    /* Sample rate is SLOWCLK/1280 */
#endif /* if RSL15_CID == 202 */
}
