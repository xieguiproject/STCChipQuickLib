#include "stc15xx_timer.h"

TimerTaskInfo TimerTaskInfoQueue[MAX_TIMER_TASK];
uint16_t uiTimeDelayCount = 0;
TimerInitValue TimerInitValueParm[5] = {0};
//��¼���еĶ�ʱ����ֵ���еĵ�Ƭ����֧���Զ����أ���Ҫ�Լ���¼
/*****************************************************************************
 �� �� ��  : Timer_Init
 ��������  : ��ʱ����ʼ�������ʹ���˲����ʷ�������ע�����и���
 �������  : uint8_t uiTimerNo  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��4��12�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

*****************************************************************************/
status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef)
{
	if(uiTimerNo > Timer4)	return ERROR;	//�ղ���
	
	TimerInitValueParm[uiTimerNo].TIM_HValue = InitTypeDef->TIM_HValue;
	TimerInitValueParm[uiTimerNo].TIM_LValue = InitTypeDef->TIM_LValue;
	switch(uiTimerNo)
	{
		case Timer0:
		{
			//����ʱ�ӹ�����12Tģʽ����1Tģʽ
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X80;
			else
				AUXR &= ~0X80;
			//���ö�ʱ��TMOD,��װģʽ
			TMOD &= ~(0X0F << 0);		//M1 M0 00
			switch(InitTypeDef->TIM_Mode)
			{
				case TIM_16BitAutoReload:
					 TMOD |= (0x00 << 0);					 //M1 M0 00
					 break;
				case TIM_16Bit:
					 TMOD |= (0X01 << 0);//M1 M0 01
					 break;
				case TIM_8BitAutoReload:
					 TMOD |= (0X02 << 0);//M1 M0 10
					 break;
				case TIM_16BitAutoReloadNoMask:
					 TMOD |= (0X03 << 0);//M1 M0 11
					 break;
			}
			
			//װ�س�ʼֵ
			TH0 = InitTypeDef->TIM_HValue;
			TL0 = InitTypeDef->TIM_LValue;
			
			//����ж�
			TF0 = 0;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				ET0 = 1;
				//�����ж�
			}
			else
			{
				ET0 = 0;
			}
			if(InitTypeDef->TIM_Run == ENABLE)
			{
				//�Ƿ�������ʱ��
				TR0 = 1;
			}
			else
			{
				TR0 = 0;
			}
			
			
		}break;
		case Timer1:
		{
			//����ʱ�ӹ�����12Tģʽ����1Tģʽ
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X40;
			else
				AUXR &= ~0X40;
			//���ö�ʱ��TMOD,��װģʽ
			TMOD &= ~(0Xf0 << 0);		//M1 M0 00
			switch(InitTypeDef->TIM_Mode)
			{
				case TIM_16BitAutoReload:
					 TMOD |= (0x00 << 4);					 //M1 M0 00
					 break;
				case TIM_16Bit:
					 TMOD |= (0X01 << 4);//M1 M0 01
					 break;
				case TIM_8BitAutoReload:
					 TMOD |= (0X02 << 4);//M1 M0 10
					 break;
				case TIM_16BitAutoReloadNoMask:
					 TMOD |= (0X03 << 4);//M1 M0 11
					 break;
			}
			//װ�س�ʼֵ
			TH1 = InitTypeDef->TIM_HValue;
			TL1 = InitTypeDef->TIM_LValue;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				ET1 = 1;
				//�����ж�
			}
			else
			{
				ET1 = 0;
			}
			if(InitTypeDef->TIM_Run == ENABLE)
			{
				//�Ƿ�������ʱ��
				TR1 = 1;
			}
			else
			{
				TR1 = 0;
			}
			
			//����ж�
			TF1 = 0;
		}break;
		case Timer2:
		{
			//����ʱ�ӹ�����12Tģʽ����1Tģʽ
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X04;
			else
				AUXR &= ~0X04;
			//��ʱ��2Ĭ���Զ���װ
			//װ�س�ʼֵ
			T2H = InitTypeDef->TIM_HValue;
			T2L = InitTypeDef->TIM_LValue;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				IE2 |= (0X01 << 2);
				//�����ж�
			}
			else
			{
				IE2 &= ~(0X01 << 2);
			}
			//�Ƿ�������ʱ��
			if(InitTypeDef->TIM_Run == ENABLE)
			{
				
				AUXR |= (0X01 << 4);
			}
			else
			{
				AUXR &= ~(0X01 << 4);
			}
		};break;
#ifndef STC15W201S	
		case Timer3:break;
		case Timer4:break;
