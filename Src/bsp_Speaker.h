#ifndef SPEAKER_H
#define SPEAKER_H

#include "STC15xx.H"
#include "bspDelay.h"
#include "stc15xx_gpio.h"


sbit SPEAKER_PIN	= 	P4^5;
status bsp_SpeakerInit();
status bsp_SpeakerOpen();
status bsp_SpeakerOff();
#endif
