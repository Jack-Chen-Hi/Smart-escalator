#ifndef __HX711_H
#define __HX711_H
#include "stm32f10x.h"                  // Device header
void HX711_GPIO_Init(void);
void HX711_W_PD_SCK(uint8_t BitValue);
void HX711_W_DOUT(uint8_t BitValue);
void HX711_Reset(void);
uint8_t HX711_R_DOUT(void);
uint32_t HX711_ReadData(void);
uint32_t Get_Pi(void);
uint32_t Get_Weight(void);

#endif
