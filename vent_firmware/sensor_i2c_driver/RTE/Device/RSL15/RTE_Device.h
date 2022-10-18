/**
 * @file RTE_Device.h
 * @brief This file is used to configure the CMSIS-Driver for each interface.
 *        To open this configuration file in GUI mode, right-click it and select
 *        Open with > CMSIS Configuration Wizard.
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
// <<< Use Configuration Wizard in Context Menu >>>

#ifndef RTE_DEVICE_H
#define RTE_DEVICE_H

// <e> DMA Configuration
// =======================
//
//   <i> Defines if DMA driver should be enabled.
//   <i> Default: 1
#ifndef RTE_DMA
 #define RTE_DMA     1
#endif
// <e>DMA 0 enabled
// ===============================
//
//   <i> Defines if dma 0 should be enabled.
//   <i> Default: 1
#ifndef RTE_DMA0_EN
 #define RTE_DMA0_EN       1
#endif
// <e>DMA 0 auto configuration
// ===============================
//
// <i> Enables dma channel 0 configuration.
// <i> Default: 1
#ifndef RTE_DMA0_AUTO_EN
 #define RTE_DMA0_AUTO_EN       0
#endif
// <h>Source configuration
// ===============================
//
//   <o>Source target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the source target
//   <i> Default: MEMORY
#ifndef RTE_DMA0_SRC_SEL_DEFAULT
 #define RTE_DMA0_SRC_SEL_DEFAULT   0
#endif
//    <o>  Source Address Step
//       <0x0=> Do not increment the source address used by DMA channel
//       <0x1=> Set the step size of DMA channel source address to 1
//       <0x2=> Set the step size of DMA channel source address to 2
//       <0x3=> Set the step size of DMA channel source address to 3
//       <0x4=> Set the step size of DMA channel source address to 4
//       <0x5=> Set the step size of DMA channel source address to 5
//       <0x6=> Set the step size of DMA channel source address to 6
//       <0x7=> Set the step size of DMA channel source address to 7
//       <0x8=> Set the step size of DMA channel source address to minus 8
//       <0x9=> Set the step size of DMA channel source address to minus 7
//       <0xA=> Set the step size of DMA channel source address to minus 6
//       <0xB=> Set the step size of DMA channel source address to minus 5
//       <0xC=> Set the step size of DMA channel source address to minus 4
//       <0xD=> Set the step size of DMA channel source address to minus 3
//       <0xE=> Set the step size of DMA channel source address to minus 2
//       <0xF=> Set the step size of DMA channel source address to minus 1
//   <i> Configure whether the source address increments/decrements in terms of source word size
//   <i> Default: Do not increment the source address used by DMA channel
#ifndef RTE_DMA0_SRC_STEP_DEFAULT
 #define RTE_DMA0_SRC_STEP_DEFAULT       1
#endif
// </h>
// <h>Destination configuration
// ===============================
//
//   <o>Destination target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the destination target
//   <i> Default: MEMORY
#ifndef RTE_DMA0_DST_SEL_DEFAULT
 #define RTE_DMA0_DST_SEL_DEFAULT   0
#endif
//  <o> Destination address step
//       <0x0=> Do not increment the destination address used by DMA channel
//       <0x1=> Set the step size of DMA channel destination address to 1
//       <0x2=> Set the step size of DMA channel destination address to 2
//       <0x3=> Set the step size of DMA channel destination address to 3
//       <0x4=> Set the step size of DMA channel destination address to 4
//       <0x5=> Set the step size of DMA channel destination address to 5
//       <0x6=> Set the step size of DMA channel destination address to 6
//       <0x7=> Set the step size of DMA channel destination address to 7
//       <0x8=> Set the step size of DMA channel destination address to minus 8
//       <0x9=> Set the step size of DMA channel destination address to minus 7
//       <0xA=> Set the step size of DMA channel destination address to minus 6
//       <0xB=> Set the step size of DMA channel destination address to minus 5
//       <0xC=> Set the step size of DMA channel destination address to minus 4
//       <0xD=> Set the step size of DMA channel destination address to minus 3
//       <0xE=> Set the step size of DMA channel destination address to minus 2
//       <0xF=> Set the step size of DMA channel destination address to minus 1
//   <i> Configure whether the destination address increments/decrements in terms of source word size
//   <i> Default: Do not increment the destination address used by DMA channel
#ifndef RTE_DMA0_DST_STEP_DEFAULT
#define RTE_DMA0_DST_STEP_DEFAULT       1
#endif
// </h>
//   <o> Word size select
//       <0x00=> source data uses 32-bit word and destination data uses 32-bit word
//       <0x01=> source data uses 32-bit word and destination data uses 4-bit word
//       <0x02=> source data uses 32-bit word and destination data uses 8-bit word
//       <0x04=> source data uses 32-bit word and destination data uses 16-bit word
//       <0x08=> source data uses 4-bit word and destination data uses 32-bit word
//       <0x09=> source data uses 4-bit word and destination data uses 4-bit word
//       <0x0A=> source data uses 4-bit word and destination data uses 8-bit word
//       <0x0C=> source data uses 4-bit word and destination data uses 16-bit word
//       <0x0E=> source data uses 4-bit word and destination data uses 24-bit word
//       <0x10=> source data uses 8-bit word and destination data uses 32-bit word
//       <0x11=> source data uses 8-bit word and destination data uses 4-bit word
//       <0x12=> source data uses 8-bit word and destination data uses 8-bit word
//       <0x14=> source data uses 8-bit word and destination data uses 16-bit word
//       <0x16=> source data uses 8-bit word and destination data uses 24-bit word
//       <0x20=> source data uses 16-bit word and destination data uses 32-bit word
//       <0x21=> source data uses 16-bit word and destination data uses 4-bit word
//       <0x22=> source data uses 16-bit word and destination data uses 8-bit word
//       <0x24=> source data uses 16-bit word and destination data uses 16-bit word
//       <0x26=> source data uses 16-bit word and destination data uses 24-bit word
//       <0x31=> source data uses 24-bit word and destination data uses 4-bit word
//       <0x32=> source data uses 24-bit word and destination data uses 8-bit word
//       <0x34=> source data uses 24-bit word and destination data uses 16-bit word
//       <0x36=> source data uses 24-bit word and destination data uses 24-bit word
//   <i> Select the source and destination word sizes for the transfer
//   <i> Default: 0
#ifndef RTE_DMA0_SRC_DEST_WORD_SIZE_DEFAULT
 #define RTE_DMA0_SRC_DEST_WORD_SIZE_DEFAULT   18
#endif
//   <o>Channel priority
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines the channel priority
//   <i> Default: 0
#ifndef RTE_DMA0_CHANNEL_PRIORITY_DEFAULT
 #define RTE_DMA0_CHANNEL_PRIORITY_DEFAULT   0
#endif
// <h>Interrupt priority configuration
// ===============================
//
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_DMA0_INT_PREEMPT_PRI
 #define RTE_DMA0_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_DMA0_INT_SUBGRP_PRI
 #define RTE_DMA0_INT_SUBGRP_PRI   0
#endif
// </h>
// </e>
// </e>
// <e>DMA 1 enabled
// ===============================
//
//   <i> Defines if dma 1 should be enabled.
//   <i> Default: 1
#ifndef RTE_DMA1_EN
 #define RTE_DMA1_EN       1
#endif
// <e>DMA 1 auto configuration
// ===============================
//
// <i> Enables dma channel 1 configuration.
// <i> Default: 1
#ifndef RTE_DMA1_AUTO_EN
 #define RTE_DMA1_AUTO_EN       1
#endif
// <h>Source configuration
// ===============================
//
//   <o>Source target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the source target
//   <i> Default: MEMORY
#ifndef RTE_DMA1_SRC_SEL_DEFAULT
 #define RTE_DMA1_SRC_SEL_DEFAULT   0
#endif
//    <o>  Source Address Step
//       <0x0=> Do not increment the source address used by DMA channel
//       <0x1=> Set the step size of DMA channel source address to 1
//       <0x2=> Set the step size of DMA channel source address to 2
//       <0x3=> Set the step size of DMA channel source address to 3
//       <0x4=> Set the step size of DMA channel source address to 4
//       <0x5=> Set the step size of DMA channel source address to 5
//       <0x6=> Set the step size of DMA channel source address to 6
//       <0x7=> Set the step size of DMA channel source address to 7
//       <0x8=> Set the step size of DMA channel source address to minus 8
//       <0x9=> Set the step size of DMA channel source address to minus 7
//       <0xA=> Set the step size of DMA channel source address to minus 6
//       <0xB=> Set the step size of DMA channel source address to minus 5
//       <0xC=> Set the step size of DMA channel source address to minus 4
//       <0xD=> Set the step size of DMA channel source address to minus 3
//       <0xE=> Set the step size of DMA channel source address to minus 2
//       <0xF=> Set the step size of DMA channel source address to minus 1
//   <i> Configure whether the source address increments/decrements in terms of source word size
//   <i> Default: Do not increment the source address used by DMA channel
#ifndef RTE_DMA1_SRC_STEP_DEFAULT
 #define RTE_DMA1_SRC_STEP_DEFAULT       0
#endif
// </h>
// <h>Destination configuration
// ===============================
//
//   <o>Destination target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the destination target
//   <i> Default: MEMORY
#ifndef RTE_DMA1_DST_SEL_DEFAULT
 #define RTE_DMA1_DST_SEL_DEFAULT   0
#endif
//  <o> Destination address step
//       <0x0=> Do not increment the destination address used by DMA channel
//       <0x1=> Set the step size of DMA channel destination address to 1
//       <0x2=> Set the step size of DMA channel destination address to 2
//       <0x3=> Set the step size of DMA channel destination address to 3
//       <0x4=> Set the step size of DMA channel destination address to 4
//       <0x5=> Set the step size of DMA channel destination address to 5
//       <0x6=> Set the step size of DMA channel destination address to 6
//       <0x7=> Set the step size of DMA channel destination address to 7
//       <0x8=> Set the step size of DMA channel destination address to minus 8
//       <0x9=> Set the step size of DMA channel destination address to minus 7
//       <0xA=> Set the step size of DMA channel destination address to minus 6
//       <0xB=> Set the step size of DMA channel destination address to minus 5
//       <0xC=> Set the step size of DMA channel destination address to minus 4
//       <0xD=> Set the step size of DMA channel destination address to minus 3
//       <0xE=> Set the step size of DMA channel destination address to minus 2
//       <0xF=> Set the step size of DMA channel destination address to minus 1
//   <i> Configure whether the destination address increments/decrements in terms of source word size
//   <i> Default: Do not increment the destination address used by DMA channel
#ifndef RTE_DMA1_DST_STEP_DEFAULT
#define RTE_DMA1_DST_STEP_DEFAULT       0
#endif
// </h>
//   <o> Word size select
//       <0x00=> source data uses 32-bit word and destination data uses 32-bit word
//       <0x01=> source data uses 32-bit word and destination data uses 4-bit word
//       <0x02=> source data uses 32-bit word and destination data uses 8-bit word
//       <0x04=> source data uses 32-bit word and destination data uses 16-bit word
//       <0x08=> source data uses 4-bit word and destination data uses 32-bit word
//       <0x09=> source data uses 4-bit word and destination data uses 4-bit word
//       <0x0A=> source data uses 4-bit word and destination data uses 8-bit word
//       <0x0C=> source data uses 4-bit word and destination data uses 16-bit word
//       <0x0E=> source data uses 4-bit word and destination data uses 24-bit word
//       <0x10=> source data uses 8-bit word and destination data uses 32-bit word
//       <0x11=> source data uses 8-bit word and destination data uses 4-bit word
//       <0x12=> source data uses 8-bit word and destination data uses 8-bit word
//       <0x14=> source data uses 8-bit word and destination data uses 16-bit word
//       <0x16=> source data uses 8-bit word and destination data uses 24-bit word
//       <0x20=> source data uses 16-bit word and destination data uses 32-bit word
//       <0x21=> source data uses 16-bit word and destination data uses 4-bit word
//       <0x22=> source data uses 16-bit word and destination data uses 8-bit word
//       <0x24=> source data uses 16-bit word and destination data uses 16-bit word
//       <0x26=> source data uses 16-bit word and destination data uses 24-bit word
//       <0x31=> source data uses 24-bit word and destination data uses 4-bit word
//       <0x32=> source data uses 24-bit word and destination data uses 8-bit word
//       <0x34=> source data uses 24-bit word and destination data uses 16-bit word
//       <0x36=> source data uses 24-bit word and destination data uses 24-bit word
//   <i> Select the source and destination word sizes for the transfer
//   <i> Default: 0
#ifndef RTE_DMA1_SRC_DEST_WORD_SIZE_DEFAULT
 #define RTE_DMA1_SRC_DEST_WORD_SIZE_DEFAULT   0
#endif
//   <o>Channel priority
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines the channel priority
//   <i> Default: 0
#ifndef RTE_DMA1_CHANNEL_PRIORITY_DEFAULT
 #define RTE_DMA1_CHANNEL_PRIORITY_DEFAULT   0
#endif
// <h>Interrupt priority configuration
// ===============================
//
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_DMA1_INT_PREEMPT_PRI
 #define RTE_DMA1_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_DMA1_INT_SUBGRP_PRI
 #define RTE_DMA1_INT_SUBGRP_PRI   0
#endif
// </h>
// </e>
// </e>
// <e>DMA 2 enabled
// ===============================
//
//   <i> Defines if dma 2 should be enabled.
//   <i> Default: 1
#ifndef RTE_DMA2_EN
 #define RTE_DMA2_EN       0
#endif
// <e>DMA 2 auto configuration
// ===============================
//
// <i> Enables dma channel 2 configuration.
// <i> Default: 1
#ifndef RTE_DMA2_AUTO_EN
 #define RTE_DMA2_AUTO_EN       1
#endif
// <h>Source configuration
// ===============================
//
//   <o>Source target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the source target
//   <i> Default: MEMORY
#ifndef RTE_DMA2_SRC_SEL_DEFAULT
 #define RTE_DMA2_SRC_SEL_DEFAULT   0
#endif
//    <o>  Source Address Step
//       <0x0=> Do not increment the source address used by DMA channel
//       <0x1=> Set the step size of DMA channel source address to 1
//       <0x2=> Set the step size of DMA channel source address to 2
//       <0x3=> Set the step size of DMA channel source address to 3
//       <0x4=> Set the step size of DMA channel source address to 4
//       <0x5=> Set the step size of DMA channel source address to 5
//       <0x6=> Set the step size of DMA channel source address to 6
//       <0x7=> Set the step size of DMA channel source address to 7
//       <0x8=> Set the step size of DMA channel source address to minus 8
//       <0x9=> Set the step size of DMA channel source address to minus 7
//       <0xA=> Set the step size of DMA channel source address to minus 6
//       <0xB=> Set the step size of DMA channel source address to minus 5
//       <0xC=> Set the step size of DMA channel source address to minus 4
//       <0xD=> Set the step size of DMA channel source address to minus 3
//       <0xE=> Set the step size of DMA channel source address to minus 2
//       <0xF=> Set the step size of DMA channel source address to minus 1
//   <i> Configure whether the source address increments/decrements in terms of source word size
//   <i> Default: Do not increment the source address used by DMA channel
#ifndef RTE_DMA2_SRC_STEP_DEFAULT
 #define RTE_DMA2_SRC_STEP_DEFAULT       0
#endif
// </h>
// <h>Destination configuration
// ===============================
//
//   <o>Destination target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the destination target
//   <i> Default: MEMORY
#ifndef RTE_DMA2_DST_SEL_DEFAULT
 #define RTE_DMA2_DST_SEL_DEFAULT   0
#endif
//  <o> Destination address step
//       <0x0=> Do not increment the destination address used by DMA channel
//       <0x1=> Set the step size of DMA channel destination address to 1
//       <0x2=> Set the step size of DMA channel destination address to 2
//       <0x3=> Set the step size of DMA channel destination address to 3
//       <0x4=> Set the step size of DMA channel destination address to 4
//       <0x5=> Set the step size of DMA channel destination address to 5
//       <0x6=> Set the step size of DMA channel destination address to 6
//       <0x7=> Set the step size of DMA channel destination address to 7
//       <0x8=> Set the step size of DMA channel destination address to minus 8
//       <0x9=> Set the step size of DMA channel destination address to minus 7
//       <0xA=> Set the step size of DMA channel destination address to minus 6
//       <0xB=> Set the step size of DMA channel destination address to minus 5
//       <0xC=> Set the step size of DMA channel destination address to minus 4
//       <0xD=> Set the step size of DMA channel destination address to minus 3
//       <0xE=> Set the step size of DMA channel destination address to minus 2
//       <0xF=> Set the step size of DMA channel destination address to minus 1
//   <i> Configure whether the destination address increments/decrements in terms of source word size
//   <i> Default: Do not increment the destination address used by DMA channel
#ifndef RTE_DMA2_DST_STEP_DEFAULT
#define RTE_DMA2_DST_STEP_DEFAULT       0
#endif
// </h>
//   <o> Word size select
//       <0x00=> source data uses 32-bit word and destination data uses 32-bit word
//       <0x01=> source data uses 32-bit word and destination data uses 4-bit word
//       <0x02=> source data uses 32-bit word and destination data uses 8-bit word
//       <0x04=> source data uses 32-bit word and destination data uses 16-bit word
//       <0x08=> source data uses 4-bit word and destination data uses 32-bit word
//       <0x09=> source data uses 4-bit word and destination data uses 4-bit word
//       <0x0A=> source data uses 4-bit word and destination data uses 8-bit word
//       <0x0C=> source data uses 4-bit word and destination data uses 16-bit word
//       <0x0E=> source data uses 4-bit word and destination data uses 24-bit word
//       <0x10=> source data uses 8-bit word and destination data uses 32-bit word
//       <0x11=> source data uses 8-bit word and destination data uses 4-bit word
//       <0x12=> source data uses 8-bit word and destination data uses 8-bit word
//       <0x14=> source data uses 8-bit word and destination data uses 16-bit word
//       <0x16=> source data uses 8-bit word and destination data uses 24-bit word
//       <0x20=> source data uses 16-bit word and destination data uses 32-bit word
//       <0x21=> source data uses 16-bit word and destination data uses 4-bit word
//       <0x22=> source data uses 16-bit word and destination data uses 8-bit word
//       <0x24=> source data uses 16-bit word and destination data uses 16-bit word
//       <0x26=> source data uses 16-bit word and destination data uses 24-bit word
//       <0x31=> source data uses 24-bit word and destination data uses 4-bit word
//       <0x32=> source data uses 24-bit word and destination data uses 8-bit word
//       <0x34=> source data uses 24-bit word and destination data uses 16-bit word
//       <0x36=> source data uses 24-bit word and destination data uses 24-bit word
//   <i> Default: 0
#ifndef RTE_DMA2_SRC_DEST_WORD_SIZE_DEFAULT
 #define RTE_DMA2_SRC_DEST_WORD_SIZE_DEFAULT   0
#endif
//   <o>Channel priority
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines the channel priority
//   <i> Default: 0
#ifndef RTE_DMA2_CHANNEL_PRIORITY_DEFAULT
 #define RTE_DMA2_CHANNEL_PRIORITY_DEFAULT   0
#endif
// <h>Interrupt priority configuration
// ===============================
//
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_DMA2_INT_PREEMPT_PRI
 #define RTE_DMA2_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_DMA2_INT_SUBGRP_PRI
 #define RTE_DMA2_INT_SUBGRP_PRI   0
#endif
// </h>
// </e>
// </e>
// <e>DMA 3 enabled
// ===============================
//
//   <i> Defines if dma 3 should be enabled.
//   <i> Default: 1
#ifndef RTE_DMA3_EN
 #define RTE_DMA3_EN       0
#endif
// <e>DMA 3 auto configuration
// ===============================
//
// <i> Enables dma channel 3 configuration.
// <i> Default: 1
#ifndef RTE_DMA3_AUTO_EN
 #define RTE_DMA3_AUTO_EN       1
#endif
// <h>Source configuration
// ===============================
//
//   <o>Source target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the source target
//   <i> Default: MEMORY
#ifndef RTE_DMA3_SRC_SEL_DEFAULT
 #define RTE_DMA3_SRC_SEL_DEFAULT   0
#endif
//    <o>  Source Address Step
//       <0x0=> Do not increment the source address used by DMA channel
//       <0x1=> Set the step size of DMA channel source address to 1
//       <0x2=> Set the step size of DMA channel source address to 2
//       <0x3=> Set the step size of DMA channel source address to 3
//       <0x4=> Set the step size of DMA channel source address to 4
//       <0x5=> Set the step size of DMA channel source address to 5
//       <0x6=> Set the step size of DMA channel source address to 6
//       <0x7=> Set the step size of DMA channel source address to 7
//       <0x8=> Set the step size of DMA channel source address to minus 8
//       <0x9=> Set the step size of DMA channel source address to minus 7
//       <0xA=> Set the step size of DMA channel source address to minus 6
//       <0xB=> Set the step size of DMA channel source address to minus 5
//       <0xC=> Set the step size of DMA channel source address to minus 4
//       <0xD=> Set the step size of DMA channel source address to minus 3
//       <0xE=> Set the step size of DMA channel source address to minus 2
//       <0xF=> Set the step size of DMA channel source address to minus 1
//   <i> Configure whether the source address increments/decrements in terms of source word size
//   <i> Default: Do not increment the source address used by DMA channel
#ifndef RTE_DMA3_SRC_STEP_DEFAULT
 #define RTE_DMA3_SRC_STEP_DEFAULT       0
#endif
// </h>
// <h>Destination configuration
// ===============================
//
//   <o>Destination target
//       <0x0=> MEMORY <0x1=> SPI0
//       <0x2=> SPI1   <0x3=> I2C0
//       <0x4=> I2C1   <0x5=> UART0
//       <0x6=> PCM0   <0x7=> TOF
//   <i> Defines the destination target
//   <i> Default: MEMORY
#ifndef RTE_DMA3_DST_SEL_DEFAULT
 #define RTE_DMA3_DST_SEL_DEFAULT   0
#endif
//  <o> Destination address step
//       <0x0=> Do not increment the destination address used by DMA channel
//       <0x1=> Set the step size of DMA channel destination address to 1
//       <0x2=> Set the step size of DMA channel destination address to 2
//       <0x3=> Set the step size of DMA channel destination address to 3
//       <0x4=> Set the step size of DMA channel destination address to 4
//       <0x5=> Set the step size of DMA channel destination address to 5
//       <0x6=> Set the step size of DMA channel destination address to 6
//       <0x7=> Set the step size of DMA channel destination address to 7
//       <0x8=> Set the step size of DMA channel destination address to minus 8
//       <0x9=> Set the step size of DMA channel destination address to minus 7
//       <0xA=> Set the step size of DMA channel destination address to minus 6
//       <0xB=> Set the step size of DMA channel destination address to minus 5
//       <0xC=> Set the step size of DMA channel destination address to minus 4
//       <0xD=> Set the step size of DMA channel destination address to minus 3
//       <0xE=> Set the step size of DMA channel destination address to minus 2
//       <0xF=> Set the step size of DMA channel destination address to minus 1
//   <i> Configure whether the destination address increments/decrements in terms of source word size
//   <i> Default: Do not increment the destination address used by DMA channel
#ifndef RTE_DMA3_DST_STEP_DEFAULT
#define RTE_DMA3_DST_STEP_DEFAULT       0
#endif
// </h>
//   <o> Word size select
//       <0x00=> source data uses 32-bit word and destination data uses 32-bit word
//       <0x01=> source data uses 32-bit word and destination data uses 4-bit word
//       <0x02=> source data uses 32-bit word and destination data uses 8-bit word
//       <0x04=> source data uses 32-bit word and destination data uses 16-bit word
//       <0x08=> source data uses 4-bit word and destination data uses 32-bit word
//       <0x09=> source data uses 4-bit word and destination data uses 4-bit word
//       <0x0A=> source data uses 4-bit word and destination data uses 8-bit word
//       <0x0C=> source data uses 4-bit word and destination data uses 16-bit word
//       <0x0E=> source data uses 4-bit word and destination data uses 24-bit word
//       <0x10=> source data uses 8-bit word and destination data uses 32-bit word
//       <0x11=> source data uses 8-bit word and destination data uses 4-bit word
//       <0x12=> source data uses 8-bit word and destination data uses 8-bit word
//       <0x14=> source data uses 8-bit word and destination data uses 16-bit word
//       <0x16=> source data uses 8-bit word and destination data uses 24-bit word
//       <0x20=> source data uses 16-bit word and destination data uses 32-bit word
//       <0x21=> source data uses 16-bit word and destination data uses 4-bit word
//       <0x22=> source data uses 16-bit word and destination data uses 8-bit word
//       <0x24=> source data uses 16-bit word and destination data uses 16-bit word
//       <0x26=> source data uses 16-bit word and destination data uses 24-bit word
//       <0x31=> source data uses 24-bit word and destination data uses 4-bit word
//       <0x32=> source data uses 24-bit word and destination data uses 8-bit word
//       <0x34=> source data uses 24-bit word and destination data uses 16-bit word
//       <0x36=> source data uses 24-bit word and destination data uses 24-bit word
//   <i> Select the source and destination word sizes for the transfer
//   <i> Default: 0
#ifndef RTE_DMA3_SRC_DEST_WORD_SIZE_DEFAULT
 #define RTE_DMA3_SRC_DEST_WORD_SIZE_DEFAULT   0
#endif
//   <o>Channel priority
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines the channel priority
//   <i> Default: 0
#ifndef RTE_DMA3_CHANNEL_PRIORITY_DEFAULT
 #define RTE_DMA3_CHANNEL_PRIORITY_DEFAULT   0
#endif
// <h>Interrupt priority configuration
// ===============================
//
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_DMA3_INT_PREEMPT_PRI
 #define RTE_DMA3_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_DMA3_INT_SUBGRP_PRI
 #define RTE_DMA3_INT_SUBGRP_PRI   0
#endif
// </h>
// </e>
// </e>
// </e>

// <e> RF Output Power Configuration
// <i> Configuration settings for RF Output Power
#define RTE_TX_POWER_ENABLED            0

//   <o>RF output power level
//      <0=> -17 dBm
//      <1=> -16 dBm
//      <2=> -15 dBm
//      <3=> -14 dBm
//      <4=> -13 dBm
//      <5=> -12 dBm
//      <6=> -11 dBm
//      <7=> -10 dBm
//      <8=> -9 dBm
//      <9=> -8 dBm
//      <10=> -7 dBm
//      <11=> -6 dBm
//      <12=> -5 dBm
//      <13=> -4 dBm
//      <14=> -3 dBm
//      <15=> -2 dBm
//      <16=> -1 dBm
//      <17=> 0 dBm
//      <18=> +1 dBm
//      <19=> +2 dBm
//      <20=> +3 dBm
//      <21=> +4 dBm
//      <22=> +5 dBm
//      <23=> +6 dBm
//   <i> Default: 0 dBm
#define RTE_TX_POWER     17
#define RTE_TX_POWER_VALUE     (RTE_TX_POWER - 17)

//   <e> Power amplifier enabled
#define POWER_AMPLIFIER_ENABLED 1
// </e>

// </e>

// <e> USART0 (Universal synchronous asynchronous receiver transmitter) [Driver_USART0]
// <i> Configuration settings for Driver_USART0 in component ::CMSIS Driver:USART
#define RTE_USART0_ENABLED               0

//   <o> USART0_RX GPIO <0-15>
#define RTE_USART0_RX_PIN                5

//   <o> USART0_TX GPIO <0-15>
#define RTE_USART0_TX_PIN                6

// </e>

// <e> I2C0 (Inter-integrated Circuit Interface 0)
// <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C
#define RTE_I2C0_ENABLED                 1

//   <o> I2C0_SCL GPIO <0-15>
#define RTE_I2C0_SCL_PIN                 11

//   <o> I2C0_SDA GPIO <0-15>
#define RTE_I2C0_SDA_PIN                 12

//   <o RTE_I2C0_GPIO_LPF> I2C0 GPIO Low Pass Filter
//      <GPIO_LPF_DISABLE=>DISABLED <GPIO_LPF_ENABLE=>ENABLED
#define RTE_I2C0_GPIO_LPF                GPIO_LPF_DISABLE

//   <o RTE_I2C0_GPIO_DRIVE> I2C0 GPIO Drive Strength  <GPIO_LEVEL1_DRIVE=>Level 1
//      <GPIO_LEVEL2_DRIVE=>Level 2 <GPIO_LEVEL3_DRIVE=>Level 3
//      <GPIO_LEVEL4_DRIVE=>Level 4
#define RTE_I2C0_GPIO_DRIVE              GPIO_LEVEL3_DRIVE

//   <o RTE_I2C0_GPIO_PULL> I2C0 GPIO Pull Selection <GPIO_NO_PULL=>No pull
//      <GPIO_STRONG_PULL_UP=>Strong pull-up <GPIO_WEAK_PULL_UP=>Weak pull-up
//      <GPIO_WEAK_PULL_DOWN=>Weak pull-down
#define RTE_I2C0_GPIO_PULL               GPIO_STRONG_PULL_UP

// <e>I2C0 DMA control
// ===============================
//
//   <i> Enables dma control of i2c0 module
//   <i> Default: 0 */
#ifndef RTE_I2C0_DMA_EN_DEFAULT
 #define RTE_I2C0_DMA_EN_DEFAULT       1
