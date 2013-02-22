// TSmartDoc.cpp: implementation of the TSmartDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartDoc.h"
#include "TSmartServer.h"

#define MAX_TIMEOUT_TRY   10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartDocObj::TSmartDocObj()
{
	m_bShare	= false;
	m_nBusNo	= 0 ;
	m_hShare = NULL ;
	m_nTotal = 0 ;
	m_nBusTask = 0 ;

	m_hExecute = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetIOStatus(IO_Status_Free);
	SetPause(false);

	m_nIndex = 0 ;

	m_bEnable = true;

	m_bOpen = false ;
	m_nRecvTimeOut = 0 ;

	m_pTaskObj = NULL ;
	m_pServer = NULL ;
	m_bShare = false ;

	m_nRealIndex = 0 ;
	m_pRealTaskObj = NULL ;

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_nTerminate = 0 ;

	ZeroMemory(&m_ReadOver, sizeof(m_ReadOver));
	ZeroMemory(&m_WriteOver, sizeof(m_WriteOver));

	ZeroMemory(m_sBuffer, sizeof(m_sBuffer));
}

TSmartDocObj::TSmartDocObj(const TSSmartDoc *pDoc) 
{
	m_bShare	= false;
	m_nBusNo	= 0 ;
	m_hShare = NULL ;
	m_nTotal = 0 ;
	m_nBusTask = 0 ; 

	m_hExecute = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetIOStatus(IO_Status_Free);
	SetPause(false);

	m_bOpen = false ;
	m_bEnable = true;

	m_nIndex = 0 ;

	m_pTaskObj = NULL ;
	m_pServer = NULL ;
	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;
	ZeroMemory(&m_ReadOver, sizeof(m_ReadOver));
	ZeroMemory(&m_WriteOver, sizeof(m_WriteOver));

	AssignBy(pDoc);

	m_nTerminate = 0 ;

	ZeroMemory(m_sBuffer, sizeof(m_sBuffer));
}

TSmartDocObj::~TSmartDocObj()
{
	DestoryStack();
	ClearChildDoc();
	CloseHandle(m_hExecute);
	CloseHandle(m_hEvent);
}

void TSmartDocObj::SetReadOver(OVERLAPPED *pOver)
{
	m_ReadOver.hEvent = pOver->hEvent ;
	m_ReadOver.Internal = pOver->Internal;
	m_ReadOver.InternalHigh = pOver->InternalHigh ;
	m_ReadOver.Offset = pOver->Offset;
	m_ReadOver.OffsetHigh = pOver->OffsetHigh;
}

