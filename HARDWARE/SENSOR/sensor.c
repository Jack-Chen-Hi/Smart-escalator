#include "sensor.h"
void SENSOR_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; //定义结构体变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟
	GPIO_InitStructure.GPIO_Pin = SENSOR1_PIN |SENSOR2_PIN; //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //设置输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置GPIO端口速度
	GPIO_Init(SENSOR1_GPIO,&GPIO_InitStructure); //初始化GPIO
}
 
