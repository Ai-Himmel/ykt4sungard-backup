///////////////////////名单管理///////////////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"

#define CMD_GETBLACK_USEFULLIFE		0x8D	//有效期   
#define CMD_SETBLACK_USEFULLIFE		0x8E 	
#define CMD_GETBLACK_VERSION		0xA8	//版本
#define CMD_SETBLACK_VERSION		0xA7   //设置黑名单版本
#define CMD_BOARDBLACKNO			0xBE   //广播
#define CMD_CHECKBLACKCARDNO		0xBC   //检查黑名单
#define CMD_DOWNBLACKCARDNO			0xA4   //下传黑名单  
#define CMD_DELBLACKCARDNO			0xA5   //删除黑名单
#define CMD_DELALLBLACKCARDNO		0xA6   //删除所有黑名单
#define CMD_GETALLBLACKCARDNO		0xDC   //上传黑名单总条数	
#define CMD_RECOUNTALLBLACKCARDNO	0xDB   //重新统计黑名单总条数

#define CMD_DOWWHITECARDNO          0xAB   //下传白名单
#define CMD_DELWHITECARDNO          0xAC   //删除白名单
#define CMD_DELALLWHITECARDNO       0xAD   //下传删除所有白名单
#define CMD_SETWHITE_VERSION		0xAE   //下传白名单版本
#define CMD_GETWHITE_VERSION        0xAF   //上传白名单版本
#define CMD_CHECKWHITECARDNO		0xB0   //检查白名单
#define CMD_BOARDWHITENO			0xB1   //广播白名单

#define CMD_SETWHITE_VERSION4		0xC7   //下传白名单版本4
#define CMD_DOWWHITECARDNO4         0xC9   //下传白名单4
#define CMD_DOWWHITECARDNO5         0x80   //下传白名单5

#define CMD_SETASSISTANCEVER        10     //设置补助名单版本
#define CMD_GETASSISTANCEVER		11     //读取补助名单版本
#define CMD_SETASSISTLIST			12     //设置补助名单
#define CMD_GETASSISTLIST           13     //读取补助名单版本
#define CMD_CLEARALLASSISLIST       0x79   //清除所有补助名单
#define CMD_SETASSISTSTATE			0x78   //设置补助功能开关
#define CMD_GETASSISTSTATE          0x77   //读取补助功能开关

#define CMD_SETINCFEERATE			0x73   //增值机费率设置
#define CMD_GETINCFEERATE			0x74   //增值机费率读取

#define CMD_DOWNEXTCLASS			0x67	//下传附加卡类
#define CMD_UPLOADEXTCLASS			0x68	//上传附加卡类
#define CMD_DOWNTIMEEXTCLASS		0x62	//下传时间段卡类
#define CMD_UPLOADTIMEEXTCLASS		0x63	//上传时间段卡类

/// 功能：获取黑名单有效期
/// 参数：无
/// Ver:1.0 ------ 20040226 Auth:Lina
int _stdcall MakeBuf_GetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETBLACK_USEFULLIFE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传黑名单有效期
/// 参数：date---六子节黑名单有效期（年、月、日、时、分、秒)
/// Ver:1.0 ------ 20040226 Auth:Lina
int _stdcall MakeBuf_SetBlackUsefulLife(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, unsigned char *date)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETBLACK_USEFULLIFE;
	addr          = pDevice->nAddr;
	len           = 10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],date,6);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传黑名单版本
/// Ver:1.0 ------ 20040227 
/// Auth:Lina
int _stdcall MakeBuf_GetBlackVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETBLACK_VERSION;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传黑名单版本
/// 参数： *date ---- 六子节黑名单版本
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_SetBlackVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETBLACK_VERSION;
	addr          = pDevice->nAddr;
	len           = 10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],date,6);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：广播黑名单
/// 参数：
///      pBuffer:数据体
///      Version:版本信息 6字节BCD码
///      CardNo: 卡号     3字节
/// 返回：
///      通信包数据体长度
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_BoardBlackNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	int           i;
	ucCommandByte = CMD_BOARDBLACKNO;
	addr          = 0;
	len           = 9;
	//for(i=0;i<6;i++)
	//	Version[i] = (Version[i] / 10) * 16 + (Version[i] - (Version[0] / 10)*10);
	memcpy(Buffer,CardNo,3);
	memcpy(&Buffer[3],Version,6);
	i = PubCommands(addr,ucCommandByte,len,Buffer,0,ucRegNo);
	return i;
}

