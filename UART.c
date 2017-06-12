/*
 * UART.c
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

#include "UART.h"
#include <avr/io.h>

void UART_init()
{
	//set the baud rate
	//set the UBRRnL to 51 to set the baud rate to 9600 at a setting of 8Mhz crystal
	UBRR0H = 0;
	UBRR0L = 51;
	//enable the transmitter and receiver
	UCSR0B |= (1 << RXEN0 | 1 << TXEN0);
	//set the data format to 8bit and 2 stop bit
	UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00 | 1 << USBS0);
}
void UART_write(uint8_t data)
{
	//wait for the transmit buffer to be empty
	while (!(UCSR0A & (1 << UDRE0)))
		;
	//put the data on the buffer
	UDR0 = data;

}
uint8_t UART_read()
{
	//wait for the receive flag
	while (!(UCSR0A & (1 << RXC0)))
		;
	uint8_t data = UDR0;
	return data;
}

