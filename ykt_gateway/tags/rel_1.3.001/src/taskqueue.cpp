
#include "taskdef.h"
#include "taskqueue.h"
#include "task_scheduler.h"
#include "ksgexception.h"
#include "deviceinterface.h"
#include "device.h"
#include "ksgateway.h"
#include <ace/ACE.h>
#include <ace/Log_Msg.h>

/////////////////////////////////////////////////////////////////////////
// KSGTaskManager
//! constructor
KSGTaskManager::KSGTaskManager()
{
	_check = new TaskAllocCheck(this);
	_pool.Attach(_check);
}
//! destructor
KSGTaskManager::~KSGTaskManager()
{
	Clear();
	if(_check)
	{
		delete _check;
	}
}
void KSGTaskManager::Clear()
{
	_tasks.clear();
}

KSGTaskManager::PtrType KSGTaskManager::NewTask(int taskId,int code,const std::string& content
					,KSGDeviceNode* node,TaskPriority pri /*= ptNormal*/)
{
	// 当增加一个新的任务时,需要调用 TaskPool 的 singal 函数去唤醒可能已经在等待的线程
	// 等待任务的线程在下一次被调度执行时,将检查可用的任务
	TaskType * task = FindTask(taskId);
	if(task != NULL)
	{
		// 如果任务已经存在, 抛出异常
		throw TaskAlreadyExistsException();
	}
	else
	{
		PtrType ret = _pool.Alloc(taskId,code,content);
		_tasks.insert(TaskMapType::value_type(ret->GetTaskId()
											  ,ret.operator ->()));
		KSG_Task_Queue *queue = node->owner_queue();
		if(!queue)
			throw NullPointerException();
		switch(pri)
		{
		case ptReal:
			queue->insert_task(ret);
			break;
		case ptPreempt:
			// TODO : support preemptive task
			break;
		default:
		case ptNormal:
			queue->push_task(ret);
			break;
		}
		std::string key = node->owner_queue()->key_name();
		Task_Queue_Pool::instance()->singal_queue(key);
		ret->SetDeviceNode(node);
		return ret;
	}
}

KSGTaskManager::TaskType* KSGTaskManager::FindTask(int taskId)
{
	TaskMapType::const_iterator i = _tasks.find(taskId);
	return (i == _tasks.end()) ? NULL : (i->second);
}

long KSGTaskManager::GenTaskId()
{
	int ret = _generator.GetNextVal();
	return -ret;
}

KSGTaskManager::PtrType KSGTaskManager::AddSysTask(int code,const std::string& content
								   ,KSGDeviceNode* node,TaskPriority pri /*= ptNormal*/)
{
	int taskid = GenTaskId();
	PtrType task = NewTask(taskid,code,content,node,pri);
	//task->SetPriority(pri);
	//task->SetDeviceNode(node);
	return task;
}

