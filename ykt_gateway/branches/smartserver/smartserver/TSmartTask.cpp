// TSmartTask.cpp: implementation of the TSmartTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartDoc.h"
#include "TSmartTask.h"

//*=================================================================================
//*ԭ��: TSmartTask::TSmartTask()
//*����: ��������ҵ��̬���ȡ�������������
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
TSmartTask::TSmartTask()
{
	lstrcpy(m_szFileName, "");
	m_hModule = NULL ;

    InitTaskDLL = NULL ;
	DestoryTaskDLL = NULL ;
	ReadTask = NULL ;
	ReadTSRTask = NULL ;
	TaskReplace = NULL ;
	GetTimeOutMap = NULL ;
	UpdateTask = NULL ;
}

TSmartTask::~TSmartTask()
{
	Destory();
}

//*=================================================================================
//*ԭ��: void TSmartTask::Initialized(LPCTSTR pszFileName)
//*����: ��ʼ�������
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
void TSmartTask::Initialized(LPCTSTR pszFileName)
{
	m_hModule = LoadLibrary(pszFileName);
	if( m_hModule == NULL )
		throw TException("����װ���������̬��!", GetLastError());

    InitTaskDLL = (lpfnInitTaskDLL)GetProcAddress(m_hModule, "InitTaskDLL");
    DestoryTaskDLL = (lpfnDestoryTaskDLL)GetProcAddress(m_hModule, "DestoryTaskDLL");
    ReadTask = (lpfnReadTask)GetProcAddress(m_hModule, "ReadTask");
    ReadTSRTask = (lpfnReadTSRTask)GetProcAddress(m_hModule, "ReadTSRTask");
    TaskReplace = (lpfnTaskReplace)GetProcAddress(m_hModule, "TaskReplace");
    GetTimeOutMap = (lpfnGetTimeOutMap)GetProcAddress(m_hModule, "GetTimeOutMap");
	UpdateTask =  (lpfnUpdateTask)GetProcAddress(m_hModule, "UpdateTask");
	ReadSmartDocInfo =  (lpfnReadSmartDocInfo)GetProcAddress(m_hModule, "ReadSmartDocInfo");
	ReleaseSmartDoc =  (lpfnReleaseSmartDoc)GetProcAddress(m_hModule, "ReleaseSmartDoc");

	if( !InitTaskDLL || !DestoryTaskDLL || !ReadTask || 
		!ReadTSRTask || !TaskReplace || !GetTimeOutMap || !UpdateTask || 
		!ReadSmartDocInfo || !ReleaseSmartDoc )
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL ;
		throw TException("���ǺϷ����������̬��!");
	}

	if( InitTaskDLL(&SmartFunction) != RET_OK )
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL ;
		throw TException("�������̬���ʼ������!");
	}
}

//*=================================================================================
//*ԭ��: void TSmartTask::Destory()
//*����: ���������
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
void TSmartTask::Destory()
{
	if( m_hModule != NULL )
	{
		DestoryTaskDLL();

		FreeLibrary(m_hModule);
		m_hModule = NULL ;
	}
}

//*=================================================================================
//*ԭ��: BOOL TSmartTask::GetSmartTaskPlan(TSmartTaskObj *pTaskPlan)
//*����: �õ�һ������
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
BOOL TSmartTask::GetSmartTaskPlan(TSmartTaskObj *pTaskPlan)
{
	static long i= 0 ;
	long nResult;

	if( !i )
	{
		ReportLog("��һ������, ���볣פ������Ϣ!");
		nResult = ReadTSRTask(pTaskPlan);
	}
	else
	{
		nResult = ReadTask(pTaskPlan);
	}

	if( i++ > 9999999 )
		i = 1 ;
	return (nResult==RET_OK?TRUE:FALSE);
}

//*=================================================================================
//*ԭ��: BOOL TSmartTask::GetSmartTaskPlanEx(TSmartTaskObj *pTaskPlan)
//*����: �õ�һ����פ�͵�����
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
BOOL TSmartTask::GetSmartTaskPlanEx(TSmartTaskObj *pTaskPlan)
{
	return FALSE;
}