#endif
//   <o>I2C0 dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 0
#ifndef RTE_I2C0_DMA_CH_DEFAULT
 #define RTE_I2C0_DMA_CH_DEFAULT        0
#endif
// </e>
// </e>

// <e> I2C1 (Inter-integrated Circuit Interface 1)
// <i> Configuration settings for Driver_I2C1I in component ::CMSIS Driver:I2C
#define RTE_I2C1_ENABLED                 1

//   <o> I2C1_SCL Pin <0-15>
#define RTE_I2C1_SCL_PIN                 13

//   <o> I2C1_SDA Pin <0-15>
#define RTE_I2C1_SDA_PIN                 14

//   <o RTE_I2C1_GPIO_LPF> I2C1 GPIO Low Pass Filter
//      <GPIO_LPF_DISABLE=>DISABLED <GPIO_LPF_ENABLE=>ENABLED
#define RTE_I2C1_GPIO_LPF                GPIO_LPF_DISABLE

//   <o RTE_I2C1_GPIO_DRIVE> I2C1 GPIO Drive Strength  <GPIO_LEVEL1_DRIVE=>Level 1
//      <GPIO_LEVEL2_DRIVE=>Level 2 <GPIO_LEVEL3_DRIVE=>Level 3
//      <GPIO_LEVEL4_DRIVE=>Level 4
#define RTE_I2C1_GPIO_DRIVE              GPIO_LEVEL3_DRIVE

