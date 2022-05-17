#ifndef _BLDC_DRIVER_H
#define _BLDC_DRIVER_H
#include "stdbool.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#define U_H_ON     CH1_PWM_START     //A相上桥开
#define V_H_ON     CH2_PWM_START     
#define W_H_ON     CH3_PWM_START
#define U_H_OFF    CH1_PWM_STOP
#define V_H_OFF    CH2_PWM_STOP
#define W_H_OFF    CH3_PWM_STOP

#define U_L_ON    _U_L_ON_                //A相上桥开
#define V_L_ON    _V_L_ON_      
#define W_L_ON    _W_L_ON_
#define U_L_OFF   _U_L_OFF_
#define V_L_OFF   _V_L_OFF_
#define W_L_OFF   _W_L_OFF_

#define U_H_PWM_DUTY(Duty) SET_CH1_PWMDUTY(Duty)
#define V_H_PWM_DUTY(Duty) SET_CH2_PWMDUTY(Duty)
#define W_H_PWM_DUTY(Duty) SET_CH3_PWMDUTY(Duty)
#define MIN_DUTY   380   //最小占空比
#define MID_DUTY   1600
#define MAX_DUTY   3000  //


#define ENABLE_FORCEDRAG_TIM()     HAL_TIM_Base_Start_IT(&htim14);
#define MOTOR_DELAY(MS)            HAL_Delay(MS)


#define MOTOR_POLEPAIRS                 4
#define FORCEDRAG_START_ROTATESPEED     600
#define FORCEDRAG_STOP_ROTATESPEED      1000 
#define FORCEDRAG_STARTFREQ             (FORCEDRAG_START_ROTATESPEED * MOTOR_POLEPAIRS) / 10
#define FORCEDRAG_STOPFREQ              (FORCEDRAG_STOP_ROTATESPEED  * MOTOR_POLEPAIRS) / 10

typedef struct
{
  /* data */
  unsigned char polepairs;//极对数
  unsigned char rotor_location;//转子当前位置
  double forcedrag_curfreq;    //强拖的当前频率
}Motor_ParamTypeDef;

typedef struct
{
  /* data */
  bool Running;//true 运行态
}Motor_StatusTypeDef;

void changedir_callbaack(void);
void motor_changedir(void);
void motor_start(void);
#endif
