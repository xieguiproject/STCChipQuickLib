#include "stc15xx_usart.h"

UsartInfoList xdata mdUsarts;

status bspUSART_Init(uint8_t uiUsartNo,USART_InitTypeDef *USART_InitStruct)
{
	uint32_t uiDat = 0;
	TIM_InitTypeDef InitTypeDef;
	switch(uiUsartNo)
	{
		case Usart1:
#ifdef STC15 | STC8
			/*设置串口的管脚切换关系 ：低端cpu不支持*/
			switch(USART_InitStruct->UART_P_SW)
			{
				case UART1_SW_P30_P31:
				{
						ACC = P_SW1;
						ACC &= ~(S1_S0 | S1_S1);
						P_SW1 = ACC;
				};break;
				case UART1_SW_P36_P37:
				{
						ACC = P_SW1;
						ACC &= ~(S1_S0 | S1_S1);
						ACC |= S1_S0;
						P_SW1 = ACC;
				};break;
				case UART1_SW_P16_P17:
				{
						ACC = P_SW1;
						ACC &= ~(S1_S0 | S1_S1);
						ACC |= S1_S1;
						P_SW1 = ACC;
				};break;
				default:
				{
						ACC = P_SW1;
						ACC &= ~(S1_S0 | S1_S1);
						P_SW1 = ACC;
				};break;
			}
#endif
			if(USART_InitStruct->UART_Interrupt == ENABLE)	
				ES = 1;	//允许中断
			else								
				ES = 0;//禁止中断
			if(USART_InitStruct->UART_RxEnable == ENABLE)	
				REN = 1;//允许接收
			else								
				REN = 0;//禁止接收
			if(USART_InitStruct->UART_RXD_TXD_Short == ENABLE)	
				PCON2 |=  (1<<4);	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
			else									
				PCON2 &= ~(1<<4);
			
			SCON &= ~(0X11 << 6);
			if(USART_InitStruct->UART_Mode == UART_8bit_BRTx)
			{
				SCON |= (UART_8bit_BRTx << 6);
				//设置串口模式位8位可变模式
			}
			//波特率设置
#ifdef STC15 | STC8
			//独立波特率发生器
			if(USART_InitStruct->UART_BRT_Use == BRT_SelfTimer)
			{
					AUXR |= 0X01;						//设置串口一为独立波特率发生器
					AUXR |= 0X04;						//设置工作在1T模式
					BRT = 0xDC;							//设置波特率为9600
					AUXR |= 0x10;						//启动独立波特率发生器
			}
#endif
#ifndef STC15W201S
			//STC15W201S 单片机只能使用定时器2作为波特率发生器
			if(USART_InitStruct->UART_BRT_Use == BRT_Timer1)
			{
#if 0
				AUXR &= ~0x01;		//选择定时器1作为波特率发生器
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 =  BuadRateH(USART_InitStruct->UART_BaudRate);
				TL1 =  BuadRateL(USART_InitStruct->UART_BaudRate);
				ET1 = 0;			//禁止中断
				TMOD &= ~0x40;		//定时
				INT_CLKO &= ~0x02;	//不输出时钟
#else		
				SCON |= 0x50;		//8???,?????
				AUXR |= 0x40;		//???1???Fosc,?1T
				AUXR &= 0xFE;		//??1?????1???????
				TMOD &= 0x0F;		//?????1?16???????
				TL1 = 0xB8;		//??????
				TH1 = 0xFF;		//??????
				ET1 = 0;		//?????1??
				TR1 = 1;		//?????1
#endif
			}
#endif
			if(USART_InitStruct->UART_BRT_Use == BRT_Timer2)
			{
				AUXR |= 0X01;//旋转定时器2作为波特率发生器
				//下面进行定时器2的配置
				InitTypeDef.TIM_Mode = TIM_16BitAutoReload;//定时器2 16位自动重载
				InitTypeDef.TIM_ClkSource = TIM_CLOCK_1T;//12t模式
				InitTypeDef.TIM_Interrupt = DISABLE;//不允许中断
				InitTypeDef.TIM_Run = DISABLE;//不直接允许
				InitTypeDef.TIM_LValue =  BuadRateL(USART_InitStruct->UART_BaudRate);	
				//定时器低位
				InitTypeDef.TIM_HValue = BuadRateH(USART_InitStruct->UART_BaudRate);     
				//定时器高位
				bspTimer_Init(Timer2,&InitTypeDef);
				//开启定时器2
				bspTimer_Cmd(Timer2,ENABLE);	
			}
			
			break;
		case Usart2:
#ifdef STC15 | STC8
			/*端口切换*/
			
#endif
			/*串口2只能使用定时器2作为波特率发生器*/
			{
				S2CON = 0x50;		
				AUXR |= 0x04;	
				T2L = 0xB8;		
				T2H = 0xFF;		
				AUXR |= 0x10;
				IE2 |= 0X01;
			}
			break;
	}
	return 1;
}
/*****************************************************************************
 函 数 名  : bspSendByte
 功能描述  : 发送一个字节数据到指定串口
 输入参数  : uint8_t uiUsartNo  
             uint8_t uiData     
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年5月28日 星期二
    作    者   : Gavinx
    修改内容   : 新生成函数

*****************************************************************************/
status bspUsartSendByte(uint8_t uiUsartNo,uint8_t uiData)
{
	switch(uiUsartNo)
	{
		case Usart1:
		{
			SBUF = uiData;
			while(TI == 0);
			TI = 0;
		};break;
		case Usart2:
		{
			S2BUF= uiData;
			while(!(S2CON & S2TI));
			S2CON &= ~S2TI;
		};break;
	}
	return true;
}
uint16_t bspUsartReadyByte(uint8_t uiUsartNo)
{
	UsartInfo *usart;
	
	usart = &mdUsarts.UsartInfos[uiUsartNo - 1];
	
	return usart->uiRCurCount;
}
/*判断串口是否接受结束*/
status bspUsartReciveEnd(uint8_t uiUsartNo)
{
	UsartInfo *usart;
	
	usart = &mdUsarts.UsartInfos[uiUsartNo - 1];
	if(usart->ucCheckEndCount > 0)
	{
		usart->ucCheckEndCount--;
	}
	if(usart->ucCheckEndCount == 0 && usart->uiRCurCount > 0)
	{
		//接受结束
		return OK;
	}
	return ERROR;
}
status bspUsartSendString(uint8_t uiUsartNo,uint8_t *uiData,uint16_t uiLen)
{
	uint16_t uiLoop = 0;
	if(uiLen == 0)
	{
		while(*uiData != '\0')
		{
			bspUsartSendByte(uiUsartNo,*uiData);
			uiData++;
		}
	}
	else
	{
		while(uiLen)
		{
			bspUsartSendByte(uiUsartNo,uiData[uiLoop]);
			uiLen--;
			uiLoop++;
		}
	}
	return true;
}
void bspUsart1_IRQHandler(void) interrupt USART1_IRQ using 1
{
	UsartInfo *usart;
	usart = &mdUsarts.UsartInfos[0];
	if(RI)
	{
		RI = 0;
		usart->ucCheckEndCount = USART_CHECK_END_MAX;
		usart->ucUart1Buf[usart->uiRCurCount++] = SBUF;
		if(usart->uiRCurCount > sizeof(usart->ucUart1Buf))
		{
			usart->uiRCurCount = 0;
		}
	}
}
void bspUsart2_IRQHandler() interrupt USART2_IRQ using 1
{
	UsartInfo *usart;
	usart = &mdUsarts.UsartInfos[1];
	
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;     //Clear receive interrupt flag
        usart->ucCheckEndCount = USART_CHECK_END_MAX;
		usart->ucUart1Buf[usart->uiRCurCount++] = S2BUF;
		if(usart->uiRCurCount > sizeof(usart->ucUart1Buf))
		{
			usart->uiRCurCount = 0;
		}
    }
}

