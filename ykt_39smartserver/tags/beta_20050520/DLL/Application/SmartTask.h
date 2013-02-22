
#ifndef __SMART_TASK_H__
#define __SMART_TASK_H__

enum 
{
	TASK_CYCLE_UNKNOW = -1, 
	TASK_CYCLE_ONCE = 0 ,
	TASK_CYCLE_DAY = 1 ,
	TASK_CYCLE_WEEK = 2 ,
	TASK_CYCLE_MONTH = 3 
};

//*******************************************************************************
//*名称: CSmartTask
//*功能: 业务层任务类
//*******************************************************************************
class CSmartTask
{
protected:
	TSSmartTaskPlan   m_SmartTask;

public:
	CSmartTask();
	virtual ~CSmartTask();

	void AddAuthID(long nAuthID, char *pTaskCode);
	void SetTask(char *sName, char *sBeginTime, long nTime, long nTimes);
	void SetMemo(int nValue);
	void SetMemo(char *pszValue);

	bool Write();
	bool Delete(long nTaskPlanID);
};

#endif //__SMART_TASK_H__