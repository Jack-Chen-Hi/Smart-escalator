#include "sensor.h"
void SENSOR_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; //����ṹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTBʱ��
	GPIO_InitStructure.GPIO_Pin = SENSOR1_PIN |SENSOR2_PIN; //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�˿��ٶ�
	GPIO_Init(SENSOR1_GPIO,&GPIO_InitStructure); //��ʼ��GPIO
}
 