void TSmartDocObj::SetWriteOver(OVERLAPPED *pOver)
{
	m_WriteOver.hEvent = pOver->hEvent ;
	m_WriteOver.Internal = pOver->Internal;
	m_WriteOver.InternalHigh = pOver->InternalHigh ;
	m_WriteOver.Offset = pOver->Offset;
	m_WriteOver.OffsetHigh = pOver->OffsetHigh;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::SetFirstShare()
//*����: ��һ�������豸��ʼ��
//*����: ��
//*����: ��
//*˵��: ��ʼ�������ϵ��豸���õı������¼�
//*=================================================================================
void TSmartDocObj::SetFirstShare()
{
	m_pBus = this;

	m_bShare = true;
	m_nBusNo = 0 ;		//���豸�������ϵĵڼ����豸(0..255)
	m_nBusTask = 0; 
	m_nTotal = 1;

	m_hShare = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetEvent(m_hShare);
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::SetShare(TSmaretDocObj& Obj)
//*����: ���������豸��Ϣ
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::SetShare(TSmartDocObj& Obj)
{
	m_pBus = &Obj;
	m_pBus->m_nTotal++;
	m_bShare = true;
	m_nBusNo = m_pBus->m_nTotal-1; //���豸�������ϵĵڼ����豸(0..255)
}

void TSmartDocObj::GetInfo(long nAuthNo, TSDocInfo *pDocInfo)
{
	if( nAuthNo == 0 )
	{
		pDocInfo->m_nAuthID = m_nAuthID;
		pDocInfo->m_nChild = m_ChildDoc.GetCount();

		if( IsExecuted() )
			pDocInfo->m_nStatus = 1;
		else if( IsOpen() )
			pDocInfo->m_nStatus = 0;
		else if( !IsOpen() )
			pDocInfo->m_nStatus = 2;
		else
			pDocInfo->m_nStatus = 9;


		if( m_pTaskObj != NULL )
			strcpy(pDocInfo->m_szTaskCode, m_pTaskObj->szTaskName);
		else
			strcpy(pDocInfo->m_szTaskCode, "������!");

		for(long i=0; i< pDocInfo->m_nChild; i++)
		{
			pDocInfo->Child[i].m_nAuthID = m_nAuthID;

			if( IsExecuted() )
				pDocInfo->Child[i].m_nStatus = 1;
			else if( IsOpen() )
				pDocInfo->Child[i].m_nStatus = 0;
			else if( !IsOpen() )
				pDocInfo->Child[i].m_nStatus = 2;
			else
				pDocInfo->Child[i].m_nStatus = 9;

			if( m_pTaskObj != NULL )
				strcpy(pDocInfo->Child[i].m_szTaskCode, m_pTaskObj->szTaskName);
			else
				strcpy(pDocInfo->Child[i].m_szTaskCode, "������!");
		}
	}
	else
	{
		for(long i=0; i< m_ChildDoc.GetCount(); i++)
		{
			TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
			if( pSmartDoc != NULL )
			{
				if( pSmartDoc->m_nAuthID == nAuthNo )
				{
					pDocInfo->m_nAuthID = m_nAuthID;
					pDocInfo->m_nChild = 0;

					if( IsExecuted() )
						pDocInfo->m_nStatus = 1;
					else if( IsOpen() )
						pDocInfo->m_nStatus = 0;
					else if( !IsOpen() )
						pDocInfo->m_nStatus = 2;
					else
						pDocInfo->m_nStatus = 9;

					if( m_pTaskObj != NULL )
						strcpy(pDocInfo->m_szTaskCode, m_pTaskObj->szTaskName);
					else
						strcpy(pDocInfo->m_szTaskCode, "������!");
				}
			}
		}
	}
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::DestoryStack()
//*����: ɾ����ջ�е�����
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::DestoryStack()
{
	printf("׼��ɾ��STACK\n");
	TSTaskStack *pTaskStack = NULL;
	while( (pTaskStack = (TSTaskStack *)m_Stack.Pop()) )
	{
		printf("ɾ����ջ�е�����!!!!\n");
		delete pTaskStack ;
	}

	m_Stack.Release();
}

void TSmartDocObj::SetPause(bool bBool)
{
	m_PauseLock.Lock();
	m_bPause = bBool ;
	m_PauseLock.Unlock();
}

bool TSmartDocObj::GetPause() 
{
	bool bRet;
	m_PauseLock.Lock();
	bRet = m_bPause;
	m_PauseLock.Unlock();
	return bRet;
}


//*=================================================================================
//*ԭ��: void TSmartDocObj::Clear()
//*����: ����ṹ��Ա
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::Clear()
{
	m_nFlow = 0;
	m_nCardID = 0;
	m_nInMoney = 0;
	m_nOutMoney = 0;
	m_nDealCount = 0;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::Release()
//*����: ɾ�����豸
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::Release()
{
	if( IsOpen() )
		Close();

	delete this;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::ClearChildDoc()
//*����: ������豸
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::ClearChildDoc()
{
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pDoc = (TSSmartDoc*)m_ChildDoc[i];
		if( pDoc != NULL )
		{
			delete pDoc;
		}
	}
	m_ChildDoc.Clear();
}

//*=================================================================================
//*ԭ��: long TSmartDocObj::GetPriority()
//*����: �õ���ǰ��������ȼ�
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::GetPriority()
{
	if( m_pTaskObj )
		return m_pTaskObj->pTask[m_nIndex].nPriority;

	return -1;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::AddChildDoc(TSSmartDoc *pSmartDoc)
//*����: ���뵽���豸��
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::AddChildDoc(TSSmartDoc *pSmartDoc)
{
	pSmartDoc->m_bEnable = true ;
	m_ChildDoc.Add(pSmartDoc);

	ZeroMemory(&pSmartDoc->DeviceInfo, sizeof(TSDeviceInfo));
	ConvertToDevice(pSmartDoc, &pSmartDoc->DeviceInfo);
}

long TSmartDocObj::GetChildDocCount()
{
	return m_ChildDoc.GetCount();
}

bool TSmartDocObj::IsChildDoc(long nAuthID)
{
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( pSmartDoc->m_nAuthID == nAuthID )
			{
				return true;
			}
		}
	}

	return false;
}

bool TSmartDocObj::Enable(long nAuthID, bool bEnable)
{
	if( m_nAuthID == nAuthID )
	{
		m_bEnable = bEnable;
		return true;
	}

	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		TSSmartDoc *pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( pSmartDoc->m_nAuthID == nAuthID )
			{
				pSmartDoc->m_bEnable = bEnable;
				return true;
			}
		}
	}
	return false;
}

//*=================================================================================
//*ԭ��: void StopChildDoc(long nAuthID)
//*����: ͣ�����豸
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::StopChildDoc(long nAuthID)
{
	SetChildDocStatus(nAuthID, 5);
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::SetChildDocStatus(long nStatus)
//*����: �������豸״̬
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::SetChildDocStatus(long nAuthID, long nStatus)
{

}

//*=================================================================================
//*ԭ��: void TSmartDocObj::AssignBy(const TSSmartDoc *pSmartDoc)
//*����: �ṹ��ֵ
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::AssignBy(const TSSmartDoc *pSmartDoc)
{
	strcpy(m_szMacCode, pSmartDoc->m_szMacCode);
	strcpy(m_szMacCard, pSmartDoc->m_szMacCard);
	strcpy(m_szMacModle, pSmartDoc->m_szMacModle);
	strcpy(m_szMacType, pSmartDoc->m_szMacType);

	strcpy(m_szOrgid, pSmartDoc->m_szOrgid);

	m_nListMark = pSmartDoc->m_nListMark;
	m_nAuthID = pSmartDoc->m_nAuthID;

	strcpy(m_szDeviceID, pSmartDoc->m_szDeviceID);  
	strcpy(m_szRegister, pSmartDoc->m_szRegister);

	m_nMachineNo = pSmartDoc->m_nMachineNo ;

	strcpy(m_szVersion, pSmartDoc->m_szVersion);
	strcpy(m_szProgramver, pSmartDoc->m_szProgramver);
	strcpy(m_szPassword, pSmartDoc->m_szPassword);  
	strcpy(m_szOprPasswd, pSmartDoc->m_szOprPasswd);

	m_nPwdswitch = pSmartDoc->m_nPwdswitch;
	m_nParentID = pSmartDoc->m_nParentID;
	m_nPortCount = pSmartDoc->m_nPortCount;
	m_nSMTPort = pSmartDoc->m_nSMTPort;

	strcpy(m_szPort, pSmartDoc->m_szPort);

	m_nBaudRate = pSmartDoc->m_nBaudRate;
	m_nConnType = pSmartDoc->m_nConnType;
	m_nCommMode = pSmartDoc->m_nCommMode;

	strcpy(m_szAddr, pSmartDoc->m_szAddr);

	m_nOnNet = pSmartDoc->m_nOnNet;
	m_nOnline = pSmartDoc->m_nOnline;
	m_nLevel = pSmartDoc->m_nLevel;

	strcpy(m_szLevelArray, pSmartDoc->m_szLevelArray);

	m_nStatus = pSmartDoc->m_nStatus;

	strcpy(m_szTableName, pSmartDoc->m_szTableName);

	m_wFlowNo = pSmartDoc->m_wFlowNo;
	m_wLastInvoiceNo = pSmartDoc->m_wLastInvoiceNo;
	strcpy(m_sLastDealTime, pSmartDoc->m_sLastDealTime);

	m_nBeginInvoice = pSmartDoc->m_nBeginInvoice;
	m_wSettleinvoice = pSmartDoc->m_wSettleinvoice;

	strcpy(m_sSettleTime, pSmartDoc->m_sSettleTime);

	m_wEndInvoice = pSmartDoc->m_wEndInvoice;

	strcpy(m_sBlackExpire, pSmartDoc->m_sBlackExpire);
	strcpy(m_sDownBlackTime, pSmartDoc->m_sDownBlackTime);

	m_nStartuse = pSmartDoc->m_nStartuse;
	m_nLostDeal = pSmartDoc->m_nLostDeal;
	m_nLostSettle = pSmartDoc->m_nLostSettle;

	strcpy(m_sBlackListVer, pSmartDoc->m_sBlackListVer);
	strcpy(m_sClockVer, pSmartDoc->m_sClockVer);
	strcpy(m_sNumberVer, pSmartDoc->m_sNumberVer);
	strcpy(m_sCommDateTime, pSmartDoc->m_sCommDateTime);

	strcpy(m_sWhiteList, pSmartDoc->m_sWhiteList);
	strcpy(m_sWorkMode, pSmartDoc->m_sWorkMode);
	m_nSwitch = pSmartDoc->m_nSwitch;
	strcpy(m_sBlockVer, pSmartDoc->m_sBlockVer);

	ZeroMemory(&m_DeviceInfo, sizeof(m_DeviceInfo));
	ConvertToDevice(this, &m_DeviceInfo);

	CopyMemory(&DeviceInfo, &m_DeviceInfo, sizeof(DeviceInfo));

	m_nFlow = pSmartDoc->m_nFlow;               //���
	m_nCardID = pSmartDoc->m_nCardID;			//����
	m_nInMoney = pSmartDoc->m_nInMoney;         //�뿨���
	m_nOutMoney = pSmartDoc->m_nOutMoney;       //�������
	m_nDealCount = pSmartDoc->m_nDealCount;		//���ױ���

	m_dwTryCount = pSmartDoc->m_dwTryCount ;
	m_dwSuccess = pSmartDoc->m_dwSuccess ;
	m_dwFaild = pSmartDoc->m_dwFaild ;
	m_dwLastTick = pSmartDoc->m_dwLastTick ;
	m_dwRecvTick = pSmartDoc->m_dwRecvTick ;
	m_dwMarkTick = pSmartDoc->m_dwMarkTick ;
	m_dwFileTick = pSmartDoc->m_dwFileTick ;
	m_dwDBTick = pSmartDoc->m_dwDBTick ;
	m_dwCollectTick = pSmartDoc->m_dwCollectTick ;

	m_nSignIn	= pSmartDoc->m_nSignIn ;
	strcpy(m_szSignInTime, pSmartDoc->m_szSignInTime);
	m_nDealLost	= pSmartDoc->m_nDealLost ;
	m_nJZLost	= pSmartDoc->m_nJZLost ;
	m_nInSuccess	= pSmartDoc->m_nInSuccess ;
	m_nInFaild	= pSmartDoc->m_nInFaild ;
	m_nInSuccessMoney	= pSmartDoc->m_nInSuccessMoney ;
	m_nInFaildMoney	= pSmartDoc->m_nInFaildMoney ;
	m_nCheckSuccess	= pSmartDoc->m_nCheckSuccess ;
	m_nCheckFaild	= pSmartDoc->m_nCheckFaild ;
	m_nCheckSuccessMoney	= pSmartDoc->m_nCheckSuccessMoney ;
	m_nCheckFaildMoney	= pSmartDoc->m_nCheckFaildMoney ;
	m_nBatchSuccess	= pSmartDoc->m_nBatchSuccess ;
	m_nBatchFaild	= pSmartDoc->m_nBatchFaild ;
	m_nBatchSuccessMoney	= pSmartDoc->m_nBatchSuccessMoney ;
	m_nBatchFaildMoney	= pSmartDoc->m_nBatchFaildMoney ;
	m_nDealNumber	= pSmartDoc->m_nDealNumber ;
	m_nTransMoney	= pSmartDoc->m_nTransMoney ;

	m_bEnable = pSmartDoc->m_bEnable;
}

//*=================================================================================
//*ԭ��: bool TSmartDocObj::HaveHistoryTask()
//*����: �Ƿ��б��жϵ�����
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
bool TSmartDocObj::HaveHistoryTask()
{
	return m_Stack.IsEmpty();
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::Run()
//*����: ִ�и�������
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::Run()
{
	while( !IsShutdown() )
	{
		DWORD dwResult = WaitForSingleObject(m_hEvent, 20);
		if( dwResult == WAIT_OBJECT_0 )
		{
			if( GetIOStatus() == IO_Status_Free )
			{
				SetIOStatus(IO_Status_Execute);
				TaskFinished(ExecuteTask(m_pTaskObj, m_nIndex));
			}
		}
	}
	
/*  modified by lina 20050512
	TSSmartDoc *pSmartDoc = this;
	if( strcmp(pSmartDoc->m_szMacCode, "5301") )
	{
		MakeBuf_SetComsumeFlag(&pSmartDoc->DeviceInfo, &m_CmdBuffer, 0);
		m_CmdBuffer.nTimeOut1 = 1000 ;
		m_CmdBuffer.nTimeOut2 = 1000;
		SendRecv(&m_CmdBuffer, 2000);
	}

	//����ǩ��ָ��
	for(long i=0; i< m_ChildDoc.GetCount(); i++)
	{
		pSmartDoc = (TSSmartDoc *)m_ChildDoc[i];
		if( pSmartDoc != NULL )
		{
			if( strcmp(pSmartDoc->m_szMacCode, "5301") )
			{
				MakeBuf_SetComsumeFlag(&pSmartDoc->DeviceInfo, &m_CmdBuffer, 0);
				m_CmdBuffer.nTimeOut1 = 1000 ;
				m_CmdBuffer.nTimeOut2 = 1000;
				SendRecv(&m_CmdBuffer, 2000);
			}
		}
	}

  */
}

//*=================================================================================
//*ԭ��: bool TSmartDocObj::AddToTaskStack(TSmartTaskObj *pObj, long nIndex)
//*����: ����һ�����񵽶�����
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
bool TSmartDocObj::AddToTaskStack(TSmartTaskObj *pObj, long nIndex)
{
	printf("�����������������!!!!\n");
	TSTaskStack  *pTaskStack = new TSTaskStack;
	if( pTaskStack != NULL )
	{
		pTaskStack->pTaskObj = pObj ;
		pTaskStack->nIndex = nIndex;

		if( m_Stack.Push(pTaskStack) >= 0 )
		{
			return true;
		}
		else
		{
			delete pTaskStack;
		}
	}
	return false;
}

//*=================================================================================
//*ԭ��: bool TSmartDocObj::Execute(TSmartTaskObj *pObj, long nIndex)
//*����: Ͷ��һ����
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
bool TSmartDocObj::Execute(TSmartTaskObj *pObj, long nIndex)
{
	static int iReal = 0 ;

	//��ֹ����
	if( WaitForSingleObject(m_hExecute, 0) != WAIT_OBJECT_0 )
	{
		if( WaitForSingleObject(m_hExecute, 1000) != WAIT_OBJECT_0 )
		{
			//printf("AuthID=%d The hExecute is return....%d..TaskCode:%s...\n", m_nAuthID, GetIOStatus(), pObj->pTask[nIndex].szTaskCode);
			return false;
		}

		Pause();
	}

	ResetEvent(m_hExecute);

	if( GetIOStatus() == IO_Status_Free )
	{
		Reset();
		SetPause(false);
		m_pTaskObj = pObj ;
		m_nIndex = nIndex ;

		if( !IsBus() ) 
			Sleep(60);

		SetEvent(m_hEvent);

		if( !iReal )
		{
			iReal = 1 ;
			m_nRealIndex = nIndex ;
			m_pRealTaskObj = pObj ;
		}

		return true;
	} 

	SetEvent(m_hExecute);

	return false;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::OpenDevice()
//*����: ���´�һ���豸
//*����: ��
//*����: ��
//*˵��: ���豸ͨѶ���������MAX_TIMEOUT_TRYʱ, ��
//       �豸���ر���, �����´�
//*=================================================================================
void TSmartDocObj::OpenDevice()
{
	Close();
	m_nRecvTimeOut = 0 ;
	Open();

	if( IsBus() )
		m_pServer->AssignBusHandle(this);
}

//*=================================================================================
//*ԭ��: void ExecuteTask(TSmartTaskObj *pObj, long nIndex)
//*����: ִ��һ������
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::ExecuteTask(TSmartTaskObj *pObj, long nIndex)
{
	TSSmartDocEx  DocEx;
	int  nRet =  RET_OK ;
	bool bBroad = false;

#if 1
	static DWORD iBeginTick = GetTickCount();

	if( GetTickCount() - iBeginTick > 5*1000 && m_pServer )
	{
		TSSmartDoc *pDocTick = this;
		m_pServer->m_Channels.SendDeviceTick(pDocTick);

		for(int k=0; k< m_ChildDoc.GetCount(); k++)
		{
			pDocTick = (TSSmartDoc*)m_ChildDoc[k];
			if( pDocTick != NULL )
			{
				m_pServer->m_Channels.SendDeviceTick(pDocTick);
			}
		}

		iBeginTick = GetTickCount();
	}
#endif

	//�����豸���𵵰�
	CreateDocArray(&DocEx);
	

	char  strText[1024];
	if( strcmp(m_pTaskObj->pTask[m_nIndex].szTaskCode, "01") && nRet == RET_OK )
	{
		sprintf(strText, "�豸%d������ִ������. �������:%s.", 
			DocEx.pChildDoc[DocEx.nPortNo]->m_nAuthID, 
			pObj->pTask[nIndex].szTaskCode);

		WriteLog(strText);
	}

	WaitBusResource();

	if( IsBus() && !strcmp(m_szMacCode, "0224") )
	{
		Sleep(1000);
	}

	static int iTick = 0 ;

	try
	{
		pObj->SetBeginFlag(nIndex);
		if( !IsOpen() )
		{
			m_nRecvTimeOut = 0 ;
			OpenDevice();
		}
		else if( m_nRecvTimeOut >= MAX_TIMEOUT_TRY )
		{
			m_nRecvTimeOut = 0 ;
			OpenDevice();
		}

		//LPortǩ��
		if( !strcmp(m_szMacCode, "5301") )
			m_nSignIn = 1 ;

		m_nTerminate = 0 ;
 		DocEx.pChildDoc[DocEx.nPortNo]->m_nTerminate = 0 ;

		//���ɵ�һ���������
		nRet = RSCreateTaskBuffer(&DocEx, &pObj->pTask[m_nIndex], &m_CmdBuffer);
		long  nCreateResult = nRet;
		if( nRet != RET_OK && nRet != RET_ERRORCALL )
		{
			if( nRet == RET_CONTINUE )
			{
				return ProcessRequest(true, &m_CmdBuffer);
			}
			else if( nRet == RET_BROADCAST )
			{
				bBroad = true;
			}
			else
			{
				char  sBuffer[256];
				char  sText[512];
				GetResultMessage(nRet, sBuffer);
				sprintf(sText, "������ִ��!�������:%d. ������Ϣ:%s", nRet, sBuffer);
				throw TException(sText);
			}
		}

		long nSleep = 0;
		long nTry = 0 ;
		
		if( DocEx.pChildDoc[DocEx.nPortNo]->m_nLevel > 0 )
		{
			nSleep = (DocEx.pChildDoc[DocEx.nPortNo]->m_nLevel)*180 ;
		}

		while( nTry++ < 3 )
		{
			if( bBroad )
			{
				m_CmdBuffer.m_nCmdType = SMART_CMD_SEND;
				nRet = SendRecv(&m_CmdBuffer, nSleep);
				break;
			}
			else
			{
				m_CmdBuffer.m_nCmdType = SMART_CMD_SENDRECV;
				nRet = SendRecv(&m_CmdBuffer, nSleep);
			}
			if( nRet != RET_RECV_TIMEOUT && 
				nRet != RET_RECV_C1_TIMEOUT && 
				nRet != RET_RECV_C2_TIMEOUT )
				break;
			else
			{
				m_nRecvTimeOut++;
			}
		}

		if( nRet == RET_OK )
		{
			return ProcessRequest(bBroad, &m_CmdBuffer);
		}
		else
		{
			if( bBroad )
			{
				return ProcessRequest(bBroad, &m_CmdBuffer);
			}
			else if( nCreateResult == RET_ERRORCALL )
			{
				return ProcessRequest(true, NULL);
			}
			else
				return nRet;
		}
	}
	catch(TException& e)
	{
		ProcessRequest(true, &m_CmdBuffer);
		m_pServer->OnDocError(this, (char*)e.GetText());
		printf("%s\n", e.GetText());
		Sleep(100);
		return RET_SYSERROR;
	}
	catch(...)
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1�쳣�׳�!\n");
		ProcessRequest(true, &m_CmdBuffer);
		m_pServer->OnDocError(this, "----ִ������ʧ��,����!");//"ִ������ʱ��δ֪���쳣!");
		return RET_SYSERROR;
	}

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long SendRecv(TCmdBuffer *pCmdBuffer, long nSleep)
//*����: ���������һ�������
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::SendRecv(TCmdBuffer *pCmdBuffer, long nSleep)
{
	long nResult = SendCmdBuffer(pCmdBuffer);
	if( nResult == RET_OK )
	{
		//���û�н��ղ���, ���������
		if( m_CmdBuffer.m_nCmdType == SMART_CMD_SEND ) 
			return RET_OK;

		if( nSleep > 0 )
			Sleep(nSleep);

		pCmdBuffer->ZeroInBuffer();

		nResult = RecvCmdBuffer(pCmdBuffer);
		if( nResult == RET_OK )
		{
			return RET_OK;
		}
	}

	return nResult;
}

void TSmartDocObj::WaitBusResource()
{
	if( !IsBus() )
		return ;

	while( !IsShutdown() )
	{
		//�ȴ���������һ���豸ִ�����
		if( WaitForSingleObject(m_pBus->m_hShare, 2000) == WAIT_OBJECT_0 )
		{
			m_pBus->LockBus();
			//�ֵ����豸ִ��
			if( m_pBus->m_nBusTask == m_nBusNo )
			{
				ResetEvent(m_pBus->m_hShare);
				m_pBus->UnLockBus();
				break;
			}
			m_pBus->UnLockBus();
		}
	}
}

void TSmartDocObj::FreeBusResource()
{ 
	if( !IsBus() )
		return ;

	m_pBus->LockBus();
	m_pBus->m_nBusTask++;
	if( m_pBus->m_nBusTask >= m_pBus->m_nTotal )
		m_pBus->m_nBusTask = 0 ;

	SetEvent(m_pBus->m_hShare);
	m_pBus->UnLockBus();
}

void TSmartDocObj::LockBus()
{
	m_BusLock.Lock();
}

void TSmartDocObj::UnLockBus()
{
	m_BusLock.Unlock();
}

//*=================================================================================
//*ԭ��: void TaskFinished(long nResult)
//*����: ������������Ϻ�Ĵ���
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::TaskFinished(long nResult)
{
	SetIOStatus(IO_Status_Finished);
	ResetEvent(m_hEvent);

	m_pTaskObj->SetTaskResult(m_nIndex, nResult, m_nTerminate);

	//��������ѹ������stack
	if( m_nTerminate == 2 )
	{
		ReportLog("��������ѹ������stack!\n");
		Pause();
		FreeBusResource();
		return ;
	}

	m_nTerminate = 0 ;

	//�ܵ������ѽ���
	if( m_pTaskObj->IsTaskFinished() )
	{
		m_pServer->FinishedTask(this, m_pTaskObj, m_nIndex);
		ReportLog("����:%s (%d) �Ѿ�����!", m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID);
		printf("����:%s (%d) �Ѿ�����!", m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID);
	} 

	//��ͷ����ִ��
	if( m_pTaskObj->IsContinue(m_nIndex) && !GetPause() )
	{
		long nIndex = m_pTaskObj->GetNextTask(this);

		SetEvent(m_hExecute);
		SetIOStatus(IO_Status_Free);

		if( nIndex >= 0 && !GetPause() )
		{
			FreeBusResource();
			m_nIndex = nIndex ;
			Execute(m_pTaskObj, nIndex);
		}
		else
		{
			if( !HaveHistoryTask() )
			{
				FreeBusResource();
				Continue();
			} 
			else
			{
				FreeBusResource();
				SetIOStatus(IO_Status_Free);
				SetEvent(m_hExecute);

				if( m_pRealTaskObj && m_nRealIndex >= 0 )
					Execute(m_pRealTaskObj, m_nRealIndex);
			}
		}
	}
	else
	{
		//�б��жϵ�����
		bool bHave = HaveHistoryTask();
		bool bPex = GetPause();

		if( !bHave )
		{
			//����ִ��
			FreeBusResource();
			Continue();
		} 
		else
		{
			SetIOStatus(IO_Status_Free);
			SetEvent(m_hExecute);
			FreeBusResource();

			if( m_pRealTaskObj && m_nRealIndex >= 0 )
				Execute(m_pRealTaskObj, m_nRealIndex);
		}
	}
}

//*=================================================================================
//*ԭ��: long SendCmdBuffer(TCmdBuffer *pCmdBuffer)
//*����: ����ָ��
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::SendCmdBuffer(TCmdBuffer *pCmdBuffer)
{
	WaitingWrite(pCmdBuffer->nTimeOut1);

	if( PostSend((char*)m_CmdBuffer.pBuffer, m_CmdBuffer.nCmdSize, 1000) == m_CmdBuffer.nCmdSize )
		return RET_OK;

	return RET_SEND_ERROR;
}

//*=================================================================================
//*ԭ��: long TSmartDocObj::RecvCmdBuffer(TCmdBuffer *pCmdBuffer)
//*����: ���շ��ص����ݰ�
//*����: ��
//*����: ��
//*˵��: �ն˻�����c
//*=================================================================================
long TSmartDocObj::RecvCmdBuffer(TCmdBuffer *pCmdBuffer)
{
	long nRecvLen = 1 ;
	long nRet = RET_OK ;

	pCmdBuffer->m_nRecvBytes = 0 ;
	pCmdBuffer->ZeroInBuffer();

	int nTm = pCmdBuffer->nTimeOut1 ;
	if( nTm < 80 )
		nTm = 80;
	
	//if( WaitRecv(m_sBuffer, 4, nTm) <= 0 )
	if(WaitRecv(m_sBuffer,1,1000) <= 0)
	{
		ReportLog("�����ն�%.8X���ݳ�ʱ,δ�ӵ��κ�����\n",m_nAuthID); //add by lina 20050314
		return RET_RECV_TIMEOUT;
	} 

	//����ͷ��ʼ��
	pCmdBuffer->m_nTick1 = GetTickCount();
	while( true  )
	{
		if( pCmdBuffer->IsTimeOutC1() )
		{
			ReportLog("����%.8X ��ʼ����ʱ",m_nAuthID);
			//ReportLog("----δ�յ�%.8X�����ݰ�!!!!",m_nAuthID);
			//printf("");
			//Sleep(5000);
			return RET_RECV_C1_TIMEOUT;
		}

		m_nReadBytes = 0 ;
		memset(m_sBuffer, 0, sizeof(m_sBuffer));

		if( PostRecv(m_sBuffer, nRecvLen, 50) > 0 )
		{
			memcpy(pCmdBuffer->m_pRetBuffer, m_sBuffer, m_nReadBytes);
			pCmdBuffer->m_nRecvBytes = m_nReadBytes;

			if( pCmdBuffer->IsValidHead() )
			{
				break;
			}
		}
	}

	//����ͷ
	nRecvLen = SmartProtocol.nLenOffset - pCmdBuffer->m_nRecvBytes + 1 ;
	if( nRecvLen > 0 )
	{
		pCmdBuffer->m_nTick2 = GetTickCount();

		while( nRecvLen > 0 )
		{
			m_nReadBytes = 0 ;
			memset(m_sBuffer, 0, sizeof(m_sBuffer));

			if( pCmdBuffer->IsTimeOutC2() ) 
			{
				ReportLog("����C2��ʱ\n");
				ReportLog("----δ�յ�%.8X�����ݰ�!!!!",m_nAuthID);
				Sleep(100);
				return RET_RECV_C2_TIMEOUT;
			}

			if( PostRecv(m_sBuffer, nRecvLen, 500) > 0 )
			{
				memcpy(pCmdBuffer->m_pRetBuffer+pCmdBuffer->m_nRecvBytes, m_sBuffer, m_nReadBytes);
				pCmdBuffer->m_nRecvBytes += m_nReadBytes;
				nRecvLen -= m_nReadBytes ;
			}
		}
	}

	//�����ȷǷ�
	nRecvLen  = pCmdBuffer->GetPackSize() - (pCmdBuffer->m_nRecvBytes - 4 ) + 3 ; 
	if( nRecvLen <= 0 ) 
	{
		ReportLog("����%.8X�����ȷǷ�",m_nAuthID);
		
		ReportLog("----δ�յ�%.8X�����ݰ�!!!!",m_nAuthID);
		Sleep(100);
		return RET_DATALENGTH_ERROR;
	}

	//������
	pCmdBuffer->m_nTick2 = GetTickCount();
	while( nRecvLen > 0 )
	{
		m_nReadBytes = 0 ;
		memset(m_sBuffer, 0, sizeof(m_sBuffer));

		if( pCmdBuffer->IsTimeOutC2() ) 
		{
			ReportLog("����%.8XC2----��ʱ\n",m_nAuthID);
			Sleep(100);
			//ReportLog("----δ�յ�%.8X�����ݰ�!!!!",m_nAuthID);
			return RET_RECV_C2_TIMEOUT;
		}

		if( PostRecv(m_sBuffer, nRecvLen, 500) > 0 )
		{
			memcpy(pCmdBuffer->m_pRetBuffer+pCmdBuffer->m_nRecvBytes, m_sBuffer, m_nReadBytes);
			pCmdBuffer->m_nRecvBytes += m_nReadBytes;
			nRecvLen -= m_nReadBytes ;
		}
	}
	//ReportLog("���յ�%.8X�������ݰ�",m_nAuthID);//,pCmdBuffer->m_nRecvBytes);
	printf("���յ�%.8X�������ݰ�\n",m_nAuthID);
	unsigned char c[256];
	memcpy(c,pCmdBuffer->m_pRetBuffer,pCmdBuffer->m_nRecvBytes);
	return RET_OK;
}

//*=================================================================================
//*ԭ��: long TSmartDocObj::ProcessRequest(TCmdBuffer *pCmdBuffer)
//*����: ��������
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::ProcessRequest(bool bBroad, TCmdBuffer *pCmdBuffer)
{
	if( !bBroad )
	{
		pCmdBuffer->CopyOut(pCmdBuffer->m_nRecvBytes);

		if( !pCmdBuffer->CheckInPacket() )
		{
			return RET_DATACRC_ERROR;
		}
	}

	long nRet = RET_OK ;
	TSSmartDocEx  DocEx;

	CreateDocArray(&DocEx);

	try
	{
		char strRet[256] = "�ɹ�";
		char strText[1024];

		SetIOStatus(IO_Status_ExecuteCall);
		long nRet = RSSmartTaskProcess(&DocEx, &m_pTaskObj->pTask[m_nIndex], pCmdBuffer);
		if( nRet != RET_NG )
		{
			GetResultMessage(nRet, strRet);
			sprintf(strText, "%d&%s&%s&%d&%s", 
				DocEx.pChildDoc[DocEx.nPortNo]->m_nAuthID, 
				m_pTaskObj->pTask[m_nIndex].szTaskCode,
				m_pTaskObj->pTask[m_nIndex].szRunTime,
				nRet,
				strRet);

			char szLog[1024];
			sprintf(szLog, "�豸:%d, ִ������<����:%s(%d), �������:%s>����! ���ؽ��(%d):%s", 
				m_nAuthID, m_pTaskObj->szTaskName, m_pTaskObj->nTaskPlanID, 
				m_pTaskObj->pTask[m_nIndex].szTaskCode, nRet, strRet);
			//printf("%s\n",szLog);
			WriteLog(szLog);
		}
		else
		{
	//		
//			printf("û�б�������!\n");
			Sleep(20);
		}

		m_nTerminate = DocEx.pChildDoc[DocEx.nPortNo]->m_nTerminate ; 
	}
	catch(TException& e)
	{
		throw e;
	}
	catch(...)
	{
		
		ReportLog("ҵ��㴦������ʧ��!����ִ�� %s!!!\n",m_pTaskObj->szTaskName);
		throw TException("ҵ��㴦������ʧ��!����ִ��!!!");
		//ReportLog("ҵ��㴦������ʱ�����쳣! ����ҵ������!");
		//throw TException("ҵ��㴦������ʱ�����쳣! ����ҵ������!");
	}

	return nRet;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::Pause()
//*����: ����ǰ�豸����ִ�е������ж�, �����浽stack��
//*����: ��
//*����: ��
//*˵��: ��ͣ�����ִ��
//*=================================================================================
void TSmartDocObj::Pause()
{
	long l;
	SetPause(true);
	ResetEvent(m_hEvent);
//	printf("------�ȴ�����ִ����� m_nTerminate= %d\n",m_nTerminate);
	//�ȴ�����ִ�����
	//Ϊ��֤ϵͳ��״��, ֻ�����ŵصȴ������������
	if( m_nTerminate == 2 )
	{
		
		m_nTerminate = 0 ;
		SetIOStatus(IO_Status_Free);
	}
	else
	{
		//ÿ��50�����������Ƿ����, 
		//���������ʱ���س�������, ����ȴ��ܾ�....
		l = 0;
												
		while( IsExecuted() )
		{
			//ÿ��50�����������Ƿ����, 
			//printf("���������ʱ���س�������, ����ȴ��ܾ�....\n");
			Sleep(50);
			l = l+1;
			if(l == 100)
				Reset();
		}
	}

	//����ǰ������ջ
	if( m_pTaskObj != NULL )
	{
		m_pTaskObj->pTask[m_nIndex].nTerminate = 0 ;
		m_nTerminate = 0 ;

		TSTaskStack  *pTaskStack = new TSTaskStack;
		pTaskStack->pTaskObj = m_pTaskObj ;
		pTaskStack->nIndex = m_nIndex;
		if( m_Stack.Push(pTaskStack) < 0 )
		{
			delete pTaskStack;
			WriteLog("������ջʧ��!");
		}
	}

	m_pTaskObj = NULL ;
	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;
	m_nIndex = 0 ;

	SetEvent(m_hExecute);
	SetPause(false);
	SetIOStatus(IO_Status_Free);
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::Continue()
//*����: ����ִ��һ������
//*����: ��
//*����: ��
//*˵��: �ӱ��豸��ջ�еõ���ͣ������, ����ִ��
//*=================================================================================
void TSmartDocObj::Continue()
{
	TSTaskStack *pTaskStack = (TSTaskStack *)m_Stack.Pop();
	if( pTaskStack != NULL )
	{
		SetIOStatus(IO_Status_Free);
		m_pTaskObj = pTaskStack->pTaskObj ;
		m_nIndex = pTaskStack->nIndex ;
		delete pTaskStack ;

		SetEvent(m_hExecute);
		Execute(m_pTaskObj, m_nIndex);
	}
	else
	{
		m_pTaskObj = NULL ;
		m_nIndex = 0 ;
		SetIOStatus(IO_Status_Free);
		SetEvent(m_hExecute);
	}
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::ConvertToDevice(TSSmartDoc *pDoc, TSDeviceInfo *pDeviceInfo)
//*����: ���豸�����ṹתΪ�豸�����Ϣ�ṹ
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::ConvertToDevice(TSSmartDoc *pDoc, TSDeviceInfo *pDeviceInfo)
{
	ZeroMemory(pDeviceInfo, sizeof(TSDeviceInfo));

	pDeviceInfo->nAuthID = pDoc->m_nAuthID;          //������Ȩ��
	pDeviceInfo->nHardware= atoi(pDoc->m_szMacCode); //Ӳ������

	strcpy(pDeviceInfo->sVersion, pDoc->m_szVersion); //Ӳ���汾��

	strcpy(pDeviceInfo->sRegNo, pDoc->m_szRegister);

	pDeviceInfo->nAddr = pDoc->m_nMachineNo ;   //��������(0-255) 0��ʾ�㲥ͨѶ
	pDeviceInfo->nNetPar = 0;                   //����ṹ: ֱ��, ����, ����
	pDeviceInfo->nLevel = pDoc->m_nLevel;		//�ն��豸�����ӵ����ݷ������ļ�����

	memcpy(pDeviceInfo->sLevelArray, pDoc->m_szLevelArray, sizeof(pDeviceInfo->sLevelArray));//��������

	pDeviceInfo->nTotalNo = pDoc->m_nPortCount;   //�ն˻�������
	pDeviceInfo->nPort = pDoc->m_nSMTPort;        //���͵�ǰͨѶ�˿� ���ߵ�ǰͨѶ��������
	pDeviceInfo->nNoReponseTime = 0;        //�ն��޷�Ӧ����
}

void TSmartDocObj::Start()
{
	TThread::Start();
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::CreateDocArray(TSSmartDocEx *pDocEx)
//*����: ����DocArray�ṹ
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::CreateDocArray(TSSmartDocEx *pDocEx)
{
	//printf("pDocEx->nChildDoc == %d\n",m_ChildDoc.GetCount());
	if( m_pTaskObj->pTask[m_nIndex].nAuthID == m_nAuthID )
	{
		pDocEx->nPortNo = 0 ;
		pDocEx->nNetPar = 1 ;
		/*if(m_ChildDoc.GetCount() == 0)
		{
			pDocEx->nChildDoc = 1;
			m_ChildDoc.Add(pDocEx);
		}
		else*/
			//pDocEx->nChildDoc+=1;
		pDocEx->nChildDoc = m_ChildDoc.GetCount()+1;
		
		//printf("m_pTaskObj->pTask[m_nIndex].nAuthID == %X  pDocEx->nChildDoc = %d \n",m_nAuthID,pDocEx->nChildDoc);
		pDocEx->pDeviceInfo = &m_DeviceInfo;
		pDocEx->pChildDoc[0] = this ;

		for(long i=1; i<= m_ChildDoc.GetCount(); i++)
			pDocEx->pChildDoc[i] = (TSSmartDoc*)m_ChildDoc[i-1];
	}
	else
	{
		for(long i=0; i< m_ChildDoc.GetCount(); i++)
		{
			TSSmartDoc *pDoc = (TSSmartDoc*)m_ChildDoc[i] ;
			if( pDoc && pDoc->m_nAuthID == m_pTaskObj->pTask[m_nIndex].nAuthID ) 
			{
				pDocEx->nPortNo = 0 ;
				pDocEx->nNetPar = 1 ;
				pDocEx->nChildDoc = 1;
				pDocEx->pDeviceInfo = &pDoc->DeviceInfo;
				pDocEx->pChildDoc[0] = pDoc ;
				break;
			}
		}
	}
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::SetOpenFlag(bool bBool)
//*����: �豸�豸�򿪵�״̬
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::SetOpenFlag(bool bBool)
{
	m_bOpen = bBool ;
}

//*=================================================================================
//*ԭ��: long SendRequest(TSCmdBuffer *pCmdBuffer)
//*����: ���͵��ʵ�����
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::SendRequest(TCmdBuffer *pCmdBuffer)
{
/*	if( GetPause() )
		return RET_TERMINATE;*/

	if( GetIOStatus() != IO_Status_ExecuteCall )
		return RET_PARAMETER_ERROR1;

	SetIOStatus(IO_Status_ExecuteApi);

	long nResult = SendCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

	nResult = RecvCmdBuffer(pCmdBuffer);
	if( nResult != RET_OK )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return nResult ;
	}

/*	if( GetPause() )
	{
		SetIOStatus(IO_Status_ExecuteCall);
		return RET_TERMINATE;
	}
*/
	pCmdBuffer->CopyOut(pCmdBuffer->m_nRecvBytes);
	SetIOStatus(IO_Status_ExecuteCall);

	return RET_OK;
}

//*=================================================================================
//*ԭ��: long TSmartDocObj::GetIOStatus()
//*����: �õ��豸�ĵ�ǰ״̬
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
long TSmartDocObj::GetIOStatus()
{
	m_StatusLock.Lock();
	long n = m_IOStatus;
	m_StatusLock.Unlock();

	return n ;
}

//*=================================================================================
//*ԭ��: void TSmartDocObj::SetIOStatus(long nStatus)
//*����: �����豸�ĵ�ǰ״̬
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
void TSmartDocObj::SetIOStatus(long nStatus)
{
	m_StatusLock.Lock();
	m_IOStatus = nStatus ;
	m_StatusLock.Unlock();
}

//*=================================================================================
//*ԭ��: bool TSmartDocObj::IsExecuted()
//*����: �Ƿ���æ��״̬
//*����: ��
//*����: ��
//*˵��: �ն˻�����
//*=================================================================================
bool TSmartDocObj::IsExecuted()
{
	if( GetIOStatus() == IO_Status_Execute || 
		GetIOStatus() == IO_Status_ExecuteCall || 
		GetIOStatus() == IO_Status_ExecuteApi || 
		GetIOStatus() == IO_Status_Finished ) 
	{
		return true;
	}

	return false;
}

bool TSmartDocObj::IsWaitExecute()
{
	if( GetIOStatus() == IO_Status_ExecuteCall || 
		GetIOStatus() == IO_Status_ExecuteApi )
		return true;
	return false;
}

bool TSmartDocObj::IsBus() const
{
	return m_bShare;
}

//�Ƿ��
bool TSmartDocObj::IsOpen() const
{
	return m_bOpen;
}

//*=================================================================================
//*ԭ��: bool TSocketSmartDocObj::Reset()
//*����: ��λ��·
//*����: ��
//*����: ��
//*˵��: �׽����豸
//*=================================================================================
void TSmartDocObj::Reset()
{
	SetIOStatus(IO_Status_Free);

	m_pTaskObj = NULL ;
	m_nIndex = 0 ;

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;
	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	m_CmdBuffer.ZeroBuffer();

	ResetEvent(m_hEvent);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///����ΪSocket����
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
TSocketSmartDocObj::TSocketSmartDocObj()
{
	m_hSocket = NULL;
}

TSocketSmartDocObj::~TSocketSmartDocObj()
{

}

//*=================================================================================
//*ԭ��: void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
//*����: ����SOCKET
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
{
	m_hSocket = WSASocket(nAf, nType, nProtocol, NULL, 0, WSA_FLAG_OVERLAPPED);
	if( m_hSocket == INVALID_SOCKET )
	{
		throw TException("�����׽��ִ���!", WSAGetLastError());
	}

	int nFlag = 1; 
	if( ioctlsocket(m_hSocket, FIONBIO, (u_long*)&nFlag) == SOCKET_ERROR )
	{
		closesocket(m_hSocket);
		throw TException("�����׽���Ϊ���Դ���!", WSAGetLastError());
	}

	return ;
}

//*=================================================================================
//*ԭ��: void TSocketSmartDocObj::Create(int nAf, int nType, int nProtocol)
//*����: �õ�һ����פ�͵�����
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
void TSocketSmartDocObj::Bind(char *pszAddress, int nPort)
{
	SOCKADDR_IN  sockAddr;

	ZeroMemory(&sockAddr, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port = htons(nPort);

	LPSTR lpszAscii = (LPSTR)pszAddress;
	if (lpszAscii == NULL)
		sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
	{
		DWORD lResult = inet_addr(lpszAscii);
		if (lResult == INADDR_NONE)
		{
			throw TException("�����ַ��������ƴ���!", WSAEINVAL);
		}
		sockAddr.sin_addr.s_addr = lResult;
	}

	if( bind(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR )
	{
		throw TException("���׽��ִ���!", WSAGetLastError());
	}
}

void TSocketSmartDocObj::Listen(int nQueue)
{
	if( listen(m_hSocket, nQueue) == SOCKET_ERROR )
	{
		throw TException("Listen�׽��ִ���!", WSAGetLastError());
	}
}

//*=================================================================================
//*ԭ��: bool TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
//*����: ���ӵ�������
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
void TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
{
	SOCKADDR_IN  sockAddr;
	TCHAR  szErrorText[256];


	sprintf(szErrorText, "�������ӵ�������(%s:%d)", pszAddress, nPort);

	ZeroMemory(&sockAddr, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET ;
	sockAddr.sin_port = htons(nPort);

	LPSTR lpszAscii = (LPSTR)pszAddress;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			throw TException("�����ַ��������ƴ���!", WSAEINVAL);
		}
	}

	WSAEVENT hEvent = WSACreateEvent();
	if( hEvent == WSA_INVALID_EVENT )
	{
		throw TException(szErrorText, WSAGetLastError());
	}

	if( WSAEventSelect(m_hSocket, hEvent, FD_CONNECT|FD_CLOSE) == SOCKET_ERROR )
	{
		WSACloseEvent(hEvent);
		throw TException(szErrorText, WSAGetLastError());
	}

	DWORD dwResult = WSAConnect(m_hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr), NULL, NULL, NULL, NULL);
	if( dwResult == SOCKET_ERROR )
	{
		dwResult = WSAGetLastError();
		if( dwResult != WSAEWOULDBLOCK )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			throw TException(szErrorText, dwResult );
		}

		//�ȴ��¼�����
		DWORD dwRet = WSAWaitForMultipleEvents(1, &hEvent, TRUE, (DWORD)dwTimeOut, FALSE);
		if( dwRet != WSA_WAIT_EVENT_0 )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);

			if( dwRet != WSA_WAIT_TIMEOUT )
				throw TException(szErrorText, WSAGetLastError());
			else
			{
				throw TException(szErrorText, WSA_WAIT_TIMEOUT);
			}
		}

		//���¼�����
		WSANETWORKEVENTS   NetEvents;

		ZeroMemory(&NetEvents, sizeof(NetEvents));		
		if( WSAEnumNetworkEvents(m_hSocket, hEvent, &NetEvents) == SOCKET_ERROR )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			throw TException(szErrorText, WSAGetLastError());
		}

		if( NetEvents.lNetworkEvents != FD_CONNECT || NetEvents.iErrorCode[FD_CONNECT_BIT] )
		{
			WSAEventSelect(m_hSocket, hEvent, 0);
			WSACloseEvent(hEvent);
			throw TException(szErrorText, NetEvents.iErrorCode[FD_CONNECT_BIT]);
		}			 
	}

	WSAEventSelect(m_hSocket, hEvent, 0);
	WSACloseEvent(hEvent);
}

//*=================================================================================
//*ԭ��: bool TSocketSmartDocObj::Connect(char* pszAddress, int nPort, long dwTimeOut)
//*����: �ص�д
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TSocketSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	WSABUF  wsaBuf;
	DWORD   dwFlag = 0 ;
	//add by lina 20050311
	unsigned char c[256];
	memcpy(c,pszBuffer,nBufferSize);
//	ReportLog("���ն˷�������:");
	
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSASend(m_hSocket, &wsaBuf, 1, &m_nWriteBytes, 0, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			printf("Send WSA_IO_PENDING.................\n");
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			if( !WSAGetOverlappedResult(m_hSocket, &m_WriteOver, &m_nWriteBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					printf("Send WSA_IO_INCOMPLETE.................\n");
					throw TException("�������ݴ���!", nLastError);
				}
			}
		}
	}

	return (long)m_nWriteBytes;
}

void TSocketSmartDocObj::ReadEmptyBuffer()
{

}

//*=================================================================================
//*ԭ��: long TSocketSmartDocObj::Read(char* pszBuffer, long dwBufferSize)
//*����: �ص���
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TSocketSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	DWORD	dwFlag = 0 ;
	WSABUF  wsaBuf;

	m_nReadBytes = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSARecv(m_hSocket, &wsaBuf, 1, &m_nReadBytes, &dwFlag, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			dwFlag = 0 ;
			if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					throw TException("�ȴ��������ݴ���!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

//*=================================================================================
//*ԭ��: long WriteTo(char *pszBuffer, long nBufferSize, const SOCKADDR_IN *psockAddr, long nTimeOut)
//*����: �ص�д(UDP)
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TSocketSmartDocObj::WriteTo(char *pszBuffer, long nBufferSize, const SOCKADDR_IN *psockAddr, long nTimeOut)
{
	DWORD   dwBytes = 0 ;
	WSABUF  wsaBuf;
	int nLen = sizeof(SOCKADDR_IN);

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSASendTo(m_hSocket, &wsaBuf, 1, &dwBytes, 0, (SOCKADDR*)psockAddr, nLen, &m_WriteOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			dwBytes = 0 ;
			if( !WSAGetOverlappedResult(m_hSocket, &m_WriteOver, &dwBytes, TRUE, NULL) )
			{
				int  nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					throw TException("�������ݴ���!", WSAGetLastError());
				}
			}
		}
	}

	return (long)dwBytes;
}

//*=================================================================================
//*ԭ��: long ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut)
//*����: �ص�д(UDP)
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TSocketSmartDocObj::ReadFrom(char *pszBuffer, long nBufferSize, SOCKADDR_IN *psockAddr, long nTimeOut)
{
	DWORD	dwFlag = MSG_PEEK ;
	WSABUF  wsaBuf;
	int nLen = sizeof(SOCKADDR_IN);

	m_nReadBytes = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	wsaBuf.buf = (LPTSTR)pszBuffer;
	wsaBuf.len = (DWORD)nBufferSize;

	int nResult = WSARecvFrom(m_hSocket, &wsaBuf, 1, &m_nReadBytes, &dwFlag, 
						(SOCKADDR*)psockAddr, &nLen, &m_ReadOver, NULL);
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			//dwFlag = 0 ;
			if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
			{
				int nLastError = WSAGetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					throw TException("�������ݴ���!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

//*=================================================================================
//*ԭ��: bool TSocketSmartDocObj::Open()
//*����: ��ͨѶ��·
//*����: ��
//*����: ��
//*˵��: �׽����豸
//*=================================================================================
void TSocketSmartDocObj::Open()
{
	m_bOpen = false;
	m_ReadOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	Create(AF_INET, SOCK_STREAM, 0);
	Connect(m_szAddr, atol(m_szPort), 1000);
	m_bOpen = true ;

	ReportLog("TSocketSmartDocObj�ն��豸%s�򿪳ɹ�! ��ַ:%s, �˿�:%s\n", m_szDeviceID, m_szAddr, m_szPort);
}

//*=================================================================================
//*ԭ��: void TSocketSmartDocObj::Close()
//*����: ǿ�ƹر���·
//*����: ��
//*����: ��
//*˵��: ��
//*=================================================================================
void TSocketSmartDocObj::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	if( m_hSocket != NULL )
	{
		shutdown(m_hSocket, SB_BOTH);
		closesocket(m_hSocket);

		m_hSocket = NULL ;
	}

	m_bOpen = false ;
}


//*=================================================================================
//*ԭ��: long TSocketSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: Ͷ�ݷ�������
//*����: ��
//*����: ��
//*˵��: �׽����豸
//*=================================================================================
long TSocketSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*ԭ��: long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: Ͷ�ݽ�������
//*����: ��
//*����: ��
//*˵��: �׽����豸
//*=================================================================================
long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

//*=================================================================================
//*ԭ��: long TSocketSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: Ͷ�ݽ�������
//*����: ��
//*����: ��
//*˵��: �׽����豸
//*=================================================================================
long TSocketSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long ret;
	SOCKADDR_IN sockAddr;

	ZeroMemory(&sockAddr, sizeof(sockAddr));
	ret = ReadFrom(lpBuffer, nBufSize, &sockAddr, nTimeOut);
	return ret;
}


//�ȴ�д
long TSocketSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
	return RET_OK;
}

//�ȴ���
long TSocketSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut) != WAIT_OBJECT_0 )
		return RET_NG;

	DWORD dwFlag = 0 ;
	if( !WSAGetOverlappedResult(m_hSocket, &m_ReadOver, &m_nReadBytes, TRUE, &dwFlag) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

TCOMSmartDocObj::TCOMSmartDocObj()
{
	m_hHandle = INVALID_HANDLE_VALUE;
}

TCOMSmartDocObj::~TCOMSmartDocObj()
{
	Close();
}


//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::ClearComm(DWORD dwMask)
//*����: ����¼�
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_hHandle, dwMask) )
		throw TException("PurgeComm()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
//*����: �����¼�
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_hHandle, dwMask) )
		throw TException("SetCommMask()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
//*����: ���ó�ʱʱ��
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
{
	COMMTIMEOUTS   CommTimeOut;

	ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));

	CommTimeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOut.ReadTotalTimeoutConstant = 0;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;

	CommTimeOut.WriteTotalTimeoutMultiplier = 5;
	CommTimeOut.WriteTotalTimeoutConstant = 50;

	if( !SetCommTimeouts(m_hHandle, &CommTimeOut) )
		throw TException("SetCommTimeouts()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
//*����: �õ�������������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_hHandle, &dwMask) )
		throw TException("GetCommMask()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
//*����: ���ô�������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
{
	TCHAR  szDCB[64];
	DCB    dcb;

	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	wsprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);

	if( !BuildCommDCB(szDCB, &dcb) )
		throw TException("BuildCommDCB()����!", GetLastError());

	if( !SetCommState(m_hHandle, &dcb) )
		throw TException("SetCommState()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::GetState(DCB *pDCB)
//*����: �õ�����״̬(DCB)
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::GetState(DCB *pDCB)
{
	if( !GetCommState(m_hHandle, pDCB) )
	{
		throw TException("����GetCommState()����!", GetLastError());
	}
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::ClearError()
//*����: ������ڴ���
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::ClearError()
{
	if( !PurgeComm(m_hHandle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
		throw TException("PurgeComm()����!", GetLastError());
	}
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::Open()
//*����: �򿪴����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::Open()
{
	TCHAR  szFileName[MAX_PATH];

	m_bOpen = false;

	wsprintf(szFileName, "%s", m_szPort);
	m_hHandle = CreateFile(
					szFileName, 
					GENERIC_READ|GENERIC_WRITE,
					0,
					0,
					OPEN_EXISTING,
					FILE_FLAG_OVERLAPPED,
					0);
	if( m_hHandle == INVALID_HANDLE_VALUE )
	{
		throw TException("��COM��ʧ��!", GetLastError());
	}

	SetState(m_nBaudRate, 'N', 8, 1);

//	EscapeCommFunction(m_hHandle, SETDTR);

//	SetEventMask(EV_RXCHAR);

//	SetupComm(m_hHandle, 1024, 1024);

//	ClearComm(PURGE_TXABORT);
//	ClearComm(PURGE_RXABORT);
//	ClearComm(PURGE_TXCLEAR);
//	ClearComm(PURGE_RXCLEAR);

	SetTimeOut(1000, 0);

	m_ReadOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	m_bOpen = true;

	ReportLog("�ն��豸%d�򿪳ɹ�! ��ַ:%s, �˿�:%s\n", m_nAuthID, m_szAddr, m_szPort);
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::Close()
//*����: �رմ����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TCOMSmartDocObj::Close()
{
	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	if( m_hHandle != INVALID_HANDLE_VALUE )
	{
		ClearError();
		ClearCommBreak(m_hHandle);
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}

	m_bOpen = false ;
}

//*=================================================================================
//*ԭ��: bool TCOMSmartDocObj::Reset()
//*����: ��λ�����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
bool TCOMSmartDocObj::Reset()
{
    try
	{
		Close();
		Open();
	}
	catch(TException& e)
	{
		WriteLog(e.GetText());
		Close();
		return false;
	}

	return true;
}

//*=================================================================================
//*ԭ��: long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: ������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*ԭ��: long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: ������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

long TCOMSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
//leep(dwTimeOut);
	return RET_OK;
} 

long TCOMSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( IsBus() )
		dwTimeOut += 200 ;
	else
		dwTimeOut += 10 ;

	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut) != WAIT_OBJECT_0 )
		return RET_NG;

	if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

long TCOMSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	if( nTimeOut < 500 )
		Sleep(nTimeOut+10);
	else
		Sleep(nTimeOut/2);

	return nTimeOut;
}

//*=================================================================================
//*ԭ��: long Write(char *pszBuffer, long nBufferSize, long nTimeOut)
//*����: �ص�д
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TCOMSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	DWORD nResult = WriteFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, &m_WriteOver);
	if( !m_nWriteBytes )
	{
		if( GetLastError() != ERROR_IO_PENDING )
		{
			throw TException("�򴮿�д���ݴ���!", GetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_WriteOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nWriteBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_WriteOver, &m_nWriteBytes, TRUE) )
			{
				DWORD dwLastError = GetLastError() ;
				if( dwLastError != ERROR_IO_INCOMPLETE )
				{
					throw TException("�򴮿�д���ݴ���!", dwLastError);
				}
			}
		}
	}

	return (long)m_nWriteBytes;
}

