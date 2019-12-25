/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, XXXXX �������޹�˾                  

 ******************************************************************************
  �� �� ��   : bspLed.c
  �� �� ��   : ����
  ��    ��   : Gavinx
  ��������   : 2019��4��3�� ������
  ����޸�   :
  ��������   : LED������
  �����б�   :
              CloseLed
              OpenLed
  �޸���ʷ   :
  1.��    ��   : 2019��4��3�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
	 
#include "bspLed.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
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
 �� �� ��  : OpenLed
 ��������  : ��LED
 �������  : LED led  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��4��3�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

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
 �� �� ��  : CloseLed
 ��������  : �ر�LED��
 �������  : LED led  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��4��3�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

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
��������
****************************************************************************/

/*�����Ŀ��Ƴ�ʼ��*/
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
/*��ȡ��ǰRGB�Ƶ���ɫ*/
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
/*��ư�RGB����,��һ���ƿ�����ɫ*/
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