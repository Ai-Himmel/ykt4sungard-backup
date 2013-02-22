////////////////////////////时钟管理///////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"
#define   CMD_SETCLOCK	0xA9
#define   CMD_GETCLOCK  0xAA
/// 功能：设置时钟
/// 输入：年月日时分秒星期
/// Ver1.0 ------ 20040226 Auth:Lina
int _stdcall MakeBuf_SetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *clock)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;
	static BYTE		buf[20];
	time_t 			timebuf;
	struct tm		*tmptr=NULL;	
	
	memset(buf, 0x00, sizeof buf );
	timebuf = time((time_t *) 0);
	tmptr   = localtime(&timebuf);	
	
	ucCommandByte = CMD_SETCLOCK;
	addr          = pDevice->nAddr;
	len           = 10;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],clock,6); 
	// add by dj 20070416 
	len++;
	if( tmptr->tm_wday == 0 )  tmptr->tm_wday=7;
	pBuffer->pBuffer[10]=(byte)tmptr->tm_wday; //星期
	
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

//功能：读取时钟  注意：该指令返回时不带星期
//Ver1.0 ------ 20040226 Auth:Lina
int _stdcall MakeBuf_GetClock(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_GETCLOCK;
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

/********************************挂失机确认管理*********************************/
#define CMD_LOST	0xC8
//功能：确认挂失机数据 
//参数：Buffer 3字节 
//			流水号					2字节
//			标记 0---ok	0xff err	1字节	
//Ver1.0 ------ 20040226 Auth:Lina
int _stdcall MakeBuf_ConfirmLost(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer,unsigned char *Buffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	ucCommandByte = CMD_LOST;
	addr          = pDevice->nAddr;
	len           = 7;
	SVC_DSP_2_HEX((unsigned char *)pDevice->sRegNo,ucRegNo,4);
	memcpy(pBuffer->pBuffer,ucRegNo,4);
	memcpy(&pBuffer->pBuffer[4],Buffer,3); 
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

