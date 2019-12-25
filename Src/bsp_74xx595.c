#include "bsp_74xx595.h"

status bsp74lx595Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P1,&GPIO_InitStruct);
}
uint8_t L74xx595_Wirte_One_Byte(uint8_t dat)
{
	uint8_t i=0;
	
	L74XX595_SHR=1;//拉低锁存信号，准备锁存数据
	for(i=0;i<L74XX595_bit;i++)
	{
		L74XX595_CLK = 0;
		if(dat&0x01 == 1)
			L74XX595_IO = 1;
		else
			L74XX595_IO = 0;
		L74XX595_CLK = 1;
		dat>>=1;
	}
	L74XX595_SHR=0;
	L74XX595_SHR=1;
	return 0;
}

