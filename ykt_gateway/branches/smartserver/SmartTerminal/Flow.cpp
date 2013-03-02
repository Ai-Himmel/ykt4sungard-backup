/*int flag;
	FILE *fp;
	CTime tm = CTime::GetCurrentTime();
	char filename[512],chTemp[512];
	
	GetCurrentDirectory(512,chTemp);
	sprintf(filename,"%s\\%s_%.2d%.2d%.2d.txt",chTemp,
					    pDevice->sRegNo, 
				        tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	fputs("收集原始数据\n",fp);
	for(flag=0;flag<pBuffer->nCmdSize;flag++)
	{
		sprintf(chTemp,"%.2X",pBuffer->pBuffer[flag]);
		fputs(chTemp,fp);
	}
	flag = VerifyBufferValid(pBuffer->pBuffer,pBuffer->nCmdSize);
	if(flag != RET_OK)
		fputs("CRC错误\n",fp);
	else
		fputs("CRC失败\n",fp);
	fclose(fp); 
	return RET_OK;*/

#include "stdafx.h"
#include "SmartTerminal.h"
//////////////////////////////////////////////////////////////////////////////////////////
/// 功能：协议规则定义函数
/// 参数：
///         pSmartPT   —— 协议规则数据块
/// 返回值：
///       见返回值定义
//////////////////////////////////////////////////////////////////////////////////////////
int _stdcall GetSmartProtocolRule(TSSmartProtocol *pSmartPT)
{
	//Smart411协议
	pSmartPT->PTHeadLen = 1;
	pSmartPT->PTHead[0] = 0xC2;
	pSmartPT->PTTailLen = 1;
	pSmartPT->PTTail[0] = 0xC3;
	pSmartPT->nLenOffset= 3;       //数据包长度偏移(0..n)
	pSmartPT->nLenSize  = 1;         //长度字节数(目前为1)
	pSmartPT->nMinPKSize= 7;       //包最短的长度
	pSmartPT->nMaxPKSize= 256;       //包最大的长度(0.不限长)
	return RET_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////
/// 功    能: -- 收到包的一部分后对其进行校验, 检测是否合法。
/// 参    数: 
///        pBuffer     --  要校验的数据块
///        nBufferSize --  数据块长度
///
/// 返 回 值: 
///        见返回值定义
///
/// 说    明:
///        只检验协议的正确性,如包的数据长度, CRC等错误
///////////////////////////////////////////////////////////////////////////////////////////
int VerifyBufferValid(unsigned char *pBuffer, int nBufferSize)
{
	unsigned char out[3];
	int           flag;
	flag = calc_crc16((unsigned char)nBufferSize,pBuffer,out);
	if(flag == 1)
		return  RET_OK;
	else
		return RET_DATACRC_ERROR;
}

//通用函数: 设备动态库检测收到数据收否正确：符合SMART411协议 
int _stdcall UnMakeDeviceBuffer(TSCmdBuffer *pBuffer)
{
	int flag;
	if(pBuffer->pBuffer[0] == 0xC2)
	{
		if(pBuffer->pBuffer[pBuffer->nCmdSize-1] == 0xC3)
		{
			if(pBuffer->nCmdSize >= 7)
			{
				flag =  VerifyBufferValid(pBuffer->pBuffer,pBuffer->nCmdSize);
				return flag;
			}
			else
				return RET_DATALENGTH_ERROR;
		}
		else
			return RET_RECV_TIMEOUT;
	}
	else
		return RET_TERME_NOANSWER;
}


////////////////////////终端设备专用指令//////////////////////////////////////
//----------------------1、初始化-------------------------------------------//
//1.1恢复终端设备为出厂状态
//Ver1.0 --- 20040225 Auth:Lina
int _stdcall MakeBuf_SetTerminalToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	if(pDevice->nHardware == 5301) //服务器
		ucCommandByte = 0x3d;
	else
		ucCommandByte = 0xc5;
	
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
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

//1.2扎帐数据初始化  产生后果: 清空所有结帐记录，并按天重新结帐。
//Ver1.0 --- 20040225 Auth:Lina
int _stdcall MakeBuf_RecountAllStateData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = 0xc7;
	
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
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

#define CMD_CLEARDATA	0x66 //清除所有交易数据

/// 功能：清除所有交易数据
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_ClearData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = CMD_CLEARDATA;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

///

//1.3服务器端口恢复为出厂状态 产生后果:端口参数恢复为出厂状态，并清空该端口所有存储纪录
//Ver1.0 --- 20040225 Auth:Lina
/*int _stdcall MakeBuf_SetPortToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer, int portno)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = 0x42;
	addr          = pDevice->nAddr;
	len           = 5;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = portno;
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}
*/
/// 功能：清除某一端口数据
/// 参数：


/// 功    能: -- 数据收集函数。
//Ver 1.0 ---20040224 Auth:Lina
int _stdcall MakeBuf_CollectData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = 0x03;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}


///////////数据接收与发送///////////////////////////////////////

/// 功能：数据确认
/// 参数：FlowNo --- 2字节流水号
/// Ver1.0 --- 20040301 Auth:Lina
int _stdcall MakeBuf_ConfirmData(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *FlowNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = 0x04;
	addr          = pDevice->nAddr;
	len           = 9;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->pBuffer[4] = 0x20;
	pBuffer->pBuffer[5] = 0xd0;
	pBuffer->pBuffer[6] = 0x10;
	memcpy(&pBuffer->pBuffer[7],FlowNo,2);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:按流水上传终端交易纪录
/// 参数:SerialNo ---- 2字节流水号
/// Ver1.0 ---- 20040301 Auth:Lina
int _stdcall MakeBuf_CollectDataBySerialNo(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	if(pDevice->nHardware == 5301)
		ucCommandByte = 0xde;
	else
		ucCommandByte = 0xbb;
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

/// 功能:上传扎帐纪录
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_CollectStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = 0x8c;
	addr          = pDevice->nAddr;
	len           = 4;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:确认扎帐纪录
/// 参数:FlowNo --- 2字节流水号
/// Ver1.0 ------ 20040301 Auth:Lina
int _stdcall MakeBuf_ConfirmStateData(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *FlowNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = 0x8B;
	addr          = pDevice->nAddr;
	len           = 6;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],FlowNo,2);
	pBuffer->nCmdSize = PubCommands(addr,ucCommandByte,len,pBuffer->pBuffer,pDevice->nLevel,pDevice->sLevelArray);
	pBuffer->nTimeOut1 = 50;
	pBuffer->nTimeOut1 = 1000;
	return RET_OK;
}

/// 功能:按流水上传扎帐纪录
/// 参数：SerialNo ---- 2字节流水号
/// Ver1.0 ----- 20040301 Auth:Lina
int _stdcall MakeBuf_CollectStateDataBySerial(TSDeviceInfo *pDevice,TSCmdBuffer *pBuffer,unsigned char *SerialNo)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	ucCommandByte = 0x8A;
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

