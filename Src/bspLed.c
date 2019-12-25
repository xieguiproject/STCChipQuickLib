/******************************************************************************

                  版权所有 (C), 2001-2011, XXXXX 技术有限公司                  

 ******************************************************************************
  文 件 名   : bspLed.c
  版 本 号   : 初稿
  作    者   : Gavinx
  生成日期   : 2019年4月3日 星期三
  最近修改   :
  功能描述   : LED驱动阈
  函数列表   :
              CloseLed
              OpenLed
  修改历史   :
  1.日    期   : 2019年4月3日 星期三
    作    者   : Gavinx
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
	 
#include "bspLed.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
void bsp_GennealLedInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;/*4.1*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIO_P4,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;/*4.1*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIO_P3,&GPIO_InitStruct);
	
	CloseLed(YellowLed);
	CloseLed(RedLed);
}
/*****************************************************************************
 函 数 名  : OpenLed
 功能描述  : 打开LED
 输入参数  : LED led  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年4月3日 星期三
    作    者   : Gavinx
    修改内容   : 新生成函数

*****************************************************************************/
void OpenLed(LED led)
{
	switch(led)
	{
		case YellowLed:
				YellowLedPIN = 1;
			break;
		case RedLed:
				RedLedPIN = 1;
	}
}
/*****************************************************************************
 函 数 名  : CloseLed
 功能描述  : 关闭LED灯
 输入参数  : LED led  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年4月3日 星期三
    作    者   : Gavinx
    修改内容   : 新生成函数

*****************************************************************************/
void CloseLed(LED led)
{
	switch(led)
	{
		case YellowLed:
				YellowLedPIN = 0;
			break;
		case RedLed:
				RedLedPIN = 0;
	}
}
/***************************************************************************
迷你板控制
****************************************************************************/

/*迷你板的控制初始化*/
void bsp_MiniRgbCtlInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;/*P3.2 P3.3 P3.4*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIO_P3,&GPIO_InitStruct);
	bsp_MiniRgbCtl(Off);
}
void bsp_MiniRgbCtl(RGBLED Color)
{
	switch(Color)
	{
		case Blue:
			KMBLed = 1;
			break;
		case Red:
			KMRLed = 1;
			break;
		case Green:
			KMGLed = 1;
			break;
		case Off:
			KMBLed = 0;
			KMRLed = 0;
			KMGLed = 0;
			break;
	}
}

void bsp_BigRgbCtlInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;/*P43.2 P4.3 P4.4*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIO_P4,&GPIO_InitStruct);
	bsp_BigRgbCtl(Off);
}
/*读取当前RGB灯的颜色*/
RGBLED  bsp_BitRgbRead()
{
	if(KBBLed)
	{
		return Blue;
	}
	else if(KBGLed && KBRLed)
	{
		return Yellow;
	}
	else if(KBRLed)
	{
		return Red;
	}
	else if(KBGLed)
	{
		return Green;
	}
	else
	{
		return Off;
	}
}
/*大灯板RGB控制,第一个灯控制颜色*/
void bsp_BigRgbCtl(RGBLED Color)
{
	switch(Color)
	{
		case Blue:
			KBBLed = 1;
			break;
		case Red:
			KBRLed = 1;
			break;
		case Green:
			KBGLed = 1;
			break;
		case Yellow:
			KBGLed = 1;
			KBRLed = 1;
			break;
		case Off:
			KBBLed = 0;
			KBRLed = 0;
			KBGLed = 0;
			break;
	}
}