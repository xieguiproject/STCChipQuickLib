#include "bspTimer.h"

uint8_t ui50MsCount = 0;


void TimerSoft50MsInter()
{
	mdUsarts.Usart2.UsartFlage |= USART_RECV_OVER;//³¬¹ý50msÃ»ÓÐ½ÓÊÜµ½Êý¾ÝÔò´ú±í½ÓÊÜÊý¾ÝÍê³É
	Timer3Disable();//¹Ø±Õ¶¨Ê±Æ÷
}
void Timer3SetCounter(uint8_t uiCount)
{
	ui50MsCount = uiCount;
}
void Timer3Disable()
{
	T4T3M &= ~0x08;                  //¹Ø±Õ
	IE2 &= ~0x20;                    //¹Ø±ÕÖÐ¶
	ui50MsCount = 0;
}
void Timer3Enable()
{
	T4T3M |= 0x08;                  //¿ªÊ¼
  	IE2 |= 0x20;                    //ÔÊÐíÖÐ¶Ï
	ui50MsCount = 0;
	Timer3Init();
}
//1ms¶¨Ê±Æ÷ÖÐ¶Ïº¯Êý
void Timer3Inter() interrupt 19
{
	ui50MsCount++;
	if(ui50MsCount > 50)
	{
		ui50MsCount = 0;
		TimerSoft50MsInter();
	}
}
void Timer3Init()
{
	T4T3M |= 0x02;//ÉèÖÃTIME3Îª1TÄ£Ê½
	
	T3L = 0xCD;		//1ms¶¨Ê±Æ÷
	T3H = 0xD4;		//1ms¶¨Ê±Æ÷
	ui50MsCount = 0;
}


void Time4Count()
{
	static uint16_t uiLoop = 0;
	static uint8_t uiFlg = 0;
	uiLoop++;
	if(uiLoop > 5000)
	{
		uiLoop = 0;
		
		if(uiFlg == 0)
		{
			uiFlg = 1;
			CloseLed(1);
			CloseLed(2);
		}
		else
		{
			uiFlg = 0; 
			OpenLed(1);
			OpenLed(2);
		}
		
	}
}
void Timer4Inter() interrupt 20
{
	Time4Count();
	soft_count();
}
void Timer4Init()
{
	T4T3M |= 0X20;
	T4L = 0xD7;		//50US
	T4H = 0xFD;		//100US
}
void Timer4Disable()
{
	T4T3M &= ~0X80;
	IE2 &= ~0X40;
}
void Timer4Enable()
{
	Timer4Init();
	T4T3M |= 0X80;
	IE2 |= 0X40;
}
