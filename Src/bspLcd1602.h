#ifndef _LCD1602_H
#define _LCD1602_H

#include "STC15xx.h"
#include "stc15xx_gpio.h"
#include "stdio.h"
#include "math.h"

//端口定义
#define  DBPort P2		//LCD数据端口
sbit LcdRs		= P0^7;
sbit LcdRw		= P0^6;
sbit LcdEn  	= P0^5;
sbit Lcdbf    = P2^0;		//LCD忙标志 Busy Flag



void LCD_Initial(void);
void Print(unsigned char *str);
void GotoXY(unsigned char x, unsigned char y);
void LCD_Write(bit style, unsigned char input);
void  LCD_Wait(void);
void delay(unsigned int t)	;
void Print_num(unsigned int display_data,unsigned char uiBit);
void Set_cursorXY(unsigned char x,unsigned char y);
void GUI_Progress_Bar(unsigned char x,unsigned char y,unsigned char Resolution);
void PrintByte(unsigned char bytes);
void bsp_LcdClean();
void Print_Float(float datas,unsigned char ucBit1,unsigned char ucBit2);
#endif