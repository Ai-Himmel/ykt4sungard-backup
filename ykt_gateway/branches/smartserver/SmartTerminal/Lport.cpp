/////////////////////////////Lport相关命令///////////////////////////////////////

#include "stdafx.h"
#include "SmartTerminal.h"

//////////////////////////////端口管理/////////////////////////
#define CMD_SETPORTREGNOANDMACNO			0x40    //重设服务器某端口注册号及机号
#define CMD_CLEARPORTDATA					0x41    //端口数据初始化
#define CMD_SETPORTPARTOFACTORYSETTING      0x42    //端口参数初始化
#define CMD_GETPORTPAR						0x43    //读服务器某端口参数
#define CMD_SEARCHPORT						0x07	//搜索端口

/// 功能：设置服务器某端口注册号及机号
/// 参数：
/// PortNo    ----- 1BYTE   对应端口号
/// newRegNo  ----- 4BYTE   对应注册号
/// MacNo     ----- 1BYTE   对应机号
/// 产生后果：Lport该端口所有数据将清空
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetPortRegNoAndMacNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo,unsigned char *newRegNo,int MacNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETPORTREGNOANDMACNO;
	addr          = pDevice->nAddr;
	len           = 0x0a;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = PortNo;
	pBuffer->pBuffer[5] = MacNo;
	memcpy(&pBuffer->pBuffer[6],newRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：端口数据初始化
/// 参数:
///     PortNo------端口号
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_ClearPortData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_CLEARPORTDATA;
	addr          = pDevice->nAddr;
	len           = 0x05;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = PortNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：端口参数初始化(将端口所有信息恢复为出厂状态)
/// 参数：
///    PortNo ------ 端口号
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetPortToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETPORTPARTOFACTORYSETTING;
	addr          = pDevice->nAddr;
	len           = 0x05;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = PortNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}
 
/// 功能：读服务器某端口参数
/// 参数：
///    PortNo ------ 端口号
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetPortPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETPORTPAR;
	addr          = pDevice->nAddr;
	len           = 0x05;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = PortNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:搜索端口
/// 参数：
///    PortNo ------ 端口号
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SearchPort(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int PortNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SEARCHPORT;
	addr          = pDevice->nAddr;
	len           = 0x05;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = PortNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


///////////////////////////端口数量管理//////////////////////////////////////////////////////
#define CMD_GETPORTTOTALNO	0x45  //获取端口总数
#define CMD_SETPORTTOTALNO  0x44  //设置端口总数

//////////////////////////电话号码相关设置///////////////////////////////////////////////////////
#define	CMD_SETDIALPHONE	0x46	//设置上位机电话号码
#define CMD_GETDIALPHONE	0x47	//获取上位机电话号码
#define CMD_SETDIALTIME		0x48	//设置定时拨号时间

////////////////////////参数//////////////////////////////////////////////////////////////////
#define CMD_GETLPORTMAINPAR				   0x10    //读取主参数
#define CMD_SETLPORTNEWREGNO			   0x11    //设置注册号
#define CMD_SETLPORTTOFACTORYSETTING       0x3d    //初始化服务器
#define CMD_DEBUGGETLPORTMAINPAR		   0xf0    //调试上传主参数

/// 功能:读取Lport主参数
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetLportMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETLPORTMAINPAR;
	addr          = pDevice->nAddr;
	len           = 0x04;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：设置注册号
/// 参数：
/// newRegNo ------ 新注册号
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetLportNewRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *newRegNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETLPORTNEWREGNO;
	addr          = pDevice->nAddr;
	len           = 0x08;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],newRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：初始化服务器
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetLportToFactorySetting(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETLPORTTOFACTORYSETTING;
	addr          = pDevice->nAddr;
	len           = 0x04;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：调试上传服务器主参数
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_DebugGetLportMainPar(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETLPORTTOFACTORYSETTING;
	addr          = pDevice->nAddr;
	len           = 0x00;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

#define CMD_ROMMOTERESET          0x01   //远程复位指令

/// 功能：远程复位
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_RemoteReset(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_ROMMOTERESET;
	addr          = pDevice->nAddr;
	len           = 0x04;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

