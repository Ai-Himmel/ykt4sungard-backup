#include "ksglobal.h"
#include "reactor_def.h"
#include "ksgateway.h"
#include <ace/Select_Reactor.h>
#ifdef ACE_HAS_EVENT_POLL
#include <ace/Dev_Poll_Reactor.h>
#endif

///////////////////////////////////////////////////////////////////////////
KSG_Reactor_Request::KSG_Reactor_Request()
{

}
KSG_Reactor_Request::~KSG_Reactor_Request()
{

}
long KSG_Reactor_Request::default_timeout()
{
	return 10000;
}

//////////////////////////////////////////////////////////////////////////
// KSG_Service_Handler
ACE_Atomic_Op<ACE_Thread_Mutex,unsigned long> KSG_Service_Handler::handle_idx_ = 0;

KSG_Service_Handler::KSG_Service_Handler(ACE_Reactor *r)
:ACE_Event_Handler(r),processing_(0),closed_(0),mblk_(NULL),curr_blk_(NULL),index_(0),
mask_(0),max_client_timeout_(180) // 3 ���ӳ�ʱ
{
	handle_idx_++;
	index_ = handle_idx_.value();
//	msg_queue_.high_water_mark(10);
	ACE_DEBUG((LM_TRACE,"����������,handle idx[%d]",index_));
}
KSG_Service_Handler::~KSG_Service_Handler()
{
	handle_idx_--;
	index_ = handle_idx_.value();
	ACE_DEBUG((LM_TRACE,"�ͷ�����,handle idx[%d]",index_));
}
int KSG_Service_Handler::open()
{
	this->request_time_ = ACE_OS::gettimeofday();
	this->connect_time_ = this->request_time_;
	char val[2] = "";
	int len = 1;
	val[0] = 0x1;
	if(ACE_OS::setsockopt(peer().get_handle(),SOL_SOCKET,TCP_NODELAY,val,len)!=0)
		ACE_DEBUG((LM_ERROR,"����������,��������ʧ��"));
	// ׼����ȡ����
	if(this->reactor()->register_handler(this,ACE_Event_Handler::READ_MASK))
	{
		ACE_DEBUG((LM_ERROR,"ע���������ʧ��"));
		return -1;
	}
	ACE_Time_Value reschedule (max_client_timeout_.sec () / 4);
	reactor()->schedule_timer(this,0,max_client_timeout_,reschedule);
	ACE_SET_BITS(this->mask_,ACE_Event_Handler::READ_MASK);
	return 0;
}
int KSG_Service_Handler::handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */)
{
	int ret;
	ACE_INET_Addr peer_addr;
	peer_.set_handle(fd);

	this->peer().get_remote_addr(peer_addr);
	//if(processing_)
	//{
	//	ACE_DEBUG((LM_INFO,"ҵ�����У��ֽ��յ��Է��������ݰ���ip[%s]",peer_addr.get_host_addr()));
	//}
	//this->processing_ = 1;
	ret = recv_data(curr_blk_);

	if(ret == -1)
	{
		ACE_DEBUG((LM_TRACE,"�ӻ���豸�������ݴ���"));
		if(curr_blk_)
		{
			curr_blk_->release();
			curr_blk_ = NULL;
		}
		return -1;
	}
	else if(0 == ret)
	{
		// ������ȡ
		//this->reactor()->register_handler(this,ACE_Event_Handler::READ_MASK);
		
		ACE_DEBUG((LM_TRACE,"������ȡ�������ip[%s]",peer_addr.get_host_addr()));
		return 0;
	}
	else
	{
		if(curr_blk_==NULL)
		{
			return 0;
		}
		// д�������,�ȴ�����
		// ��������ʱ��
		this->request_time_ = ACE_OS::gettimeofday();
		
		if(this->scheduler()->push_handle(this,curr_blk_) == -1)
		{
			// д�봦�����ʧ��,���ش���
			ACE_DEBUG((LM_ERROR,"д���������ʧ��"));
			curr_blk_->release();
			curr_blk_ = NULL;
			return -1;
		}
		curr_blk_ = NULL;
		return 0;
	}
}

