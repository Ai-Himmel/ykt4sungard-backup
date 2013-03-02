#include "stdafx.h"
#include "taskdef.h"
#include "taskqueue.h"
#include "ksgexception.h"
#include "deviceinterface.h"
#include "device.h"
#include "ksgateway.h"
#include <ace/ACE.h>
#include <ace/Log_Msg.h>

//////////////////////////////////////////////////////////////////////////
// KSGTaskQueueManager
void KSGTaskQueueManager::AddTask(TaskType& task)
{
	KSGDeviceNode* node = task->GetDeviceNode();
	if(node == NULL)
		throw KSGException();
	TaskGroupType* group= FindDeviceTaskGroup(node);

	if(!group)
	{
		throw KSGException();
	}
	if(group->count() > KsgGetGateway()->GetConfig()->_taskQueueMaxWaiting 
		&& KsgGetGateway()->GetConfig()->_taskQueueMaxWaiting != -1)
	{
		throw TaskQueueExceedException();
	}
	if(task->GetPriority() == ptNormal)
		group->append(task);
	else
		group->insert(task);
}

KSGTaskQueueManager::TaskGroupType* KSGTaskQueueManager::NewTaskGroup(int id)
{
	TaskGroupType* grp = new TaskGroupType(id);
	_groups.insert(GroupMapType::value_type(id,grp));
	return grp;
}

void KSGTaskQueueManager::FreeTaskGroup(GroupMapType::value_type& value)
{
	TaskGroupType* grp = value.second;
	if(grp)
	{
		delete grp;
	}
}
KSGTaskQueueManager::TaskGroupType* KSGTaskQueueManager::FindDeviceTaskGroup(KSGDeviceNode* node)
{
	DeviceGrpMapType::const_iterator i = _devgrps.find(node->GetDevId());
	if(i != _devgrps.end())
	{
		GroupMapType::const_iterator j = _groups.find(i->second);
		if(j != _groups.end())
		{
			return j->second;
		}
	}
	return NULL;
}
void KSGTaskQueueManager::RecursiveAddDevice(KSGDeviceNode* parent,int grpId)
{
	if(!parent)
	{
		return;
	}
	_devgrps.insert(DeviceGrpMapType::value_type(parent->GetDevId(),grpId));
	KSGDeviceNode* c = parent->GetFirstChild();
	while(c)
	{
		_devgrps.insert(DeviceGrpMapType::value_type(c->GetDevId(),grpId));
		RecursiveAddDevice(c,grpId);
		c = c->GetNextSibling();
	}
}

//////////////////////////////////////////////////////////////////////////
// TaskExecScheduler

void TaskExecScheduler::Run()
{
	bool notask = false;
	std::string retmsg;
	{
		ACE_DEBUG((LM_DEBUG,"ָ�����ִ��ָ��..."));
		GlobalTaskManager::PtrType task = _group->peek();
		if(task)
		{
			// ִ��ָ��
			KSGDeviceNode* node = task->GetDeviceNode();
			if(node == NULL)
			{
				ACE_DEBUG((LM_DEBUG,"ָ��[%d]û��ִ���豸",task->GetTaskId()));
				return;
			}
			int ret = TASK_ERR_COMMON;
			try
			{
				task->GetParams();
				task->SetNeedResponse();
				ret = node->ExecuteTask(task.operator->());
				ACE_DEBUG((LM_DEBUG,"ִ��ָ��[%d]dev[%d]ret[%d]",
					task->GetTaskId(),node->GetDevId(),ret));
			}
			catch(...)
			{
				// ָ���ʽ����ȷ
			}
			if(TASK_SUCCESS == ret)
			{
				// ִ��ָ��ɹ�
				retmsg = "�ɹ�";
			}
			else if( TASK_ERR_NOT_SUPPORT == ret )
			{
				retmsg = "�豸��֧��ָ��";
				ret = TASK_SUCCESS;
			}
			else if( TASK_ERR_TIMEOUT == ret)
			{
				// ִ�г�ʱ
				retmsg = "ִ�г�ʱ";
			}
			else if(TASK_ERR_EXECUTE == ret)
			{
				retmsg = "ִ��ʧ��";
			}
			else if(TASK_ERR_CONNECT == ret)
			{
				// �����豸ʧ��
				ACE_DEBUG((LM_DEBUG,"�޷����ӵ��豸�����̵߳ȴ�5�������"));
				retmsg = "�����豸ʧ��";
				KSGThreadUtil::Sleep(5000);
			}
			else
			{
				// ָ��ִ��ʧ��
				// ������ָ��
			}
			if(task->NeedResponse())
			{
				// ���µ���̨
				DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
				obj->SetRequestHeader(KsgGetGateway()->GetConfig()->_taskResponseFuncNo);
				obj->AddField(F_LVOL1,task->GetTaskId());
				obj->AddField(F_LVOL4,ret);
				obj->AddField(F_VSMESS,retmsg.c_str());
				
				KSGTaskExecutor* exec = NULL;
				try
				{
					exec = KSGTaskExecutorFactory::Instance().Create(
						task->GetTaskCode());
					if(exec)
					{
						if(exec->ExecuteTask(obj.operator ->(),task.operator->()))
						{
							ACE_DEBUG((LM_ERROR,"ָ��ִ����ִ��ʧ��!"));
						}
					}
				}
				catch(...)
				{
					//
				}
				if(obj->Connect() || obj->SendRequest(300))
					ACE_DEBUG((LM_ERROR,"ָ��Ӧ��ʧ��...taskid[%d]",task->GetTaskId()));
			}
		}
		else
			notask = true;
		ACE_DEBUG((LM_DEBUG,"ָ�����ִ��ָ�����"));
	}
	if(notask)
	{
		// û��ָ��ִ��Ҫ���� Idle ״̬
		_group->wait();
	}
}

////////////////////////////////////////////////////////////////////////
//
int KSGDeviceGroupScheduler::AddNewDeviceGroup(KSGTaskQueueManager::TaskGroupType* grp)
{
	if( grp != NULL )
	{
		TaskExecScheduler * schd = _pool.construct(grp);
		this->NewScheduler(schd);
		_taskexecs.push_back(schd);
		return 0;
	}
	return -1;
}

//void KSGDeviceGroupScheduler::ClearAllExec()
//{
//	std::for_each(_taskexecs.begin(),_taskexecs.end(),
//		boost::bind(&KSGDeviceGroupScheduler::FreeTaskExecs,this,_1));
//}
void KSGDeviceGroupScheduler::FreeScheduler(KSGScheduler* exec)
{
	TaskExecScheduler * p = dynamic_cast<TaskExecScheduler*>(exec);
	if(p)
		_pool.free(p);
}
