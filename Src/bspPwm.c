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
 * �� �� ��  : bspPwmInit
 * �� �� ��  : xiegui
 * ��������  : 2018��11��16��
 * ��������  : pwmģ���ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
	
	/*P2.7 ����Ϊ�������ģʽ*/
	GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
	
	GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
	/*P3.7����Ϊ�������������Ϊ��ͨģʽ*/
	/*PWM1��PWM2�ǲ���ͬʱ���PWM��*/
	PWM1 = 0;
#endif
}
/*****************************************************************************
 * �� �� ��  : bspPwmPinSet
 * �� �� ��  : xiegui
 * ��������  : 2019��1��3��
 * ��������  : ����PWM���Ӳ������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
			/*����PWM1ΪPWMģʽ,pwm2Ϊ��ͨIO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			
			GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
			PWM2 = 0;
			break;
		case 2:
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
			/*����PWM1ΪPWMģʽ,pwm2Ϊ��ͨIO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Out_PP;
			
			GPIO_Init(GPIO_P3,&GPIO_InitTypeDefs);
			PWM1 = 0;
			break;
		default:
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			GPIO_Init(GPIO_P2,&GPIO_InitTypeDefs);
			/*����PWM1ΪPWMģʽ,pwm2Ϊ��ͨIO*/
			GPIO_InitTypeDefs.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitTypeDefs.GPIO_Mode = GPIO_Mode_Standard_IO;
			PWM1 = 0;
			PWM2 = 0;
			break;
	}
	#endif
}
#define CYCLE   0x550L     //����PWM����(���ֵΪ32767)
#define DUTY    2L         //����ռ�ձ�Ϊ10%

