/**
 * @file ble_protocol_support.c
 * @brief Provide Bluetooth protocol related parameters
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

#include <ble_protocol_support.h>

#if APP_HEAP_SIZE_DEFINED
uint32_t rwip_heap_env[RWIP_CALC_HEAP_LEN(APP_RWIP_HEAP_ENV_SIZE)];

#if (BLE_HOST_PRESENT)

/** Memory allocated for Attribute database */
uint32_t rwip_heap_db[RWIP_CALC_HEAP_LEN(APP_RWIP_HEAP_DB_SIZE)];
#endif    /* (BLE_HOST_PRESENT) */

/** Memory allocated for kernel messages */
uint32_t rwip_heap_msg[RWIP_CALC_HEAP_LEN(APP_RWIP_HEAP_MSG_SIZE)];

/** Non Retention memory block */
uint32_t rwip_heap_non_ret[RWIP_CALC_HEAP_LEN(APP_RWIP_HEAP_NON_RET_SIZE)];
#else    /* if APP_HEAP_SIZE_DEFINED */
uint32_t rwip_heap_env[RWIP_CALC_HEAP_LEN(RWIP_HEAP_ENV_SIZE)];

#if (BLE_HOST_PRESENT)

/** Memory allocated for Attribute database */
uint32_t rwip_heap_db[RWIP_CALC_HEAP_LEN(RWIP_HEAP_DB_SIZE)];
#endif    /* (BLE_HOST_PRESENT) */

/** Memory allocated for kernel messages */
uint32_t rwip_heap_msg[RWIP_CALC_HEAP_LEN(RWIP_HEAP_MSG_SIZE)];

/** Non Retention memory block */
uint32_t rwip_heap_non_ret[RWIP_CALC_HEAP_LEN(RWIP_HEAP_NON_RET_SIZE)];
#endif    /* if APP_HEAP_SIZE_DEFINED */

/** BLE Public Address */
static uint8_t ble_public_addr[BD_ADDR_LEN];

void Device_BLE_Public_Address_Read(uint32_t ble_public_addr_loc)
{
    if (ble_public_addr_loc)
    {
        if (ble_public_addr_loc == FLASH0_MNVR_BASE)    /* Get BLE MAC address (6 Bytes) from MNVR */
        {
            uint32_t tempValue = 0;

            /* Read 32-bit from FLASH0_MNVR_BASE */
            Sys_Read_MNVR(FLASH0_MNVR_BASE, &tempValue);
            ble_public_addr[0] = tempValue;
            ble_public_addr[1] = (tempValue >> 8);
            ble_public_addr[2] = (tempValue >> 16);
            ble_public_addr[3] = (tempValue >> 24);

            /* Read 32-bit from FLASH0_MNVR_BASE+0x04 */
            Sys_Read_MNVR(FLASH0_MNVR_BASE + 0x04, &tempValue);
            ble_public_addr[4] = tempValue;
            ble_public_addr[5] = (tempValue >> 8);
        }
        else    /* Get BLE address from given location */
        {
            memcpy(ble_public_addr, (uint8_t *)ble_public_addr_loc, BD_ADDR_LEN);
        }
    }
}

