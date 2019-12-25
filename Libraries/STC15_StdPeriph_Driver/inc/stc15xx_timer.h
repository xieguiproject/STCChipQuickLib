#ifndef STC15XX_TIMER_H
#define STC15XX_TIMER_H

#include "STC15xx.H"

#define	Timer0						0
#define	Timer2						2
#define	Timer1						1
#define	Timer3						3
#define	Timer4						4


#define	TIM_16BitAutoReload			0		//16位自动重装
#define	TIM_16Bit					1		//16位
#define	TIM_8BitAutoReload			2		//8位自动重装
#define	TIM_16BitAutoReloadNoMask	3		//16位自动重装

#define	TIM_CLOCK_1T				0		//1T模式
#define	TIM_CLOCK_12T				1		//12T模式
#define	TIM_CLOCK_Ext				2		


typedef struct
{
	uint8_t	TIM_Mode;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	//uint8_t	TIM_Polity;		//优先级设置	PolityHigh,PolityLow
	uint8_t	TIM_Interrupt;	//中断允许		ENABLE,DISABLE
	uint8_t	TIM_ClkSource;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	uint8_t	TIM_ClkOut;		//可编程时钟输出,	ENABLE,DISABLE
	uint8_t	TIM_HValue;	   //装载初值
	uint8_t	TIM_LValue;	   //装载初值
	uint8_t	TIM_Run;		//是否运行		ENABLE,DISABLE
} TIM_InitTypeDef;

#define  TimerH(Us,ClkSource) (65536 - (MAIN_Fosc / (ClkSource == 0?1:12)) / (1000 / Us)) / 256
#define  TimerL(Us,ClkSource) (65536 - (MAIN_Fosc / (ClkSource == 0?1:12)) / (1000 / Us)) % 256
 

status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef);
void bspTimer_Cmd(uint8_t uiTimerNo,FunctionalState State);

//回调函数模型
typedef void * (*TimerTaskHook)(void *arg);

//下面实现一个任务队列，任务队列中不能执行耗时任务
typedef struct tagTimerTaskInfo
{
	uint16_t uiCount;//定时计数器
	uint16_t uiIntTime;//单位ms //执行周期
	uint16_t uiRunTime;//运行次数
	TimerTaskHook  Hook;//回调函数
	uint16_t  ucUseState;
}TimerTaskInfo;
typedef struct tagTimerInitValue
{
	uint8_t	TIM_HValue;	   //装载初值
	uint8_t	TIM_LValue;	   //装载初值
}TimerInitValue;

#define MAX_TIMER_TASK  			5

int8_t bspTimerTaskGetItem();
void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime);
void bspTimerTaskInit();
void bspTimeDelayInit();//系统节拍时间初始化
void bspTimeDelay(uint16_t uiDelayMs);
#endif
