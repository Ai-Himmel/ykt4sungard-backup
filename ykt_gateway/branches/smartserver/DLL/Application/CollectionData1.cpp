 // CollectionData.cpp: implementation of the CCollectionData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Application.h"
#include "CollectionData.h"
#include "SRCTable.h"
#include "JZSRCTable.h"
#include "SmartTask.h"
#include "SingInServer.h"
#include "CheckBlackVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long iCount = 0 ;
DWORD dwLastTime = 0 ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCollectionData::CCollectionData()
{
	m_bMarkCheck = true ;
	m_strTaskCode = "01";
}

CCollectionData::~CCollectionData()
{

}

long CCollectionData::CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	pDocEx->pChildDoc[pDocEx->nPortNo]->m_dwLastTick = GetTickCount();
	MakeBuf_CollectData(pDocEx->pDeviceInfo, pBuffer);

	pDocEx->pChildDoc[0]->m_dwTryCount = GetTickCount();

	return RET_OK;
}

//*----------------------------------------------------------------------------
//*����: long ProcessRequest()
//*����: ��������ҵ������
//*����: ��
//*����: ��ϵͳ����ֵ˵��
//*˵��: 
//*----------------------------------------------------------------------------
long CCollectionData::ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	int nIndex = m_pDocEx->nPortNo ;
	long nRet = RET_NG;

	switch(GetMachineType(m_pDocEx->pChildDoc[nIndex]))
	{
	case MACHINE_TYPE_5301://������
		nRet = LPort_Process(pDocEx,pTask,pBuffer);
		break;
	case MACHINE_TYPE_0201://��ֵ��
	case MACHINE_TYPE_0226://�շѻ�
	case MACHINE_TYPE_0228://���ػ�
	case MACHINE_TYPE_0230://�����
	case MACHINE_TYPE_0232://�ϻ�������
	case MACHINE_TYPE_0234://��ԡ�����
	case MACHINE_TYPE_0240://��Ʊ��
	case MACHINE_TYPE_0130://���ʶ���
	case MACHINE_TYPE_0140://��Ʊ��
		{
#ifdef __DEBUG_OUTPUT__
/*			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");*/
#endif
			unsigned char ucRawData[256];
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("����%d����ǩ��!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_DealTypeData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	case MACHINE_TYPE_0121://��ʱ��
		{
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");
#endif
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("����%d����ǩ��!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_IdentifyData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	case MACHINE_TYPE_0224://��ʧ��
		{
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");
#endif
			memset(ucRawData, 0, sizeof(ucRawData));
			switch(pBuffer->pBuffer[2])
			{
			case 0x17:
				if( ReadJZRecord(pDocEx, pTask, pBuffer) )
				{
					memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
					nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				}
				else
					nRet = RET_NG;
				break;
			case 0x0D:
				{
				CString strText;
				strText.Format("����%d����ǩ��!", pDocEx->pChildDoc[pDocEx->nPortNo]->m_nAuthID);
				ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));

				CSingInServer  SingIn;
				SingIn.SignInProcess(pDocEx, pBuffer, 0, pTask);
				break;
				}
			case 0x00:
				memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
				nRet = Process_GSJData(pDocEx,pTask,pBuffer,&ucRawData[0], 0);
				break;
			default:
				nRet = RET_NG;
				break;
			}
		}
		break;
	default:
		break;
	}

	return nRet;
}

//*----------------------------------------------------------------------------
//*����: long LPort_DataProcess(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer)
//*����: ��������ҵ������
//*����: ��
//*����: ��ϵͳ����ֵ˵��
//*˵��: 
//*----------------------------------------------------------------------------
long CCollectionData::LPort_Process(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer)
{
	printf("bbbbb\n");

	unsigned char ucRawData[256];
	int nTotalPortNo=24, nPortNo=0;
	
	memset(ucRawData, 0, sizeof(ucRawData));

	memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
#ifdef __DEBUG_OUTPUT__
/*	for(int i=0; i< 256; i++)
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");*/
#endif

	int nTempLen = pBuffer->nCmdSize ;
	unsigned char sTempData[256];
	memcpy(sTempData, pBuffer->pBuffer, 256);

	//�����ڶ˿�����
	if( ucRawData[2] != pDocEx->pChildDoc[pDocEx->nPortNo]->m_nPortCount )
	{
		CString strString;

		strString.Format("�ռ�LPort����ʱ, ���صĶ˿����������ݿ�˿����������. ���صĶ˿���Ϊ:%d, ������Ϊ:%d! ����LPort�������ò���ȷ, ������У��LPort�Ĳ���", 
			ucRawData[2], pDocEx->pChildDoc[0]->m_nPortCount);
		ReportLog(pDocEx, pTask, RET_SYSERROR, "ʵʱ����", strString.GetBuffer(0) );

		if( !ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) )
		{
			ReportLog(pDocEx, pTask, RET_SYSERROR, "ʵʱ����", "�ռ�LPort����ʱ, ���ڷ��صĶ˿����������, ��λʱ����!");
		}

		return RET_SYSERROR;
	}

	if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		return RET_NG;
	}

	nTotalPortNo = ucRawData[2];
	nPortNo = ucRawData[3+nTotalPortNo];

	//�˿�������, ��λ
	if( nPortNo > nTotalPortNo )
	{
		ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer);
		return RET_SYSERROR;
	}

	nPortNo = GetPos(pDocEx, nPortNo);

	pBuffer->nCmdSize = nTempLen;
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(pBuffer->pBuffer, sTempData, 256);

	long nRet = RET_NG ;
	switch(GetMacDataType(pBuffer)) //GetMacDataType(pBuffer))
	{
	case MACDATA_TYPE_JY://Ϊ������������
		{
		int nType = MACHINE_TYPE_5301 ;

		if( nPortNo < 0 )
		{
			char szDataReg[32];
			sprintf(szDataReg, "%.2X%.2X%.2X%.2X", ucRawData[5+nTotalPortNo],ucRawData[6+nTotalPortNo],ucRawData[7+nTotalPortNo],ucRawData[8+nTotalPortNo]);
			if( nPortNo < 0 )
			{
				//�Ƿ��ڱ���������
				int iPos = GetPos(pDocEx, szDataReg);
				if( iPos > 0 )
				{
					nPortNo = iPos;
				}
				else
				{
					nPortNo = 0 ;
					/*
					TSSmartDoc doc;

					//��������������
					if( FindMachine(szDataReg, &doc) )
						nType = GetMachineType(&doc);
						*/
				}
			}
		}

		switch(GetMachineType(pDocEx->pChildDoc[nPortNo])) 
		{
		case MACHINE_TYPE_5301://������
		case MACHINE_TYPE_0201://��ֵ��
		case MACHINE_TYPE_0226://�շѻ�
		case MACHINE_TYPE_0228://���ػ�
		case MACHINE_TYPE_0230://�����
		case MACHINE_TYPE_0232://�ϻ�������
		case MACHINE_TYPE_0234://��ԡ�����
		case MACHINE_TYPE_0240://��Ʊ��
		case MACHINE_TYPE_0130://���ʶ���
		case MACHINE_TYPE_0140://��Ʊ��
			nRet = Process_DealTypeData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		case MACHINE_TYPE_0121://��ʱ��
			nRet = Process_IdentifyData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		case MACHINE_TYPE_0224://��ʧ��
			nRet = Process_GSJData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
			break;
		default:
			break;
		}
		}
		break;
	case MACDATA_TYPE_ZZ://Ϊ��������
		nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	case MACDATA_TYPE_BZ://Ϊ��������
		nPortNo = 0;
		nRet = Process_AssisData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	default:
		break;
	}

	return nRet;
}

