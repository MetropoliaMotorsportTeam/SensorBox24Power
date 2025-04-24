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





uint8_t RxData[8];
uint8_t TxData[8];
uint8_t toggle = 0;


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxMessage.Bytes) != HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}else{
			if(RxHeader.Identifier == CAN_ID){
				RxMessage.DLC = RxHeader.DataLength;
				decode();
			}
		}

		if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			Error_Handler();
		}
	}
}

void CanSend(uint8_t *TxData){
	while(HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) != 0 && HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK){
		Error_Handler();
		HAL_GPIO_WritePin(GPIOB,LED1_Pin,0);
	}
}

//function to send state of switches on CAN, for debugging!
void CAN_switch_state(){
	if(ID == 1){
		TxData[0] = Default_Switch_State;
		TxHeader.Identifier = 29;
	}else if(ID == 2){
		TxData[0] = Default_Switch_State;
		TxHeader.Identifier = 30;
	}
	CanSend(TxData);
	TxHeader.Identifier = CAN_ID;
}

void switch_on_off(GPIO_TypeDef *port, uint16_t pin, uint8_t state){
	HAL_GPIO_WritePin(port, pin, state);
}

void switch_output(){
	uint8_t i = 0;
	for(i = 0; i < 8;i++){
		outputs[i].state = check_bit(Default_Switch_State, i);
		switch_on_off(outputs[i].port, outputs[i].physical_pin, outputs[i].state);
	}
}

void Over_current(uint8_t output_pin){
	TxData[0] = 15;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void Warning_current(uint8_t output_pin){
	TxData[0] = 14;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void Under_current(uint8_t output_pin){
	TxData[0] = 13;
	TxData[1] = output_pin;
	CanSend(TxData);
}

void Send_current(uint8_t output_pin, uint16_t current){
	uint8_t cur1 = current/100;
	uint8_t cur2 = current%100;
	TxData[0] = 16;
	TxData[1] = output_pin;
	TxData[2] = cur1;
	TxData[3] = cur2;
	CanSend(TxData);
}

void decode(){
	
	switch (RxMessage.Bytes[0]) //PWM or switch output
	{
		case 1:
			PWM_width[RxMessage.Bytes[1]] = RxMessage.Bytes[2]; // 0 - htim1 1 - htim2
			(RxMessage.Bytes[1]) ? set_pwm_duty_cycle(&htim2) : set_pwm_duty_cycle(&htim1);
			break;
		case 2:
				Default_Switch_State = set_bit(Default_Switch_State,RxMessage.Bytes[1],RxMessage.Bytes[2]);
				switch_output();
				break;
		default:

			break;

	}
}



void Current_Sense_process(){
	//4031 == 3.3V since 12bit, have to pick shunt resistor according to this
	for(int i = 0; i < 8; i++){
		outputs[i].raw_current = outputs[i].Current_Sense[0];
		for(int z = 1; z < I_AVERAGE; z++){
				outputs[i].raw_current = outputs[i].raw_current + outputs[i].Current_Sense[z];
		}
		outputs[i].actual_current = Current_Sense_Raw_to_mA(outputs[i].raw_current/I_AVERAGE);
		if ((outputs[i].device != NC) && (outputs[i].actual_current != 0)){
			Send_current(i, outputs[i].actual_current);
		}
	}
	check_warnings();
}

void check_warnings(){
	for(uint8_t x = 0; x < 7; x++){
		if(outputs[x].device != NC){
			if(outputs[x].actual_current >= outputs[x].Warning_Current){
				if(outputs[x].actual_current >= outputs[x].Over_Current){
					Default_Switch_State = set_bit(Default_Switch_State, outputs[x].pin, 0);
					Over_current(x);
				}else{
					Warning_current(x);
				}
			}
		}
		if(outputs[x].actual_current < outputs[x].Under_Current){
			Under_current(x);
		}
	}
	switch_output();
}


void ConfigureCurrentSense(uint8_t SEL0, uint8_t SEL1){
	HAL_GPIO_WritePin(GPIOB,SEL0_Pin,SEL0);
	HAL_GPIO_WritePin(GPIOB,SEL1_Pin,SEL1);
}

void ReadADCValues(uint16_t *adc1_values, uint16_t *adc2_values){
	for(int i = 0; i < I_AVERAGE; i++){
		for(volatile int d = 0; d<5000; ++d);
		if(HAL_ADC_Start(&hadc1)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_Start(&hadc2)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_PollForConversion(&hadc1,100)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_PollForConversion(&hadc2,100)!=HAL_OK){Error_Handler();}
        adc1_values[i] = (uint16_t)HAL_ADC_GetValue(&hadc1);
        adc2_values[i] = (uint16_t)HAL_ADC_GetValue(&hadc2);
		if(HAL_ADC_Stop(&hadc1)!=HAL_OK){Error_Handler();}
		if(HAL_ADC_Stop(&hadc2)!=HAL_OK){Error_Handler();}
	}
}

void Current_Sense_read(){
	for(int x = 0;x < 5; x++){
		switch(x){
		case 0:
			if((outputs[0].device != NC) || (outputs[4].device != NC)){
				ConfigureCurrentSense(0, 0);
				ReadADCValues(outputs[0].Current_Sense, outputs[4].Current_Sense);
				break;
			}
		case 1:
			if((outputs[1].device != NC) || (outputs[5].device != NC)){
				ConfigureCurrentSense(0, 1);
				ReadADCValues(outputs[1].Current_Sense, outputs[5].Current_Sense);
				break;
			}
		case 2:
			if((outputs[2].device != NC) || (outputs[6].device != NC)){
				ConfigureCurrentSense(1, 0);
				ReadADCValues(outputs[2].Current_Sense, outputs[6].Current_Sense);
				break;
			}
		case 3:
			if((outputs[3].device != NC) || (outputs[7].device != NC)){
				ConfigureCurrentSense(1, 1);
				ReadADCValues(outputs[3].Current_Sense, outputs[7].Current_Sense);
				break;
			}
		}
	}
	Current_Sense_process();
}

uint8_t check_bit(uint8_t byte, uint8_t bitn){
	uint8_t buffer = 1<<bitn;
	if (byte & buffer){
		return 1;
	}else{
		return 0;
	}
}

uint8_t set_bit(uint8_t byte, uint8_t pos, uint8_t new_bit){
	uint8_t mask = 1 << pos;
	if(new_bit == 1){
		byte |= mask;
	}else{
		byte &= ~mask;
	}
	return byte;
}

uint16_t Current_Sense_Raw_to_mA(uint16_t raw){
	//4095 is the max, depending on resistors we will find the current values		3.3 V == 4,95 A
	//uint32_t max_mA = 4950;
	uint16_t current = 0;
	uint16_t cal = 12;
	current = raw * 150 * 33 * cal / (4095 * 10);
	//current = raw*3300 / 4095;

	return current;
}

