#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "STC15xx.H"

/*****************控制协议头部******************/
typedef struct tagCmdHeadProtocol
{
    uint16_t uiHead;//协议头部0x5a5a
    uint16_t uiCmdId;//命令id
    uint16_t uiCmdLen;//协议负载长度
    uint16_t uiEnd; //协议尾部0x7e7e
}CmdHeadProtocol;


#define MOTO_CONTROL_CMD    1		//方向控制命令
#define MOTO_SET_CMD		2		//设定按钮
#define MOTO_ENTER_CMD		3		//确认按钮
#define MOTO_CHANGE_DIR     4		//修改电机默认方向

#define MOTO_CONTROL_UP 	1
#define MOTO_CONTROL_DOWN 	2
#define MOTO_CONTROL_STOP	3



#endif