//   <o RTE_I2C1_GPIO_PULL> I2C1 GPIO Pull Selection <GPIO_NO_PULL=>No pull
//      <GPIO_STRONG_PULL_UP=>Strong pull-up <GPIO_WEAK_PULL_UP=>Weak pull-up
//      <GPIO_WEAK_PULL_DOWN=>Weak pull-down
#define RTE_I2C1_GPIO_PULL               GPIO_STRONG_PULL_UP

// <e>I2C1 DMA control
// ===============================
//
//   <i> Enables dma control of i2c1 module
//   <i> Default: 0
#ifndef RTE_I2C1_DMA_EN_DEFAULT
 #define RTE_I2C1_DMA_EN_DEFAULT       1
#endif
//   <o>I2C1 dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 0
#ifndef RTE_I2C1_DMA_CH_DEFAULT
 #define RTE_I2C1_DMA_CH_DEFAULT   1
#endif
// </e>
// </e>

// <e> SPI0 (Serial Peripheral Interface 0) [Driver_SPI0]
// <i> Configuration settings for Driver_SPI0 in component ::CMSIS Driver:SPI
#ifndef RTE_SPI0_ENABLED
 #define RTE_SPI0_ENABLED                 0
#endif

//   <e>SPI0 auto configuration
// ===============================
//
#ifndef RTE_SPI0_CFG_EN_DEFAULT
 #define RTE_SPI0_CFG_EN_DEFAULT   1
