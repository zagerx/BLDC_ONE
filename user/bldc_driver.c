#include "stdbool.h"
#include "bldc_driver.h"
Motor_ParamTypeDef Motor_1;
Motor_StatusTypeDef motorstatus;

static void CapacitorCharge(void);
static void motor_forcedrag(void);
/*电机参数初始化*/
void motor_paraminit(void)
{
  motorstatus.Running = 0;
}
/*
**电机启动
*/
void motor_start(void)
{
  CapacitorCharge();
  motor_forcedrag();
}
/*
**电机停止
*/
void motor_stop(void)
{
  
}

/*给自举电容充电*/
static void CapacitorCharge(void)
{
  U_H_PWM_DUTY(MID_DUTY);
  V_H_PWM_DUTY(MID_DUTY);
  W_H_PWM_DUTY(MID_DUTY);  
  /*关闭上桥*/
  U_H_OFF;V_H_OFF;W_H_OFF;
  /*打开下桥*/
  U_L_ON;V_L_ON;W_L_ON;
  MOTOR_DELAY(10);
  /*关闭下桥*/
  U_L_OFF;V_L_OFF;W_L_OFF;
}

/*
强拖阶段  固定占空比10%
强拖的目标频率：   
强拖的初始频率：
*/
static void motor_forcedrag(void)
{
  /*设置PWM占空比10%*/
  U_H_PWM_DUTY(MIN_DUTY);
  V_H_PWM_DUTY(MIN_DUTY);
  W_H_PWM_DUTY(MIN_DUTY);

  /*转子定位*/
  Motor_1.rotor_location = 5;
  motor_changedir();
  MOTOR_DELAY(10);

  /*开始强拖 使能强拖定时器*/
  ENABLE_FORCEDRAG_TIM();
  /*设置当前频率为初始频率 */
  Motor_1.forcedrag_curfreq = FORCEDRAG_STARTFREQ;//2400 / 10 = 240

}
/*
**换相周期(500us)定时器回调函数
**1、空载拖动到1000Rmp  1000Rmp--->T换相:
*/
void changedir_callbaack(void)
{
  static unsigned long irq_freq;
  static unsigned long irq_cycle = 0; //中断周期
  // irq_freq = 1 / irq_cycle * 1000000;//计算中断频率
  // if(irq_freq <= Motor_1.forcedrag_curfreq)//说明换相周期到达
  // {
  //   motor_changedir();
  //   if(Motor_1.forcedrag_curfreq >= FORCEDRAG_STOPFREQ) //强拖到指定转速 保持
  //   {
      
  //   }else{
  //     Motor_1.forcedrag_curfreq += 10;
  //   }
  //   irq_freq = 10;//重新更新中断频率
  // }else{//更新中断频率
  //   irq_cycle++;
  // }
  if(irq_cycle++ >= 12)
  {
    irq_cycle = 0;
    motor_changedir();
  }
}

/*电机换相
ch1-u  ch2-v  ch3-w   5  1  3  2  6  4
*/
void motor_changedir(void)
{
  
  switch (Motor_1.rotor_location)
  {
  case  1:
    /* code W+  V- */
    U_H_OFF;V_H_OFF;
    U_L_OFF;        W_L_OFF;
    W_H_ON;
    V_L_ON;
    Motor_1.rotor_location = 2;
    break;
  case 2:
  /* code W+  U- */
    U_H_OFF;V_H_OFF;
            V_L_OFF;W_L_OFF;  
    W_H_ON;
    U_L_ON;
    Motor_1.rotor_location = 3;
    break;
  case 3:
  /* code V+  U- */
    U_H_OFF;       W_H_OFF;
            V_L_OFF;W_L_OFF;
    V_H_ON;  
    U_L_ON;
    Motor_1.rotor_location = 4;  
    break;
  case 4:
  /* code V+  W- */
    U_H_OFF;        W_H_OFF;
    U_L_OFF;V_L_OFF; 
    V_H_ON; 
    W_L_ON;
    Motor_1.rotor_location = 5;  
    break;
  case 5:
  /* code U+  W- */
            V_H_OFF;W_H_OFF;
    U_L_OFF;V_L_OFF; 
    U_H_ON;
    W_L_ON; 
    Motor_1.rotor_location = 6;  
    break;
  case 6:
  /* code U+  V- */
           V_H_OFF;W_H_OFF;
    U_L_ON;        W_L_OFF;  
    U_H_ON;
    V_L_ON;
    Motor_1.rotor_location = 1;  
    break;            
  default:
    break;
  }
}
