/*
 * LCD.c
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

#include "LCD.h"
#include <util/delay.h>

//important macro functions
#define CLEAR_BIT(PORT,BIT)		GPIO_Write(PORT,(1<<BIT),LOW)		//clear certain bit
#define SET_BIT(PORT,BIT)		GPIO_Write(PORT,(1<<BIT),HIGH)		//set certain bit
#define HIGH_NIBBLE(Hvar , var)	(Hvar = var&0xF0)					//extract the highNibble from the data
#define LOW_NIBBLE(Lvar , var)	(Lvar = var<<4)						//extract the lowNibble from the data

//prototypes needed
void delayUs(int time);
void delayMs(int time);
void enableTrigger(void);
void sendCommand(uint8_t cmd);

/*	initialize the lcd pins
 4bit mode -5x7 pixels mode - 2 lines */
void LCD_init()
{
	//initialize the pins
	GPIO_Init(DATA_PORT, DATA_MASK, OUTPUT, NONE);
	GPIO_Init(CMD_PORT, ((1 << RS_PIN) | (1 << EN_PIN) | (1 << RW_PIN)), OUTPUT,
			NONE);

	//activate the enable pin
	SET_BIT(CMD_PORT, EN_PIN);

	//the mode of the LCD
	sendCommand(0x33);
	sendCommand(0x32);
	sendCommand(0x28);

	//turn on the lcd
	sendCommand(0x0C);

}

//clears the screen
void LCD_clearScreen()
{
	sendCommand(0x01);
}

//change the cursor position
void LCD_gotoxy(uint8_t x, uint8_t y)
{
	//variable to hold the position request
	uint8_t position = 0x00 ;
	switch (y)
	{
	//if the first row
	case 0x00:
		position = 0x80 + x;
		break;
		//if the second row
	case 0x01:
		position = 0xC0 + x;
		break;
	}
	//send the request to the LCD
	sendCommand(position);
}

//shifting the LCD display
void LCD_shiftDisplayLeft(void)
{
	sendCommand(0x18);
}

void LCD_shiftDisplayRight(void)
{
	sendCommand(0x1C);
}

//display a char on the LCD
void LCD_displayChar(char character)
{
	uint8_t highNibble, lowNibble;

	SET_BIT(CMD_PORT,RS_PIN); //to enable the data mode
	CLEAR_BIT(CMD_PORT, RW_PIN);
	//to enable the write mode

	//extracting the data (high and low nibbles)
	HIGH_NIBBLE(highNibble, character);
	LOW_NIBBLE(lowNibble, character);

	//send the high nibble
	GPIO_Write(DATA_PORT, DATA_MASK, highNibble);
	enableTrigger();

	//send the low nibble
	GPIO_Write(DATA_PORT, DATA_MASK, lowNibble);
	enableTrigger();

}

//display a string on the LCD
void LCD_displayString(char* string)
{
	//check for the end of the string
	while (*string != '\0')
		LCD_displayChar(*(string++)); //divide it into chars
}

//display an int on the LCD
void LCD_displayInt(int decimal)
{
	//a memory to hold the transfered number into string
	char string[6];
	sprintf(string, "%d", decimal); //use the sprintf to create a string of that number
	LCD_displayString(string); //display that number as a string
}

//display a float on the LCD the same concept as the int
void LCD_displayFloat(float number)
{
	char string[6];
	sprintf(string, "%0.2f", number);
	LCD_displayString(string);
}

//4-bit mode commands
void sendCommand(uint8_t cmd)
{
	uint8_t highNibble, lowNibble;

	//divide the high and low nibbles
	HIGH_NIBBLE(highNibble, cmd);
	LOW_NIBBLE(lowNibble, cmd);

	CLEAR_BIT(CMD_PORT, RS_PIN);
	//to enable the command mode
	CLEAR_BIT(CMD_PORT, RW_PIN);
	//to enable the write mode

	//send the high nibble
	GPIO_Write(DATA_PORT, DATA_MASK, highNibble);
	enableTrigger();

	//send the low nibble
	GPIO_Write(DATA_PORT, DATA_MASK, lowNibble);
	enableTrigger();

}

//delay functions that depend on the time needed for an operation (in this driver the speed is set on 16Mhz)
void delayUs(int time)
{
	for (int i = 0; i < time; ++i)
		_delay_us(1);

}
void delayMs(int time)
{
	for(int i = 0 ; i < time ; i++)
		_delay_ms(1);
}

//the trigger is needed by the LCD
void enableTrigger()
{
	CLEAR_BIT(CMD_PORT, EN_PIN);
	delayUs(500);

	SET_BIT(CMD_PORT, EN_PIN);
	delayUs(1500);

}