#endif
//   <o>Mode selection
//       <0x0=> inactive
//       <0x10=> master ss unused
//       <0x11=> master
//       <0x20=> slave ss hw controlled
//       <0x21=> slave ss sw controlled
//   <i> Sets the SPI0 mode
//   <i> Default: master
#ifndef RTE_SPI0_MODE_DEFAULT
 #define RTE_SPI0_MODE_DEFAULT   0x11
#endif
//   <o>Speed selection <1000-10000000>
//   <i> Defines the SPI0 speed.
//   <i> The selected speed may not be achievable. Driver will set the closest speed by diving the sysclk by 2^N (N max = 9).
//   <i> Default: 750000
#ifndef RTE_SPI0_SPEED_DEFAULT
 #define RTE_SPI0_SPEED_DEFAULT   150000
#endif
//   <o>Clock polarity
//       <0x0=> normal
//       <0x2=> inverse
//   <i> Sets the SPI0 clock polarity
//   <i> Default: normal
#ifndef RTE_SPI0_POL_DEFAULT
 #define RTE_SPI0_POL_DEFAULT   0
#endif
//   <o>Word size
//       <0x8=> 8
//       <0x10=> 16
//       <0x18=> 24 (not supported in dma mode)
//       <0x20=> 32
//   <i> Sets the SPI0 word size
//   <i> Default: 8
#ifndef RTE_SPI0_WS_DEFAULT
 #define RTE_SPI0_WS_DEFAULT   8
#endif
// </e>

//   <o> SPI0_MOSI GPIO <0-15>
#ifndef RTE_SPI0_MOSI_PIN
 #define RTE_SPI0_MOSI_PIN                1
#endif

//   <o> SPI0_MISO GPIO <0-15>
#ifndef RTE_SPI0_MISO_PIN
 #define RTE_SPI0_MISO_PIN                2
