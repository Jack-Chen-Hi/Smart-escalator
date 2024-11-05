#include "motor.h"
void Motor_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12; //�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��
 GPIO_ResetBits(GPIOB,GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12);	//�����
}
 
void BUJING_Cotrol(u8 step)
{
		switch(step)//:A->AB->B->BC->C->CD->D->DA
	{
		case 0: BUJ1=1;BUJ2=0;BUJ3=0;BUJ4=0;break;
		case 1: BUJ1=1;BUJ2=1;BUJ3=0;BUJ4=0;break;
		case 2: BUJ1=0;BUJ2=1;BUJ3=0;BUJ4=0;break;
		case 3: BUJ1=0;BUJ2=1;BUJ3=1;BUJ4=0;break;
		case 4: BUJ1=0;BUJ2=0;BUJ3=1;BUJ4=0;break;
		case 5: BUJ1=0;BUJ2=0;BUJ3=1;BUJ4=1;break;
		case 6: BUJ1=0;BUJ2=0;BUJ3=0;BUJ4=1;break;
		case 7: BUJ1=1;BUJ2=0;BUJ3=0;BUJ4=1;break;
		default: BUJ1=0;BUJ2=0;BUJ3=0;BUJ4=0;break;
	}
}


