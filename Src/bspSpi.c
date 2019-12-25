#include "bspSpi.h"

void bspSpiInit()
{
	SPDAT = 0;					//初始化SPI数据
	SPSTAT = SPIF | WCOL;		//清除SPI状态位
	SPCTL = SPEN | MSTR;		//主机模式,并使能，速度设置
	IE2 |= ESPI;
}

void bspSpiInterrupt() interrupt 9 using 1 
{
    SPSTAT = SPIF | WCOL;       //清除SPI状态位
    //接受到的数据直接通过串口送出去
		//BspUsartSendByte(SPDAT);
    SPISS = 1;                  //拉高从机的SS
}
void bspSpiSendByte(uint8_t Dat)
{
	SPDAT = Dat;            //触发SPI发送数据
	_nop_();
	_nop_();
}
void bspSpiSendBuff(uint8_t *Buff,uint16_t uiLen)
{
	uint16_t uiLoop = 0;
	if(uiLen == 0)
	{
		while (*Buff)
    {
        //BspUsartSendByte(*Buff++); 
    }
	}
	else
	{
		while(uiLoop < uiLen);
		{
			//bspSpiSendByte(Buff[uiLoop]);
			uiLoop++;
		}
	}
}