int KSG_Service_Handler::handle_timeout(const ACE_Time_Value &current_time, const void *act )
{
	if(current_time - this->request_time_ >= max_client_timeout_
		|| current_time - this->connect_time_ >= max_client_timeout_)
	{
		ACE_DEBUG((LM_INFO,"���ӳ�ʱ���ر�����..."));
		
		reactor()->remove_handler(this,ACE_Event_Handler::ALL_EVENTS_MASK|ACE_Event_Handler::DONT_CALL);
		//reactor()->notify(this);
		closed_ = 1;
		return -1;
	}
	return 0;
}
int KSG_Service_Handler::handle_exception(ACE_HANDLE fd )
{
	//return this->handle_close(fd,ACE_Event_Handler::EXCEPT_MASK);
	return -1;
}
void KSG_Service_Handler::process_end()
{
	process_end_time_ = ACE_OS::gettimeofday();
	processing_ = 0;
}

int KSG_Service_Handler::release()
{
	if(curr_blk_)
	{
		// ����������һ���ʱ��ر����ӣ�����Ҫ�ͷ���Դ
		curr_blk_->release();
		curr_blk_ = NULL;
	}
	reactor()->cancel_timer(this);
	//reactor()->remove_handler(this,ACE_Event_Handler::ALL_EVENTS_MASK);
	return 0;
}
int KSG_Service_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{

	closed_ = 1;
	ACE_DEBUG((LM_TRACE,"handle_close[%08X]",this->get_handle()));
	release();

	ACE_OS::closesocket(this->get_handle());

	//if(ACE_BIT_ENABLED(close_mask,ACE_Event_Handler::READ_MASK))
	//	ACE_CLR_BITS(this->mask_,close_mask);
	//if(this->mask_ == 0)
	{
		delete this;
	}
	return -1;
}
/*
int KSG_Service_Handler::putq(ACE_Message_Block *mb)
{
	ACE_Time_Value tv(1);
	tv += ACE_OS::gettimeofday();
	return msg_queue_.enqueue_tail(mb,&tv);
}
int KSG_Service_Handler::getq(ACE_Message_Block *&mb)
{
	ACE_Time_Value tv(1);
	tv += ACE_OS::gettimeofday();
	return msg_queue_.dequeue_head(mb,&tv);
}
*/
//////////////////////////////////////////////////////////////////////////
// 

class KSG_Quit_Handler : public ACE_Event_Handler {
public:
	KSG_Quit_Handler (ACE_Reactor *r) : ACE_Event_Handler (r) {}

	virtual int handle_exception (ACE_HANDLE) {
		reactor ()->end_reactor_event_loop ();
		return -1; // Trigger call to handle_close() method.
	}

	virtual int handle_close (ACE_HANDLE, ACE_Reactor_Mask)
	{ delete this; return 0; }

protected:

	// Protected destructor ensures dynamic allocation.
	virtual ~KSG_Quit_Handler () {}
};