#endif

//   <o> SPI0_SSEL GPIO <0-15>
#ifndef RTE_SPI0_SSEL_PIN
 #define RTE_SPI0_SSEL_PIN                3
#endif

//   <o> SPI0_SCLK GPIO <0-15>
#ifndef RTE_SPI0_SCLK_PIN
 #define RTE_SPI0_SCLK_PIN                4
#endif

//   <o RTE_SPI0_GPIO_LPF> SPI0 GPIO Low Pass Filter
//      <GPIO_LPF_DISABLE=>DISABLED <GPIO_LPF_ENABLE=>ENABLED
#define RTE_SPI0_GPIO_LPF                GPIO_LPF_DISABLE

//   <o RTE_SPI0_GPIO_DRIVE> SPI0 GPIO Drive Strength  <GPIO_LEVEL1_DRIVE=>Level 1
//      <GPIO_LEVEL2_DRIVE=>Level 2 <GPIO_LEVEL3_DRIVE=>Level 3
//      <GPIO_LEVEL4_DRIVE=>Level 4
#define RTE_SPI0_GPIO_DRIVE              GPIO_LEVEL1_DRIVE

//   <o RTE_SPI0_GPIO_PULL> SPI0 GPIO Pull Selection <GPIO_NO_PULL=>No pull
//      <GPIO_STRONG_PULL_UP=>Strong pull-up <GPIO_WEAK_PULL_UP=>Weak pull-up
//      <GPIO_WEAK_PULL_DOWN=>Weak pull-down
#define RTE_SPI0_GPIO_PULL               GPIO_WEAK_PULL_UP


// <e>SPI0 DMA control
// ===============================
//
//   <i> Enables dma control of spi0 module
//   <i> Default: 0
#ifndef RTE_SPI0_DMA_EN_DEFAULT
 #define RTE_SPI0_DMA_EN_DEFAULT       0
#endif
//   <o>SPI0 rx dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 0
#ifndef RTE_SPI0_RX_DMA_CH_DEFAULT
 #define RTE_SPI0_RX_DMA_CH_DEFAULT   0
#endif
//   <o>SPI0 tx dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 1
#ifndef RTE_SPI0_TX_DMA_CH_DEFAULT
 #define RTE_SPI0_TX_DMA_CH_DEFAULT   1
#endif
// </e>
// </e>


// <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
// <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI
#define RTE_SPI1_ENABLED                 0

//   <e>SPI1 auto configuration
// ===============================
//
#ifndef RTE_SPI1_CFG_EN_DEFAULT
 #define RTE_SPI1_CFG_EN_DEFAULT   1
#endif
//   <o>Mode selection
//       <0x0=> inactive
//       <0x10=> master ss unused
//       <0x11=> master
//       <0x20=> slave ss hw controlled
//       <0x21=> slave ss sw controlled
//   <i> Sets the SPI1 mode
//   <i> Default: master
#ifndef RTE_SPI1_MODE_DEFAULT
 #define RTE_SPI1_MODE_DEFAULT   0x21
#endif
//   <o>Speed selection <1000-10000000>
//   <i> Defines the SPI1 speed.
//   <i> The selected speed may not be achievable. Driver will set the closest speed by diving the sysclk by 2^N (N max = 9).
//   <i> Default: 750000
#ifndef RTE_SPI1_SPEED_DEFAULT
 #define RTE_SPI1_SPEED_DEFAULT   150000
#endif
//   <o>Clock polarity
//       <0x0=> normal
//       <0x2=> inverse
//   <i> Sets the SPI1 clock polarity
//   <i> Default: normal
#ifndef RTE_SPI1_POL_DEFAULT
 #define RTE_SPI1_POL_DEFAULT   0
#endif
//   <o>Word size
//       <0x8=> 8
//       <0x10=> 16
//       <0x18=> 24 (not supported in dma mode)
//       <0x20=> 32
//   <i> Sets the SPI1 word size
//   <i> Default: 8
#ifndef RTE_SPI1_WS_DEFAULT
 #define RTE_SPI1_WS_DEFAULT   8
#endif
// </e>

//   <o> SPI1_MOSI GPIO <0-15>
#ifndef RTE_SPI1_MOSI_PIN
 #define RTE_SPI1_MOSI_PIN                11
#endif

//   <o> SPI1_MISO GPIO <0-15>
#ifndef RTE_SPI1_MISO_PIN
 #define RTE_SPI1_MISO_PIN                12
#endif

//   <o> SPI1_SSEL GPIO <0-15>
#ifndef RTE_SPI1_SSEL_PIN
 #define RTE_SPI1_SSEL_PIN                13
#endif

//   <o> SPI1_SCLK GPIO <0-15>
#ifndef RTE_SPI1_SCLK_PIN
 #define RTE_SPI1_SCLK_PIN                14
#endif


//   <o RTE_SPI1_GPIO_LPF> SPI1 GPIO Low Pass Filter
//      <GPIO_LPF_DISABLE=>DISABLED <GPIO_LPF_ENABLE=>ENABLED
#define RTE_SPI1_GPIO_LPF                GPIO_LPF_DISABLE

//   <o RTE_SPI1_GPIO_DRIVE> SPI1 GPIO Drive Strength  <GPIO_LEVEL1_DRIVE=>Level 1
//      <GPIO_LEVEL2_DRIVE=>Level 2 <GPIO_LEVEL3_DRIVE=>Level 3
//      <GPIO_LEVEL4_DRIVE=>Level 4
#define RTE_SPI1_GPIO_DRIVE              GPIO_LEVEL1_DRIVE

//   <o RTE_SPI1_GPIO_PULL> SPI1 GPIO Pull Selection <GPIO_NO_PULL=>No pull
//      <GPIO_STRONG_PULL_UP=>Strong pull-up <GPIO_WEAK_PULL_UP=>Weak pull-up
//      <GPIO_WEAK_PULL_DOWN=>Weak pull-down
#define RTE_SPI1_GPIO_PULL               GPIO_WEAK_PULL_UP

// <e>SPI1 DMA control
// ===============================
//
//   <i> Enables dma control of spi1 module
//   <i> Default: 0
#ifndef RTE_SPI1_DMA_EN_DEFAULT
 #define RTE_SPI1_DMA_EN_DEFAULT       0
#endif
//   <o>SPI1 rx dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 2
#ifndef RTE_SPI1_RX_DMA_CH_DEFAULT
 #define RTE_SPI1_RX_DMA_CH_DEFAULT   2
#endif
//   <o>SPI1 tx dma channel selection
//       <0x0=> 0  <0x1=> 1
//       <0x2=> 2  <0x3=> 3
//   <i> Defines which dma channel should be used for data transfer (valid only if dma control was selected).
//   <i> Default: 3
#ifndef RTE_SPI1_TX_DMA_CH_DEFAULT
 #define RTE_SPI1_TX_DMA_CH_DEFAULT   3
#endif
// </e>
// </e>

// <e> GPIO Configuration
// =======================
//
//   <i> Defines if GPIO driver should be enabled.
//   <i> Default: 0
#ifndef RTE_GPIO
 #define RTE_GPIO     0
#endif
// <e>GPIO 0 configure
// ===============================
//
// <i> Enabled GPIO0 configuration
// <i> Default: 0
#ifndef RTE_GPIO0_EN
 #define RTE_GPIO0_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO0_DRIVE_DEFAULT
 #define RTE_GPIO0_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO0_LPF_DEFAULT
 #define RTE_GPIO0_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO0_PULL_DEFAULT
 #define RTE_GPIO0_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO0_IOMODE_DEFAULT
 #define RTE_GPIO0_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 1 configure
// ===============================
//
// <i> Enabled GPIO1 configuration
// <i> Default: 0
#ifndef RTE_GPIO1_EN
 #define RTE_GPIO1_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO1_DRIVE_DEFAULT
 #define RTE_GPIO1_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO1_LPF_DEFAULT
 #define RTE_GPIO1_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO1_PULL_DEFAULT
 #define RTE_GPIO1_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO1_IOMODE_DEFAULT
 #define RTE_GPIO1_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 2 configure
// ===============================
//
// <i> Enabled GPIO2 configuration
// <i> Default: 0
#ifndef RTE_GPIO2_EN
 #define RTE_GPIO2_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO2_DRIVE_DEFAULT
 #define RTE_GPIO2_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO2_LPF_DEFAULT
 #define RTE_GPIO2_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO2_PULL_DEFAULT
 #define RTE_GPIO2_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO2_IOMODE_DEFAULT
 #define RTE_GPIO2_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 3 configure
