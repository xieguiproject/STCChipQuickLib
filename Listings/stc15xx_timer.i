
#line 1 "Libraries\STC15_StdPeriph_Driver\src\stc15xx_timer.c" /0
  
#line 1 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_timer.h" /0
 
 
 
  
#line 1 ".\Libraries\CMSIS\STC15xx.H" /0
 
 
 
 
  
#line 1 "\STM32Project\STC8A\ControlBoradCodeFor51\Libraries\CMSIS\STC15xx_types.h" /0
 
 
 
  
#line 1 "d:\Keil_v5\C51\Inc\intrins.h" /0






 
 
 
 
 
 #pragma SAVE
 
 
#line 15 "d:\Keil_v5\C51\Inc\intrins.h" /1
 
 
 
#line 18 "d:\Keil_v5\C51\Inc\intrins.h" /0
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 
#line 29 "d:\Keil_v5\C51\Inc\intrins.h" /1
 
 
 
#line 32 "d:\Keil_v5\C51\Inc\intrins.h" /0
 
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 #pragma RESTORE
 
 
 
#line 4 "\STM32Project\STC8A\ControlBoradCodeFor51\Libraries\CMSIS\STC15xx_types.h" /0
 
 
 
 typedef unsigned char uint8_t;
 typedef unsigned int  uint16_t;
 typedef unsigned long int uint32_t;
 typedef int			  int16_t;
 typedef char 		  int8_t;
 
 typedef char STATUS;
 typedef char status;
 
 
 
 
 
 
 
 typedef unsigned char BYTE;
 typedef unsigned int WORD;
 
 
 


 
 
 
 typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
 typedef enum {true = 1,false = 0}BoolState;
 typedef enum 
 {
 IntSensorError1 = 1, 
 IntSensorError2 = 2, 
 IntSensorErrorAll = 3, 
 
 }SystemErrorCode;
 
 
 
 
