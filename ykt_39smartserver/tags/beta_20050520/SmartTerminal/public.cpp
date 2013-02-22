#include "stdafx.h"
#include "SmartTerminal.h"
#define  CMD_SETID		    0xE0
#define  CMD_GETID		    0xE1
#define  CMD_SEARCHID	    0xE2
#define  CMD_SETADDRESS     0xE3
#define  CMD_GETTYPE        0xE4
#define  CMD_GETVERSION     0xE5
#define  CMD_CHANGEBUADRATE	0xE6
/*******************************公用命令********************************/
//设置终端设备ID号 
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_SetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETID;
	addr          = 0xFF;
	len           = 4;
	memcpy(pBuffer->pBuffer,id,4);
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//读取终端设备ID号
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_GetID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETID;
	addr          = 0xFF;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//通过ID号最低位查询终端设备ID号
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_SearchID(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SEARCHID;
	addr          = 0xFF;
	len           = 1;
	pBuffer->pBuffer[0] = id[0];
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}
//通过终端设备ID号给终端设备设置机号
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_SetAddr(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *id)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETADDRESS;
	addr          = 0xFF;
	len           = 5;
	memcpy(pBuffer->pBuffer,id,5);
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//读终端设备机号类型命令
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_GetType(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETTYPE;
	addr          = pDevice->nAddr;
	len           = 0;
	
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//读终端设备程序版本号
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_GetVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETVERSION;
	addr          = pDevice->nAddr;
	len           = 0;
	
	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

///  更改通信波特率
/// 输入                                      
///    nBaudRate 波特率值  19200  9600 4800 2400  1200 28800	57600	115200  38400
/// Ver 1.0 --- 20040225 Auth:Lina
int _stdcall MakeBuf_ChangeBuadRate(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int nBaudRate)
{
	unsigned char ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_CHANGEBUADRATE;
	addr          = pDevice->nAddr;
	len           = 1;
	if(nBaudRate == 19200)
		pBuffer->pBuffer[0] = 0;
	else if(nBaudRate == 9600)
		pBuffer->pBuffer[0] = 1;
	else if(nBaudRate == 4800)
		pBuffer->pBuffer[0] = 2;	
	else if(nBaudRate == 2400)
		pBuffer->pBuffer[0] = 3;
	else if(nBaudRate == 1200)
		pBuffer->pBuffer[0] = 4;
	else if(nBaudRate == 28800)
		pBuffer->pBuffer[0] = 5;
	else if(nBaudRate == 57600)
		pBuffer->pBuffer[0] = 6;
	else if(nBaudRate == 115200)
		pBuffer->pBuffer[0] = 7;
	else if(nBaudRate == 38400)
		pBuffer->pBuffer[0] = 8;	
	else
		return RET_DATAVALUE_ERROR;

	pBuffer->nCmdSize = PubCommands(addr,
		                            ucCommandByte,
						     	    len,
								    pBuffer->pBuffer,
								    pDevice->nLevel,
								    pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}
