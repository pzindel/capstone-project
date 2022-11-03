/**
 * @file app_init.c
 * @brief Application initialization source file
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

#include <app.h>
#include "ble_bass.h"

#if SWMTRACE_ENABLE
static uint32_t traceOptions[] = {
    SWM_LOG_LEVEL_INFO,                  /* In all cases log info messages */
    SWM_UART_RX_PIN | UART_RX_GPIO,      /* Set RX pin for cases when using UART */
    SWM_UART_TX_PIN | UART_TX_GPIO,      /* Set TX pin for cases when using UART */
    SWM_UART_RX_ENABLE,                  /* Enable the UART Rx Interrupts */
    SWM_UART_BAUD_RATE | UART_BAUD       /* Set Baud rate */
};
#endif /* if SWMTRACE_ENABLE */

/* Device Information structure initialization, includes length and data string */
const struct DISS_DeviceInfo_t deviceInfo =
{
    .MANUFACTURER_NAME  = {.len = APP_DIS_MANUFACTURER_NAME_LEN, .data = (uint8_t*) APP_DIS_MANUFACTURER_NAME},
    .MODEL_NB_STR       = {.len = APP_DIS_MODEL_NB_STR_LEN, .data = (uint8_t*) APP_DIS_MODEL_NB_STR},
    .SERIAL_NB_STR      = {.len = APP_DIS_SERIAL_NB_STR_LEN, .data = (uint8_t*) APP_DIS_SERIAL_NB_STR},
    .FIRM_REV_STR       = {.len = APP_DIS_FIRM_REV_STR_LEN, .data = (uint8_t*) APP_DIS_FIRM_REV_STR},
    .SYSTEM_ID          = {.len = APP_DIS_SYSTEM_ID_LEN, .data = (uint8_t*) APP_DIS_SYSTEM_ID},
    .HARD_REV_STR       = {.len = APP_DIS_HARD_REV_STR_LEN, .data = (uint8_t*) APP_DIS_HARD_REV_STR},
    .SW_REV_STR         = {.len = APP_DIS_SW_REV_STR_LEN, .data = (uint8_t*) APP_DIS_SW_REV_STR},
    .IEEE               = {.len = APP_DIS_IEEE_LEN, .data = (uint8_t*) APP_DIS_IEEE},
    .PNP                = {.len = APP_DIS_PNP_ID_LEN, .data = (uint8_t*) APP_DIS_PNP_ID},
};

void DeviceInit(void)
{
    /* Disable all existing interrupts, clearing all pending source */
    Sys_NVIC_DisableAllInt();
    Sys_NVIC_ClearAllPendingInt();

	/* Debug Catch Mode
	 * If DEBUG_CATCH_GPIO is low, enter Debug Catch Mode which holds the program execution in a
	 * while loop to make it easier to connect to the debugger.
	 * We suggest retaining this feature during development.
	 */
    SYS_GPIO_CONFIG(DEBUG_CATCH_GPIO, (GPIO_MODE_GPIO_IN | GPIO_LPF_DISABLE |
                                       GPIO_WEAK_PULL_UP  | GPIO_6X_DRIVE));

    while ((Sys_GPIO_Read(DEBUG_CATCH_GPIO)) == 0)
    {
        SYS_WATCHDOG_REFRESH();
    }

    /* Disable JTAG TDI, TDO, and TRST connections to GPIO 2, 3, and 4 */
    GPIO->JTAG_SW_PAD_CFG &= ~(CM33_JTAG_DATA_ENABLED | CM33_JTAG_TRST_ENABLED);

    SYS_GPIO_CONFIG(LED_STATE_GPIO, GPIO_MODE_GPIO_OUT);
    SYS_GPIO_CONFIG(CONNECTION_STATE_GPIO, GPIO_MODE_GPIO_OUT);
    Sys_GPIO_IntConfig(0, GPIO_EVENT_TRANSITION | GPIO_SRC(BUTTON_GPIO) |
    GPIO_DEBOUNCE_ENABLE, GPIO_DEBOUNCE_SLOWCLK_DIV1024, 49);

    /* Turn LED_STATE_GPIO off */
    Sys_GPIO_Set_High(LED_STATE_GPIO);

    /* Load default trim values */
    uint32_t trim_error = SYS_TRIM_LOAD_DEFAULT();

    /* Start 48 MHz XTAL oscillator */
    Sys_Clocks_XTALClkConfig(CK_DIV_1_6_PRESCALE_6_BYTE);

    /* Switch to (divided 48 MHz) oscillator clock, and update the
     * SystemCoreClock global variable */
    Sys_Clocks_SystemClkConfig(SYSCLK_CLKSRC_RFCLK);

    /* Enable/disable buck converter */
    Sys_ACS_WriteRegister(&ACS->VCC_CTRL, ((ACS->VCC_CTRL & ~VCC_BUCK) | VCC_BUCK_LDO_CTRL));

    /* Load custom trim values */
    uint32_t custom_trim_error __attribute__((unused)) = SYS_TRIM_LOAD_CUSTOM();

    /* Configure clock dividers */
    Sys_Clocks_DividerConfig(UART_CLK, SENSOR_CLK, USER_CLK);

    /* Initialize clock and access to flash */
    Flash_Initialize(0, (FlashClockFrequency_t)(SystemCoreClock));

    /* Configuring temperature sensor */
    Temperature_Sensor_Init(trim_error);

    /* Configuring LSAD input channels */
    LSAD_ChannelInit(trim_error);
}

