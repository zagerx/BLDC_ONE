/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN Private defines */
#define CH1_PWM_START HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1)
#define CH2_PWM_START HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2)
#define CH3_PWM_START HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3)

#define CH1_PWM_STOP HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1)
#define CH2_PWM_STOP HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2)
#define CH3_PWM_STOP HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3)

#define SET_CH1_PWMDUTY(duty)  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,duty)
#define SET_CH2_PWMDUTY(duty)  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,duty)
#define SET_CH3_PWMDUTY(duty)  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3,duty)


#define GET_TIM_COUNTER()     __HAL_TIM_GET_COUNTER(&htim2)
#define SET_TIM_COUNTER(counter)     __HAL_TIM_SET_COUNTER(&htim2,counter)
#define ENABLE_TIM()          __HAL_TIM_ENABLE(&htim2)
#define DISABLE_TIM()         __HAL_TIM_DISABLE(&htim2)
#define ENABLE_TIM_IT()       __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE)
#define DISABLE_TIM_IT()      __HAL_TIM_DISABLE_IT(&htim2,TIM_IT_UPDATE)

/* USER CODE END Private defines */

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM14_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
