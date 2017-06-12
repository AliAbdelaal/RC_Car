/*
 * Motor_Drive.h
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

#ifndef MOTOR_DRIVE_H_
#define MOTOR_DRIVE_H_

// the pins connected to the motor
#define MOTOR_PORT PD
#define M1	0x04
#define M2	0x05
#define M3 	0x06
#define M4	0x07

void Motor_init();
void Motor_forward();
void Motor_backward();
void Motor_left();
void Motor_right();
void Motor_stop();




#endif /* MOTOR_DRIVE_H_ */
