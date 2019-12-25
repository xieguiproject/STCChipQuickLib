#ifndef BSP_DATA_TYPE_H
#define BSP_DATA_TYPE_H

#include "intrins.h"


typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long int uint32_t;
typedef int			  int16_t;
typedef char 		  int8_t;

typedef char STATUS;
typedef char status;

#define ERROR   -1
#define OK      1
#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5


typedef unsigned char BYTE;
typedef unsigned int WORD;
#define NULL ((void *)0)

#define SWAP_LE16(x)	((uint16_t)(\
							(((uint16_t)(x) & (uint16_t)0x00ffUL) <<  8) | \
							(((uint16_t)(x) & (uint16_t)0xff00UL) >>  8)))



typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {true = 1,false = 0}BoolState;
typedef enum 
{
	IntSensorError1 = 1,/*转速装传感器故障1,P3.5霍尔传感器无中断*/
	IntSensorError2 = 2,/*转速装传感器故障1,P3.6霍尔传感器无中断*/
	IntSensorErrorAll = 3,/*P3.5和3.6均无中断，一般为电机被卡死或者电机故障*/
	
}SystemErrorCode;
/*系统故障代码*/


#endif
