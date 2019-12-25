#include "bspDHT11.h"

void Delay8us()     //@11.0592MHz
{
    unsigned char i;

    _nop_();
    _nop_();
    i = 19;
    while (--i);
}
void Delay35us()        //@11.0592MHz
{
    unsigned char i;

    _nop_();
    i = 94;
    while (--i);
}
void Delay30us()        //@11.0592MHz
{
    unsigned char i;

    _nop_();
    _nop_();
    i = 80;
    while (--i);
}
void Delay18ms()        //@11.0592MHz
{
    unsigned char i, j, k;

    i = 1;
    j = 194;
    k = 160;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void bspDHT11Init()
{
	//���ô�������ioΪ���ܺ�ģʽ
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	GPIO_Init(GPIO_P3,&GPIO_InitStruct);
	//DHT11_IO = 0;
}
/*****************************************************************************
 �� �� ��  : bspDHT11ReceiveByte
 ��������  : DHT11һ���ֽ�
 �������  : ��,
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��5��24�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

*****************************************************************************/
#if 1

uint8_t bspDHT11ReceiveByte()
{
	uint8_t uiLoop = 0;
	uint8_t uiDat = 0;
	uint16_t uiCount = 0;
	uint8_t uiTemp = 0;
	for(uiLoop = 0; uiLoop < 8; uiLoop++)
	{
		uiCount = 65535;
		while(!DHT11_IO && --uiCount  > 0);
		Delay30us();
		uiTemp = 0;
		if(DHT11_IO)
		{
			uiTemp = 1;
		}
		uiCount = 65535;
		while(DHT11_IO && --uiCount  > 0);
		uiDat <<= 1;
		uiDat = uiDat | uiTemp;
	}
	return uiDat;
}
#else

uint8_t bspDHT11ReceiveByte()
{
	uint8_t uiLoop = 0;
	uint8_t uiCount = 0;
	uint8_t uiData = 0;
	uint8_t uiTemp = 0;
	uint8_t uiJoop = 0;
	for(uiLoop = 0;uiLoop < 8;uiLoop++)
	{
		uiCount = 3;
		while(!DHT11_IO && uiCount--);
		uiTemp = 0;
		delayUs(27);
		if(DHT11_IO)
		{
			uiTemp = 1;
		}
		uiCount = 3;
		while(DHT11_IO && uiCount--);	
		uiData <<= 1;
		uiData |= uiTemp;
	}
	return uiData;
}
#endif
/*****************************************************************************
 �� �� ��  : bspDHT11Receive
 ��������  : DHT11��ȡ��ʪ����Ϣ
 �������  : ��,�ú����������ִ��һ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��5��24�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

*****************************************************************************/
uint8_t bspDHT11Receive(DHT11Info *Info)
{
	uint16_t uiCount = 0;
	
	DHT11_IO = 1;//����
	Delay8us();
	DHT11_IO = 0;//����
	//�ȴ�20ms
	Delay18ms();
	DHT11_IO = 1;//����
	Delay35us();
	if(!DHT11_IO)
	{
		uiCount = 65536;
		while(!DHT11_IO && --uiCount > 0);
		uiCount = 65536;
		while(DHT11_IO && --uiCount > 0);
			//����5���ֽڵ�����
		Info->uiHumidity = bspDHT11ReceiveByte();
		Info->uiHumidityPoint = bspDHT11ReceiveByte();
		
		Info->uiTemperature = bspDHT11ReceiveByte();
		Info->uiTemperaturePoint = bspDHT11ReceiveByte();
		
		Info->uiCrcData = bspDHT11ReceiveByte();
		
		if(Info->uiCrcData == Info->uiTemperature + Info->uiTemperaturePoint + 
					Info->uiHumidity + Info->uiHumidityPoint)
		{
			return true;
		}
	}
	return false;
}