KSG_Reactor_Listener_Task::KSG_Reactor_Listener_Task():work_thr_(&scheduler_)
{
	//
}
KSG_Reactor_Listener_Task::~KSG_Reactor_Listener_Task()
{
	//
}
int KSG_Reactor_Listener_Task::svc()
{
	reactor_->owner(ACE_OS::thr_self());
	while(KsgGetGateway()->is_running())
	{
		ACE_Time_Value tv(5);
		tv += ACE_OS::gettimeofday();				//ȡ����ʱ��?
		reactor_->run_reactor_event_loop(tv);
		//if(reactor_->reactor_event_loop_done())
		//	break;
	}
	return 0;
}
int KSG_Reactor_Listener_Task::start_task(int max_task)
{
#ifdef ACE_HAS_EVENT_POLL
	ACE_Dev_Poll_Reactor *reactor_imp = new ACE_Dev_Poll_Reactor;
#else
	ACE_Select_Reactor *reactor_imp = new ACE_Select_Reactor;
#endif // ACE_HAS_EVENT_POLL
	reactor_ = new ACE_Reactor(reactor_imp);
	std::auto_ptr<ACE_Reactor> delete_instance(ACE_Reactor::instance(reactor_));
	work_thr_.activate(THR_NEW_LWP | THR_JOINABLE,max_task);
	max_work_thr_ = max_task;
	this->activate(THR_NEW_LWP | THR_JOINABLE,1);
	return 0;
}
int KSG_Reactor_Listener_Task::stop_task()
{
	KSG_Quit_Handler *quit_handler = 0;
	ACE_NEW_RETURN (quit_handler, KSG_Quit_Handler (reactor_), 0);
	reactor_->notify (quit_handler);
	this->scheduler_.shutdown(max_work_thr_);
	work_thr_.wait();
	wait();
	return 0;
}
int KSG_Reactor_Listener_Task::init_listener(KSG_Server_Listener *l)
{
	KSG_Service_Acceptor *acceptor = reinterpret_cast<KSG_Service_Acceptor*>(l);
	if(!acceptor)
	{
		ACE_DEBUG((LM_ERROR,"��������ʧ��!"));
		return -1;
	}
	acceptor->reactor(reactor_);
	acceptor->scheduler(&scheduler_);
	scheduler_.reactor(reactor_);
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// KSG_Service_Acceptor

int KSG_Service_Acceptor::open(const ACE_INET_Addr &local_addr)
{
	if(acceptor_.open(local_addr) == -1) 
	{
		ACE_DEBUG((LM_ERROR,"�ڶ˿�[%d]����ʧ��!",local_addr.get_port_number()));
		return -1;
	}
	this->reactor()->register_handler(this,ACE_Event_Handler::ACCEPT_MASK);
	return 0;
}
int KSG_Service_Acceptor::handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */)
{
	KSG_Service_Handler *handle = new_handle();
	if(!handle)
	{
		ACE_DEBUG((LM_ERROR,"����Reactor���ʧ��"));
		return 0;
	}
	handle->set_handle(fd);
	
	if(acceptor_.accept(handle->peer())==-1)
	{
		//free_handle(handle);
		handle->handle_close();
		return 0;
	}
	else 
	{
		handle->scheduler(this->schd_);
		if(handle->open() == -1)
		{
			handle->handle_close();
			return 0;
		}
		else
		{
			ACE_INET_Addr peer_addr;
			handle->peer().get_remote_addr(peer_addr);
			ACE_DEBUG((LM_DEBUG,"�����µ���������[%s]",peer_addr.get_host_addr()));
			int val;
			ACE::record_and_set_non_blocking_mode(handle->peer().get_handle(),val);
			return 0;
		}
	}
}
int KSG_Service_Acceptor::handle_close(ACE_HANDLE handle , ACE_Reactor_Mask close_mask )
{
	acceptor_.close();
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// KSG_Reactor_Scheduler
KSG_Reactor_Scheduler::KSG_Reactor_Scheduler():reactor_(NULL)
{}
KSG_Reactor_Scheduler::~KSG_Reactor_Scheduler()
{}

/*
KSG_Service_Handler * KSG_Reactor_Scheduler::peek_handle()
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,mutex_,NULL);
	if(process_list_.empty())
		return NULL;
	KSG_Service_Handler * result = *(process_list_.begin());
	process_list_.pop_front();
	return result;
}
*/

KSG_Reactor_Scheduler::SERVER_HANDLER * KSG_Reactor_Scheduler::peek_handle()
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,mutex_,NULL);
	if(process_list_.empty())
		return NULL;
	SERVER_HANDLER * result = *(process_list_.begin());
	process_list_.pop_front();
	return result;
}
int KSG_Reactor_Scheduler::push_handle(KSG_Service_Handler *handle,ACE_Message_Block *mblk)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,mutex_,-1);
	/*
	ACE_Message_Block *mblk = NULL;
	if(handle->getq(mblk)==-1)
	{
		ACE_DEBUG((LM_ERROR,"��ȡ�����������ʧ�ܣ�"));
		return -1;
	}
	*/
	if(mblk == NULL)
	{
		ACE_DEBUG((LM_ERROR,"�����������"));
		return -1;
	}
	SERVER_HANDLER *hd = svr_handler_pool_.construct();
	if(!hd)
	{
		ACE_DEBUG((LM_ERROR,"�������Ӷ�����Դʧ�ܣ�"));
		return -1;
	}
	
	hd->handle_ = handle->get_handle();
	hd->mblk_ = mblk;
	hd->request_ = handle->get_request();
	hd->request_time_ = handle->request_time_;
	hd->event_handler_ = handle;
	process_list_.push_back(hd);
	ACE_DEBUG((LM_INFO,"�����������[%d]",process_list_.size()));
	// ������������
	event_.signal();
	return 0;

}
int KSG_Reactor_Scheduler::push_mblk(ACE_Message_Block *mblk)
{
	int ret;
	ACE_Time_Value tv(300);
	ret = work_thr_->putq(mblk,&tv);
	if(ret)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int KSG_Reactor_Scheduler::wait()
{
	int ret;
	ACE_Time_Value tv(2);
	tv += ACE_OS::gettimeofday();
	ret = event_.wait(&tv);
	if(ret == 0)
		return 1;
	if(ret == -1)
		return 0;
	return -1;
}
int KSG_Reactor_Scheduler::svc()
{
	return 0;
}
void KSG_Reactor_Scheduler::work_thr(KSG_Reactor_Work_Thr *r)
{
	work_thr_ = r;
}
int KSG_Reactor_Scheduler::free_handle(SERVER_HANDLER *hd)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,mutex_,-1);
	if(svr_handler_pool_.is_from(hd))
	{
		svr_handler_pool_.destroy(hd);
		ACE_DEBUG((LM_TRACE,"�ͷ�������Դ"));
		return 0;
	}
	return 1;
}

