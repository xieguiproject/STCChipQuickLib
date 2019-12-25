#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "STC15xx.H"

/*****************����Э��ͷ��******************/
typedef struct tagCmdHeadProtocol
{
    uint16_t uiHead;//Э��ͷ��0x5a5a
    uint16_t uiCmdId;//����id
    uint16_t uiCmdLen;//Э�鸺�س���
    uint16_t uiEnd; //Э��β��0x7e7e
}CmdHeadProtocol;


#define MOTO_CONTROL_CMD    1		//�����������
#define MOTO_SET_CMD		2		//�趨��ť
#define MOTO_ENTER_CMD		3		//ȷ�ϰ�ť
#define MOTO_CHANGE_DIR     4		//�޸ĵ��Ĭ�Ϸ���

#define MOTO_CONTROL_UP 	1
#define MOTO_CONTROL_DOWN 	2
#define MOTO_CONTROL_STOP	3



#endif