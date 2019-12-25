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
	uint32_t uiCurMM;//��ǰ������׵�λ
	float 	uiCurM;//��ǰ�����׵�λ
	uint32_t uiCurErroeCode;//��ǰ��������
}SensorInfo;
void bspDelSensorBack();
#define ERROR1 		 0xFF000000  /*�������*/
#define ERROR2		 0xFE000000 /*�޷��ع�*/
#define ERROR3     0xFD000000	/*���ع�ǿ*/
#define ERROR4     0xFC000000  /*��������*/
extern SensorInfo mdSensorInfo[2];
#endif