bool CCollectionData::ConfirmJZData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, 
								    unsigned char *ucFlowNo,int nPortNo,int nRetryNo)
{
	if( !strcmp(pDocEx->pChildDoc[0]->m_szMacCode, "5301") )
	{
		return ConfirmData(pDocEx, pTask, pBuffer, ucFlowNo, nPortNo, nRetryNo);
	}
	else
	{
		for(int i=0; i<nRetryNo; i++)
		{
			MakeBuf_ConfirmStateData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
			if( SendRequest(pDocEx->pChildDoc[nPortNo], pBuffer) == RET_OK )
			{
				//����ǳɹ����˳�
				if( UnMakeDeviceBuffer(pBuffer) == RET_OK && 
					pBuffer->pBuffer[2]==0x00 ) 
				{
					return true;
				}
			}
			else
			{
				Sleep(1000);
			}
		}
	}

	return false;
}

//ȷ��������������
bool CCollectionData::ConfirmData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, 
								    unsigned char *ucFlowNo,int nPortNo,int nRetryNo)
{
	DWORD dwTick = GetTickCount();

	for(int i=0; i<nRetryNo; i++)
	{
		MakeBuf_ConfirmData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);

		if( SendRequest(pDocEx->pChildDoc[nPortNo], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK ) 
			{
				//if(pBuffer->pBuffer[1] == pDocEx->pChildDoc[nPortNo]->m_nMachineNo)
				{
					//����ǳɹ����˳�
					if(pBuffer->pBuffer[2]==0x00)
					{
						return true;
					}
				}
			}
			else
			{
				Sleep(1000);
			}
		}
		else
		{
			Sleep(1000);
		}
	}

	ReportLog(pDocEx->pChildDoc[nPortNo], pTask, RET_SYSERROR, "ʵʱ����", "�����ʧ��!");

	return false;
}

