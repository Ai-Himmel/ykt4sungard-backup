#ifndef _TASK_SCHEDULER_H_
#define _TASK_SCHEDULER_H_

#include "device.h"
#include "taskdef.h"
#include "taskqueue.h"
#include <ace/Thread_Mutex.h>
#include <ace/Local_Tokens.h>
#include <ace/Token.h>
#include <ace/Singleton.h>
#include <ace/Thread_Semaphore.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <boost/pool/object_pool.hpp>

class KSG_Task_Queue_Pool;

class KSG_Task_Queue
{
public:
	//typedef KSGTask<KSGDeviceNode> task_type;
	typedef KSGTaskManager::PtrType task_type;
	typedef enum { tq_running , tq_waiting, tq_sleeping , tq_blocking } task_status;
private:
	typedef std::list<KSGDeviceNode*> device_list_type;
	typedef std::list<task_type> task_list_type;

	/** 
	 * @brief  根设备节点
	 */
	KSGDeviceNode *_root_node;
	/** 
	 * @brief 子设备节点列表
	 */
	device_list_type _list_of_children;
	/** 
	 * @brief 任务列表 , FIFO
	 */
	task_list_type _list_of_tasks;
	/** 
	 * @brief 抢占式任务列表 , FIFO
	 */
	task_list_type _list_of_preempt_tasks;

	ACE_Recursive_Thread_Mutex _task_list_mutex;

	KSG_Task_Queue *_previous;
	KSG_Task_Queue *_next;
	task_status _status;

	std::string _key_name;
protected:
	KSG_Task_Queue();
	friend class KSG_Task_Queue_Pool;
	friend class boost::object_pool<KSG_Task_Queue>;
public:
	~KSG_Task_Queue();
	int push_task(task_type task);
	int insert_task(task_type task);
	task_type peek_task();
	/*!
	 \brief 增加抢占式任务
	 \param task - 任务
	 \return 0 表示成功,-1 表示失败
	 */
	int push_preemptive_task(task_type task);
	task_type peek_preemptive_task();
	inline size_t count_of_tasks();
	inline size_t count_of_preemptive_tasks();

	KSG_Task_Queue* previous(KSG_Task_Queue *p = NULL);
	KSG_Task_Queue* next(KSG_Task_Queue *n = NULL);
	void reset();
	inline task_status status() const
	{
		return _status;
	}
	inline void status(task_status s)
	{
		_status = s;
	}

	inline KSGDeviceNode* root_node(KSGDeviceNode* root = NULL)
	{
		KSGDeviceNode *old = _root_node;
		if(root)
		{
			_root_node = root;
		}
		return _root_node;
	}

	inline std::string key_name() const
	{
		return _key_name;
	}
	inline void key_name(const std::string &key)
	{
		_key_name = key;
	}

	int load_all_device(KSGDeviceNode * parent);
};

//< 将所有的 Task_Queue 分类存放在 POOL 里
class KSG_Task_Queue_Pool
{
public:
	typedef std::list<KSG_Task_Queue*> queue_list_type;
private:
	class Queue_List_Cond 
	{
	private:
		/*
		ACE_Thread_Mutex _mutex;
		ACE_Condition<ACE_Thread_Mutex> _cond;
		*/
		ACE_Thread_Semaphore _mutex;
	public:
		Queue_List_Cond()
		{}
		~Queue_List_Cond();
		int wait(ACE_Time_Value *time_out);
		int broadcast();
		int signal();
		static void sleep_hook(void *arg);
	};
	typedef std::map<std::string,queue_list_type*> key_queue_map_type;
	typedef std::map<std::string,Queue_List_Cond*> queue_cond_map_type;
	typedef boost::object_pool<KSG_Task_Queue> queue_pool_type;
	
	key_queue_map_type _key_queue_list;
	queue_pool_type _queue_pool;
	ACE_Thread_Mutex _mutex;
	queue_cond_map_type _queue_cond;
	void free_queue_list(KSG_Task_Queue *queue);
	void free_all_queue();
public:
	virtual ~KSG_Task_Queue_Pool();
	virtual KSG_Task_Queue* add_initial_queue(const std::string &key);
	virtual int remove_queue(const std::string &key,KSG_Task_Queue *queue);
	virtual int is_contain_key(const std::string &key) const;
	/** 
	 * @brief 等待队列
	 * 
	 * @param key - 队列分组标识
	 * @param usec - 超时时间, 单位为 ms , 如果为 0 表示一直等待
	 * 
	 * @return - -1 表示失败, 0 表示成功, 1 表示超时
	 */
	virtual int wait_for_queue(const std::string &key,long time_out);
	virtual int singal_queue(const std::string &key,KSG_Task_Queue *queue);
	virtual queue_list_type* find_queue_list(const std::string &key) const;
protected:
	friend class KSG_Task_Scheduler;
	friend class ACE_Singleton<KSG_Task_Queue_Pool,ACE_Thread_Mutex>;
	KSG_Task_Queue_Pool();
};

typedef ACE_Singleton<KSG_Task_Queue_Pool,ACE_Thread_Mutex> Task_Queue_Pool;

