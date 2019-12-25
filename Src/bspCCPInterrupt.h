#ifndef BSP_CCP_INTERRUPT_H
#define BSP_CCP_INTERRUPT_H

#include "STC15xx.H"
#include "main.h"
#include "bspPwm.h"

void bspCCPInterruptInit();

extern uint8_t uiIntFlg;
extern uint8_t uiCount;

#endif
