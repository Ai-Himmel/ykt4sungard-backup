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
	pDocEx->pChildDoc[0]->m_dwTryCount = GetTickCount();

	MakeBuf_CollectData(pDocEx->pDeviceInfo, pBuffer);
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


	//���ճɹ�ͳ��
	InterlockedExchangeAdd((LONG*)&gSendRecv, (LONG)(GetTickCount()- pDocEx->pChildDoc[pDocEx->nPortNo]->m_dwLastTick));
	InterlockedIncrement((LONG*)&gTrySendRecv);

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
			unsigned char ucRawData[256];
#ifdef __DEBUG_OUTPUT__
			/*for(int i=0; i< 256; i++)
			{
				printf("%02X ", pBuffer->pBuffer[i]);
			}
			printf("\n");*/
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
//	printf("����LPORT%.8X����\n",pDocEx->pChildDoc[0]->m_nAuthID);
	unsigned char ucRawData[256];
	int nTotalPortNo, nPortNo;
	
	memset(ucRawData, 0, sizeof(ucRawData));

	memcpy(ucRawData, &pBuffer->pBuffer[4], pBuffer->pBuffer[3]);
#ifdef __DEBUG_OUTPUT__
	for(int i=0; i< 256; i++)
	{
		printf("%02X ", pBuffer->pBuffer[i]);
	}
	printf("\n");
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
			printf("1---ʵʱ�ռ�LPORT����ʱ,���صĶ˿����������ڲ����ڵĶ˿�����\n");
			ReportLog(pDocEx, pTask, RET_SYSERROR, "ʵʱ����", "�ռ�LPort����ʱ, ���ڷ��صĶ˿����������, ��λʱ����!");
		}

		return RET_SYSERROR;
	}