//<! Scheduler 实现的接口
class KSG_Task_Scheduler_Implementation
{
public:
	virtual ~KSG_Task_Scheduler_Implementation()
	{
	}
	virtual int open(const std::string &key) = 0;
	virtual KSG_Task_Queue* peek_queue(long time_out) = 0;
	virtual int push_queue(KSG_Task_Queue *queue) = 0;
	virtual int process_loop_done() = 0;
	virtual int end_process_loop() = 0;
	/*
	 \brief 等待队列被唤醒
	 \param time_out 超时时间,单位为 ms
	 \return - 0 表示被唤醒, 1 表示等待超时, -1 表示失败
	*/
	virtual int wait_for_wake_up(long time_out) = 0;
	virtual int notify_new_task() = 0;

};

typedef KSG_Task_Scheduler_Implementation * (*Task_Schd_Impl_Creator_Type)();
typedef AbstractObject<std::string,KSG_Task_Scheduler_Implementation,
		Task_Schd_Impl_Creator_Type,
		CloneInstance> KSG_Task_Schd_Impl_Object;
typedef ACE_Singleton<KSG_Task_Schd_Impl_Object,ACE_Thread_Mutex> Task_Schd_Impl_Object;

inline bool _register_schd_impl_class(const std::string &id,Task_Schd_Impl_Creator_Type cr)
{
	Task_Schd_Impl_Object::instance()->Register(id,cr);
	return true;
}

#ifdef KSG_REGISTER_SCHD_IMPL_CLASS
#undef KSG_REGISTER_SCHD_IMPL_CLASS
#endif 

#define KSG_REGISTER_SCHD_IMPL_CLASS(theid,clazz) \
	bool clazz::clazz##Registered =_register_schd_impl_class(theid,\
	reinterpret_cast<Task_Schd_Impl_Creator_Type>(clazz::clazz##CreateObject))

class KSG_Task_Schd_Token_Guard
{
public:
	KSG_Task_Schd_Token_Guard(ACE_Token &token);
	KSG_Task_Schd_Token_Guard(void);
	~KSG_Task_Schd_Token_Guard();
	int acquire_token(ACE_Time_Value *tv);
	int release_token();
	int is_owner() const;
private:
	ACE_Token &_token;
	int _owner;
	KSG_Task_Schd_Token_Guard(const KSG_Task_Schd_Token_Guard&);
	KSG_Task_Schd_Token_Guard& operator=(const KSG_Task_Schd_Token_Guard&);
};

class KSG_Task_Scheduler
{
private:
	KSG_Task_Scheduler_Implementation *_implement;
	//ACE_Recursive_Thread_Mutex _process_mutex;
	ACE_Token _process_mutex;
	ACE_Thread_Semaphore _start_sem;

	typedef KSGTaskManager::PointerType TaskPointer;

	int execute_task(KSG_Task_Queue *queue);
	int do_try_task(TaskPointer task);
public:
	typedef KSG_Task_Queue::task_type task_type;
	KSG_Task_Scheduler(KSG_Task_Scheduler_Implementation * impl = NULL);
	~KSG_Task_Scheduler();
	int open(const std::string &queue_key);
	int process_loop_done();
	/** 
	 * @brief 执行一个任务
	 * 
	 * @param time_out  - 如果没有任务等待的超时时间(ms), <=0 表示一直等待
	 * 
	 * @return 返回 0 表示处理成功, 返回 -1 表示处理失败
	 */
	int process_task(long time_out = -1);
	int end_process_loop();
	KSG_Task_Scheduler_Implementation* implementation() const
	{
		return _implement;
	}
	int wait_semaphore();
	int release_semaphore();
	int notify_new_task();
};


class KSG_Queue_Task_Scheduler_Impl : public KSG_Task_Scheduler_Implementation
{
	DECLARE_FACTORY_CREATOR(KSG_Queue_Task_Scheduler_Impl)
private:
	struct Queue_Head
	{
		KSG_Task_Queue * _head;
		ACE_Thread_Mutex _mutex;
	};
	//KSG_Task_Queue *_head_of_running, *_head_of_waiting, *_head_of_sleeping, *_head_of_blocking;
	Queue_Head *_head_of_running, *_head_of_waiting, *_head_of_sleeping, *_head_of_blocking;
	std::string _queue_key;
	void initial_new_queue(const std::string &key,Queue_Head **queue);
	
	KSG_Task_Queue* push_back_queue(Queue_Head *head,KSG_Task_Queue *queue);
	KSG_Task_Queue* remove_queue(Queue_Head *head,KSG_Task_Queue *queue);
	KSG_Task_Queue* insert_front_queue(Queue_Head *head,KSG_Task_Queue *queue);
	void free_queue_head(Queue_Head *head);
	int _is_end_loop;
public:
	KSG_Queue_Task_Scheduler_Impl();
	virtual ~KSG_Queue_Task_Scheduler_Impl();
	virtual int open(const std::string &key);
	virtual KSG_Task_Queue* peek_queue(long time_out);
	virtual int push_queue(KSG_Task_Queue *queue);
	virtual int process_loop_done();
	virtual int end_process_loop();
	virtual int wait_for_wake_up(long time_out);
	virtual int notify_new_task();
};

#endif // _TASK_SCHEDULER_H_

