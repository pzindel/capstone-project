/**
 * @file app_init.h
 * @brief Header file for main application
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

#ifndef APP_INIT_H_
#define APP_INIT_H_

#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/** Macro to Set Priority Mask and Fault Mask interrupts disable */
#define PRIMASK_FAULTMASK_DISABLE_INTERRUPTS()  __set_PRIMASK(PRIMASK_DISABLE_INTERRUPTS); \
    __set_FAULTMASK(FAULTMASK_DISABLE_INTERRUPTS);

/** Macro to Set Priority Mask and Fault Mask interrupts enable */
#define PRIMASK_FAULTMASK_ENABLE_INTERRUPTS()   __set_PRIMASK(PRIMASK_ENABLE_INTERRUPTS); \
    __set_FAULTMASK(FAULTMASK_ENABLE_INTERRUPTS);

/**
 * @brief Initialize the device, including GPIOs.
 *
 * This function disable interrupts, initialize device clocks, GPIOs
 * and trace interface.
 */
void DeviceInit(void);

/**
 * @brief Initialize swmTrace.
 *
 * This function initialize SWM trace with swmtrace options
 */
void SWMTraceInit(void);

/**
 * @brief Initialize the device to configure BLE
 *
 * This function configure settings for setting TX power, RF performance
 * improvement and initialize BLE stack.
 */
void BLESystemInit(void);

/**
 * @brief Enable application BLE interrupts.
 *
 * This function clear pending BLE IRQs and enable BLE interrupts.
 */
void EnableBLEInterrupts(void);

/**
 * @brief Set the priority of non-BLE interrupts
 *
 * This function sets the priority of all non-BLE interrupts to 1.
 * By default, BLE interrupts have priority 0.
 */
void IRQPriorityInit(void);

/**
 * @brief Initialize BLE stack.
 *
 * This function initialize the kernel and create application task.
 */
void BLEStackInit(void);

/**
 * @brief Initialize application related message handlers.
 *
 * This function initialize different message handlers which are used
 * as callback for relative BLE events.
 */
void AppMsgHandlersInit(void);
void BatteryServiceServerInit(void);
void DeviceInformationServiceServerInit(void);
void CustomServiceServerInit(void);
void EnableAppInterrupts(void);

#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_INIT_H */
