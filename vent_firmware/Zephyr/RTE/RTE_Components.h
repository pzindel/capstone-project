/*
 * Auto generated Run-Time-Environment Component Configuration File
 *      *** Do not modify ! ***
 *
 * Project: Zephyr
 * RTE configuration: Zephyr.rteconfig
*/
#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H

/*
 * Define the Device Header File:
*/
#define CMSIS_device_header "rsl15.h"

/* ONSemiconductor::Device.Bluetooth Core.BLE Abstraction */
#define RTE_ADDED_BLE_ABSTRACTION
/* ONSemiconductor::Device.Bluetooth Profiles.BASS.release */
#define RTE_ADDED_PRF_BASS
/* ONSemiconductor::Device.Bluetooth Profiles.DISS.release */
#define RTE_ADDED_PRF_DISS
/* ONSemiconductor::Device.Libraries.SwmTrace.swmTrace_UART_DMA_NB_Source */
#define SWMTRACE_ENABLEMENT SWMTRACE_ENABLED
       #define SWM_TRACE_TYPE SWM_TRACE_UART_DMA_NON_BLOCKING

#endif /* RTE_COMPONENTS_H */
