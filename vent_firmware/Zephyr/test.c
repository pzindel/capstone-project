/**
  ******************************************************************************
  * @file   test.c
  * @author James Le
  * @date   19/09/2022
  * @brief  library for mcp9700 module
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <app.h>
#include "HDC2080.h"
#include "test.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


uint8_t APP_BASS_ReadTempLevel(uint8_t bas_nb)
{
    uint8_t batt_lvl_percent;

    trigger_measurement();
    batt_lvl_percent = (uint8_t)get_temperature();

    return batt_lvl_percent;
}
