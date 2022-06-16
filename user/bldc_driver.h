#ifndef _BLDC_DRIVER_H
#define _BLDC_DRIVER_H
#include "stdbool.h"

#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#define U_H_ON     CH1_PWM_START     //A相上桥开
#define V_H_ON     CH2_PWM_START     
#define W_H_ON     CH3_PWM_START

#define U_H_OFF    CH1_PWM_STOP
#define V_H_OFF    CH2_PWM_STOP
#define W_H_OFF    CH3_PWM_STOP

#define U_L_ON    _U_L_ON_           
#define V_L_ON    _V_L_ON_      
#define W_L_ON    _W_L_ON_

#define U_L_OFF   _U_L_OFF_
#define V_L_OFF   _V_L_OFF_
#define W_L_OFF   _W_L_OFF_

#define U_H_PWM_DUTY(Duty) SET_CH1_PWMDUTY(Duty)
#define V_H_PWM_DUTY(Duty) SET_CH2_PWMDUTY(Duty)
#define W_H_PWM_DUTY(Duty) SET_CH3_PWMDUTY(Duty)

#define START_ADC_MOTION  ADC_START_IT 
#define STOP_ADC_MOTION   ADC_STOP_IT



#define MIN_DUTY   640   //最小占空比
#define MID_DUTY   1600
// #define MAX_DUTY   3199  //可能是50%

#define MOTOR_DELAY(MS)            HAL_Delay(MS)

/*强拖模块定时器*/
#define ENABLE_FORCEDRAG_TIM()     HAL_TIM_Base_Start_IT(&htim14);
#define DISENABLE_FORCEDRAG_TIM()  HAL_TIM_Base_Stop_IT(&htim14);

/*计算换向定时器*/
#define GET_CHANGEDIR_TIM()        GET_TIM_COUNTER()
#define SET_CHANGEDIR_TIM(counter) //SET_TIM_COUNTER(counter)
#define ENABLE_CHANGEDIR_TIM()     //ENABLE_TIM()
#define DISABLE_CHANGEDIR_TIM()    //DISABLE_TIM()
#define ENABLE_CHANGEDIR_TIM_IT()  //ENABLE_TIM_IT()
#define DISABLE_CHANGEDIR_TIM_IT() //DISABLE_TIM_IT()

#define MOTOR_POLEPAIRS                 10
#define FORCEDRAG_START_ROTATESPEED     1000
#define FORCEDRAG_STOP_ROTATESPEED      2000 
#define FORCEDRAG_STARTFREQ             (FORCEDRAG_START_ROTATESPEED * MOTOR_POLEPAIRS) / 10  //1000HZ
#define FORCEDRAG_STOPFREQ              (FORCEDRAG_STOP_ROTATESPEED  * MOTOR_POLEPAIRS) / 10  //2000HZ

#define FORCEDRAG_START_T              10000000 / (FORCEDRAG_START_ROTATESPEED * MOTOR_POLEPAIRS)   //1000
#define FORCEDRAG_STOP_T               10000000 / (FORCEDRAG_STOP_ROTATESPEED  * MOTOR_POLEPAIRS)   //500

typedef enum{
  STOP_STATUS = 0,
  START_STATUS,
  FORCEDRAG_STATUS,
  CLOSELOOP_STATUS,
  RUNING_STATUS,
}M_STATUS;
typedef struct
{
  /*电机的运行状态*/
  volatile M_STATUS status;

  /* 电机硬件参数 */
  unsigned char pair;//磁极对数
  unsigned short kv;
  unsigned long max_rpm;
  unsigned long max_current;//最大电流

  /*软件参数*/
  unsigned char rotor_location;//转子当前位置
  double forcedrag_curfreq;    //强拖的当前频率
  unsigned long _30_angle;

}Motor_ParamTypeDef;

void force_changedir_callback(void);
void changedir_callback(void);
void motor_changedir(void);
void motor_start(void);
void motor_stop(void);
#endif