void KSG_Reactor_Scheduler::shutdown(int maxthr)
{
	while(maxthr-->0)
	{
		this->event_.signal();
	}
}
ACE_Reactor* KSG_Reactor_Scheduler::reactor()
{
	return reactor_;
}
int KSG_Reactor_Scheduler::close_error_socket(ACE_HANDLE fd)
{
	KSG_ExceptSock_Handler *h;
	ACE_Time_Value tv(0,100*1000);
	ACE_NEW_RETURN(h,KSG_ExceptSock_Handler(),-1);
	h->set_error_handle(fd);
	return reactor()->notify(h,ACE_Event_Handler::EXCEPT_MASK,&tv);
}
//////////////////////////////////////////////////////////////////////////
int KSG_ExceptSock_Handler::handle_exception(ACE_HANDLE fd )
{
	//ACE_DEBUG((LM_INFO,"close exception socket[%08X]",this->get_error_handle()));

	return -1;
}
int KSG_ExceptSock_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
	ACE_DEBUG((LM_TRACE,"delete exception handler,[%08X]",this->get_error_handle()));
#ifdef WIN32
	ACE_OS::shutdown(this->get_error_handle(),ACE_SHUTDOWN_WRITE);
#endif
	ACE_OS::closesocket(this->get_error_handle());
	delete this;
	return 0;
}
KSG_ExceptSock_Handler::~KSG_ExceptSock_Handler()
{
	ACE_DEBUG((LM_TRACE,"call KSG_ExceptSock_Handler::~KSG_ExceptSock_Handler"));
}
//////////////////////////////////////////////////////////////////////////
// KSG_Reactor_Work_Thr
KSG_Reactor_Work_Thr::KSG_Reactor_Work_Thr(KSG_Reactor_Scheduler *s)
:schd_(s)
{}
KSG_Reactor_Work_Thr::~KSG_Reactor_Work_Thr()
{}
int KSG_Reactor_Work_Thr::svc()
{
	int ret;
#if 0
	KSG_Service_Handler *handle = NULL;
	while(KsgGetGateway()->is_running())
	{
		handle = schd_->peek_handle();
		if(!handle)
		{
			// wait for signal
			ret = schd_->wait();
			if(ret)
			{
				// ������
				continue;
			}
			else
			{
				// ��ʱ, sleep һ��
				KSG_SLEEP(1000);
			}
		}
		else
		{
			ret = do_task(handle);
			if(0 == ret)
			{
				// ����ɹ�, �ֹ��ر�
				handle->handle_close();
			}
			else if(-1 == ret)
			{
				// ����ʧ��
			}
			else if(1 == ret)
			{
				// �ɹ�,������ҪӦ����Է�
				// ��δ������������ݰ�
			}
			KSGThreadUtil::Sleep(10); // 10ms sleep
		}
	}
#else
	KSG_Reactor_Scheduler::SERVER_HANDLER *handle = NULL;
	while(KsgGetGateway()->is_running())
	{
		handle = schd_->peek_handle();
		if(!handle)
		{
			// wait for signal
			ret = schd_->wait();
			if(ret)
			{
				// ������
				continue;
			}
			else
			{
				// ��ʱ, sleep һ��
				KSG_SLEEP(1000);
			}
		}
		else
		{
			ret = do_task2(handle);
			//ret = 0;
			if(0 == ret)
			{
				// ����ɹ�, �ֹ��ر�
				
			}
			else if(-1 == ret)
			{
				// ����ʧ��
			}
			else if(1 == ret)
			{
				// �ɹ�,������ҪӦ����Է�
				// ��δ������������ݰ�
			}
			KSGThreadUtil::Sleep(10); // 10ms sleep
		}
	}
#endif
	return 0;
}

