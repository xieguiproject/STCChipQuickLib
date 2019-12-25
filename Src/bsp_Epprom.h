#ifndef BSP_EPPROM_H
#define BSP_EPPROM_H


#include "STC15xx.H"
#include "intrins.h"


#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

#define ENABLE_IAP_30M 0x80           //if SYSCLK<30MHz
#define ENABLE_IAP_24M 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP_20M 0x82            //if SYSCLK<20MHz
#define ENABLE_IAP_12M 0x83           //if SYSCLK<12MHz
#define ENABLE_IAP_6M 0x84           //if SYSCLK<6MHz
#define ENABLE_IAP_3M 0x85           //if SYSCLK<3MHz
#define ENABLE_IAP_2M 0x86           //if SYSCLK<2MHz
#define ENABLE_IAP_1M 0x87           //if SYSCLK<1MHz

#define ENABLE_IAP ENABLE_IAP_20M

#define EPPROM_PARM_BASE_ADDR   0x0400     

void IapEraseSector(WORD addr);

void IapWrite(WORD addr,BYTE *buf,uint16_t uiLen);
void IapRead(WORD addr,BYTE *buf,uint16_t uiLen);
BYTE IapReadByte(WORD addr);

void EppromTest();


#endif