//*=================================================================================
//*ԭ��: long Read(char *pszBuffer, long nBufferSize, long nTimeOut)
//*����: �ص���
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TCOMSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	ResetEvent(m_ReadOver.hEvent);

//	DWORD dwMask;
//	COMSTAT  comstat;
//	ClearCommError(m_hHandle, &dwMask, &comstat);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	m_nReadBytes = 0 ;

	DWORD nResult = ReadFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nReadBytes, &m_ReadOver);
	if( !nResult )
	{
		if( GetLastError() != WSA_IO_PENDING )
		{
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
			{
				DWORD nLastError = GetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					printf("com wait read WSA_IO_INCOMPLETE........\n");
					throw TException("�ȴ��������ݴ���!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
///����ΪModem����
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
TModemSmartDocObj::TModemSmartDocObj()
{
	m_hHandle = INVALID_HANDLE_VALUE;
}

TModemSmartDocObj::~TModemSmartDocObj()
{
	Close();
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::ClearComm(DWORD dwMask)
//*����: ����¼�
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::ClearComm(DWORD dwMask)
{
	if( !PurgeComm(m_hHandle, dwMask) )
		throw TException("PurgeComm()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetEventMask(DWORD dwMask)
//*����: �����¼�
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::SetEventMask(DWORD dwMask)
{
	if( !SetCommMask(m_hHandle, dwMask) )
		throw TException("SetCommMask()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
//*����: ���ó�ʱʱ��
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::SetTimeOut(DWORD dwReadTimeOut, DWORD dwWriteTimeOut)
{
	COMMTIMEOUTS   CommTimeOut;

	ZeroMemory(&CommTimeOut, sizeof(CommTimeOut));

	CommTimeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOut.ReadTotalTimeoutConstant = 0;
    CommTimeOut.ReadTotalTimeoutMultiplier = 0 ;

	CommTimeOut.WriteTotalTimeoutMultiplier = 5;
	CommTimeOut.WriteTotalTimeoutConstant = 50;

	if( !SetCommTimeouts(m_hHandle, &CommTimeOut) )
		throw TException("SetCommTimeouts()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::GetEventMask(DWORD& dwMask)
//*����: �õ�������������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::GetEventMask(DWORD& dwMask)
{
	if( !GetCommMask(m_hHandle, &dwMask) )
		throw TException("GetCommMask()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
//*����: ���ô�������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::SetState(int nBaud, char cParity, int nDataBit, int nStopBit)
{
	TCHAR  szDCB[128];
	DCB    dcb;

	ZeroMemory(&dcb, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);

	GetState(&dcb);

	wsprintf(szDCB, "baud=%d parity=%c data=%d stop=%d", nBaud, cParity, nDataBit, nStopBit);
	if( !BuildCommDCB(szDCB, &dcb) )
		throw TException("BuildCommDCB()����!", GetLastError());

	if( !SetCommState(m_hHandle, &dcb) )
		throw TException("SetCommState()����!", GetLastError());
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::GetState(DCB *pDCB)
//*����: �õ�����״̬(DCB)
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::GetState(DCB *pDCB)
{
	if( !GetCommState(m_hHandle, pDCB) )
	{
		throw TException("����GetCommState()����!", GetLastError());
	}
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::ClearError()
//*����: ������ڴ���
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::ClearError()
{
	if( !PurgeComm(m_hHandle, PURGE_TXCLEAR|PURGE_RXCLEAR) )
	{
		throw TException("PurgeComm()����!", GetLastError());
	}
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::Open()
//*����: �򿪴����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::Open()
{
	TCHAR  szFileName[MAX_PATH];

	Close();

	m_bOpen = false;

	wsprintf(szFileName, "%s", m_szPort);
	m_hHandle = CreateFile(
					szFileName, 
					GENERIC_READ|GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_FLAG_OVERLAPPED|FILE_ATTRIBUTE_NORMAL,
					NULL);
	if( m_hHandle == INVALID_HANDLE_VALUE )
	{
		throw TException("��COM��ʧ��!", GetLastError());
	}

	SetState(m_nBaudRate, 'N', 8, 1);

	EscapeCommFunction(m_hHandle, SETDTR);

	SetEventMask(EV_RXCHAR);

	SetupComm(m_hHandle, 1024, 1024);

	ClearComm(PURGE_TXABORT);
	ClearComm(PURGE_RXABORT);
	ClearComm(PURGE_TXCLEAR);
	ClearComm(PURGE_RXCLEAR);

	SetTimeOut(1000, 0);

	m_ReadOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_WriteOver.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_nReadBytes = 0 ;
	m_nWriteBytes = 0 ;

	m_ReadOver.Internal = 0 ;
	m_ReadOver.InternalHigh = 0 ;
	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	ResetEvent(m_ReadOver.hEvent);

	m_WriteOver.Internal = 0 ;
	m_WriteOver.InternalHigh = 0 ;
	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;
	ResetEvent(m_WriteOver.hEvent);

	DialCall();

	m_bOpen = true;

	ReportLog("�ն��豸%d�򿪳ɹ�! ���ŷ���������:%s, �˿�:%s\n", m_nAuthID, m_szAddr, m_szPort);
}

//*=================================================================================
//*ԭ��: void DialCall()
//*����: ����
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::DialCall()
{
	char  szCmdText[256];

	memset(szCmdText, 0, sizeof(szCmdText));
	strcpy(szCmdText, "ATZ \r");
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("���ܸ�λModem! �����Ͽ���û��Modem�豸!");

	Sleep(1000);
	memset(szCmdText, 0, sizeof(szCmdText));
	if( PostRecv(szCmdText, 256, 3000) <= 0 )
		throw TException("���ܸ�λModem! �����Ͽ���û��Modem�豸!");

	if( FindString(szCmdText, "OK") < 0 )
	{
		;
	}

	memset(szCmdText, 0, sizeof(szCmdText));
	sprintf(szCmdText, "ATDT %s\r", m_szAddr);
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("���ܶ�Modem����! �����Ͽ���û��Modem�豸!");

	Sleep(2000);

	int nRead = 256;
	int iTick=0;
	while( iTick++ < 12 )
	{
		memset(szCmdText, 0, sizeof(szCmdText));
		long nResult = PostRecv(szCmdText, nRead, 3000);
		if( nResult > 0 )
		{
			if( FindString(szCmdText, "CONN") >= 0 )
			{
				return ;
			}
		}
		else if( nResult != RET_TIMEOUT ) 
		{
			Sleep(3000);
		}
	}

	if( iTick > 12 )
	{
		throw TException("��·��ͨ��Է����ŷ������޷�Ӧ!");
	}
}

//*=================================================================================
//*ԭ��: void Hangup()
//*����: �Ҷ�
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::Hangup()
{
	char  szCmdText[256];

	memset(szCmdText, 0, sizeof(szCmdText));

	strcpy(szCmdText, "+++");
	if( PostSend(szCmdText, strlen(szCmdText), 1000L) <= 0 )
		throw TException("����д���ݵ�Modem! ���ڹ���!");

	Sleep(2000);

	int nRead = 2 ;
	memset(szCmdText, 0, sizeof(szCmdText));
	if( PostRecv(szCmdText, nRead, 5000) >= nRead )
	{
		if( _strnicmp(szCmdText, "OK", 2) )
		{
			throw TException("Modem���ܹһ�!");
		}
	}
	else
	{
		throw TException("Modem�޷�Ӧ!");
	}

	strcpy(szCmdText, "ATH\r");
	PostSend(szCmdText, strlen(szCmdText), 1000L);
	Sleep(1000);
}

//*=================================================================================
//*ԭ��: void TCOMSmartDocObj::Close()
//*����: �رմ����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
void TModemSmartDocObj::Close()
{
	if( m_hHandle != INVALID_HANDLE_VALUE )
	{
		try
		{
			Hangup();
		}
		catch(...)
		{
		
		}

		EscapeCommFunction(m_hHandle, CLRDTR);

		ClearCommBreak(m_hHandle);
		CloseHandle(m_hHandle);
		m_hHandle = INVALID_HANDLE_VALUE;
	}

	if( m_ReadOver.hEvent != NULL )
	{
		CloseHandle(m_ReadOver.hEvent);
		m_ReadOver.hEvent = NULL ;
	}

	if( m_WriteOver.hEvent != NULL )
	{
		CloseHandle(m_WriteOver.hEvent);
		m_WriteOver.hEvent = NULL ;
	}

	m_bOpen = false ;
}

//*=================================================================================
//*ԭ��: bool TCOMSmartDocObj::Reset()
//*����: ��λ�����豸
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
bool TModemSmartDocObj::Reset()
{ 
   try
   {
	   Close();
	   Open();
   }
   catch(TException& e)
   {
	   WriteLog(e.GetText());
	   Close();
	   return false;
   }
   return true;
}

//*=================================================================================
//*ԭ��: long TCOMSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: ������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
long TModemSmartDocObj::PostSend(char *lpBuffer, int nBufSize, long nTimeOut)
{
	return Write(lpBuffer, nBufSize, nTimeOut);
}

//*=================================================================================
//*ԭ��: long TCOMSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
//*����: ������
//*����: ��
//*����: ��
//*˵��: �����豸
//*=================================================================================
long TModemSmartDocObj::PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	long nRet = Read(lpBuffer, nBufSize, nTimeOut);
	if( nRet == RET_TIMEOUT )
	{
		if( WSAGetLastError() == 997 )
		{
			return WaitingRead(nTimeOut);
		}
	}
	return nRet;
}

long TModemSmartDocObj::WaitingWrite(DWORD dwTimeOut)
{
	return RET_OK;
} 

long TModemSmartDocObj::WaitingRead(DWORD dwTimeOut)
{
	if( WaitForSingleObject(m_ReadOver.hEvent, dwTimeOut+300) != WAIT_OBJECT_0 )
		return RET_NG;

	if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
	{
		int nError = WSAGetLastError();
		return RET_NG;
	}

	return (long)m_nReadBytes;
}

//*=================================================================================
//*ԭ��: long Write(char *pszBuffer, long nBufferSize, long nTimeOut)
//*����: �ص�д
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TModemSmartDocObj::Write(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	m_nWriteBytes = 0 ;

	ResetEvent(m_WriteOver.hEvent);

	m_WriteOver.Offset = 0 ;
	m_WriteOver.OffsetHigh = 0 ;

	DWORD nResult = WriteFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nWriteBytes, &m_WriteOver);
	if( !m_nWriteBytes )
	{
		if( GetLastError() != ERROR_IO_PENDING )
		{
			throw TException("�򴮿�д���ݴ���!", GetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_WriteOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nWriteBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_WriteOver, &m_nWriteBytes, TRUE) )
			{
				DWORD dwLastError = GetLastError() ;
				if( dwLastError != ERROR_IO_INCOMPLETE )
				{
					throw TException("�򴮿�д���ݴ���!", dwLastError);
				}
			}
		}
	}

	return (long)m_nWriteBytes;
}

//*=================================================================================
//*ԭ��: long Read(char *pszBuffer, long nBufferSize, long nTimeOut)
//*����: �ص���
//*����: ��
//*����: ��
//*˵��: �׽���ͨѶ��װ(�����ص�ģ��)
//*=================================================================================
long TModemSmartDocObj::Read(char *pszBuffer, long nBufferSize, long nTimeOut)
{
	ResetEvent(m_ReadOver.hEvent);

	DWORD dwMask;
	COMSTAT  comstat;
	ClearCommError(m_hHandle, &dwMask, &comstat);
	nBufferSize = min(nBufferSize, (long)comstat.cbInQue);

	m_ReadOver.Offset = 0 ;
	m_ReadOver.OffsetHigh = 0 ;

	m_nReadBytes = 0 ;

	DWORD nResult = ReadFile(m_hHandle, pszBuffer, (DWORD)nBufferSize, &m_nReadBytes, &m_ReadOver);
	if( !nResult )
	{
		if( GetLastError() != WSA_IO_PENDING )
		{
			throw TException("�������ݴ���!", WSAGetLastError());
		}
		else
		{
			if( WaitForSingleObject(m_ReadOver.hEvent, nTimeOut) != WAIT_OBJECT_0 )
			{
				return RET_TIMEOUT;
			}

			m_nReadBytes = 0 ;
			if( !GetOverlappedResult(m_hHandle, &m_ReadOver, &m_nReadBytes, TRUE) )
			{
				DWORD nLastError = GetLastError() ;
				if( nLastError != WSA_IO_INCOMPLETE )
				{
					printf("com wait read WSA_IO_INCOMPLETE........\n");
					throw TException("�ȴ��������ݴ���!", nLastError);
				}
			}
		}
	}

	return (long)m_nReadBytes;
}

long TModemSmartDocObj::WaitRecv(char *lpBuffer, int nBufSize, long nTimeOut)
{
	if( nTimeOut < 500 )
		Sleep(nTimeOut+10);
	else
		Sleep(nTimeOut/2);

	return nTimeOut;
}

