#include "stm32f10x.h"                  // Device header
#include "HX711.h"
#include "sys.h"
float	BiaoDing=205;       //�궨ϵ��,�����Լ��Ĵ���������
uint32_t weight_reset;
void HX711_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //ʱ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�����߸�������     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	weight_reset = Get_Pi();
}

void HX711_W_PD_SCK(uint8_t BitValue)                  //дʱ����
{	
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)BitValue);
}

void HX711_W_DOUT(uint8_t BitValue)                    //д�����ߣ���ʼʱ����Ҫ����DOUT��ƽ
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)BitValue);
}

uint8_t HX711_R_DOUT(void)                             //������
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
}


void HX711_Reset(void)                                 // ��������λ��ȥƤ
{
	HX711_W_PD_SCK(1);                                   //���ߣ���ʱ60us
	delay_us(60);
}

uint32_t HX711_ReadData(void)                          //������
{
	uint8_t i;
	uint32_t value = 0;    						//����HX711�ɼ���ADֵ
	
	HX711_W_DOUT(1); 									//��ʼDOUTΪ�ߵ�ƽ
	HX711_W_PD_SCK(0); 							  //��ʼPD_SCKΪ�͵�ƽ
	delay_us(1);
	HX711_R_DOUT();                   //DOUTת��Ϊ����
	
	while(HX711_R_DOUT());           //�ȴ�DOUT���ű�Ϊ�ߵ�ƽ
	delay_us(1);
	for(i=0;i<24;i++)                 //����HX711ʱ���������
	{
		HX711_W_PD_SCK(1);              // PD_SCK�øߣ��������� 
		value = value << 1;              //�½�����ʱ��������һλ���Ҳಹ�㣬
		delay_us(1);
		HX711_W_PD_SCK(0);               // PD_SCK�õ�
		if(HX711_R_DOUT())               //��ȡһλ���ݣ�����ߵ�ƽ����һ���͵�ƽ���䡣
			value++;
	  delay_us(1);
	}
	HX711_W_PD_SCK(1);               //���һ�����壬����Ϊ128
	value = value^0x800000;          //��25������ת�����ݣ�24λADת�������λΪ����λ������Ϊ��Чλ
	delay_us(1);
	HX711_W_PD_SCK(0);
	delay_us(1);
	return value;
}




uint32_t Get_Pi(void)                                  //Ƥ�غ���
{
	uint8_t MEDIAN_LEN=5,MEDIAN=3;              //��ֵ�˲�������ð������
	uint32_t   buffer[5];                //��������
	uint32_t HX711_dat,pi_weight,num;           				
	uint8_t i,medleng = 0;
	for(i=0;i<MEDIAN_LEN;i++)
	{
		HX711_dat=HX711_ReadData();	        	   
		if(medleng == 0)                           //��1��Ԫ��,ֱ�ӷ���,����Ҫ����
		{ 
			buffer[0] = HX711_dat;
			medleng = 1; 
		}
		else                            	           //��ֵ�˲���ȡ�м�ֵ��ð������
		{  
			for(i = 0; i < medleng; i ++)  
			{
				if( buffer[i] > HX711_dat) 	          
				{ 
					num = HX711_dat; HX711_dat = buffer[i]; buffer[i] = num;
				}
			}
			buffer[medleng] = HX711_dat;          	
			medleng++;
		}		
		if(medleng >= MEDIAN_LEN) 		           
		{
			HX711_dat = buffer[MEDIAN];	            //ȡ����õ��м�ֵ��
			medleng = 0; 
		}
	}
	pi_weight=HX711_dat;      
	return pi_weight;
}

uint32_t Get_Weight(void)	               //���غ���
{
	uint32_t get_weight;
	uint32_t weight;
	
	get_weight=HX711_ReadData();		            //HX711���ݲɼ�����
	if(get_weight>weight_reset)
	{			 														   
		weight=(uint32_t)(((float)(get_weight-weight_reset))/BiaoDing);//�޸ı궨ϵ�������ݴ�������ͬ
		if(weight<=100000)
			weight =weight;
		else
			weight=0;
	}
	else				
		weight=0;
	return weight;
}