// ===============================
//
// <i> Enabled GPIO3 configuration
// <i> Default: 0
#ifndef RTE_GPIO3_EN
 #define RTE_GPIO3_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO3_DRIVE_DEFAULT
 #define RTE_GPIO3_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO3_LPF_DEFAULT
 #define RTE_GPIO3_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO3_PULL_DEFAULT
 #define RTE_GPIO3_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO3_IOMODE_DEFAULT
 #define RTE_GPIO3_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 4 configure
// ===============================
//
// <i> Enabled GPIO4 configuration
// <i> Default: 0
#ifndef RTE_GPIO4_EN
 #define RTE_GPIO4_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO4_DRIVE_DEFAULT
 #define RTE_GPIO4_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO4_LPF_DEFAULT
 #define RTE_GPIO4_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO4_PULL_DEFAULT
 #define RTE_GPIO4_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO4_IOMODE_DEFAULT
 #define RTE_GPIO4_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 5 configure
// ===============================
//
// <i> Enabled GPIO5 configuration
// <i> Default: 0
#ifndef RTE_GPIO5_EN
 #define RTE_GPIO5_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO5_DRIVE_DEFAULT
 #define RTE_GPIO5_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO5_LPF_DEFAULT
 #define RTE_GPIO5_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO5_PULL_DEFAULT
 #define RTE_GPIO5_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO5_IOMODE_DEFAULT
 #define RTE_GPIO5_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 6 configure
// ===============================
//
// <i> Enabled GPIO6 configuration
// <i> Default: 0
#ifndef RTE_GPIO6_EN
 #define RTE_GPIO6_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO6_DRIVE_DEFAULT
 #define RTE_GPIO6_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO6_LPF_DEFAULT
 #define RTE_GPIO6_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO6_PULL_DEFAULT
 #define RTE_GPIO6_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO6_IOMODE_DEFAULT
 #define RTE_GPIO6_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 7 configure
// ===============================
//
// <i> Enabled GPIO7 configuration
// <i> Default: 0
#ifndef RTE_GPIO7_EN
 #define RTE_GPIO7_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO7_DRIVE_DEFAULT
 #define RTE_GPIO7_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO7_LPF_DEFAULT
 #define RTE_GPIO7_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO7_PULL_DEFAULT
 #define RTE_GPIO7_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO7_IOMODE_DEFAULT
 #define RTE_GPIO7_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 8 configure
// ===============================
//
// <i> Enabled GPIO8 configuration
// <i> Default: 0
#ifndef RTE_GPIO8_EN
 #define RTE_GPIO8_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO8_DRIVE_DEFAULT
 #define RTE_GPIO8_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO8_LPF_DEFAULT
 #define RTE_GPIO8_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO8_PULL_DEFAULT
 #define RTE_GPIO8_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO8_IOMODE_DEFAULT
 #define RTE_GPIO8_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 9 configure
// ===============================
//
// <i> Enabled GPIO9 configuration
// <i> Default: 0
#ifndef RTE_GPIO9_EN
 #define RTE_GPIO9_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO9_DRIVE_DEFAULT
 #define RTE_GPIO9_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO9_LPF_DEFAULT
 #define RTE_GPIO9_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO9_PULL_DEFAULT
 #define RTE_GPIO9_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO9_IOMODE_DEFAULT
 #define RTE_GPIO9_IOMODE_DEFAULT   0x003
#endif
// </e>
// <e>GPIO 10 configure
// ===============================
//
// <i> Enabled GPIO10 configuration
// <i> Default: 0
#ifndef RTE_GPIO10_EN
 #define RTE_GPIO10_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO10_DRIVE_DEFAULT
 #define RTE_GPIO10_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO10_LPF_DEFAULT
 #define RTE_GPIO10_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO10_PULL_DEFAULT
 #define RTE_GPIO10_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO10_IOMODE_DEFAULT
 #define RTE_GPIO10_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 11 configure
// ===============================
//
// <i> Enabled GPIO11 configuration
// <i> Default: 0
#ifndef RTE_GPIO11_EN
 #define RTE_GPIO11_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO11_DRIVE_DEFAULT
 #define RTE_GPIO11_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO11_LPF_DEFAULT
 #define RTE_GPIO11_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO11_PULL_DEFAULT
 #define RTE_GPIO11_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO11_IOMODE_DEFAULT
 #define RTE_GPIO11_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 12 configure
// ===============================
//
// <i> Enabled GPIO12 configuration
// <i> Default: 0
#ifndef RTE_GPIO12_EN
 #define RTE_GPIO12_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO12_DRIVE_DEFAULT
 #define RTE_GPIO12_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO12_LPF_DEFAULT
 #define RTE_GPIO12_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO12_PULL_DEFAULT
 #define RTE_GPIO12_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO12_IOMODE_DEFAULT
 #define RTE_GPIO12_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 13 configure
// ===============================
//
// <i> Enabled GPIO13 configuration
// <i> Default: 0
#ifndef RTE_GPIO13_EN
 #define RTE_GPIO13_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO13_DRIVE_DEFAULT
 #define RTE_GPIO13_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO13_LPF_DEFAULT
 #define RTE_GPIO13_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO13_PULL_DEFAULT
 #define RTE_GPIO13_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO13_IOMODE_DEFAULT
 #define RTE_GPIO13_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 14 configure
// ===============================
//
// <i> Enabled GPIO14 configuration
// <i> Default: 0
#ifndef RTE_GPIO14_EN
 #define RTE_GPIO14_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO14_DRIVE_DEFAULT
 #define RTE_GPIO14_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO14_LPF_DEFAULT
 #define RTE_GPIO14_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO14_PULL_DEFAULT
 #define RTE_GPIO14_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO14_IOMODE_DEFAULT
 #define RTE_GPIO14_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e>GPIO 15 configure
// ===============================
//
// <i> Enabled GPIO15 configuration
// <i> Default: 0
#ifndef RTE_GPIO15_EN
 #define RTE_GPIO15_EN       0
#endif
//   <o>Drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the GPIO output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO15_DRIVE_DEFAULT
 #define RTE_GPIO15_DRIVE_DEFAULT   3
#endif
//   <o>Low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled
//   <i> Default: disable
#ifndef RTE_GPIO15_LPF_DEFAULT
 #define RTE_GPIO15_LPF_DEFAULT   0
#endif
//   <o>Pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the gpio pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO15_PULL_DEFAULT
 #define RTE_GPIO15_PULL_DEFAULT   1
