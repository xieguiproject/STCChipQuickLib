#ifndef CPU_CFG_H
#define CPU_CFG_H
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "Main.h"
#include "intrins.h"

#define STC_15WXX	/*stc15Wϵ�е�Ƭ��*/
#undef  STC_15FXX	/*stc15Fϵ�е�Ƭ��*/
#undef  STC_89CXX	/*stc89Cϵ�е�Ƭ��*/


typedef enum tagRM_LOG_LEVEL_E
{
	RM_ERROR = 0, 
	RM_RUN,
	RM_DEBUG
}RM_LOG_LEVEL_E;

#define logMsg(level, X0, X1, X2, X3, X4, X5, X6)             \
{                                                             \
    if (guiDbgLevel >= level)                               \
    {                                                         \
      	printf("<%s %d> "X0,__FILE__, __LINE__, X1, X2, X3, X4,X5,X6);\
    }                                                         \
}

#endif
