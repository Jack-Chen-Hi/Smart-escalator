#ifndef __SENSOR_H
#define __SENSOR_H 
#include "sys.h"
//红外传感器 IO口设置
#define SENSOR1_PIN         GPIO_Pin_8
#define SENSOR1_GPIO        GPIOB
#define IN_SENSOR       	 	GPIO_ReadInputDataBit(SENSOR1_GPIO,SENSOR1_PIN)
#define SENSOR2_PIN         GPIO_Pin_9
#define SENSOR2_GPIO        GPIOB
#define OUT_SENSOR        	GPIO_ReadInputDataBit(SENSOR2_GPIO,SENSOR2_PIN)
void SENSOR_Init(void);//初始化		 				    
#endif