void KSGTaskManager::FreeTask(TaskType* task)
{
	assert(task != NULL);
	TaskMapType::iterator i = _tasks.find(task->GetTaskId());
	if(i != _tasks.end())
	{
		ACE_DEBUG((LM_DEBUG,"释放指令对象id[%d]",task->GetTaskId()));
		_tasks.erase(i);
	}
}

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
	switch(task->GetPriority())
	{
	case ptNormal:
		group->append(task);
		break;
	case ptReal:
		group->insert(task);
		break;
	case ptPreempt:
		// 增加抢占式任务 
		break;
	}
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
		ACE_DEBUG((LM_DEBUG,"指令队列执行指令..."));
		GlobalTaskManager::PtrType task = _group->peek();
		if(task)
		{
			// 执行指令
			KSGDeviceNode* node = task->GetDeviceNode();
			if(node == NULL)
			{
				ACE_DEBUG((LM_DEBUG,"指令[%d]没有执行设备",task->GetTaskId()));
				return;
			}
			int ret = TASK_ERR_COMMON;
			try
			{
				task->GetParams();
				task->SetNeedResponse();
				ret = node->ExecuteTask(task.operator->());
				ACE_DEBUG((LM_DEBUG,"执行指令[%d]dev[%d]ret[%d]",
					task->GetTaskId(),node->GetDevId(),ret));
			}
			catch(...)
			{
				// 指令格式不正确
			}
			if(TASK_SUCCESS == ret)
			{
				// 执行指令成功
				retmsg = "成功";
			}
			else if( TASK_ERR_NOT_SUPPORT == ret )
			{
				retmsg = "设备不支持指令";
				ret = TASK_SUCCESS;
			}
			else if( TASK_ERR_TIMEOUT == ret)
			{
				// 执行超时
				retmsg = "执行超时";
			}
			else if(TASK_ERR_EXECUTE == ret)
			{
				retmsg = "执行失败";
			}
			else if(TASK_ERR_CONNECT == ret)
			{
				// 连接设备失败
				ACE_DEBUG((LM_DEBUG,"无法连接到设备，该线程等待5秒后重试"));
				retmsg = "连接设备失败";
				KSGThreadUtil::Sleep(5000);
			}
			else
			{
				// 指令执行失败
				// 放弃该指令
			}
			if(task->NeedResponse())
			{
				// 更新到后台
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
							ACE_DEBUG((LM_ERROR,"指令执行器执行失败!"));
						}
					}
				}
				catch(...)
				{
					//
				}
				if(obj->Connect() || obj->SendRequest(300))
					ACE_DEBUG((LM_ERROR,"指令应答失败...taskid[%d]",task->GetTaskId()));
			}
		}
		else
			notask = true;
		ACE_DEBUG((LM_DEBUG,"指令队列执行指令结束"));
	}
	if(notask)
	{
		// 没有指令执行要进入 Idle 状态
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

//////////////////////////////////////////////////////////////////////////
// KSGTaskQueueScheduler
KSGTaskQueueScheduler::KSGTaskQueueScheduler(int thr_max_cnt)
	:_thread_max_count(thr_max_cnt),_is_terminated(true),_group_current_id(0)
{
}
KSGTaskQueueScheduler::~KSGTaskQueueScheduler()
{
}

int KSGTaskQueueScheduler::terminate()
{
	return -1;
}

int KSGTaskQueueScheduler::peek_task_queue(task_queue_type *queue)
{
	return -1;
}

int KSGTaskQueueScheduler::push_task_queue(task_queue_type *queue, KSGTaskQueueStatus status)
{
	return -1;
}

int KSGTaskQueueScheduler::add_task(GlobalTaskManager::PtrType task)
{
	return -1;
}

int KSGTaskQueueScheduler::setup_all_queue()
{
	return -1;
}

int KSGTaskQueueScheduler::svc()
{
	return -1;
}

int KSGTaskQueueScheduler::add_device_group(KSGDeviceNode *node)
{
	if(contain_device_in_queue(node))
	{
		return node->GetDevId();
	}
	task_queue_ptr_type queue = new_task_queue();
	if(queue == NULL)
		return -1;
	// TODO : 完成 queue 的初始化工作
	//
	
	_all_queue->push_back(queue);

	return 0;
}

int KSGTaskQueueScheduler::recursive_add_device(KSGDeviceNode *node,int group_id)
{
	if(contain_device_in_queue(node))
		return node->GetDevId();
	_dev_grp_queue.insert( device_task_queue_map_type::value_type(node->GetDevId(),group_id));
	KSGDeviceNode * next = node->GetFirstChild();
	int ret;
	while(next != NULL)
	{
		ret = recursive_add_device(next,group_id);
		if(ret)
			return ret;
		next = next->GetNextSibling();
	}
	return 0;
}

KSGTaskQueueScheduler::task_queue_ptr_type KSGTaskQueueScheduler::new_task_queue()
{
	return _queue_pool.construct(_group_current_id++);
}
inline bool KSGTaskQueueScheduler::contain_device_in_queue(KSGDeviceNode *node)
{
	return (_dev_grp_queue.find(node->GetDevId()) == _dev_grp_queue.end()) ? false : true;
}

