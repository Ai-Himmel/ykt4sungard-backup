/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "proactor_def.h"
#include "ksgateway.h"
#include "factory.h"
#include <ace/Proactor.h>
#include <ace/Proactor_Impl.h>
#include <ace/WIN32_Proactor.h>
#include <ace/POSIX_Proactor.h>

///////////////////////////////////////////////////////////////////////////
// KSG_Proactor_Task 
KSG_Proactor_Task::KSG_Proactor_Task():_max_task(0),_sem(NULL)
{
	//
}
KSG_Proactor_Task::~KSG_Proactor_Task()
{
	if(_sem)
	{
		_sem->release();
		delete _sem;
		_sem = NULL;
	}
}

int KSG_Proactor_Task::start_task(int max_task)
{
	_max_task = max_task;
	if(_max_task <= 0)
		_max_task = 1;
	if(_sem)
	{
		_sem->release();
		_sem->remove();
		delete _sem;
	}
	ACE_NEW_RETURN(_sem,ACE_Thread_Semaphore(_max_task),-1);
	for(int i = _max_task;i>0;i--)
		_sem->acquire();
	ACE_DEBUG((LM_DEBUG,"准备启动线程..."));
	activate(THR_NEW_LWP|THR_JOINABLE,_max_task);
	return 0;
}

int KSG_Proactor_Task::stop_task()
{
	// 关闭 Proactor 服务
	ACE_Proactor::instance()->proactor_end_event_loop();
	// 等待所有线程被关闭
	this->wait();
	// 释放所有 acceptor 以及 连接
	listener_map_type::const_iterator iter;
	for(iter = _listeners.begin(); iter != _listeners.end();++iter)
	{
		KSG_Proactor_Listener * pl = iter->second;
		if(pl)
		{
			ACE_DEBUG((LM_DEBUG,"关闭 Listener!"));
			pl->stop_listen();
			delete pl;
		}
	}
	_listeners.clear();
	return 0;
}

int KSG_Proactor_Task::svc()
{
	int ret;
	_sem->release(1);
	while(!ACE_Proactor::instance()->proactor_event_loop_done())
	{
		ACE_Time_Value t(5,0);
		ret = ACE_Proactor::instance()->handle_events(t);
		if(ret < 0)
			ACE_DEBUG((LM_ERROR,"Poractor 执行失败!"));
		else if(ret == 0)
            ACE_DEBUG((LM_DEBUG,"Proactor 没有事件处理"));
		else
			ACE_DEBUG((LM_DEBUG,"Proactor 服务正在运行"));
	}
	ACE_DEBUG((LM_DEBUG,"Proactor 线程结束进行..."));
	return 0;
}

int KSG_Proactor_Task::register_listener(int id,ListenerCreatorType creator)
{
	_listener_classes.Register(id,creator);
	return 0;
}

int KSG_Proactor_Task::start_listener(int id)
{
	KSG_Proactor_Listener *pl = NULL;
	listener_map_type::const_iterator iter = _listeners.find(id);
	if( iter != _listeners.end())
		pl = iter->second;
	else
		pl = _listener_classes.Create(id);
	if(!pl)
		return -1;
	_listeners.insert(listener_map_type::value_type(id,pl));
	return pl->start_listen();
}

//////////////////////////////////////////////////////////////////////////
//
KSG_Proactor_Acceptor::KSG_Proactor_Acceptor(size_t max_cli_cnt)
:_max_clients_cnt(max_cli_cnt),_total_cli(0)
{
	_clients.clear();
}

KSG_Proactor_Acceptor::~KSG_Proactor_Acceptor()
{
	close();
}

void KSG_Proactor_Acceptor::remove(handler_type* ih)
{
	ACE_GUARD(ACE_Recursive_Thread_Mutex,ace_mon,*ACE_Static_Object_Lock::instance());
	if(_total_cli > _max_clients_cnt)
	{
		_total_cli--;
		ACE_DEBUG((LM_DEBUG,"句柄数超过上限,释放句柄资源, 剩余[%d]",_total_cli));
		delete ih;
	}
	else
		_clients.push_back(ih);
}
void KSG_Proactor_Acceptor::close()
{
	ACE_GUARD(ACE_Recursive_Thread_Mutex,ace_mon,*ACE_Static_Object_Lock::instance());
	handler_type *ih;
	std::list<handler_type*>::iterator iter;
	for(iter = _clients.begin(); iter != _clients.end(); ++iter)
	{
		ih = *iter;
		delete ih;
	}
	_clients.clear();
}

