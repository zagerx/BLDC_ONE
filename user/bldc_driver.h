#ifndef _BLDC_DRIVER_H
#define _BLDC_DRIVER_H

#define A_H_ON          //A相上桥开
#define B_H_ON          
#define C_H_ON
#define A_H_OFF
#define B_H_OFF
#define C_H_OFF

#define A_L_ON          //A相上桥开
#define B_L_ON          
#define C_L_ON
#define A_L_OFF
#define B_L_OFF
#define C_L_OFF

typedef struct
{
  /* data */
  unsigned char weizhi;//当前位置
}NOHALL_DataTypeDef;

typedef struct
{
  /* data */
  bool Running;//true 运行态
}Motor_StatusTypeDef;

#endif
