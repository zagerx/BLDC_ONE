#include "stdbool.h"
#include "bldc_driver.h"
NOHALL_DataTypeDef Nohall_data;
Motor_StatusTypeDef motorstatus;
/*电机参数初始化*/
void motor_paraminit(void)
{
  motorstatus.Running = 0;
}
/*电机定位*/
static void motor_positioning(void)
{

}
/*强制拖动*/
static void motor_forcedrag(void)
{
  if(motorstatus.Running)
  {

  }else{

  }
}
/*电机换相*/
void motor_changedir(void)
{
  switch (Nohall_data.weizhi)
  {
  case  0:
    /* code */
    A_H_ON;B_H_OFF;C_H_OFF;
    A_L_OFF;B_L_ON;C_L_OFF;
    break;
  case 1:
    A_H_ON;B_H_OFF;C_H_OFF;
    A_L_OFF;B_L_OFF;C_L_ON;  
    break;
  case 2:
    break;
    
  default:
    break;
  }
}

/*
**换相周期(10us)定时器回调函数
**1、空载拖动到1000Rmp  1000Rmp--->T换相:
*/
void changedir_callbaack(void)
{
  static unsigned short cur_T;//当前换相周期cut_T=30代表  回调间隔（10us）* 30 
  static unsigned short cnt;
  cur_T = 33;
  if(cur_T > 10)     //还需要继续更新换相周期
  {
    cur_T--;
  }else{             //代表换相周期已经达到启动转速所对应周期了
    
  }
  //换相
  motor_changedir();

  //获取当前换相时刻点
}