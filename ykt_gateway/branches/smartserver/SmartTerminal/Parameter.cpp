///////////////////////参数管理////////////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"

#define CMD_SETTERMINAL_MAINPAR			0xB7	//设置主参数(终端设备)
#define CMD_GETTERMINAL_MAINPAR			0xBF   //获取主参数(终端设备)
#define CMD_GETNET_MAINPAR				0x10   //获取主参数(网络设备)
#define CMD_DEBUG_GETTERMINAL_MAINPAR	0xB8   //调试获取主参数(终端设备)
#define CMD_DEBUG_GETNET_MAINPAR        0xF0   //调试获取主参数(网络设备)	


/// 功能：设置主参数
/// 输入：*mainpar 28字节
/// Ver1.0 ------ 20040228 Auth:Lina
int _stdcall MakeBuf_SetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *mainpar)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETTERMINAL_MAINPAR;
	addr          = pDevice->nAddr;
	len           = 32;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],mainpar,28);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：获取主参数
/// Ver1.0------ 20040228 Auth:Lina
int _stdcall MakeBuf_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	if(pDevice->nHardware != 5301)
		ucCommandByte = CMD_GETTERMINAL_MAINPAR;
	else
		ucCommandByte = CMD_GETNET_MAINPAR;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：调试获取主参数(不带注册号)
/// Ver1.0 ------ 20040228 Auth:Lina
int _stdcall MakeBuf_Debug_GetMainPar(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	if(pDevice->nHardware != 5301)
		ucCommandByte = CMD_DEBUG_GETTERMINAL_MAINPAR;
	else
		ucCommandByte = CMD_DEBUG_GETNET_MAINPAR;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:设置注册号
/// 参数:*regno---4字节注册号
/// Ver1.0 ----- 20040228 Auth:Lina
#define CMD_SETREGNO_TERMINAL 0xC4
#define CMD_SETREGNO_NET      0x11
int _stdcall MakeBuf_SetRegNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *regno)
{
	unsigned char ucCommandByte,ucRegNo[4],out[3];
	int           addr,len;
	if(pDevice->nHardware != 5301)
		ucCommandByte = CMD_SETREGNO_TERMINAL;
	else
		ucCommandByte = CMD_SETREGNO_NET;
	addr          = pDevice->nAddr;
	len           = 8;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],regno,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	if(pDevice->nHardware != 5301)
	{
		pBuffer->pBuffer[2] = CMD_SETREGNO_TERMINAL;
		calc_crc16(pBuffer->nCmdSize-3,pBuffer->pBuffer,out);
		pBuffer->pBuffer[pBuffer->nCmdSize-3] = out[0];
		pBuffer->pBuffer[pBuffer->nCmdSize-2] = out[1];
	}
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


///////////////////////////////收费类辅助参数////////////////////////////////////

/// 1、时间段管理
#define CMD_SFJ_SET_TIMEPHASE	0xAB
#define CMD_SFJ_GET_TIMEPHASE   0xAC
/// 功能：设置时间段
/// 参数：
///    No   ---- 时间段总条数
///    Time ---  节日次数
///    Buffer--- no*10 时间段参数
/// Ver1.0 --- 20040228 Auth:Lina
int _stdcall MakeBuf_SetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,int No,int Time,unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SFJ_SET_TIMEPHASE;
	addr          = pDevice->nAddr;
	len           = 6+No*10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	pBuffer->pBuffer[5] = Time;
	memcpy(&pBuffer->pBuffer[6],Buffer,No*10);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：获取时间段参数
