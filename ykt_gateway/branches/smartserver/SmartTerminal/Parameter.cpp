///////////////////////��������////////////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"

#define CMD_SETTERMINAL_MAINPAR			0xB7	//����������(�ն��豸)
#define CMD_GETTERMINAL_MAINPAR			0xBF   //��ȡ������(�ն��豸)
#define CMD_GETNET_MAINPAR				0x10   //��ȡ������(�����豸)
#define CMD_DEBUG_GETTERMINAL_MAINPAR	0xB8   //���Ի�ȡ������(�ն��豸)
#define CMD_DEBUG_GETNET_MAINPAR        0xF0   //���Ի�ȡ������(�����豸)	


/// ���ܣ�����������
/// ���룺*mainpar 28�ֽ�
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

/// ���ܣ���ȡ������
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

/// ���ܣ����Ի�ȡ������(����ע���)
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

/// ����:����ע���
/// ����:*regno---4�ֽ�ע���
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


///////////////////////////////�շ��ศ������////////////////////////////////////

/// 1��ʱ��ι���
#define CMD_SFJ_SET_TIMEPHASE	0xAB
#define CMD_SFJ_GET_TIMEPHASE   0xAC
/// ���ܣ�����ʱ���
/// ������
///    No   ---- ʱ���������
///    Time ---  ���մ���
///    Buffer--- no*10 ʱ��β���
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

/// ���ܣ���ȡʱ��β���
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


/// 2.��Ź���
#define CMD_SFJ_SET_FASTNO			0xAD	//�´���ݱ��
#define CMD_SFJ_GET_FASTNO			0xAE	//�ϴ���ݱ��
#define CMD_SFJ_SET_CONSUMENO		0xB3	//�´����ѱ��
#define CMD_SFJ_DEL_COMSUMENO		0xB4	//ɾ�����ѱ��
#define CMD_SFJ_GET_CONSUMEVERSION	0xB6	//�ϴ����ѱ�Ű汾	
#define CMD_SFJ_SET_CONSUMEVERSION  0xB5	//�´����ѱ�Ű汾	

/// ���ܣ��´���ݱ��
/// ������
///   No:�������(1�ֽ�)
///   Buffer:3*No�������
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

/// ���ܣ��ϴ���ݱ��
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

/// ����:�´����ѱ��
/// ����:
///    Flag:ȫ��/����ӱ��(1�ֽ�)
///    No:  �����(1�ֽ�)
///    Buffer:N*3�ֽڱ��
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

/// ���ܣ�ɾ�����ѱ��
/// ����:
///   No:�������
///   Buffer:N*3�ֽڱ��
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

/// ���ܣ��ϴ����ѱ�Ű汾
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

/// ����:�´����ѱ�Ű汾	
/// ������
///  Buffer:���ѱ�Ű汾(6�ֽ�)
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


/// 3 ��Ƭ��������
#define CMD_SETDIRSECTOR		0x65	//���ÿ�ƬĿ¼������
#define CMD_GETDIRSECTOR		0x64    //��ȡ��ƬĿ¼������
#define CMD_SETV10PACKETSECTOR	0xDA    //����V10��ƬǮ�����ڵ�����
#define CMD_GETV10PACKETSECTOR	0xDD	//��ȡV10��ƬǮ�����ڵ�����
#define CMD_SETV10PASSWORD		0xD5	//�´�V10����λ����

/// ���ܣ����ÿ�ƬĿ¼������
/// ������Sector---��ƬĿ¼������
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

/// ���ܣ����ÿ�ƬĿ¼������
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

/// ���ܣ�����V10��ƬǮ�����ڵ����� 
/// ������Sector --- ������
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

/// ���ܣ���ȡV10��ƬǮ�����ڵ�����
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

/// ����:�´�V10����λ����
/// ������Password(2�ֽ�,��λ��ǰ)
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


/// 4 ���ʲ�������
#define	CMD_GETSTATETIMETABLE	0x84	//�ϴ���ʱ����ʱ���
#define CMD_SETSTATETIMETALBE	0x85	//�´���ʱ����ʱ���
#define CMD_STATE               0x89	//��λ��Ҫ������
#define CMD_RESTATE				0x87	//��������

/// ����:�ϴ���ʱ����ʱ���
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

/// ���ܣ��´���ʱ����ʱ���
/// ������
///    No:��ʱ����������
///    Buffer:��ʱ����ʱ����� ʱ��Ϊ1��
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

/// ���ܣ���λ��Ҫ������
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

/// ���ܣ���λ��Ҫ�󸴺�����
/// ������
///      SerialNo��Ҫ�󸴺�������ˮ��
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

/// 5 ǩ������
#define CMD_SETCONSUMEFLAG	0x9F	//�������ѹ��ܿ�����ر�
#define CMD_SETSIGNINTIME	0x82	//���ö�ʱǩ��ʱ��
#define CMD_SETWORKINGKEY   0x83	//���ù�����Կ���㷨���

/// ���ܣ��������ѹ��ܿ�����ر�
/// ������
///    Flag --- 1 ����
///    Flag --- 0 �ر�
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

/// ���ܣ����ù�����Կ���㷨���
/// ������
///     *Plain ------ ��Կ���� 9�ֽ�
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

/// 6 ���ѽ���޶�
#define	CMD_GETLARGECONSUMEMONEY	0xCB	//��ȡ��������޶�
#define CMD_SETLARGECONSUMEMONEY    0xCA	//������������޶�

/// ���ܣ���ȡ��������޶�
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

/// ���ܣ�������������޶�
/// ������
///     Money:3�ֽڽ���λ��ǰ
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

//����:��������������޶�
//����:
//    Money: 4�ֽڽ���λ��ǰ
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

//����:��ȡ����������޶�
//����:
//    Money: 4�ֽڽ���λ��ǰ
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



/// 7 �������
#define CMD_SETMANAGEPASSWORD	0xD6	//����ϵͳ����Ա����

/// ���ܣ�����ϵͳ����Ա����
/// ������
///     Password:����(3�ֽ� BCD��)
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

