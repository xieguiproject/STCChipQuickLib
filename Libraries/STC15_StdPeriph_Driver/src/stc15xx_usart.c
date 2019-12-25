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
			/*���ô��ڵĹܽ��л���ϵ ���Ͷ�cpu��֧��*/
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
				ES = 1;	//�����ж�
			else								
				ES = 0;//��ֹ�ж�
			if(USART_InitStruct->UART_RxEnable == ENABLE)	
				REN = 1;//�������
			else								
				REN = 0;//��ֹ����
			if(USART_InitStruct->UART_RXD_TXD_Short == ENABLE)	
				PCON2 |=  (1<<4);	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
			else									
				PCON2 &= ~(1<<4);
			
			SCON &= ~(0X11 << 6);
			if(USART_InitStruct->UART_Mode == UART_8bit_BRTx)
			{
				SCON |= (UART_8bit_BRTx << 6);
				//���ô���ģʽλ8λ�ɱ�ģʽ
			}
			//����������
#ifdef STC15 | STC8
			//���������ʷ�����
			if(USART_InitStruct->UART_BRT_Use == BRT_SelfTimer)
			{
					AUXR |= 0X01;						//���ô���һΪ���������ʷ�����
					AUXR |= 0X04;						//���ù�����1Tģʽ
					BRT = 0xDC;							//���ò�����Ϊ9600
					AUXR |= 0x10;						//�������������ʷ�����
			}
#endif
#ifndef STC15W201S
			//STC15W201S ��Ƭ��ֻ��ʹ�ö�ʱ��2��Ϊ�����ʷ�����
			if(USART_InitStruct->UART_BRT_Use == BRT_Timer1)
			{
#if 0
				AUXR &= ~0x01;		//ѡ��ʱ��1��Ϊ�����ʷ�����
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 =  BuadRateH(USART_InitStruct->UART_BaudRate);
				TL1 =  BuadRateL(USART_InitStruct->UART_BaudRate);
				ET1 = 0;			//��ֹ�ж�
				TMOD &= ~0x40;		//��ʱ
				INT_CLKO &= ~0x02;	//�����ʱ��
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
				AUXR |= 0X01;//��ת��ʱ��2��Ϊ�����ʷ�����
				//������ж�ʱ��2������
				InitTypeDef.TIM_Mode = TIM_16BitAutoReload;//��ʱ��2 16λ�Զ�����
				InitTypeDef.TIM_ClkSource = TIM_CLOCK_1T;//12tģʽ
				InitTypeDef.TIM_Interrupt = DISABLE;//�������ж�
				InitTypeDef.TIM_Run = DISABLE;//��ֱ������
				InitTypeDef.TIM_LValue =  BuadRateL(USART_InitStruct->UART_BaudRate);	
				//��ʱ����λ
				InitTypeDef.TIM_HValue = BuadRateH(USART_InitStruct->UART_BaudRate);     
				//��ʱ����λ
				bspTimer_Init(Timer2,&InitTypeDef);
				//������ʱ��2
				bspTimer_Cmd(Timer2,ENABLE);	
			}
			
			break;
		case Usart2:
#ifdef STC15 | STC8
			/*�˿��л�*/
			
#endif
			/*����2ֻ��ʹ�ö�ʱ��2��Ϊ�����ʷ�����*/
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
 �� �� ��  : bspSendByte
 ��������  : ����һ���ֽ����ݵ�ָ������
 �������  : uint8_t uiUsartNo  
             uint8_t uiData     
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��5��28�� ���ڶ�
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

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
/*�жϴ����Ƿ���ܽ���*/
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
		//���ܽ���
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