//���������״̬
// ����false ������Ҫ��һ������
// ����true  ������Ҫ��һ������
bool CCollectionData::LportState(TSSmartDocEx *pDocEx, TSSmartTask *pTask, 
								    TSCmdBuffer *pBuffer,unsigned char *ucRawData)
{
	CString strText = "";
	int nTotalNo;
	bool bFlag1,bFlag2;

	bFlag1 = false;
	bFlag2 = false;

	nTotalNo = ucRawData[2];

	//������������
	if( ucRawData[1] != 0x0a ) 
		bFlag1 = true; 
	
	for(int i=0;i<nTotalNo; i++ ) 
	{
		switch(ucRawData[3+i])
		{
		case 0x0a://�˿�������
			break;
		case 0x0b://�ն�ע��Ų�����
			strText.Format("�˿�%dע��Ų�����", i+1);
#if 0
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));
			ModifyRegisterEx(pDocEx, pBuffer, i+1);		
#endif
			bFlag2 = false;
			break;
		case 0x0c://�ն��豸����Ӧ
			break;
		case 0x0d://����ǩ��
			printf("Port=%d, ����ǩ��!\n", i+1);
#if 0
			printf("AuthID=%d, Port=%d, The SingIn Server!\n", pDocEx->pChildDoc[0]->m_nAuthID, i+1);			strText.Format("�˿�%d����ǩ��!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));

			CSingInServer  SingIn;
			SingIn.SignInProcess(pDocEx, pBuffer, i+1, pTask);*/
			bFlag2 = true;
#endif
			break;
		case 0x0e://��������Ч�ڹ���
			printf("��������Ч�ڹ���...........\n");
#if 0
			CCheckBlackVersion  Check;
			int nTemp = pDocEx->nPortNo ;
			pDocEx->nPortNo = GetPos(pDocEx, i+1);
			if( Check.ProcessCheck(pDocEx, pTask, pBuffer) != RET_OK )
			{
				pDocEx->nPortNo  = nTemp ;
				if(bFlag2 == false)
					bFlag2 = true;
			}
			else
				pDocEx->nPortNo  = nTemp ;
#endif
			break;
		case 0xFF://δ���ն�
			break;
		default://����״̬������
			strText.Format("�˿�%d״̬δ����!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_SYSERROR, "ʵʱ����", strText.GetBuffer(0));
			break;
		}
	}

	if(bFlag2 == true)
		return false;

	return bFlag1;
}

//����֧�����������ն��豸����
long CCollectionData::Process_DealTypeData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData, int nPortNo)
{
//	CSmartSRCSFTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("�˿�%d�Ƿ�!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	int nType = 0x01 ;
	if( !strcmp(pDocEx->pChildDoc[nPortNo]->m_szMacCode, "0201") )
	{
		static bool bFound = true;
		if( bFound )
			nType = 0x07 ;
		else
			nType = 0x06 ;

		bFound = !bFound;
	/*	if( ucRawData[25] == 0x30 )
			nType = 0x07 ;
		else
			nType = 0x06 ;*/
	}

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		//strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
	}
	return RET_OK;
}

//���������֤�����ն��豸����
long CCollectionData::Process_IdentifyData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	CSmartSRCJSBTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString  strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("�˿�%d�Ƿ�!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x02, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

	//	strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
	}

	return RET_OK;
}

//�����ʧ�����ն��豸ԭʼƾ֤����
//Ŀǰ������û���������������ҵ����ɺ��ڴ���û������
long CCollectionData::Process_GSJData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer, unsigned char *ucRawData, int nPortNo)
{
	CSmartSRCGSJTable  SRCTable;
	CString  cs;

	unsigned char ucFlowNo[32];
	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];

	//CRC���
	if( !CRCValid(ucRawData) )
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		ConfirmLost(nPortNo, ucRawData, 0xFF);
		return RET_DATACRC_ERROR;
	}

