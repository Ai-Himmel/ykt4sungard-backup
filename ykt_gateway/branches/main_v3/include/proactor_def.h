#ifndef _PROACTOR_DEF_H_
#define _PROACTOR_DEF_H_

#include <ace/Thread_Semaphore.h>
#include <ace/Task_T.h>
#include <ace/Asynch_Acceptor.h>
#include <ace/Asynch_IO.h>
#include <ace/Null_Mutex.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Atomic_Op.h>
#include <map>
#include <set>
#include <ace/Singleton.h>
#include "factory.h"
#include "thread.h"
#include "ksgateway.h"
#include "listener.h"


class KSG_Proactor_Handler;
//!
/*
  NOTICE: 注意此处的继承顺序不能变，否则会对 KSG_Proactor_Listener 的虚函数
  指针引用错误
 */
class KSG_Proactor_Acceptor :
	public KSG_Server_Listener
	,public ACE_Asynch_Acceptor<KSG_Proactor_Handler>
{
public:
	typedef KSG_Proactor_Handler handler_type;
	enum { DEFAULT_MAX_CLIENT_CNT = 50 };
	KSG_Proactor_Acceptor(size_t max_cli_cnt = DEFAULT_MAX_CLIENT_CNT);
	virtual ~KSG_Proactor_Acceptor();
	void check_timeout_handle(long msec);
	inline void remove(handler_type* ih);
	void close();
	/*
	virtual int open(const ACE_INET_Addr &address, size_t bytes_to_read, int pass_addresses, 
		int backlog, int reuse_addr, ACE_Proactor *proactor, int validate_new_connection, 
		int reissue_accept, int number_of_initial_accepts);
	
	virtual int validate_connection(const ACE_Asynch_Accept::Result &result,
			const ACE_INET_Addr &remote,
			const ACE_INET_Addr &local);
	*/
protected:
	//!
	/*
	 \brief 创建 Handler 对象的接口，必须由子类实现
	 \return 返回 Handler 对象指针， 失败返回 NULL
	 */
	virtual KSG_Proactor_Handler* new_handler() = 0;
	virtual KSG_Proactor_Handler* make_handler();
private:
	std::list<handler_type*> _clients;
	std::set<handler_type*> _used_clts;
	size_t _max_clients_cnt;
	size_t _total_cli;
};

//! 
/*
 */
class KSG_Proactor_Check_Handler : public ACE_Handler
{
private:
	KSG_Proactor_Acceptor *acceptor_;
public:
	KSG_Proactor_Check_Handler(KSG_Proactor_Acceptor *apt):acceptor_(apt)
	{}

	virtual void handle_time_out(const ACE_Time_Value &tv, const void *act /* = 0 */);
};
//!
/*
 因为编译上的问题， ACE 不允许将这个类做为纯虚类，
 所以 on_open , on_free_handler 函数有一个空的实现
 */
class KSG_Proactor_Handler : public ACE_Service_Handler
{
public:
	KSG_Proactor_Handler(KSG_Proactor_Acceptor* acceptor = NULL);
	virtual ~KSG_Proactor_Handler();
	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);
	virtual void addresses(const ACE_INET_Addr &remote_address, const ACE_INET_Addr &local_address);
protected:
	ACE_Asynch_Read_Stream _reader;
	ACE_Asynch_Write_Stream _writer;
	ACE_Message_Block *_mblk;
	KSG_Proactor_Acceptor *_acceptor;
	ACE_Time_Value _max_timeout_sec;
	ACE_Time_Value _last_io_time;
	ACE_INET_Addr _remote_addr;

	void update_io_time()
	{
		_last_io_time = ACE_OS::gettimeofday();
	}
	virtual void handle_time_out(const ACE_Time_Value &tv, const void *act = NULL);
	virtual int free_handler();
	//! 当连接打开 Proactor 调用 open 接口时被调用, 由子类实现
	virtual int on_open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
	{return 0;}
	//! 当调用 free_handler 函数时被调用, 由子类实现
	virtual int on_free_handler()
	{return 0;}
	inline int get_handler_id();
	inline void can_close_handle()
	{
		_can_be_closing = 1;
	}
	//ACE_Atomic_Op<ACE_Mutex,int> _send_count;
	//ACE_Atomic_Op<ACE_Mutex,int> _recv_count;
	int _send_count;
	int _recv_count;
private:
	friend class KSG_Proactor_Acceptor;
	void set_handler_id(int id);
	int _handler_id;
	int _can_be_closing;
	
};

class KSG_Proactor_Listener_Task : public KSG_Listener_Task
{
private:
	int _max_task;
	ACE_Thread_Semaphore *_sem;
public:
	KSG_Proactor_Listener_Task();
	~KSG_Proactor_Listener_Task();
	virtual int svc();
	virtual int start_task(int max_task);
	virtual int stop_task();
};


#endif // _PROACTOR_DEF_H_
