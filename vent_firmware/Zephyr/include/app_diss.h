/**
 * @file app_diss.h
 * @brief Bluetooth device information server service header
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

#ifndef APP_DISS_H_
#define APP_DISS_H_

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

#include <ble_diss.h>
#include <stdint.h>
#include <ke_msg.h>

/* --------------------------------------------------------------------------
 *  Device Information used for Device Information Server Service (DISS)
 * ----------------------------------------------------------------------- */

/* Manufacturer Name Value */
#define APP_DIS_MANUFACTURER_NAME       ("Peripheral_DISS")
#define APP_DIS_MANUFACTURER_NAME_LEN   (15)

/* Model Number String Value */
#define APP_DIS_MODEL_NB_STR            ("RW-BLE-1.0")
#define APP_DIS_MODEL_NB_STR_LEN        (10)

/* Serial Number */
#define APP_DIS_SERIAL_NB_STR           ("1.0.0.0-LE")
#define APP_DIS_SERIAL_NB_STR_LEN       (10)

/* Firmware Revision */
#define APP_DIS_FIRM_REV_STR            ("6.1.2")
#define APP_DIS_FIRM_REV_STR_LEN        (5)

/* System ID Value - LSB -> MSB */
#define APP_DIS_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_DIS_SYSTEM_ID_LEN           (8)

/* Hardware Revision String */
#define APP_DIS_HARD_REV_STR            ("1.0.0")
#define APP_DIS_HARD_REV_STR_LEN        (5)

/* Software Revision String */
#define APP_DIS_SW_REV_STR              ("6.3.0")
#define APP_DIS_SW_REV_STR_LEN          (5)

/* IEEE */
#define APP_DIS_IEEE                    ("\xFF\xEE\xDD\xCC\xBB\xAA")
#define APP_DIS_IEEE_LEN                (6)

/**
 * PNP ID Value - LSB -> MSB
 *      Vendor ID Source : 0x02 (USB Implementer's Forum assigned Vendor ID value)
 *      Vendor ID : 0x1057      (onsemi)
 *      Product ID : 0x0040
 *      Product Version : 0x0300
 */

#define APP_DIS_PNP_ID               ("\x02\x57\x10\x40\x00\x00\x03")
#define APP_DIS_PNP_ID_LEN           (7)
#define APP_DIS_FEATURES             (DIS_ALL_FEAT_SUP)

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* LINKED_INCLUDE_APP_DISS_H_ */
