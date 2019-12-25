
#line 1 "Src\bspDelay.c" /0
  
#line 1 "Src\bspDelay.h" /0
 
 
 
  
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
 
 
 
#line 4 "Src\bspDelay.h" /0
 
 void Delay10ms();
 
#line 1 "Src\bspDelay.c" /0
 
 
 void Delay1us()		 
 {
 _nop_();
 _nop_();
 _nop_();
 }
 void Delay10us()		 
 {
 unsigned char i;
 
 _nop_();
 i = 25;
 while (--i);
 }
 void Delay100us()		 
 {
 unsigned char i, j;
 
 _nop_();
 _nop_();
 i = 2;
 j = 15;
 do
 {
 while (--j);
 } while (--i);
 }
 void Delay500us()		 
 {
 unsigned char i, j;
 
 _nop_();
 _nop_();
 i = 6;
 j = 93;
 do
 {
 while (--j);
 } while (--i);
 }
 void Delay1ms()		 
 {
 unsigned char i, j;
 
 _nop_();
 _nop_();
 _nop_();
 i = 11;
 j = 190;
 do
 {
 while (--j);
 } while (--i);
 }
 void Delay10ms()		 
 {
 unsigned char i, j;
 
 i = 108;
 j = 145;
 do
 {
 while (--j);
 } while (--i);
 }
 void Delay100ms()		 
 {
 unsigned char i, j, k;
 
 _nop_();
 _nop_();
 i = 5;
 j = 52;
 k = 195;
 do
 {
 do
 {
 while (--k);
 } while (--j);
 } while (--i);
 }
 void Delay500ms()		 
 {
 unsigned char i, j, k;
 
 _nop_();
 _nop_();
 i = 22;
 j = 3;
 k = 227;
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