uint8_t Device_BLE_Param_Get(uint8_t param_id, uint8_t *lengthPtr, uint8_t *buf)
{
    uint8_t status = PARAM_OK;
    uint32_t temp;
    struct channel_map_assess_tag *tempAssessPtr;

#if APP_SECURELE_KEYS_FORCED
    uint8_t tempPrivateKey[PARAM_LEN_PRIVATE_KEY_P256] = APP_PRIVATE_KEY;
    uint8_t tempPublicKey[PARAM_LEN_PUBLIC_KEY_P256] = APP_PUBLIC_KEY;
#endif    /* if APP_SECURELE_KEYS_FORCED */

#if APP_HEAP_SIZE_DEFINED
    uint16_t tempSizes[4] = {
        APP_RWIP_HEAP_ENV_SIZE, APP_RWIP_HEAP_DB_SIZE, APP_RWIP_HEAP_MSG_SIZE, APP_RWIP_HEAP_NON_RET_SIZE
    };
#endif    /* if APP_HEAP_SIZE_DEFINED */

#ifdef CFG_PLF_UART
#if (RF_TESTER_GENERATES_PATTERN == 0)
    uint8_t antennaIdToPattern[4] = DTM_ANTENNA_ID_TO_PATTERN;
#endif
#endif    /* ifdef CFG_PLF_UART */

    switch (param_id)
    {
        case PARAM_ID_BD_ADDRESS:
        {
            memcpy(buf, ble_public_addr, *lengthPtr);
        }
        break;

        case PARAM_ID_LPCLK_DRIFT:
        {
            temp = ble_dev_params.low_pwr_clk_accuracy;
            memcpy(buf, (uint8_t *)&temp, *lengthPtr);
        }
        break;

        case PARAM_ID_ACTCLK_DRIFT:
        {
            temp = RADIO_CLOCK_ACCURACY;
            memcpy(buf, (uint8_t *)&temp, *lengthPtr);
        }
        break;

        case PARAM_ID_OSC_WAKEUP_TIME:
        {
            temp = ble_dev_params.twosc;
            memcpy(buf, (uint8_t *)&temp, *lengthPtr);
        }
        break;

        case PARAM_ID_CH_ASS_EN:
        {
            buf[0] = true;
        }
        break;

        case PARAM_ID_LPCLK_NO_XTAL32K:
        {
            if (ble_dev_params.low_pwr_clk.low_pwr_standby_clk_src ==
                    ble_dev_params.low_pwr_clk.low_pwr_clk_xtal32) /* Low power standby clock source is XTAL32 */
            {
                buf[0] = false;
            }
            else
            {
                buf[0] = true;
                LPCLK_PeriodValue_Set(LPCLK_PERIOD_VALUE);
            }
        }
        break;

#if APP_SECURELE_KEYS_FORCED
        case PARAM_ID_LE_PRIVATE_KEY_P256:
        {
            memcpy(buf, tempPrivateKey, *lengthPtr);
        }
        break;

        case PARAM_ID_LE_PUBLIC_KEY_P256:
        {
            memcpy(buf, tempPublicKey, *lengthPtr);
        }
        break;

        case PARAM_ID_LE_DBG_FIXED_P256_KEY:
        {
            temp = true;
            memcpy(buf, (uint8_t *)&temp, *lengthPtr);
        }
        break;
#endif    /* if APP_SECURELE_KEYS_FORCED */

        case PARAM_ID_CH_ASSESS_PARAMS:
        {
            tempAssessPtr = (struct channel_map_assess_tag *)buf;
            tempAssessPtr->rssi_interf_thr = BLE_CH_ASSESS_RSSI_INTERF_THR;
            tempAssessPtr->assess_valid_timer = BLE_CH_ASSESS_VALID_TO;
            tempAssessPtr->Reassess_timer = BLE_CH_REASSESS_TO;
            tempAssessPtr->assess_count_max = BLE_CH_ASSESS_COUNT_MAX;
            tempAssessPtr->assess_count_min = BLE_CH_ASSESS_COUNT_MIN;
            tempAssessPtr->assess_count_thr_bad = BLE_CH_ASSESS_COUNT_THR_BAD;
            tempAssessPtr->channel_map_update_period = BLE_CH_MAP_UPDATE_PERIOD;
        }
        break;

#ifdef CFG_PLF_UART
        case PARAM_ID_DTM_ANT_ID_TO_PTRN_PARAMS:
        {
        #if RF_TESTER_GENERATES_PATTERN
            status = PARAM_FAIL;
        #else    /* if RF_TESTER_GENERATES_PATTERN */
            memcpy(buf, (uint8_t *)&antennaIdToPattern, *lengthPtr);
        #endif    /* if RF_TESTER_GENERATES_PATTERN */
        }
        break;
#endif    /* ifdef CFG_PLF_UART */

#if APP_HEAP_SIZE_DEFINED
        case PARAM_ID_CUSTOMIZED_HEAP_SIZE:
        {
            temp = true;
            memcpy(buf, (uint8_t *)&tempSizes, *lengthPtr);
            break;
        }
#endif    /* if APP_HEAP_SIZE_DEFINED */

        case PARAM_ID_DFT_SLAVE_MD:
        {
            buf[0] = true;
        }
        break;

        case PARAM_ID_ACTIVITY_MOVE_CONFIG:
        {
            buf[0] = true;
        }
        break;

        default:
        {
            status = PARAM_FAIL;
        }
        break;
    }

    return (status);
}

void platform_reset(uint32_t error)
{
    NVIC_SystemReset();
}

void srand_func(uint32_t seed)
{
#if (APP_BLE_RAND_SEED_DEFINED != 0)
    /* Application can provide its own seed to
     * rand() function used in BLE stack */
    uint32_t app_seed_value;
    memcpy((uint8_t *)&app_seed_value, app_seed_value, sizeof(uint32_t));    /*TODO */
#endif    /* if (APP_BLE_RAND_SEED_DEFINED != 0) */
    srand(seed);
}

int rand_func(void)
{
#if (APP_BLE_RAND_GENERATE_DEFINED != 0)
    /* Application can generate and provide a 32-bit random number
     * instead of BLE stack random value */
    return 0x12345678;    /*TODO */
#else    /* if (APP_BLE_RAND_GENERATE_DEFINED != 0) */
    return rand();
#endif    /* if (APP_BLE_RAND_GENERATE_DEFINED != 0) */
}

