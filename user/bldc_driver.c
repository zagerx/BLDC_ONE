#include "stdbool.h"
#include "bldc_driver.h"
volatile Motor_ParamTypeDef Motor1;
static unsigned long irq_T;
static unsigned long irq_cnt; //中断周期500us
static unsigned long forcedrag_curT;
static void CapacitorCharge(void);
static void motor_forcedrag(void);
/*电机参数初始化*/
void motor_paraminit(void)
{
  Motor1.pair = 7;
  Motor1.kv = 300;
  // Motor1.max_rpm = 3500;

  Motor1.status = STOP_STATUS;
}
/*
**电机启动
*/
void motor_start(void)
{
  RED_OFF;
  irq_T = 50;
  irq_cnt = 0;
  forcedrag_curT = 6000;
  /*使能 换相点定时器*/

  /*使能30度角定时器*/

  CapacitorCharge();
  motor_forcedrag();
  printf("motor start\r\n");
}
/*
**电机停止
*/
void motor_stop(void)
{
  DISENABLE_FORCEDRAG_TIM();
  U_H_OFF;V_H_OFF;W_H_OFF;
  U_L_OFF;V_L_OFF;W_L_OFF;
  STOP_ADC_MOTION;
  printf("motor stop\r\n");

}

/*给自举电容充电*/
static void CapacitorCharge(void)
{
  /*设置占空比*/
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
  Motor1.rotor_location = 2;
  motor_changedir();
  MOTOR_DELAY(10);

  /*开始强拖 使能强拖定时器*/
  Motor1.status = FORCEDRAG_STATUS;
  ENABLE_FORCEDRAG_TIM();
}
/*
**强拖处理 + 切闭环
*/

void force_changedir_callback(void)
{
  static unsigned char cnt = 0;
  
  if(Motor1.status == FORCEDRAG_STATUS)
  {/*强拖过程*/
    // printf("moto.status = %d\r\n");
    if(irq_cnt * irq_T >= forcedrag_curT)
    {
      irq_cnt = 0;
      if(forcedrag_curT <= 5000)/*已经达停止转速*/
      {
        forcedrag_curT = 5000;
        // RED_TOGGLE;
        if(cnt++ > 50)/*保持一段时间 进入反电动势检测换相点模式*/
        {
          cnt = 0;
          /**/
          // Motor1.status = CLOSELOOP_STATUS;
        }
      }else{
        forcedrag_curT -= 1;
      }
      motor_changedir();
      // printf("%d,%d \n",forcedrag_curT,1000);
    }else{
      irq_cnt += 1;
    }
  }else if(Motor1.status == CLOSELOOP_STATUS){/*进入反电动势检测换相点模式*/
    /**/
  }else{
  }
}

void changedir_callback(void)
{
  /*关闭定时器中断*/
  DISABLE_CHANGEDIR_TIM_IT();
  /**/
}
/*过零检测函数*/
void zeropoint_process_callback(float val)
{
  unsigned long temp1,temp2;
  if(val > MAX_VAL || val < MIN_VAL) //
  {
    /*是过零点 获取换相时刻到现在的时间*/
    temp1 = Motor1._30_angle;
    temp2 = GET_CHANGEDIR_TIM();
    Motor1._30_angle = temp1 * 0.3 + temp2 * 0.7;//滤波处理
    Motor1._30_angle += 15;//消磁处理 
    /*定时后30度所需时间*/
    ENABLE_CHANGEDIR_TIM();
    SET_CHANGEDIR_TIM(Motor1._30_angle);
    ENABLE_CHANGEDIR_TIM_IT();
  }
}

/*定时换相回调函数*/

/*
电机换相
*/
void motor_changedir(void)
{
  /*清零计时器并且使能*/
  SET_CHANGEDIR_TIM(0);
  ENABLE_CHANGEDIR_TIM();
  
  RED_TOGGLE;
  printf("<");
  START_ADC_MOTION;
  /*开始换相*/
  switch (Motor1.rotor_location)
  {
  case  1:
    /* code W+  V- */
    U_H_OFF;V_H_OFF;
    U_L_OFF;        W_L_OFF;
    W_H_ON;
    V_L_ON;
    Motor1.rotor_location = 2;
    /*启动测量U相ADC通道*/
    break;
  case 2:
  /* code W+  U- */
    U_H_OFF;V_H_OFF;
            V_L_OFF;W_L_OFF;  
    W_H_ON;
    U_L_ON;
    Motor1.rotor_location = 3;
    /*启动测量V相ADC通道*/
    break;
  case 3:
  /* code V+  U- */
    U_H_OFF;       W_H_OFF;
            V_L_OFF;W_L_OFF;
    V_H_ON;  
    U_L_ON;
    Motor1.rotor_location = 4;  
    /*启动测量W相ADC通道*/
    break;
  case 4:
  /* code V+  W- */
    U_H_OFF;        W_H_OFF;
    U_L_OFF;V_L_OFF; 
    V_H_ON; 
    W_L_ON;
    Motor1.rotor_location = 5;  
    /*启动测量U相ADC通道*/
    break;
  case 5:
  /* code U+  W- */
            V_H_OFF;W_H_OFF;
    U_L_OFF;V_L_OFF; 
    U_H_ON;
    W_L_ON; 
    Motor1.rotor_location = 6;  
    /*启动测量V相ADC通道*/
    break;
  case 6:
  /* code U+  V- */
           V_H_OFF;W_H_OFF;
    U_L_OFF;        W_L_OFF;  
    U_H_ON;
    V_L_ON;
    Motor1.rotor_location = 1;  
    /*启动测量W相ADC通道*/
    break;            
  default:
    break;
  }
}
