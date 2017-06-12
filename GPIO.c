/*
 * GPIO.c
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

#include "GPIO.h"
#include <avr/io.h>
// write a macro to write a register with a certain value on specific bits locations
#define WRITE_REG(Reg,Value,Mask) Reg&=~(Mask); Reg|=(Value & Mask)
//read a maco to read specific bits from a register
#define READ_REG(Reg,Mask) Reg & Mask

void GPIO_Init(uint8_t PortName, uint8_t Mask, uint8_t Direction,
		uint8_t pull_up)
{
	//check the required port, specified bits and direction on the Data Direction Register
	switch (PortName)
	{
	case PB:
		WRITE_REG(DDRB, Direction, Mask);
		break;
	case PC:
		WRITE_REG(DDRC, Direction, Mask);
		break;
	case PD:
		WRITE_REG(DDRD, Direction, Mask);
		break;
	}
	//enable the pull_up resistor
	if (Direction == INPUT && pull_up == PULL_UP_ENABLE)
		switch (PortName)
		{
		case PB:
			WRITE_REG(PORTB, OUTPUT, Mask);
			break;
		case PC:
			WRITE_REG(PORTC, OUTPUT, Mask);
			break;
		case PD:
			WRITE_REG(PORTD, OUTPUT, Mask);
			break;
		}

}

void GPIO_Write(uint8_t PortName, uint8_t Mask, uint8_t Data)
{
	//check the required port, specified bits and value on the Port Data Register
	switch (PortName)
	{
	case PB:
		WRITE_REG(PORTB, Data, Mask);
		break;
	case PC:
		WRITE_REG(PORTC, Data, Mask);
		break;
	case PD:
		WRITE_REG(PORTD, Data, Mask);
		break;
	}
}

uint8_t GPIO_Read(uint8_t PortName, uint8_t mask)
{
	//check the required port, specified bits and value from the Port input Register
	uint8_t data = 0x00;
	switch (PortName)
	{
	case PB:
		data = READ_REG(PINB,mask);
		break;
	case PC:
		data = READ_REG(PINC,mask);
		break;
	case PD:
		data = READ_REG(PIND,mask);
		break;
	}
	return data;
}
