#ifndef STCXX_USART_H
#define STCXX_USART_H

#include "STC15xx.H"
#include "stc15xx_timer.h"

#define MAX_USART		2
#define USART_MAX_BUF	256

typedef struct
{ 
	uint8_t		UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	uint8_t		UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2
	uint32_t	UART_BaudRate;		//������,       ENABLE,DISABLE
	uint8_t		Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	uint8_t		UART_RxEnable;		//�������,   ENABLE,DISABLE
	uint8_t		BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
	uint8_t		UART_Interrupt;		//�жϿ���,   ENABLE,DISABLE
	uint8_t		UART_Polity;		//���ȼ�,     PolityLow,PolityHigh
	uint8_t		UART_P_SW;			//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	uint8_t		UART_RXD_TXD_Short;	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE
}USART_InitTypeDef; 


/********************************
�����л�����
**********************************/
#define UART1_SW_P30_P31			0
#define UART1_SW_P36_P37			1
#define UART1_SW_P16_P17			2

#define UART2_SW_P10_P11			0
#define UART2_SW_P46_P47			1

#define UART3_SW_P00_P01			0
#define UART3_SW_P50_P51

typedef struct tagUsartInfo
{
	uint8_t  ucUart1Buf[128];
	uint8_t  ucCheckEndCount;//��������ɼ�����
	uint16_t uiRCurCount;
}UsartInfo;
typedef struct tagUsartInfoList
{
	UsartInfo UsartInfos[MAX_USART];
}UsartInfoList;
#define BuadRateH(Rate) ((65536 - (MAIN_Fosc / 4 / Rate)) >> 8)
#define BuadRateL(Rate) (65536 - (MAIN_Fosc / 4 / Rate))


#define	Usart1	1
#define	Usart2	2

#define	BRT_Timer1		1				//ʹ�ö�ʱ��1��Ϊ�����ʷ�����
#define	BRT_Timer2		2				//ʹ�ö�ʱ��2��Ϊ�����ʷ�����
#define BRT_SelfTimer	3			//���������ʷ�����

#define UART_ShiftRight 0x00
#define UART_8bit_BRTx  0x01
#define UART_9bit       0x02
#define UART_9bit_BRTx  0x03

#define USART_CHECK_END_MAX 10

status bspUsartSendByte(uint8_t uiUsartNo,uint8_t uiData);
status bspUSART_Init(uint8_t uiUsartNo,USART_InitTypeDef *USART_InitStruct);
status bspUsartSendString(uint8_t uiUsartNo,uint8_t *uiData,uint16_t uiLen);
status bspUsartReciveEnd(uint8_t uiUsartNo);
uint16_t bspUsartReadyByte(uint8_t uiUsartNo);
extern UsartInfoList xdata mdUsarts;

#endif
