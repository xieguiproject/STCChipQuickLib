/***********************************************************************************
 * 文 件 名   : bspCCPInterrupt.c
 * 负 责 人   : xiegui
 * 创建日期   : 2019年1月6日
 * 文件描述   : stc15单片机CCP  扩展外部中断
 * 版权说明   : Copyright (c) 2008-2019   xx xx xx xx 技术有限公司
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/
#include "bspCCPInterrupt.h"
#include "bspUsart.h"
uint8_t uiIntFlg = 0;
uint8_t uiIntCount = 0;

//ccp中断
/*****************************************************************************
 * 函 数 名  : CCP0Interrupt
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月6日
 * 函数功能  : 中断入口地址
                从中需要获取出电机的方向和计算出电机运转的角度信息。
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/

void CCP0Interrupt() interrupt 7 using 1
{
    
	float  fTemp1 = 0;
    if(CCF0 == 1)
    {
        CCF0 = 0;
        //上一个中断为P3.5，本次中断依然为P3.5，这样的现象超过5次则代表P3.6中断故障
        if(uiIntFlg == 1)
        {
            //P3.6故障
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
    /*计算距离 电机转1圈，对应两个中断，则一个中断对应180度
            运转的距离 = 中断个数 / 每一圈的中断个数 / 
            一圈的周长 / 360度则代表一度对应的距离
   经过验证，内部转148圈，外部转1圈。        
    */
 #if 0
    fTemp1 = (1 / MotoIntNum * 360); 
    fTemp1 = fTemp1 * (Permimeter / 360.0) / RetardScale;
#else
	//Perimeter 外部电机转一圈的周长 * 148 对应 外部1cm对应内部移动了
	//最终换算出一个中断对应外部转动的距离
	fTemp1 = Perimeter / RetardScale / MotoIntNum;
#endif
            /*电机运转的位移*/
    //根据方向计算当前运转的距离，此方向为正转，根据用户定义的方向计算//默认为正方向
    if(mdSysParm.uiDirFromUser)
    {
        if(mdSysParm.ImportantParms.fCenterCm >= mdSysParm.ImportantParms.fTagetCm)
        {
            //当前的运转距离已经到达目标设定位置，则需要停止电机。
            BpsMotoCtrl(0,0,0);
            //写入当前运转的位置到FLASH中，以免电机断电后需要重新设定参数
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
        //反转
        if(mdSysParm.ImportantParms.fCenterCm <= mdSysParm.ImportantParms.fTagetCm)
        {
            //当前的运转距离已经到达目标设定位置，则需要停止电机。
            BpsMotoCtrl(0,0,0);
            //写入当前运转的位置到FLASH中，以免电机断电后需要重新设定参数
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
 * 函 数 名  : bspCCPInterruptInit
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月6日
 * 函数功能  : 初始化 扩展 外部中断
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
void bspCCPInterruptInit()
{
    ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);
    ACC |= CCP_S0;
    P_SW1 = ACC;
    /*设置CCP_S0 = 1 CCP_S1 = 0 引脚绑定再P3.5 P3.6 作为外部中断*/

    CCON = 0;

    CL = 0;
    CH = 0;
    CMOD = 0X00;//设置时钟源，静止定时器溢出中断

    CCAPM0 = 0X11;//P3.5上升沿触发
    CCAPM1 = 0X11;//P3.6上升沿触发
    
    CR =1;
}

