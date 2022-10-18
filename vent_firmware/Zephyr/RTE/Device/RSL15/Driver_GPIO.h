/**
 * @file Driver_GPIO.h
 * @brief GPIO Driver implementation
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

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

 /** @addtogroup CMSISDRVg
 *  @{
 */
/**
 * @defgroup CMSISDRVGPIOg CMSIS GPIO Driver
 * @brief CMSIS GPIO Driver Reference
 * @{
 */
 
#ifdef  __cplusplus
extern "C"
{
#endif

#include <Driver_Common.h>

#define ARM_GPIO_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  ///< GPIO API version 

/****** GPIO Control Codes *****/

/** GPIO Control Codes: GPIO Selection */
typedef enum _GPIO_SEL_t {
    GPIO_0                          = 0x0,            ///< GPIO pad 0  
    GPIO_1                          = 0x1,            ///< GPIO pad 1  
    GPIO_2                          = 0x2,            ///< GPIO pad 2  
    GPIO_3                          = 0x3,            ///< GPIO pad 3  
    GPIO_4                          = 0x4,            ///< GPIO pad 4  
    GPIO_5                          = 0x5,            ///< GPIO pad 5  
    GPIO_6                          = 0x6,            ///< GPIO pad 6  
    GPIO_7                          = 0x7,            ///< GPIO pad 7  
    GPIO_8                          = 0x8,            ///< GPIO pad 8  
    GPIO_9                          = 0x9,            ///< GPIO pad 9  
    GPIO_10                         = 0xA,            ///< GPIO pad 10 
    GPIO_11                         = 0xB,            ///< GPIO pad 11 
    GPIO_12                         = 0xC,            ///< GPIO pad 12 
    GPIO_13                         = 0xD,            ///< GPIO pad 13 
    GPIO_14                         = 0xE,            ///< GPIO pad 14 
    GPIO_15                         = 0xF             ///< GPIO pad 15 
} GPIO_SEL_t;

/** GPIO Control Codes: GPIO direction */
typedef enum _GPIO_DIR_t {
	GPIO_DIR_IN                            = 0x0,            ///< GPIO direction input     
    GPIO_DIR_OUT_0                         = 0x1,            ///< GPIO direction output 0  
    GPIO_DIR_OUT_1                         = 0x2,            ///< GPIO direction output 1  
    GPIO_DIR_OUT_2                         = 0x4,            ///< GPIO direction output 2  
    GPIO_DIR_OUT_3                         = 0x8,            ///< GPIO direction output 3  
    GPIO_DIR_OUT_4                         = 0x10,           ///< GPIO direction output 4  
    GPIO_DIR_OUT_5                         = 0x20,           ///< GPIO direction output 5  
    GPIO_DIR_OUT_6                         = 0x40,           ///< GPIO direction output 6  
    GPIO_DIR_OUT_7                         = 0x80,           ///< GPIO direction output 7  
    GPIO_DIR_OUT_8                         = 0x100,          ///< GPIO direction output 8  
    GPIO_DIR_OUT_9                         = 0x200,          ///< GPIO direction output 9  
    GPIO_DIR_OUT_10                        = 0x400,          ///< GPIO direction output 10  
    GPIO_DIR_OUT_11                        = 0x800,          ///< GPIO direction output 11  
    GPIO_DIR_OUT_12                        = 0x1000,         ///< GPIO direction output 12  
    GPIO_DIR_OUT_13                        = 0x2000,         ///< GPIO direction output 13  
    GPIO_DIR_OUT_14                        = 0x4000,         ///< GPIO direction output 14  
    GPIO_DIR_OUT_15                        = 0x8000          ///< GPIO direction output 15  
} GPIO_DIR_t;

/** GPIO Control Codes: GPIO INT Selection */
typedef enum _GPIO_INT_SEL_t {
    GPIO_INT_0                      = 0x0,            ///< GPIO interrupt 0 
    GPIO_INT_1                      = 0x1,            ///< GPIO interrupt 1 
    GPIO_INT_2                      = 0x2,            ///< GPIO interrupt 2 
    GPIO_INT_3                      = 0x3,            ///< GPIO interrupt 3 
} GPIO_INT_SEL_t;

/** GPIO Control Codes: Drive strength */
typedef enum _GPIO_DRIVE_t {
    GPIO_2X                         = 0x0,           ///< 2x drive strength 
    GPIO_3X                         = 0x1,           ///< 3x drive strength 
    GPIO_5X                         = 0x2,           ///< 5x drive strength 
    GPIO_6X                         = 0x3            ///< 6x drive strength 
} GPIO_DRIVE_t;

/** GPIO Control Codes: Low pass filter */
typedef enum _GPIO_LPF_t {
    GPIO_LPF_DISABLED                = 0x0,           ///< Low pass filter disabled 
    GPIO_LPF_ENABLED                 = 0x1            ///< Low pass filter enabled  
} GPIO_LPF_t;

/** GPIO Control Codes: Pull control */
typedef enum _GPIO_PULL_t {
    GPIO_PC_NO_PULL                    = 0x0,           ///< No pull selected        
    GPIO_PC_WEAK_PULL_UP               = 0x1,           ///< Weak pull-up selected   
    GPIO_PC_WEAK_PULL_DOWN             = 0x2,           ///< Weak pull-down selected 
    GPIO_PC_STRONG_PULL_UP             = 0x3            ///< Strong pull-up selected 
} GPIO_PULL_t;

/** GPIO Control Codes: IO Mode */
typedef enum _GPIO_MODE_t {
MODE_GPIO_DISABLE               = 0x000,
MODE_GPIO_INPUT                 = 0x001,
MODE_GPIO_GPIO_IN               = 0x002,
MODE_GPIO_GPIO_OUT              = 0x003,
MODE_GPIO_SLOWCLK               = 0x004,
MODE_GPIO_SYSCLK                = 0x005,
MODE_GPIO_USRCLK                = 0x006,
MODE_GPIO_RCCLK                 = 0x007,
MODE_GPIO_SWCLK_DIV             = 0x008,
MODE_GPIO_EXTCLK_DIV            = 0x009,
MODE_GPIO_RFCLK                 = 0x00A,
MODE_GPIO_STANDBYCLK            = 0x00B,
MODE_GPIO_SENSORCLK             = 0x00C,
MODE_GPIO_SPI0_IO0              = 0x00D,
MODE_GPIO_SPI0_IO1              = 0x00E,
MODE_GPIO_SPI0_IO2              = 0x00F,
MODE_GPIO_SPI0_IO3              = 0x010,
MODE_GPIO_SPI0_CS               = 0x011,
MODE_GPIO_SPI0_CLK              = 0x012,
MODE_GPIO_SPI1_IO0              = 0x013,
MODE_GPIO_SPI1_IO1              = 0x014,
MODE_GPIO_SPI1_IO2              = 0x015,
MODE_GPIO_SPI1_IO3              = 0x016,
MODE_GPIO_SPI1_CS               = 0x017,
MODE_GPIO_SPI1_CLK              = 0x018,
MODE_GPIO_UART0_TX              = 0x019,
MODE_GPIO_I2C0_SCL              = 0x01A,
MODE_GPIO_I2C0_SDA              = 0x01B,
MODE_GPIO_I2C1_SCL              = 0x01C,
MODE_GPIO_I2C1_SDA              = 0x01D,
MODE_GPIO_PCM0_SERO             = 0x01E,
MODE_GPIO_PCM0_FRAME            = 0x01F,
MODE_GPIO_PWM0                  = 0x020,
MODE_GPIO_PWM1                  = 0x021,
MODE_GPIO_PWM2                  = 0x022,
MODE_GPIO_PWM3                  = 0x023,
MODE_GPIO_PWM4                  = 0x024,
MODE_GPIO_PWM0_INV              = 0x025,
MODE_GPIO_PWM1_INV              = 0x026,
MODE_GPIO_PWM2_INV              = 0x027,
MODE_GPIO_PWM3_INV              = 0x028,
MODE_GPIO_PWM4_INV              = 0x029,
MODE_GPIO_LIN0_TX               = 0x02A,
MODE_GPIO_BB_TX_DATA            = 0x02B,
MODE_GPIO_BB_TX_DATA_VALID      = 0x02C,
MODE_GPIO_BB_SPI_CSN            = 0x02D,
MODE_GPIO_BB_SPI_CLK            = 0x02E,
MODE_GPIO_BB_SPI_MOSI           = 0x02F,
MODE_GPIO_BB_DBG_0              = 0x030,
MODE_GPIO_BB_DBG_1              = 0x031,
MODE_GPIO_BB_DBG_2              = 0x032,
MODE_GPIO_BB_DBG_3              = 0x033,
MODE_GPIO_BB_DBG_4              = 0x034,
MODE_GPIO_BB_DBG_5              = 0x035,
MODE_GPIO_BB_DBG_6              = 0x036,
MODE_GPIO_BB_DBG_7              = 0x037,
MODE_GPIO_BB_BLE_SYNC           = 0x038,
MODE_GPIO_BB_BLE_IN_PROCESS     = 0x039,
MODE_GPIO_BB_BLE_TX             = 0x03A,
MODE_GPIO_BB_BLE_RX             = 0x03B,
MODE_GPIO_BB_BLE_PTI_0          = 0x03C,
MODE_GPIO_BB_BLE_PTI_1          = 0x03D,
MODE_GPIO_BB_BLE_PTI_2          = 0x03E,
MODE_GPIO_BB_BLE_PTI_3          = 0x03F,
MODE_GPIO_BB_ANT_SW_EN          = 0x040,
MODE_GPIO_BB_ANT_SW_0           = 0x041,
MODE_GPIO_BB_ANT_SW_1           = 0x042,
MODE_GPIO_BB_ANT_SW_2           = 0x043,
MODE_GPIO_BB_ANT_SW_3           = 0x044,
MODE_GPIO_BB_ANT_SW_4           = 0x045,
MODE_GPIO_BB_ANT_SW_5           = 0x046,
MODE_GPIO_BB_ANT_SW_6           = 0x047,
MODE_GPIO_BB_CTE_MODE           = 0x048,
MODE_GPIO_BB_CTE_SAMPLE_P       = 0x049,
MODE_GPIO_RF_SPI_MISO           = 0x04A,
MODE_GPIO_RF_GPIO0              = 0x04B,
MODE_GPIO_RF_GPIO1              = 0x04C,
MODE_GPIO_RF_GPIO2              = 0x04D,
MODE_GPIO_RF_GPIO3              = 0x04E,
MODE_GPIO_RF_GPIO4              = 0x04F,
MODE_GPIO_RF_GPIO5              = 0x050,
MODE_GPIO_RF_GPIO6              = 0x051,
MODE_GPIO_RF_GPIO7              = 0x052,
MODE_GPIO_RF_GPIO8              = 0x053,
MODE_GPIO_RF_GPIO9              = 0x054,
MODE_GPIO_RF_IQ_DATA_P          = 0x055,
MODE_GPIO_RF_I_DATA_0           = 0x056,
MODE_GPIO_RF_I_DATA_1           = 0x057,
MODE_GPIO_RF_I_DATA_2           = 0x058,
MODE_GPIO_RF_I_DATA_3           = 0x059,
MODE_GPIO_RF_I_DATA_4           = 0x05A,
MODE_GPIO_RF_I_DATA_5           = 0x05B,
MODE_GPIO_RF_I_DATA_6           = 0x05C,
MODE_GPIO_RF_I_DATA_7           = 0x05D,
MODE_GPIO_RF_Q_DATA_0           = 0x05E,
MODE_GPIO_RF_Q_DATA_1           = 0x05F,
MODE_GPIO_RF_Q_DATA_2           = 0x060,
MODE_GPIO_RF_Q_DATA_3           = 0x061,
MODE_GPIO_RF_Q_DATA_4           = 0x062,
MODE_GPIO_RF_Q_DATA_5           = 0x063,
MODE_GPIO_RF_Q_DATA_6           = 0x064,
MODE_GPIO_RF_Q_DATA_7           = 0x065,
MODE_GPIO_RF_ANT_SW_0           = 0x066,
MODE_GPIO_RF_ANT_SW_1           = 0x067,
MODE_GPIO_RF_ANT_SW_2           = 0x068,
MODE_GPIO_RF_ANT_SW_3           = 0x069,
MODE_GPIO_TOF_START             = 0x06A,
MODE_GPIO_TOF_STOP              = 0x06B,
MODE_GPIO_PCM_SERI_IN           = 0x100,
MODE_GPIO_PCM_FRAME_IN          = 0x101,
MODE_GPIO_PCM_FRAME_OUT         = 0x102,
MODE_GPIO_PCM_CLK_IN            = 0x103,
MODE_GPIO_SPI0_CS_IN            = 0x200,
MODE_GPIO_SPI0_CLK_IN           = 0x201,
MODE_GPIO_SPI1_CS_IN            = 0x202,
MODE_GPIO_SPI1_CLK_IN           = 0x203,
MODE_GPIO_UART_RX_IN            = 0x300,
MODE_GPIO_I2C0_SCL_IN           = 0x400,
MODE_GPIO_I2C0_SDA_IN           = 0x401,
MODE_GPIO_I2C1_SCL_IN           = 0x402,
MODE_GPIO_I2C1_SDA_IN           = 0x403,
MODE_GPIO_NMI_IN                = 0x500,
MODE_GPIO_BB_RX_CLK_IN          = 0x600,
MODE_GPIO_BB_RX_DATA_IN         = 0x601,
MODE_GPIO_BB_SYNC_P_IN          = 0x602,
MODE_GPIO_BB_SPI_MISO_IN        = 0x603,
MODE_GPIO_RF_SPI_MOSI_IN        = 0x700,
MODE_GPIO_RF_SPI_CSN_IN         = 0x701,
MODE_GPIO_RF_SPI_CLK_IN         = 0x702,
MODE_GPIO_RF_GPIO0_IN           = 0x800,
MODE_GPIO_RF_GPIO1_IN           = 0x801,
MODE_GPIO_RF_GPIO2_IN           = 0x802,
MODE_GPIO_RF_GPIO3_IN           = 0x803,
MODE_GPIO_RF_GPIO4_IN           = 0x804,
MODE_GPIO_RF_GPIO5_IN           = 0x805,
MODE_GPIO_RF_GPIO6_IN           = 0x806,
MODE_GPIO_RF_GPIO7_IN           = 0x807,
MODE_GPIO_RF_GPIO8_IN           = 0x808,
MODE_GPIO_RF_GPIO9_IN           = 0x809,
MODE_GPIO_ADC_IN                = 0x80A
} GPIO_MODE_t;

/** GPIO Control Codes: GPIO alternative function registers */
typedef enum _GPIO_FUNC_REGISTERS_t {
    GPIO_FUNC_REG_SPI0              = 0x00,          ///< SPI 0 register       
    GPIO_FUNC_REG_SPI1              = 0x01,          ///< SPI 1 register       
    GPIO_FUNC_REG_UART0             = 0x03,          ///< UART register        
    GPIO_FUNC_REG_I2C0              = 0x04,          ///< I2C 0 register       
    GPIO_FUNC_REG_I2C1              = 0x05,          ///< I2C 1 register       
    GPIO_FUNC_REG_PCM0              = 0x06,          ///< PCM register         
    GPIO_FUNC_REG_NMI               = 0x07,          ///< NMI register         
    GPIO_FUNC_REG_BB_RX             = 0x08,          ///< BB RX register       
    GPIO_FUNC_REG_BB_SPI            = 0x09,          ///< BB SPI register      
    GPIO_FUNC_REG_RF_SPI            = 0x0A,          ///< RF SPI register      
    GPIO_FUNC_REG_RF_GPIO03         = 0x0B,          ///< RF GPIO03 register   
    GPIO_FUNC_REG_RF_GPIO47         = 0x0C,          ///< RF GPIO47 register   
    GPIO_FUNC_REG_RF_GPIO89         = 0x0D,          ///< RF GPIO89 register   
    GPIO_FUNC_REG_JTAG_SW_PAD       = 0x0E           ///< JTAG SW pad register 
} GPIO_FUNC_REGISTERS_t;

/** GPIO Control Codes: Enable / Disable values */
typedef enum _GPIO_EN_DIS_t {
    GPIO_DISABLE                    = 0,             ///< GPIO disable value 
    GPIO_ENABLE                     = 1              ///< GPIO enable value  
} GPIO_EN_DIS_t;


/** GPIO Control Codes: Interrupts events */
typedef enum _GPIO_EVENT_t {
    GPIO_IN_EVENT_NONE                 = 0,             ///< Interrupt event none         
    GPIO_IN_EVENT_HIGH_LEVEL           = 1,             ///< Interrupt event high level   
    GPIO_IN_EVENT_LOW_LEVEL            = 2,             ///< Interrupt event low level    
    GPIO_IN_EVENT_RISING_EDGE          = 3,             ///< Interrupt event rising edge  
    GPIO_IN_EVENT_FALLING_EDGE         = 4,             ///< Interrupt event falling edge 
    GPIO_IN_EVENT_TRANSITION           = 5              ///< Interrupt event transition   
} GPIO_EVENT_t;

/** GPIO Control Codes: Debounce clock source */
typedef enum _GPIO_DBC_CLK_t {
    GPIO_DBC_CLK_SLOWCLK_DIV32      = 0,             ///< Debounce clock source = slow clock / 32   
    GPIO_DBC_CLK_SLOWCLK_DIV1024    = 1              ///< Debounce clock source = slow clock / 1024 
} GPIO_DBC_CLK_t;

/** GPIO Control Codes: Pads strength */
typedef enum _GPIO_DRIVE_STRENGTHS_t {
    GPIO_LOW_DRIVE                  = 0,             ///< Regular drive strengths           
    GPIO_HIGH_DRIVE                 = 1              ///< Drive strengths increased by ~50% 
} GPIO_DRIVE_STRENGTHS_t;

/** GPIO Event */
#define GPIO_EVENT_0_IRQ   (1UL << 0)                ///< GPIO0 interrupt event value
#define GPIO_EVENT_1_IRQ   (1UL << 1)                ///< GPIO1 interrupt event value 
#define GPIO_EVENT_2_IRQ   (1UL << 2)                ///< GPIO2 interrupt event value 
#define GPIO_EVENT_3_IRQ   (1UL << 3)                ///< GPIO3 interrupt event value 

/* Function documentation */
/**
  \fn          ARM_DRIVER_VERSION GPIO_GetVersion (void)
  \brief       Get driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          int32_t GPIO_Initialize (GPIO_SignalEvent_t cb)
  \brief       Initialize the GPIO driver.
  \param[in]   cb  Pointer to \ref GPIO_SignalEvent
  \return      \ref execution_status

  \fn          int32_t GPIO_Configure (const GPIO_CFG_t * cfg)
  \brief       Configure common GPIO settings.
  \param[in]   cfg  Pointer to \ref GPIO_CFG_t
  \return      \ref execution_status

  \fn          int32_t GPIO_ConfigurePad (GPIO_SEL_t sel, const GPIO_PAD_CFG_t *cfg)
  \brief       Configure the GPIO pad.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \param[in]   cfg  Pointer to \ref GPIO_PAD_CFG_t
  \return      \ref execution_status

  \fn          int32_t GPIO_ConfigureInterrupt (GPIO_INT_SEL_t sel, const GPIO_INT_CFG_t *cfg)
  \brief       Configure the GPIO interrupt.
  \param[in]   sel  Interrupt selection \ref GPIO_INT_SEL_t
  \param[in]   cfg  Pointer to \ref GPIO_INT_CFG_t
  \return      \ref execution_status

  \fn          int32_t GPIO_SetInterruptPriority(GPIO_INT_SEL_t sel, const GPIO_PRI_CFG_t *cfg)
  \brief       Configure GPIO interrupt priority.
  \param[in]   sel  Interrupt selection \ref GPIO_INT_SEL_t
  \param[in]   cfg  Pointer to \ref GPIO_PRI_CFG_t
  \return      \ref execution_status

  \fn          int32_t GPIO_ConfigureJTAG (const GPIO_JTAG_SW_CFG_t *cfg)
  \brief       Configure the GPIO JTAG mode.
  \param[in]   cfg  Pointer to \ref GPIO_JTAG_SW_CFG_t
  \return      \ref execution_status

  \fn          void GPIO_SetDir (GPIO_SEL_t sel, GPIO_DIR_t dir)
  \brief       Set particular GPIO pad direction.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \param[in]   dir  Pad direction \ref GPIO_DIR_t
  \return      None

  \fn          void GPIO_SetHigh (GPIO_SEL_t sel)
  \brief       Set particular GPIO pad.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \return      None

  \fn          void GPIO_ToggleValue (GPIO_SEL_t sel)
  \brief       Toggle particular GPIO pad.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \return      None

  \fn          void GPIO_SetLow (GPIO_SEL_t sel)
  \brief       Reset particular GPIO pad.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \return      None

  \fn          uint32_t GPIO_ReadValue (GPIO_SEL_t sel)
  \brief       Returns the selected GPIO pad value.
  \param[in]   sel  Pad selection \ref GPIO_SEL_t
  \return      GPIO pad value


  \fn          int32_t GPIO_ResetAltFuncRegister (GPIO_FUNC_REGISTERS_t reg)
  \brief       Reset the particular alternative function register.
  \param[in]   reg  Register selection \ref GPIO_FUNC_REGISTERS_t
  \return      \ref execution_status

  \fn          void GPIO_SignalEvent (uint32_t event)
  \brief       Signal GPIO events.
  \param[in]   event notification mask
  \return      None
*/

typedef void (*GPIO_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref GPIO_SignalEvent : Signal GPIO Event. 

/**
\brief Debounce filter configuration.
*/
typedef struct _GPIO_DBF_CFG_t
{
    uint8_t                count           :8;   ///< Debounce filter count value  
    GPIO_DBC_CLK_t         clk_source      :1;   ///< Debounce filter clock source 
    uint8_t                                :7;   ///< Reserved                     
} GPIO_DBF_CFG_t;

/**
\brief GPIO interrupt priority configuration
*/
typedef struct _GPIO_PRI_CFG_t
{
    uint32_t               preempt_pri     :3;   ///< Preempt priority  
    uint32_t                               :13;  ///< Reserved          
    uint32_t               subgrp_pri      :3;   ///< Subgroup priority 
    uint32_t                               :13;  ///< Reserved          
} GPIO_PRI_CFG_t;

/**
\brief GPIO Driver configuration.
*/
typedef struct _GPIO_CFG_t
{
    GPIO_DRIVE_STRENGTHS_t drive_strengths :1;   ///< Drive strengths configuration 
    uint8_t                                :7;   ///< Reserved                      
    GPIO_DBF_CFG_t         debounce_cfg;         ///< Debounce filter configuration 
} GPIO_CFG_t;

/**
\brief GPIO PAD configuration.
*/
typedef struct _GPIO_PAD_CFG_t
{
    GPIO_PULL_t            pull_mode       :2;   ///< Pull control           
    uint8_t                                :6;   ///< Reserved               
    GPIO_DRIVE_t           drive_mode      :2;   ///< Drive mode             
    uint8_t                                :6;   ///< Reserved               
    GPIO_LPF_t             lpf_en          :1;   ///< Low pass filter enable 
    uint16_t                               :3;   ///< Reserved               
    GPIO_MODE_t            io_mode         ;     ///< IO mode                
} GPIO_PAD_CFG_t;

/**
\brief GPIO INT configuration.
*/
typedef struct _GPIO_INT_CFG_t
{
    GPIO_SEL_t             src_sel         :4;   ///< Interrupt source selection 
    GPIO_EVENT_t           event           :3;   ///< Event selection            
    GPIO_EN_DIS_t          debounce_en     :1;   ///< Debouce filter enable      
    GPIO_EN_DIS_t          interrup_en     :1;   ///< Interrupt enable flag      
    uint8_t                                :7;   ///< Reserved                   
} GPIO_INT_CFG_t;

/**
\brief External clock pad configuration.
*/
typedef struct _GPIO_EXTCLK_CFG_t
{
    GPIO_PULL_t            pull_mode       :2;   ///< Pull control           
    GPIO_LPF_t             lpf_en          :1;   ///< Low pass filter enable 
    uint8_t                                :6;   ///< Reserved               
} GPIO_EXTCLK_CFG_t;

/**
\brief JTAG configuration.
*/
typedef struct _GPIO_JTAG_SW_CFG_t
{
    GPIO_LPF_t             swclk_jtck_lpf_en    :1;   ///< SWCLK/JTCK low pass filter enable     
    GPIO_LPF_t             swdio_jtms_lpf_en    :1;   ///< SWDIO/JTMS low pass filter enable     
    GPIO_EN_DIS_t          jtag_data_en         :1;   ///< JTAG data available on GPIO[2:3]      
    GPIO_EN_DIS_t          jtag_trst_en         :1;   ///< JTAG trst available on GPIO4          
    GPIO_PULL_t            swclk_jtck_pull      :2;   ///< SWCLK/JTCK pull mode                  
    GPIO_PULL_t            swdio_jtms_pull      :2;   ///< SWDIO/JTMS pull mode                  
    GPIO_DRIVE_t           swdio_jtms_drive     :2;   ///< SWDIO/JTMS drive mode                 
    uint8_t                                     :6;   ///< Reserved                              
} GPIO_JTAG_SW_CFG_t;

/**
\brief Access structure of the GPIO Driver.
*/
typedef struct _DRIVER_GPIO_t {
    ARM_DRIVER_VERSION  (*GetVersion)            (void);                                          ///< Pointer to \ref GPIO_GetVersion : Get driver version.                                 
    int32_t             (*Initialize)            (GPIO_SignalEvent_t cb);                         ///< Pointer to \ref GPIO_Initialize : Initialize the GPIO driver.                         
    int32_t             (*Configure)             (const GPIO_CFG_t *cfg);                         ///< Pointer to \ref GPIO_Configure : Configure common GPIO settings.                      
    int32_t             (*ConfigurePad)          (GPIO_SEL_t sel, const GPIO_PAD_CFG_t *cfg);     ///< Pointer to \ref GPIO_ConfigurePad : Configure the GPIO pad.                           
    int32_t             (*ConfigureInterrupt)    (GPIO_INT_SEL_t sel, const GPIO_INT_CFG_t *cfg); ///< Pointer to \ref GPIO_ConfigureInterrupt : Configure the GPIO interrupt.               
    int32_t             (*SetInterruptPriority)  (GPIO_INT_SEL_t sel, const GPIO_PRI_CFG_t *pri); ///< Pointer to \ref GPIO_SetInterruptPriority : Configure GPIO interrupt priority.        
    int32_t             (*ConfigureJTAGSW)       (const GPIO_JTAG_SW_CFG_t *cfg);                 ///< Pointer to \ref GPIO_ConfigureJTAG : Configure the GPIO JTAG mode.                    
    void                (*SetDir)                (GPIO_SEL_t sel, GPIO_DIR_t dir);                ///< Pointer to \ref GPIO_SetDir : Set particular GPIO pad direction.                      
    void                (*SetHigh)               (GPIO_SEL_t sel);                                ///< Pointer to \ref GPIO_SetHigh : Set particular GPIO pad.                               
    void                (*ToggleValue)           (GPIO_SEL_t sel);                                ///< Pointer to \ref GPIO_ToggleValue : Toggle particular GPIO pad.
    void                (*SetLow)                (GPIO_SEL_t sel);                                ///< Pointer to \ref GPIO_SetLow : Reset particular GPIO pad.                              
    uint32_t            (*ReadValue)              (GPIO_SEL_t sel);                               ///< Pointer to \ref GPIO_ReadValue : Return the selected GPIO value.                      
    int32_t             (*ResetAltFuncRegister)  (GPIO_FUNC_REGISTERS_t sel);                     ///< Pointer to \ref GPIO_ResetAltFuncRegister : Reset GPIO alternative function register. 
} const DRIVER_GPIO_t;

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of the CMSISDRVGPIOg group */
/** @} */ /* End of the CMSISDRVg group */

#endif /* DRIVER_GPIO_H_ */
