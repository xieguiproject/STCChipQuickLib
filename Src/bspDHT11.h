#ifndef BSP_DHT11_H
#define BSO_DHT11_H

#include "STC15xx.H"

#include "stdio.h"
#include "string.h"
#include "stc15xx_gpio.h"
#include "stc15xx_usart.h"

sbit DHT11_IO = P3^3;

typedef struct tagDHT11Info
{
	uint8_t uiHumidity;//�¶���������
	uint8_t uiHumidityPoint;//�¶�С������
	uint8_t uiTemperature;//ʪ����������
	uint8_t uiTemperaturePoint;//ʪ��С������
	uint8_t uiCrcData;//У��ֵ
}DHT11Info;
uint8_t bspDHT11Receive(DHT11Info *Info);
void bspDHT11Init();
void Dht11_delay_ms(uint16_t ms);
void Dht11_delay_us(uint8_t ms);
#endif