/// Ver1.0 --- 20040228 Auth:Lina
int _stdcall MakeBuf_GetSFJ_TimePhase(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SFJ_GET_TIMEPHASE;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


/// 2.编号管理
#define CMD_SFJ_SET_FASTNO			0xAD	//下传快捷编号
#define CMD_SFJ_GET_FASTNO			0xAE	//上传快捷编号
#define CMD_SFJ_SET_CONSUMENO		0xB3	//下传消费编号
#define CMD_SFJ_DEL_COMSUMENO		0xB4	//删除消费编号
#define CMD_SFJ_GET_CONSUMEVERSION	0xB6	//上传消费编号版本	
#define CMD_SFJ_SET_CONSUMEVERSION  0xB5	//下传消费编号版本	

/// 功能：下传快捷编号
/// 参数：
///   No:编号总数(1字节)
///   Buffer:3*No编号内容
/// Ver1.0---20040228 Auth:Lina
int _stdcall MakeBuf_SetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char No, unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SFJ_SET_FASTNO;
	addr          = pDevice->nAddr;
	len           = 5+No*3;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,No*3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传快捷编号
/// Ver1.0---20040228 Auth:Lina
int _stdcall MakeBuf_GetSFJFastNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SFJ_GET_FASTNO;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:下传消费编号
/// 参数:
///    Flag:全部/或添加标记(1字节)
///    No:  编号数(1字节)
///    Buffer:N*3字节编号
/// Ver1.0 ------ 20040228 Auth:Lina
int _stdcall MakeBuf_SetSFJConsumeNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char Flag, unsigned char No,unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SFJ_SET_CONSUMENO;
	addr          = pDevice->nAddr;
	len           = 6+No*3;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = Flag;
	pBuffer->pBuffer[5] = No;
	memcpy(&pBuffer->pBuffer[6],Buffer,No*3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：删除消费编号
/// 参数:
///   No:编号总数
///   Buffer:N*3字节编号
/// Ver1.0 ----- 20040228 Auth:Lina
int _stdcall MakeBuf_DelSFJConsumeNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char No,unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SFJ_DEL_COMSUMENO;
	addr          = pDevice->nAddr;
	len           = 5+No*3;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,No*3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传消费编号版本
/// Ver1.0 --- 20040228 Auth:Lina
int _stdcall MakeBuf_GetSFJConsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SFJ_GET_CONSUMEVERSION;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:下传消费编号版本	
/// 参数：
///  Buffer:消费编号版本(6字节)
/// Ver1.0 ------ 20040228 Auth:Lina
int _stdcall MakeBuf_SetSFJComsumeVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SFJ_SET_CONSUMEVERSION;
	addr          = pDevice->nAddr;
	len           = 10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,6);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}


/// 3 卡片操作管理
#define CMD_SETDIRSECTOR		0x65	//设置卡片目录扇区号
#define CMD_GETDIRSECTOR		0x64    //读取卡片目录扇区号
#define CMD_SETV10PACKETSECTOR	0xDA    //设置V10卡片钱包所在的扇区
#define CMD_GETV10PACKETSECTOR	0xDD	//读取V10卡片钱包所在的扇区
#define CMD_SETV10PASSWORD		0xD5	//下传V10卡单位密码

/// 功能：设置卡片目录扇区号
/// 参数：Sector---卡片目录扇区号
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_SetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETDIRSECTOR;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = Sector;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：设置卡片目录扇区号
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_GetDirSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_GETDIRSECTOR;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：设置V10卡片钱包所在的扇区 
/// 参数：Sector --- 扇区号
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_SetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int Sector)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETV10PACKETSECTOR;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = Sector;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：读取V10卡片钱包所在的扇区
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_GetV10PacketSector(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_GETV10PACKETSECTOR;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能:下传V10卡单位密码
/// 参数：Password(2字节,低位在前)
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_SetV10Password(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETV10PASSWORD;
	addr          = pDevice->nAddr;
	len           = 6;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Password,2);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}


/// 4 扎帐参数管理
#define	CMD_GETSTATETIMETABLE	0x84	//上传定时结帐时间表
#define CMD_SETSTATETIMETALBE	0x85	//下传定时结帐时间表
#define CMD_STATE               0x89	//上位机要求扎帐
#define CMD_RESTATE				0x87	//复核扎帐

