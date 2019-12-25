#ifndef _7SEG_H
#define _7SEG_H

#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"
#include "bsp_74xx595.h"

void bsp_7SegInit();
void bsp_7SegProcessDel();
#define MAX_7SEG_NUM		4			//数码管位数
#endif

