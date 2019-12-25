#ifndef BSP_AT_H
#define BSP_AT_H

#include "bspUsart.h"
#include "bspPwm.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"



#undef DEBUG_WIFI_DB	1				//wifi天线性能测试宏		

typedef int8_t (*AtCmdCbFunc)(void);

typedef struct tagEspAtWifi
{
	struct tagUsartInfo *usart;
	uint16_t uiWifiNetStates;			//系统WiFi状态
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
   
    NoCfgWifiInfo = 0x0001,  //没有配置过WiFi模块
    WifiCfgInfoError = 0x0002,//wifi账户和密码配置信息有无,连接错误
    WifiConnecting = 0x0004,//wifi连接中
    WifiConnected = 0x0008,// wifi连接成功
    WifiDisconnect = 0x0010,//wifi连接失败
    ServerConnectError = 0x0020, //服务器连接失败
    ServerConnectOk	= 0x0040,
    ServerConnecting = 0x0080,//增在进行服务器连接
    NoWifiNode = 0x0100,//无WiFi模块或者wifi模块无响应
}WifiNetState;//系统wifi网络状态状态

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

/********************************需要移植的地方******************************/
/*如果你需要使用到本库，请移植下面的代码即可在你的硬件平台上进行使用
下面是需要移植的地方说明
1、注册串口驱动
	#define BIND_USART &mdUsarts.Usart2		//绑定再串口2上
2、注册定时器驱动
	
3、
*/
#define WITI_BIND_USART &mdUsarts.Usart2		//绑定再串口2上

/********************************需要移植的地方******************************/


#endif
