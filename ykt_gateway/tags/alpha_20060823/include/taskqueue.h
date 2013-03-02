#ifndef _TASKQUEUE_H_
#define _TASKQUEUE_H_
/*! @file
 *	ģ����:	һ��ͨͨ��ǰ�û�
 *	�ļ���: taskqueue.h
 *	�ļ�ʵ�ֹ���: ָ���������
 *	����:	����
 *	�汾:	V0.1
 *	��ע:	
*/
#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "device.h"
#include "scheduler.h"
#include "lockqueue.h"
#include "smartpool.h"
#include "thread.h"
#include "memutil.h"
#include <ace/Condition_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Time_Value.h>
#include <ace/OS.h>
#include <xutils/xtype_trait.h>
#include <string>
#include <map>
#include <assert.h>
#include <boost/pool/object_pool.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

//! ָ�������
template<class Task>
class KSGTaskManager
{
	class TaskAllocCheck : public KSGObserver<Task,KSGLockThreadModel>
	{
	public:
		KSGTaskManager* _manager;
		TaskAllocCheck(KSGTaskManager* m):_manager(m){}
		virtual void Update(Task& obj)
		{
			_manager->FreeTask(&obj);
		}
	};

	//<! ָ���������
	typedef Task TaskType;
public:
	//<! ָ������ڴ������
	//typedef boost::object_pool<TaskType> TaskObjPoolType;
	//typedef TaskType* PtrType;
	typedef SmartPtrPool<TaskType,boost::object_pool<TaskType>,KSGLockThreadModel> TaskObjPoolType;
	typedef typename TaskObjPoolType::SmartPtr PtrType;
	typedef typename PtrType::PointerType PointerType;
private:
	TaskAllocCheck* _check;
	//<! ָ���б�����
	typedef std::map<int,TaskType*> TaskMapType;
	//<! ָ���ڴ��
	TaskObjPoolType _pool;
	//<! ָ���б�
	TaskMapType _tasks;
	//<! ǰ�û�ָ������������
	KSGSequenceGenerator<MTTheadModel> _generator;
public:
	//! constructor
	KSGTaskManager()
	{
		_check = new TaskAllocCheck(this);
		_pool.Attach(_check);
	}
	//! destructor
	virtual ~KSGTaskManager()
	{
		Clear();
		if(_check)
		{
			delete _check;
		}
	}
	void Clear()
	{
		_tasks.clear();
	}
	//! �����µ�ָ��
	/*
	\brief ���ID��ָ���Ѿ����ڣ����µ�ָ�����ݸ��Ƹ�ԭ����ָ��
	\param taskId ָ��ID��
	\param code ָ�����
	\param content ָ������
	\return ����ָ������ָ��
	*/
	PtrType NewTask(int taskId,int code,const std::string& content)
	{
		TaskType * task = FindTask(taskId);
		//PtrType obj;
		if(task != NULL)
		{
			throw TaskAlreadyExistsException();
		}
		else
		{
			PtrType ret = _pool.Alloc(taskId,code,content);
			_tasks.insert(typename TaskMapType::value_type(ret->GetTaskId()
				,ret.operator ->()));
			return ret;
		}
	}

	//! ����ID�Ų���ָ��
	/* 
	\param taskId ָ��ID��
	\return ����ָ�����ָ��
	*/
	TaskType* FindTask(int taskId)
	{
		typename TaskMapType::const_iterator i = _tasks.find(taskId);
		return (i == _tasks.end()) ? NULL : (i->second);
	}

	long GenTaskId()
	{
		int ret = _generator.GetNextVal();
		return -ret;
	}

	PtrType AddSysTask(int code,const std::string& content
		,KSGDeviceNode* node,TaskPriority pri = ptNormal)
	{
		int taskid = GenTaskId();
		PtrType task = NewTask(taskid,code,content);
		task->SetPriority(pri);
		task->SetDeviceNode(node);
		return task;
	}
protected:
	//! �ͷ�ָ������ڴ�
	/*
	\param task ָ�����ָ��
	\throw KSGExcpetion ���ָ��������ڸû�����������׳��쳣
	*/
	void FreeTask(TaskType* task)
	{
		assert(task != NULL);
		typename TaskMapType::iterator i = _tasks.find(task->GetTaskId());
		if(i != _tasks.end())
			_tasks.erase(i);
	}
};

