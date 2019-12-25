#include "bsp_7seg.h"

uint8_t ucDisplayBuf[MAX_7SEG_NUM] = {0};

uint8_t code ucSegCode[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void bsp_7SegInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P0,&GPIO_InitStruct);
	
}
//数码管数据的写方式
void bsp_7SegDataWrite(uint8_t ucData)
{
	L74xx595_Wirte_One_Byte(ucData);
}
//数码管位选写入方式
void bsp_7SegSegmentWrite()
{
	static uint8_t ucBitCode = 0;
	
	uint8_t ucDat = P0;
	
	ucDat &= ~(0x1e);
	
	switch(ucBitCode)
	{
		case 0:
		{
			ucDat |= 0x02;
		};break;
		case 1:
		{
			ucDat |= 0x04;
		};break;
		case 2:
		{
			ucDat |= 0x08;
		}
		case 3:
		{
			ucDat |= 0x10;
		}
	}
	P0 = ucDat;
	ucBitCode++;
	if(ucBitCode == MAX_7SEG_NUM)
	{
		ucBitCode = 0;
	}
}
void bsp_7SegProcessDel()
{
	uint8_t ucLoop = 0;
	
	for(ucLoop = 0;ucLoop < MAX_7SEG_NUM;ucLoop++)
	{
		bsp_7SegDataWrite(ucSegCode[ucDisplayBuf[ucLoop]]);//送段选码
		bsp_7SegSegmentWrite();															//送位选码
		Delay10ms();																			//延时
		bsp_7SegDataWrite(0x00);													//消影子
	}
}