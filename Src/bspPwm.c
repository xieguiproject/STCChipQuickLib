#include "bspPwm.h"

unsigned char SystemStatus = 0;
unsigned char SystemRunMoto = 1;
unsigned int OnTime = 100;
unsigned int OffTime = 10;
uint8_t dutyRates = 0;

PWM_InitTypeDef mdPWM_InitTypeDefs;

void Delay1ms()		//@11.0592MHz
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
void DelayMs(unsigned int time)
{
	while(time--)
	{
		Delay1ms();
	}
}
/*****************************************************************************
 * 函 数 名  : bspPwmInit
 * 负 责 人  : xiegui
 * 创建日期  : 2018年11月16日
 * 函数功能  : pwm模块初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspPwmGpioDefInit()
{
#if 0
	uint8_t datas = 0;
	GPIO_InitTypeDef GPIO_InitTypeDefs;
	memset(&GPIO_InitTypeDefs,0,sizeof(GPIO_InitTypeDef));

	
	GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
	PWM2 = 0;
	
	/*P2.7 设置为推完输出模式*/
	GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
	/*P3.7设置为退挽输出，其余为普通模式*/
	/*PWM1和PWM2是不能同时输出PWM的*/
	PWM1 = 0;
#endif
}
/*****************************************************************************
 * 函 数 名  : bspPwmPinSet
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月3日
 * 函数功能  : 设置PWM输出硬件功能
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspPwmPinSet(uint8_t uiPwmNum)
{
	#if 0
	GPIO_InitTypeDef GPIO_InitTypeDefs;
	memset(&GPIO_InitTypeDefs,0,sizeof(GPIO_InitTypeDef));
	
	switch(uiPwmNum)
	{
		case 1:
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
			/*设置PWM1为PWM模式,pwm2为普通IO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			
			GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
			PWM2 = 0;
			break;
		case 2:
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
			/*设置PWM1为PWM模式,pwm2为普通IO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Out_PP;
			
			GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
			PWM1 = 0;
			break;
		default:
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
			/*设置PWM1为PWM模式,pwm2为普通IO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			PWM1 = 0;
			PWM2 = 0;
			break;
	}
	#endif
}
#define CYCLE   0x550L     //定义PWM周期(最大值为32767)
#define DUTY    2L         //定义占空比为10%

void bspPwmConfigLockCmd(FunctionalState state)
{
	if(state == ENABLE)
	{
		P_SW2 |= 0x80;                  //使能访问XSFR
	}
	else
	{
		P_SW2 &= ~0x80;
	}
}
void bspSetPwmDutyRate(uint8_t uiDutyRate)
{
	bspPwmConfigLockCmd(ENABLE);                  //使能访问XSFR

	mdPWM_InitTypeDefs.fDutyRate = uiDutyRate;
	PWM2T2 = (mdPWM_InitTypeDefs.uiCycle * mdPWM_InitTypeDefs.fDutyRate) / 100;

	bspPwmConfigLockCmd(DISABLE);
}
void bspPwmConfig(uint8_t uiPwmNum,PWM_InitTypeDef *PWM_InitTypeDefs)
{
	uint8_t uiReg = 0;
	
	bspPwmConfigLockCmd(ENABLE);                  //使能访问XSFR
	
	PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
	
	PWMCKS = 0x00;                  //选择PWM的时钟为Fosc/(0+1)
	//选择时钟
	PWMC = PWM_InitTypeDefs->uiCycle;                   //设置PWM周期
	
	PWM2T1 = 0x0000;                //设置PWM2第1次反转的PWM计数
	
	PWM2T2 = (uint16_t)((PWM_InitTypeDefs->uiCycle * PWM_InitTypeDefs->fDutyRate) / 100);    //设置PWM2第2次反转的PWM计数
                                    //占空比为(PWM2T2-PWM2T1)/PWMC
    
  	if(PWM_InitTypeDefs->OutPinMode == PWM_Out_Pin_Mode0)
  	{
		PWM2CR = 0x00;                  //选择PWM2输出到P3.7,不使能PWM2中断
	}
	else
	{
		PWM2CR = 0x08;                  //选择PWM2输出到P2.7,不使能PWM2中断
	}
    
    bspPwmConfigLockCmd(DISABLE);
}
/*****************************************************************************
 * 函 数 名  : bspPwmInit
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月3日
 * 函数功能  : PWM初始化
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspPwmInit(uint8_t uiPwmNum,uint8_t uiPwmClk,uint8_t fDutyRate,uint16_t uiCycle)
{
	

	mdPWM_InitTypeDefs.PwmClk = uiPwmClk;
	mdPWM_InitTypeDefs.fDutyRate = fDutyRate;
	mdPWM_InitTypeDefs.uiCycle = uiCycle;
	switch(uiPwmNum)
	{
		case 1:
			mdPWM_InitTypeDefs.OutPinMode = PWM_Out_Pin_Mode0;//pwm1 P3.7 在第一组
			break;
		case 2:
			mdPWM_InitTypeDefs.OutPinMode = PWM_Out_Pin_Mode1;//pwm2 P2.7 在第2组
			break;
	}
	
	bspPwmConfig(uiPwmNum,&mdPWM_InitTypeDefs);
	/*配置时钟和模式等信息*/
	bspPwmCmd(ENABLE);
	/*使能PWM输出*/
}
/*****************************************************************************
 * 函 数 名  : bspPwmCmd
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月3日
 * 函数功能  : 使能PWM模块并开始输出PWM信号
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspPwmCmd(FunctionalState state)
{
#if 1
	if(state == ENABLE)
	{
		PWMCR = 0x01;                   //使能PWM信号输出
    	PWMCR |= 0x80;                  //使能PWM模块
	}
	else
	{
		PWMCR = 0x00;                   //使能PWM信号输出
	}
#endif
}
void CheckCmd()
{
	unsigned int uiLoop = 0;
	uint8_t uiDat = 0;
	char *Pointe = NULL;
	Pointe = strstr(mdUsarts.Usart1.UsartBuf,"SETDUTYRATE:");
	Delay1ms();
	
	if(NULL != Pointe)
	{
		Delay1ms();
		Delay1ms();
		uiDat = 50;//atoi(Pointe + 12);
		dutyRates = 10;
		
		logMsg(RM_RUN,"SetDutyRate:%d\r\n",dutyRates,0,0,0,0,0);
		BpsMotoCtrl(1,1,dutyRates);
		CleanBuff();
		return;
	}
	Pointe = strstr(mdUsarts.Usart1.UsartBuf,"SETCYCLE:");
	Delay1ms();
	if(NULL != Pointe)
	{
		uiDat = atoi(Pointe + 9);
		OffTime = uiDat;
		BpsMotoCtrl(1,1,uiDat);
		CleanBuff();
		return;
	}
	Pointe = strstr(mdUsarts.Usart1.UsartBuf,"STOPRUN");
	Delay1ms();
	if(NULL != Pointe)
	{
		BpsMotoCtrl(0,0,0);
		logMsg(RM_RUN,"Moto Stop Run\r\n",0,0,0,0,0,0);
		CleanBuff();
		return;
	}
	Pointe = strstr(mdUsarts.Usart1.UsartBuf,"MOTODIR:");
	Delay1ms();
	if(NULL != Pointe)
	{
		uiDat = atoi(Pointe + 8);
		logMsg(RM_RUN,"MOTODIR:%d\r\n",uiDat,0,0,0,0,0);
		if(uiDat == 0)
		{
			BpsMotoCtrl(0,1,dutyRates);
		}
		else
		{
			BpsMotoCtrl(1,1,dutyRates);
		}
		CleanBuff();
		return;
	}

}
/*****************************************************************************
 * 函 数 名  : BpsMotoCtrl
 * 负 责 人  : xiegui
 * 创建日期  : 2018年12月6日
 * 函数功能  : 电机运转控制
 * 输入参数  : int iDir  方向
 				uiMode:为0时刹车，为1时运行
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void BpsMotoCtrl(uint8_t iDir,uint8_t uiMode,float fDutyRate)
{
	/*配置根据方向设置PWM波，然后进行运转控制*/
	mdSysParm.uiRunable = uiMode;
	
	if(uiMode)
	{
		if(iDir)
		{
			PWM1 = 0;
			PWM2 = 0;
			bspPwmCmd(DISABLE);
			//DelayMs(10);
			bspPwmInit(2,PWM_Clock_SysClkDiv,fDutyRate,CYCLE);
			/*pwm1输出PWM波形，PWM2固定拉高即可控制正转*/
			PWM1 = 1;
			//选择PWM时钟信号
			
		}
		else
		{
			PWM1 = 0;
			PWM2 = 0;
			/*pwm2输出PWM波形，PWM1固定拉高即可控制正转*/
			bspPwmCmd(DISABLE);
			//DelayMs(10);
			//选择PWM时钟信号
			bspPwmInit(1,PWM_Clock_SysClkDiv,fDutyRate,CYCLE);
			PWM2 = 1;
		}
	}
	else
	{
		PWM1 = 0;
		PWM2 = 0;
		bspPwmCmd(DISABLE);
		//DelayMs(10);
	}
}