void bspPwmConfigLockCmd(FunctionalState state)
{
	if(state == ENABLE)
	{
		P_SW2 |= 0x80;                  //ʹ�ܷ���XSFR
	}
	else
	{
		P_SW2 &= ~0x80;
	}
}
void bspSetPwmDutyRate(uint8_t uiDutyRate)
{
	bspPwmConfigLockCmd(ENABLE);                  //ʹ�ܷ���XSFR

	mdPWM_InitTypeDefs.fDutyRate = uiDutyRate;
	PWM2T2 = (mdPWM_InitTypeDefs.uiCycle * mdPWM_InitTypeDefs.fDutyRate) / 100;

	bspPwmConfigLockCmd(DISABLE);
}
void bspPwmConfig(uint8_t uiPwmNum,PWM_InitTypeDef *PWM_InitTypeDefs)
{
	uint8_t uiReg = 0;
	
	bspPwmConfigLockCmd(ENABLE);                  //ʹ�ܷ���XSFR
	
	PWMCFG = 0x00;                  //����PWM�������ʼ��ƽΪ�͵�ƽ
	
	PWMCKS = 0x00;                  //ѡ��PWM��ʱ��ΪFosc/(0+1)
	//ѡ��ʱ��
	PWMC = PWM_InitTypeDefs->uiCycle;                   //����PWM����
	
	PWM2T1 = 0x0000;                //����PWM2��1�η�ת��PWM����
	
	PWM2T2 = (uint16_t)((PWM_InitTypeDefs->uiCycle * PWM_InitTypeDefs->fDutyRate) / 100);    //����PWM2��2�η�ת��PWM����
                                    //ռ�ձ�Ϊ(PWM2T2-PWM2T1)/PWMC
    
  	if(PWM_InitTypeDefs->OutPinMode == PWM_Out_Pin_Mode0)
  	{
		PWM2CR = 0x00;                  //ѡ��PWM2�����P3.7,��ʹ��PWM2�ж�
	}
	else
	{
		PWM2CR = 0x08;                  //ѡ��PWM2�����P2.7,��ʹ��PWM2�ж�
	}
    
    bspPwmConfigLockCmd(DISABLE);
}
/*****************************************************************************
 * �� �� ��  : bspPwmInit
 * �� �� ��  : xiegui
 * ��������  : 2019��1��3��
 * ��������  : PWM��ʼ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void bspPwmInit(uint8_t uiPwmNum,uint8_t uiPwmClk,uint8_t fDutyRate,uint16_t uiCycle)
{
	

	mdPWM_InitTypeDefs.PwmClk = uiPwmClk;
	mdPWM_InitTypeDefs.fDutyRate = fDutyRate;
	mdPWM_InitTypeDefs.uiCycle = uiCycle;
	switch(uiPwmNum)
	{
		case 1:
			mdPWM_InitTypeDefs.OutPinMode = PWM_Out_Pin_Mode0;//pwm1 P3.7 �ڵ�һ��
			break;
		case 2:
			mdPWM_InitTypeDefs.OutPinMode = PWM_Out_Pin_Mode1;//pwm2 P2.7 �ڵ�2��
			break;
	}
	
	bspPwmConfig(uiPwmNum,&mdPWM_InitTypeDefs);
	/*����ʱ�Ӻ�ģʽ����Ϣ*/
	bspPwmCmd(ENABLE);
	/*ʹ��PWM���*/
}
/*****************************************************************************
 * �� �� ��  : bspPwmCmd
 * �� �� ��  : xiegui
 * ��������  : 2019��1��3��
 * ��������  : ʹ��PWMģ�鲢��ʼ���PWM�ź�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void bspPwmCmd(FunctionalState state)
{
#if 1
	if(state == ENABLE)
	{
		PWMCR = 0x01;                   //ʹ��PWM�ź����
    	PWMCR |= 0x80;                  //ʹ��PWMģ��
	}
	else
	{
		PWMCR = 0x00;                   //ʹ��PWM�ź����
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
 * �� �� ��  : BpsMotoCtrl
 * �� �� ��  : xiegui
 * ��������  : 2018��12��6��
 * ��������  : �����ת����
 * �������  : int iDir  ����
 				uiMode:Ϊ0ʱɲ����Ϊ1ʱ����
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void BpsMotoCtrl(uint8_t iDir,uint8_t uiMode,float fDutyRate)
{
	/*���ø��ݷ�������PWM����Ȼ�������ת����*/
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
			/*pwm1���PWM���Σ�PWM2�̶����߼��ɿ�����ת*/
			PWM1 = 1;
			//ѡ��PWMʱ���ź�
			
		}
		else
		{
			PWM1 = 0;
			PWM2 = 0;
			/*pwm2���PWM���Σ�PWM1�̶����߼��ɿ�����ת*/
			bspPwmCmd(DISABLE);
			//DelayMs(10);
			//ѡ��PWMʱ���ź�
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
 * �� �� ��  : MotoSetPosition
 * �� �� ��  : xiegui
 * ��������  : 2019��1��13��
 * ��������  : ���Ƶ����ת��ָ�� λ��
 * �������  : float fSetPositionCm  ���Ի�
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void MotoSetPosition(float fSetPositionCm)
{  
	uint16_t uiDir = 0;
	uiDir = (uint16_t)mdSysParm.ImportantParms.fBigDir; //Ĭ��Ϊ0,�޸�������������޸ĵ������
	if(mdSysParm.ImportantParms.fCenterCm < fSetPositionCm)  
	{   
		//���������ת
		mdSysParm.ImportantParms.fTagetCm = fSetPositionCm;
		//��ǰλ�ôﵽĿ��λ��ʱ���Զ�ֹͣ���    
		mdSysParm.uiDirFromUser = 1;
		//SetSystemParmInfoToEpprom();//д�������flash�� 
		BpsMotoCtrl(!uiDir,1,10);
	}  
	else if(mdSysParm.ImportantParms.fCenterCm > fSetPositionCm)  
	{    //���������ת;
		mdSysParm.uiDirFromUser = 0;
		mdSysParm.ImportantParms.fTagetCm = fSetPositionCm;//��ǰλ�ôﵽĿ��λ��ʱ���Զ�ֹͣ���    
		//SetSystemParmInfoToEpprom();//д�����     
		BpsMotoCtrl(uiDir,1,10);
	}
}


