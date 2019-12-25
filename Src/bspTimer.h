#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include "STC15xx.H"
#include "stdio.h"
#include "string.h"
#include "CpuCfg.h"
#include "bspUsart.h"
#include "bspLed.h"


#define T38_4KHz (256-18432000/38400/2)         //1T

void TimerSoft50MsInter();
void Timer3Disable();
void Timer3Enable();
void Timer3Init();
void Timer3SetCounter(uint8_t uiCount);
void Timer4Disable();
void Timer4Enable();
void Timer4Init();



#endif
