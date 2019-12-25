#ifndef STCXX_USART_H
#define STCXX_USART_H

#include "STC15xx.H"
#include "stc15xx_timer.h"

#define MAX_USART		2
#define USART_MAX_BUF	256

typedef struct
{ 
	uint8_t		UART_Mode;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	uint8_t		UART_BRT_Use;		//使用波特率,   BRT_Timer1,BRT_Timer2
	uint32_t	UART_BaudRate;		//波特率,       ENABLE,DISABLE
	uint8_t		Morecommunicate;	//多机通讯允许, ENABLE,DISABLE
	uint8_t		UART_RxEnable;		//允许接收,   ENABLE,DISABLE
	uint8_t		BaudRateDouble;		//波特率加倍, ENABLE,DISABLE
	uint8_t		UART_Interrupt;		//中断控制,   ENABLE,DISABLE
	uint8_t		UART_Polity;		//优先级,     PolityLow,PolityHigh
	uint8_t		UART_P_SW;			//切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
	uint8_t		UART_RXD_TXD_Short;	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE
}USART_InitTypeDef; 


/********************************
串口切换描述
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
	uint8_t  ucCheckEndCount;//检测接受完成计数器
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

#define	BRT_Timer1		1				//使用定时器1作为波特率发生器
#define	BRT_Timer2		2				//使用定时器2作为波特率发生器
#define BRT_SelfTimer	3			//独立波特率发生器

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
