#ifndef _BSP_DIGITAL_SENSOR_H
#define _BSP_DIGITAL_SENSOR_H


#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"

#define 	MAX_DIGITAL_SENSOR_NUM			3

sbit DigitalPin_0		= 	P1^6;
sbit DigitalPin_1		=	P1^7;
sbit DigitalPin_2		=	P4^7;

status bspDigitalSensorInit();

typedef struct tagDigitalSensor
{
	uint8_t uiValue[MAX_DIGITAL_SENSOR_NUM];
}DigitalSensor;

void bspDigitalSensorDel();
extern DigitalSensor mdDigitalSensor;
#endif