#endif
//   <o>IO mode
//   <0x000=> DISABLED              <0x001=> INPUT                 <0x002=> GPIO_IN               <0x003=> GPIO_OUT
//   <0x004=> SLOWCLK_OUT           <0x005=> SYSCLK_OUT            <0x006=> USRCLK_OUT            <0x007=> RCCLK_OUT
//   <0x008=> JTCK_DIV_OUT          <0x009=> EXTCLK_DIV_OUT        <0x00A=> RFCLK_OUT             <0x00B=> STANDBYCLK_OUT
//   <0x00C=> SENSORCLK_OUT         <0x00D=> SPI0_IO0              <0x00E=> SPI0_IO1              <0x00F=> SPI0_IO2
//   <0x010=> SPI0_IO3              <0x011=> SPI0_CS_OUT           <0x012=> SPI0_CLK_OUT          <0x013=> SPI1_IO0
//   <0x014=> SPI1_IO1              <0x015=> SPI1_IO2              <0x016=> SPI1_IO3              <0x017=> USPI1_CS_OUT
//   <0x018=> SPI1_CLK_OUT          <0x019=> UART0_TX0_OUT         <0x01A=> I2C0_SCL_OUT          <0x01B=> I2C0_SDA_OUT
//   <0x01C=> I2C1_SCL_OUT          <0x01D=> I2C1_SDA_OUT          <0x01E=> PCM0_SERO_OUT         <0x01F=> PCM0_FRAME_OUT
//   <0x020=> PWM0_OUT              <0x021=> PWM1_OUT              <0x022=> PWM2_OUT              <0x023=> PWM3_OUT
//   <0x024=> PWM4_OUT              <0x025=> PWM0_INV_OUT          <0x026=> PWM1_INV_OUT          <0x027=> PWM2_INV_OUT
//   <0x028=> PWM3_INV_OUT          <0x029=> PWM4_INV_OUT          <0x02A=> LIN0_TX_OUT           <0x02B=> BB_TX_DATA_OUT
//   <0x02C=> BB_TX_DATA_VALID_OUT  <0x02D=> BB_SPI_CSN_OUT        <0x02E=> BB_SPI_CLK_OUT        <0x02F=> BB_SPI_MOSI_OUT
//   <0x030=> BB_DBG0_0_OUT         <0x031=> BB_DBG0_1_OUT         <0x032=> BB_DBG0_2_OUT         <0x033=> BB_DBG0_3_OUT
//   <0x034=> BB_DBG0_4_OUT         <0x035=> BB_DBG0_5_OUT         <0x036=> BB_DBG0_6_OUT         <0x037=> BB_DBG0_7_OUT
//   <0x038=> BB_BLE_SYNC           <0x039=> BB_BLE_IN_PROCESS     <0x03A=> BB_BLE_TX             <0x03B=> BB_BLE_RX
//   <0x03C=> BB_BLE_PTI_0          <0x03D=> BB_BLE_PTI_1          <0x03E=> BB_BLE_PTI_2          <0x03F=> BB_BLE_PTI_3
//   <0x040=> BB_ANT_SW_EN          <0x041=> BB_ANT_SW_0           <0x042=> BB_ANT_SW_1           <0x043=> BB_ANT_SW_2
//   <0x044=> BB_ANT_SW_3           <0x045=> BB_ANT_SW_4           <0x046=> BB_ANT_SW_5           <0x047=> BB_ANT_SW_6
//   <0x048=> BB_CTE_MODE           <0x049=> BB_CTE_SAMPLE_P       <0x04A=> RF_SPI_MISO_OUT       <0x04B=> RF_GPIO0_OUT
//   <0x04C=> RF_GPIO1_OUT          <0x04D=> RF_GPIO2_OUT          <0x04E=> RF_GPIO3_OUT          <0x04F=> RF_GPIO4_OUT
//   <0x050=> RF_GPIO5_OUT          <0x051=> RF_GPIO6_OUT          <0x052=> RF_GPIO7_OUT          <0x053=> RF_GPIO8_IN
//   <0x054=> RF_GPIO9_IN           <0x055=> RF_IQ_DATA_P_OUT      <0x056=> RF_I_DATA_0_OUT       <0x057=> RF_I_DATA_1_OUT
//   <0x058=> RF_I_DATA_2_OUT       <0x059=> RF_I_DATA_3_OUT       <0x05A=> RF_I_DATA_4_OUT       <0x05B=> RF_I_DATA_5_OUT
//   <0x05C=> RF_I_DATA_6_OUT       <0x05D=> RF_I_DATA_7_OUT       <0x05E=> RF_Q_DATA_0_OUT       <0x05F=> RF_Q_DATA_1_OUT
//   <0x060=> RF_Q_DATA_2_OUT       <0x061=> RF_Q_DATA_3_OUT       <0x062=> RF_Q_DATA_4_OUT       <0x063=> RF_Q_DATA_5_OUT
//   <0x064=> RF_Q_DATA_6_OUT       <0x065=>RF_Q_DATA_7_OUT        <0x066=> RF_ANT_SW_0_OUT       <0x067=> RF_ANT_SW_1_OUT
//   <0x068=> RF_ANT_SW_2_OUT       <0x069=> RF_ANT_SW_3_OUT       <0x06A=> TOF_START_OUT         <0x06B=> RTOF_STOP_OUT
//   <0x100=> PCM_SERI_IN           <0x101=> PCM_FRAME_IN          <0x102=> PCM_FRAME_OUT         <0x103=> PCM_CLK_IN
//   <0x200=> SPI0_CS_IN            <0x201=> SPI0_CLK_IN           <0x202=> SPI1_CS_IN            <0x203=> SPI1_CLK_IN
//   <0x300=> UART_RX_IN            <0x400=> I2C0_SCL_IN           <0x401=> I2C0_SDA_IN           <0x402=> I2C1_SCL_IN
//   <0x403=>I2C1_SDA_IN            <0x500=> NMI_IN                <0x600=> BB_RX_CLK_IN          <0x601=> BB_RX_DATA_IN
//   <0x602=> BB_SYNC_P_IN          <0x603=> BB_SPI_MISO_IN        <0x700=> RF_SPI_MOSI_IN        <0x701=> RF_SPI_CSN_IN
//   <0x702=> RF_SPI_CLK_IN         <0x800=> RF_GPIO0_IN           <0x801=> RF_GPIO1_IN           <0x802=> RF_GPIO2_IN
//   <0x803=> RF_GPIO3_IN           <0x804=> RF_GPIO4_IN           <0x805=> RF_GPIO5_IN           <0x806=> RF_GPIO6_IN
//   <0x807=> RF_GPIO7_IN           <0x808=> RF_GPIO8_IN           <0x809=> RF_GPIO9_IN           <0x80A=> ADC_IN
//   <i> Defines the io mode
//   <i> Default: DISABLED
#ifndef RTE_GPIO15_IOMODE_DEFAULT
 #define RTE_GPIO15_IOMODE_DEFAULT   0x000
#endif
// </e>
// <e> GPIO 0 interrupt enable
// ===============================
//
// <i> Enables GPIO0 interrupt.
// <i> Default: 1
#ifndef RTE_GPIO_GPIO0_INT_EN
 #define RTE_GPIO_GPIO0_INT_EN       0
#endif
//   <o>Interrupt source
//       <0x0=> GPIO 0   <0x1=> GPIO 1   <0x2=> GPIO 2   <0x3=> GPIO 3
//       <0x4=> GPIO 4   <0x5=> GPIO 5   <0x6=> GPIO 6   <0x7=> GPIO 7
//       <0x8=> GPIO 8   <0x9=> GPIO 9   <0xA=> GPIO 10  <0xB=> GPIO 11
//       <0xC=> GPIO 12  <0xD=> GPIO 13  <0xE=> GPIO 14  <0xF=> GPIO 15
//   <i> Defines the GPIO0 interrupt source
//   <i> Default: GPIO 0
#ifndef RTE_GPIO_GPIO0_SRC_DEFAULT
 #define RTE_GPIO_GPIO0_SRC_DEFAULT   0
#endif
//   <o>Trigger event
//       <0x0=> none           <0x1=> high level      <0x2=> low level
//       <0x3=> rising edge    <0x4=> falling edge    <0x5=> transition
//   <i> Defines the interrupt trigger event
//   <i> Default: rising edge
#ifndef RTE_GPIO_GPIO0_TRG_DEFAULT
 #define RTE_GPIO_GPIO0_TRG_DEFAULT   4
#endif
//   <o>Debounce filter
//       <0x0=> disabled
//       <0x1=> enabled
//   <i> Defines if debounce filter should be enabled
//   <i> Default: disabled
#ifndef RTE_GPIO_GPIO0_DBC_DEFAULT
 #define RTE_GPIO_GPIO0_DBC_DEFAULT   0
#endif
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO0_INT_PREEMPT_PRI
 #define RTE_GPIO_GPIO0_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO0_INT_SUBGRP_PRI
 #define RTE_GPIO_GPIO0_INT_SUBGRP_PRI   0
#endif
// </e>
// <e> GPIO 1 interrupt enable
// ===============================
//
// <i> Enables GPIO1 interrupt.
// <i> Default: 1
#ifndef RTE_GPIO_GPIO1_INT_EN
 #define RTE_GPIO_GPIO1_INT_EN       0
#endif
//   <o>Interrupt source
//       <0x0=> GPIO 0   <0x1=> GPIO 1   <0x2=> GPIO 2   <0x3=> GPIO 3
//       <0x4=> GPIO 4   <0x5=> GPIO 5   <0x6=> GPIO 6   <0x7=> GPIO 7
//       <0x8=> GPIO 8   <0x9=> GPIO 9   <0xA=> GPIO 10  <0xB=> GPIO 11
//       <0xC=> GPIO 12  <0xD=> GPIO 13  <0xE=> GPIO 14  <0xF=> GPIO 15
//   <i> Defines the GPIO1 interrupt source
//   <i> Default: GPIO 1
#ifndef RTE_GPIO_GPIO1_SRC_DEFAULT
 #define RTE_GPIO_GPIO1_SRC_DEFAULT   1
#endif
//   <o>Trigger event
//       <0x0=> none           <0x1=> high level      <0x2=> low level
//       <0x3=> rising edge    <0x4=> falling edge    <0x5=> transition
//   <i> Defines the interrupt trigger event
//   <i> Default: rising edge
#ifndef RTE_GPIO_GPIO1_TRG_DEFAULT
 #define RTE_GPIO_GPIO1_TRG_DEFAULT   3
#endif
//   <o>Debounce filter
//       <0x0=> disabled
//       <0x1=> enabled
//   <i> Defines if debounce filter should be enabled
//   <i> Default: disabled
#ifndef RTE_GPIO_GPIO1_DBC_DEFAULT
 #define RTE_GPIO_GPIO1_DBC_DEFAULT   0
