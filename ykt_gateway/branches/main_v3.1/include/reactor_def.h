#ifndef _KSG_REACTOR_DEF_H_
#define _KSG_REACTOR_DEF_H_

#include <ace/Message_Block.h>
#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/Event.h>
#include <ace/Auto_Event.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Atomic_Op.h>
#include <ace/Message_Queue_T.h>
#include <ace/Thread_Mutex.h>
#include <ace/Task_T.h>
#include <boost/pool/object_pool.hpp>
#include <list>
#include "listener.h"

class KSG_Reactor_Work_Thr;
class KSG_Reactor_Scheduler;

class KSG_Reactor_Request 
{
public:
	KSG_Reactor_Request();
	virtual ~KSG_Reactor_Request();

	virtual int process_request(void *arg,long timeout = 5000) = 0;
	virtual long default_timeout();

};
class KSG_Service_Handler : public ACE_Event_Handler
{
private:
	KSG_Reactor_Scheduler *scheduler_;
	int processing_;
	int closed_;
	unsigned long index_;
	ACE_Time_Value max_client_timeout_;
	static ACE_Atomic_Op<ACE_Thread_Mutex,unsigned long> handle_idx_;
	typedef ACE_Message_Queue_Ex<ACE_Message_Block, ACE_MT_SYNCH> MESSAGE_QUEUE_EX;
	int release();
	int mask_;
	
protected:
	friend class KSG_Reactor_Work_Thr;
	//MESSAGE_QUEUE_EX msg_queue_;
	ACE_SOCK_Stream peer_;
	//! 建立连接时间
	ACE_Time_Value connect_time_;
	
	//! 请求处理开始时间
	ACE_Time_Value process_start_time_;
	//! 请求处理结束时间
	ACE_Time_Value process_end_time_;
	ACE_Message_Block *mblk_;
	ACE_Message_Block *curr_blk_;
	//! 判断数据包是否已经接收完成,可以进行业务处理,必须由子类实现
	/*!
	 \return 0 表示还需要继续接收数据 , 1 表示可以进行业务处理 , -1 表示数据包不合法
	*/
	virtual int recv_data(ACE_Message_Block *&blk) = 0;

	// request 处理
	KSG_Reactor_Request * request_;
public:
	//! 请求开始时间
	ACE_Time_Value request_time_;

	KSG_Service_Handler(ACE_Reactor *r);
	virtual ~KSG_Service_Handler();
	//! Activate the object
	virtual int open();
	//! 当有数据到达时被调用
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	//! 当对象对销毁时被调用
	virtual int handle_close(ACE_HANDLE handle = ACE_INVALID_HANDLE, ACE_Reactor_Mask close_mask = 0);
	virtual int handle_timeout(const ACE_Time_Value &current_time, const void *act /* = 0 */);
	virtual int handle_exception(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
	//! 处理业务流程函数,必须由子类实现
	/*!
	 \return 0 表示业务处理成功, -1 表示业务处理失败, 1 表示处理成功并且需要应答给对方
	*/
	virtual int process_request(long timeout = 5000) = 0;
	//
	void scheduler(KSG_Reactor_Scheduler *s) 
	{
		scheduler_ = s;
	}
	KSG_Reactor_Scheduler *scheduler() 
	{
		return scheduler_;
	}
	virtual long default_timeout()
	{
		// 默认不处理 10000 ms 前的请求
		return 10000;
	}
	void process_end();
	int closed() const { return closed_; }
	void process(int p) { processing_ = p; }
	int process() const { return processing_; }

	ACE_SOCK_Stream &peer() { return peer_; }

	virtual ACE_HANDLE get_handle (void) const {
		const ACE_SOCK_Stream h = const_cast<ACE_SOCK_Stream &>(peer_);
		return h.get_handle ();
	};

	unsigned long get_index() const { return index_; }

	//int getq(ACE_Message_Block *&mb);
	//int putq(ACE_Message_Block *mb);
	KSG_Reactor_Request*  get_request() const 
	{
		return request_;
	}
};

//! 侦听句柄
class KSG_Service_Acceptor : public KSG_Server_Listener,public ACE_Event_Handler
{
private:
	ACE_SOCK_Acceptor acceptor_;
	KSG_Reactor_Scheduler *schd_;
protected:
	//! 创建新句柄
	virtual KSG_Service_Handler *new_handle() = 0;
	virtual int free_handle(KSG_Service_Handler *handle) = 0;
public:
	typedef ACE_INET_Addr PEER_ADDR;
	//! constructor
	KSG_Service_Acceptor(ACE_Reactor * reactor = ACE_Reactor::instance())
		:ACE_Event_Handler(reactor)
	{}

