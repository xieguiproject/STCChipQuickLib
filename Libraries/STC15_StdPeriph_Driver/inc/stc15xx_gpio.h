#ifndef STC15XX_GPIO_H
#define STC15XX_GPIO_H

#include "STC15xx.H"
typedef enum
{ 
	GPIO_Mode_Standard_IO = 0x00,		/*��׼�������*/
	GPIO_Mode_Out_PP = 0x03,			/*�������*/
	GPIO_Mode_IPD = 0x01,				/*�������룬��������*/
	GPIO_Mode_Out_OD = 0x02				/*��©���*/
}GPIOMode_TypeDef;

#define GPIO_P0			0X00
#define GPIO_P1			0X01
#define GPIO_P2			0X02
#define GPIO_P3			0X03
#define	GPIO_P4			0x04
#define	GPIO_P5			0x05


#define GPIO_Pin_0		0x01
#define GPIO_Pin_1		0x02
#define GPIO_Pin_2		0x04
#define GPIO_Pin_3		0x08
#define GPIO_Pin_4		0x10
#define GPIO_Pin_5		0x20
#define GPIO_Pin_6		0x40
#define GPIO_Pin_7		0x80

#define GPIO_Pin_All	0xff

typedef struct
{
	uint8_t 			GPIO_Pin;		/*gpio����*/
	GPIOMode_TypeDef	GPIO_Mode;		/*gpioģʽ*/
}GPIO_InitTypeDef;

status GPIO_Init(uint8_t GPIO_PX,GPIO_InitTypeDef *GPIO_InitStruct);


#endif
