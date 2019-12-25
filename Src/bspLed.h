#ifndef BSP_LED_H
#define BSP_LED_H

#include "STC15xx.H"
#include "stc15xx_gpio.h"
#include "stc15xx_timer.h"

/******************************************
��ͨ��ɫLED��
*******************************************/
sbit YellowLedPIN = P3^5;
sbit RedLedPIN = P4^1;

typedef enum
{
	YellowLed = 1,
	RedLed
}LED;
void bsp_GennealLedInit();
void OpenLed(LED led);
void CloseLed(LED led);

/***********************************************
�����RGB���ƴ���
***********************************************/

sbit KMBLed = P3^2;
sbit KMRLed = P3^3;
sbit KMGLed = P3^4;

typedef enum
{
	Blue = 1,
	Red = 2,
	Green = 3,
	Yellow = 4,
	Off = 5
}RGBLED;
void bsp_MiniRgbCtlInit();
void bsp_MiniRgbCtl(RGBLED Color);

/***********************************************
�����RGB���ƴ���
***********************************************/


/***********************************************
��ƴ�RGB���ƴ���
***********************************************/

sbit KBBLed = P4^4;
sbit KBRLed = P4^2;
sbit KBGLed = P4^3;

void bsp_BigRgbCtlInit();
void bsp_BigRgbCtl(RGBLED Color);
RGBLED  bsp_BitRgbRead();
#endif