KSG_Proactor_Handler* KSG_Proactor_Acceptor::make_handler()
{
	ACE_DEBUG((LM_DEBUG,"开始申请 ACE HANDLER ..."));
	ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,ace_mon,*ACE_Static_Object_Lock::instance(),NULL);
	handler_type* ih;
	if(_clients.empty())
	{
		ih = new_handler();
		_total_cli++;
		ih->set_handler_id(static_cast<int>(_total_cli));
		ACE_DEBUG((LM_DEBUG,"创建第 [%d] 个句柄对象",_total_cli));
	}
	else
	{
		ih = _clients.front();
		_clients.pop_front();
	}
	ACE_DEBUG((LM_DEBUG,"申请 ACE HANDLER 成功!"));
	return ih;
}

//////////////////////////////////////////////////////////////////////////

KSG_Proactor_Handler::~KSG_Proactor_Handler()
{
	ACE_DEBUG((LM_DEBUG,"释放 ACE 连接 ... "));
}

KSG_Proactor_Handler::KSG_Proactor_Handler(
	KSG_Proactor_Acceptor* acceptor /* = NULL */)
	:_acceptor(acceptor),_mblk(NULL),_handler_id(0)
{
	int sec = KsgGetGateway()->GetConfig()->_execTimeout/1000+8;
	sec = sec < 4 ? 4 : sec;
	_max_timeout_sec = ACE_Time_Value(sec);
	this->handle(ACE_INVALID_HANDLE);
}
void KSG_Proactor_Handler::open(ACE_HANDLE new_handle
								  , ACE_Message_Block &message_block)
{
	ACE_DEBUG((LM_DEBUG,"打开连接 HANDLER[%d]",get_handler_id()));
	this->handle(new_handle);
	if(_reader.open(*this) == -1 
		|| _writer.open(*this) == -1)
	{
		ACE_DEBUG((LM_ERROR,"打开 ACE 连接失败!!!"));
		free_handler();
		return;
	}
	on_open(new_handle,message_block);
	/*
	if(proactor()->schedule_timer(*this,NULL,_max_timeout_sec) == -1)
	{
		ACE_DEBUG((LM_ERROR,"设置超时控制失败"));
		free_handler();
		return;
	}
	*/
	ACE_DEBUG((LM_DEBUG,"打开连接成功..."));
}

int KSG_Proactor_Handler::free_handler()
{
	ACE_DEBUG((LM_DEBUG,"开始归还 ACE HANDLER [%d] ... ",get_handler_id()));
	/*
	if(_reader.implementation())
		_reader.cancel();
	if(_writer.implementation())
		_writer.cancel();
	
	if(proactor())
		proactor()->cancel_timer(*this);
	*/
	if(this->handle() != ACE_INVALID_HANDLE)
	{
		ACE_Message_Block mb(1);
		_reader.read(mb,0);
		ACE_OS::closesocket(this->handle());
	}
	this->handle(ACE_INVALID_HANDLE);
	if(_mblk) _mblk->release();
	_mblk = NULL;
	on_free_handler();
	_acceptor->remove(this);
	ACE_DEBUG((LM_DEBUG,"归还 ACE HANDLER 完成"));
	return 0;
}

void KSG_Proactor_Handler::handle_time_out(const ACE_Time_Value &tv
											 , const void *act /* = NULL */)
{
	ACE_DEBUG((LM_ERROR," HANDLER [%d]超时...",get_handler_id()));
	free_handler();
}

inline int KSG_Proactor_Handler::get_handler_id()
{
	return _handler_id;
}

void KSG_Proactor_Handler::set_handler_id(int id)
{
	_handler_id = id;
}

