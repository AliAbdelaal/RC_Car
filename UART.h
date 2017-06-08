/*
 * UART.h
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

/**
 * this module is built for a specific requirements
 * it only uses the 8bit mode of data and a baud rate of 9600
 * it also uses 1 stop bit
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void UART_init();
void UART_write(uint8_t data);
uint8_t UART_read();


#endif /* UART_H_ */