/// 功能：检查黑名单
/// 参数：*CardNo	3字节卡号
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_CheckBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_CHECKBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 3;
	memcpy(pBuffer->pBuffer,CardNo,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传黑名单( 注意：一次只能下传一条黑名单)
/// 参数： *CardNo 3子节卡号
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_DownBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_DOWNBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 8;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = 1;
	memcpy(&pBuffer->pBuffer[5],CardNo,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：删除黑名单(注意：一次只能删除一条黑名单)
/// 参数： *CardNo 3子节卡号
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_DelOneBlackCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_DELBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 8;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = 1;
	memcpy(&pBuffer->pBuffer[5],CardNo,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
} 

/// 功能：删除所有黑名单
/// Ver:  1.0 ---- 20040227
/// Auth: Lina 
int _stdcall MakeBuf_DelAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_DELALLBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


/// 功能：上传黑名单条数
/// Ver:  1.0 ---- 20040227
/// Auth: Lina
int _stdcall MakeBuf_GetBlackAllCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETALLBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：重新统计黑名单总条数
/// Ver:  1.0 ---- 20040227
/// Auth: Lina
int _stdcall MakeBuf_RecountAllBlackCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_RECOUNTALLBLACKCARDNO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	
	return RET_OK;
}

/// 功能：下传白名单(注意：一次只能下传一条)
/// 参数： CardNo----3字节
/// Ver ： 1.0 ------ 20040227
/// Auth： Lina
int _stdcall MakeBuf_DownWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int flag, unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	addr          = pDevice->nAddr;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);

	if( flag == 4 ) 
	{
		ucCommandByte = CMD_DOWWHITECARDNO4;
		len   = 22;
		memcpy(&pBuffer->pBuffer[4],CardNo,18);
		pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	}
	else if( flag == 5 ) 
	{
		ucCommandByte = CMD_DOWWHITECARDNO5;
		len   = 30;
		memcpy(&pBuffer->pBuffer[4],CardNo,26);
		pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	}
	else
	{
		ucCommandByte = CMD_DOWWHITECARDNO;
		len   = 8;
		pBuffer->pBuffer[4] = 1;
		memcpy(&pBuffer->pBuffer[5],CardNo,3);
		pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	}

	pBuffer->nTimeOut1 = 1000;
	pBuffer->nTimeOut1 = 1000;

	return RET_OK;
}

/// 功能：删除白名单(注意：一次只能删除一条)
/// 参数：CardNo---3字节
/// Ver ：1.0 ------ 20040227
/// Auth：Lina
int _stdcall MakeBuf_DelWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_DELWHITECARDNO;
	addr          = pDevice->nAddr;
	len           = 8;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = 1;
	memcpy(&pBuffer->pBuffer[5],CardNo,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：删除所有白名单
/// Ver： 1.0 ------ 20040227
/// Auth：Lina
int _stdcall MakeBuf_DelAllWhiteCardNo(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_DELALLWHITECARDNO;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传白名单版本
/// 参数：*date ---- 六子节黑名单版本
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_SetWhiteVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETWHITE_VERSION;
	addr          = pDevice->nAddr;

	len           = 10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],date,6);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传白名单版本4
/// 参数：*date ---- 六子节黑名单版本4
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_SetWhiteVersion4(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *date)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_SETWHITE_VERSION4;
	addr          = pDevice->nAddr;
	len           = 16;
	unsigned char out[5];

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);

	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],date,10);

	calc_crc16(14,pBuffer->pBuffer,out);
	pBuffer->pBuffer[14] = out[0];
	pBuffer->pBuffer[15] = out[1];

	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 200;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传白名单版本
/// Ver:1.0 ------ 20040227 
/// Auth:Lina
int _stdcall MakeBuf_GetWhiteVersion(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETWHITE_VERSION;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：检查白名单
/// 参数：*CardNo	3字节卡号
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_CheckWhiteCardNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *CardNo)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_CHECKWHITECARDNO;
	addr          = pDevice->nAddr;
	len           = 3;
	memcpy(pBuffer->pBuffer,CardNo,3);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：广播白名单