//*=================================================================================
//*ԭ��: BOOL TSmartTask::ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
//*����: ������
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
BOOL TSmartTask::ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
{
	if( TaskReplace(pTaskPlan) != RET_OK )
	{
		//������´�, �������ؾ�����Ϣ
		char   sBuffer[4096];

		memset(sBuffer, 0, sizeof(sBuffer));
		sBuffer[0] = 9 ;
		sBuffer[1] = 9 ;
		strcpy(&sBuffer[2], "���ؾ�����Ϣ:������´�!");
		SendMsg(sBuffer, strlen(sBuffer));
		return FALSE;
	}

	return TRUE;
}

//*=================================================================================
//*ԭ��: BOOL ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
//*����: ��ԭ�����ѡ��״̬
//*����: ��
//*����: �ɹ����
//*˵��: ������
//*=================================================================================
BOOL TSmartTask::UpdateTaskStatus(TSmartTaskObj *pTaskPlan)
{
	return (UpdateTask(pTaskPlan)==RET_OK?TRUE:FALSE);
}

void TSmartTask::GetSmartTimeOut(TSSmartTimeOut *pSmartTimeOut)
{
	nSmartTimeOut = 0 ;
	ZeroMemory(SmartTimeOut, sizeof(SmartTimeOut));
}


TSmartTaskObj::TSmartTaskObj()
{
	Reset();
}

TSmartTaskObj::~TSmartTaskObj()
{

}

void TSmartTaskObj::Clear()
{
	nTask = 0 ;

	Reset();
}

void TSmartTaskObj::Reset()
{
	nTaskPlanID = 0 ;
    strcpy(szTaskName, "");
	nTaskCycle = 0 ;
	strcpy(szBeginTime, "");
	nRepeatTime = 1 ;
	nRepeatTimes = 1 ;
	strcpy(szPlan, "");
	strcpy(szNextRunTime, "");
	strcpy(szPriorRunTime, "");
	nPriorRetrun = 0 ;
	strcpy(szTaskTime, "");
	strcpy(szMemo, "");

	ZeroMemory(pTask, sizeof(pTask));
	nTask = 0 ;
}

bool TSmartTaskObj::IsTSRTask() const
{
	return TRUE;
}

bool TSmartTaskObj::IsFinished() const
{
	return FALSE;
}

int TSmartTaskObj::GetTaskResult() const
{
	return m_Result;
}

//*=================================================================================
//*ԭ��: void TSmartTaskObj::SetTaskResult(long nIndex, long nRet)
//*����: ���õ�������ķ��ؽ��
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
void TSmartTaskObj::SetTaskResult(long nIndex, long nRet, long nTerminate)
{
	if( nIndex < 0 || nIndex >= nTask )
		return ;

	strcpy(pTask[nIndex].szSystemRCode, "");
	pTask[nIndex].nResult = nRet ;

	GetCurDateTime(pTask[nIndex].szRunTime);

	strcpy(pTask[nIndex].szSystemRCode, "");
	pTask[nIndex].nRepeat1++;
	pTask[nIndex].nRepeat2 = (GetTickCount()-pTask[nIndex].nTick)/(1000*60);
	pTask[nIndex].nTerminate = nTerminate ;
}

void TSmartTaskObj::Release()
{

}

//*=================================================================================
//*ԭ��: long TSmartTaskObj::GetPriority(long nIndex)
//*����: �õ���Ӧ�ն���������ȼ�
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
long TSmartTaskObj::GetPriority(long nIndex)
{
	return pTask[nIndex].nPriority;
}

