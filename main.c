/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: ali
 *      Target : ATMega328p
 *      project :
 *      this project is a remotely controlled car via a bluetooth remote
 *      the car controls two DC motor via a motor drive module L298n
 *      A LCD is connected to the system to output the command to execute
 *      set the motors pins and it's port in the Motor_Drive.h file
 *      set the LCD pins (that uses 4bit mode) in the LCD.h
 *      connect the bluetooth TX and RX to the RX and TX of the microcontroller respectively
 */
#include <avr/io.h>
#include <util/delay.h>
#include "Motor_Drive.h"
#include "LCD.h"
#include "UART.h"
int main()
{
	//initialize the modules
	LCD_init();
	Motor_init();
	UART_init();
	//start the motor at stop condition and LCD at welcome message
	LCD_displayString("Welcome!");
	Motor_stop();
	while (1)
	{
		//wait for a new character then alter the motor state
		uint8_t data = 0x00;
		data = UART_read();
		switch (data)
		{
		case 's':
			LCD_clearScreen();
			LCD_displayString("stop!");
			Motor_stop();
			break;
		case 'f':
			LCD_clearScreen();
			LCD_displayString("moving forward");
			Motor_forward();
			break;
		case 'b':
			LCD_clearScreen();
			LCD_displayString("moving backward");
			Motor_backward();
			break;
		case 'l':
			LCD_clearScreen();
			LCD_displayString("moving left");
			Motor_left();
			break;
		case 'r':
			LCD_clearScreen();
			LCD_displayString("moving right");
			Motor_right();
			break;
		}

	}
}