/// 参数：
///      pBuffer:数据体
///      Version:版本信息 6字节BCD码
///      CardNo: 卡号     3字节
/// 返回：
///      通信包数据体长度
/// Ver: 1.0 ------- 20040227
/// Auth:Lina
int _stdcall MakeBuf_BoardWhiteNo(unsigned char *Buffer, unsigned char *Version, unsigned char *CardNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	int           i;
	ucCommandByte = CMD_BOARDWHITENO;
	addr          = 0;
	len           = 9;
	//for(i=0;i<6;i++)
	//	Version[i] = (Version[i] / 10) * 16 + (Version[i] - (Version[0] / 10)*10);
	memcpy(Buffer,CardNo,3);
	memcpy(&Buffer[3],Version,6);
	i = PubCommands(addr,ucCommandByte,len,Buffer,0,ucRegNo);
	return i;
}


/// 功能：补助名单版本下传
/// 参数：
///   Buffer: 
///     版本时间:  6字节
///     总条数:    2字节
///     总金额:    4字节(低位在前)
///     加钱总条数:2字节
///     加钱总金额:4字节(低位在前)
///     减钱总条数:2字节
///     减钱金额:  4字节(低位在前)
/// Ver: 1.0 ------ 20040227
/// Auth: Lina
int _stdcall MakeBuf_SetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer)
{
	unsigned char ucCommandByte,out[3];
	int           addr,len;
	ucCommandByte = CMD_SETASSISTANCEVER;
	addr          = pDevice->nAddr;
	len           = 26;
	calc_crc16(24,Buffer,out);
	memcpy(pBuffer->pBuffer,Buffer,24);
	pBuffer->pBuffer[24] = out[0];
	pBuffer->pBuffer[25] = out[1];
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：补助名单版本上传
/// Ver: 1.0 ------ 20040227
/// Auth: Lina
int _stdcall MakeBuf_GetAssistVersion(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETASSISTANCEVER;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：下传补助名单
/// 参数：*List
///       3字节交易卡号
///       2字节批号
///       2字节金额(低位在前)
///       1字节加减钱标记(0---加，1---减)
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_SetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *Buffer)
{
	unsigned char ucCommandByte,out[3];
	int           addr,len;
	ucCommandByte = CMD_SETASSISTLIST;
	addr          = pDevice->nAddr;
	len           = 10;
	calc_crc16(8,Buffer,out);
	memcpy(pBuffer->pBuffer,Buffer,8);
	pBuffer->pBuffer[8] = out[0];
	pBuffer->pBuffer[9] = out[1];
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：上传补助名单
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_GetAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_GETASSISTLIST;
	addr          = pDevice->nAddr;
	len           = 0;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：清除补助名单
/// Ver： 1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_ClearAllAssisList(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_CLEARALLASSISLIST;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

#define CMD_SETASSISTSTATE			0x78   //设置补助功能开关
#define CMD_GETASSISTSTATE          0x77   //读取补助功能开关

/// 功能：设置补助功能开关
/// 参数：
/// switchflag ---00开
///            ---FF关
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_SetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char switchflag)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETASSISTSTATE;
	addr          = pDevice->nAddr;
	len           = 5;

	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = switchflag;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能：获取补助功能开关
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_GetAssistState(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_GETASSISTSTATE;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


/// 增值机费率设置
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_SetIncFeeRate(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char cCard, unsigned char nRate)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETINCFEERATE;
	addr          = pDevice->nAddr;
	len           = 6;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = cCard;
	pBuffer->pBuffer[5] = nRate;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 增值机费率读取
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_GetIncFeeRate(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char cCard)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_SETINCFEERATE;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = cCard;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 下传附加卡类
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_DownloadExtClass(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char *pClass)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_DOWNEXTCLASS;
	addr          = pDevice->nAddr;
	len           = 34;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],pClass,30);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 上传附加卡类
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_UploadExtClass(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_UPLOADEXTCLASS;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


/// 下传时间段卡类
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_DownloadExtTimeClass(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char cNo, unsigned char *pClass)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_DOWNTIMEEXTCLASS;
	addr          = pDevice->nAddr;
	len           = 35;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = cNo;
	memcpy(&pBuffer->pBuffer[5],pClass,30);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


/// 上传时间段卡类
/// 参数：
/// Ver：1.0 ------ 20040228
/// Auth：Lina
int _stdcall MakeBuf_UploadExtTimeClass(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer, unsigned char cNo)
{
	unsigned char ucCommandByte,ucRegNo[4];
	int           addr,len;
	ucCommandByte = CMD_UPLOADTIMEEXTCLASS;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = cNo;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