//	printf("The ��ʧ�����ն��豸ԭʼƾ֤����: Port:%d......\n", nPortNo);

	//�޸ĸ�������
	if( ucRawData[25] == 0xFD )
	{
		if( !ModifyPassword(pTask, pDocEx->pChildDoc[nPortNo], ucRawData) )
		{
			return RET_SYSERROR;
		}
		else
		{	
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_OK;
		}
	}
	//��ʧ���� or �������
	else if( ucRawData[25] == 0xFC || ucRawData[25] == 0xFB )
	{
		//�����Ϊ����
		unsigned char AccountNum[17];
		int nType;

		if(ucRawData[25] == 0xFC)
			nType = 0x81;
		else
			nType = 0x82;

		memset(AccountNum,'0',17);
		sprintf((char *)AccountNum,"%.2X%.2X%.2X%.2X%.2X",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);

		unsigned char Password[17];
		memset(Password, 0, sizeof(Password));
		memcpy(Password,ucRawData+13,3);//add by lina 20050308
		/*memcpy(Password,ucRawData+13,8);
		
		unsigned char c_key[32];
		memset(c_key,'9',16);
		*/
		unsigned char PlainPin[32];
		memset(PlainPin,0,32);
		
		//�������� PlainPin
		//Smart_CardDes(AccountNum,c_key,PlainPin,Password,'d');
        */ //DELETE BY LINA 20050308
		TSGSJRecord  Data;
		
		SVC_HEX_2_DSP(Password,PlainPin,3);//add by lina 20040305	
		
		memset(&Data, 0, sizeof(Data));
		Data.nCardID = 0;
		strcpy(Data.szDeviceID, pDocEx->pChildDoc[pDocEx->nPortNo]->m_szDeviceID);
		strcpy(Data.szPassword, (char*)PlainPin);
		strcpy(Data.szSerial, "");
		strcpy(Data.szShowID, (char*)AccountNum);
		WriteLog("����˴�����TSGJRecord��ϢΪ szDeviceID=%s nCardID=%d szShowID=%s nFlag=%d szPassword=%s szSerial=%s szCRC=%s",
			Data.szDeviceID,Data.nCardID,Data.szShowID,Data.nFlag,Data.szPassword,Data.szSerial,Data.szCRC);
		if( ReadCardGSInfo(nType, &Data) != RET_OK )
		{
			printf("������ʾ����:%s  ��������:%s  ���ݿ����벻��ͬ!!\n", AccountNum, PlainPin);
			WriteLog("������ʾ����:%s  ��������:%s  ���ݿ����벻��ͬ!!\n", AccountNum, PlainPin);
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			
			return false ;
		}

		printf("������ʾ����:%s  ��������:%s  ���ݿ�����:%s\n", AccountNum, PlainPin, Data.szPassword);
		WriteLog("������ʾ����:%s  ��������:%s  ���ݿ�����:%s\n", AccountNum, PlainPin, Data.szPassword);

		
		memset(&Data, 0, sizeof(Data));

		strcpy(Data.szDeviceID, pDocEx->pChildDoc[nPortNo]->m_szDeviceID);
		strcpy(Data.szPassword, (char*)PlainPin);
		strcpy(Data.szShowID, (char*)AccountNum);
		sprintf(Data.szCRC, "%.2X%.2X", ucRawData[26],ucRawData[27]);

		if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, (unsigned char*)&Data, sizeof(Data)) != RET_OK )
		{
			WriteLog("����ȶ���ȷ,�����˴ﲻ��������ʧ��Ҷ���");
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_SYSERROR;
		}
		else
		{
			WriteLog("����ȶ���ȷ,���˴���������ʧ��Ҷ���");
			ConfirmLost(nPortNo, ucRawData, 0x00);
			Sleep(100);
			ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
			return RET_OK;
		}
	}
	else
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	//	ConfirmLost(nPortNo, ucRawData, 0xff);
		printf("δ֪����������!\n");
	}

	return RET_OK;
}

//�������ʼ�¼
long CCollectionData::Process_StateData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	CSmartJZSRCTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( nPortNo < 0 || nPortNo >= pDocEx->nChildDoc )
	{
		printf("�˿�%d�Ƿ�!\n", nPortNo);
		nPortNo = pDocEx->nPortNo;
	}

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	//CRC���
	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
		//ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
	}

	return RET_OK;
}