#line 5 ".\Libraries\CMSIS\STC15xx.H" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr ACC         =   0xE0;    
 sfr B           =   0xF0;    
 sfr PSW         =   0xD0;    
 sbit CY         =   PSW^7;
 sbit AC         =   PSW^6;
 sbit F0         =   PSW^5;
 sbit RS1        =   PSW^4;
 sbit RS0        =   PSW^3;
 sbit OV         =   PSW^2;
 sbit P          =   PSW^0;
 sfr SP          =   0x81;    
 sfr DPL         =   0x82;    
 sfr DPH         =   0x83;    
 
 
 sfr P0          =   0x80;    
 sbit P00        =   P0^0;
 sbit P01        =   P0^1;
 sbit P02        =   P0^2;
 sbit P03        =   P0^3;
 sbit P04        =   P0^4;
 sbit P05        =   P0^5;
 sbit P06        =   P0^6;
 sbit P07        =   P0^7;
 sfr P1          =   0x90;    
 sbit P10        =   P1^0;
 sbit P11        =   P1^1;
 sbit P12        =   P1^2;
 sbit P13        =   P1^3;
 sbit P14        =   P1^4;
 sbit P15        =   P1^5;
 sbit P16        =   P1^6;
 sbit P17        =   P1^7;
 sfr P2          =   0xA0;    
 sbit P20        =   P2^0;
 sbit P21        =   P2^1;
 sbit P22        =   P2^2;
 sbit P23        =   P2^3;
 sbit P24        =   P2^4;
 sbit P25        =   P2^5;
 sbit P26        =   P2^6;
 sbit P27        =   P2^7;
 sfr P3          =   0xB0;    
 sbit P30        =   P3^0;
 sbit P31        =   P3^1;
 sbit P32        =   P3^2;
 sbit P33        =   P3^3;
 sbit P34        =   P3^4;
 sbit P35        =   P3^5;
 sbit P36        =   P3^6;
 sbit P37        =   P3^7;
 sfr P4          =   0xC0;    
 sbit P40        =   P4^0;
 sbit P41        =   P4^1;
 sbit P42        =   P4^2;
 sbit P43        =   P4^3;
 sbit P44        =   P4^4;
 sbit P45        =   P4^5;
 sbit P46        =   P4^6;
 sbit P47        =   P4^7;
 sfr P5          =   0xC8;    
 sbit P50        =   P5^0;
 sbit P51        =   P5^1;
 sbit P52        =   P5^2;
 sbit P53        =   P5^3;
 sbit P54        =   P5^4;
 sbit P55        =   P5^5;
 sbit P56        =   P5^6;
 sbit P57        =   P5^7;
 sfr P6          =   0xE8;    
 sbit P60        =   P6^0;
 sbit P61        =   P6^1;
 sbit P62        =   P6^2;
 sbit P63        =   P6^3;
 sbit P64        =   P6^4;
 sbit P65        =   P6^5;
 sbit P66        =   P6^6;
 sbit P67        =   P6^7;
 sfr P7          =   0xF8;    
 sbit P70        =   P7^0;
 sbit P71        =   P7^1;
 sbit P72        =   P7^2;
 sbit P73        =   P7^3;
 sbit P74        =   P7^4;
 sbit P75        =   P7^5;
 sbit P76        =   P7^6;
 sbit P77        =   P7^7;
 sfr P0M0        =   0x94;    
 sfr P0M1        =   0x93;    
 sfr P1M0        =   0x92;    
 sfr P1M1        =   0x91;    
 sfr P2M0        =   0x96;    
 sfr P2M1        =   0x95;    
 sfr P3M0        =   0xB2;    
 sfr P3M1        =   0xB1;    
 sfr P4M0        =   0xB4;    
 sfr P4M1        =   0xB3;    
 sfr P5M0        =   0xCA;    
 sfr P5M1        =   0xC9;    
 sfr P6M0        =   0xCC;    
 sfr P6M1        =   0xCB;    
 sfr P7M0        =   0xE2;    
 sfr P7M1        =   0xE1;    
 
 
 sfr PCON        =   0x87;    
 
 sfr AUXR        =   0x8E;    
 
 
 
 sfr AUXR1       =   0xA2;    
 sfr P_SW1       =   0xA2;    
 
 
 sfr CLK_DIV     =   0x97;    
 sfr PCON2				=   0X97;	 
 
 
 
 sfr BUS_SPEED   =   0xA1;    
 sfr P1ASF       =   0x9D;    
 sfr P_SW2       =   0xBA;    
 
 
 sfr IE          =   0xA8;    
 sbit EA         =   IE^7;
 sbit ELVD       =   IE^6;
 sbit EADC       =   IE^5;
 sbit ES         =   IE^4;
 sbit ET1        =   IE^3;
 sbit EX1        =   IE^2;
 sbit ET0        =   IE^1;
 sbit EX0        =   IE^0;
 sfr IP          =   0xB8;    
 sbit PPCA       =   IP^7;
 sbit PLVD       =   IP^6;
 sbit PADC       =   IP^5;
 sbit PS         =   IP^4;
 sbit PT1        =   IP^3;
 sbit PX1        =   IP^2;
 sbit PT0        =   IP^1;
 sbit PX0        =   IP^0;
 sfr IE2         =   0xAF;    
 sfr IP2         =   0xB5;    
 sfr INT_CLKO    =   0x8F;    
 
 
 sfr TCON        =   0x88;    
 sbit TF1        =   TCON^7;
 sbit TR1        =   TCON^6;
 sbit TF0        =   TCON^5;
 sbit TR0        =   TCON^4;
 sbit IE1        =   TCON^3;
 sbit IT1        =   TCON^2;
 sbit IE0        =   TCON^1;
 sbit IT0        =   TCON^0;
 
 sfr TMOD        =   0x89;    
 sfr TL0         =   0x8A;    
 sfr TL1         =   0x8B;    
 sfr TH0         =   0x8C;    
 sfr TH1         =   0x8D;    
 sfr T4T3M       =   0xD1;    
 sfr T3T4M       =   0xD1;    
 sfr T4H         =   0xD2;    
 sfr T4L         =   0xD3;    
 sfr T3H         =   0xD4;    
 sfr T3L         =   0xD5;    
 sfr T2H         =   0xD6;    
 sfr T2L         =   0xD7;    
 sfr WKTCL       =   0xAA;    
 sfr WKTCH       =   0xAB;    
 sfr WDT_CONTR   =   0xC1;    
 
 
 sfr SCON        =   0x98;    
 sbit SM0        =   SCON^7;
 sbit SM1        =   SCON^6;
 sbit SM2        =   SCON^5;
 sbit REN        =   SCON^4;
 sbit TB8        =   SCON^3;
 sbit RB8        =   SCON^2;
 sbit TI         =   SCON^1;
 sbit RI         =   SCON^0;
 sfr SBUF        =   0x99;    
 sfr S2CON       =   0x9A;    
 sfr S2BUF       =   0x9B;    
 sfr S3CON       =   0xAC;    
 sfr S3BUF       =   0xAD;    
 sfr S4CON       =   0x84;    
 sfr S4BUF       =   0x85;    
 sfr SADDR       =   0xA9;    
 sfr SADEN       =   0xB9;    
 
 
 sfr ADC_CONTR   =   0xBC;    
 sfr ADC_RES     =   0xBD;    
 sfr ADC_RESL    =   0xBE;    
 
 
 sfr SPSTAT      =   0xCD;    
 sfr SPCTL       =   0xCE;    
 sfr SPDAT       =   0xCF;    
 
 
 sfr IAP_DATA    =   0xC2;    
 sfr IAP_ADDRH   =   0xC3;    
 sfr IAP_ADDRL   =   0xC4;    
 sfr IAP_CMD     =   0xC5;    
 sfr IAP_TRIG    =   0xC6;    
 sfr IAP_CONTR   =   0xC7;    
 
 
 sfr CCON        =   0xD8;    
 sbit CF         =   CCON^7;
 sbit CR         =   CCON^6;
 sbit CCF2       =   CCON^2;
 sbit CCF1       =   CCON^1;
 sbit CCF0       =   CCON^0;
 sfr CMOD        =   0xD9;    
 sfr CL          =   0xE9;    
 sfr CH          =   0xF9;    
 sfr CCAPM0      =   0xDA;    
 sfr CCAPM1      =   0xDB;    
 sfr CCAPM2      =   0xDC;    
 sfr CCAP0L      =   0xEA;    
 sfr CCAP1L      =   0xEB;    
 sfr CCAP2L      =   0xEC;    
 sfr PCA_PWM0    =   0xF2;    
 sfr PCA_PWM1    =   0xF3;    
 sfr PCA_PWM2    =   0xF4;    
 sfr CCAP0H      =   0xFA;    
 sfr CCAP1H      =   0xFB;    
 sfr CCAP2H      =   0xFC;    
 
 
 sfr CMPCR1      =   0xE6;    
 sfr CMPCR2      =   0xE7;    
 
 
 sfr PWMCFG      =   0xf1;    
 sfr PWMCR       =   0xf5;    
 sfr PWMIF       =   0xf6;    
 sfr PWMFDCR     =   0xf7;    
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 4 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_timer.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef struct
 {
 uint8_t	TIM_Mode;		 
 
 uint8_t	TIM_Interrupt;	 
 uint8_t	TIM_ClkSource;	 
 uint8_t	TIM_ClkOut;		 
 uint8_t	TIM_HValue;	    
 uint8_t	TIM_LValue;	    
 uint8_t	TIM_Run;		 
 } TIM_InitTypeDef;
 
 
 
 
 
 status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef);
 void bspTimer_Cmd(uint8_t uiTimerNo,FunctionalState State);
 
 
 typedef void * (*TimerTaskHook)(void *arg);
 
 
 typedef struct tagTimerTaskInfo
 {
 uint16_t uiCount; 
 uint16_t uiIntTime; 
 uint16_t uiRunTime; 
 TimerTaskHook  Hook; 
 uint16_t  ucUseState;
 }TimerTaskInfo;
 typedef struct tagTimerInitValue
 {
 uint8_t	TIM_HValue;	    
 uint8_t	TIM_LValue;	    
 }TimerInitValue;
 
 
 
 int8_t bspTimerTaskGetItem();
 void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime);
 void bspTimerTaskInit();
 void bspTimeDelayInit(); 
 void bspTimeDelay(uint16_t uiDelayMs);
 
