/*
 * functions.c
 *
 *  Created on: Nov 26, 2023
 *      Author: marcelc
 */
#include "main.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx.h"
#include "stdio.h"
#include "config.h"
#include "fdcan.h"

uint8_t RxData[8];
uint8_t TxData[8];

uint8_t toggle = 0;

extern CAN_Message RxMessage;
//function to send state of switches on CAN, for debugging!
void CANSwitchDeviceState(){
	if(ID == 1){
		TxData[0] = Default_Switch_State;
		TxHeader.Identifier = 29;
	}else if(ID == 2){
		TxData[0] = Default_Switch_State;
		TxHeader.Identifier = 30;
	}
	CANSend(TxData, CAN_ID);
}

void OverCurrent(uint8_t output_pin){
	TxData[0] = 15;
	TxData[1] = output_pin;
	CANSend(TxData, CAN_over_currernt);
}

void WarningCurrent(uint8_t output_pin){
	TxData[0] = 14;
	TxData[1] = output_pin;
	CANSend(TxData, CAN_warning_currernt);
}

void UnderCurrent(uint8_t output_pin){
	TxData[0] = 13;
	TxData[1] = output_pin;
	CANSend(TxData, CAN_under_currernt);
}

void SendCurrent(uint8_t output_pin, uint16_t current){
	uint8_t cur1 = current/100;
	uint8_t cur2 = current%100;
	TxData[0] = 16;
	TxData[1] = output_pin;
	TxData[2] = cur1;
	TxData[3] = cur2;
	CANSend(TxData, CAN_ID);
}

void DecodeCANMessage(){
	
	switch (RxMessage.Bytes[0]) //PWM or switch output
	{
		case 1:
			PWM_width[RxMessage.Bytes[1]] = RxMessage.Bytes[2]; // 0 - htim1 1 - htim2
			(RxMessage.Bytes[1]) ? set_pwm_duty_cycle(&htim2) : set_pwm_duty_cycle(&htim1);
			break;
		case 2:
				Default_Switch_State = SetBit(Default_Switch_State,RxMessage.Bytes[1],RxMessage.Bytes[2]);
				SwitchOutput();
				break;
		default:

			break;

	}
}


void CheckWarnings(){
	for(uint8_t x = 0; x < 7; x++){
		if(outputs[x].device != NC){
			if(outputs[x].actual_current >= outputs[x].Warning_Current){
				if(outputs[x].actual_current >= outputs[x].Over_Current){
					Default_Switch_State = SetBit(Default_Switch_State, outputs[x].pin, 0);
					OverCurrent(x);
				}else{
					WarningCurrent(x);
				}
			}
		}
		if(outputs[x].actual_current < outputs[x].Under_Current){
			UnderCurrent(x);
		}
	}
	SwitchOutput();
}


void ConfigureCurrentSense(uint8_t SEL0, uint8_t SEL1){
	HAL_GPIO_WritePin(GPIOB,SEL0_Pin,SEL0);
	HAL_GPIO_WritePin(GPIOB,SEL1_Pin,SEL1);
}



uint8_t CheckBit(uint8_t byte, uint8_t bitn){
	uint8_t buffer = 1<<bitn;
	if (byte & buffer){
		return 1;
	}else{
		return 0;
	}
}

uint8_t SetBit(uint8_t byte, uint8_t pos, uint8_t new_bit){
	uint8_t mask = 1 << pos;
	if(new_bit == 1){
		byte |= mask;
	}else{
		byte &= ~mask;
	}
	return byte;
}


