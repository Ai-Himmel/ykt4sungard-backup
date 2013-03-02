#ifndef _PROACTOR_DEF_H_
#define _PROACTOR_DEF_H_

#include <ace/Thread_Semaphore.h>
#include <ace/Task_T.h>
#include <ace/Asynch_Acceptor.h>
#include <ace/Asynch_IO.h>
#include <ace/Recursive_Thread_Mutex.h>
#include <map>
#include "factory.h"
#include "xutils/xsingleton.h"
#include "thread.h"

//! Proactor listener 

class KSG_Proactor_Listener
{
public:
	KSG_Proactor_Listener(){}
	virtual ~KSG_Proactor_Listener(){}
	virtual int start_listen() = 0;
	virtual int stop_listen() = 0;
};


//! proactor task
class KSG_Proactor_Task : public ACE_Task<ACE_MT_SYNCH>
{
public:
	typedef AbstractObject<int,KSG_Proactor_Listener> ListenerClassMap;
	typedef ListenerClassMap::CreatorType ListenerCreatorType;

	KSG_Proactor_Task();
	virtual ~KSG_Proactor_Task();
	int start_task(int max_task);
	int stop_task();
	virtual int svc();
	int register_listener(int id,ListenerCreatorType creator);
	int start_listener(int id);
private:
	int _max_task;
	ACE_Thread_Semaphore *_sem;
	ListenerClassMap _listener_classes;
	typedef std::map<int,KSG_Proactor_Listener*> listener_map_type;
	listener_map_type _listeners;
	KSG_Proactor_Listener* create_listener(int id);
};

class KSG_Proactor_Handler;
//!
/*
  NOTICE: ע��˴��ļ̳�˳���ܱ䣬������ KSG_Proactor_Listener ���麯��
  ָ�����ô���
 */
class KSG_Proactor_Acceptor :
	public KSG_Proactor_Listener
	,public ACE_Asynch_Acceptor<KSG_Proactor_Handler>
{
public:
	typedef KSG_Proactor_Handler handler_type;
	enum { DEFAULT_MAX_CLIENT_CNT = 50 };
	KSG_Proactor_Acceptor(size_t max_cli_cnt = DEFAULT_MAX_CLIENT_CNT);
	virtual ~KSG_Proactor_Acceptor();
	inline void remove(handler_type* ih);
	void close();
protected:
	//!
	/*
	 \brief ���� Handler ����Ľӿڣ�����������ʵ��
	 \return ���� Handler ����ָ�룬 ʧ�ܷ��� NULL
	 */
	virtual KSG_Proactor_Handler* new_handler() = 0;
	virtual KSG_Proactor_Handler* make_handler();
private:
	std::list<handler_type*> _clients;
	size_t _max_clients_cnt;
	size_t _total_cli;
};

//!
/*
 ��Ϊ�����ϵ����⣬ ACE �������������Ϊ�����࣬
 ���� on_open , on_free_handler ������һ���յ�ʵ��
 */
class KSG_Proactor_Handler : public ACE_Service_Handler
{
public:
	KSG_Proactor_Handler(KSG_Proactor_Acceptor* acceptor = NULL);
	virtual ~KSG_Proactor_Handler();
	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);
protected:
	ACE_Asynch_Read_Stream _reader;
	ACE_Asynch_Write_Stream _writer;
	ACE_Message_Block *_mblk;
	KSG_Proactor_Acceptor *_acceptor;
	ACE_Time_Value _max_timeout_sec;

	virtual void handle_time_out(const ACE_Time_Value &tv, const void *act = NULL);
	virtual int free_handler();
	//! �����Ӵ� Proactor ���� open �ӿ�ʱ������, ������ʵ��
	virtual int on_open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
	{return 0;}
	//! ������ free_handler ����ʱ������, ������ʵ��
	virtual int on_free_handler()
	{return 0;}
	inline int get_handler_id();
private:
	friend class KSG_Proactor_Acceptor;
	void set_handler_id(int id);
	int _handler_id;
};

typedef xutil::SingletonHolder<KSG_Proactor_Task,KSGSingleThreadModel> Proactor_Task;
#define KSG_ADD_LISTENER_CLASS(id,clazz) \
	bool clazz::clazz##Registered = Proactor_Task::Instance().register_listener(id, \
	reinterpret_cast<KSG_Proactor_Task::ListenerCreatorType>(clazz::clazz##CreateObject))


#endif // _PROACTOR_DEF_H_
