///////////////////////////////////////////////////////////////////////////////////////////////////
// SmartServer Version4.0
// Copyright by ?-2004. ���������ǻ۵�����Ϣ��ҵ��˾
///////////////////////////////////////////////////////////////////////////////////////////////////
// �ļ�����: TSmartServer.cpp
// ʵ�ֹ���: ����ǰ�òɼ������������
// �����д: ��ΰ
// �汾���: 2004.02 ��һ��
//           2004.05 �ڶ���. �޸����豸��ȡ��bug.
//           .................
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartServer.h"
#include "TSmartRegister.h"
#include "TExportFunc.h"

//*=================================================================================
//*ԭ��: TSmartServer::TSmartServer()
//*����: ǰ�òɼ���������
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
TSmartServer::TSmartServer()
{
	nSmartTimeOut = 0 ;
	ZeroMemory(SmartTimeOut, sizeof(SmartTimeOut));

	m_DocList.Clear();
	m_TaskList.Clear();

	gethostname(m_SmartInfo.szHostName, 128);
	strcpy(m_SmartInfo.szVersion, "1.0");

	m_SmartInfo.nWorkMode = 1 ;
	strcpy(m_SmartInfo.szDateTime, "");

	m_SmartInfo.nTick = 0;
	m_SmartInfo.nDevLevel1 = 0;
	m_SmartInfo.nDevLevel1Ack = 0;
	m_SmartInfo.nDevLevel2 = 0;
	m_SmartInfo.nDevLevel2Ack = 0;

	TCHAR  szDir[MAX_PATH];

	GetCurPath(szDir);
	wsprintf(szLogDir, "%s\\��������־", szDir);
	CreateDirectory(szLogDir, NULL);
}


//*=================================================================================
//*ԭ��: TSmartServer::~TSmartServer()
//*����: ǰ�òɼ���������
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
TSmartServer::~TSmartServer()
{

}

//*=================================================================================
//*ԭ��: void TSmartServer::InitInstance()
//*����: ��ʼ��������
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::InitInstance()
{
	TSmartRegister  sr;
	sr.ReadParameter();

	m_OutThread.Initialized(sr.m_nPort, this);
	ReportLog("��ʼ����������ӿ��̳߳ɹ�!�˿�:%d", sr.m_nPort);

	try
	{
		m_Channels.Initialized(
			sr.m_szChannels,
			sr.m_szCenter,
			sr.m_nCenterPort,
			sr.m_nEncode, 
			sr.m_nChannelsNotify,
			this,
			sr.m_nFunc,
			sr.m_nServerNo);
	}
	catch(TException& e)
	{
		ReportLog("���ӵ����ʴ��м�����!",  e.GetText());
		throw TException( e.GetText());
	}

	ReportLog("��ʼ��ͨ���̳߳ɹ�!�˿�:%d", sr.m_nPort);

	TExportFunc::pServer = this ;
	TExportFunc::FillAPI(&SmartFunction);

	m_SmartProtocol.Initialized(sr.m_szProtocol);
	ReportLog("��ʼ��Э��ģ��:%s�ɹ�!", sr.m_szProtocol);

	char szFileName[256];
	int  i = 0 ;

	m_SmartModule.Initialized();
	for(i=0; i< sr.m_nModule; i++)
	{
		try
		{
			if( sr.GetModule(szFileName, i+1) )
				m_SmartModule.AddModule(szFileName);
			ReportLog("ϵͳװ��ģ��:%s�ɹ�!", szFileName);
		}
		catch(TException& e)
		{
			ReportLog("ϵͳװ��ģ��:%sʧ��!ԭ��:%s", szFileName, e.GetText());
		}
		catch(...)
		{
			ReportLog("ϵͳװ��ģ��:%sʧ��!ԭ��:δ֪�Ĵ���!", szFileName);
		}
	}

	if( i <= 0 )
	{
		ReportLog("���ؾ���:ϵͳû��װ���κ�ҵ��ģ���ļ�! ϵͳ������ִ��ҵ����!");
	}

	m_SmartMonitor.Initialized(this);

	InitSmartDocList();
}

