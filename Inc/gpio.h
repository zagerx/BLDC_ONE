/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define _U_L_ON_  HAL_GPIO_WritePin(U_L_GPIO_Port, U_L_Pin, GPIO_PIN_SET)
#define _V_L_ON_  HAL_GPIO_WritePin(V_L_GPIO_Port, V_L_Pin, GPIO_PIN_SET)
#define _W_L_ON_  HAL_GPIO_WritePin(W_L_GPIO_Port, W_L_Pin, GPIO_PIN_SET)

#define _U_L_OFF_  HAL_GPIO_WritePin(U_L_GPIO_Port, U_L_Pin, GPIO_PIN_RESET)
#define _V_L_OFF_  HAL_GPIO_WritePin(V_L_GPIO_Port, V_L_Pin, GPIO_PIN_RESET)
#define _W_L_OFF_  HAL_GPIO_WritePin(W_L_GPIO_Port, W_L_Pin, GPIO_PIN_RESET)

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
