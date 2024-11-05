#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY1    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取按键1
#define KEY2    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//读取按键2
#define KEY1_PRES 1	//KEY1按下
#define KEY2_PRES	2	//KEY2按下
void KEY_Init(void);//IO初始化			    
#endif
