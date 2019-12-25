#ifndef _BSP_GET_MM_H
#define _BSP_GET_MM_H

#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"
#include "stc15xx_usart.h"

void bspGetmmUsartInit();
void bspGetmm();

typedef struct tagSensorInfo
{
	uint32_t uiCurMM;//当前距离毫米单位
	float 	uiCurM;//当前距离米单位
	uint32_t uiCurErroeCode;//当前错误类型
}SensorInfo;
void bspDelSensorBack();
#define ERROR1 		 0xFF000000  /*计算错误*/
#define ERROR2		 0xFE000000 /*无返回光*/
#define ERROR3     0xFD000000	/*返回过强*/
#define ERROR4     0xFC000000  /*超过量程*/
extern SensorInfo mdSensorInfo[2];
#endif