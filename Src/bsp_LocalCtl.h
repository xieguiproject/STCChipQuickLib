#ifndef BSP_LOCAL_CTL_H
#define BSP_LOCAL_CTL_H


#include "STC15xx.H"

sbit RF_Dat = P2^5;

#define LOCAL_BASE_TIME  15
#define SUPP_LOCAL_CONTROL 1
#if 0

#define _start_us_min	160
#define _start_us_max	200

#define _num0_us_min	10
#define _num0_us_max	20
#define _num1_us_min	0
#define _num1_us_max	8
#else

#define _start_us_min	170
#define _start_us_max	240

#define _num0_us_min	12
#define _num0_us_max	50
#define _num1_us_min	2
#define _num1_us_max	10

#endif

extern uint16_t uiLocalKey;
extern uint16_t uiKeyPaseTime;
extern uint8_t uiNewKeyFlg;
extern uint8_t cntint;	
extern uint16_t IR_Key;
extern uint16_t Low;
void soft_count();
void soft_decode();

#endif