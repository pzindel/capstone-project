/******************************************************************************
 * File Name        : Servo.c
 * Description		: This module implements drivers for handling a servo
 * 					  motor using a PWM peripheral function.
 *
 * 					  Designed for a PWM connection with RSL15 with the
 * 					  following pinout:
 *                          Servo_Signal_Pin <--> GPIO_2 (PWM_0)
 *
 * Author		    : Pierino Zindel
 * Date				: October 26, 2022
 * Version			: 0.1.0
 ******************************************************************************
 */


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include "Servo.h"


/* ----------------------------------------------------------------------------
 * Function definitions
 * --------------------------------------------------------------------------*/

void disable_servo(void)
{
	return;
}

void enable_servo(void)
{
	return;
}

uint8_t get_position(void)
{
	uint8_t position = 0xFF;

	return position;
}

void set_position(uint8_t angle)
{
	return;
}