#endif
	}
	return OK;
}
void bspTimer_Cmd(uint8_t  uiTimerNo,FunctionalState State)
{
	switch(uiTimerNo)
	{
		case Timer0:
		{
			if(State == ENABLE)
			{
				TR0 = 1;
			}
			else
			{
				TR0 = 0;
			}
		}break;
		case Timer1:
			break;
		case Timer2:
		{
			if(State == ENABLE)
			{
				AUXR |= (0X01 << 4);
			}
			else
			{
				AUXR &= ~(0X01 << 4);
			}
		};break;
	}
}
void bspTimerTaskInit()
{
	uint8_t ucLoop = 0;
	for(ucLoop = 0;ucLoop < MAX_TIMER_TASK;ucLoop++)
	{
			TimerTaskInfoQueue[ucLoop].ucUseState = false;
			TimerTaskInfoQueue[ucLoop].uiCount = 0;
			TimerTaskInfoQueue[ucLoop].uiIntTime = 0;
			TimerTaskInfoQueue[ucLoop].Hook = NULL;
	}
}
int8_t bspTimerTaskGetItem()
{
	uint8_t ucLoop = 0;
	for(ucLoop = 0;ucLoop < MAX_TIMER_TASK;ucLoop++)
	{
		if(TimerTaskInfoQueue[ucLoop].ucUseState == false) 
		{
			TimerTaskInfoQueue[ucLoop].ucUseState = true;
			TimerTaskInfoQueue[ucLoop].uiCount = 0;
			TimerTaskInfoQueue[ucLoop].uiIntTime = 0;
			TimerTaskInfoQueue[ucLoop].Hook = NULL;
			return ucLoop;
		}
	}
	return ERROR;
}
void bspTimerTaskFreeItem(int8_t Item)
{
	if(Item < MAX_TIMER_TASK)
	{
		TimerTaskInfoQueue[Item].ucUseState = false;
	}
}
sbit led1 = P2^3;
void LedControlTasksss()
{
	static unsigned int  uiLedFlag = 0;
	
	if(uiLedFlag == 0)
	{
		led1 = 1;
		uiLedFlag = 1;
	}
	else
	{ 
		led1 = 0;
		uiLedFlag = 0;
	}
}
void bspTimer2_IRQHandler(void) interrupt 12
{
	T2H = TimerInitValueParm[Timer2].TIM_HValue;
	T2L = TimerInitValueParm[Timer2].TIM_LValue;
	
}
//��ʱ��0�жϺ���
void bspTimer0_IRQHandler(void) interrupt 1
{
	uint16_t ucLoop = 0;
	
	TH0 = TimerInitValueParm[Timer0].TIM_HValue;
	
	TL0 = TimerInitValueParm[Timer0].TIM_LValue;
	
	for(ucLoop = 0;ucLoop < MAX_TIMER_TASK;ucLoop++)
	{	
		if(TimerTaskInfoQueue[ucLoop].ucUseState == true && 
			TimerTaskInfoQueue[ucLoop].Hook != NULL)
		{
			if(TimerTaskInfoQueue[ucLoop].uiRunTime == 0xffff ||
				TimerTaskInfoQueue[ucLoop].uiRunTime > 0)
			{
				if(TimerTaskInfoQueue[ucLoop].uiCount >= TimerTaskInfoQueue[ucLoop].uiIntTime)
				{
					//ʱ�䵽
					TimerTaskInfoQueue[ucLoop].Hook(NULL);
					TimerTaskInfoQueue[ucLoop].uiCount = 0;
					TimerTaskInfoQueue[ucLoop].uiRunTime--;
				}
				else
				{
					TimerTaskInfoQueue[ucLoop].uiCount++;//1ms
				}
			}
			else
			{
				TimerTaskInfoQueue[ucLoop].ucUseState = false;
				TimerTaskInfoQueue[ucLoop].Hook = NULL;
				/*����ִ�д���������ɾ������*/
			}
		}
	}
}

void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime)
{
	uint8_t Item = 0;
	
	Item = bspTimerTaskGetItem();//��ȡһ������
	if(Item == ERROR)
	{
		return;
	}
	TimerTaskInfoQueue[Item].Hook = hook;
	TimerTaskInfoQueue[Item].uiIntTime = uiIntTime;//1��һִ��
	TimerTaskInfoQueue[Item].uiCount = 0;
	TimerTaskInfoQueue[Item].uiRunTime = 0xffff;
}

void * bspTimeDelayTask(void *arg)
{
	if(uiTimeDelayCount > 0)
	{
		uiTimeDelayCount--;
	}
}
void bspTimeDelayInit()
{
	uint8_t Item = 0;
	
	Item = bspTimerTaskGetItem();//��ȡһ������
	if(Item == ERROR)
	{
		return;
	}
	TimerTaskInfoQueue[Item].Hook = bspTimeDelayTask;
	TimerTaskInfoQueue[Item].uiIntTime = 1;//1ms��һִ��
	TimerTaskInfoQueue[Item].uiCount = 0;
	TimerTaskInfoQueue[Item].uiRunTime = 0xffff;
}
void bspTimeDelay(uint16_t uiDelayMs)
{
	uiTimeDelayCount = uiDelayMs;
	while(uiTimeDelayCount != 0);
}