typedef KSGTaskManager<KSGTask<KSGDeviceNode> > GlobalTaskManager;
//! ָ�����
/*!
 * \param T ָ���������
 */
template<class T>
class KSGTaskGroup
{
private:
	//<! ����ָ�����ָ������
	typedef T Task_Type;
	//<! 
	typedef KSGLockQueue<Task_Type> QueueType;
	QueueType* _runningQueue;
	QueueType* _waitingQueue;
	KSGLockThreadModel::MutexType _mutex;
	//<! ����ID
	int _groupId;

	inline void NewTaskQueue()
	{
		_runningQueue = new QueueType;
		_waitingQueue = new QueueType;
	}
	
	ACE_Thread_Mutex _idleMutex;
	ACE_Condition<ACE_Thread_Mutex> _idleCondition;
	bool _isIdle;
public:
	//! default constructor
	/*
	KSGTaskGroup():KSGTaskGroup(-1)
	{
	}
	*/
	//! constructor
	/*!
	 \brief ���캯��
	 \param gid ��ID��
	 */
	KSGTaskGroup(int gid)
		:_groupId(gid),_idleMutex(0),_idleCondition(_idleMutex),_isIdle(true)
	{
		NewTaskQueue();
	}
	//! destructor
	~KSGTaskGroup()
	{
		delete _runningQueue;
		delete _waitingQueue;
	}
	/*!
	 * ��ָ���������һ��ָ������ǰ��������ִ��д�������߳̽��ᱻ����
	 * �÷���Ҳ������������ָ����еķ���
	 * \return �ɹ����ӷ��� true , ʧ�ܷ��� false
	 */
	bool append(Task_Type& pTask)
	{
		KSGLockThreadModel lock(_mutex);
		bool ret = _runningQueue->append(pTask);
		if(ret)
			singal();
		return ret;

	}
	//! ��ָ����в���һ��ָ��,�����ָ������ȱ�ִ��
	/*
	 \param pTask ָ��
	 \return �ɹ����� true, ʧ�ܷ��� false
	 */
	bool insert(Task_Type& pTask)
	{
		KSGLockThreadModel lock(_mutex);
		bool ret = _runningQueue->insert(pTask);
		if(ret)
			singal();
		return ret;
	}
	//! ��ǰ����������ָ�������
	/*
	 \return ������ָ�������
	 */
	size_t count()
	{
		KSGLockThreadModel lock(_mutex);
		size_t ret = _runningQueue->count() + _waitingQueue->count();
		return ret;
	}
	//! �Ӷ����ж�ȡһ��ָ����Ϊ�շ��� NULL
	/*!
	 \brief �Ӷ����ж�ȡ��һ��ָ��
	  �ȴ�running�����ж�ȡһ�������running��û�У���waiting�����е�ָ���Ƶ�
	  running �����У��������û�У����� NULL��
	  ʹ����ָ������Ҫ�ֶ�ɾ������
	 \return �����������ָ�� 
	 */
	Task_Type peek()
	{
		KSGLockThreadModel lock(_mutex);
		Task_Type task;
		try
		{
			task = _runningQueue->peek();
			if(task)
				return task;
		}
		catch(NoneResourceException& )
		{
			// 
		}
		if(!task)
		{
			std::swap(_runningQueue,_waitingQueue);
			try
			{
				task = _runningQueue->peek();
			}
			catch(NoneResourceException& )
			{
				//
			}
			
		}
		return task;
	}
	//! ��ID ��
	inline int GetGroupId() const { return _groupId; }

	//! ����ȴ�״̬,�ȴ�������,����10���������.
	int wait()
	{
		_idleMutex.acquire();
		_isIdle = true;
		
		ACE_Time_Value now(10);
		now += ACE_OS::gettimeofday();
		int ret = _idleCondition.wait(&now);
		_idleMutex.release();
		return ret;
	}
	//! ���ѵȴ��߳�
	inline int singal()
	{	
		if(_isIdle)
		{
			_isIdle = false;
			return _idleCondition.signal();
		}
		return 0;
	}
};

