/*
 * commands.c
 *
 *  Created on: Dec 9, 2023
 *      Author: marcelc
 */

#include "main.h"
#include "functions.h"
#include "main.h"
#include "string.h"

void set_pwm_duty_cycle(TIM_HandleTypeDef* htim)
{
  uint16_t timer_period = 0;
  if (check_bit(PWM_out_enable, 1) != 0)
  {
    timer_period = htim1.Init.Period;
    PWM_speed[0] = (PWM_width[0] * (timer_period + 1)) / 100;
  }
  else
  {
    PWM_speed[0] = 0;
  }
  if (check_bit(PWM_out_enable, 0) != 0)
  {
    timer_period = htim2.Init.Period;
    PWM_speed[1] = (PWM_width[1] * (timer_period + 1)) / 100;
  }
  else
  {
    PWM_speed[1] = 0;
  }

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM_speed[0]);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM_speed[1]);
}






