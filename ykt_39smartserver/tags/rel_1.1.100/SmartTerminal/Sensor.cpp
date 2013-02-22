////////////////////////////感应头管理///////////////////////////
///////////////////////////模式三时间段管理//////////////////////
///////////////////////////登陆公共信息查询//////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"



////////////////////////////感应头管理///////////////////////////
#define   CMD_SEARCHSENSOR		0x96	//搜索感应头
#define   CMD_GETSENSORINFO		0x97	//上传感应头信息
#define   CMD_SETSENSORADDRESS	0x98	//设置感应头机号
/// 功能：搜索感应头
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SearchSensor(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SEARCHSENSOR;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传感应头信息
/// Ver1.0 ----- 20040303 Auth:Lina
int _stdcall MakeBuf_GetSensorInfo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETSENSORINFO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：设置感应头机号
/// 参数：
///     No----感应头总数
///     Buffer----n*5字节 
int _stdcall MakeBuf_SetSensorAddress(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETSENSORADDRESS;
	addr          = pDevice->nAddr;
	len           = 5+5*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,5*No);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

////////////////////////////防火防盗处理/////////////////////////////////
#define CMD_SETFIRESTATE	0x9B	//设置为防火状态
#define CMD_SETTHEFTSTATE   0x9C    //设置为防盗状态
#define CMD_SETNORMALSTATE  0x9D    //恢复为正常状态

/// 功能：设置为防火状态
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SetFireState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETFIRESTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：设置为防盗状态
/// Ver1.0 ------ 20040303 Auth:Lina
int _stdcall MakeBuf_SetTheftState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETTHEFTSTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：恢复为正常状态
/// Ver1.0 ------ 20040303 Auth:Lina 
int _stdcall MakeBuf_SetNormalState(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_SETNORMALSTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

//////////////////////////////模式三时间段管理/////////////////////////
#define CMD_SETMODE3HOLIDAYINFO		0xB2	//设置模式三节假日信息
#define CMD_SETMODE3TIMEPHASEINFO	0xB3	//设置模式三时间段信息
#define CMD_GETMODE3HOLIDAYINFO     0xB4	//获取模式三节假日信息
#define CMD_GETMODE3TIMEPHASEINFO	0xB5	//获取模式三时间段信息


//////////////////////////////模式四时间段管理/////////////////////////
#define CMD_SETMODE4HOLIDAYINFO		0xCB	//设置模式四节假日信息
#define CMD_SETMODE4TIMEPHASEINFO	0xCD	//设置模式四时间段信息
#define CMD_GETMODE4HOLIDAYINFO     0xB4	//获取模式四节假日信息
#define CMD_GETMODE4TIMEPHASEINFO	0xB5	//获取模式四时间段信息


/// 功能：设置模式三节假日信息
/// 参数：
///    No:节假日总条数
///    Buffer:节假日信息
/// Ver1.0 ------ 20040304 Auth:Lina
int _stdcall MakeBuf_SetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE3HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 5+2*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,2*No);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：设置模式三时间段信息
/// 参数:
///    WeekInfo:星期信息 1Byte
///    No:时间段数       1Byte
///    Buffer:时间段信息 No*8 Byte
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo,int No,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE3TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 6+8*No;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = WeekInfo;
	pBuffer->pBuffer[5] = No;
	memcpy(&pBuffer->pBuffer[6],Buffer,8*No);
	pBuffer->nCmdSize  = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：设置模式四时间段信息
/// 参数:
///    Buffer:时间段信息 32 Byte
///
/// Ver1.0 ------ 20040308 Auth:Lina
/*      32Byte时间段信息：                   */
/*    1、时间段号：1Byte(0至63)  (连续)      */
/*    2、起始日期：年、月、日，3Byte(hex)    */
/*    3、结束日期：年、月、日，3Bye(hex)     */
/*    4、起始时间：时、分，2Byte(hex)	     */	
/*    5、结束时间：时、分，2Byte(hex)        */
/*    6、星期及节假日信息：1Byte		     */	
/* 分别代表周1(最低位)至周7以及节假日(最高位)*/
/*该位置0时表示当天有效，置1时表示当天无效   */
/*	  7、保留 20Byte 0xff					 */
/* Output:									 */
/*  Return:    		                         */ 
/*    0    ---成功                           */
/*    -6   ---终端在1500ms内无应答           */
int _stdcall MakeBuf_SetMode4TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE4TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 36;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,32);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 200;
	pBuffer->nTimeOut1 = 1000;

	return RET_OK;
}


/// 功能：设置模式四节假日信息
/// 参数：
///    No:节假日总条数
///    Buffer:节假日信息
///      1Byte 节假日编号(0---63)   
///      3Byte 节假日信息(年、月、日)
/// Ver1.0 ------ 20040304 Auth:Lina
int _stdcall MakeBuf_SetMode4Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No, unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETMODE4HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 4+4;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);

	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,4);

	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 200;
	pBuffer->nTimeOut1 = 1000;

	return RET_OK;
}

/// 功能：获取模式三节假日信息
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetMode3Holiday(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETMODE3HOLIDAYINFO;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
} 

/// 功能：获取模式三时间段信息
/// 参数: 
///   WeekInfo:星期信息
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_GetMode3TimePhaseInfo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int WeekInfo)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETMODE3TIMEPHASEINFO;
	addr          = pDevice->nAddr;
	len           = 1;
	pBuffer->pBuffer[0] = WeekInfo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

#define  CMD_LOGINPUBLIC1PASSWORD	0x83
/// 功能：下传登陆公共信息1所需要的密码
/// 参数：
///     Password
/// Ver1.0 ------ 20040308 Auth:Lina
int _stdcall MakeBuf_SetLoginPublic1Password(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Password)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_LOGINPUBLIC1PASSWORD;
	addr          = pDevice->nAddr;
	len           = 14;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Password,10);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}