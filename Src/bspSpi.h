#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "STC15.H"
#include "intrins.h"
#include "bspUsart.h"
#include "string.h"
#include <stdlib.h>
#include "bspDataType.h"
#include "bspGpioLib.h"


#define SPIF        0x80        //SPSTAT.7  
#define WCOL        0x40        //SPSTAT.6 
#define SPEN        0x40        //SPCTL.6   

sbit SPISS      =   P2^4;       //SPI设备的片选信号线
#define MSTR        0x10        //SPCTL.4
#define ESPI        0x02        //IE2.1

#define SPI_SPEED_DIV4 		0X00
#define SPI_SPEED_DEV8		0X01
#define SPI_SPEED_DEV16     0X02
#define SPI_SPEED_DEV32		0X03

#endif