//*=================================================================================
//*ԭ��: void TSmartServer::InitSmartDocList()
//*����: ��ʼ���豸������Ϣ
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::InitSmartDocList()
{
	TSSmartDoc *pSmartDoc = NULL;
	long nRecCount = 0 ;
	
	m_DocList.Clear();

	try
	{
		pSmartDoc = new TSSmartDoc[MAX_SMART_DOC];
		if( pSmartDoc == NULL )
		{
			ReportLog("���ܶ����豸������!�������ݿ�������ҵ����Ƿ���ȷ!");
			return ;
		}

		ZeroMemory(pSmartDoc, sizeof(TSSmartDoc)*MAX_SMART_DOC);

		if( !m_Channels.ReadSmartDoc(pSmartDoc, &nRecCount) )
		{
			delete [] pSmartDoc;
			ReportLog("���ܶ����豸������!�������ݿ�������ҵ����Ƿ���ȷ!");
			return ;
		}

		if( nRecCount <= 0 )
		{
			delete [] pSmartDoc;
			ReportLog("����: û���κ��豸������Ϣ!");
			return ;
		}
		printf("-----------�豸������Ϣ----------\n");
		for(long mm=0;mm<nRecCount;mm++)
		{
			printf("��Ȩ��=%.8X\n",pSmartDoc[mm].m_nAuthID);
			printf("ID��=%s\n",pSmartDoc[mm].m_szDeviceID);
			printf("�������˿�����=%d\n",pSmartDoc[mm].m_nPortCount);
			printf("�������˿ں�=%d\n",pSmartDoc[mm].m_nSMTPort);
			printf("�豸��������=%d\n",pSmartDoc[mm].m_nLevel);
			printf("�豸��������=%s\n",pSmartDoc[mm].m_szLevelArray);
		}
		long  k = 0 ;
		for(long i=0; i<nRecCount; i++) 
		{
			TSmartDocObj *pObj = CreateSmartDoc(&pSmartDoc[i]);
			if( pObj != NULL )
			{
				printf("i= %d pObj->m_szDeviceID=%.8X\n",i,pObj->m_nAuthID);  
				pObj->SetServer(this);
				pObj->AssignBy(&pSmartDoc[i]);
				AddChildDoc(pObj, pSmartDoc, nRecCount);

				//û�и��豸, �п����������ϵ��豸
				if( pObj->IsParent() )
				{
					long iIndex = FindBusFromDocList(pObj);
					if( iIndex >= 0 )
					{
						TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(iIndex);
						pObj->SetShare(*pBus);
					}
					else
					{
						iIndex = FindBusFromDocArray(pSmartDoc, i, nRecCount);
						if( iIndex >= 0 )
						{
							pObj->SetFirstShare();
						}
					}
				}

				try
				{
					pObj->Start();
					m_DocList.Add(pObj);
					k++;
				}
				catch(TException& e)
				{
					OnError((char*)e.GetText());
					delete pObj;
				}
			}
		}

		if( !k )
		{
			ReportLog("û�������ն��豸������!");
		}

		if( pSmartDoc != NULL )
		{
			delete [] pSmartDoc;
			pSmartDoc = NULL ;
		}
	}
	catch(...)
	{
		if( pSmartDoc != NULL )
			delete [] pSmartDoc;

		OnError("�����豸�������쳣! ����ҵ��ģ���Ƿ���ȷ!");
	}
}

//*=================================================================================
//*ԭ��: TSmartDocObj* CreateSmartDoc(TSSmartDoc *pDoc)
//*����: ������ص��豸������Ϣ
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
TSmartDocObj* TSmartServer::CreateSmartDoc(TSSmartDoc *pDoc)
{
	TSmartDocObj *pObj = NULL ;

	if( pDoc->m_nParentID > 0 )
		return NULL ;

	if( pDoc->m_nParentID == 0 && strcmp(pDoc->m_sClockVer, "") )
		return NULL;
	
	switch(pDoc->m_nCommMode)
	{
	case 1:	//����
		pObj = new TCOMSmartDocObj;
		break;
	case 2: //MODEM
		pObj = new TModemSmartDocObj;
		break;
	case 3: //TCP/IPЭ��
		pObj = new TSocketSmartDocObj;
		break;
	default:
		printf("��֧�ֵ���·ģʽ!!!..............\n");
		break;
	}

	return pObj;
}

