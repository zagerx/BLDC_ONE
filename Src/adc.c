/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
uint32_t adc_buf[4] = {0xFFFE,0xFFFE,0xFFFE,0xFFFE};
void Motor_ADC_Start_DMA(void)
{
   #if 1
    float u_vla,v_vla,w_vla,n_vla;
    float eu_vla,ev_vla,ew_vla,en_vla;

    /*端电�?????*/
    u_vla = (float)(adc_buf[0]) / 4096  * 3.3;
    v_vla = (float)(adc_buf[1]) / 4096  * 3.3;
    w_vla = (float)(adc_buf[2]) / 4096  * 3.3;
    //中�?�点电压
    n_vla = (float)(adc_buf[3]) / 4096  * 3.3;
    //反电动势
    // eu_vla = u_vla - (float)((v_vla + w_vla)/2);
    // ev_vla = v_vla - (float)((u_vla + w_vla)/2);
    // ew_vla = w_vla - (float)((v_vla + u_vla)/2);
    // printf("%d %d %d \r\n",adc_buf[0],adc_buf[1],adc_buf[2]);

    /*反电动势*/ 
    en_vla = (float)((u_vla + v_vla + w_vla)/3);
    eu_vla = u_vla - en_vla;
    ev_vla = v_vla - en_vla;;
    ew_vla = w_vla - en_vla;;
    // printf("%d %d %d \r\n",adc_buf[0],adc_buf[1],adc_buf[2]);
    // printf("%.2f,%.2f,%.2f,%.2f,%.2f \n",ew_vla,eu_vla,ev_vla,en_vla,n_vla);
    // printf("%.2f,%.2f,%.2f \n",w_vla,u_vla,v_vla);
  #else
    uint32_t u_adc,v_adc,w_adc;
    uint32_t eu_adc,ev_adc,ew_adc;
    u_adc = adc_buf[0];
    v_adc = adc_buf[1];
    w_adc = adc_buf[2];

    eu_adc = u_adc + (v_adc + w_adc)/2;
    ev_adc = v_adc + (u_adc + w_adc)/2;
    ew_adc = w_adc + (v_adc + u_adc)/2;
    printf("%d,%d,%d \r\n",eu_adc,ev_adc,ew_adc);
  #endif


  HAL_ADC_Start_DMA(&hadc,adc_buf,4); 
}
/* USER CODE END 0 */

ADC_HandleTypeDef hadc;

/* ADC init function */
void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = ENABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC GPIO Configuration
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA4     ------> ADC_IN4
    PA5     ------> ADC_IN5
    */
    GPIO_InitStruct.Pin = W_AD_CHANNEL_Pin|EN_AD_CHANNEL_Pin|V_AD_CHANNEL_Pin|U_AD_CHANNEL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC GPIO Configuration
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA4     ------> ADC_IN4
    PA5     ------> ADC_IN5
    */
    HAL_GPIO_DeInit(GPIOA, W_AD_CHANNEL_Pin|EN_AD_CHANNEL_Pin|V_AD_CHANNEL_Pin|U_AD_CHANNEL_Pin);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC1_COMP_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/*
采集电压数据的回调函�??? 该函数可以是ADC中断回调/DMA中断回调 
总之在该函数中要处理ADC数据
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  uint32_t val;
 /*数据处理*/
  val = HAL_ADC_GetValue(hadc);
  printf("adc = %d\r\n",val);
 /*使能TIM3定时30度时*/
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