//��������¼
long CCollectionData::Process_AssisData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData, int nPortNo)
{
	CSmartSRCBZTable  SRCTable;
	unsigned char ucFlowNo[2];
//	unsigned char out[32];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[8]; 
	ucFlowNo[1] = ucRawData[9];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];

	if( OutputRealData(pTask, pDocEx->pChildDoc[0], 0x04, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

	//	strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
	}

	return RET_OK;
}

//������һ������
long CCollectionData::InsertTask(TSSmartDoc *pDoc, long nTry, char *TaskCode)
{
	CSmartTask Task;
//	Task.SetMemo(nNumber);
	Task.SetTask("����ʷ��", "", 0, nTry);
	Task.AddAuthID(pDoc->m_nAuthID, TaskCode);

	if( !Task.Write() )
	{
		ReportLog(pDoc, m_pTask, RET_DBQUERYERROR, "ʵʱ����", "��������ʷ������ʧ��!");
		return RET_DBQUERYERROR;
	}
	else
	{
		printf("\n����ʱ, ��������ʷ������ɹ�!..............\n\n");
		ReportLog(pDoc, m_pTask, RET_OK, "ʵʱ����", "��������ʷ������ɹ�!");
		TerminateTask(2);
		return RET_OK;
	}
}

//MARKֵ��
bool CCollectionData::OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark)
{
	CString strText;

	switch(nMark)
	{
	case 0x0b: //��Ȩ�Ų���
		strText.Format("ʵʱ�ռ�ʱ����mark=ע��Ų���! ����Ϊ:%s. ���ڸ���ע���!", pBuffer->pBuffer, pBuffer->pBuffer[3]+7);
		ReportLog(pDoc, pTask, RET_SYSERROR, "ʵʱ����", strText.GetBuffer(0));
		return ModifyRegister(pDoc, pBuffer);
		break;
	case 0x05: //
		break;
	default:
		ResetDevice(pDoc, pBuffer);
		break;
	}
	return true;
}

void CCollectionData::OnCRCError()
{
	ReportLog(m_pDocEx, m_pTask, RET_SYSERROR, "ʵʱ����", "ʵʱ�ռ�ʱCRC��!");
	ClearPortData(m_pDocEx->pChildDoc[m_pDocEx->nPortNo], m_pBuffer, m_pDocEx->nPortNo);
}


bool CCollectionData::ConfirmLost(int nPortNo, unsigned char *ucRawData, unsigned char flag)
{
	unsigned char Buffer[32];

	Buffer[0] = ucRawData[6];
	Buffer[1] = ucRawData[7];
	Buffer[2] = flag;

	TSSmartDoc *pDoc = m_pDocEx->pChildDoc[nPortNo];

	for(int i=0; i<3; i++)
	{
		MakeBuf_ConfirmLost(&pDoc->DeviceInfo, m_pBuffer, Buffer);
		m_pBuffer->nTimeOut1 = 1500 ;
		m_pBuffer->nTimeOut2 = 200 ;
		if(SendRequest(pDoc, m_pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(m_pBuffer) == RET_OK && m_pBuffer->pBuffer[2]==0x00 )
			{
				return true;
			}
		}
		else
		{
			Sleep(100);
		}
	}

	return false;
}

//����ע��Ŷ�Ӧ���豸
bool CCollectionData::FindMachine(char *szDataReg, TSSmartDoc *pDoc)
{
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase > 0 )
	{
		CString strSQL;

		strSQL.Format("select * from smart_machine where smt_regno='%s' order by smt_status", 
			szDataReg);

		long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
		if( nRec > 0 )
		{
			if( MoveFirst(nRec) == RET_OK )
			{
				ZeroMemory(pDoc, sizeof(TSSmartDoc));

				GetFieldLongValueEx(nRec, "smt_authno", &pDoc->m_nAuthID);
				GetFieldStringValueEx(nRec, "smt_machineid", pDoc->m_szDeviceID);
				GetFieldStringValueEx(nRec, "smt_regno", pDoc->m_szRegister);
				GetFieldStringValueEx(nRec, "smt_machinecode", pDoc->m_szMacCode);

				CloseRecHandle(nRec);
				FreeDBHandle(nDatabase);

				return true;
			}
			CloseRecHandle(nRec);
		}
		FreeDBHandle(nDatabase);
	}
	return false;
}

