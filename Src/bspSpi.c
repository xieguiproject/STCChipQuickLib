#include "bspSpi.h"

void bspSpiInit()
{
	SPDAT = 0;					//��ʼ��SPI����
	SPSTAT = SPIF | WCOL;		//���SPI״̬λ
	SPCTL = SPEN | MSTR;		//����ģʽ,��ʹ�ܣ��ٶ�����
	IE2 |= ESPI;
}

void bspSpiInterrupt() interrupt 9 using 1 
{
    SPSTAT = SPIF | WCOL;       //���SPI״̬λ
    //���ܵ�������ֱ��ͨ�������ͳ�ȥ
		//BspUsartSendByte(SPDAT);
    SPISS = 1;                  //���ߴӻ���SS
}
void bspSpiSendByte(uint8_t Dat)
{
	SPDAT = Dat;            //����SPI��������
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
