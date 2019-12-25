/***********************************************************************************
 * �� �� ��   : bspPwm.h
 * �� �� ��   : xiegui
 * ��������   : 2018��11��16��
 * �ļ�����   : PWMģ��ͷ�ļ�
 * ��Ȩ˵��   : Copyright (c) 2008-2018   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
***********************************************************************************/
#ifndef BSP_PWM_H
#define BSP_PWM_H


#include "STC15xx.H"

#include "intrins.h"
#include "bspUsart.h"
#include "string.h"
#include <stdlib.h>

#include "stdio.h"
#include "Main.h"

typedef enum
{ 
	PWM_Clock_SysClkDiv = 0x00,//ѡ�񾭹���Ƶ����Ƶ֮���ʱ��
	PWM_Clock_OverFlowT2 = 0x01//ѡ��T2���ʱ��
}PWMClock_TypeDef;
/*pwmʱ��Դ*/

typedef enum
{ 
	PWM_Out_Pin_Mode0 = 0x00,//pwm2 P3.7 P2.1 P2.2 P2.3 P1.6 P1.7
	PWM_Out_Pin_Mode1 = 0x01,//pwm2 P2.7 P4.5 P4.4 P4.2 P0.7 P0.6
}PWMOutPin_TypeDef;
/*����3��PWM���������λ��CCP_S1,CCP_S0*/

typedef struct
{
	PWMClock_TypeDef PwmClk;		/*Ƶ��*/
	PWMOutPin_TypeDef OutPinMode;/*�������ģʽ*/
	uint8_t fDutyRate;			/*ռ�ձ�*/
	uint16_t uiCycle;			/*����*/
}PWM_InitTypeDef;



sbit PWM1 = P3^7;
sbit PWM2 = P2^7;
void bspPwmGpioDefInit();
void BspPwmMoto();
void CheckCmd();
void bspPwmCmd(FunctionalState state);
void bspPwmInit(uint8_t uiPwmNum,uint8_t uiPwmClk,uint8_t fDutyRate,uint16_t uiCycle);
void BpsMotoCtrl(uint8_t iDir,uint8_t uiMode,float fDutyRate);
void bspSetPwmDutyRate(uint8_t uiDutyRate);
void Delay1ms(void);
void MotoSetPosition(float fSetPositionCm);
void DelayMs(unsigned int time);
#endif /* BSP_PWM_H */
