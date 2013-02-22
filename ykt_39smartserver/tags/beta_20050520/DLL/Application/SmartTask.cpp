
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
//*����: void CSmartTask::AddAuthID(long nAuthID, char *pTaskCode)
//*����: ����һ���豸
//*����: ��
//*����: ��
//*˵��: ����������
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
//*����: void CSmartTask::SetTask(char *sName, char *sBeginTime, long nTime, long nTimes)
//*����: ��������������
//*����: ��
//*����: ��
//*˵��: ����������
//*========================================================================================
void CSmartTask::SetTask(char *sName, char *sBeginTime, long nTime, long nTimes)
{
	m_SmartTask.nRepeatTime = nTime;				//�ּ�ʱ��
	m_SmartTask.nRepeatTimes = nTimes;				//�̴ּ���
	m_SmartTask.nTask = 0 ;							//��ԭ�豸��
	m_SmartTask.nTaskCycle = TASK_CYCLE_ONCE;		//�̶�Ϊ 'һ��������'
	strcpy(m_SmartTask.szTaskName, sName);			//��������

	if( !strcmp(sBeginTime, "") )
		GetCurDateTime(m_SmartTask.szBeginTime);
	else
		strcpy(m_SmartTask.szBeginTime, sBeginTime);	//������ʼʱ��
}

//*========================================================================================
//*����: bool CSmartTask::Write()
//*����: ������һ������
//*����: ��
//*����: ��
//*˵��: ����������
//*========================================================================================
bool CSmartTask::Write()
{
	return true;
}

//*========================================================================================
//*����: void CSmartTask::Delete(long nTaskPlanID)
//*����: ɾ��һ������
//*����: ��
//*����: ��
//*˵��: ����������
//*========================================================================================
bool CSmartTask::Delete(long nTaskPlanID)
{
	return true;
}