//*=================================================================================
//*ԭ��: void TSmartServer::AddChildDoc(TSmartDocObj *pObj, TSSmartDoc *pSmartDoc, long nRecCount)
//*����: �������豸
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::AddChildDoc(TSmartDocObj *pObj, TSSmartDoc *pSmartDoc, long nRecCount)
{
	for(long i=0; i< nRecCount; i++)
	{
		if( pSmartDoc[i].m_nAuthID != pObj->m_nAuthID )
		{
			if( pSmartDoc[i].m_nParentID == pObj->m_nAuthID && pObj->GetChildDocCount() < 24 )
			{
				TSSmartDoc *pDoc = new TSSmartDoc;
				memcpy(pDoc, &pSmartDoc[i], sizeof(TSSmartDoc));
				pObj->AddChildDoc(pDoc);
			}
		}
	}
}

//*=================================================================================
//*ԭ��: void TSmartServer::ExitInstance()
//*����: �˳�������
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::ExitInstance()
{
	m_OutThread.BroadShutdown();
	m_Channels.Destroy();

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			pObj->Shutdown();
		}
	}

	for(i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			try
			{
				pObj->WaitForQuit();
				delete pObj;
			}
			catch(...)
			{

			}
		}
	}

	m_DocList.Clear();

	m_SmartMonitor.Shutdown();
	m_OutThread.Shutdown();

	Sleep(500);

	m_SmartMonitor.WaitFor();
	m_OutThread.WaitFor();

	m_SmartModule.Destory();
	m_SmartProtocol.Destory();
}

//*=================================================================================
//*ԭ��: void TSmartServer::Run()
//*����: ������ִ�з���
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::Run()
{
	bool bReloadFlag = false;
	try
	{
		m_OutThread.Start();
		m_SmartMonitor.Start();

		TSmartTaskObj *pObj = NULL ;
		bool  bRet;
		DWORD nTick = GetTickCount();

		//ִ������
		while( !IsShutdown() )
		{
			if( GetDocCount() <= 0 )
			{
				ReportLog("û���豸������Ϣ! �������Զ�����װ���豸������!");
				InitSmartDocList();
				Sleep(1000);
				continue;
			}
			
			
			bRet = false ;
			pObj = new TSmartTaskObj;
			if( pObj != NULL )
			{
				pObj->Clear();
				
				if( m_Channels.GetSmartTaskPlan(pObj) )
				{
					
					ReportLog("ѡ������: %s(%d), ִ�д���:%d, ִ��ʱ��:%d, �豸��:%d.\n", 
						pObj->szTaskName, pObj->nTaskPlanID,  
						pObj->nRepeatTimes, pObj->nRepeatTime, pObj->nTask); 
				
					pObj->SetBeginTime();
					bRet = ExecuteTask(pObj) ;
				}
				else
				{
					bRet = false ;
				}
			}
			else
			{
				OnError("���ܷ����µ��������, ϵͳ��æ!");
			}
			
			if( pObj != NULL && !bRet )
			{
				for(int j=0; j< pObj->nTask; j++)
				{
					TSResultData  data;
					ZeroMemory(&data, sizeof(data));

					strcpy(data.sMsg, "������ִ��!");
					m_Channels.ReportTaskResult(&pObj->pTask[j], RET_SYSERROR, &data);
				}

				delete pObj;
				pObj = NULL ;
			}
			/*if(pObj != NULL && bRet)
			{
				delete pObj;
				pObj = NULL;
			}*/

			if( GetTickCount() - nTick > 400 )
			{
				
				m_Channels.SendTick();
				nTick = GetTickCount();

			}
			

			Sleep(100);
		}
		m_OutThread.Shutdown();
	}
	catch(TException& e)
	{
		ReportError(e.GetText());
		printf("------ e error ----\n");
		Shutdown();
	}
	catch(...)
	{
		ReportError("δ֪�Ĵ����·�������ֹ!");
//		printf("δ֪�Ĵ����·�������ֹ\n");
		Shutdown();
	}

	PostQuitMessage(0);
}

//�Ƿ���̫�������
bool TSmartServer::IsFullTask()
{
	return GetBusyTask()>MAX_BUSY_TASK?true:false;
}

//�õ���ǰ�������е�������
long TSmartServer::GetBusyTask()
{
	m_TaskLock.Lock();
	long nCount = m_TaskList.GetCount();
	m_TaskLock.Unlock();

	return nCount;
}

