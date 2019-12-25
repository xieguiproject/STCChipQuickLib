/***********************************************************************************
 * �� �� ��   : bspCCPInterrupt.c
 * �� �� ��   : xiegui
 * ��������   : 2019��1��6��
 * �ļ�����   : stc15��Ƭ��CCP  ��չ�ⲿ�ж�
 * ��Ȩ˵��   : Copyright (c) 2008-2019   xx xx xx xx �������޹�˾
 * ��    ��   : 
 * �޸���־   : 
***********************************************************************************/
#include "bspCCPInterrupt.h"
#include "bspUsart.h"
uint8_t uiIntFlg = 0;
uint8_t uiIntCount = 0;

//ccp�ж�
/*****************************************************************************
 * �� �� ��  : CCP0Interrupt
 * �� �� ��  : xiegui
 * ��������  : 2019��1��6��
 * ��������  : �ж���ڵ�ַ
                ������Ҫ��ȡ������ķ���ͼ���������ת�ĽǶ���Ϣ��
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/

void CCP0Interrupt() interrupt 7 using 1
{
    
	float  fTemp1 = 0;
    if(CCF0 == 1)
    {
        CCF0 = 0;
        //��һ���ж�ΪP3.5�������ж���ȻΪP3.5�����������󳬹�5�������P3.6�жϹ���
        if(uiIntFlg == 1)
        {
            //P3.6����
            if(uiIntCount >= 5)
            {
                uiIntCount = 0;
                mdSysParm.uiErrorCode = IntSensorError1;
                BpsMotoCtrl(0,0,0);
                BspUsartSendStr(1,"1Moto Only One Int\r\n");
            }
            else
            {
                uiIntCount++;
            }
        }
        else
        {
            uiIntCount = 0;
        }
        uiIntFlg  = 1;
        
    }
    else if(CCF1 == 1)
    {
        CCF1 = 0;
        if(uiIntFlg == 2)
        {
            if(uiIntCount >= 5)
            {
                uiCount = 0;
                mdSysParm.uiErrorCode = IntSensorError2;
                BpsMotoCtrl(0,0,0);
                BspUsartSendStr(1,"2Moto Only One Int\r\n");
            }
            else
            {
                uiIntCount++;
            }
        }
        else
        {
            uiCount = 0;
        }
        uiIntFlg = 2;
    }
    /*������� ���ת1Ȧ����Ӧ�����жϣ���һ���ж϶�Ӧ180��
            ��ת�ľ��� = �жϸ��� / ÿһȦ���жϸ��� / 
            һȦ���ܳ� / 360�������һ�ȶ�Ӧ�ľ���
   ������֤���ڲ�ת148Ȧ���ⲿת1Ȧ��        
    */
 #if 0
    fTemp1 = (1 / MotoIntNum * 360); 
    fTemp1 = fTemp1 * (Permimeter / 360.0) / RetardScale;
#else
	//Perimeter �ⲿ���תһȦ���ܳ� * 148 ��Ӧ �ⲿ1cm��Ӧ�ڲ��ƶ���
	//���ջ����һ���ж϶�Ӧ�ⲿת���ľ���
	fTemp1 = Perimeter / RetardScale / MotoIntNum;
#endif
            /*�����ת��λ��*/
    //���ݷ�����㵱ǰ��ת�ľ��룬�˷���Ϊ��ת�������û�����ķ������//Ĭ��Ϊ������
    if(mdSysParm.uiDirFromUser)
    {
        if(mdSysParm.ImportantParms.fCenterCm >= mdSysParm.ImportantParms.fTagetCm)
        {
            //��ǰ����ת�����Ѿ�����Ŀ���趨λ�ã�����Ҫֹͣ�����
            BpsMotoCtrl(0,0,0);
            //д�뵱ǰ��ת��λ�õ�FLASH�У��������ϵ����Ҫ�����趨����
            SystemParmFush();
        }
        else
        {
            if(mdSysParm.ImportantParms.fCenterCm < MAX_CM)
            {
                mdSysParm.ImportantParms.fCenterCm += fTemp1;
            }
            else
            {
                mdSysParm.ImportantParms.fCenterCm = MAX_CM;
            }
        }
    }
    else
    {
        //��ת
        if(mdSysParm.ImportantParms.fCenterCm <= mdSysParm.ImportantParms.fTagetCm)
        {
            //��ǰ����ת�����Ѿ�����Ŀ���趨λ�ã�����Ҫֹͣ�����
            BpsMotoCtrl(0,0,0);
            //д�뵱ǰ��ת��λ�õ�FLASH�У��������ϵ����Ҫ�����趨����
            SystemParmFush();
        }
        else
        {
            if(mdSysParm.ImportantParms.fCenterCm > MIN_CM)
            {
                mdSysParm.ImportantParms.fCenterCm -= fTemp1;
            }
            else
            {
                mdSysParm.ImportantParms.fCenterCm = MIN_CM;
            }
        }
    }
	
	
}

/*****************************************************************************
 * �� �� ��  : bspCCPInterruptInit
 * �� �� ��  : xiegui
 * ��������  : 2019��1��6��
 * ��������  : ��ʼ�� ��չ �ⲿ�ж�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void bspCCPInterruptInit()
{
    ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);
    ACC |= CCP_S0;
    P_SW1 = ACC;
    /*����CCP_S0 = 1 CCP_S1 = 0 ���Ű���P3.5 P3.6 ��Ϊ�ⲿ�ж�*/

    CCON = 0;

    CL = 0;
    CH = 0;
    CMOD = 0X00;//����ʱ��Դ����ֹ��ʱ������ж�

    CCAPM0 = 0X11;//P3.5�����ش���
    CCAPM1 = 0X11;//P3.6�����ش���
    
    CR =1;
}

