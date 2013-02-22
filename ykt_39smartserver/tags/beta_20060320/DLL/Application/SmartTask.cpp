
#include "stdafx.h"
#include "smarttask.h"

CSmartTask::CSmartTask()
{
	ZeroMemory(&m_SmartTask, sizeof(m_SmartTask));
}

CSmartTask::~CSmartTask()
{

}


//*========================================================================================
//*函数: void CSmartTask::AddAuthID(long nAuthID, char *pTaskCode)
//*功能: 增加一个设备
//*参数: 略
//*返回: 无
//*说明: 任务表操作类
//*========================================================================================
void CSmartTask::AddAuthID(long nAuthID, char *pTaskCode)
{
	m_SmartTask.pTask[m_SmartTask.nTask].nAuthID = nAuthID ;
	strcpy(m_SmartTask.pTask[m_SmartTask.nTask].szTaskCode, pTaskCode);
	m_SmartTask.nTask++;
}

void CSmartTask::SetMemo(int nValue)
{
	sprintf(m_SmartTask.szMemo, "%d", nValue);
}

void CSmartTask::SetMemo(char *pszValue)
{
	strncpy(m_SmartTask.szMemo, pszValue, sizeof(m_SmartTask.szMemo));
}

//*========================================================================================
//*函数: void CSmartTask::SetTask(char *sName, char *sBeginTime, long nTime, long nTimes)
//*功能: 设置新任务属性
//*参数: 略
//*返回: 无
//*说明: 任务表操作类
//*========================================================================================
void CSmartTask::SetTask(char *sName, char *sBeginTime, long nTime, long nTimes)
{
	m_SmartTask.nRepeatTime = nTime;				//持继时间
	m_SmartTask.nRepeatTimes = nTimes;				//持继次数
	m_SmartTask.nTask = 0 ;							//复原设备数
	m_SmartTask.nTaskCycle = TASK_CYCLE_ONCE;		//固定为 '一次性任务'
	strcpy(m_SmartTask.szTaskName, sName);			//任务名称

	if( !strcmp(sBeginTime, "") )
		GetCurDateTime(m_SmartTask.szBeginTime);
	else
		strcpy(m_SmartTask.szBeginTime, sBeginTime);	//任务起始时间
}

//*========================================================================================
//*函数: bool CSmartTask::Write()
//*功能: 新增加一条任务
//*参数: 略
//*返回: 无
//*说明: 任务表操作类
//*========================================================================================
bool CSmartTask::Write()
{
	return true;
}

//*========================================================================================
//*函数: void CSmartTask::Delete(long nTaskPlanID)
//*功能: 删除一条任务
//*参数: 略
//*返回: 无
//*说明: 任务表操作类
//*========================================================================================
bool CSmartTask::Delete(long nTaskPlanID)
{
	return true;
}