//*=================================================================================
//*ԭ��: TSmartTaskObj* TSmartServer::GetFreeTaskObj()
//*����: �õ�һ�����е������ڴ��
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
TSmartTaskObj* TSmartServer::GetFreeTaskObj()
{
	m_FreeTaskLock.Lock();

	TSmartTaskObj *pObj = NULL ;

	if( m_FreeTaskList.GetCount() <= 0 )
	{
		pObj = new TSmartTaskObj;
		if( pObj == NULL )
			return NULL;
	}
	else
	{
		pObj = (TSmartTaskObj*)m_FreeTaskList[0];
		if( pObj != NULL )
			m_FreeTaskList.Remove(pObj);
	}

	m_FreeTaskLock.Unlock();

	return pObj;
}

//*=================================================================================
//*ԭ��: void TSmartServer::AddToFreeTaskList(TSmartTaskObj *pObj)
//*����: ��һ�����������뵽���е������б�
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::AddToFreeTaskList(TSmartTaskObj *pObj) 
{
	m_TaskLock.Lock();
	m_TaskList.Remove(pObj);
	m_TaskLock.Unlock();

	m_FreeTaskLock.Lock();
	if( pObj != NULL )
	{
		if( m_FreeTaskList.GetCount() < MAX_FREE_TASK )
		{
			pObj->Clear();
			m_FreeTaskList.Add(pObj);
		}
		else
		{
			pObj->Release();
		}
	}
	m_FreeTaskLock.Unlock();
}

