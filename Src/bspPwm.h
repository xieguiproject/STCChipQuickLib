/***********************************************************************************
 * 文 件 名   : bspPwm.h
 * 负 责 人   : xiegui
 * 创建日期   : 2018年11月16日
 * 文件描述   : PWM模块头文件
 * 版权说明   : Copyright (c) 2008-2018   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
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
	PWM_Clock_SysClkDiv = 0x00,//选择经过分频器分频之后的时钟
	PWM_Clock_OverFlowT2 = 0x01//选择T2溢出时钟
}PWMClock_TypeDef;
/*pwm时钟源*/

typedef enum
{ 
	PWM_Out_Pin_Mode0 = 0x00,//pwm2 P3.7 P2.1 P2.2 P2.3 P1.6 P1.7
	PWM_Out_Pin_Mode1 = 0x01,//pwm2 P2.7 P4.5 P4.4 P4.2 P0.7 P0.6
}PWMOutPin_TypeDef;
/*设置3组PWM输出的引脚位置CCP_S1,CCP_S0*/

typedef struct
{
	PWMClock_TypeDef PwmClk;		/*频率*/
	PWMOutPin_TypeDef OutPinMode;/*输出引脚模式*/
	uint8_t fDutyRate;			/*占空比*/
	uint16_t uiCycle;			/*周期*/
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
