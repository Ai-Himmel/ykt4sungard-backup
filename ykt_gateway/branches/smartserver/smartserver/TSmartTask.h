// TSmartTask.h: interface for the TSmartTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTTASK_H__3D3910A5_6E9B_4640_B0E6_ACAA39E0C1E0__INCLUDED_)
#define AFX_TSMARTTASK_H__3D3910A5_6E9B_4640_B0E6_ACAA39E0C1E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TSmartTaskObj;
class TSmartDocObj;

enum 
{
	Task_NotStart,
	Task_Execute,
	Task_Success,
	Task_Faild,
	Task_SuccessFaild
};

//************************************************************************************
//*名称: TSmartTask  
//*功能: 任务处理类
//************************************************************************************
class TSmartTask  
{
protected:
	TCHAR              m_szFileName[MAX_PATH];
	HMODULE            m_hModule ;

	lpfnInitTaskDLL    InitTaskDLL;
	lpfnDestoryTaskDLL DestoryTaskDLL;
	lpfnReadTask       ReadTask;
	lpfnReadTSRTask    ReadTSRTask;
	lpfnTaskReplace    TaskReplace;
	lpfnGetTimeOutMap  GetTimeOutMap;
	lpfnUpdateTask     UpdateTask;

public:
	lpfnReadSmartDocInfo      ReadSmartDocInfo;
	lpfnReleaseSmartDoc       ReleaseSmartDoc;

public:
	TSmartTask();
	virtual ~TSmartTask();

	void Initialized(LPCTSTR pszFileName);
	void Destory();

	BOOL GetSmartTaskPlan(TSmartTaskObj *pTaskPlan);
	BOOL GetSmartTaskPlanEx(TSmartTaskObj *pTaskPlan);
	BOOL ReplaceTaskPlan(TSmartTaskObj *pTaskPlan);
	BOOL UpdateTaskStatus(TSmartTaskObj *pTaskPlan);

	void GetSmartTimeOut(TSSmartTimeOut *pSmartTimeOut);

};

//************************************************************************************
//*名称: TSmartTaskObj
//*功能: 任务操作类
//************************************************************************************
class TSmartTaskObj : public TSSmartTaskPlan
{
protected:
	TLock		  m_lock;
	int           m_Result;
	int           m_nExecCount;

	char          m_szDateTime[24];

public:
	TSmartTaskObj();
	virtual ~TSmartTaskObj();

	void Clear();
	void Reset();
	void Release();

	int GetTaskResult() const ;
	void SetTaskResult(long nIndex, long nRet, long nTerminate);

	bool IsTSRTask() const ;
	bool IsFinished() const ;

	long GetPriority(long nIndex);
	bool IsTaskFinished();
	bool IsContinue(long nIndex);
	long GetMaxPriorityTask(TSmartDocObj *pDocObj);
	void SetFinished(long nIndex);
	void SetBeginFlag(long nIndex);

	long GetChildTaskCount(TSmartDocObj *pDocObj);
	long GetChildTask(TSmartDocObj *pDocObj, int iIndex);
	long GetNextTask(TSmartDocObj *pDocObj);

	void SetBeginTime();
	void ReportFinished();
};

#endif // !defined(AFX_TSMARTTASK_H__3D3910A5_6E9B_4640_B0E6_ACAA39E0C1E0__INCLUDED_)