//! ָ����й���
class KSGTaskQueueManager
{
public:
	//<! ������е�����
	typedef KSGTaskGroup<GlobalTaskManager::PtrType> TaskGroupType;
private:
	//<! �������
	typedef GlobalTaskManager::PtrType TaskType;
	typedef std::map<int,TaskGroupType*> GroupMapType;
	typedef std::map<int,int> DeviceGrpMapType;
	GroupMapType _groups;
	DeviceGrpMapType _devgrps;
	int _currGrpId;
private:
	TaskGroupType* NewTaskGroup(int id);
	void RecursiveAddDevice(KSGDeviceNode* parent,int grpId);
	TaskGroupType* FindDeviceTaskGroup(KSGDeviceNode* node);
	void FreeTaskGroup(GroupMapType::value_type& value);
	void ClearGroups()
	{
		std::for_each(_groups.begin(),_groups.end(),
			boost::bind(&KSGTaskQueueManager::FreeTaskGroup,this,_1));
		_groups.clear();
	}
public:
	//! constructor
	KSGTaskQueueManager():_currGrpId(0){}
	//! destructor
	~KSGTaskQueueManager()
	{
		ClearGroups();
	}
	//! ����һ���豸,���� node ���������豸 
	inline int AddDevices(KSGDeviceNode* node)
	{
		assert(node != NULL);
		TaskGroupType* group = NewTaskGroup(++_currGrpId);
		RecursiveAddDevice(node,_currGrpId);
		return _currGrpId;
	}
	//! ����һ��ָ�ָ�������,ϵͳ���� task �е� devicenode ���жϷ����ĸ���������
	/*
	 \param task ָ��
	 */
	void AddTask(TaskType& task);
	//! ������Ŷ�ȡָ����
	/*
	 \param grpid - ָ�����
	 \return - ����ָ���,���ָ����ڷ��� NULL
	 */
	inline TaskGroupType* GetDeviceGroup(int grpid)
	{
		GroupMapType::iterator i = _groups.find(grpid);
		if(i != _groups.end())
			return i->second;
		return NULL;
	}
};

class KSGDeviceNode;
class TaskExecScheduler : public KSGScheduler
{
private:
	typedef GlobalTaskManager::PtrType TaskType;
	typedef KSGTaskGroup<TaskType> TaskGroupType;
	TaskGroupType* _group;
public:
	TaskExecScheduler(TaskGroupType* g):KSGScheduler(),_group(g)
	{}
	virtual ~TaskExecScheduler(){}
	virtual void Run();
	virtual KSGScheduler& GetObserverable()
	{
		return *this;
	}
};

class TaskExecRunner : public KSGThreadExec<TaskExecRunner>
{
private:
	KSGScheduler * _schd;
public:
	TaskExecRunner(KSGScheduler * schd):_schd(schd){}
	virtual ~TaskExecRunner(){}
	virtual void Run()
	{
		if(!_schd)
			return;
		while(!IsTerminated())
		{
			try
			{
				_schd->Run();
			}
			catch(std::exception& ex)
			{
				ACE_DEBUG((LM_ERROR,"�豸ִ��ָ��ʧ��[%s]",ex.what()));
			}
			// sleep 50 ����
			KSGThreadUtil::Sleep(50);
		}
		// ��־�Ѿ�����,�����ٴ���־
		//ACE_DEBUG((LM_INFO,"�豸ָ�����ֹͣ[%p]"));
	}
};

class KSGDeviceGroupScheduler : public KSGSchedulerGroup<TaskExecRunner> 
{
private:
	typedef std::list<TaskExecScheduler*> TaskExecList;
	typedef boost::object_pool<TaskExecScheduler> TaskExecPool;
	TaskExecList _taskexecs;
	TaskExecPool _pool;
protected:
	virtual void FreeScheduler(KSGScheduler* exec);
public:
	KSGDeviceGroupScheduler(){}
	virtual ~KSGDeviceGroupScheduler(){}
	int AddNewDeviceGroup(KSGTaskQueueManager::TaskGroupType* grp);
};

#endif
