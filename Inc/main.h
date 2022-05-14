/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define U_L_Pin GPIO_PIN_7
#define U_L_GPIO_Port GPIOA
#define V_L_Pin GPIO_PIN_0
#define V_L_GPIO_Port GPIOB
#define W_L_Pin GPIO_PIN_1
#define W_L_GPIO_Port GPIOB
#define RGB_GREEN_Pin GPIO_PIN_14
#define RGB_GREEN_GPIO_Port GPIOB
#define RGB_RED_Pin GPIO_PIN_15
#define RGB_RED_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_10
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_11
#define KEY2_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_12
#define KEY3_GPIO_Port GPIOC
#define KEY4_Pin GPIO_PIN_2
#define KEY4_GPIO_Port GPIOD
#define KEY4_EXTI_IRQn EXTI2_3_IRQn
/* USER CODE BEGIN Private defines */

#define READ_KEY1()  HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define RED_ON     HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_RESET);
#define RED_OFF    HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_SET);

#define GREEN_ON     HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_RESET);
#define GREEN_OFF    HAL_GPIO_WritePin(RGB_GREEN_GPIO_Port, RGB_GREEN_Pin, GPIO_PIN_SET);

// #define RED_ON     HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_RESET);
// #define RED_OFF    HAL_GPIO_WritePin(RGB_RED_GPIO_Port, RGB_RED_Pin, GPIO_PIN_SET);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
