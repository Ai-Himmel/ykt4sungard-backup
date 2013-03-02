/*int flag;
	FILE *fp;
	CTime tm = CTime::GetCurrentTime();
	char filename[512],chTemp[512];
	
	GetCurrentDirectory(512,chTemp);
	sprintf(filename,"%s\\%s_%.2d%.2d%.2d.txt",chTemp,
					    pDevice->sRegNo, 
				        tm.GetYear(),tm.GetMonth(),tm.GetDay());
	fp = fopen(filename,"a+");
	fputs("�ռ�ԭʼ����\n",fp);
	for(flag=0;flag<pBuffer->nCmdSize;flag++)
	{
		sprintf(chTemp,"%.2X",pBuffer->pBuffer[flag]);
		fputs(chTemp,fp);
	}
	flag = VerifyBufferValid(pBuffer->pBuffer,pBuffer->nCmdSize);
	if(flag != RET_OK)
		fputs("CRC����\n",fp);
	else
		fputs("CRCʧ��\n",fp);
	fclose(fp); 
	return RET_OK;*/

#include "stdafx.h"
#include "SmartTerminal.h"
//////////////////////////////////////////////////////////////////////////////////////////
/// ���ܣ�Э������庯��
/// ������
///         pSmartPT   ���� Э��������ݿ�
/// ����ֵ��
///       ������ֵ����
//////////////////////////////////////////////////////////////////////////////////////////
int _stdcall GetSmartProtocolRule(TSSmartProtocol *pSmartPT)
{
	//Smart411Э��
	pSmartPT->PTHeadLen = 1;
	pSmartPT->PTHead[0] = 0xC2;
	pSmartPT->PTTailLen = 1;
	pSmartPT->PTTail[0] = 0xC3;
	pSmartPT->nLenOffset= 3;       //���ݰ�����ƫ��(0..n)
	pSmartPT->nLenSize  = 1;         //�����ֽ���(ĿǰΪ1)
	pSmartPT->nMinPKSize= 7;       //����̵ĳ���
	pSmartPT->nMaxPKSize= 256;       //�����ĳ���(0.���޳�)
	return RET_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////
/// ��    ��: -- �յ�����һ���ֺ�������У��, ����Ƿ�Ϸ���
/// ��    ��: 
///        pBuffer     --  ҪУ������ݿ�
///        nBufferSize --  ���ݿ鳤��
///
/// �� �� ֵ: 
///        ������ֵ����
///
/// ˵    ��:
///        ֻ����Э�����ȷ��,��������ݳ���, CRC�ȴ���
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

//ͨ�ú���: �豸��̬�����յ������շ���ȷ������SMART411Э�� 
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


////////////////////////�ն��豸ר��ָ��//////////////////////////////////////
//----------------------1����ʼ��-------------------------------------------//
//1.1�ָ��ն��豸Ϊ����״̬
//Ver1.0 --- 20040225 Auth:Lina
int _stdcall MakeBuf_SetTerminalToFactorySetting(TSDeviceInfo *pDevice, TSCmdBuffer *pBuffer)
{
	unsigned char ucRegNo[4],ucCommandByte;
	int           addr,len;

	if(pDevice->nHardware == 5301) //������
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

//1.2�������ݳ�ʼ��  �������: ������н��ʼ�¼�����������½��ʡ�
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

#define CMD_CLEARDATA	0x66 //������н�������

/// ���ܣ�������н�������
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

//1.3�������˿ڻָ�Ϊ����״̬ �������:�˿ڲ����ָ�Ϊ����״̬������ոö˿����д洢��¼
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
/// ���ܣ����ĳһ�˿�����
/// ������


/// ��    ��: -- �����ռ�������
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


///////////���ݽ����뷢��///////////////////////////////////////

/// ���ܣ�����ȷ��
/// ������FlowNo --- 2�ֽ���ˮ��
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

/// ����:����ˮ�ϴ��ն˽��׼�¼
/// ����:SerialNo ---- 2�ֽ���ˮ��
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

/// ����:�ϴ����ʼ�¼
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

/// ����:ȷ�����ʼ�¼
/// ����:FlowNo --- 2�ֽ���ˮ��
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

/// ����:����ˮ�ϴ����ʼ�¼
/// ������SerialNo ---- 2�ֽ���ˮ��
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