	// 打开端口开始侦听
	virtual int open(const ACE_INET_Addr &local_addr);
	//! 当有新的连接请求到达时被调用
	virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
	//! 当对象被销毁时调用
	virtual int handle_close(ACE_HANDLE handle = ACE_INVALID_HANDLE
		, ACE_Reactor_Mask close_mask = 0);
	//!
	virtual ACE_HANDLE get_handle() const 
	{
		return acceptor_.get_handle();
	}
	//! 返回底层 acceptor
	ACE_SOCK_Acceptor &acceptor() 
	{
		return acceptor_;
	}
	void scheduler(KSG_Reactor_Scheduler *s)
	{
		schd_ = s;
	}
};

class KSG_ExceptSock_Handler : public ACE_Event_Handler
{
private:
	ACE_HANDLE error_handle_;
public:
	KSG_ExceptSock_Handler(){}
	virtual ~KSG_ExceptSock_Handler();
	virtual int handle_exception(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
	void set_error_handle(ACE_HANDLE h) { error_handle_ = h;}
	ACE_HANDLE get_error_handle() const { return error_handle_; }
};


class KSG_Reactor_Work_Thr;
//! 对请求进行分类处理的业务线程
class KSG_Reactor_Scheduler : public ACE_Task<ACE_NULL_SYNCH>
{
public:
	struct SERVER_HANDLER
	{
		ACE_HANDLE handle_;
		ACE_Message_Block *mblk_;
		KSG_Reactor_Request *request_;
		ACE_Time_Value request_time_;
		ACE_Event_Handler *event_handler_;
	};
private:
	ACE_Reactor *reactor_;
	typedef boost::object_pool<SERVER_HANDLER> SERVICE_HANDLER_POOL;
	typedef std::list<SERVER_HANDLER*> SERVICE_HANDLER_LIST;
	//! 等待处理的句柄, 采用简单的先进先出方式
	SERVICE_HANDLER_LIST process_list_;
	SERVICE_HANDLER_LIST finish_list_;
	SERVICE_HANDLER_LIST invalid_list_;
	SERVICE_HANDLER_POOL svr_handler_pool_;
	ACE_Thread_Mutex mutex_;
	ACE_Auto_Event event_;
	KSG_Reactor_Work_Thr *work_thr_;
	KSG_ExceptSock_Handler except_event_;
public:
	KSG_Reactor_Scheduler();
	~KSG_Reactor_Scheduler();
	//! 主业务线程
	virtual int svc();
	//! 获取最早一个业务队列
	//KSG_Service_Handler *peek_handle();
	SERVER_HANDLER *peek_handle();
	int push_handle(KSG_Service_Handler *handle,ACE_Message_Block *mblk);
	int push_mblk(ACE_Message_Block *mblk);
	int wait();
	void shutdown(int maxthr);
	void work_thr(KSG_Reactor_Work_Thr *r);
	int free_handle(SERVER_HANDLER *hd);
	int close_error_socket(ACE_HANDLE fd);
	ACE_Reactor* reactor();
	void reactor(ACE_Reactor *rec) {reactor_ = rec;}
};

typedef KSG_Reactor_Scheduler::SERVER_HANDLER KSG_WORK_SVR_HANDLER;

//! 处理业务逻辑的线程
class KSG_Reactor_Work_Thr : public ACE_Task<ACE_NULL_SYNCH>
{
private:
	KSG_Reactor_Scheduler *schd_;
	int do_task(KSG_Service_Handler *handle);
	int do_task2(KSG_Reactor_Scheduler::SERVER_HANDLER *handle);
public:
	KSG_Reactor_Work_Thr(KSG_Reactor_Scheduler *schd);
	~KSG_Reactor_Work_Thr();
	virtual int svc();
};

typedef ACE_Singleton<KSG_Reactor_Scheduler,ACE_Null_Mutex> REACTOR_SCHEDULER;
class KSG_Reactor_Listener_Task : public KSG_Listener_Task
{
private:
	ACE_Reactor *reactor_;
	KSG_Reactor_Work_Thr  work_thr_;
	KSG_Reactor_Scheduler *scheduler_;
	int max_work_thr_;
protected:
	virtual int init_listener(KSG_Server_Listener *l);
public:
	KSG_Reactor_Listener_Task();
	virtual ~KSG_Reactor_Listener_Task();
	virtual int start_task(int max_task);
	virtual int stop_task();
	virtual int svc();
};



#endif // _KSG_REACTOR_DEF_H_
