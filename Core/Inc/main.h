/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "config.h"
#include "functions.h"
#include "commands.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IN1_2_Pin GPIO_PIN_1
#define IN1_2_GPIO_Port GPIOA
#define IN0_2_Pin GPIO_PIN_4
#define IN0_2_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_9
#define IN3_GPIO_Port GPIOA
#define IN2_Pin GPIO_PIN_10
#define IN2_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_15
#define IN1_GPIO_Port GPIOA
#define IN0_Pin GPIO_PIN_3
#define IN0_GPIO_Port GPIOB
#define IN3_2_Pin GPIO_PIN_4
#define IN3_2_GPIO_Port GPIOB
#define SEL1_Pin GPIO_PIN_5
#define SEL1_GPIO_Port GPIOB
#define SEL0_Pin GPIO_PIN_6
#define SEL0_GPIO_Port GPIOB
#define IN2_2_Pin GPIO_PIN_7
#define IN2_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */


extern uint8_t CAN_ID;
extern uint16_t CAN_interval;
extern uint8_t Default_Switch_State;
extern uint8_t PWM_out_enable;
extern uint16_t PWM_width[2];
extern uint16_t PWM_speed[2];
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern uint16_t us;
extern uint16_t millis;
extern uint8_t can_select;
extern FDCAN_HandleTypeDef hfdcan1;

extern FDCAN_RxHeaderTypeDef RxHeader;
extern FDCAN_TxHeaderTypeDef TxHeader;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim2;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
