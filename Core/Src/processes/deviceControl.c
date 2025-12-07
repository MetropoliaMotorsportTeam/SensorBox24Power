/*
 * deviceControl.c
 *
 *  Created on: Nov 16, 2025
 *      Author: dovlatib
 */


#include "main.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx.h"
#include "stdio.h"
#include "config.h"
#include "deviceControl.h"



void SwitchOnOff(GPIO_TypeDef *port, uint16_t pin, uint8_t state){
	HAL_GPIO_WritePin(port, pin, state);
}

void SwitchOutput(){
	uint8_t i = 0;
	for(i = 0; i < 8;i++){
		outputs[i].state = CheckBit(Default_Switch_State, i);
		SwitchOnOff(outputs[i].port, outputs[i].physical_pin, outputs[i].state);
	}
}

