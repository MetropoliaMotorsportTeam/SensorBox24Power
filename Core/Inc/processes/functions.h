/*
 * functions.h
 *
 *  Created on: Nov 26, 2023
 *      Author: marcelc
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32g4xx_hal.h"

void CANSwitchDeviceState();
void OverCurrent(uint8_t output_pin);
void WarningCurrent(uint8_t output_pin);
void UnderCurrent(uint8_t output_pin);
void SendCurrent(uint8_t output_pin, uint16_t current);
void DecodeCANMessage();
void CheckWarnings();
void ConfigureCurrentSense(uint8_t SEL0, uint8_t SEL1);
uint8_t CheckBit(uint8_t byte, uint8_t bitn);
uint8_t SetBit(uint8_t byte, uint8_t pos, uint8_t new_bit);

#endif /* INC_FUNCTIONS_H_ */
