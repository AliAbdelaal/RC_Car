/*
 * GPIO.h
 *
 *  Created on: Jun 8, 2017
 *      Author: ali
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

#define PB 0x01
#define PC 0x02
#define PD 0x03

#define HIGH 0xff
#define LOW 0x00
#define INPUT LOW
#define OUTPUT HIGH
#define PULL_UP_ENABLE OUTPUT
#define NONE INPUT

void GPIO_Init(uint8_t PortName, uint8_t Mask, uint8_t Direction, uint8_t pull_up);
void GPIO_Write(uint8_t PortName, uint8_t Mask, uint8_t Data);
uint8_t GPIO_Read(uint8_t PortName, uint8_t MAsk);

#endif /* GPIO_H_ */