//����һ̨�豸
bool CCollectionData::AddNewMachine(int nPort, char *type, TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, char *szDataReg, TSSmartDoc *pDoc)
{
	unsigned char szID[32];
	long nAuthID= 0;

	memset(szID, 0, sizeof(szID));

	bool bFound = false ;
	for( int p =0; p < 3; p++ )
	{
		MakeBuf_GetPortPar(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer, nPort);
		if( SendRequest(pDocEx->pChildDoc[0], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && !pBuffer->pBuffer[2] ) 
			{
				bFound = true;
				SVC_HEX_2_DSP(&pBuffer->pBuffer[4], szID, 4);
				break;
			}
		}
	}

	if( !bFound )
		return false;

	int nNo = pBuffer->pBuffer[8];
	strcpy(pDoc->m_szRegister, szDataReg);

	CString strSQL;
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
	{
		return false;
	}

	strSQL = "select SMART_MACHINE_SEQUENCE.nextval as seq from dual";
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	GetFieldLongValueEx(nRec, "seq", &nAuthID);
	CloseRecHandle(nRec);

	strSQL.Format("INSERT INTO SMART_MACHINE("
		"SMT_AUTHNO, SMT_MACHINEID, SMT_MACHINENO, "
		"SMT_PARENT_ID, SMT_PORTNO, SMT_COMADDR,"
		"SMT_IPADDR, SMT_MACHINECODE, SMT_STATUS, "
		"SMT_CHANGEDATE, SMT_COMMODE,smt_regno) VALUES(%d, '%s', %d, "
		"%d, %d, "
		"'%s', '%s', '%s', 0, "
		"SYSDATE, 3,'%s')", 
		nAuthID, szID, nNo, 
		pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDocEx->pChildDoc[0]->m_szPort,
		pDocEx->pChildDoc[0]->m_szAddr, type, szDataReg);
	if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
	{
		printf("%s\n", strSQL.GetBuffer(0));
		FreeDBHandle(nDatabase);
		return false;
	}

	strSQL.Format("INSERT INTO SMART_COMMREC(SMT_AUTHNO , SMT_LASTINVOICENO, SMT_DAILYCODE, SMT_DAILYNO) VALUES(%d, 0, 'M', 0)", nAuthID);
	if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	FreeDBHandle(nDatabase);

	GetSmartDocInfo(szDataReg, pDoc);
	pDoc->m_nLevel = 1;
	pDoc->m_szLevelArray[0] = (char)pDocEx->pChildDoc[0]->m_nMachineNo;
	pDoc->m_szLevelArray[1] = nPort;

	AddNewSmartDoc(pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDoc);

	return true;
}

