#include "bsp_DigitalSensor.h"

DigitalSensor mdDigitalSensor;

status bspDigitalSensorInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P1,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P4,&GPIO_InitStruct);
	
	return 1;
}
static bspDigitalSensor(uint8_t ucSensorNo)
{
	switch(ucSensorNo)
	{
		case 0:
			return DigitalPin_0;	
		case 1:
			return DigitalPin_1;
		case 2:
			return DigitalPin_2;
	}
	return -1;
}
/*读取当前传感器值*/
void bspDigitalSensorDel()
{
	uint8_t ucLoop = 0;

	for(ucLoop = 0;ucLoop < MAX_DIGITAL_SENSOR_NUM;ucLoop++)
	{
		mdDigitalSensor.uiValue[ucLoop] = bspDigitalSensor(ucLoop);
	}
}