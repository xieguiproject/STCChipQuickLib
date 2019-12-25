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
	uint8_t uiHumidity;//温度整数部分
	uint8_t uiHumidityPoint;//温度小数部分
	uint8_t uiTemperature;//湿度整数部分
	uint8_t uiTemperaturePoint;//湿度小数部分
	uint8_t uiCrcData;//校验值
}DHT11Info;
uint8_t bspDHT11Receive(DHT11Info *Info);
void bspDHT11Init();
void Dht11_delay_ms(uint16_t ms);
void Dht11_delay_us(uint8_t ms);
#endif