/*****************************************************************************
 * 函 数 名  : MotoSetPosition
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月13日
 * 函数功能  : 控制电机运转到指定 位置
 * 输入参数  : float fSetPositionCm  绝对恢
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void MotoSetPosition(float fSetPositionCm)
{  
	uint16_t uiDir = 0;
	uiDir = (uint16_t)mdSysParm.ImportantParms.fBigDir; //默认为0,修改这个变量即可修改电机方向
	if(mdSysParm.ImportantParms.fCenterCm < fSetPositionCm)  
	{   
		//开启电机正转
		mdSysParm.ImportantParms.fTagetCm = fSetPositionCm;
		//当前位置达到目标位置时会自动停止电机    
		mdSysParm.uiDirFromUser = 1;
		//SetSystemParmInfoToEpprom();//写入参数到flash中 
		BpsMotoCtrl(!uiDir,1,10);
	}  
	else if(mdSysParm.ImportantParms.fCenterCm > fSetPositionCm)  
	{    //开启电机反转;
		mdSysParm.uiDirFromUser = 0;
		mdSysParm.ImportantParms.fTagetCm = fSetPositionCm;//当前位置达到目标位置时会自动停止电机    
		//SetSystemParmInfoToEpprom();//写入参数     
		BpsMotoCtrl(uiDir,1,10);
	}
}


