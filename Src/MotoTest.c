#include "STC15.H"


sbit PWM1 = P3^7;
sbit PWM2 = P2^7;

sbit LED1 = P1^1;
sbit LED2 = P1^2;

sbit KEY1 = P1^3;
sbit KEY2 = P1^4;

unsigned char SystemStatus = 0;
unsigned char SystemRunMoto = 1;
unsigned char Key1Flage = 0,Key2Flage = 0;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
void DelayMs(unsigned int time)
{
	while(time--)
	{
		Delay1ms();
	}
}
unsigned char  KeyScanf()
{
	unsigned char KeyValue = 0;
	if(KEY1 == 0)
	{
		Key1Flage = 1;	
	}	
	if(KEY1 == 0 && Key1Flage == 1)
	{
		KeyValue |= 0x01;
	}
	
	if(KEY2 == 0)
	{
		Key2Flage = 1;	
	}	
	if(KEY2 == 0 && Key2Flage == 1)
	{
		KeyValue |= 0x02;
	}
	return KeyValue;
}
void main()
{
	unsigned char KeyValue = 0;
	while(1)
	{
		KeyValue = KeyScanf();
		if(KeyValue & 0x01)//方向切换按钮按下
		{
			SystemStatus = !SystemStatus;
			break;
		}
		if(SystemRunMoto)
		{
			if(SystemStatus == 1)
			{
				PWM1 = 1;
				PWM2 = 0;
			}
			else
			{
				PWM1 = 0;
				PWM2 = 1;
			}
	    }
		else
		{
			PWM1 = 0;
			PWM2 = 0;
		}
		
	}
}


