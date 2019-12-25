/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, XXXXX �������޹�˾                  

 ******************************************************************************
  �� �� ��   : bspEspAtWifi.c
  �� �� ��   : ����
  ��    ��   : Gavinx
  ��������   : 2019��4��3�� ������
  ����޸�   :
  ��������   : ESP8266WIFIģ�飬ATָ���������WIFIģ��
  �����б�   :
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
  �޸���ʷ   :
  1.��    ��   : 2019��4��3�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "bspEspAtWifi.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
	
#ifdef STC_15WXX || STC_15FXX || STC_89CXX
	EspAtWifi xdata mdEspAtWifi;
#else
	EspAtWifi  mdEspAtWifi;
#endif

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/


/*****************************************************************************
 �� �� ��  : bspEspAtWifiInit
 ��������  : ģʽ��ʼ��,��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2019��4��3�� ������
    ��    ��   : Gavinx
    �޸�����   : �����ɺ���

*****************************************************************************/
void bspEspAtWifiInit()
{
    uint8_t uiTryCount = 0;
    uint8_t uiTryTotalCount = 0;
	
    BspUsartInit(2,115200);
	Timer3Init();//��ʱ����ʼ�� 50ms
	
    mdEspAtWifi.usart = WITI_BIND_USART;
    
    logMsg(RM_RUN,"Wifi Mode Begin Init\r\n",0,0,0,0,0,0);
EspModeInit:
    
    while(bspEspAtWifiTest())//���ģ���Ƿ��ܿ��ƣ�����������������
    {
        bspEspAtWifiQuitTrans();
        bspEspAtWifiSendCmd("AT+CIPMODE=0","OK",NULL,20);
        DelayMs(1000);
        uiTryCount++;
        if(uiTryCount > 5)
        {
            logMsg(RM_RUN,"Wifi Mode Will Reboot\r\n",0,0,0,0,0,0);
            bspEspAtWifiSoftRest();//�����λ�������λ����Ȼ�������������wifi���ƹ���
            DelayMs(1000);
            DelayMs(1000);
            uiTryCount = 0;
			uiTryTotalCount++;
			if(uiTryTotalCount > 5)
			{
				mdEspAtWifi.uiWifiNetStates = NoWifiNode;//�޷�ʶ��wifiģ��
			}
            goto EspModeInit;
        }
    }
		
    logMsg(RM_RUN,"Wifi Mode Is OnLine\r\n",0,0,0,0,0,0);
    /*�رջ���ģʽ*/
    while(bspEspAtWifiSendCmd("ATE0","OK",NULL,50));
    
    bspEspAtWifiSetWorkMode(Station);//Stationģʽ
    bspEspAtWifiSoftRest();//�����λ

#ifndef DEBUG_WIFI_DB
    bspEspAtWifiConnectWifi("Xiaomi_1F14","11111111");

    logMsg(RM_RUN,"Wifi Connect Is OnLine\r\n",0,0,0,0,0,0);
    bspEspAtWifiTcpMux(0);//*����Ϊ������*/

	
    bspEspAtWifiConnectServer("192.168.31.212","8081");
    logMsg(RM_RUN,"Server Is Connnect\r\n",0,0,0,0,0,0);
    //����͸��ģʽ
    bspEspAtWifiTransBeginSend();//���봫��ģʽ
    bspEspAtWifiTransMode();
	OpenLed(LED2);
#endif
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiCleanRecvBuf
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ������ܻ���
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiCleanRecvBuf()
{
    memset(mdEspAtWifi.usart->UsartBuf,0,sizeof(mdEspAtWifi.usart->UsartBuf));
    mdEspAtWifi.usart->UsartCount = 0;
    mdEspAtWifi.usart->UsartFlage = 0;
    return True;
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiSendCmd
 * �� �� ��  : xiegui
 * ��������  : 2019��1��20��
 * ��������  : ���������������ֵ,�û�����ֲʱֻ��Ҫ��ֲ����ؼ��ӿھͿ����ˡ�
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
            //������ܵ������ݣ�
            if(mdEspAtWifi.usart->UsartFlage & USART_RECV_OVER)
            {
                mdEspAtWifi.usart->UsartBuf[mdEspAtWifi.usart->UsartCount] = 0;//����ַ������͵�ǿ�ƽ�����
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
        //��ʱ�˳�
    }
	else if(waittime)
	{
		while(--waittime)
        {
            DelayMs(10);
            //������ܵ������ݣ�
            if(mdEspAtWifi.usart->UsartFlage & USART_RECV_OVER)
            {
            	mdEspAtWifi.usart->UsartBuf[mdEspAtWifi.usart->UsartCount] = 0;//����ַ������͵�ǿ�ƽ�����
               	return cb();
                break;
            }
			
			mdEspAtWifi.usart->UsartCount = 0;
			mdEspAtWifi.usart->UsartFlage = 0;
        }
        if(waittime == 0)
            res = False;
        //��ʱ�˳�
	}
	CloseLed(LED2);	
    return res;
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiSoftRest
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : �����λ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiSoftRest()
{
    return bspEspAtWifiSendCmd("AT+RST","OK",NULL,50);
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiHardwareRest
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : Ӳ������
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiHardwareRest()
{
    return True;
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiTest
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ����ģ���Ƿ��ܿ���
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiTest()
{
    return bspEspAtWifiSendCmd("AT","OK",NULL,30);
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiQuitTrans
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : �˳�����ģʽ
 * �������  : ��
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiQuitTrans()
{
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    BspUsartSendByte(mdEspAtWifi.usart->uiSerialNum,'+');
    
    DelayMs(1000);
    
    return bspEspAtWifiSendCmd("AT","OK",NULL,50);
}
//����͸��ģʽ
int8_t bspEspAtWifiTransMode()
{
	char xdata CmdBuf[50];
	sprintf((char*)CmdBuf,"AT+CIPSEND");
	
	return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,800);
}
//����͸��
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
			mdEspAtWifi.uiWifiNetStates = WifiDisconnect;//wifi����ʧ��
		}
	}
    
    return 1;
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiConnectServer
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ����tcp��ָ��������
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiConnectServer(uint8_t *ServerIp,uint8_t *Port)
{
    char xdata CmdBuf[50] = {0};
    sprintf((char*)CmdBuf,"AT+CIPSTART=\"TCP\",\"%s\",%s",ServerIp,(uint8_t*)Port);    //����Ŀ��TCP������

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
 * �� �� ��  : bspEspAtWifiCheckConnectCb
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ���ܵ����ݻص��������ʺ��ڴ����д������ݷ��صĹ��̡�
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
 * �� �� ��  : bspEspAtWifiCheckConnectSeverState
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ���WiFiģ��tcp����״̬
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiCheckConnectSeverState()
{
	uint8_t ucLoop = 5;
	char xdata CmdBuf[50] = {0};
	//bspEspAtWifiCleanRecvBuf();
	
    sprintf((char*)CmdBuf,"AT+CIPSTATUS");    //����Ŀ��TCP������
 	
	return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,NULL,bspEspAtWifiCheckConnectCb,500);
}
/*****************************************************************************
 * �� �� ��  : bspEspAtWifiTcpMux
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : �����ӺͶ������л�
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
//��ѯ��ǰ������WiFi�ź�
int8_t bspEspAtWifiListWifiAp()
{
  char xdata CmdBuf[50] = {0};
	
  sprintf((char*)CmdBuf,"AT+CWLAP");    //��ѯwifi
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
				ucFlg = 1;//�д��󣬼�����ѯ
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
 * �� �� ��  : bspEspAtWifiRecvData
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ��͸��ģʽ�µ����ݽ���
 * �������  : int8_t Mode  
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiRecvData(uint8_t WaitPort,uint8_t *RecvBuf,uint16_t RecvDatLen,uint16_t TimeOut)
{
    char *IpdStr = NULL;
    char *IpdStr1 = NULL;
    uint16_t  RecvDatNum = 0;
    /*�����ַ�����*/
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
                        memcpy(RecvBuf,IpdStr1,RecvDatNum);/*��������*/
                        bspEspAtWifiCleanRecvBuf();//���������
                        return RecvDatNum;
                    }
                    else
                    {
                        memcpy(RecvBuf,IpdStr1,RecvDatLen);/*��������*/
                        bspEspAtWifiCleanRecvBuf();//���������
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
 * �� �� ��  : bspEspAtWifiSetWorkMode
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ���ù���ģʽ
 * �������  : int8_t Mode  
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

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
 * �� �� ��  : bspEspAtWifiCreateFreeWifiAp
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : �����ӺͶ������л�
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspEspAtWifiCreateFreeWifiAp()
{
	char xdata CmdBuf[50] = {0};
    
    sprintf(CmdBuf,"AT+CWSAP=\"SmartWindows\",\"SmartWindows\",10,0");
    
    return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,50);
}
/*����udp�㲥�źţ�*/
int8_t bspEspWifiConnectUdpServer()
{
	char xdata CmdBuf[50] = {0};
    
    sprintf(CmdBuf,"AT+CIPSTART=\"UDP\",\"255.255.255.255\",6000,1000,0");
	
    return bspEspAtWifiSendCmd((uint8_t *)CmdBuf,"OK",NULL,80);
}
/*****************************************************************************
 * �� �� ��  : bspCfgWifiInfo
 * �� �� ��  : xiegui
 * ��������  : 2019��1��29��
 * ��������  : ����wifi
 * �������  : int8_t Mode  
                1��������
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
int8_t bspCfgWifiInfo()
{
    //1�����ģ���Ƿ�����
    uint8_t uiTryCount = 0;
		BspUsartInit(2,9600);
    mdEspAtWifi.usart = WITI_BIND_USART;
    
    logMsg(RM_RUN,"Wifi Mode Begin Init\r\n",0,0,0,0,0,0);
EspModeInit:
    
   	while(bspEspAtWifiTest())//���ģ���Ƿ��ܿ��ƣ�����������������
    {
        bspEspAtWifiQuitTrans();
        bspEspAtWifiSendCmd("AT+CIPMODE=0","OK",NULL,20);
        DelayMs(1000);
        uiTryCount++;
        if(uiTryCount > 5)
        {
            logMsg(RM_RUN,"Wifi Mode Will Reboot\r\n",0,0,0,0,0,0);
            bspEspAtWifiSoftRest();//�����λ�������λ����Ȼ�������������wifi���ƹ���
            DelayMs(1000);
            DelayMs(1000);
            DelayMs(1000);
            DelayMs(1000);
            uiTryCount = 0;
            goto EspModeInit;
        }
    }
    logMsg(RM_RUN,"Wifi Mode Is OnLine\r\n",0,0,0,0,0,0);
    //2������wifi����ģʽ
    /*�رջ���ģʽ*/
    while(bspEspAtWifiSendCmd("ATE0","OK",NULL,50));
    
    bspEspAtWifiSetWorkMode(AP);//APģʽ
    bspEspAtWifiSoftRest();//�����λ
    DelayMs(1000);
    
    //bspEspAtWifiCleanRecvBuf();
	bspEspAtWifiTcpMux(0);
    //3������wifi
    bspEspAtWifiCreateFreeWifiAp();
	DelayMs(1000);
	DelayMs(1000);
    //4�����ܹ㲥�ź�
    while(bspEspWifiConnectUdpServer());
    //5���洢wifi�˻�������
    
    //6������ϵͳ��������������wifi��
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
