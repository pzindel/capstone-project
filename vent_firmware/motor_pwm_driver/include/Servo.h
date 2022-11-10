/******************************************************************************
 * File Name        : Servo.h
 * Description		: This header module contains the constants and function
 * 					  prototypes for the Servo drivers module.
 *
 * 					  This module can be configured to work with regular servo
 * 					  motors as well as continuous rotation servo motors.
 *
 * 					  Designed for a PWM connection with RSL15 with the
 * 					  following pinout:
 *                          Servo_Signal_Pin <--> GPIO_2 (PWM_0)
 *
 * Author		    : Pierino Zindel
 * Date				: October 26, 2022
 * Version			: 1.0.0
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
// General
/* Set the type of Servo motor
 *     Fixed range (0-180 deg) 	= 0
 *     Continuous range			= 1
 */
#define CONTINUOUS_SERVO		(0)
#ifndef MICRO_DELAY											// microseconds delay function
 #define MICRO_DELAY(x)			Sys_Delay(((x * SystemCoreClock) / 1000000))
#endif
#ifndef MILLI_DELAY											// milliseconds delay function
 #define MILLI_DELAY(x)			Sys_Delay(((x * SystemCoreClock) / 1000))
#endif
#ifndef SECOND_DELAY										// seconds delay function
 #define SECOND_DELAY(x)		Sys_Delay((x * SystemCoreClock))
#endif

// Clock configuration
#define SERVO_CLK_SELECT		(1)
#define SERVO_CLK_PRESCALER		(50)

// PWM configuration
#define SERVO_PWM_CHANNEL		(0)
#define SERVO_PWM_PERIOD		(3200)

// Servo motor constants
#define US_PER_ROTATION			(564000)					// microseconds (empirically obtained)
#define US_PER_DEGREE			(US_PER_ROTATION / 360)
#define DEG_ROTATION_DELAY(x)	(int)(x * US_PER_ROTATION / 360)

// Vent state configuration
#define VENT_OPEN_DEG			(180)						// degrees
#define VENT_OPEN_STATE			(0)
#define VENT_CLOSED_DEG			(90)						// degrees
#define VENT_CLOSED_STATE		(1)


/* ----------------------------------------------------------------------------
 * Macros
 * --------------------------------------------------------------------------*/
// Degrees to duty cycle conversion
#define DEG_TO_DUTY_PERCENT(x)	(0.051666 * x + 2.7)	// scale and offset found through empirical means
#define DEG_TO_DUTY_CYCLE(x)	(int)(SERVO_PWM_PERIOD * DEG_TO_DUTY_PERCENT(x) / 100)


/* ----------------------------------------------------------------------------
 * Global variables
 * --------------------------------------------------------------------------*/
// Import the handler for the PWM peripheral
extern DRIVER_PWM_t Driver_PWM;
extern DRIVER_GPIO_t Driver_GPIO;
extern DRIVER_PWM_t *pwm;
extern DRIVER_GPIO_t *gpio;


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
 * 				   controlled to a set position.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void enable_servo(void);


/* Function      : get_vent_state
 *
 * Description   : Reads and returns the current state of the vent. A return
 * 				   return value of 0 indicates that the vent is open. A
 * 				   return value of 1 indicates that the vent is closed.
 *
 * Parameters    : uint8_t state : The state of the vent; 0=open, 1=closed.
 *
 * Returns		 : None
 */
uint8_t get_vent_state(void);


/* Function      : init_servo
 *
 * Description   : Set the PWM channels to a known state.
 *
 * Parameters    : None
 *
 * Returns		 : None
 */
void initialize_servo(void);


/* Function      : set_position
 *
 * Description   : Sets the position of the servo to the specified degree
 * 				   between 0 and 180. In the case of a continuous servo, the
 * 				   position is approximated based on rotation speed.
 *
 * Parameters    : uint8_t angle : The angle that the servo should move to (0-180).
 *
 * Returns		 : None
 */
void set_position(uint8_t angle);


/* Function      : set_vent_state
 *
 * Description   : Sets the opening in state of the vent. Providing a state
 * 				   value of 0 places the vent in the open position, providing
 * 				   a state value of 1 places the vent in the closed position.
 *
 * Parameters    : uint8_t state : The state of the vent; 0=open, 1=closed.
 *
 * Returns		 : None
 */
void set_vent_state(uint8_t state);

#endif /* INCLUDE_SERVO_H_ */