void SWMTraceInit(void)
{
#if SWMTRACE_ENABLE
    swmTrace_init(traceOptions, 5);
#endif /* if SWMTRACE_ENABLE */
}

void BLESystemInit(void)
{
    /* Set ICH_TRIM for optimum RF performance */
	Sys_ACS_WriteRegister(&ACS->VCC_CTRL, (((ACS->VCC_CTRL) & (~(ACS_VCC_CTRL_ICH_TRIM_Mask))) |
            ((uint32_t)(0x5U << ACS_VCC_CTRL_ICH_TRIM_Pos))));

    /* Set TX power */
    Sys_RFFE_SetTXPower(DEF_TX_POWER, LSAD_TXPWR_DEF, VDDPA_EN);

    /* Configure Baseband Controller Interface */
    BBIF->CTRL = (BB_CLK_ENABLE | BBCLK_DIVIDER_8);

    /* Initialize BLE stack */
    BLEStackInit();
}

void EnableBLEInterrupts(void)
{
    NVIC_ClearPendingIRQ(BLE_HSLOT_IRQn);
    NVIC_ClearPendingIRQ(BLE_SLP_IRQn);
    NVIC_ClearPendingIRQ(BLE_FIFO_IRQn);
    NVIC_ClearPendingIRQ(BLE_CRYPT_IRQn);
    NVIC_ClearPendingIRQ(BLE_ERROR_IRQn);
    NVIC_ClearPendingIRQ(BLE_TIMESTAMP_TGT1_IRQn);
    NVIC_ClearPendingIRQ(BLE_FINETGT_IRQn);
    NVIC_ClearPendingIRQ(BLE_TIMESTAMP_TGT2_IRQn);
    NVIC_ClearPendingIRQ(BLE_SW_IRQn);

    NVIC_EnableIRQ(BLE_HSLOT_IRQn);
    NVIC_EnableIRQ(BLE_SLP_IRQn);
    NVIC_EnableIRQ(BLE_FIFO_IRQn);
    NVIC_EnableIRQ(BLE_CRYPT_IRQn);
    NVIC_EnableIRQ(BLE_ERROR_IRQn);
    NVIC_EnableIRQ(BLE_TIMESTAMP_TGT1_IRQn);
    NVIC_EnableIRQ(BLE_FINETGT_IRQn);
    NVIC_EnableIRQ(BLE_TIMESTAMP_TGT2_IRQn);
    NVIC_EnableIRQ(BLE_SW_IRQn);
}

void EnableAppInterrupts(void)
{
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
    NVIC_EnableIRQ(GPIO0_IRQn);
}

void IRQPriorityInit(void)
{
	IRQn_Type interrupt;

	/* Iterate through all external interrupts excluding WAKEUP_IRQn */
	for (interrupt = RTC_ALARM_IRQn; interrupt <= NVIC_LAST_VECTOR; ++interrupt)
	{
		/* If the interrupt is non-BLE, set priority to 1 (lower than
		 * the default priority of 0). This ensures BLE stability. */
		if (interrupt < BLE_SW_IRQn || interrupt > BLE_ERROR_IRQn)
		{
			NVIC_SetPriority((IRQn_Type)(interrupt), 1);
		}
	}
}

