#ifndef STC15XX_TIMER_H
#define STC15XX_TIMER_H

#include "STC15xx.H"

#define	Timer0						0
#define	Timer2						2
#define	Timer1						1
#define	Timer3						3
#define	Timer4						4


#define	TIM_16BitAutoReload			0		//16λ�Զ���װ
#define	TIM_16Bit					1		//16λ
#define	TIM_8BitAutoReload			2		//8λ�Զ���װ
#define	TIM_16BitAutoReloadNoMask	3		//16λ�Զ���װ

#define	TIM_CLOCK_1T				0		//1Tģʽ
#define	TIM_CLOCK_12T				1		//12Tģʽ
#define	TIM_CLOCK_Ext				2		


typedef struct
{
	uint8_t	TIM_Mode;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	//uint8_t	TIM_Polity;		//���ȼ�����	PolityHigh,PolityLow
	uint8_t	TIM_Interrupt;	//�ж�����		ENABLE,DISABLE
	uint8_t	TIM_ClkSource;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	uint8_t	TIM_ClkOut;		//�ɱ��ʱ�����,	ENABLE,DISABLE
	uint8_t	TIM_HValue;	   //װ�س�ֵ
	uint8_t	TIM_LValue;	   //װ�س�ֵ
	uint8_t	TIM_Run;		//�Ƿ�����		ENABLE,DISABLE
} TIM_InitTypeDef;

#define  TimerH(Us,ClkSource) (65536 - (MAIN_Fosc / (ClkSource == 0?1:12)) / (1000 / Us)) / 256
#define  TimerL(Us,ClkSource) (65536 - (MAIN_Fosc / (ClkSource == 0?1:12)) / (1000 / Us)) % 256
 

status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef);
void bspTimer_Cmd(uint8_t uiTimerNo,FunctionalState State);

//�ص�����ģ��
typedef void * (*TimerTaskHook)(void *arg);

//����ʵ��һ��������У���������в���ִ�к�ʱ����
typedef struct tagTimerTaskInfo
{
	uint16_t uiCount;//��ʱ������
	uint16_t uiIntTime;//��λms //ִ������
	uint16_t uiRunTime;//���д���
	TimerTaskHook  Hook;//�ص�����
	uint16_t  ucUseState;
}TimerTaskInfo;
typedef struct tagTimerInitValue
{
	uint8_t	TIM_HValue;	   //װ�س�ֵ
	uint8_t	TIM_LValue;	   //װ�س�ֵ
}TimerInitValue;

#define MAX_TIMER_TASK  			5

int8_t bspTimerTaskGetItem();
void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime);
void bspTimerTaskInit();
void bspTimeDelayInit();//ϵͳ����ʱ���ʼ��
void bspTimeDelay(uint16_t uiDelayMs);
#endif
