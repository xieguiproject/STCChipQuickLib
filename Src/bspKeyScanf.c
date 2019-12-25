#include "bspKeyScanf.h"

/*****************************************************************************
 * 函 数 名  : bspKeyScanfInit
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月6日
 * 函数功能  : 按键初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspKeyScanfInit()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P4,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P5,&GPIO_InitStruct);
	
}
uint8_t bspKeyScanf()
{
    static uint8_t ucKey1,ucKey2,ucKey3,ucKey4;
    uint8_t uiKeyValue = 0;
    if(KEY1_PIN == 0)
    {
        ucKey1 = 1;
    }
    //Delay10ms();
	//	Delay10ms();		
    if(KEY1_PIN == 1 && ucKey1 == 1)
    {
			ucKey1 = 0;
			uiKeyValue |= 0x01;
    }
		
	if(KEY2_PIN == 0)
    {
        ucKey2 = 1;
    }
    //Delay10ms();
	//	Delay10ms();		
    if(KEY2_PIN == 1 && ucKey2 == 1)
    {
			ucKey2 = 0;
			uiKeyValue |= 0x02;
    }
		
		if(KEY3_PIN == 0)
    {
        ucKey3 = 1;
    }
   // Delay10ms();
	//	Delay10ms();		
    if(KEY3_PIN == 1 && ucKey3 == 1)
    {
			ucKey3 = 0;
			uiKeyValue |= 0x04;
    }
		
		if(KEY4_PIN == 0)
    {
        ucKey4 = 1;
    }
    //Delay10ms();
		//Delay10ms();		
    if(KEY4_PIN == 1 && ucKey4 == 1)
    {
			ucKey4 = 0;
			uiKeyValue |= 0x08;
    }
	return uiKeyValue;
}
/*****************************************************************************
 * 函 数 名  : 按键轮询处理函数
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月6日
 * 函数功能  : 按键初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspKeyScanfDel()
{
    
}