#include "bsp_LocalCtl.h"
#include "stdio.h"



uint16_t Low = 0;
bit   Jump_flag;
uint8_t Temp_addrl,Temp_addrh,Address_l,Address_h;
uint8_t cntint = 0;	
uint16_t IR_Key = 0;
uint32_t IR_IdCode = 0;//遥控器身份信息
bit   start_flag=0,IR_OVER;
uint16_t release_key;	
uint16_t RF_Value_Cnt;

uint32_t RF_data;
uint16_t uiLocalKey = 0;
uint16_t uiKeyPaseTime = 0;
uint8_t  uiNewKeyFlg = 0;
void soft_decode();
uint16_t uiSoftCount = 0;
void soft_count()//接受吗
{
	if(RF_Dat==0)	
	{	
		Low++;
		if(Jump_flag)Jump_flag=0;		
	}
	else if(RF_Dat==1)	
	{
		if(!Jump_flag)
		{	
			Jump_flag=1;
			soft_decode();
			Low=0;
		}
	}
	uiSoftCount++;
	if(uiSoftCount > 5000)
	{
		uiSoftCount = 0;
		LocalCmdDel();
	}

}

void soft_decode()
{
	static uint8_t uiKeyFlg = 0;
	if(start_flag==0)
	{
		if(( Low > _start_us_min ) && ( Low < _start_us_max ))	
		{
			start_flag=1;
			cntint=0;
			IR_Key=0;
			RF_data=0;
		}
		else 
		{
			RF_Value_Cnt=0;
			release_key++;
			if(release_key>500)release_key=500;
		}
	}
	else if((start_flag==1)&&(cntint<24))
	{
		if(( Low > _num0_us_min ) && ( Low < _num0_us_max ))
		{
			RF_data = RF_data<<1;
			cntint++;
		}
		else if(( Low > _num1_us_min ) && ( Low < _num1_us_max ))		
		{
			RF_data=RF_data<<1;
			RF_data|=1;
			cntint++;
		}
		else 
		{
			start_flag=0;
			cntint=0;
		}
	}

	if(cntint == 24)
	{
		release_key=0;
		RF_Value_Cnt++;
		if(RF_Value_Cnt>500)RF_Value_Cnt=500;

		cntint=0;
		start_flag=0;
		IR_Key = (uint8_t)(RF_data&0x0000000f);
		
		
		if(uiLocalKey != IR_Key)
		{
			uiLocalKey = IR_Key;
			uiKeyPaseTime = 0;//按下按钮的时间计数器
			uiNewKeyFlg = 1;
		}

		uiKeyPaseTime++;//100ms

		Temp_addrl = (RF_data>>4)&0x000000ff; 
		Temp_addrh = (RF_data>>12)&0x000000ff;
		
		IR_OVER = 1;
  	}
	
}