/*	LportState(pDocEx,pTask,pBuffer,ucRawData);
	if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		InterlockedIncrement((LONG*)&gNotFound);
		//Sleep(50);
		return RET_NG;
	}*/

	nTotalPortNo = ucRawData[2];
	nPortNo = ucRawData[3+nTotalPortNo];

	//�˿�������, ��λ
	if( nPortNo > nTotalPortNo )
	{
		printf("1---ʵʱ�ռ�LPORT����ʱ,���صĶ˿����������ڲ����ڵĶ˿�����\n");
		ResetDevice(pDocEx->pChildDoc[pDocEx->nPortNo], pBuffer);
		return RET_SYSERROR;
	}

	nPortNo = GetPos(pDocEx, nPortNo);

	pBuffer->nCmdSize = nTempLen;
	memset(pBuffer->pBuffer, 0, pBuffer->nBufferSize);
	memcpy(pBuffer->pBuffer, sTempData, 256);

	long nRet = RET_NG ;
	switch(GetMacDataType(pBuffer))
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
					TSSmartDoc doc;

					//��������������
					if( FindMachine(szDataReg, &doc) )
						nType = GetMachineType(&doc);
				}
			}
		}
		nType = GetMachineType(pDocEx->pChildDoc[nPortNo]);

		switch( nType) 
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
		nRet = Process_StateData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],pDocEx->nPortNo);
		break;
	case MACDATA_TYPE_BZ://Ϊ��������
		nRet = Process_AssisData(pDocEx,pTask,pBuffer,&ucRawData[5+nTotalPortNo],nPortNo);
		break;
	default:
		break;
	}
		LportState(pDocEx,pTask,pBuffer,ucRawData);
	/*if( !LportState(pDocEx,pTask,pBuffer,ucRawData) )
	{
		InterlockedIncrement((LONG*)&gNotFound);
		Sleep(50);
		//printf("����LPORT%.8X״̬����\n",pDocEx->pChildDoc[0]->m_nAuthID);

		return RET_NG;
	}*/
	Sleep(100);
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
				printf("���������ݱ�־ʧ��!\n");
				Sleep(30);
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
						//���ճɹ�ͳ��
						InterlockedExchangeAdd((LONG*)&gMark, (LONG)(GetTickCount()-dwTick));
						InterlockedIncrement((LONG*)&gTryMark);
						return true;
					}
				}
			}
			else
			{
				printf("���������ݱ�־���ɹ�!\n");
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
			printf("!!!!�豸%s,�˿ں�%dע��Ų���\n",pDocEx->pChildDoc[0]->m_szDeviceID, i+1);
			bFlag2 = false;
			break;
		case 0x0c://�ն��豸����Ӧ
			break;
		case 0x0d://����ǩ��
			{
			printf("-----�豸%sPort=%d����ǩ��\n", pDocEx->pChildDoc[0]->m_szDeviceID, i+1);			
			strText.Format("�˿�%d����ǩ��!", i+1);
			ReportLog(pDocEx->pChildDoc[0], pTask, RET_OK, "ʵʱ����", strText.GetBuffer(0));

			CSingInServer  SingIn;
			SingIn.SignInProcess(pDocEx, pBuffer, i+1, pTask);
			bFlag2 = true;
			}
			break;
		case 0x0e://��������Ч�ڹ���
  	      printf("!!!!��������Ч�ڹ���\n");
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
	CSmartSRCSFTable  SRCTable;
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	CString strText;

	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	nFlowNo = ucFlowNo[0]*256+ucFlowNo[1];
	printf("nPortNo = %d ������ˮ=%d\n",nPortNo,nFlowNo);
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
		if( ucRawData[25] == 0x30 )
			nType = 0x07 ;
		else
			nType = 0x06 ;
	}

	char szStatus[64];
	long nTick = GetTickCount();

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "����ɹ�!");
	}
	else
	{
		printf("!!!!���ݽ������ݸ����˴�ʧ��,�ظ��ռ�����!!!!\n");
		strcpy(szStatus, "����ʧ��!û�������!�ظ��ռ�����!");
	}

	WriteLog("������ˮ��%d, ��ʼ����ʱ���:%ld, ����ʱ��(����):%d, ����ʱ��(����):%d, �����ܺķ�ʱ��(����):%d. ״̬:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);
		
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

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x02, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	}
	else
	{
		printf("!!!!���ݽ������ݸ����˴�ʧ��,�ظ��ռ�����!!!!\n");
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

		char  szStuNo[22];
		memset(szStuNo, 0, sizeof(szStuNo));
		sprintf(szStuNo,"%.2X%.2X%.2X%.2X%.2X",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);
	
		memset(AccountNum,'0',17);
		
		unsigned char Password[17];
		memset(Password, 0, sizeof(Password));
		memcpy(Password,ucRawData+13,8);

		unsigned char c_key[32];
		memset(c_key,'9',16);

		unsigned char PlainPin[32];
		memset(PlainPin,0,32);
		
		//�������� PlainPin
		Smart_CardDes(AccountNum,c_key,PlainPin,Password,'d');

		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);

		TSGSJRecord  Data;
		memset(&Data, 0, sizeof(Data));

		int t = 0 ;
		for(int k=0; k<20; k++)
		{
			if( szStuNo[k] != 'F' )
				Data.szShowID[t++] = szStuNo[k];
		}

		sprintf(Data.szDeviceID, "%.2X.2X.2X.2X", ucRawData[0], ucRawData[1], ucRawData[2],ucRawData[3]);

		strcpy(Data.szDeviceID, pDocEx->pChildDoc[nPortNo]->m_szDeviceID);
		//strcpy(Data.szPassword, (char*)PlainPin);
		sprintf(Data.szPassword,"%.2X%.2X%.2X",ucRawData[13],ucRawData[14],ucRawData[15]);
		sprintf(Data.szCRC, "%.2X%.2X", ucRawData[26], ucRawData[27]);
		Data.nCardID = ucRawData[6]*256+ucRawData[7];
		sprintf(Data.szSerial,"%d", ucRawData[4]);
		
		printf("�ն��豸ID��:%.2X%.2X%.2X%.2X\n",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]);
		printf("ͨѶ�汾��:%.2X\n",ucRawData[4]);
		printf("��������ԭ��:%.2X\n",ucRawData[5]);
		printf("������ˮ��:%.2X%.2X\n",ucRawData[6],ucRawData[7]);
		printf("��ʾ����:%.2X%.2X%.2X%.2X%.2X\n",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]);
		printf("��������:%.2X%.2X%.2X\n",ucRawData[13],ucRawData[14],ucRawData[15]);
		printf("����:%.2X%.2X%.2X\n",ucRawData[16],ucRawData[17],ucRawData[18]);
		printf("ʱ��:%.2d%.2d%.2d%.2d%.2d%.2d\n",ucRawData[19],ucRawData[20],ucRawData[21],
			                                     ucRawData[22],ucRawData[23],ucRawData[24]);
		if(ucRawData[25] == 0xFC)
		{
			printf("------��ʧ����: ѧ��:%s, ����:%s. \n", Data.szShowID, Data.szPassword);
			

		}
		else
			printf("------�������: ѧ��:%s, ����:%s. \n", Data.szShowID, Data.szPassword);

		if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], nType, (unsigned char*)&Data, sizeof(Data)) != RET_OK )
		{
			printf("���˴ﷵ�ز�ͬ��\n");
			ConfirmLost(nPortNo, ucRawData, 0xFF);
			return RET_SYSERROR;
		}
		else
		{
			printf("���˴ﷵ��ͬ��\n");
			ConfirmLost(nPortNo, ucRawData, 0x00);
		}
	}
	else
	{
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
	//	ConfirmLost(nPortNo, ucRawData, 0xff);
	}

	return RET_OK;
}