#line 1 "Libraries\STC15_StdPeriph_Driver\src\stc15xx_timer.c" /0
 
 
 TimerTaskInfo TimerTaskInfoQueue[5];
 uint16_t uiTimeDelayCount = 0;
 TimerInitValue TimerInitValueParm[5] = {0};
 














 
 status bspTimer_Init(uint8_t uiTimerNo,TIM_InitTypeDef *InitTypeDef)
 {
 if(uiTimerNo > 4)	return -1;	 
 
 TimerInitValueParm[uiTimerNo].TIM_HValue = InitTypeDef->TIM_HValue;
 TimerInitValueParm[uiTimerNo].TIM_LValue = InitTypeDef->TIM_LValue;
 switch(uiTimerNo)
 {
 case 0:
 {
 
 if(InitTypeDef->TIM_ClkSource == 0)
 AUXR |= 0X80;
 else
 AUXR &= ~0X80;
 
 TMOD &= ~(0X0F << 0);		 
 switch(InitTypeDef->TIM_Mode)
 {
 case 0:
 TMOD |= (0x00 << 0);					  
 break;
 case 1:
 TMOD |= (0X01 << 0); 
 break;
 case 2:
 TMOD |= (0X02 << 0); 
 break;
 case 3:
 TMOD |= (0X03 << 0); 
 break;
 }
 
 
 TH0 = InitTypeDef->TIM_HValue;
 TL0 = InitTypeDef->TIM_LValue;
 
 
 TF0 = 0;
 
 if(InitTypeDef->TIM_Interrupt == ENABLE)
 {
 ET0 = 1;
 
 }
 else
 {
 ET0 = 0;
 }
 if(InitTypeDef->TIM_Run == ENABLE)
 {
 
 TR0 = 1;
 }
 else
 {
 TR0 = 0;
 }
 
 
 }break;
 case 1:
 {
 
 if(InitTypeDef->TIM_ClkSource == 0)
 AUXR |= 0X40;
 else
 AUXR &= ~0X40;
 
 TMOD &= ~(0Xf0 << 0);		 
 switch(InitTypeDef->TIM_Mode)
 {
 case 0:
 TMOD |= (0x00 << 4);					  
 break;
 case 1:
 TMOD |= (0X01 << 4); 
 break;
 case 2:
 TMOD |= (0X02 << 4); 
 break;
 case 3:
 TMOD |= (0X03 << 4); 
 break;
 }
 
 TH1 = InitTypeDef->TIM_HValue;
 TL1 = InitTypeDef->TIM_LValue;
 
 if(InitTypeDef->TIM_Interrupt == ENABLE)
 {
 ET1 = 1;
 
 }
 else
 {
 ET1 = 0;
 }
 if(InitTypeDef->TIM_Run == ENABLE)
 {
 
 TR1 = 1;
 }
 else
 {
 TR1 = 0;
 }
 
 
 TF1 = 0;
 }break;
 case 2:
 {
 
 if(InitTypeDef->TIM_ClkSource == 0)
 AUXR |= 0X04;
 else
 AUXR &= ~0X04;
 
 
 T2H = InitTypeDef->TIM_HValue;
 T2L = InitTypeDef->TIM_LValue;
 
 if(InitTypeDef->TIM_Interrupt == ENABLE)
 {
 IE2 |= (0X01 << 2);
 
 }
 else
 {
 IE2 &= ~(0X01 << 2);
 }
 
 if(InitTypeDef->TIM_Run == ENABLE)
 {
 
 AUXR |= (0X01 << 4);
 }
 else
 {
 AUXR &= ~(0X01 << 4);
 }
 };break;
 
 case 3:break;
 case 4:break;
 
 }
 return 1;
 }
 void bspTimer_Cmd(uint8_t  uiTimerNo,FunctionalState State)
 {
 switch(uiTimerNo)
 {
 case 0:
 {
 if(State == ENABLE)
 {
 TR0 = 1;
 }
 else
 {
 TR0 = 0;
 }
 }break;
 case 1:
 break;
 case 2:
 {
 if(State == ENABLE)
 {
 AUXR |= (0X01 << 4);
 }
 else
 {
 AUXR &= ~(0X01 << 4);
 }
 };break;
 }
 }
 void bspTimerTaskInit()
 {
 uint8_t ucLoop = 0;
 for(ucLoop = 0;ucLoop < 5;ucLoop++)
 {
 TimerTaskInfoQueue[ucLoop].ucUseState = false;
 TimerTaskInfoQueue[ucLoop].uiCount = 0;
 TimerTaskInfoQueue[ucLoop].uiIntTime = 0;
 TimerTaskInfoQueue[ucLoop].Hook = ((void *)0);
 }
 }
 int8_t bspTimerTaskGetItem()
 {
 uint8_t ucLoop = 0;
 for(ucLoop = 0;ucLoop < 5;ucLoop++)
 {
 if(TimerTaskInfoQueue[ucLoop].ucUseState == false) 
 {
 TimerTaskInfoQueue[ucLoop].ucUseState = true;
 TimerTaskInfoQueue[ucLoop].uiCount = 0;
 TimerTaskInfoQueue[ucLoop].uiIntTime = 0;
 TimerTaskInfoQueue[ucLoop].Hook = ((void *)0);
 return ucLoop;
 }
 }
 return -1;
 }
 void bspTimerTaskFreeItem(int8_t Item)
 {
 if(Item < 5)
 {
 TimerTaskInfoQueue[Item].ucUseState = false;
 }
 }
 sbit led1 = P2^3;
 void LedControlTasksss()
 {
 static unsigned int  uiLedFlag = 0;
 
 if(uiLedFlag == 0)
 {
 led1 = 1;
 uiLedFlag = 1;
 }
 else
 { 
 led1 = 0;
 uiLedFlag = 0;
 }
 }
 void bspTimer2_IRQHandler(void) interrupt 12
 {
 T2H = TimerInitValueParm[2].TIM_HValue;
 T2L = TimerInitValueParm[2].TIM_LValue;
 
 }
 
 void bspTimer0_IRQHandler(void) interrupt 1
 {
 uint16_t ucLoop = 0;
 
 TH0 = TimerInitValueParm[0].TIM_HValue;
 
 TL0 = TimerInitValueParm[0].TIM_LValue;
 
 for(ucLoop = 0;ucLoop < 5;ucLoop++)
 {	
 if(TimerTaskInfoQueue[ucLoop].ucUseState == true && 
 TimerTaskInfoQueue[ucLoop].Hook != ((void *)0))
 {
 if(TimerTaskInfoQueue[ucLoop].uiRunTime == 0xffff ||
 TimerTaskInfoQueue[ucLoop].uiRunTime > 0)
 {
 if(TimerTaskInfoQueue[ucLoop].uiCount >= TimerTaskInfoQueue[ucLoop].uiIntTime)
 {
 
 TimerTaskInfoQueue[ucLoop].Hook(((void *)0));
 TimerTaskInfoQueue[ucLoop].uiCount = 0;
 TimerTaskInfoQueue[ucLoop].uiRunTime--;
 }
 else
 {
 TimerTaskInfoQueue[ucLoop].uiCount++; 
 }
 }
 else
 {
 TimerTaskInfoQueue[ucLoop].ucUseState = false;
 TimerTaskInfoQueue[ucLoop].Hook = ((void *)0);
 
 }
 }
 }
 }
 
 void bspTimerRegisterHook(TimerTaskHook hook,uint16_t uiIntTime)
 {
 uint8_t Item = 0;
 
 Item = bspTimerTaskGetItem(); 
 if(Item == -1)
 {
 return;
 }
 TimerTaskInfoQueue[Item].Hook = hook;
 TimerTaskInfoQueue[Item].uiIntTime = uiIntTime; 
 TimerTaskInfoQueue[Item].uiCount = 0;
 TimerTaskInfoQueue[Item].uiRunTime = 0xffff;
 }
 
 void * bspTimeDelayTask(void *arg)
 {
 if(uiTimeDelayCount > 0)
 {
 uiTimeDelayCount--;
 }
 }
 void bspTimeDelayInit()
 {
 uint8_t Item = 0;
 
 Item = bspTimerTaskGetItem(); 
 if(Item == -1)
 {
 return;
 }
 TimerTaskInfoQueue[Item].Hook = bspTimeDelayTask;
 TimerTaskInfoQueue[Item].uiIntTime = 1; 
 TimerTaskInfoQueue[Item].uiCount = 0;
 TimerTaskInfoQueue[Item].uiRunTime = 0xffff;
 }
 void bspTimeDelay(uint16_t uiDelayMs)
 {
 uiTimeDelayCount = uiDelayMs;
 while(uiTimeDelayCount != 0);
 }