bool CCollectionData::GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc)
{
	char sSQL[1600];
	char sWhere[256];

	//�õ����ݿ���
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
		return false;

	memset(sSQL, 0, sizeof(sSQL));
	sprintf(sWhere, " A.SMT_REGNO = '%s' ", pszRegNo);

	//���ն˼�¼��
	strcpy(sSQL, "SELECT A.SMT_AUTHNO , A.SMT_MACHINEID, A.SMT_MACHINENO, A.SMT_ORG_ID, A.SMT_LOCATIONCODE, ");
	strcat(sSQL, "   A.SMT_PARENT_ID, A.SMT_PORTNO, A.SMT_COMADDR, A.SMT_IPADDR, A.SMT_IPADDRDES, ");
	strcat(sSQL, "   A.SMT_BAUDRATE, A.SMT_MACHINEVER, A.SMT_PROGRAMVER, A.SMT_MACHINECODE, A.SMT_STATUS, ");
	strcat(sSQL, "   A.SMT_CHANGEDATE, A.SMT_COMMODE, A.SMT_COLLECTWAY, A.SMT_ONNET, A.SMT_ONLINE,");
	strcat(sSQL, "   A.SMT_Level, A.smt_levelarray, A.SMT_STATIONIP, A.SMT_DAILYCODE, A.SMT_DAILYNO, A.SMT_REGNO, A.SMT_SYSPWD,");
	strcat(sSQL, "   A.SMT_USECARD, A.SMT_CLASS, A.SMT_PORTCOUNT, ");
	strcat(sSQL, "   B.SMT_LASTINVOICENO, to_char(B.SMT_LASTDEALDATETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_LASTDEALDATETIME ,");
	strcat(sSQL, "   B.SMT_BEGININVOICE, B.SMT_SETTLEINVOICE, to_char(B.SMT_SETTLETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_SETTLETIME , ");
	strcat(sSQL, "   B.SMT_ENDINVOICE, B.SMT_BLACKEXPIRE, to_char(B.SMT_DOWNBLACKTIME, 'yyyymmdd hh24:mm:ss') as SMT_DOWNBLACKTIME , ");
	strcat(sSQL, "   B.SMT_STARTUSE, B.SMT_LOSTDEAL, B.SMT_LOSTSETTLEMENT, B.SMT_BLACKLISTVER, B.SMT_CLOCKVER, ");
	strcat(sSQL, "   B.SMT_NUMBERVER, to_char(B.SMT_COMMDATETIME, 'yyyy-mm-dd hh24:mm:ss') as SMT_COMMDATETIME ");
	strcat(sSQL, "FROM ");
	strcat(sSQL, "   SMART_MACHINE A, Smart_CommRec B ");
	strcat(sSQL, "WHERE ");
	strcat(sSQL, "   A.SMT_AUTHNO = B.SMT_AUTHNO(+) AND ") ;
	strcat(sSQL, sWhere);

	long nRec = ExecuteQuery(nDatabase, sSQL);
	if( nRec <= 0 )
	{
		FreeDBHandle(nDatabase);
		return false;
	}

	long nResult = MoveFirst(nRec) ;
	if( nResult != RET_OK )
	{
		CloseRecHandle(nRec);
		FreeDBHandle(nDatabase);
		return false;
	}

	while( IsEOF(nRec) == RET_NG )
	{
		GetFieldStringValueEx(nRec, "SMT_MACHINECODE", pDoc->m_szMacCode);	//�ն˻��ͺŴ���
		GetFieldStringValueEx(nRec, "SMT_CLASS", pDoc->m_szMacCard);		//����IC������

		GetFieldLongValueEx(nRec, "SMT_AUTHNO", &pDoc->m_nAuthID);			//��Ȩ��
		GetFieldStringValueEx(nRec, "SMT_MACHINEID", pDoc->m_szDeviceID);	//�豸ID
		GetFieldStringValueEx(nRec, "SMT_REGNO", pDoc->m_szRegister);		//ע���
		GetFieldLongValueEx(nRec, "SMT_MACHINENO", &pDoc->m_nMachineNo);	//����
		GetFieldStringValueEx(nRec, "SMT_MACHINEVER", pDoc->m_szVersion);	//�豸�汾��
		GetFieldStringValueEx(nRec, "SMT_PROGRAMVER", pDoc->m_szProgramver);//�ֿ����汾��
		GetFieldStringValueEx(nRec, "SMT_SYSPWD", pDoc->m_szPassword);		//ϵͳԱ����
		GetFieldStringValueEx(nRec, "SMT_OPRPWD", pDoc->m_szOprPasswd);		//����Ա����
		GetFieldLongValueEx(nRec, "SMT_PWDSwitch", (long*)&pDoc->m_nPwdswitch);	//���뿪��

		GetFieldLongValueEx(nRec, "SMT_PARENT_ID", &pDoc->m_nParentID);		//�ն˻��ͺŴ���

		GetFieldLongValueEx(nRec, "SMT_PORTCOUNT", (long*)&pDoc->m_nPortCount);		//�������˿�����
		GetFieldLongValueEx(nRec, "SMT_PORTNO", (long*)&pDoc->m_nSMTPort);		//�������˿ں�

		GetFieldStringValueEx(nRec, "SMT_COMADDR", pDoc->m_szPort);			//ͨѶ�˿�
		GetFieldLongValueEx(nRec, "SMT_BAUDRATE", &pDoc->m_nBaudRate);		//������
		GetFieldLongValueEx(nRec, "SMT_COLLECTWAY", &pDoc->m_nConnType);	//ͨѶ��ʽ
		GetFieldLongValueEx(nRec, "SMT_COMMODE", &pDoc->m_nCommMode);		//��·ģʽ
		GetFieldStringValueEx(nRec, "SMT_IPADDR", pDoc->m_szAddr);			//ͨѶ��ַ
		GetFieldLongValueEx(nRec, "SMT_ONNET", &pDoc->m_nOnNet);			//�Ƿ�����
		GetFieldLongValueEx(nRec, "SMT_ONLINE", &pDoc->m_nOnline);			//�Ƿ���������
 		GetFieldLongValueEx(nRec, "SMT_Level", (long*)&pDoc->m_nLevel);			//�豸����
		GetFieldStringValueEx(nRec, "SMT_LevelArray", pDoc->m_szLevelArray);//��������
		GetFieldLongValueEx(nRec, "SMT_STATUS", (long*)&pDoc->m_nStatus);	//�豸״̬
		
		GetFieldLongValueEx(nRec, "SMT_LASTINVOICENO", (long*)&pDoc->m_wFlowNo);	//������ˮ��
		GetFieldLongValueEx(nRec, "SMT_LASTINVOICENO", (long*)&pDoc->m_wLastInvoiceNo);	//�ն˽�����ˮ����ĩֵ
 		GetFieldStringValueEx(nRec, "SMT_LASTDEALDATETIME", pDoc->m_sLastDealTime);	//�ն˽���ʱ����ĩֵ

		GetFieldLongValueEx(nRec, "SMT_BEGININVOICE", (long*)&pDoc->m_nBeginInvoice);	//���ʵĿ�ʼ��ˮ
		GetFieldLongValueEx(nRec, "SMT_SETTLEINVOICE", (long*)&pDoc->m_wSettleinvoice);	//������ˮ����ĩֵ
		GetFieldStringValueEx(nRec, "SMT_DOWNBLACKTIME", pDoc->m_sSettleTime);			//����ʱ����ĩֵ
		GetFieldLongValueEx(nRec, "SMT_ENDINVOICE", (long*)&pDoc->m_wEndInvoice);	//���ʵĽ�����ˮ��
		
		GetFieldStringValueEx(nRec, "SMT_BLACKEXPIRE", pDoc->m_sBlackExpire);	//����������Ч��
		GetFieldStringValueEx(nRec, "SMT_DOWNBLACKTIME", pDoc->m_sDownBlackTime);	//�������´�ʱ����ĩֵ
		GetFieldLongValueEx(nRec, "SMT_STARTUSE", (long*)&pDoc->m_nStartuse);	//ǩ�����
		GetFieldLongValueEx(nRec, "SMT_LOSTDEAL", (long*)&pDoc->m_nLostDeal);	//�������ݶ�ʧ����
		GetFieldLongValueEx(nRec, "SMT_LOSTSETTLEMENT", (long*)&pDoc->m_nLostSettle);//�������ݶ�ʧ�ı���

		GetFieldStringValueEx(nRec, "SMT_BLACKLISTVER", pDoc->m_sBlackListVer);	//�������汾��
		GetFieldStringValueEx(nRec, "SMT_CLOCKVER", pDoc->m_sClockVer);	//ʱ�䵥�汾��
		GetFieldStringValueEx(nRec, "SMT_NUMBERVER", pDoc->m_sNumberVer);	//���ʽ�շѻ����ѱ�Ű汾
		GetFieldStringValueEx(nRec, "SMT_COMMDATETIME", pDoc->m_sCommDateTime);	//���һ���ռ����ݵ�����ʱ��

		break;
	}

	CloseRecHandle(nRec);
	FreeDBHandle(nDatabase);

	return true;
}

