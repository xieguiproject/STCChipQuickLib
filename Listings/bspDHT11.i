
#line 1 "Src\bspDHT11.c" /0
  
#line 1 "Src\bspDHT11.h" /0
 
 
 
  
#line 1 ".\Libraries\CMSIS\STC15xx.H" /0
 
 
 
 
  
#line 1 "\STM32Project\SmartPowerPlugK095\Designer\TempAcquisition\Code\ControlBoradCodeFor51\Libraries\CMSIS\STC15xx_types.h" /0
 
 
 
  
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
 
 
 
#line 4 "\STM32Project\SmartPowerPlugK095\Designer\TempAcquisition\Code\ControlBoradCodeFor51\Libraries\CMSIS\STC15xx_types.h" /0
 
 
 
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 4 "Src\bspDHT11.h" /0
 
 
  
#line 1 "d:\Keil_v5\C51\Inc\stdio.h" /0






 
 
 
 
 
 
 
 
 
 
#line 17 "d:\Keil_v5\C51\Inc\stdio.h" /1
  
 
#line 19 "d:\Keil_v5\C51\Inc\stdio.h" /0
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 6 "Src\bspDHT11.h" /0
 
  
#line 1 "d:\Keil_v5\C51\Inc\string.h" /0






 
 
 
 
 
 
#line 13 "d:\Keil_v5\C51\Inc\string.h" /1
  
 
 
#line 16 "d:\Keil_v5\C51\Inc\string.h" /0
 
 
#line 18 "d:\Keil_v5\C51\Inc\string.h" /1
  
 
#line 20 "d:\Keil_v5\C51\Inc\string.h" /0
 
 #pragma SAVE
 #pragma REGPARMS
 extern char  *strcat  (char *s1, const char *s2);
 extern char  *strncat (char *s1, const char *s2, size_t n);
 
 extern char   strcmp  (const char *s1, const char *s2);
 extern char   strncmp (const char *s1, const char *s2, size_t n);
 
 extern char  *strcpy  (char *s1, const char *s2);
 extern char  *strncpy (char *s1, const char *s2, size_t n);
 
 extern size_t strlen  (const char *);
 
 extern char  *strchr  (const char *s, char c);
 extern int    strpos  (const char *s, char c);
 extern char  *strrchr (const char *s, char c);
 extern int    strrpos (const char *s, char c);
 
 extern size_t strspn  (const char *s, const char *set);
 extern size_t strcspn (const char *s, const char *set);
 extern char  *strpbrk (const char *s, const char *set);
 extern char  *strrpbrk(const char *s, const char *set);
 extern char  *strstr  (const char *s, const char *sub);
 extern char  *strtok  (char *str, const char *set);
 
 extern char   memcmp  (const void *s1, const void *s2, size_t n);
 extern void  *memcpy  (void *s1, const void *s2, size_t n);
 extern void  *memchr  (const void *s, char val, size_t n);
 extern void  *memccpy (void *s1, const void *s2, char val, size_t n);
 extern void  *memmove (void *s1, const void *s2, size_t n);
 extern void  *memset  (void *s, char val, size_t n);
 #pragma RESTORE
 
 
#line 7 "Src\bspDHT11.h" /0
 
  
#line 1 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_gpio.h" /0
 
 
 
  
#line 1 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 2 ".\Libraries\CMSIS\STC15xx.H" /1
  
 
 
  
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
 
 
#line 321 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 4 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_gpio.h" /0
 
 typedef enum
 { 
 GPIO_Mode_Standard_IO = 0x00,		 
 GPIO_Mode_Out_PP = 0x03,			 
 GPIO_Mode_IPD = 0x01,				 
 GPIO_Mode_Out_OD = 0x02				 
 }GPIOMode_TypeDef;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef struct
 {
 uint8_t 			GPIO_Pin;		 
 GPIOMode_TypeDef	GPIO_Mode;		 
 }GPIO_InitTypeDef;
 
 status GPIO_Init(uint8_t GPIO_PX,GPIO_InitTypeDef *GPIO_InitStruct);
 
 
 
#line 8 "Src\bspDHT11.h" /0
 
  
#line 1 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_usart.h" /0
 
 
 
  
#line 1 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 2 ".\Libraries\CMSIS\STC15xx.H" /1
  
 
 
  
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
 
 
#line 321 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 4 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_usart.h" /0
 
  
#line 1 "\STM32Project\SmartPowerPlugK095\Designer\TempAcquisition\Code\ControlBoradCodeFor51\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_timer.h" /0
 
 
 
  
#line 1 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 2 ".\Libraries\CMSIS\STC15xx.H" /1
  
 
 
  
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
 
 
#line 321 ".\Libraries\CMSIS\STC15xx.H" /0
 
