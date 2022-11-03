/**
 * @file app_bass.h
 * @brief Bluetooth battery service header
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

#ifndef APP_BASS_H
#define APP_BASS_H

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

#include <stdint.h>
#include <ke_msg.h>

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/

#define CONCAT(x, y)                     x##y
#define BATMON_CH(x)                     CONCAT(BATMON_CH, x)

/* Note:
 *   The ble_peripheral_server sample code is only designed to work with APP_BAS_NB
 *   set to 1. */
#define APP_BAS_NB                       1    /* Number of batteries */
#define BATT_LEVEL_LOW_THRESHOLD_PERCENT 15    /* Battery level low at 15% of 1.1V to 1.4V range */

/* LSAD, VBAT and BATMON alarm configuration */
#define BATMON_ALARM_COUNT_CFG           1U

/* Maximum and minimum voltage values used as a reference in order to calculate
 * battery level percent */
#define MAX_VOLTAGE_MV                   3000
#define MIN_VOLTAGE_MV                   1800

/* VBAT LSAD Channel */
#define LSAD_VBAT_CHANNEL                3

/* Factor that VBAT is divided by */
#define LSAD_VBAT_FACTOR                 2

/* Compensation LSAD Channel */
#define LSAD_COMPENSATION_CHANNEL        7

/* Since the LSAD output code is 14 bits, the LSAD output maximum size is 2^14 */
#define LSAD_MAX_SIZE                    0x4000

#define LSAD_VOLTAGE_RANGE_MV            2000

#define LSAD_READS_NUM                   16

/* Sample rate is SLOWCLK/1280 (97.65625 Hz per channel), where SLOWCLK = 1MHz
 * so the value must be above 81.92 milliseconds in order to allow enough time
 * for all 8 channels to be sampled */
#define LSAD_READ_INTERVAL_MS            100

#define LSAD_CHANNEL_NUM                 8

/* Interval for timer that calls BattLevelReadHandler the first time */
#define BEGIN_TIMER_S     1

/* Time interval to check for battery level changes and notify if necessary.
 * BASS_NotifyOnBattLevelChange uses this value to set a kernel timer for
 * the BASS_BATT_MONITORING_TIMEOUT event, which checks if the battery level
 * has changed and if yes, sends a battery level update request.
 * Should be greater than LSAD_READ_INTERVAL_MS / 1000 * LSAD_READS_NUM  */
#define BATT_CHANGE_TIMEOUT_S            5

/* Time interval to notify battery level. BASS_NotifyOnTimeout uses this value
 * to set a kernel timer for the BASS_BATT_LEVEL_NTF_TIMEOUT event, which
 * sends a battery level update request regardless of whether the previous
 * battery level was the same.
 * Should be greater than BATT_CHANGE_TIMEOUT_S */
#define BATT_UPDATE_TIMEOUT_S            15

#define LSAD_BATMON_CH                    6
#define LSAD_GND_CH                       0

void APP_BASS_SetBatMonAlarm(uint32_t supplyThresholdCfg);

uint8_t APP_BASS_ReadBattLevel(uint8_t bas_nb);

void BattLevelReadHandler(ke_msg_id_t const msg_id,
                          void const *param,
                          ke_task_id_t const dest_id,
                          ke_task_id_t const src_id);

void APP_BASS_BattLevelLow_Handler(ke_msg_id_t const msg_id,
                                   void const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id);

void APP_BASS_ReadBattLevelInit(uint32_t trim_error);

void LSAD_ChannelInit(uint32_t trim_error);

extern void LSAD_BATMON_IRQHandler(void);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */

struct app_batt_read_t
{
    uint32_t lsad_sum_mV;
    uint8_t prev_batt_lvl_percent;
    uint8_t read_cnt;
};

#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_H */
