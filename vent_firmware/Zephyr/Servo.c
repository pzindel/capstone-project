/******************************************************************************
 * File Name        : Servo.c
 * Description		: This module implements drivers for handling a servo
 * 					  motor using a PWM peripheral function.
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
 * Version			: 1.2.0
 * Last Rev. Date   : November 24, 2022
 ******************************************************************************
 */


/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include "Servo.h"

/* ----------------------------------------------------------------------------
 * Private Global Variables
 * --------------------------------------------------------------------------*/
// Variables to track the vent state
static uint8_t State;
#if (CONTINUOUS_SERVO)
 static uint8_t MotorPosition;		// A position in degrees (0-360)
#endif


/* ----------------------------------------------------------------------------
 * Function definitions
 * --------------------------------------------------------------------------*/

void disable_servo(void)
{
	// TODO: Implement this function using GPIO control of a transistor
	return;
}

void enable_servo(void)
{
	// TODO: Implement this function using GPIO control of a transistor
	return;
}

uint8_t get_vent_state(void)
{
	return State;
}

void initialize_servo(void)
{
	// Initialize the GPIO pin
    //gpio = &Driver_GPIO;
	//gpio->Initialize((GPIO_SignalEvent_t) 0);

	// Disable the PWM channels
	PWM->CTRL |= (0x100 << SERVO_PWM_CHANNEL);

	// Configure offset
	PWM->OFFSET[SERVO_PWM_CHANNEL] = 0x0;

	// Enable PWM offset
	PWM->OFFSET[SERVO_PWM_CHANNEL] |= PWM_OFFSET_ENABLE;

	// Initialize the PWM driver
	pwm = &Driver_PWM;
	pwm->Initialize();

	// Set the clock and prescaler for the PWM
	pwm->SelectClock(SERVO_CLK_SELECT, SERVO_CLK_PRESCALER);

	// Set the PWM period
	pwm->SetPeriod(SERVO_PWM_CHANNEL, SERVO_PWM_PERIOD);

	// Set the global status variables
	State = VENT_OPEN_STATE;
#if (CONTINUOUS_SERVO)
	MotorPosition = VENT_OPEN_DEG;
#endif

	return;
}

void set_position(uint8_t angle)
{
#if (CONTINUOUS_SERVO) // Servo motor is continuous; positioning is based on motor runtime
	// Compute the time to reach given angle
	int8_t difference = MotorPosition - angle;
	uint32_t move_time = 0;
	int16_t duty_cycle = 0;

	if (difference < 0) {
		// Set the number of microseconds to reach the position
		move_time = DEG_ROTATION_DELAY(-difference);

		// Compute the duty cycle for CCW rotation (i.e. set to 180 deg)
		duty_cycle = DEG_TO_DUTY_CYCLE(180);
	} else {
		// Set the number of microseconds to reach the position
		move_time = DEG_ROTATION_DELAY(difference);

		// Compute the duty cycle for CW rotation (i.e. set to 0 deg)
		duty_cycle = DEG_TO_DUTY_CYCLE(0);
	}

	// Configure PWM high period
	PWM->HIGH[SERVO_PWM_CHANNEL] &= ~(PWM_HIGH_HIGH_Mask);
	PWM->HIGH[SERVO_PWM_CHANNEL] |= (duty_cycle << PWM_HIGH_HIGH_Pos);

	// Enable the servo motor
	PWM->CTRL |= (1 << (SERVO_PWM_CHANNEL + PWM_CTRL_ENABLE_Pos));

	// Wait for required travel time
	if (move_time > 1000000) {
		move_time = move_time / 1000000;
		SECOND_DELAY(move_time);
	} else if (move_time > 1000) {
		move_time = move_time / 1000;
		MILLI_DELAY(move_time);
	} else {
		MICRO_DELAY(move_time);
	}

	// Disable the servo motor
	PWM->CTRL |= (1 << (SERVO_PWM_CHANNEL + PWM_CTRL_DISABLE_Pos));

	// Update the current motor position
	MotorPosition = angle;

#else // Servo motor is not continuous; positioning is based on angle provided
    // Compute the duty cycle (# of cycles based on period)
	uint16_t cycles = DEG_TO_DUTY_CYCLE(angle);

	pwm->SetHighPeriod(SERVO_PWM_CHANNEL, cycles);

	// Enable the servo motor
	pwm->Start(SERVO_PWM_CHANNEL);

	// Wait for 500 ms
	MILLI_DELAY(500);

	// Disable the servo motor
	pwm->Stop(SERVO_PWM_CHANNEL);

#endif /* if (CONTINUOUE_SERVO) */

	return;
}

void set_vent_state(uint8_t state)
{
	if (state == VENT_OPEN_STATE) {
		// Open the vent
		set_position(VENT_OPEN_DEG);
	} else if (state == VENT_CLOSED_STATE) {
		// Close the vent
		set_position(VENT_CLOSED_DEG);
	} else {
		return;
	}

	// Update the global status variable
	State = state;

	return;
}
