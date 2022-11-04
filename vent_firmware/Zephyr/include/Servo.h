/******************************************************************************
 * File Name        : Servo.h
 * Description		: This header module contains the constants and function
 * 					  prototypes for the Servo drivers module.
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

#ifndef INCLUDE_SERVO_H_
#define INCLUDE_SERVO_H_


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include "app.h"

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/
#define MIN_PULSE_WIDTH			(544)
#define MAX_PULSE_WIDTH			(2400)
#define DEFAULT_PULSE_WIDTH		(1500)
#define REFRESH_INTERVAL		(20000)

/* ----------------------------------------------------------------------------
 * Global variables
 * --------------------------------------------------------------------------*/


/* ----------------------------------------------------------------------------
 * Function prototypes
 * --------------------------------------------------------------------------*/

/* Function      : disable_servo
 *
 * Description   : Disables the power to the servo motor so that is doesn't
 * 				   consume resources while idle.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void disable_servo(void);

/* Function      : enable_servo
 *
 * Description   : Enables the power to the servo motor so that it may be
 * 				   controlled.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void enable_servo(void);

/* Function      : get_position
 *
 * Description   : Returns the current relative position of the servo motor as
 * 				   an angle between 0 and 180 degrees.
 *
 * Parameters    : None
 *
 * Returns		 : uint8_t : The current angle of the servo (0-180).
 */
uint8_t get_position(void);

/* Function      : set_position
 *
 * Description   : Sets the position of the servo to the specified degree
 * 				   between 0 and 180.
 *
 * Parameters    : uint8_t angle : The angle that the servo should move to (0-180).
 *
 * Returns		 : None
 */
void set_position(uint8_t angle);

#endif /* INCLUDE_SERVO_H_ */