int8_t Device_RF_TxPwr_Get_dBm(uint8_t txpwr_idx)
{
#ifndef NON_SECURE
    int32_t vddpa = 0;
    float currentTXPower = -100.0f;    /* Set default reading to an invalid value */
    TRIM_Type *trims = TRIM;
    float temp = 0.0f;
    uint16_t trim_val;                    

    if ((SYSCTRL->VDDPA_CFG0 & DYNAMIC_CTRL_ENABLE_BYTE) ||
        ((ACS->VDDPA_CTRL & VDDPA_ENABLE) && (!(ACS->VDDPA_CTRL & VDDPA_SW_VDDRF))))
    {
        /* VDDPA is enabled, calculate output power accordingly. */
        /* Cannot measure VDDPA accurately, since dynamic VDDPA is enabled*/
        /* Use trims to determine approximate VDDPA voltage */
        /* 10mV per trim setting */
        trim_val= trims->vddpa[2].trim_voltage;
        vddpa = (TARGET_VDDPA_1600 * 10) +
                ((ACS_VDDPA_CTRL->VTRIM_BYTE - trim_val) * 10);

        /* Calculate current set power, using VDDPA measurement and current
         * register setting. */
        currentTXPower = (RF_MAX_POWER -
                          (((PA_PWR_BYTE_0DBM - txpwr_idx) * 3.0f) / 2.0f));
        temp = ((float)(vddpa) - (TARGET_VDDPA_1600 * 10.0f));
        currentTXPower += temp / (float)(MV_PER_DBM_VDDPA);
    }
    else
    {
        /* Calculate current set power, using VDDRF measurement and current
         * register setting. */
        currentTXPower = (RF_NO_VDDPA_TYPICAL_POWER -
                          (((PA_PWR_BYTE_0DBM - txpwr_idx) * 3.0f) / 2.0f));
        trim_val= trims->vddrf[0].trim;
        temp = ((float)(ACS_VDDRF_CTRL->VTRIM_BYTE - trim_val) * 10.0f);
        currentTXPower += temp / (float)(MV_PER_DBM_VDDRF);
    }

    /* Round value */
    if (currentTXPower > 0)
    {
        currentTXPower += 0.5f;
    }
    else if (currentTXPower < 0)
    {
        currentTXPower -= 0.5f;
    }

    return (int8_t)(currentTXPower);
#else    /* ifndef NON_SECURE */
    return ERRNO_RFFE_INVALIDSETTING_ERROR;
#endif    /* ifndef NON_SECURE */
}

uint8_t Device_RF_TxPwr_Get_Idx(int8_t txpwr_dbm)
{
    uint8_t idx = 0;

    if (!(txpwr_dbm % 3))
    {
        if ((SYSCTRL->VDDPA_CFG0 & DYNAMIC_CTRL_ENABLE_BYTE) ||
            ((ACS->VDDPA_CTRL & VDDPA_ENABLE) && (!(ACS->VDDPA_CTRL & VDDPA_SW_VDDRF))) ||
            (txpwr_dbm > 2))
        {
            /* Requested TX power is an even multiple of 3.
             * VDDPA is enabled */
            idx = (int8_t)(PA_PWR_BYTE_0DBM) - ((((int8_t)(RF_MAX_POWER) - txpwr_dbm) * 2) / 3);
        }
        else
        {
            /* Requested TX power is an even multiple of 3.
             * VDDPA is disabled */
            idx = (int8_t)(PA_PWR_BYTE_0DBM) - ((((int8_t)(RF_NO_VDDPA_TYPICAL_POWER) - txpwr_dbm) * 2) / 3);
        }
    }
    else
    {
        /* Requested TX power is not an even multiple of 3. */
        if ((SYSCTRL->VDDPA_CFG0 & DYNAMIC_CTRL_ENABLE_BYTE) ||
            ((ACS->VDDPA_CTRL & VDDPA_ENABLE) && (!(ACS->VDDPA_CTRL & VDDPA_SW_VDDRF))) ||
            (txpwr_dbm > 2))
        {
            idx = (int8_t)(PA_PWR_BYTE_0DBM) + (((((txpwr_dbm) - RF_MAX_POWER) * 2) / 3));
        }
        else if ((!(SYSCTRL->VDDPA_CFG0 & DYNAMIC_CTRL_ENABLE_BYTE) ||
                  ((ACS->VDDPA_CTRL & VDDPA_ENABLE) && (!(ACS->VDDPA_CTRL & VDDPA_SW_VDDRF)))) && txpwr_dbm > 0)
        {
            /* VDDPA is not enabled, tx pwr over 0. */
            idx = PA_PWR_BYTE_0DBM;
        }
        else
        {
            /* TX power below 0 */
            int8_t upper_trim = (txpwr_dbm * 2) + 1;
            int8_t lower_trim = (txpwr_dbm * 2) - 1;

            if (!(upper_trim % 3))
            {
                /* trim above target divides evenly */
                idx = (int8_t)(PA_PWR_BYTE_0DBM) + (upper_trim / 3);
            }
            else if (!(lower_trim % 3))
            {
                /* trim below target divides evenly */
                idx = (int8_t)(PA_PWR_BYTE_0DBM) + (lower_trim / 3);
            }
            else
            {
                /* Target divides by 1.5 evenly. */
                idx = PA_PWR_BYTE_0DBM + (((txpwr_dbm) * 2) / 3);
            }
        }
    }
    return idx;
}

int8_t Device_RF_RSSI_Convert(uint8_t rssi_reg)
{
    /*TODO */
    return (int8_t)(((0.29 * rssi_reg) - 107));
}

uint8_t Device_RF_SetMaxPwrIdx(void)
{
    return(Device_RF_TxPwr_Get_Idx(ble_dev_params.rf_tx_power_dbm));
}
