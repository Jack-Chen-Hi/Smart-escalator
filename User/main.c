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
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
//***************************���þֲ�����***************************//
u8 buff[30];//������ʾ��������
u8 motor_status=1;
u8 fault,stop,start;
uint32_t weight_shiwu;
u16 people_sum;
u8 flag;
//*****************************************************************//
void WIFI_Contection(void);//WiFi���ӿ���
void Gizwits_Init(void);
int main(void)
{	
	
	delay_init();	    //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	BEEP_Init();//��������ʼ��
	LED_Init();		//LED��ʼ����
	IIC_Init();				//I2C���߳�ʼ��
	OLED_Init();			//��ʾ����ʼ��
	OLED_Clear();				//OLED����
	HX711_GPIO_Init();
	EXTIX_Init();
	Motor_Init();//���������ʼ��
	uart1_init(9600);
	Gizwits_Init();//������Э���ʼ��	
	gizwitsSetMode(WIFI_SOFTAP_MODE);//softapģʽ����
	
	
	OLED_Clear();				//OLED����
	OLED_ShowCHinese(16,0,0);//���ܷ���ϵͳ
	OLED_ShowCHinese(32,0,1);
	OLED_ShowCHinese(48,0,2);
	OLED_ShowCHinese(64,0,3);
	OLED_ShowCHinese(80,0,4);
	OLED_ShowCHinese(96,0,5);
	OLED_ShowCHinese(0,2,6);//����
	OLED_ShowCHinese(16,2,7);	
	OLED_ShowString(32, 2,":",16);
	OLED_ShowCHinese(0,4,8);//����
	OLED_ShowCHinese(16,4,9);	
	OLED_ShowString(32, 4,":",16);
	OLED_ShowCHinese(0,6,10);//�ٶ�
	OLED_ShowCHinese(16,6,11);	
	OLED_ShowString(32, 6,":",16);
	OLED_ShowCHinese(40,6,13);//����
	OLED_ShowCHinese(56,6,10);	
	OLED_ShowCHinese(72,6,16);//����
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
			OLED_ShowCHinese(40,6,14);//ֹͣ
			OLED_ShowCHinese(56,6,15);	
		}
		if(motor_status==1)
		{	
			OLED_ShowCHinese(40,6,13);//����
			OLED_ShowCHinese(56,6,10);	
		}
		if(motor_status==2)
		{	
			OLED_ShowCHinese(40,6,12);//����
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
		userHandle();		//�û����ݲɼ�
		gizwitsHandle((dataPoint_t *)&currentDataPoint);//������Э�鴦��
		delay_ms(100);
	}
}

	
//Э���ʼ��
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
  usart2_init(9600);//WIFI��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();//��������ʼ��
}

void WIFI_Contection(void)//WiFi���ӿ���
{
	
	gizwitsSetMode(WIFI_SOFTAP_MODE);//softapģʽ����
	//gizwitsSetMode(WIFI_RESET_MODE);
}
/*********************************************END OF FILE**********************/