//*=================================================================================
//*ԭ��: void TSmartServer::ExecuteTask(TSmartTaskObj *pObj)
//*����: ��SmartTask���з�����ִ��
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
bool TSmartServer::ExecuteTask(TSmartTaskObj *pTaskObj)
{
	bool bResult = false ;

	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			long iCount = pTaskObj->GetChildTaskCount(pObj);
			
			for(int t=0; t< iCount; t++)
			{
				long nIndex = pTaskObj->GetChildTask(pObj, t);
				if( nIndex >= 0 )
				{
					//����ִ��
					//printf("!!!!!!!!!!!!!!!!!!!1����ִ��!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					if( pObj->IsExecuted() )
					{
						if( pObj->GetPriority() < pTaskObj->GetPriority(nIndex) )
						{
							ReportLog("����:%s(%d), �������:%s, �豸:%d, ��ͣԭ������!", 
								pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
								pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
							pObj->Pause();

							pTaskObj->SetBeginFlag(nIndex);
							if( !pObj->Execute(pTaskObj, nIndex) )
							{
								ReportLog("����:%s(%d), �������:%s, �豸:%d, ����ִ���µ�����!", 
									pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
									pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								pObj->DestoryStack();
						
							}
							else 
							{
								pObj->DestoryStack();
								printf("����:%s(%d), �������:%s, �豸:%d, ִ�гɹ�!\n", 
								pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
								pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
								bResult = true ;
							}
						}
						else
						{
							if( pObj->IsOpen() )
							{
								pTaskObj->SetBeginFlag(nIndex);
								printf("------------------------------------------\n");
								if( !pObj->AddToTaskStack(pTaskObj, nIndex) )
								{
									ReportLog("����:%s(%d), �������:%s, �豸:%d,  �豸æ, ����ִ���µ�����!", 
										pTaskObj->szTaskName, pTaskObj->nTaskPlanID, 
										pTaskObj->pTask[nIndex].szTaskCode, pObj->m_nAuthID);
									pObj->DestoryStack();
								}
								else
								{
									bResult = true ;

									Sleep(50);
								}
							}
						} 
					}
					//û��ִ��
					else 
					{
						//printf("-----δִ��----nIndex=%d---\n",nIndex);
						bResult = true ;
						pTaskObj->SetBeginFlag(nIndex);
						if( !pObj->Execute(pTaskObj, nIndex) )
						{
//							printf("------ִ��-----\n");
							Sleep(50);
							pObj->Execute(pTaskObj, nIndex);
						}
						//else
						//	printf("-----δִ��-----\n");
					}
				}
			}//for
		}
	}//for
	m_DocLock.Unlock();

	return bResult;
}

//*=================================================================================
//*ԭ��: BOOL TSmartServer::AddSmartDoc(TSmartDocObj *pDocObj)
//*����: ����һ���豸
//*����: pDocObj -- �豸��Ϣ
//*����: �ɹ����
//*˵��: ǰ�òɼ���������
//*=================================================================================
BOOL TSmartServer::AddSmartDoc(TSmartDocObj *pDocObj)
{
	m_DocLock.Lock();
	m_DocList.Add(pDocObj);
	m_DocLock.Unlock();
	return TRUE;
}

//*=================================================================================
//*ԭ��: BOOL TSmartServer::DelSmartDoc(TSmartDocObj *pDocObj)
//*����: ɾ��һ���豸
//*����: pDocObj -- �豸��Ϣ
//*����: �ɹ����
//*˵��: ǰ�òɼ���������
//*=================================================================================
BOOL TSmartServer::DelSmartDoc(TSmartDocObj *pDocObj)
{
	if( pDocObj->m_nParentID > 0 )
	{
		m_DocLock.Lock();
		m_DocList.Remove(pDocObj);
		m_DocLock.Unlock();

		pDocObj->Release();
	}
	else
	{

	}

	return TRUE;
}

long TSmartServer::GetDocCount()
{ 
	long i=m_DocList.GetCount();
	return i; 
}


//*=================================================================================
//*ԭ��: BOOL TSmartServer::StopSmartDoc(TSmartDocObj *pDocObj)
//*����: ֹͣһ���豸
//*����: pDocObj -- �豸��Ϣ
//*����: �ɹ����
//*˵��: ǰ�òɼ���������
//*=================================================================================
BOOL TSmartServer::StopSmartDoc(TSmartDocObj *pDocObj)
{
//	return m_DriverPool.StopSmartDoc(pDocObj);
	return TRUE;
}


//*=================================================================================
//*ԭ��: BOOL StartSmrtDoc(TSmartDocObj *pDocObj)
//*����: ����һ���豸
//*����: pDocObj -- �豸��Ϣ
//*����: �ɹ����
//*˵��: ǰ�òɼ���������
//*=================================================================================
BOOL TSmartServer::StartSmartDoc(TSmartDocObj *pDocObj)
{
	try
	{
		pDocObj->Start();
	}
	catch(TException& e)
	{
		OnError((char*)e.GetText());
		return FALSE;
	}
	return TRUE;
}

void TSmartServer::FinishedTask(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex)
{
	//�����������
	printf("----�����������!\n");
	m_Channels.ReportFinished(pTaskObj);
	pTaskObj->ReportFinished();
	delete pTaskObj;
}

//*=================================================================================
//*ԭ��: void TSmartServer::Noti fyTaskFinished(TSmartDocObj *pDocObj)
//*����: ֪ͨ�˿��ϵĵ�ǰ�������
//*����: pDocObj  -- �豸��Ϣ
//*      pTaskObj -- ������Ϣ
//*      nIndex   -- �ն˶�Ӧ���豸����
//*����: �ɹ����
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::NotifyTaskFinished(TSmartDocObj *pDocObj, TSmartTaskObj *pTaskObj, long nIndex)
{
	//�ܵ������ѽ���
	if( pTaskObj->IsTaskFinished() )
	{
		AddToFreeTaskList(pTaskObj);
		return ;
	}

	//��ͷ����ִ��
	if( pTaskObj->IsContinue(nIndex) )
	{
		long nIndex = pTaskObj->GetMaxPriorityTask(pDocObj);
		if( pDocObj->GetIOStatus() == IO_Status_Free )
		{
			pDocObj->Execute(pTaskObj, nIndex);
		}
	}
	else
	{
		//�б��жϵ�����
		if( pDocObj->HaveHistoryTask() )
		{
			//����ִ��
			pDocObj->Continue();
		}
	}
}

//*=================================================================================
//*ԭ��: void TSmartServer::OnError(LPTSTR pszErrorText)
//*����: ���������д���
//*����: pszErrorText   -- ������Ϣ
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::OnError(LPTSTR pszErrorText)
{

}

//*=================================================================================
//*ԭ��: void TSmartServer::OnNetError(TSmartDocObj *pObj, int nError)
//*����: ���������Э�����
//*����: pObj   -- �������
//*      nError -- �������
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::OnNetError(TSmartDocObj *pObj, int nError)
{


}

//*=================================================================================
//*ԭ��: void TSmartServer::OnDocError(TSmartDocObj *pObj, char *pszError)
//*����: �豸����
//*����: pObj   -- �������
//*      pszError -- ����
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::OnDocError(TSmartDocObj *pObj, char *pszError)
{
	char szText[512];

	sprintf(szText, "%d&%s", pObj->m_nAuthID, pszError);
	WriteLog(szText);
}

//*=================================================================================
//*ԭ��: void TSmartServer::Monitor()
//*����: �Է��������(ҵ����������ݿ���)
//*����: ��
//*����: ��
//*˵��: ǰ�òɼ���������
//*=================================================================================
void TSmartServer::Monitor()
{

}

//*=================================================================================
//*ԭ��: long TSmartServer::SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
//*����: ���Ͳ���������
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	if( pDoc == NULL )
		return RET_PARAMETER_ERROR1;

	TSmartDocObj *pObj = NULL ;

	if( pDoc->m_nParentID > 0 )
	{
		pObj = GetParentDoc(pDoc->m_nParentID);
	}
	else
	{
		pObj = (TSmartDocObj*)pDoc;
	}

	if( pObj == NULL )
		return RET_PARAMETER_ERROR1;

	//������API���������û����ִ������
	if( pObj->GetIOStatus() == IO_Status_ExecuteApi || 
		pObj->GetIOStatus() != IO_Status_ExecuteCall )
	{
		return RET_PARAMETER_ERROR1;
	}

	return pObj->SendRequest((TCmdBuffer*)pBuffer);
}