//*=================================================================================
//*ԭ��: bool TSmartTaskObj::IsTaskFinished()
//*����: ���е��������Ƿ����, ���������Ƿ����
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
bool TSmartTaskObj::IsTaskFinished()
{
	bool bEnd = true ;

	//����ʱ�䲻��, ��������
	if( nRepeatTime == 0 && nRepeatTimes == 0 )
		return false;
	if( nRepeatTime == 0 || nRepeatTimes == 0 )
	{
		//ÿ���豸��Ӧ��������ж�, ������
		for(long k=0; k< nTask; k++ )
		{
			if( !pTask[k].nTerminate )
			{
				bEnd = false;
			}
		}
		if( bEnd )  
		{
			return true;
		}
	}
	else
		return true;
/*	
	m_lock.Lock();

	for(long i=0; i< nTask; i++ )
	{
		if( pTask[i].nTerminate == 1 )
			continue;

		//����ʱ�䲻��, ��������
		if( nRepeatTime == 0 && nRepeatTimes )
		{
			if( pTask[i].nRepeat1 < nRepeatTimes )
			{
				bEnd = false ;
				break;
			}
		}
		//��������, ����ʱ������
		else if( nRepeatTime && nRepeatTimes == 0 )
		{
			if( pTask[i].nRepeat2 < nRepeatTime )
			{
				bEnd = false ;
				break;
			}
		}
		//����ʱ������, ��������
		else if( nRepeatTime && nRepeatTimes )
		{
			if( pTask[i].nRepeat2 < nRepeatTime && pTask[i].nRepeat1 < nRepeatTimes )
			{
				bEnd = false ;
				break;
			}
		}
	}

	m_lock.Unlock();
*/
	return bEnd ;
}

//*=================================================================================
//*ԭ��: bool TSmartTaskObj::IsContinue(long nIndex)
//*����: ���������Ƿ�Ҫ����ִ����ȥ
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
bool TSmartTaskObj::IsContinue(long nIndex)
{
	if( nIndex < 0 || nIndex >= nTask )
		return false;

	//���жϵ�������
	if( pTask[nIndex].nTerminate == 1 )
		return false;

	//����ʱ�䲻��, ��������, ����ִ��
	if( nRepeatTime == 0 && nRepeatTimes == 0 )
		return true;

	//����ʱ�䲻��, ��������
	if( nRepeatTime == 0 && nRepeatTimes )
	{
		if( pTask[nIndex].nRepeat1 < nRepeatTimes )
		{
			return true;
		}
	}
	//��������, ����ʱ������
	else if( nRepeatTime && nRepeatTimes == 0 )
	{
		if( pTask[nIndex].nRepeat2 < nRepeatTime )
		{
			return true ;
		}
	}
	//����ʱ������, ��������
	else if( nRepeatTime && nRepeatTimes )
	{
		if( pTask[nIndex].nRepeat2 < nRepeatTime && pTask[nIndex].nRepeat1 < nRepeatTimes )
		{
			return true ;
		}
	}

	return false;
}

long TSmartTaskObj::GetChildTaskCount(TSmartDocObj *pDocObj)
{
	long iCount = 0 ;

	for(long i=0; i< nTask; i++)
	{
		if( pTask[i].nAuthID == pDocObj->m_nAuthID || 
			pDocObj->IsChildDoc(pTask[i].nAuthID) )
		{
			iCount++;
		}
	}

	return iCount;
}

long TSmartTaskObj::GetChildTask(TSmartDocObj *pDocObj, int iIndex)
{
	long iCount = -1 ;

	for(long i=0; i< nTask; i++)
	{
		if( pTask[i].nAuthID == pDocObj->m_nAuthID || 
			pDocObj->IsChildDoc(pTask[i].nAuthID) )
		{
			if( ++iCount == iIndex )
			{
				return i;
			}			
		}
	}

	return -1;
}

long TSmartTaskObj::GetNextTask(TSmartDocObj *pDocObj)
{
	long nIndex = -1;
	long nPos = -1 ;

	int nTotal = GetChildTaskCount(pDocObj);

	for(long i=0; i< nTask; i++)
	{
		if( pTask[i].nAuthID == pDocObj->m_nAuthID || 
			pDocObj->IsChildDoc(pTask[i].nAuthID) )
		{
			if( nTotal <= 1 )
				return i;
			else if( !pTask[i].nTerminate ) 
			{
				if( pTask[i].nRepeat1 <= 0 || (nRepeatTime<=0 || nRepeatTimes<=0)  ) 
				{
					return i;
				}
			}
		}
	}

	return -1;
}