/// 功能:上传定时结帐时间表
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_GetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_GETSTATETIMETABLE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：下传定时结帐时间表
/// 参数：
///    No:定时扎帐总条数
///    Buffer:定时扎帐时间参数 时分为1组
/// Ver1.0 ------ 20040301 Auth:Lina 
int _stdcall MakeBuf_SetStateTimeTable(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,int No,unsigned char *Buffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETSTATETIMETALBE;
	addr          = pDevice->nAddr;
	len           = 4+1+No*2;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = No;
	memcpy(&pBuffer->pBuffer[5],Buffer,No*2);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：上位机要求扎帐
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_State(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_STATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：上位机要求复核扎帐
/// 参数：
///      SerialNo：要求复核扎帐流水号
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_ReState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_STATE;
	addr          = pDevice->nAddr;
	len           = 6;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],SerialNo,2);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 5 签到管理
#define CMD_SETCONSUMEFLAG	0x9F	//设置消费功能开启或关闭
#define CMD_SETSIGNINTIME	0x82	//设置定时签到时间
#define CMD_SETWORKINGKEY   0x83	//设置工作密钥及算法编号

/// 功能：设置消费功能开启或关闭
/// 参数：
///    Flag --- 1 开启
///    Flag --- 0 关闭
/// Ver1.0 ------ 20040301 Auth:Lina 
int _stdcall MakeBuf_SetComsumeFlag(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char Flag)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETCONSUMEFLAG;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = Flag;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

//int _stdcall MakeBuf_SetSignInTime(

/// 功能：设置工作密钥及算法编号
/// 参数：
///     *Plain ------ 密钥密文 9字节
/// Ver1.0 ------- 20040301 Auth:Lina
int _stdcall MakeBuf_SetWorkingKey(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Plain,unsigned char KeyNo)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = 0x8F;// modified by lina 20050309 CMD_SETWORKINGKEY;
	addr          = pDevice->nAddr;
	len           = 0x0c;// modified by lina 20050309 14;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Plain,8); //add by lina 20050309 
	//modified by lina 20050309 memcpy(&pBuffer->pBuffer[4],Plain,9);
	//modified by lina 20050309 pBuffer->pBuffer[13] = KeyNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 6 消费金额限定
#define	CMD_GETLARGECONSUMEMONEY	0xCB	//获取最大消费限额
#define CMD_SETLARGECONSUMEMONEY    0xCA	//设置最大消费限额

/// 功能：获取最大消费限额
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_GetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETLARGECONSUMEMONEY;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

/// 功能：设置最大消费限额
/// 参数：
///     Money:3字节金额低位在前
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_SetLargeConsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Money)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETLARGECONSUMEMONEY;
	addr          = pDevice->nAddr;
	len           = 7;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Money,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

#define CMD_SETDAYLARGECONSUMEMONEY 0x70
#define CMD_GETDAYLARGECONSUMEMONEY 0x71

//功能:设置日消费最大限额
//参数:
//    Money: 4字节金额低位在前
///   Ver1.0 ----- 20050316 Auth:lina
int _stdcall MakeBuf_SetDayLargeComsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Money)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETDAYLARGECONSUMEMONEY;
	addr          = pDevice->nAddr;
	len           = 7;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Money,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

//功能:获取日消费最大限额
//参数:
//    Money: 4字节金额低位在前
///   Ver1.0 ----- 20050316 Auth:lina
int _stdcall MakeBuf_GetDayLargeComsumeMoney(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Money)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_GETDAYLARGECONSUMEMONEY;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	//memcpy(&pBuffer->pBuffer[4],Money,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}



/// 7 密码管理
#define CMD_SETMANAGEPASSWORD	0xD6	//设置系统管理员密码

/// 功能：设置系统管理员密码
/// 参数：
///     Password:密码(3字节 BCD码)
int _stdcall MakeBuf_SetManagePassword(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Password)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETMANAGEPASSWORD;
	addr          = pDevice->nAddr;
	len           = 7;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Password,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;	
}

