#include  "bsp_Getmm.h"

SensorInfo mdSensorInfo[2];


//发送一次获取距离命令
void bspGetmm()
{
	uint8_t cmd[] = {0x01,0x03,0x00,0x0F,0x00,0x02,0xF4,0x08};
	
	bspUsartSendString(Usart1,cmd,sizeof(cmd));
	//Delay10ms();
	bspUsartSendString(Usart2,cmd,sizeof(cmd));
}
void bspDelSensorData(uint8_t uiSenSorNo,UsartInfo *usart,uint16_t uiByte)
{
	uint32_t uiData = 0;
	uint16_t uiLoop = 0;
	for(uiLoop = 0;uiLoop < uiByte;uiLoop++)
	{
		if(usart->ucUart1Buf[uiLoop] == 0x01 &&
			usart->ucUart1Buf[uiLoop + 1] == 0x03 &&
		  usart->ucUart1Buf[uiLoop + 2] == 0x04)
		{
				uiData = (((uint32_t)usart->ucUart1Buf[uiLoop + 3] << 24) |
						((uint32_t)usart->ucUart1Buf[uiLoop + 4] << 16) |
						((uint32_t)usart->ucUart1Buf[uiLoop + 5] << 8) |
						((uint32_t)usart->ucUart1Buf[uiLoop + 6]));
				
				if(uiData == ERROR1 || uiData == ERROR2 || 
						uiData == ERROR3 || uiData == ERROR4)
				{
					  mdSensorInfo[uiSenSorNo].uiCurMM = 0;
					  mdSensorInfo[uiSenSorNo].uiCurErroeCode = uiData;
				}
				else
				{
					 mdSensorInfo[uiSenSorNo].uiCurMM = uiData;
					 mdSensorInfo[uiSenSorNo].uiCurErroeCode = 1;
				}
				mdSensorInfo[uiSenSorNo].uiCurM = (float)mdSensorInfo[uiSenSorNo].uiCurMM / 1000.0;
		}
	}
}
//处理传感器的数据回传
void bspDelSensorBack()
{
	
	uint16_t uiByte = 0;
	
	UsartInfo *usart;
	if(bspUsartReciveEnd(Usart1) == OK)
	{
		usart = &mdUsarts.UsartInfos[Usart1 - 1];
		uiByte = bspUsartReadyByte(Usart1);/*获取串口接受到的数据量*/
		bspDelSensorData(0,usart,uiByte);
		usart->uiRCurCount = 0;
	}
	if(bspUsartReciveEnd(Usart2) == OK)
	{
		usart = &mdUsarts.UsartInfos[Usart2 - 1];
		uiByte = bspUsartReadyByte(Usart2);/*获取串口接受到的数据量*/
		bspDelSensorData(1,usart,uiByte);
		usart->uiRCurCount = 0;
	}
}