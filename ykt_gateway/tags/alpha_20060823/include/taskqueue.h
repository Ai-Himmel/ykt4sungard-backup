#ifndef _TASKQUEUE_H_
#define _TASKQUEUE_H_
/*! @file
 *	模块名:	一卡通通用前置机
 *	文件名: taskqueue.h
 *	文件实现功能: 指令任务队列
 *	作者:	汤成
 *	版本:	V0.1
 *	备注:	
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

//! 指令管理器
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

	//<! 指令对象类型
	typedef Task TaskType;
public:
	//<! 指令对象内存池类型
	//typedef boost::object_pool<TaskType> TaskObjPoolType;
	//typedef TaskType* PtrType;
	typedef SmartPtrPool<TaskType,boost::object_pool<TaskType>,KSGLockThreadModel> TaskObjPoolType;
	typedef typename TaskObjPoolType::SmartPtr PtrType;
	typedef typename PtrType::PointerType PointerType;
private:
	TaskAllocCheck* _check;
	//<! 指令列表类型
	typedef std::map<int,TaskType*> TaskMapType;
	//<! 指令内存池
	TaskObjPoolType _pool;
	//<! 指令列表
	TaskMapType _tasks;
	//<! 前置机指令主键生成器
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
	//! 增加新的指令
	/*
	\brief 如果ID号指令已经存在，将新的指令内容复制给原来的指令
	\param taskId 指令ID号
	\param code 指令代码
	\param content 指令内容
	\return 返回指令对象的指针
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

	//! 根据ID号查找指令
	/* 
	\param taskId 指令ID号
	\return 返回指令对象指针
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
	//! 释放指令对象内存
	/*
	\param task 指令对象指针
	\throw KSGExcpetion 如果指令对象不是在该缓存中申请的抛出异常
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
//! 指令分组
/*!
 * \param T 指令对象类型
 */
template<class T>
class KSGTaskGroup
{
private:
	//<! 任务指令对象指针类型
	typedef T Task_Type;
	//<! 
	typedef KSGLockQueue<Task_Type> QueueType;
	QueueType* _runningQueue;
	QueueType* _waitingQueue;
	KSGLockThreadModel::MutexType _mutex;
	//<! 分组ID
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
	 \brief 构造函数
	 \param gid 组ID号
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
	 * 向指令队列增加一条指令，如果当前队列正在执行写操作，线程将会被阻塞
	 * 该方法也会阻塞其它对指令队列的访问
	 * \return 成功增加返回 true , 失败返回 false
	 */
	bool append(Task_Type& pTask)
	{
		KSGLockThreadModel lock(_mutex);
		bool ret = _runningQueue->append(pTask);
		if(ret)
			singal();
		return ret;

	}
	//! 向指令队列插入一条指令,插入的指令会优先被执行
	/*
	 \param pTask 指令
	 \return 成功返回 true, 失败返回 false
	 */
	bool insert(Task_Type& pTask)
	{
		KSGLockThreadModel lock(_mutex);
		bool ret = _runningQueue->insert(pTask);
		if(ret)
			singal();
		return ret;
	}
	//! 当前队列中所有指令的数量
	/*
	 \return 队列中指令的数量
	 */
	size_t count()
	{
		KSGLockThreadModel lock(_mutex);
		size_t ret = _runningQueue->count() + _waitingQueue->count();
		return ret;
	}
	//! 从队列中读取一条指令，如果为空返回 NULL
	/*!
	 \brief 从队列中读取第一条指令
	  先从running队列中读取一条，如果running中没有，将waiting队列中的指令移到
	  running 队列中，如果还是没有，返回 NULL。
	  使用完指令对象后，要手动删除对象
	 \return 返回任务对象指针 
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
	//! 组ID 号
	inline int GetGroupId() const { return _groupId; }

	//! 进入等待状态,等待被唤醒,或者10秒后再运行.
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
	//! 唤醒等待线程
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

//! 指令队列管理
class KSGTaskQueueManager
{
public:
	//<! 分组队列的类型
	typedef KSGTaskGroup<GlobalTaskManager::PtrType> TaskGroupType;
private:
	//<! 分组队列
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
	//! 增加一组设备,包括 node 的所有子设备 
	inline int AddDevices(KSGDeviceNode* node)
	{
		assert(node != NULL);
		TaskGroupType* group = NewTaskGroup(++_currGrpId);
		RecursiveAddDevice(node,_currGrpId);
		return _currGrpId;
	}
	//! 增加一个指令到指令队列中,系统根据 task 中的 devicenode 来判断放入哪个队列线中
	/*
	 \param task 指令
	 */
	void AddTask(TaskType& task);
	//! 根据组号读取指令组
	/*
	 \param grpid - 指令组号
	 \return - 返回指令号,如果指令不存在返回 NULL
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
				ACE_DEBUG((LM_ERROR,"设备执行指令失败[%s]",ex.what()));
			}
			// sleep 50 毫秒
			KSGThreadUtil::Sleep(50);
		}
		// 日志已经结束,不能再打日志
		//ACE_DEBUG((LM_INFO,"设备指令队列停止[%p]"));
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
