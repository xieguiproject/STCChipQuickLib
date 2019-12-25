#include "stc15xx_gpio.h"

status GPIO_SetBits(uint8_t GPIO_PX,uint8_t GPIO_Pin)
{
	switch(GPIO_PX)
	{
		case GPIO_P0:
			P0 = 0X00;
			break;
		case GPIO_P1:
			break;
	}
}
status GPIO_Init(uint8_t GPIO_PX,GPIO_InitTypeDef *GPIO_InitStruct)
{
	if(GPIO_PX > GPIO_P5)				return ERROR;	//空操作
	if(GPIO_InitStruct->GPIO_Mode > GPIO_Mode_Out_PP)	return ERROR;	//错误
	if(GPIO_PX == GPIO_P0)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P0M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P0M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P0M1 |=  GPIO_InitStruct->GPIO_Pin;
			P0M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P0M1 |=  GPIO_InitStruct->GPIO_Pin;
			P0M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P0M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P0M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	if(GPIO_PX == GPIO_P1)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P1M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P1M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P1M1 |=  GPIO_InitStruct->GPIO_Pin;
			P1M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P1M1 |=  GPIO_InitStruct->GPIO_Pin;
			P1M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P1M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P1M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	if(GPIO_PX == GPIO_P2)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P2M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P2M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P2M1 |=  GPIO_InitStruct->GPIO_Pin;
			P2M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P2M1 |=  GPIO_InitStruct->GPIO_Pin;
			P2M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P2M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P2M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	if(GPIO_PX == GPIO_P3)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P3M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P3M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P3M1 |=  GPIO_InitStruct->GPIO_Pin;
			P3M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P3M1 |=  GPIO_InitStruct->GPIO_Pin;
			P3M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P3M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P3M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	if(GPIO_PX == GPIO_P4)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P4M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P4M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P4M1 |=  GPIO_InitStruct->GPIO_Pin;
			P4M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P4M1 |=  GPIO_InitStruct->GPIO_Pin;
			P4M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P4M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P4M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	if(GPIO_PX == GPIO_P5)
	{
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Standard_IO)
		{
			P5M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P5M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //上拉准双向口
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
		{
			P5M1 |=  GPIO_InitStruct->GPIO_Pin;
			P5M0 &= ~GPIO_InitStruct->GPIO_Pin;	 //浮空输入
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_OD)
		{
			P5M1 |=  GPIO_InitStruct->GPIO_Pin;
			P5M0 |=  GPIO_InitStruct->GPIO_Pin;	 //开漏输出
		}
		if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_Out_PP)
		{
			P5M1 &= ~GPIO_InitStruct->GPIO_Pin;
			P5M0 |=  GPIO_InitStruct->GPIO_Pin;	 //推挽输出
		}
	}
	
	return OK;	//成功
}
