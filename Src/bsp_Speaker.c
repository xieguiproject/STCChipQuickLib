#include "bsp_Speaker.h"

status bsp_SpeakerInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P4,&GPIO_InitStruct);
	return true;
}
status bsp_SpeakerOpen()
{
	SPEAKER_PIN	= 1;
}
status bsp_SpeakerOff()
{
	SPEAKER_PIN = 0;
}
