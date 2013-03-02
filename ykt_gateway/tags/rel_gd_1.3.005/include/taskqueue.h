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
#include "taskdef.h"
#include "thread.h"
#include "memutil.h"
#include <ace/Condition_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Time_Value.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/OS.h>
#include <xutils/xtype_trait.h>
#include <string>
#include <map>
#include <utility>
#include <assert.h>
#include <boost/pool/object_pool.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

//! ָ�������
class KSGTaskManager
{
	typedef KSGTask<KSGDeviceNode> Task;
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
	typedef TaskObjPoolType::SmartPtr PtrType;
	typedef PtrType::PointerType PointerType;
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
	//<!
	static ACE_Thread_Mutex _s_mutex;
public:
	//! constructor
	KSGTaskManager();
	//! destructor
	virtual ~KSGTaskManager();
	void Clear();
	//! �����µ�ָ��
	/*
	\brief ���ID��ָ���Ѿ����ڣ����µ�ָ�����ݸ��Ƹ�ԭ����ָ��
	\param taskId ָ��ID��
	\param code ָ�����
	\param content ָ������
	\return ����ָ������ָ��
	*/
	PtrType NewTask(int taskId,int code,const std::string& content
					,KSGDeviceNode* node,TaskPriority pri = ptNormal);

	//! ����ID�Ų���ָ��
	/* 
	\param taskId ָ��ID��
	\return ����ָ�����ָ��
	*/
	TaskType* FindTask(int taskId);

	int GetTaskCount();

	long GenTaskId();

	/** 
	 * @brief ����һ��ϵͳ����������
	 * 
	 * @param code - ��������
	 * @param content - ����
	 * @param node - ָ��ִ�е��豸�ڵ�
	 * @param pri - ָ�����ȼ�
	 * 
	 * @return  - ָ�����
	 */
	PtrType AddSysTask(int code,const std::string& content
		,KSGDeviceNode* node,TaskPriority pri = ptNormal);
protected:
	//! �ͷ�ָ������ڴ�
	/*
	\param task ָ�����ָ��
	\throw KSGExcpetion ���ָ��������ڸû�����������׳��쳣
	*/
	void FreeTask(TaskType* task);
};

typedef KSGTaskManager GlobalTaskManager;

typedef enum { tq_running = 0, tq_waiting, tq_blocking, tq_executing, tq_sleeping }KSGTaskQueueStatus;
//! ָ�����
/*!
 * \param T ָ���������
 */
template<class T>
class KSGTaskQueue
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
	//<! ָ����״̬
	KSGTaskQueueStatus _status;
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
	KSGTaskQueue(int gid)
		:_groupId(gid),_idleMutex(0),_idleCondition(_idleMutex),_isIdle(true),_status(tq_sleeping)
	{
		NewTaskQueue();
	}
	//! destructor
	~KSGTaskQueue()
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

	//! ��ȡָ�����״̬
	KSGTaskQueueStatus get_status() 
	{
		KSGLockThreadModel lock(_mutex);
		return _status;
	}
	//! ����ָ�����״̬
	void set_status(KSGTaskQueueStatus status)
	{
		KSGLockThreadModel lock(_mutex);
		_status = status;
	}
};

//! ָ����й���
class KSGTaskQueueManager
{
public:
	//<! ������е�����
	typedef KSGTaskQueue<GlobalTaskManager::PtrType> TaskGroupType;
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
	typedef KSGTaskQueue<TaskType> TaskGroupType;
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

//! ָ����е�����,������ģ��
/*
 * ָ������㷨˵��
 */
class KSGTaskQueueScheduler
{
private:
	//<! �̳߳�����߳���
	int _thread_max_count;
	//<! �̵߳����Ƿ��Ѿ�ֹͣ
	bool _is_terminated;
public:
	KSGTaskQueueScheduler(int max_thr_cnt);
	~KSGTaskQueueScheduler();
	inline bool is_terminated() const 
	{
		return _is_terminated;
	}
	//<! ָ�������ȼ���Χ
	static const int MAX_PRIORITY_LEVEL = 20;

	typedef KSGTaskQueue<GlobalTaskManager::PtrType> task_queue_type;
	//! 
	/*
	 \brief ����һ���豸��, ����豸���ظ�����, ���س�����豸��
	 \param node - �豸��ĸ��ڵ�, �� CCU , GCU , LPORT �ȵ�
	 \return ���� 0 ��ʾ�ɹ�, <> 0 Ϊ���صĴ�����豸��
	 */
	int add_device_group(KSGDeviceNode *node);
private:
	typedef task_queue_type * task_queue_ptr_type;
	typedef std::list<task_queue_ptr_type> task_queue_list_type;
	typedef std::map<task_queue_ptr_type,int> task_queue_map_type;
	typedef std::map<int,int> device_task_queue_map_type;
	typedef std::pair<KSGDeviceNode*,task_queue_ptr_type> task_queue_device_pair_type;
	typedef std::list<task_queue_device_pair_type> task_queue_device_list_type;
	typedef std::multimap<task_queue_ptr_type,GlobalTaskManager::PtrType> preemptive_task_map_type;
	typedef boost::object_pool<task_queue_type> task_queue_pool_type;

	//<! task queue pool
	task_queue_pool_type _queue_pool;
	//<! running ����
	task_queue_list_type *_running_queue[MAX_PRIORITY_LEVEL];
	//<! waiting queue
	task_queue_list_type *_waiting_queue[MAX_PRIORITY_LEVEL];
	//<! sleeping queue
	task_queue_map_type *_sleeping_queue;
	//<! blocking queue
	task_queue_device_list_type *_blocking_queue;
	//<! all task queue
	task_queue_list_type *_all_queue;
	//<! preemptive queue
	preemptive_task_map_type *_preemptive_queue;
	//<! device and task queue map
	device_task_queue_map_type _dev_grp_queue;
	//<! lock
	ACE_Recursive_Thread_Mutex _mutex;

	//<! group start id
	int _group_current_id;

	int setup_all_queue();

	task_queue_ptr_type new_task_queue();

	inline bool contain_device_in_queue(KSGDeviceNode *node);
	int recursive_add_device(KSGDeviceNode *node,int group_id);
protected:
	//////////////////////////////////////////////////////////////
	// ������нӿ�
	/** 
	 * @brief ����һ��ָ�ָ�������  
	 * @param task ָ��
	 * 
	 * @return 0 ��ʾ�ɹ�, -1 ��ʾʧ��
	 */
	int add_task(GlobalTaskManager::PtrType task);
	/** 
	 * @brief �Ӷ�����ȡ��һ��ָ�����
	 * 
	 * @param queue 
	 * 
	 * @return 0 ��ʾ�ɹ��ҵ�һ�� Queue , ���� -1 ��ʾ����ʧ��, 1 ��ʾ���������
	 */
	int peek_task_queue(task_queue_type *queue);
	/** 
	 * @brief ִ��ָ����ɺ�,��һ�� Queue ���·Żص��ȶ�������
	 * 
	 * @param queue - Queue
	 * @param status  - ״̬, 
	 * 
	 * @return 0 ��ʾ�ɹ�, -1 ��ʾʧ��
	 */
	int push_task_queue(task_queue_type *queue,KSGTaskQueueStatus status);

public:
	/** 
	 * @brief ��������
	 * 
	 * @return 0 ��ʾ�����ɹ�, -1 ��ʾ����ʧ��
	 */
	int svc();
	//! ֹͣ�����߳�
	int terminate();
};

#endif

