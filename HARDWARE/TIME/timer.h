#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
extern u16 time;
extern u8 motor_status;
void TIM3_Int_Init(u16 arr,u16 psc);
#endif

