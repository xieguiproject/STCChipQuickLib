#include "bsp_Epprom.h"



/*----------------------------
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //�������Ĵ���
    IAP_TRIG = 0;                   //��������Ĵ���
    IAP_ADDRH = 0x80;               //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}


/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //���ݻ�����

    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                      //�ر�IAP����

    return dat;                     //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}
/*****************************************************************************
 * �� �� ��  : IapWrite
 * �� �� ��  : xiegui
 * ��������  : 2019��1��13��
 * ��������  : д����������
 * �������  : WORD addr       д��ַ
               BYTE *buf       д
               uint16_t uiLen  ����
 * �������  : ��
 * �� �� ֵ  : 
 * ���ù�ϵ  : 
 * ��    ��  : 

*****************************************************************************/
void IapWrite(WORD addr,BYTE *buf,uint16_t uiLen)
{
	uint16_t uiLoop = 0;
	while(uiLoop < uiLen)
	{
		IapProgramByte(addr + uiLoop,buf[uiLoop]);
		uiLoop++;
	}
	IapIdle();
}
void IapRead(WORD addr,BYTE *buf,uint16_t uiLen)
{
	uint16_t uiLoop = 0;
	while(uiLoop < uiLen)
	{
		buf[uiLoop] =  IapReadByte(addr + uiLoop);
		uiLoop++;
	}
	IapIdle();
}

/*----------------------------
��������
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}
void EppromTest()
{
	uint16_t uiLoop = 0;
	//printf("erase ok\n");
	IapEraseSector(EPPROM_PARM_BASE_ADDR);
	for(uiLoop = 0;uiLoop < 512;uiLoop++)
	{
		if(IapReadByte(EPPROM_PARM_BASE_ADDR + uiLoop) != 0xff)
		{
			//printf("erase error\n");
		}
	}
	//printf("erase ok\n");
}
