///////////////////////��������///////////////////////////////////
#include "stdafx.h"
#include "SmartTerminal.h"

#define CMD_GETBLACK_USEFULLIFE		0x8D	//��Ч��   
#define CMD_SETBLACK_USEFULLIFE		0x8E 	
#define CMD_GETBLACK_VERSION		0xA8	//�汾
#define CMD_SETBLACK_VERSION		0xA7   //���ú������汾
#define CMD_BOARDBLACKNO			0xBE   //�㲥
#define CMD_CHECKBLACKCARDNO		0xBC   //��������
#define CMD_DOWNBLACKCARDNO			0xA4   //�´�������  
#define CMD_DELBLACKCARDNO			0xA5   //ɾ��������
#define CMD_DELALLBLACKCARDNO		0xA6   //ɾ�����к�����
#define CMD_GETALLBLACKCARDNO		0xDC   //�ϴ�������������	
#define CMD_RECOUNTALLBLACKCARDNO	0xDB   //����ͳ�ƺ�����������

#define CMD_DOWWHITECARDNO          0xAB   //�´�������
#define CMD_DELWHITECARDNO          0xAC   //ɾ��������
#define CMD_DELALLWHITECARDNO       0xAD   //�´�ɾ�����а�����
#define CMD_SETWHITE_VERSION		0xAE   //�´��������汾
#define CMD_GETWHITE_VERSION        0xAF   //�ϴ��������汾
#define CMD_CHECKWHITECARDNO		0xB0   //��������
#define CMD_BOARDWHITENO			0xB1   //�㲥������

#define CMD_SETWHITE_VERSION4		0xC7   //�´��������汾4
#define CMD_DOWWHITECARDNO4         0xC9   //�´�������4
#define CMD_DOWWHITECARDNO5         0x80   //�´�������5

#define CMD_SETASSISTANCEVER        10     //���ò��������汾
#define CMD_GETASSISTANCEVER		11     //��ȡ���������汾
#define CMD_SETASSISTLIST			12     //���ò�������
#define CMD_GETASSISTLIST           13     //��ȡ���������汾
#define CMD_CLEARALLASSISLIST       0x79   //������в�������
#define CMD_SETASSISTSTATE			0x78   //���ò������ܿ���
#define CMD_GETASSISTSTATE          0x77   //��ȡ�������ܿ���

#define CMD_SETINCFEERATE			0x73   //��ֵ����������
#define CMD_GETINCFEERATE			0x74   //��ֵ�����ʶ�ȡ

#define CMD_DOWNEXTCLASS			0x67	//�´����ӿ���
#define CMD_UPLOADEXTCLASS			0x68	//�ϴ����ӿ���
#define CMD_DOWNTIMEEXTCLASS		0x62	//�´�ʱ��ο���
#define CMD_UPLOADTIMEEXTCLASS		0x63	//�ϴ�ʱ��ο���

/// ���ܣ���ȡ��������Ч��
/// ��������
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

/// ���ܣ��´���������Ч��
/// ������date---���ӽں�������Ч�ڣ��ꡢ�¡��ա�ʱ���֡���)
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

/// ���ܣ��ϴ��������汾
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

/// ���ܣ��´��������汾
/// ������ *date ---- ���ӽں������汾
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

/// ���ܣ��㲥������
/// ������
///      pBuffer:������
///      Version:�汾��Ϣ 6�ֽ�BCD��
///      CardNo: ����     3�ֽ�
/// ���أ�
///      ͨ�Ű������峤��
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

/// ���ܣ���������
/// ������*CardNo	3�ֽڿ���
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

/// ���ܣ��´�������( ע�⣺һ��ֻ���´�һ��������)
/// ������ *CardNo 3�ӽڿ���
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

/// ���ܣ�ɾ��������(ע�⣺һ��ֻ��ɾ��һ��������)
/// ������ *CardNo 3�ӽڿ���
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

/// ���ܣ�ɾ�����к�����
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


/// ���ܣ��ϴ�����������
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

/// ���ܣ�����ͳ�ƺ�����������
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

/// ���ܣ��´�������(ע�⣺һ��ֻ���´�һ��)
/// ������ CardNo----3�ֽ�
/// Ver �� 1.0 ------ 20040227
/// Auth�� Lina
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

/// ���ܣ�ɾ��������(ע�⣺һ��ֻ��ɾ��һ��)
/// ������CardNo---3�ֽ�
/// Ver ��1.0 ------ 20040227
/// Auth��Lina
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

/// ���ܣ�ɾ�����а�����
/// Ver�� 1.0 ------ 20040227
/// Auth��Lina
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

/// ���ܣ��´��������汾
/// ������*date ---- ���ӽں������汾
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

/// ���ܣ��´��������汾4
/// ������*date ---- ���ӽں������汾4
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

/// ���ܣ��ϴ��������汾
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

/// ���ܣ���������
/// ������*CardNo	3�ֽڿ���
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

/// ���ܣ��㲥������
/// ������
///      pBuffer:������
///      Version:�汾��Ϣ 6�ֽ�BCD��
///      CardNo: ����     3�ֽ�
/// ���أ�
///      ͨ�Ű������峤��
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


/// ���ܣ����������汾�´�
/// ������
///   Buffer: 
///     �汾ʱ��:  6�ֽ�
///     ������:    2�ֽ�
///     �ܽ��:    4�ֽ�(��λ��ǰ)
///     ��Ǯ������:2�ֽ�
///     ��Ǯ�ܽ��:4�ֽ�(��λ��ǰ)
///     ��Ǯ������:2�ֽ�
///     ��Ǯ���:  4�ֽ�(��λ��ǰ)
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

/// ���ܣ����������汾�ϴ�
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

/// ���ܣ��´���������
/// ������*List
///       3�ֽڽ��׿���
///       2�ֽ�����
///       2�ֽڽ��(��λ��ǰ)
///       1�ֽڼӼ�Ǯ���(0---�ӣ�1---��)
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// ���ܣ��ϴ���������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// ���ܣ������������
/// Ver�� 1.0 ------ 20040228
/// Auth��Lina
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

#define CMD_SETASSISTSTATE			0x78   //���ò������ܿ���
#define CMD_GETASSISTSTATE          0x77   //��ȡ�������ܿ���

/// ���ܣ����ò������ܿ���
/// ������
/// switchflag ---00��
///            ---FF��
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// ���ܣ���ȡ�������ܿ���
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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


/// ��ֵ����������
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// ��ֵ�����ʶ�ȡ
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// �´����ӿ���
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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

/// �ϴ����ӿ���
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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


/// �´�ʱ��ο���
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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


/// �ϴ�ʱ��ο���
/// ������
/// Ver��1.0 ------ 20040228
/// Auth��Lina
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