//*=================================================================================
//*ԭ��: long TSmartServer::BroadData(long nAuthID, char *pszBuffer, long nBufSize)
//*����: �㲥����--���ɼ������ݹ㲥������ն˻���
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::BroadData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	m_OutThread.Broadcast(pDoc, pBuffer->pBuffer, pBuffer->nCmdSize);
	return RET_OK;
}

void TSmartServer::BroadDataEx(char *pszBuffer, long nLength)
{
	m_OutThread.Broadcast(NULL, pszBuffer, nLength);
}

void TSmartServer::BroadcastPro(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize)
{
	m_OutThread.BroadcastEx(pszCmd, pDoc, pData, nSize);
}

TSmartDocObj* TSmartServer::GetParentDoc(long nParent)
{
//	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nParent )
			{
				//m_DocLock.Unlock();
				return pObj;
			}
		}
	}
//	m_DocLock.Unlock();

	return NULL;
}

//*=================================================================================
//*ԭ��: long AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc)
//*����: ������һ̨�豸, �����ն˻�ǩ��
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc)
{
	bool bResult = false ;

	m_DocLock.Lock();

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nParentID )
			{
				//���������ڴ��е����豸
				if( !pObj->IsChildDoc(pDoc->m_nAuthID) )
				{
					TSSmartDoc *pNewDoc = new TSSmartDoc;
					memcpy(pNewDoc, pDoc, sizeof(TSSmartDoc));
					pObj->AddChildDoc(pNewDoc);
				}
				bResult = true;
				break;
			}
		}
	}
	m_DocLock.Unlock();

	return bResult?RET_OK:RET_NG;
}

//*=================================================================================
//*ԭ��: long DelSmartDoc(long nAuthID)
//*����: ɾ��һ̨�豸
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::DelSmartDoc(long nAuthID)
{
	return RET_OK;
}

long TSmartServer::EnableDevice(long nAuthID, bool bEnable)
{
	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->Enable(nAuthID, bEnable) ) 
			{
				break;
			}
		}
	}

	m_DocLock.Unlock();

	return RET_OK;
}

long TSmartServer::GetDeviceInfo(long nAuthID, TSDocInfo *pDocInfo)
{
	bool bFound = false;

	m_DocLock.Lock();
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			if( pObj->m_nAuthID == nAuthID )
			{
				pObj->GetInfo(0, pDocInfo);
				bFound = true;
				break;
			}
			else if( pObj->IsChildDoc(nAuthID) )
			{
				pObj->GetInfo(nAuthID, pDocInfo);
				bFound = true;
				break;
			}
		}
	}
	m_DocLock.Unlock();

	if( !bFound )
	{
		pDocInfo->m_nAuthID = nAuthID;
		pDocInfo->m_nChild = 0;
		pDocInfo->m_nStatus = 2;
		strcpy(pDocInfo->m_szTaskCode, "δ����!");
	}

	return RET_OK;
}