#endif
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO1_INT_PREEMPT_PRI
 #define RTE_GPIO_GPIO1_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO1_INT_SUBGRP_PRI
 #define RTE_GPIO_GPIO1_INT_SUBGRP_PRI   0
#endif
// </e>
// <e> GPIO 2 interrupt enable
// ===============================
//
// <i> Enables GPIO1 interrupt.
// <i> Default: 1
#ifndef RTE_GPIO_GPIO2_INT_EN
 #define RTE_GPIO_GPIO2_INT_EN       0
#endif
//   <o>Interrupt source
//       <0x0=> GPIO 0   <0x1=> GPIO 1   <0x2=> GPIO 2   <0x3=> GPIO 3
//       <0x4=> GPIO 4   <0x5=> GPIO 5   <0x6=> GPIO 6   <0x7=> GPIO 7
//       <0x8=> GPIO 8   <0x9=> GPIO 9   <0xA=> GPIO 10  <0xB=> GPIO 11
//       <0xC=> GPIO 12  <0xD=> GPIO 13  <0xE=> GPIO 14  <0xF=> GPIO 15
//   <i> Defines the GPIO2 interrupt source
//   <i> Default: GPIO 2
#ifndef RTE_GPIO_GPIO2_SRC_DEFAULT
 #define RTE_GPIO_GPIO2_SRC_DEFAULT   2
#endif
//   <o>Trigger event
//       <0x0=> none           <0x1=> high level      <0x2=> low level
//       <0x3=> rising edge    <0x4=> falling edge    <0x5=> transition
//   <i> Defines the interrupt trigger event
//   <i> Default: rising edge
#ifndef RTE_GPIO_GPIO2_TRG_DEFAULT
 #define RTE_GPIO_GPIO2_TRG_DEFAULT   3
#endif
//   <o>Debounce filter
//       <0x0=> disabled
//       <0x1=> enabled
//   <i> Defines if debounce filter should be enabled
//   <i> Default: disabled
#ifndef RTE_GPIO_GPIO2_DBC_DEFAULT
 #define RTE_GPIO_GPIO2_DBC_DEFAULT   0
#endif
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO2_INT_PREEMPT_PRI
 #define RTE_GPIO_GPIO2_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO2_INT_SUBGRP_PRI
 #define RTE_GPIO_GPIO2_INT_SUBGRP_PRI   0
#endif
// </e>
// <e> GPIO 3 interrupt enable
// ===============================
//
// <i> Enables GPIO3 interrupt.
// <i> Default: 1
#ifndef RTE_GPIO_GPIO3_INT_EN
 #define RTE_GPIO_GPIO3_INT_EN       0
#endif
//   <o>Interrupt source
//       <0x0=> GPIO 0   <0x1=> GPIO 1   <0x2=> GPIO 2   <0x3=> GPIO 3
//       <0x4=> GPIO 4   <0x5=> GPIO 5   <0x6=> GPIO 6   <0x7=> GPIO 7
//       <0x8=> GPIO 8   <0x9=> GPIO 9   <0xA=> GPIO 10  <0xB=> GPIO 11
//       <0xC=> GPIO 12  <0xD=> GPIO 13  <0xE=> GPIO 14  <0xF=> GPIO 15
//   <i> Defines the GPIO3 interrupt source
//   <i> Default: GPIO 3
#ifndef RTE_GPIO_GPIO3_SRC_DEFAULT
 #define RTE_GPIO_GPIO3_SRC_DEFAULT   3
#endif
//   <o>Trigger event
//       <0x0=> none           <0x1=> high level      <0x2=> low level
//       <0x3=> rising edge    <0x4=> falling edge    <0x5=> transition
//   <i> Defines the interrupt trigger event
//   <i> Default: rising edge
#ifndef RTE_GPIO_GPIO3_TRG_DEFAULT
 #define RTE_GPIO_GPIO3_TRG_DEFAULT   3
#endif
//   <o>Debounce filter
//       <0x0=> disabled
//       <0x1=> enabled
//   <i> Defines if debounce filter should be enabled
//   <i> Default: disabled
#ifndef RTE_GPIO_GPIO3_DBC_DEFAULT
 #define RTE_GPIO_GPIO3_DBC_DEFAULT   0
#endif
//   <o>Pre-empt priority <0-0x7>
//   <i> Defines the pre-empt priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO3_INT_PREEMPT_PRI
 #define RTE_GPIO_GPIO3_INT_PREEMPT_PRI   0
#endif
//   <o>Subgroup priority <0-0x7>
//   <i> Defines the subgroup priority
//   <i> Default: 0
#ifndef RTE_GPIO_GPIO3_INT_SUBGRP_PRI
 #define RTE_GPIO_GPIO3_INT_SUBGRP_PRI   0
#endif
// </e>
// <h>Interrupt debounce configuration
// ===============================
//
//   <o>Debounce clock source
//       <0x0=> slow clock / 32
//       <0x1=> slow clock / 1024
//   <i> Defines the debouce filter clock soruce
//   <i> Default: slow clock / 32
#ifndef RTE_GPIO_INT_DBC_CLK_SRC_DEFAULT
 #define RTE_GPIO_INT_DBC_CLK_SRC_DEFAULT   1
#endif
//   <o>Debounce filter count <0-0xFF>
//   <i> Defines debounce filter count
//   <i> Default: 10
#ifndef RTE_GPIO_INT_DBC_CNT_DEFAULT
 #define RTE_GPIO_INT_DBC_CNT_DEFAULT   10
#endif
// </h>
// <h>SW JTAG PAD configuration
// ===============================
//
// <i>SW JTAG Debug Port PAD configuration
#ifndef RTE_GPIO_JTAG_EN
 #define RTE_GPIO_JTAG_EN       1
#endif
//   <o>SWD/JTAG debug port selection
//       <0x0=> SWD
//       <0x1=> JTAG
//   <i> Selects either SWD or JTAG debug port
//   <i> If JTAG is selected, GPIOs 2 and 3 will be dedicated to JTDI and JTDO, respectively, and must not be used by the application.
//   <i> JTRST is connected with NRESET (GPIO 4 can be used by the application)
//   <i> Default: SWD
#ifndef RTE_GPIO_JTAG_DATA_DEFAULT
 #define RTE_GPIO_JTAG_DATA_DEFAULT   0
#endif
//   <o>SWCLK/JTCK low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled for SWCLK/JTCK
//   <i> Default: disable
#ifndef RTE_GPIO_JTCK_LPF_DEFAULT
 #define RTE_GPIO_JTCK_LPF_DEFAULT   0
#endif
//   <o>SWCLK/JTCK pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the SWCLK/JTCK pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO_JTCK_PULL_DEFAULT
 #define RTE_GPIO_JTCK_PULL_DEFAULT   1
#endif
//   <o>SWDIO/JTMS low pass filter
//       <0x0=> disable
//       <0x1=> enable
//   <i> Defines if low pass filter should be enabled for SWDIO/JTMS
//   <i> Default: disable
#ifndef RTE_GPIO_JTMS_LPF_DEFAULT
 #define RTE_GPIO_JTMS_LPF_DEFAULT   0
#endif
//   <o>SWDIO/JTMS pull control
//       <0x0=> no pull
//       <0x1=> weak pull up
//       <0x2=> weak pull down
//       <0x3=> strong pull up
//   <i> Defines the SWDIO/JTMS pull configuration
//   <i> Default: weak pull up
#ifndef RTE_GPIO_JTMS_PULL_DEFAULT
 #define RTE_GPIO_JTMS_PULL_DEFAULT   1
#endif
//   <o>SWDIO/JTMS drive strength
//       <0x0=> 2x drive strength
//       <0x1=> 3x drive strength
//       <0x2=> 5x drive strength
//       <0x3=> 6x drive strength
//   <i> Defines the SWDIO/JTMS output strength
//   <i> Default: 6x drive strength
#ifndef RTE_GPIO_JTMS_DRIVE_DEFAULT
 #define RTE_GPIO_JTMS_DRIVE_DEFAULT   3
#endif
// </h>
// </e>
#ifndef RTE_GPIO_JTAG_TRST_DEFAULT
 #define RTE_GPIO_JTAG_TRST_DEFAULT   0
#endif
// <h> GPIO Assignment
// =======================
//   <i> Assigns specified GPIO pin numbers to macros
//
// <o>GREEN_LED <0-15>
// ===============================
//
//   <i> Assigns specified pin number to GREEN_LED
#ifndef GREEN_LED
 #define GREEN_LED       8
#endif
// <o>BLUE_LED <0-15>
// ===============================
//
//   <i> Assigns specified pin number to BLUE_LED
#ifndef BLUE_LED
 #define BLUE_LED       10
#endif
// </h>
#endif    /* RTE_DEVICE_H */
