// TSmartTask.cpp: implementation of the TSmartTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartDoc.h"
#include "TSmartTask.h"

//*=================================================================================
//*原型: TSmartTask::TSmartTask()
//*功能: 调用任务业务动态库读取任务与更新任务
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
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
//*原型: void TSmartTask::Initialized(LPCTSTR pszFileName)
//*功能: 初始化任务库
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
//*=================================================================================
void TSmartTask::Initialized(LPCTSTR pszFileName)
{
	m_hModule = LoadLibrary(pszFileName);
	if( m_hModule == NULL )
		throw TException("不能装入任务管理动态库!", GetLastError());

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
		throw TException("不是合法的任务管理动态库!");
	}

	if( InitTaskDLL(&SmartFunction) != RET_OK )
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL ;
		throw TException("任务管理动态库初始化错误!");
	}
}

//*=================================================================================
//*原型: void TSmartTask::Destory()
//*功能: 销毁任务库
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
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
//*原型: BOOL TSmartTask::GetSmartTaskPlan(TSmartTaskObj *pTaskPlan)
//*功能: 得到一个任务
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
//*=================================================================================
BOOL TSmartTask::GetSmartTaskPlan(TSmartTaskObj *pTaskPlan)
{
	static long i= 0 ;
	long nResult;

	if( !i )
	{
		ReportLog("第一次运行, 读入常驻任务信息!");
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
//*原型: BOOL TSmartTask::GetSmartTaskPlanEx(TSmartTaskObj *pTaskPlan)
//*功能: 得到一个常驻型的任务
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
//*=================================================================================
BOOL TSmartTask::GetSmartTaskPlanEx(TSmartTaskObj *pTaskPlan)
{
	return FALSE;
}

//*=================================================================================
//*原型: BOOL TSmartTask::ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
//*功能: 任务处理
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
//*=================================================================================
BOOL TSmartTask::ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
{
	if( TaskReplace(pTaskPlan) != RET_OK )
	{
		//任务更新错, 发出严重警告信息
		char   sBuffer[4096];

		memset(sBuffer, 0, sizeof(sBuffer));
		sBuffer[0] = 9 ;
		sBuffer[1] = 9 ;
		strcpy(&sBuffer[2], "严重警告信息:任务更新错!");
		SendMsg(sBuffer, strlen(sBuffer));
		return FALSE;
	}

	return TRUE;
}

//*=================================================================================
//*原型: BOOL ReplaceTaskPlan(TSmartTaskObj *pTaskPlan)
//*功能: 还原任务的选中状态
//*参数: 略
//*返回: 成功与否
//*说明: 任务处理
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
//*原型: void TSmartTaskObj::SetTaskResult(long nIndex, long nRet)
//*功能: 设置单个任务的返回结果
//*参数: 略
//*返回: 无
//*说明: 任务管理类
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
//*原型: long TSmartTaskObj::GetPriority(long nIndex)
//*功能: 得到对应终端任务的优先级
//*参数: 略
//*返回: 无
//*说明: 任务管理类
//*=================================================================================
long TSmartTaskObj::GetPriority(long nIndex)
{
	return pTask[nIndex].nPriority;
}

//*=================================================================================
//*原型: bool TSmartTaskObj::IsTaskFinished()
//*功能: 所有的子任务是否结束, 本次任务是否结束
//*参数: 略
//*返回: 无
//*说明: 任务管理类
//*=================================================================================
bool TSmartTaskObj::IsTaskFinished()
{
	bool bEnd = true ;

	//持续时间不限, 次数不限
	if( nRepeatTime == 0 && nRepeatTimes == 0 )
		return false;
	if( nRepeatTime == 0 || nRepeatTimes == 0 )
	{
		//每个设备对应的任务均中断, 则会结束
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

		//持续时间不限, 次数限制
		if( nRepeatTime == 0 && nRepeatTimes )
		{
			if( pTask[i].nRepeat1 < nRepeatTimes )
			{
				bEnd = false ;
				break;
			}
		}
		//次数不限, 持续时间限制
		else if( nRepeatTime && nRepeatTimes == 0 )
		{
			if( pTask[i].nRepeat2 < nRepeatTime )
			{
				bEnd = false ;
				break;
			}
		}
		//持续时间限制, 次数限制
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
//*原型: bool TSmartTaskObj::IsContinue(long nIndex)
//*功能: 本子任务是否要继续执行下去
//*参数: 略
//*返回: 无
//*说明: 任务管理类
//*=================================================================================
bool TSmartTaskObj::IsContinue(long nIndex)
{
	if( nIndex < 0 || nIndex >= nTask )
		return false;

	//被中断的则会结束
	if( pTask[nIndex].nTerminate == 1 )
		return false;

	//持续时间不限, 次数不限, 继续执行
	if( nRepeatTime == 0 && nRepeatTimes == 0 )
		return true;

	//持续时间不限, 次数限制
	if( nRepeatTime == 0 && nRepeatTimes )
	{
		if( pTask[nIndex].nRepeat1 < nRepeatTimes )
		{
			return true;
		}
	}
	//次数不限, 持续时间限制
	else if( nRepeatTime && nRepeatTimes == 0 )
	{
		if( pTask[nIndex].nRepeat2 < nRepeatTime )
		{
			return true ;
		}
	}
	//持续时间限制, 次数限制
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
//*原型: long TSmartTaskObj::GetMaxPriorityTask(TSmartDocObj *pDocObj)
//*功能: 得到本设备将要执行的优先级最大的任务索引
//*参数: 略
//*返回: 无
//*说明: 任务管理类
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

	//同一个设备可能存在多个任务, 多个不同的优先级
	while( pTask[nPos].nAuthID == pDocObj->m_nAuthID || 
		pDocObj->IsChildDoc(pTask[i].nAuthID) )
	{
		//持续时间不限, 次数不限, 各个任务轮流执行
		//如果有限制, 则优先级最高的任务执行完后才执行下一个任务
		if( nRepeatTime == 0 && nRepeatTimes == 0 )
		{
			//按执行次数来决定轮流执行
			if( pTask[nPos].nRepeat1 < nTry )
			{
				nTry = pTask[nPos].nRepeat1 ;
				nIndex = nPos;
			}
		}
		//持续时间不限, 次数限制, 
		else if( nRepeatTime == 0 && nRepeatTimes )
		{
			if( pTask[i].nRepeat1 < nRepeatTimes )
			{
				nIndex = nPos ;
				break;
			}
		}
		//次数不限, 持续时间限制
		else if( nRepeatTime && nRepeatTimes == 0 )
		{
			if( pTask[i].nRepeat2 < nRepeatTime )
			{
				nIndex = nPos ;
				break;
			}
		}
		//持续时间限制, 次数限制
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
//*原型: void TSmartTaskObj::SetFinished(long nIndex)
//*功能: 设置子任务结束
//*参数: 略
//*返回: 无
//*说明: 任务管理类
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
//*原型: void TSmartTaskObj::ReportFinished()
//*功能: 写任务结束日志
//*参数: 略
//*返回: 无
//*说明: 任务管理类
//*=================================================================================
void TSmartTaskObj::ReportFinished()
{
	char   strText[28192];
	char   strString[1024];
	char   szTime[24];
	long   nOK = 0, nFaild = 0 ;
	char   pszResult[256];

	GetCurDateTime(szTime);

	sprintf(strText,"******任务计划(%d):%s 开始时间:%s****结束时间:%d***设备数:%d****成功数:%d****\n", 
		nTaskPlanID, szTaskName, m_szDateTime, szTime, nTask, nTask);

	for(int i=0; i< nTask; i++)
	{
		GetResultMessage(pTask[i].nResult, pszResult);

		sprintf(strString, "设备(%d) ID号:%s 机型:%s 任务代码:%s 开始时间:%s  结束时间:%s  运行时长:%d  结果(%d):%s\n",
			pTask[i].nAuthID, "", "", pTask[i].szTaskCode, 
			m_szDateTime, pTask[i].szRunTime, 
			pTask[i].nRepeat2, pTask[i].nResult, pszResult);
		strcat(strText,strString);
	}

	strcat(strText,"************************************************************************************\n\n");
	WriteTaskLog(strText);
}
