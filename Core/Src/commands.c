/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"
#include "string.h"

uint16_t timer_period;

void set_pwm_duty_cycle(TIM_HandleTypeDef *htim){
	if(CheckBit(PWM_out_enable,1) != 0){
		timer_period=htim1.Init.Period;
		PWM_speed[0] = (PWM_width[0] * (timer_period + 1))/100;
	}else{
		PWM_speed[0] = 0;
	}
	if(CheckBit(PWM_out_enable,0) != 0){
		timer_period=htim2.Init.Period;
		PWM_speed[1] = (PWM_width[1] * (timer_period + 1))/100;
	}else{
		PWM_speed[1] = 0;
	}
}