//�������ʼ�¼
long CCollectionData::Process_StateData(TSSmartDocEx *pDocEx,TSSmartTask *pTask,TSCmdBuffer *pBuffer,unsigned char *ucRawData,int nPortNo)
{
	unsigned char ucFlowNo[2];
	int  nFlowNo;
	//CString strText;
	OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256);
	//printf("nPortNo = %d ������ˮ=%d\n",nPortNo,ucRawData[6]*256+ucRawData[7]);
	ucFlowNo[0] = ucRawData[6]; 
	ucFlowNo[1] = ucRawData[7];
	
	for(int i=0; i<3; i++)
	{
		if( GetMachineType(m_pDocEx->pChildDoc[m_pDocEx->nPortNo]) == MACHINE_TYPE_5301)
			MakeBuf_ConfirmData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
		else
			MakeBuf_ConfirmStateData(&pDocEx->pChildDoc[nPortNo]->DeviceInfo, pBuffer, ucFlowNo);
			
			/*printf("%.2X%.2X%.2X%.2X%.2X%.2X%.2X\n",pBuffer->pBuffer[0],
				pBuffer->pBuffer[1],
				pBuffer->pBuffer[2],
				pBuffer->pBuffer[3],
				pBuffer->pBuffer[4],
				pBuffer->pBuffer[5],
				pBuffer->pBuffer[6]);*/
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
				//printf("�����ʼ�¼ʧ��\n");
				Sleep(100);
			}
	}
	return RET_OK;
	
	CSmartJZSRCTable  SRCTable;
	//unsigned char ucFlowNo[2];
	//int  nFlowNo;
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

	char szStatus[64];
	long nTick = GetTickCount();
	//modified by lina 20050403
	//CRC���
	OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256);
	if(nFlowNo == 0xFFFF)
		pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
	else
		pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;
		
	ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
	/*if( OutputRealData(pTask, pDocEx->pChildDoc[nPortNo], 0x03, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;
		
		ConfirmJZData(pDocEx, pTask, pBuffer, ucFlowNo, pDocEx->nPortNo, 3);
		//ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "����ɹ�!");

	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
		strcpy(szStatus, "����ʧ��!û�������!�ظ��ռ�����!");
	}*/

	WriteLog("������ˮ��%d, ��ʼ����ʱ���:%ld, ����ʱ��(����):%d, ����ʱ��(����):%s, �����ܺķ�ʱ��(����):%d. ״̬:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);

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

	if( nPortNo > 0 )
	{
		pDocEx->pChildDoc[nPortNo]->m_dwTryCount = m_pDocEx->pChildDoc[0]->m_dwTryCount;
	}

	char szStatus[64];
	long nTick = GetTickCount();

	if( OutputRealData(pTask, pDocEx->pChildDoc[0], 0x04, ucRawData, 256) == RET_OK )
	{
		//����ȷ������,���ɹ�����3��
		if(nFlowNo == 0xFFFF)
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo = 0x0000;
		else
			pDocEx->pChildDoc[nPortNo]->m_wFlowNo += 1;

		strcpy(pDocEx->pChildDoc[nPortNo]->m_sLastDealTime, SRCTable.sDealDateTime);
		ConfirmData(pDocEx,pTask,pBuffer,ucFlowNo,pDocEx->nPortNo, 3);
		strcpy(szStatus, "����ɹ�!");
	}
	else
	{
		printf("����ʧ��, û�������, �ظ��ռ�����!!!!\n");
		strcpy(szStatus, "����ʧ��!û�������!�ظ��ռ�����!");
	}

	WriteLog("������ˮ��%d, ��ʼ����ʱ���:%ld, ����ʱ��(����):%d, ����ʱ��(����):%s, �����ܺķ�ʱ��(����):%d. ״̬:%s.", 
		nFlowNo, pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		nTick - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, 
		GetTickCount() - nTick, 
		GetTickCount() - pDocEx->pChildDoc[nPortNo]->m_dwTryCount, szStatus);

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
		printf("1---ʵʱ�ռ�LPORT����ʱ,���ص�״ֵ̬����!!!!\n");
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
	return true;
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



	GetSmartDocInfo(szDataReg, pDoc);
	pDoc->m_nLevel = 1;
	pDoc->m_szLevelArray[0] = (char)pDocEx->pChildDoc[0]->m_nMachineNo;
	pDoc->m_szLevelArray[1] = nPort;

	AddNewSmartDoc(pDocEx->pChildDoc[0]->m_nAuthID, nPort, pDoc);

	return true;
}

bool CCollectionData::GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc)
{
	

	return true;
}

//��ʧ/���ʱ����������
bool CCollectionData::PostBlackCard(int nflag, long nDatabase, long nCardID)
{
	return true;
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
