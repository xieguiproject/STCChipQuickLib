#include "bsp_Epprom.h"



/*----------------------------
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}


/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //数据缓冲区

    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}
/*****************************************************************************
 * 函 数 名  : IapWrite
 * 负 责 人  : xiegui
 * 创建日期  : 2019年1月13日
 * 函数功能  : 写入批量数据
 * 输入参数  : WORD addr       写地址
               BYTE *buf       写
               uint16_t uiLen  长度
 * 输出参数  : 无
 * 返 回 值  : 
 * 调用关系  : 
 * 其    它  : 

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
扇区擦除
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
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
