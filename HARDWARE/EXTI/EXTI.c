#include "EXTI.h"
#include "sys.h"
#include "key.h"
#include "sensor.h"
/**
 * 功能：初始化外部中断3
 * 参数：None
 * 返回值：None
 */
//外部中断0服务程序
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化
		SENSOR_Init();

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
   //GPIOB.6  中断线以及中断初始化配置 上升沿触发 KEY1
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
   //GPIOB.7  中断线以及中断初始化配置 下降沿触发 KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
   //GPIOB.8  中断线以及中断初始化配置 下降沿触发 IN_SENSOR 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	
   //GPIOB.9  中断线以及中断初始化配置 下降沿触发 OUT_SENSOR
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}


void EXTI9_5_IRQHandler(void)
{
		delay_ms(5);//消抖
		if(KEY1==0 || KEY2==0)	 //按键KEY1 
	{
		flag=~flag;
		if(flag) motor_status=0;
		else
		{
			if(people_sum) motor_status=2;
			else motor_status=1;
		}
		
	}	
	if(IN_SENSOR==0)	 //进
	{
		people_sum++;
		motor_status=2;
	}	
	if(OUT_SENSOR==0)	 //出
	{
		people_sum--;
		if(people_sum==65535 || people_sum==0)
		{
			people_sum=0;	
			motor_status=1;
		}

	}	
	 
	EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位  	
	EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE7上的中断标志位  
	EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位  	
	EXTI_ClearITPendingBit(EXTI_Line9);  //清除LINE9上的中断标志位  
}

