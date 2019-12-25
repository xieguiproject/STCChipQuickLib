#include "bspLcd1602.h"

void delay_ms(unsigned int ms)
{
	unsigned int i=0,j=0;
	for(i=0;i<ms;i++)
	for(j=0;j<123;j++);
}
void delay(unsigned int t)	 //��ʱ
{    
	while(t--);
}

void  LCD_Wait(void)	//��æ״̬
{
	LcdRs=0;
	LcdRw=1;
	LcdEn=1;delay(10);LcdEn=0;	//�½���	
	while(Lcdbf)
	{
	  LcdEn=0;LcdEn=1;	 //�������Ҫ�����,ʵ��Ӳ���в���Ҫ
	}			
} 
unsigned char  LcdDataSwap(unsigned char input)
{
		unsigned char uiRet = 0;
    unsigned char uiLoop = 0;
    for(uiLoop = 0;uiLoop < 8;uiLoop++)
    {
        uiRet <<= 1;
        if((input & (0x01 << uiLoop)) != 0)
        {
            uiRet |= 0x01;
        }
    }
    return uiRet;
}
void LCD_Write(bit style, unsigned char input)	 //д����1/����0
{
	LcdRs=style;
	LcdRw=0;		
	DBPort = LcdDataSwap(input);	
	LcdEn=1;delay(20);LcdEn=0;			
	LCD_Wait();	
}
void bspLcdGpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P2,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P0,&GPIO_InitStruct);
	
}
void LCD_Initial(void)			  //��ʼ��LCD
{
	bspLcdGpioInit();
	
	LCD_Write(0,0x38);  		 //8λ���ݶ˿�,2����ʾ,5*7����
	delay(300);
	LCD_Write(0,0x0c);           //��ʾģʽ
	LCD_Write(0,0x01);           //����
	LCD_Write(0,0x06);           //����ģʽ
}
void bsp_LcdClean()
{
	LCD_Write(0,0x01); 
}
void GotoXY(unsigned char x, unsigned char y)  //�ƶ���굽ָ��λ��
{
	if(y==0)	LCD_Write(0,0x80|x);
	if(y==1)    LCD_Write(0,0xc0|x);
}
void PrintByte(unsigned char bytes)
{
	LCD_Write(1,bytes);
}
void Print(unsigned char *str)	 //ָ����������ַ���
{
	while(*str)  LCD_Write(1,*str++);
}

void Print_num(unsigned int display_data,unsigned char uiBit)
{
	if(uiBit == 1)
	{
		LCD_Write(1,display_data+0x30);
	}
	else if(uiBit == 2)
	{
		LCD_Write(1,display_data/10+0x30);
		LCD_Write(1,display_data%10/1+0x30);	
	}
	else if(uiBit == 3)
	{
		LCD_Write(1,display_data/100+0x30);
		LCD_Write(1,display_data%100/10+0x30);	
		LCD_Write(1,display_data%10/1+0x30);	
	}
	else if(uiBit == 4)
	{
		LCD_Write(1,display_data/1000+0x30);
		LCD_Write(1,display_data%1000/100+0x30);	
		LCD_Write(1,display_data%100/10+0x30);	
		LCD_Write(1,display_data%10/1+0x30);		
	}
	else
	{
		LCD_Write(1,display_data/10000+0x30);
		LCD_Write(1,display_data%10000/1000+0x30);	
		LCD_Write(1,display_data%1000/100+0x30);	
		LCD_Write(1,display_data%100/10+0x30);
		LCD_Write(1,display_data%10/1+0x30);
	}
		
}
void Print_Float(float datas,unsigned char ucBit1,unsigned char ucBit2)
{
	char buf[16] = {0};
	sprintf(buf,"%02.1f",datas);
	Print(buf);
}

void Set_cursorXY(unsigned char x,unsigned char y) //��ָ��λ�ù����˸
{
	LCD_Write(0,0x0f);
	GotoXY(x,y);
}
void GUI_donghua1(unsigned char x,unsigned char y)
{
	/*
		----------------------------------
		|......			   					 |
		|								 |
		----------------------------------
	*/
	unsigned char i=0;
	GotoXY(x,y);
	for(i=0;i<6;i++)
	{	
		delay_ms(100);	  
		Print(".");
		delay_ms(100);
	}
	GotoXY(x,y);
	Print("      ");	
}
void GUI_Progress_Bar(unsigned char x,unsigned char y,unsigned char Resolution)
{
	unsigned char i=0,geshu=16;
	GotoXY(x,y);
	if(Resolution<=100)
	{
		
		for(i=0;i<Resolution/(100/geshu);i++)
		{
			delay_ms(300);
			Print("=");
		}
		Print_num(Resolution,1);
		//Print("%");	
	}
}