void TSmartServer::SendInitData(SOCKET hSocket, SOCKADDR_IN *psockAddr)
{
	TSmartPacket Packet;
	char *pBuffer = NULL ;
	long  nLength = 0 ;
	char  szTemp[256];

	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pObj = (TSmartDocObj*)m_DocList[i];
		if( pObj != NULL )
		{
			sprintf(szTemp, "%d&%d&%d&%s&%d&%d&%d", 
				pObj->m_nAuthID, pObj->m_nDealCount, pObj->m_nFlow, 
				pObj->m_sLastDealTime, pObj->m_nCardID, pObj->m_nInMoney, 
				pObj->m_nOutMoney);

			Packet.Create(PACKET_CMD_1002, SERVER_SID);
			Packet.SetResult(RET_OK);
			Packet.AddItem((char*)szTemp, strlen(szTemp));
			Packet.AddEnd();

			pBuffer = Packet.GetBuffer();
			nLength = Packet.GetLength();

			sendto(hSocket, pBuffer, nLength, 0, (SOCKADDR*)psockAddr, sizeof(SOCKADDR_IN));

			//���豸�������
			for(int k=0; k< pObj->m_ChildDoc.GetCount(); k++)
			{
				TSSmartDoc *pSmartDoc = (TSSmartDoc *)pObj->m_ChildDoc[k];
				if( pSmartDoc != NULL )
				{
					sprintf(szTemp, "%d&%d&%d&%s&%d&%d&%d", 
						pSmartDoc->m_nAuthID, pSmartDoc->m_nDealCount, pSmartDoc->m_nFlow, 
						pSmartDoc->m_sLastDealTime, pSmartDoc->m_nCardID, pSmartDoc->m_nInMoney, 
						pSmartDoc->m_nOutMoney);

					Packet.Create(PACKET_CMD_1002, SERVER_SID);
					Packet.SetResult(RET_OK);
					Packet.AddItem((char*)szTemp, strlen(szTemp));
					Packet.AddEnd();

					pBuffer = Packet.GetBuffer();
					nLength = Packet.GetLength();

					sendto(hSocket, pBuffer, nLength, 0, (SOCKADDR*)psockAddr, sizeof(SOCKADDR_IN));
				}
			}
		}
	}
}

//*=================================================================================
//*ԭ��: long TSmartServer::FindBusFromDocArray(TSSmartDoc *pSmartDoc, long i, long nRecCount)
//*����: ��δ����ĵ������в�����ͬ����������
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::FindBusFromDocArray(TSSmartDoc *pSmartDoc, long i, long nRecCount)
{
	for(long k=i+1; k< nRecCount; k++)
	{
		if( !strcmp(pSmartDoc[i].m_szAddr, pSmartDoc[k].m_szAddr) && 
			!strcmp(pSmartDoc[i].m_szPort, pSmartDoc[k].m_szAddr) )
		{
			return k;
		}
	}

	return -1;
}

//*=================================================================================
//*ԭ��: long TSmartServer::FindBusFromDocList(TSmartDocObj *pDoc)
//*����: ���Ѽ���ĵ������в�����ͬ����������
//*����: ��
//*����: ��
//*˵��: �������ṩ���ⲿ��API
//*=================================================================================
long TSmartServer::FindBusFromDocList(TSmartDocObj *pDoc)
{
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(i);
		if( pBus != NULL )
		{
			if( !strcmp(pBus->m_szAddr, pDoc->m_szAddr) && 
				!strcmp(pBus->m_szPort, pDoc->m_szAddr) )
			{
				return i;
			}
		}
	}

	return -1;
}

void TSmartServer::AssignBusHandle(TSmartDocObj *pDoc)
{
	for(long i=0; i< m_DocList.GetCount(); i++)
	{
		TSmartDocObj *pBus = (TSmartDocObj*)m_DocList.Get(i);
		if( pBus != NULL && pDoc != pBus )
		{
			if( !strcmp(pBus->m_szAddr, pDoc->m_szAddr) && 
				!strcmp(pBus->m_szPort, pDoc->m_szAddr) && 
				pBus->m_nCommMode == pDoc->m_nCommMode )
			{
				pBus->SetHandle(pDoc->GetHandle());
				pBus->SetReadOver(&pDoc->m_ReadOver);
				pBus->SetWriteOver(&pDoc->m_WriteOver);
			}
		}
	}
}