#line 4 "\STM32Project\SmartPowerPlugK095\Designer\TempAcquisition\Code\ControlBoradCodeFor51\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_timer.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
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
 
#line 5 ".\Libraries\STC15_StdPeriph_Driver\inc\stc15xx_usart.h" /0
 
 typedef struct
 { 
 uint8_t		UART_Mode;			 
 uint8_t		UART_BRT_Use;		 
 uint32_t	UART_BaudRate;		 
 uint8_t		Morecommunicate;	 
 uint8_t		UART_RxEnable;		 
 uint8_t		BaudRateDouble;		 
 uint8_t		UART_Interrupt;		 
 uint8_t		UART_Polity;		 
 uint8_t		UART_P_SW;			 
 uint8_t		UART_RXD_TXD_Short;	 
 
 }USART_InitTypeDef; 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 status bspUsartSendByte(uint8_t uiUsartNo,uint8_t uiData);
 status bspUSART_Init(uint8_t uiUsartNo,USART_InitTypeDef *USART_InitStruct);
 status bspUsartSendString(uint8_t uiUsartNo,uint8_t *uiData,uint16_t uiLen);
 
#line 9 "Src\bspDHT11.h" /0
 
 
 sbit DHT11_IO = P3^3;
 
 typedef struct tagDHT11Info
 {
 uint8_t uiHumidity; 
 uint8_t uiHumidityPoint; 
 uint8_t uiTemperature; 
 uint8_t uiTemperaturePoint; 
 uint8_t uiCrcData; 
 }DHT11Info;
 uint8_t bspDHT11Receive(DHT11Info *Info);
 void bspDHT11Init();
 void Dht11_delay_ms(uint16_t ms);
 void Dht11_delay_us(uint8_t ms);
 
#line 1 "Src\bspDHT11.c" /0
 
 
 void Delay8us()      
 {
 unsigned char i;
 
 _nop_();
 _nop_();
 i = 19;
 while (--i);
 }
 void Delay35us()         
 {
 unsigned char i;
 
 _nop_();
 i = 94;
 while (--i);
 }
 void Delay30us()         
 {
 unsigned char i;
 
 _nop_();
 _nop_();
 i = 80;
 while (--i);
 }
 void Delay18ms()         
 {
 unsigned char i, j, k;
 
 i = 1;
 j = 194;
 k = 160;
 do
 {
 do
 {
 while (--k);
 } while (--j);
 } while (--i);
 }
 void Delay1000ms()		 
 {
 unsigned char i, j, k;
 
 _nop_();
 _nop_();
 i = 43;
 j = 6;
 k = 203;
 do
 {
 do
 {
 while (--k);
 } while (--j);
 } while (--i);
 }
 void bspDHT11Init()
 {
 
 GPIO_InitTypeDef GPIO_InitStruct;
 
 GPIO_InitStruct.GPIO_Pin = 0x08;
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Standard_IO;
 GPIO_Init(0X03,&GPIO_InitStruct);
 
 }














 
 
 
 uint8_t bspDHT11ReceiveByte()
 {
 uint8_t uiLoop = 0;
 uint8_t uiDat = 0;
 uint16_t uiCount = 0;
 uint8_t uiTemp = 0;
 for(uiLoop = 0; uiLoop < 8; uiLoop++)
 {
 uiCount = 65535;
 while(!DHT11_IO && --uiCount  > 0);
 Delay30us();
 uiTemp = 0;
 if(DHT11_IO)
 {
 uiTemp = 1;
 }
 uiCount = 65535;
 while(DHT11_IO && --uiCount  > 0);
 uiDat <<= 1;
 uiDat = uiDat | uiTemp;
 }
 return uiDat;
 }
 
#line 112 "Src\bspDHT11.c" /1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 138 "Src\bspDHT11.c" /0














 
 uint8_t bspDHT11Receive(DHT11Info *Info)
 {
 uint16_t uiCount = 0;
 
 DHT11_IO = 1; 
 Delay8us();
 DHT11_IO = 0; 
 
 Delay18ms();
 DHT11_IO = 1; 
 Delay35us();
 if(!DHT11_IO)
 {
 uiCount = 65536;
 while(!DHT11_IO && --uiCount > 0);
 uiCount = 65536;
 while(DHT11_IO && --uiCount > 0);
 
 Info->uiHumidity = bspDHT11ReceiveByte();
 Info->uiHumidityPoint = bspDHT11ReceiveByte();
 
 Info->uiTemperature = bspDHT11ReceiveByte();
 Info->uiTemperaturePoint = bspDHT11ReceiveByte();
 
 Info->uiCrcData = bspDHT11ReceiveByte();
 
 if(Info->uiCrcData == Info->uiTemperature + Info->uiTemperaturePoint + 
 Info->uiHumidity + Info->uiHumidityPoint)
 {
 return true;
 }
 }
 return false;
 }
 
