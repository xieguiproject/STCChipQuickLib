#include "stc15xx_timer.h"

TimerTaskInfo TimerTaskInfoQueue[MAX_TIMER_TASK];
uint16_t uiTimeDelayCount = 0;
TimerInitValue TimerInitValueParm[5] = {0};
//记录所有的定时器初值，有的单片机不支持自动重载，需要自己记录
/*****************************************************************************
 函 数 名  : Timer_Init
 功能描述  : 定时器初始化，如果使用了波特率发生器请注意自行更改
 输入参数  : uint8_t uiTimerNo  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年4月12日 星期五
    作    者   : Gavinx
    修改内容   : 新生成函数

*****************************************************************************/
status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef)
{
	if(uiTimerNo > Timer4)	return ERROR;	//空操作
	
	TimerInitValueParm[uiTimerNo].TIM_HValue = InitTypeDef->TIM_HValue;
	TimerInitValueParm[uiTimerNo].TIM_LValue = InitTypeDef->TIM_LValue;
	switch(uiTimerNo)
	{
		case Timer0:
		{
			//配置时钟工作再12T模式还是1T模式
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X80;
			else
				AUXR &= ~0X80;
			//配置定时器TMOD,重装模式
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
			
			//装载初始值
			TH0 = InitTypeDef->TIM_HValue;
			TL0 = InitTypeDef->TIM_LValue;
			
			//清除中断
			TF0 = 0;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				ET0 = 1;
				//允许中断
			}
			else
			{
				ET0 = 0;
			}
			if(InitTypeDef->TIM_Run == ENABLE)
			{
				//是否启动定时器
				TR0 = 1;
			}
			else
			{
				TR0 = 0;
			}
			
			
		}break;
		case Timer1:
		{
			//配置时钟工作再12T模式还是1T模式
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X40;
			else
				AUXR &= ~0X40;
			//配置定时器TMOD,重装模式
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
			//装载初始值
			TH1 = InitTypeDef->TIM_HValue;
			TL1 = InitTypeDef->TIM_LValue;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				ET1 = 1;
				//允许中断
			}
			else
			{
				ET1 = 0;
			}
			if(InitTypeDef->TIM_Run == ENABLE)
			{
				//是否启动定时器
				TR1 = 1;
			}
			else
			{
				TR1 = 0;
			}
			
			//清除中断
			TF1 = 0;
		}break;
		case Timer2:
		{
			//配置时钟工作再12T模式还是1T模式
			if(InitTypeDef->TIM_ClkSource == TIM_CLOCK_1T)
				AUXR |= 0X04;
			else
				AUXR &= ~0X04;
			//定时器2默认自动重装
			//装载初始值
			T2H = InitTypeDef->TIM_HValue;
			T2L = InitTypeDef->TIM_LValue;
			
			if(InitTypeDef->TIM_Interrupt == ENABLE)
			{
				IE2 |= (0X01 << 2);
				//允许中断
			}
			else
			{
				IE2 &= ~(0X01 << 2);
			}
			//是否启动定时器
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
//定时器0中断函数
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
					//时间到
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
				/*任务执行次数到，则删除任务*/
			}
		}
	}
}

void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime)
{
	uint8_t Item = 0;
	
	Item = bspTimerTaskGetItem();//获取一个对象
	if(Item == ERROR)
	{
		return;
	}
	TimerTaskInfoQueue[Item].Hook = hook;
	TimerTaskInfoQueue[Item].uiIntTime = uiIntTime;//1秒一执行
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
	
	Item = bspTimerTaskGetItem();//获取一个对象
	if(Item == ERROR)
	{
		return;
	}
	TimerTaskInfoQueue[Item].Hook = bspTimeDelayTask;
	TimerTaskInfoQueue[Item].uiIntTime = 1;//1ms秒一执行
	TimerTaskInfoQueue[Item].uiCount = 0;
	TimerTaskInfoQueue[Item].uiRunTime = 0xffff;
}
void bspTimeDelay(uint16_t uiDelayMs)
{
	uiTimeDelayCount = uiDelayMs;
	while(uiTimeDelayCount != 0);
}