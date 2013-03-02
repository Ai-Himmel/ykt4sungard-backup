/////////////////////////////Lport�������///////////////////////////////////////

#include "stdafx.h"
#include "SmartTerminal.h"

//////////////////////////////�˿ڹ���/////////////////////////
#define CMD_SETPORTREGNOANDMACNO			0x40    //���������ĳ�˿�ע��ż�����
#define CMD_CLEARPORTDATA					0x41    //�˿����ݳ�ʼ��
#define CMD_SETPORTPARTOFACTORYSETTING      0x42    //�˿ڲ�����ʼ��
#define CMD_GETPORTPAR						0x43    //��������ĳ�˿ڲ���
#define CMD_SEARCHPORT						0x07	//�����˿�

/// ���ܣ����÷�����ĳ�˿�ע��ż�����
/// ������
/// PortNo    ----- 1BYTE   ��Ӧ�˿ں�
/// newRegNo  ----- 4BYTE   ��Ӧע���
/// MacNo     ----- 1BYTE   ��Ӧ����
/// ���������Lport�ö˿��������ݽ����
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

/// ���ܣ��˿����ݳ�ʼ��
/// ����:
///     PortNo------�˿ں�
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

/// ���ܣ��˿ڲ�����ʼ��(���˿�������Ϣ�ָ�Ϊ����״̬)
/// ������
///    PortNo ------ �˿ں�
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
 
/// ���ܣ���������ĳ�˿ڲ���
/// ������
///    PortNo ------ �˿ں�
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

/// ����:�����˿�
/// ������
///    PortNo ------ �˿ں�
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


///////////////////////////�˿���������//////////////////////////////////////////////////////
#define CMD_GETPORTTOTALNO	0x45  //��ȡ�˿�����
#define CMD_SETPORTTOTALNO  0x44  //���ö˿�����

//////////////////////////�绰�����������///////////////////////////////////////////////////////
#define	CMD_SETDIALPHONE	0x46	//������λ���绰����
#define CMD_GETDIALPHONE	0x47	//��ȡ��λ���绰����
#define CMD_SETDIALTIME		0x48	//���ö�ʱ����ʱ��

////////////////////////����//////////////////////////////////////////////////////////////////
#define CMD_GETLPORTMAINPAR				   0x10    //��ȡ������
#define CMD_SETLPORTNEWREGNO			   0x11    //����ע���
#define CMD_SETLPORTTOFACTORYSETTING       0x3d    //��ʼ��������
#define CMD_DEBUGGETLPORTMAINPAR		   0xf0    //�����ϴ�������

/// ����:��ȡLport������
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

/// ���ܣ�����ע���
/// ������
/// newRegNo ------ ��ע���
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

/// ���ܣ���ʼ��������
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

/// ���ܣ������ϴ�������������
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

#define CMD_ROMMOTERESET          0x01   //Զ�̸�λָ��

/// ���ܣ�Զ�̸�λ
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

