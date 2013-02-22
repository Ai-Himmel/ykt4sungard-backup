////////////////////////////ʱ�ӹ���///////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"
#define   CMD_SETCLOCK	0xA9
#define   CMD_GETCLOCK  0xAA
/// ���ܣ�����ʱ��
/// ���룺������ʱ��������
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
	pBuffer->pBuffer[10]=(byte)tmptr->tm_wday; //����
	
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

//���ܣ���ȡʱ��  ע�⣺��ָ���ʱ��������
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

/********************************��ʧ��ȷ�Ϲ���*********************************/
#define CMD_LOST	0xC8
//���ܣ�ȷ�Ϲ�ʧ������ 
//������Buffer 3�ֽ� 
//			��ˮ��					2�ֽ�
//			��� 0---ok	0xff err	1�ֽ�	
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

