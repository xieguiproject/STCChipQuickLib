#ifndef _74XX595_H
#define _74XX595_H

#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"

sbit L74XX595_CLK = P1^3;
sbit L74XX595_IO = P1^4;
sbit L74XX595_SHR = P1^5;

#define L74XX595_bit 	1 //这个定义控制595的多少位，
#define L74xx595_num 	(L74XX595_bit/8+1) //这里来标示使用了几片595芯片

uint8_t L74xx595_Wirte_One_Byte(uint8_t dat);
status bsp74lx595Init();

#endif