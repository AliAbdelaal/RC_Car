/*
 * Motor_Drive.c
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */
#include "Motor_Drive.h"
#include "GPIO.h"

uint8_t motor_mask = (1 << M1 | 1 << M2 | 1 << M3 | 1 << M4);

void Motor_init()
{
	//init the pins as output
	GPIO_Init(MOTOR_PORT, motor_mask, OUTPUT, NONE);
}
void Motor_forward()
{
	GPIO_Write(MOTOR_PORT, motor_mask, (1 << M1 | 1 << M3));
}
void Motor_backward()
{
	GPIO_Write(MOTOR_PORT, motor_mask, (1 << M2 | 1 << M4));
}
void Motor_left()
{
	GPIO_Write(MOTOR_PORT, motor_mask, (1 << M1 | 1 << M4));
}
void Motor_right()
{
	GPIO_Write(MOTOR_PORT, motor_mask, (1 << M2 | 1 << M3));
}
void Motor_stop()
{
	GPIO_Write(MOTOR_PORT, motor_mask, motor_mask);
}