void BLEStackInit(void)
{
    uint8_t param_ptr;

    BLE_Initialize(&param_ptr);

    /* BLE_Initialize() initialized a number of trim registers
     * using default values from the BLE stack,
     * SYS_TRIM_LOAD_CUSTOM() ensures custom trim values are used. */
    uint32_t custom_trim_error __attribute__((unused)) = SYS_TRIM_LOAD_CUSTOM();

    ke_task_create(TASK_APP, MsgHandler_GetTaskAppDesc());
    Device_BLE_Public_Address_Read((uint32_t)APP_BLE_PUBLIC_ADDR_LOC);

    IRQPriorityInit();
}

void AppMsgHandlersInit(void)
{
    /* BLE database setup handler */
    MsgHandler_Add(GAPM_CMP_EVT, BLE_ConfigHandler);
    MsgHandler_Add(GAPM_PROFILE_ADDED_IND, BLE_ConfigHandler);
    MsgHandler_Add(GATTM_ADD_SVC_RSP, BLE_ConfigHandler);

    /* BLE activity handler (responsible for air operations) */
    MsgHandler_Add(GAPM_CMP_EVT, BLE_ActivityHandler);
    MsgHandler_Add(GAPM_ACTIVITY_CREATED_IND, BLE_ActivityHandler);
    MsgHandler_Add(GAPM_ACTIVITY_STOPPED_IND, BLE_ActivityHandler);

    /* BLE connection handler */
    MsgHandler_Add(GAPM_CMP_EVT, BLE_ConnectionHandler);
    MsgHandler_Add(GAPC_CONNECTION_REQ_IND, BLE_ConnectionHandler);
    MsgHandler_Add(GAPC_DISCONNECT_IND, BLE_ConnectionHandler);
    MsgHandler_Add(GAPM_ADDR_SOLVED_IND, BLE_ConnectionHandler);
    MsgHandler_Add(GAPC_GET_DEV_INFO_REQ_IND, BLE_ConnectionHandler);
    MsgHandler_Add(GAPC_PARAM_UPDATE_REQ_IND, BLE_ConnectionHandler);

    /* BLE pairing / bonding  handler */
    MsgHandler_Add(GAPC_BOND_REQ_IND, BLE_PairingHandler);
    MsgHandler_Add(GAPC_BOND_IND, BLE_PairingHandler);
    MsgHandler_Add(GAPC_ENCRYPT_REQ_IND, BLE_PairingHandler);
    MsgHandler_Add(GAPC_ENCRYPT_IND, BLE_PairingHandler);

    /* LED Blink handler (control the LED blinking frequency
     * according to number of connected peer devices) */
    MsgHandler_Add(APP_LED_TIMEOUT, LEDHandler);

    /* Battery level read handler */
    MsgHandler_Add(APP_BATT_LEVEL_READ_TIMEOUT, BattLevelReadHandler);

    /* SW1 handler (to time the 5 seconds holding SW1) */
    MsgHandler_Add(APP_SW1_TIMEOUT, SW1Handler);

    /* SW1 LED handler (to control the timing of LED
     * blinking when bond list clear is successful) */
    MsgHandler_Add(APP_SW1LED_TIMEOUT, SW1LEDHandler);
}

void BatteryServiceServerInit(void)
{
    /* Passing 1 as the number of battery instances since the
     * ble_peripheral_server sample code is only designed to work with 1
     * battery instance, and the APP_BASS_ReadBattLevel function as the
     * callback function that will be called in the BLE abstraction layer
     * to return the battery level.
     */
     BASS_Initialize(APP_BAS_NB, APP_BASS_ReadBattLevel);

     /* Periodically monitor the battery level.
      * Only notify changes in battery level */
     BASS_NotifyOnBattLevelChange(TIMER_SETTING_S(BATT_CHANGE_TIMEOUT_S));

     /* Periodically notify the battery level to connected peers */
     BASS_NotifyOnTimeout(TIMER_SETTING_S(BATT_UPDATE_TIMEOUT_S));
}

void DeviceInformationServiceServerInit(void)
{
    DISS_Initialize(APP_DIS_FEATURES, (const struct DISS_DeviceInfo_t*) &deviceInfo);
}

void CustomServiceServerInit(void)
{
    CUSTOMSS_Initialize();
    CUSTOMSS_NotifyOnTimeout(TIMER_SETTING_S(10));
}
