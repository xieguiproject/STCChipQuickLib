/******************************************************************************

                  版权所有 (C), 2001-2011, XXXXX 技术有限公司                  

 ******************************************************************************
  文 件 名   : bspEspAtWifi.c
  版 本 号   : 初稿
  作    者   : Gavinx
  生成日期   : 2019年4月3日 星期三
  最近修改   :
  功能描述   : ESP8266WIFI模块，AT指令控制类型WIFI模块
  函数列表   :
              bspCfgWifiInfo
              bspEspAtWifiCheckConnectCb
              bspEspAtWifiCheckConnectSeverState
              bspEspAtWifiCleanRecvBuf
              bspEspAtWifiConnectServer
              bspEspAtWifiConnectWifi
              bspEspAtWifiCreateFreeWifiAp
              bspEspAtWifiFindStr
              bspEspAtWifiHardwareRest
              bspEspAtWifiInit
              bspEspAtWifiListWifiAp
              bspEspAtWifiQuitTrans
              bspEspAtWifiRecvData
              bspEspAtWifiSendCmd
              bspEspAtWifiSetWorkMode
              bspEspAtWifiSoftRest
              bspEspAtWifiTcpMux
              bspEspAtWifiTest
              bspEspAtWifiTransBeginSend
              bspEspAtWifiTransMode
              bspEspWifiConnectUdpServer
              WifiTest
  修改历史   :
  1.日    期   : 2019年4月3日 星期三
    作    者   : Gavinx
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "bspEspAtWifi.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
	
#ifdef STC_15WXX || STC_15FXX || STC_89CXX
	EspAtWifi xdata mdEspAtWifi;
#else
	EspAtWifi  mdEspAtWifi;
#endif

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/


/*****************************************************************************
 函 数 名  : bspEspAtWifiInit
 功能描述  : 模式初始化,阻塞调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2019年4月3日 星期三
    作    者   : Gavinx
    修改内容   : 新生成函数

*****************************************************************************/
void bspEspAtWifiInit()
{
    uint8_t uiTryCount = 0;
    uint8_t uiTryTotalCount = 0;
	
    BspUsartInit(2,115200);
	Timer3Init();//定时器初始化 50ms
	
    mdEspAtWifi.usart = WITI_BIND_USART;
    
    logMsg(RM_RUN,"Wifi Mode Begin Init\r\n",0,0,0,0,0,0);
EspModeInit:
    
    while(bspEspAtWifiTest())//检测模块是否受控制，如果不是则进行重启
    {
        bspEspAtWifiQuitTrans();
        bspEspAtWifiSendCmd("AT+CIPMODE=0","OK",NULL,20);
        DelayMs(1000);
        uiTryCount++;
        if(uiTryCount > 5)
        {
            logMsg(RM_RUN,"Wifi Mode Will Reboot\r\n",0,0,0,0,0,0);
            bspEspAtWifiSoftRest();//软件复位，软件复位后依然不能连接则放弃wifi控制功能
            DelayMs(1000);
            DelayMs(1000);
            uiTryCount = 0;
			uiTryTotalCount++;
			if(uiTryTotalCount > 5)
			{
				mdEspAtWifi.uiWifiNetStates = NoWifiNode;//无法识别wifi模块
			}
            goto EspModeInit;
        }
    }
		
    logMsg(RM_RUN,"Wifi Mode Is OnLine\r\n",0,0,0,0,0,0);
    /*关闭回显模式*/
    while(bspEspAtWifiSendCmd("ATE0","OK",NULL,50));
    
    bspEspAtWifiSetWorkMode(Station);//Station模式
    bspEspAtWifiSoftRest();//软件复位

#ifndef DEBUG_WIFI_DB
    bspEspAtWifiConnectWifi("Xiaomi_1F14","11111111");

    logMsg(RM_RUN,"Wifi Connect Is OnLine\r\n",0,0,0,0,0,0);
    bspEspAtWifiTcpMux(0);//*设置为单连接*/

	
    bspEspAtWifiConnectServer("192.168.31.212","8081");
    logMsg(RM_RUN,"Server Is Connnect\r\n",0,0,0,0,0,0);
    //进入透传模式
    bspEspAtWifiTransBeginSend();//进入传输模式
    bspEspAtWifiTransMode();
	OpenLed(LED2);
#endif
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiCleanRecvBuf
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 清除接受缓存
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiCleanRecvBuf()
{
    memset(mdEspAtWifi.usart->UsartBuf,0,sizeof(mdEspAtWifi.usart->UsartBuf));
    mdEspAtWifi.usart->UsartCount = 0;
    mdEspAtWifi.usart->UsartFlage = 0;
    return True;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiSendCmd
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月20日
 * 函数功能  : 发送命令并监听返回值,用户再移植时只需要移植这个关键接口就可以了。
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiSendCmd(uint8_t *cmd,uint8_t *ack,AtCmdCbFunc cb,uint16_t waittime)
{
    uint8_t xdata CmdBuf[128] = {0};
    uint8_t res = True;
    char *Poite = NULL;
    OpenLed(LED2);
    memset(CmdBuf,0,sizeof(CmdBuf));
    bspEspAtWifiCleanRecvBuf();
    mdEspAtWifi.usart->UsartCount = 0;
	mdEspAtWifi.usart->UsartFlage = 0;
		
    sprintf(CmdBuf,"%s\r\n",cmd);
    BspUsartSendStr(mdEspAtWifi.usart->uiSerialNum,CmdBuf);
    DelayMs(50);
    if(ack && waittime)
    {
        while(--waittime)
        {
            DelayMs(10);
            //如果接受到新数据，
            if(mdEspAtWifi.usart->UsartFlage & USART_RECV_OVER)
            {
                mdEspAtWifi.usart->UsartBuf[mdEspAtWifi.usart->UsartCount] = 0;//添加字符串类型的强制结束符
                if((Poite = strstr(mdEspAtWifi.usart->UsartBuf,ack)) != NULL)
                {
										printf("ack:%s\r\n",(uint8_t*)Poite);
                    break;
                }
								mdEspAtWifi.usart->UsartCount = 0;
								mdEspAtWifi.usart->UsartFlage = 0;
            }
        }
        if(waittime == 0)
            res = False;
        //超时退出
    }
	else if(waittime)
	{
		while(--waittime)
        {
            DelayMs(10);
            //如果接受到新数据，
            if(mdEspAtWifi.usart->UsartFlage & USART_RECV_OVER)
            {
            	mdEspAtWifi.usart->UsartBuf[mdEspAtWifi.usart->UsartCount] = 0;//添加字符串类型的强制结束符
               	return cb();
                break;
            }
			
			mdEspAtWifi.usart->UsartCount = 0;
			mdEspAtWifi.usart->UsartFlage = 0;
        }
        if(waittime == 0)
            res = False;
        //超时退出
	}
	CloseLed(LED2);	
    return res;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiSoftRest
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 软件复位
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiSoftRest()
{
    return bspEspAtWifiSendCmd("AT+RST","OK",NULL,50);
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiHardwareRest
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 硬件重启
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiHardwareRest()
{
    return True;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiTest
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 测试模块是否受控制
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiTest()
{
    return bspEspAtWifiSendCmd("AT","OK",NULL,30);
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiQuitTrans
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 退出传输模式
 * 输入参数  : 无
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiQuitTrans()
{
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    
    DelayMs(1000);
    
    return bspEspAtWifiSendCmd("AT","OK",NULL,50);
}
//进入透传模式
int8_t bspEspAtWifiTransMode()
{
	char xdata CmdBuf[50];
	sprintf((char*)CmdBuf,"AT+CIPSEND");
	
	return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,800);
}
//开发透传
int8_t bspEspAtWifiTransBeginSend()
{
	char xdata CmdBuf[50];
	sprintf((char*)CmdBuf,"AT+CIPMODE=1");
	
	return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,">",NULL,800);
}
int8_t bspEspAtWifiConnectWifi(uint8_t *WifiName,uint8_t *Password)
{
    char xdata CmdBuf[50];
	uint8_t uiTryCount = 0;
    sprintf((char*)CmdBuf,"AT+CWJAP=\"%s\",\"%s\"",WifiName,Password);
    
    while(bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"WIFI GOT IP",NULL,1200))
	{
		uiTryCount++;
		DelayMs(1000);
		if(uiTryCount > 20)
		{
			break;
			mdEspAtWifi.uiWifiNetStates = WifiDisconnect;//wifi连接失败
		}
	}
    
    return 1;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiConnectServer
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 连接tcp到指定服务器
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiConnectServer(uint8_t *ServerIp,uint8_t *Port)
{
    char xdata CmdBuf[50] = {0};
    sprintf((char*)CmdBuf,"AT+CIPSTART=\"TCP\",\"%s\",%s",ServerIp,(uint8_t*)Port);    //配置目标TCP服务器

    while(bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,800))
    {
    	if(strstr(mdEspAtWifi.usart->UsartBuf,"ALREADY CONNECTED")!= NULL)
        {
						mdEspAtWifi.uiWifiNetStates = ServerConnectOk;
					logMsg(RM_RUN,"Server Reconnected\r\n",0,0,0,0,0,0);
					break;
        }
    	mdEspAtWifi.uiWifiNetStates |= ServerConnectError;
        logMsg(RM_RUN,"Server Connect Error\r\n",0,0,0,0,0,0);
        DelayMs(1000);
        logMsg(RM_RUN,"Server Reconnect Ing\r\n",0,0,0,0,0,0);
		mdEspAtWifi.uiWifiNetStates |= ServerConnecting;
    }   
    return 1;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiCheckConnectCb
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 接受到数据回调函数，适合于处理有大量数据返回的过程。
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiCheckConnectCb(void)
{
	char *Poite = NULL;
	
	if(strstr(mdEspAtWifi.usart->UsartBuf,"STATUS:3") != NULL)
    {
        return  3;
    }
	else if(strstr(mdEspAtWifi.usart->UsartBuf,"STATUS:4") != NULL)
	{
		return 4;
	}
	else if(strstr(mdEspAtWifi.usart->UsartBuf,"STATUS:2") != NULL)
	{
		return 2;
	}
	else
	{
		return False;
	}
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiCheckConnectSeverState
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 检测WiFi模块tcp连接状态
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiCheckConnectSeverState()
{
	uint8_t ucLoop = 5;
	char xdata CmdBuf[50] = {0};
	//bspEspAtWifiCleanRecvBuf();
	
    sprintf((char*)CmdBuf,"AT+CIPSTATUS");    //配置目标TCP服务器
 	
	return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,NULL,bspEspAtWifiCheckConnectCb,500);
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiTcpMux
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 单连接和多连接切换
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t  bspEspAtWifiTcpMux(uint16_t Mode)
{
    uint8_t xdata CmdBuf[30] = {0};
#if 0
    if(Mode == 0)
    {
    	sprintf(CmdBuf,"AT+CIPMUX=0");
    }
	else if(Mode == 1)
	{
		sprintf(CmdBuf,"AT+CIPMUX=1");
	}
#else
	sprintf(CmdBuf,"AT+CIPMUX=%d",Mode);
	printf("CmdBuf:%s\r\n",CmdBuf);
#endif
    while(bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,500))
    {
		 DelayMs(500);
		 return True;
	}
	return False;
}
int8_t bspEspAtWifiListWifiApCb(void)
{
	char *Pointe = NULL;
	char *Pointe2 = NULL;
	uint16_t uiLoop = 0;
	uint16_t uiCount = 0;
	for(uiLoop = 0;uiLoop < RECV_MAX_LEN;uiLoop++)
	{
		Pointe = bspEspAtWifiFindStr(mdEspAtWifi.usart->UsartBuf + uiLoop,"+CWLAP:");
		if(Pointe != NULL)
		{
			Pointe2= strstr(Pointe,")");
			*(Pointe2 + 1) = 0;
			printf("%s\r\n",Pointe);
			uiLoop += strlen(Pointe);
		}
		else
		{
			uiLoop += 1;
		}
	}
}
//查询当前环境的WiFi信号
int8_t bspEspAtWifiListWifiAp()
{
  char xdata CmdBuf[50] = {0};
	
  sprintf((char*)CmdBuf,"AT+CWLAP");    //查询wifi
 // usartflg = 1;
  bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,400);
  //usartflg = 0;
  bspEspAtWifiListWifiApCb();
}
char * bspEspAtWifiFindStr(char *String,char *cFindString)
{
	char *Pointe = cFindString;
	uint8_t ucFlg = 0;
	uint16_t uiLoop = 0;
	uint16_t uiJoop = 0;
	for(uiLoop = 0;uiLoop < RECV_MAX_LEN;uiLoop++)
	{
		ucFlg = 0;
		uiJoop = 0;
		Pointe = cFindString;
		while(*Pointe != '\0')
		{
			if(String[uiLoop + uiJoop] != *Pointe)
			{
				ucFlg = 1;//有错误，继续查询
				break;
			}
			uiJoop++;
			Pointe++;
		}
		if(ucFlg != 1)
		{
			return (char *)&String[uiLoop];
		}	
	}
	return NULL;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiRecvData
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 非透传模式下的数据接受
 * 输入参数  : int8_t Mode  
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiRecvData(uint8_t WaitPort,uint8_t *RecvBuf,uint16_t RecvDatLen,uint16_t TimeOut)
{
    char *IpdStr = NULL;
    char *IpdStr1 = NULL;
    uint16_t  RecvDatNum = 0;
    /*接受字符个数*/
    uint8_t Temp[4] = {0};
    uint8_t RecvDatPort = 0;
    while(TimeOut--)
    {
        IpdStr = bspEspAtWifiFindStr(mdEspAtWifi.usart->UsartBuf,"+IPD,");
        if(IpdStr != NULL)
        {
        	IpdStr += 5;
            IpdStr1 = strstr(IpdStr,":");
            if(IpdStr1 != NULL)
            {
                memcpy(Temp,IpdStr,(IpdStr1 - IpdStr));
                RecvDatNum = atoi(Temp);
                    
                IpdStr1+=1;
                memset(RecvBuf,0,RecvDatLen);
                if(RecvDatNum > 0)
                {
                    printf("DATA:%d %s\r\n",RecvDatNum,IpdStr1);
                    if(RecvDatNum <= RecvDatLen)
                    {
                        memcpy(RecvBuf,IpdStr1,RecvDatNum);/*拷贝数据*/
                        bspEspAtWifiCleanRecvBuf();//清除缓存区
                        return RecvDatNum;
                    }
                    else
                    {
                        memcpy(RecvBuf,IpdStr1,RecvDatLen);/*拷贝数据*/
                        bspEspAtWifiCleanRecvBuf();//清除缓存区
                        return RecvDatLen;
                    }
                }
            }
        }
        DelayMs(1);
    }
    return 0;
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiSetWorkMode
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 设置工作模式
 * 输入参数  : int8_t Mode  
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiSetWorkMode(uint16_t Mode)
{

    char xdata CmdBuf[30] = {0};
#if 0
    if(Mode == 1)
    {
		sprintf(CmdBuf,"AT+CWMODE=1");
	}
	else if(Mode == 2)
	{
		sprintf(CmdBuf,"AT+CWMODE=2");
	}
	else if(Mode == 3)
	{
		sprintf(CmdBuf,"AT+CWMODE=3");
	}
#else
	sprintf(CmdBuf,"AT+CWMODE=%d",Mode);
#endif
    return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,50);
}
/*****************************************************************************
 * 函 数 名  : bspEspAtWifiCreateFreeWifiAp
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 单连接和多连接切换
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspEspAtWifiCreateFreeWifiAp()
{
	char xdata CmdBuf[50] = {0};
    
    sprintf(CmdBuf,"AT+CWSAP=\"SmartWindows\",\"SmartWindows\",10,0");
    
    return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,50);
}
/*监听udp广播信号，*/
int8_t bspEspWifiConnectUdpServer()
{
	char xdata CmdBuf[50] = {0};
    
    sprintf(CmdBuf,"AT+CIPSTART=\"UDP\",\"255.255.255.255\",6000,1000,0");
	
    return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,80);
}
/*****************************************************************************
 * 函 数 名  : bspCfgWifiInfo
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月29日
 * 函数功能  : 配置wifi
 * 输入参数  : int8_t Mode  
                1：单连接
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

*****************************************************************************/
int8_t bspCfgWifiInfo()
{
    //1、检测模块是否在线
    uint8_t uiTryCount = 0;
		BspUsartInit(2,9600);
    mdEspAtWifi.usart = WITI_BIND_USART;
    
    logMsg(RM_RUN,"Wifi Mode Begin Init\r\n",0,0,0,0,0,0);
EspModeInit:
    
   	while(bspEspAtWifiTest())//检测模块是否受控制，如果不是则进行重启
    {
        bspEspAtWifiQuitTrans();
        bspEspAtWifiSendCmd("AT+CIPMODE=0","OK",NULL,20);
        DelayMs(1000);
        uiTryCount++;
        if(uiTryCount > 5)
        {
            logMsg(RM_RUN,"Wifi Mode Will Reboot\r\n",0,0,0,0,0,0);
            bspEspAtWifiSoftRest();//软件复位，软件复位后依然不能连接则放弃wifi控制功能
            DelayMs(1000);
            DelayMs(1000);
            DelayMs(1000);
            DelayMs(1000);
            uiTryCount = 0;
            goto EspModeInit;
        }
    }
    logMsg(RM_RUN,"Wifi Mode Is OnLine\r\n",0,0,0,0,0,0);
    //2、配置wifi工作模式
    /*关闭回显模式*/
    while(bspEspAtWifiSendCmd("ATE0","OK",NULL,50));
    
    bspEspAtWifiSetWorkMode(AP);//AP模式
    bspEspAtWifiSoftRest();//软件复位
    DelayMs(1000);
    
    //bspEspAtWifiCleanRecvBuf();
	bspEspAtWifiTcpMux(0);
    //3、发射wifi
    bspEspAtWifiCreateFreeWifiAp();
	DelayMs(1000);
	DelayMs(1000);
    //4、接受广播信号
    while(bspEspWifiConnectUdpServer());
    //5、存储wifi账户和密码
    
    //6、重启系统（或者重新连接wifi）
    return true;
}

void WifiTest()
{
	#if 0
		if(bspEspAtWifiCheckConnectSeverState() != 3)
		{
			printf("Server Disconnect!\r\n");
		}
		else
		{
			printf("Server Connect! \r\n");
		}
		DelayMs(5000);
#endif
}