int KSG_Reactor_Work_Thr::do_task(KSG_Service_Handler *handle)
{
	int ret;
	ACE_Time_Value estimated = ACE_OS::gettimeofday() - handle->request_time_;
	long t = estimated.msec();
	if(t > handle->default_timeout())
	{
		// ����ҵ�������ʱ��
		ACE_DEBUG((LM_ERROR,"�Է������Ѿ��ȴ���ʱ...[%d]ms",handle->default_timeout()));
		// ֪ͨ����Դ������
		handle->process_end();
		if(!handle->closed())
			handle->handle_close();
		return -1;
	}
	ret = handle->process_request();
	// ����ҵ�������ʱ��
	handle->process_end();
	return ret;
}

int KSG_Reactor_Work_Thr::do_task2(KSG_Reactor_Scheduler::SERVER_HANDLER *handle)
{
	int ret;
	ACE_Time_Value estimated = ACE_OS::gettimeofday() - handle->request_time_;
	long t = estimated.msec();
	if(t > handle->request_->default_timeout())
	{
		// ����ҵ�������ʱ��
		ACE_DEBUG((LM_ERROR,"�Է������Ѿ��ȴ���ʱ...[%d]ms",handle->request_->default_timeout()));
		// ֪ͨ����Դ������
		ret = -1;
	}
	else
	{
		ret = handle->request_->process_request(handle);
	}
	handle->mblk_->release();
	handle->mblk_ = NULL;
	if(ret == -1)
	{
		// ���������⣬��Ҫ�ر�
		ACE_DEBUG((LM_TRACE,"����Ӧ��ʧ�ܣ��ر�����[%08X]",handle->handle_));
		//ACE_OS::closesocket(handle->handle_);
		//this->schd_->reactor()->remove_handler(handle->handle_,ACE_Event_Handler::ALL_EVENTS_MASK);

		this->schd_->close_error_socket(handle->handle_);
	}
	// �ͷ� handle
	schd_->free_handle(handle);
	
	// ����ҵ�������ʱ��
	return ret;
}