#ifndef BSP_AT_H
#define BSP_AT_H

#include "bspUsart.h"
#include "bspPwm.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"



#undef DEBUG_WIFI_DB	1				//wifi�������ܲ��Ժ�		

typedef int8_t (*AtCmdCbFunc)(void);

typedef struct tagEspAtWifi
{
	struct tagUsartInfo *usart;
	uint16_t uiWifiNetStates;			//ϵͳWiFi״̬
}EspAtWifi;

typedef enum {
	True = 0, 
	False= !True
} State;
typedef enum{
	Station = 1,
	AP = 2,
	ApStation = 3
}WorkMode;

typedef enum
{
   
    NoCfgWifiInfo = 0x0001,  //û�����ù�WiFiģ��
    WifiCfgInfoError = 0x0002,//wifi�˻�������������Ϣ����,���Ӵ���
    WifiConnecting = 0x0004,//wifi������
    WifiConnected = 0x0008,// wifi���ӳɹ�
    WifiDisconnect = 0x0010,//wifi����ʧ��
    ServerConnectError = 0x0020, //����������ʧ��
    ServerConnectOk	= 0x0040,
    ServerConnecting = 0x0080,//���ڽ��з���������
    NoWifiNode = 0x0100,//��WiFiģ�����wifiģ������Ӧ
}WifiNetState;//ϵͳwifi����״̬״̬

int8_t bspEspAtWifiSendCmd(uint8_t *cmd,uint8_t *ack,AtCmdCbFunc cb,uint16_t waittime);
int8_t bspEspAtWifiQuitTrans();
int8_t bspEspAtWifiConnectWifi(uint8_t *WifiName,uint8_t *Password);
int8_t  bspEspAtWifiTcpMux(uint16_t Mode);
void bspEspAtWifiInit();
int8_t bspEspAtWifiConnectServer(uint8_t *ServerIp,uint8_t *Port);
int8_t bspEspAtWifiRecvData(uint8_t WaitPort,uint8_t *RecvBuf,uint16_t RecvDatLen,uint16_t TimeOut);
int8_t bspEspAtWifiSoftRest();
int8_t bspEspAtWifiCleanRecvBuf();
int8_t bspEspAtWifiTest();
int8_t bspEspAtWifiSetWorkMode(uint16_t Mode);
int8_t bspCfgWifiInfo();
int8_t bspEspAtWifiCheckConnectSeverState();
int8_t bspEspAtWifiTransMode();
int8_t bspEspAtWifiTransBeginSend();
int8_t bspEspAtWifiListWifiAp();
char * bspEspAtWifiFindStr(char *String,char *cFindString);

#ifdef STC_15WXX || STC_15FXX || STC_89CXX

extern EspAtWifi xdata mdEspAtWifi;

#else

extern EspAtWifi  mdEspAtWifi;
#endif

/********************************��Ҫ��ֲ�ĵط�******************************/
/*�������Ҫʹ�õ����⣬����ֲ����Ĵ��뼴�������Ӳ��ƽ̨�Ͻ���ʹ��
��������Ҫ��ֲ�ĵط�˵��
1��ע�ᴮ������
	#define BIND_USART &mdUsarts.Usart2		//���ٴ���2��
2��ע�ᶨʱ������
	
3��
*/
#define WITI_BIND_USART &mdUsarts.Usart2		//���ٴ���2��

/********************************��Ҫ��ֲ�ĵط�******************************/


#endif