//*=================================================================================
//*ԭ��: long TSmartTaskObj::GetMaxPriorityTask(TSmartDocObj *pDocObj)
//*����: �õ����豸��Ҫִ�е����ȼ�������������
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
long TSmartTaskObj::GetMaxPriorityTask(TSmartDocObj *pDocObj)
{
	long nIndex = -1;
	long nPos = -1 ;

	for(long i=0; i< nTask; i++)
	{
		if( pTask[i].nAuthID == pDocObj->m_nAuthID || pDocObj->IsChildDoc(pTask[i].nAuthID) )
		{
			nPos = i ;
			break;
		}
	}

	if( nPos < 0 || nPos >= nTask )
		return -1 ;

	long nTry = 9999999;

	//ͬһ���豸���ܴ��ڶ������, �����ͬ�����ȼ�
	while( pTask[nPos].nAuthID == pDocObj->m_nAuthID || 
		pDocObj->IsChildDoc(pTask[i].nAuthID) )
	{
		//����ʱ�䲻��, ��������, ������������ִ��
		//���������, �����ȼ���ߵ�����ִ������ִ����һ������
		if( nRepeatTime == 0 && nRepeatTimes == 0 )
		{
			//��ִ�д�������������ִ��
			if( pTask[nPos].nRepeat1 < nTry )
			{
				nTry = pTask[nPos].nRepeat1 ;
				nIndex = nPos;
			}
		}
		//����ʱ�䲻��, ��������, 
		else if( nRepeatTime == 0 && nRepeatTimes )
		{
			if( pTask[i].nRepeat1 < nRepeatTimes )
			{
				nIndex = nPos ;
				break;
			}
		}
		//��������, ����ʱ������
		else if( nRepeatTime && nRepeatTimes == 0 )
		{
			if( pTask[i].nRepeat2 < nRepeatTime )
			{
				nIndex = nPos ;
				break;
			}
		}
		//����ʱ������, ��������
		else if( nRepeatTime && nRepeatTimes )
		{
			if( pTask[i].nRepeat2 < nRepeatTime && pTask[i].nRepeat1 < nRepeatTimes )
			{
				nIndex = nPos ;
				break;
			}
		}

		if( nPos == nTask-1 )
			break;

		nPos++;
	}

	if( nPos > 0 )
		nPos--;

	if( nPos < 0 || nPos >= nTask )
		return -1 ;

	return nIndex;
}

//*=================================================================================
//*ԭ��: void TSmartTaskObj::SetFinished(long nIndex)
//*����: �������������
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
void TSmartTaskObj::SetFinished(long nIndex)
{
	if( nIndex < 0 || nIndex >= nTask )
		return ;

	GetCurDateTime(pTask[nIndex].szRunTime);
	strcpy(pTask[nIndex].szSystemRCode, "");

	pTask[nIndex].nResult = 0 ;
	pTask[nIndex].nRepeat1++;
	pTask[nIndex].nRepeat2 = (GetTickCount()-pTask[nIndex].nTick)/(1000*60);
}

void TSmartTaskObj::SetBeginFlag(long nIndex)
{
	if( nIndex < 0 || nIndex >= nTask )
		return ;

	pTask[nIndex].nTick = GetTickCount();
}

void TSmartTaskObj::SetBeginTime()
{
	GetCurDateTime(m_szDateTime);
}

//*=================================================================================
//*ԭ��: void TSmartTaskObj::ReportFinished()
//*����: д���������־
//*����: ��
//*����: ��
//*˵��: ���������
//*=================================================================================
void TSmartTaskObj::ReportFinished()
{
	char   strText[28192];
	char   strString[1024];
	char   szTime[24];
	long   nOK = 0, nFaild = 0 ;
	char   pszResult[256];

	GetCurDateTime(szTime);

	sprintf(strText,"******����ƻ�(%d):%s ��ʼʱ��:%s****����ʱ��:%d***�豸��:%d****�ɹ���:%d****\n", 
		nTaskPlanID, szTaskName, m_szDateTime, szTime, nTask, nTask);

	for(int i=0; i< nTask; i++)
	{
		GetResultMessage(pTask[i].nResult, pszResult);

		sprintf(strString, "�豸(%d) ID��:%s ����:%s �������:%s ��ʼʱ��:%s  ����ʱ��:%s  ����ʱ��:%d  ���(%d):%s\n",
			pTask[i].nAuthID, "", "", pTask[i].szTaskCode, 
			m_szDateTime, pTask[i].szRunTime, 
			pTask[i].nRepeat2, pTask[i].nResult, pszResult);
		strcat(strText,strString);
	}

	strcat(strText,"************************************************************************************\n\n");
	WriteTaskLog(strText);
}