//��ʧ/���ʱ����������
bool CCollectionData::PostBlackCard(int nflag, long nDatabase, long nCardID)
{
	CSmartTask Task;
	char szText[32];
	char szBeginTime[24];

	GetCurDateTime(szBeginTime);

	if(!nflag) 
	{
		sprintf(szText,"%d", nCardID);
		Task.SetTask("��ʧ�������㲥", szBeginTime, 0, 1);
	}
	else
	{
		sprintf(szText,"-%d", nCardID);
		Task.SetTask("��Һ������㲥", szBeginTime, 0, 1);
	}

//	Task.SetMemo(szText);

	CString strSQL;
	strSQL = "SELECT SMT_AUTHNO FROM SMART_MACHINE WHERE SMT_STATUS IN(0,1) AND SMT_MACHINECODE <> '5301' ORDER BY SMT_AUTHNO ";
	long nRec = ExecuteQuery(nDatabase, strSQL.GetBuffer(0));
	if( nRec <= 0 ) 
		return false;

	long nAuthno=0;
	while( IsEOF(nRec) == RET_NG )
	{
		if( GetFieldLongValueEx(nRec, "SMT_AUTHNO", &nAuthno) == RET_OK )
		{
			Task.AddAuthID(nAuthno, "70");
		}
		MoveNext(nRec);
	}
	CloseRecHandle(nRec);

	return Task.Write();
}

//�ϴ�һ�����ʼ�¼
bool CCollectionData::ReadJZRecord(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
	bool bResult = false ;

	MakeBuf_CollectStateData(&pDocEx->pChildDoc[pDocEx->nPortNo]->DeviceInfo, pBuffer);

	for(int i=0; i< 3; i++)
	{
		if(SendRequest(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer) == RET_OK )
		{
			if( UnMakeDeviceBuffer(pBuffer) == RET_OK && pBuffer->pBuffer[2]==0x00 )
			{
				bResult = true ;
				break;
			}
		}
	}

	return bResult;
}
