#ifndef BSP_KEYSCANF_H
#define BSP_KEYSCANF_H

#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"

sbit KEY1_PIN	= P5^4;
sbit KEY2_PIN = P5^5;
sbit KEY3_PIN	= P4^0;
sbit KEY4_PIN = P4^6;

void bspKeyScanfDel();
void bspKeyScanfInit();
uint8_t bspKeyScanf();
#endif