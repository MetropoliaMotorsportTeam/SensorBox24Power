/*
 * currentSense.c
 *
 *  Created on: Nov 16, 2025
 *      Author: dovlatib
 */

#include "main.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx.h"
#include "stdio.h"
#include "config.h"
#include "currentSense.h"

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


void CurrentSenseProcess(){
	//4031 == 3.3V since 12bit, have to pick shunt resistor according to this
	for(int i = 0; i < 8; i++){
		outputs[i].raw_current = outputs[i].Current_Sense[0];
		for(int z = 1; z < I_AVERAGE; z++){
				outputs[i].raw_current = outputs[i].raw_current + outputs[i].Current_Sense[z];
		}
		outputs[i].actual_current = CurrentSenseRawTomA(outputs[i].raw_current/I_AVERAGE);
		if ((outputs[i].device != NC) && (outputs[i].actual_current != 0)){
			SendCurrent(i, outputs[i].actual_current);
		}
	}
	CheckWarnings();
}

void CurrentSenseRead(){
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
	CurrentSenseProcess();
}


uint16_t CurrentSenseRawTomA(uint16_t raw){
	//4095 is the max, depending on resistors we will find the current values		3.3 V == 4,95 A
	//uint32_t max_mA = 4950;
	uint16_t current = 0;
	uint16_t cal = 10;
	current = raw * 150 * 33 * cal / (4095 * 10);
	//current = raw*3300 / 4095;

	return current;
}
