#include "stm32f10x_it.h"
#include "sys.h"
#include "stdio.h" 
#include "iic.h"
#include "oled.h"
#include "usart1.h"
#include "usart2.h"
#include "ADC.h"
#include "beep.h"
#include "led.h"
#include "motor.h"
#include "key.h"
#include "sensor.h"
#include "HX711.h"
#include "timer.h"
#include "gizwits_product.h"
#include "EXTI.h"
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
//***************************设置局部变量***************************//
u8 buff[30];//参数显示缓存数组
u8 motor_status=1;
u8 fault,stop,start;
uint32_t weight_shiwu;
u16 people_sum;
u8 flag;
//*****************************************************************//
void WIFI_Contection(void);//WiFi连接控制
void Gizwits_Init(void);
int main(void)
{	
	
	delay_init();	    //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	BEEP_Init();//蜂鸣器初始化
	LED_Init();		//LED初始化化
	IIC_Init();				//I2C总线初始化
	OLED_Init();			//显示屏初始化
	OLED_Clear();				//OLED清屏
	HX711_GPIO_Init();
	EXTIX_Init();
	Motor_Init();//电机驱动初始化
	uart1_init(9600);
	Gizwits_Init();//机智云协议初始化	
	gizwitsSetMode(WIFI_SOFTAP_MODE);//softap模式接入
	
	
	OLED_Clear();				//OLED清屏
	OLED_ShowCHinese(16,0,0);//智能扶梯系统
	OLED_ShowCHinese(32,0,1);
	OLED_ShowCHinese(48,0,2);
	OLED_ShowCHinese(64,0,3);
	OLED_ShowCHinese(80,0,4);
	OLED_ShowCHinese(96,0,5);
	OLED_ShowCHinese(0,2,6);//人数
	OLED_ShowCHinese(16,2,7);	
	OLED_ShowString(32, 2,":",16);
	OLED_ShowCHinese(0,4,8);//载重
	OLED_ShowCHinese(16,4,9);	
	OLED_ShowString(32, 4,":",16);
	OLED_ShowCHinese(0,6,10);//速度
	OLED_ShowCHinese(16,6,11);	
	OLED_ShowString(32, 6,":",16);
	OLED_ShowCHinese(40,6,13);//低速
	OLED_ShowCHinese(56,6,10);	
	OLED_ShowCHinese(72,6,16);//报警
	OLED_ShowCHinese(88,6,17);	
	OLED_ShowString(104, 6,":",16);
	OLED_ShowCHinese(112,6,19);	
	//WIFI_Contection();
	while(1)
	{
		sprintf(buff,"%4u",people_sum);
		OLED_ShowString(40,2,buff,16);
		weight_shiwu = Get_Weight();
		sprintf(buff,"%8ug",weight_shiwu);
		OLED_ShowString(40,4,buff,16);
		
		if(motor_status==0)
		{	
			OLED_ShowCHinese(40,6,14);//停止
			OLED_ShowCHinese(56,6,15);	
		}
		if(motor_status==1)
		{	
			OLED_ShowCHinese(40,6,13);//低速
			OLED_ShowCHinese(56,6,10);	
		}
		if(motor_status==2)
		{	
			OLED_ShowCHinese(40,6,12);//高速
			OLED_ShowCHinese(56,6,10);	
		}	
		if(weight_shiwu >600)
		{
			LED=0;
			BEEP=0;
			OLED_ShowCHinese(112,6,18);	
			motor_status=0;
			fault=1;
		}
		else if(flag)
		{
			motor_status=0;
			fault=0;
		}
		else
		{
			LED=1;
			BEEP=1;	
			fault=0;
			OLED_ShowCHinese(112,6,19);	
			if(people_sum) motor_status=2;
			else motor_status=1;
		}
		userHandle();		//用户数据采集
		gizwitsHandle((dataPoint_t *)&currentDataPoint);//机智云协议处理
		delay_ms(100);
	}
}

	
//协议初始化
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1MS系统定时
  usart2_init(9600);//WIFI初始化
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}

void WIFI_Contection(void)//WiFi连接控制
{
	
	gizwitsSetMode(WIFI_SOFTAP_MODE);//softap模式接入
	//gizwitsSetMode(WIFI_RESET_MODE);
}
/*********************************************END OF FILE**********************/
