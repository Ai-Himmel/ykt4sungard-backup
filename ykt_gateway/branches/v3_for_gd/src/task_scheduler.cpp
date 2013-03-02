/** 
 * ģ����
 * �ļ��� task_scheduler.cpp
 * �ļ�ʵ�ֹ���
 * ���� 
 * �汾
 * ���� 2007-02-28
 * ��ע
 * $Id$
 */
#include "task_scheduler.h"
#include "ksgateway.h"
#include "executor.h"
#include "deviceinterface.h"
#include "taskcode.h"
#include "bcc_server.h"
#include <algorithm>

/////////////////////////////////////////////////////////////////
//  KSG_Task_Queue
KSG_Task_Queue::KSG_Task_Queue()
:_previous(NULL),_next(NULL)
{
}
KSG_Task_Queue::~KSG_Task_Queue()
{
	// empty
	_list_of_tasks.clear();
	_list_of_preempt_tasks.clear();
}

int KSG_Task_Queue::push_task(task_type task)
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,-1));
	_list_of_tasks.push_back(task);
	return 0;
}

int KSG_Task_Queue::insert_task(task_type task)
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,-1));
	_list_of_tasks.push_front(task);
	return 0;
}

KSG_Task_Queue::task_type KSG_Task_Queue::peek_task()
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,KSG_Task_Queue::task_type()));
	if(_list_of_tasks.size() == 0)
		return KSG_Task_Queue::task_type();
	KSG_Task_Queue::task_type task = _list_of_tasks.front();
	_list_of_tasks.pop_front();
	return task;
}

int KSG_Task_Queue::push_preemptive_task(task_type task)
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,-1));
	_list_of_preempt_tasks.push_back(task);
	return 0;
}

KSG_Task_Queue::task_type KSG_Task_Queue::peek_preemptive_task()
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,KSG_Task_Queue::task_type()));
	if(_list_of_preempt_tasks.size() == 0)
		return KSG_Task_Queue::task_type();
	KSG_Task_Queue::task_type task = _list_of_preempt_tasks.front();
	_list_of_preempt_tasks.pop_front();
	return task;
}

size_t KSG_Task_Queue::count_of_tasks()
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,0));
	return _list_of_tasks.size();
}

size_t KSG_Task_Queue::count_of_preemptive_tasks()
{
	ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_task_list_mutex,0));
	return _list_of_preempt_tasks.size();
}

KSG_Task_Queue* KSG_Task_Queue::previous(KSG_Task_Queue *p)
{
	KSG_Task_Queue *old = _previous;
	if(p)
	{
		_previous = p;
		p->_next = this;
	}
	return old;
}


KSG_Task_Queue* KSG_Task_Queue::next(KSG_Task_Queue *n)
{
	KSG_Task_Queue *old = _next;
	if(n)
	{
		_next = n;
		n->_previous = this;
	}
	return old;
}

void KSG_Task_Queue::reset()
{
	_previous = NULL;
	_next = NULL;
}

int KSG_Task_Queue::load_all_device(KSGDeviceNode *parent,int level /* = 0*/)
{
	if(!parent)
		return 0;
	if(parent->owner_queue())
	{
		ACE_DEBUG((LM_ERROR,"����,�豸�Ѿ�������!!!dev[%d]",parent->GetDevId()));
		return -1;
	}
	parent->owner_queue(this);
	if(level == 0)
	{
		std::stringstream queue_name;
		queue_name<<parent->get_name().c_str()<<"_"<<parent->GetDevId()<<std::ends;
		this->queue_name(queue_name.str());
		ACE_DEBUG((LM_DEBUG,"�ɹ������豸,dev[%d],queue[%s]",
			parent->GetDevId(),this->queue_name().c_str()));
	}
	KSGDeviceNode *c = parent->GetFirstChild();
	while(c)
	{
		load_all_device(c,++level);
		c = c->GetNextSibling();
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// KSG_Task_Queue_Pool 
int KSG_Task_Queue_Pool::Queue_List_Cond::wait(ACE_Time_Value *time_out)
{
	return _mutex.acquire(time_out);
}
int KSG_Task_Queue_Pool::Queue_List_Cond::broadcast()
{
	return _mutex.release();
}

int KSG_Task_Queue_Pool::Queue_List_Cond::signal()
{
	return _mutex.release(1);
}
KSG_Task_Queue_Pool::Queue_List_Cond::~Queue_List_Cond()
{
	//
	_mutex.release();
}
void KSG_Task_Queue_Pool::Queue_List_Cond::sleep_hook(void *arg)
{
	ACE_UNUSED_ARG(arg);
	// empty
}

KSG_Task_Queue_Pool::KSG_Task_Queue_Pool()
{
	//
}

KSG_Task_Queue_Pool::~KSG_Task_Queue_Pool()
{
	//
	free_all_queue();
}

KSG_Task_Queue* KSG_Task_Queue_Pool::add_initial_queue(const std::string &key)
{
	if(key.empty())
		return NULL;
	ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_mutex,NULL);
	key_queue_map_type::iterator i = _key_queue_list.find(key);
	queue_list_type *list = NULL;
	if(i != _key_queue_list.end())
	{
		list = i->second;
	}
	else
	{
		list = new queue_list_type;
		_key_queue_list.insert(key_queue_map_type::value_type(key,list));
		Queue_List_Cond *cond = new Queue_List_Cond;
		_queue_cond.insert(queue_cond_map_type::value_type(key,cond));
	}
	ACE_ASSERT(list != NULL);
	KSG_Task_Queue *queue = _queue_pool.construct();
	if(queue)
	{
		queue->key_name(key);
		list->push_back(queue);
	}
	return queue;
}

int KSG_Task_Queue_Pool::remove_queue(const std::string &key,KSG_Task_Queue *queue)
{
	if(!queue || key.empty())
		return -1;
	ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_mutex,-1);
	key_queue_map_type::iterator i = _key_queue_list.find(key);
	if(i != _key_queue_list.end())
	{
		queue_list_type *list = i->second;
		if(list)
		{
			queue_list_type::iterator q;
			for(q = list->begin();q != list->end(); ++q)
			{
				if(*q == queue)
				{
					if(_queue_pool.is_from(queue))
					{
						list->erase(q);
						_queue_pool.free(queue);
						return 1;
					}
					return 0;
				}
			}
		}
		return 0;
	}
	return 0;
}

int KSG_Task_Queue_Pool::is_contain_key(const std::string &key) const
{
	key_queue_map_type::const_iterator i = _key_queue_list.find(key);
	return (i != _key_queue_list.end()) ? 1 : 0;
}

KSG_Task_Queue_Pool::queue_list_type* KSG_Task_Queue_Pool::find_queue_list(const std::string &key) const
{
	key_queue_map_type::const_iterator i = _key_queue_list.find(key);
	if( i != _key_queue_list.end() )
	{
		return i->second;
	}
	return NULL;
}

int KSG_Task_Queue_Pool::wait_for_queue(const std::string &key,long time_out)
{
	queue_cond_map_type::const_iterator i = _queue_cond.find(key);
	if(i == _queue_cond.end())
	{
		ACE_DEBUG((LM_ERROR,"û�ж�Ӧ�Ķ���[%s]",key.c_str()));
		return -1;
	}
	Queue_List_Cond *cond = i->second;
	ACE_DEBUG((LM_TRACE,"�ȴ�������[%s]...",key.c_str()));
	int ret;
	if(time_out > 0)
	{
		ACE_Time_Value tv = ACE_Time_Value(time_out/1000,time_out%1000);
		tv += ACE_OS::gettimeofday();
		ret = cond->wait(&tv);
		// maybe timeout 
		if( ret == -1 && ACE_OS::last_error() == ETIME )
			ret = 1;
	}
	else
		ret = cond->wait(NULL);
	return ret;
}

int KSG_Task_Queue_Pool::singal_queue(const std::string &key,KSG_Task_Queue *queue)
{	
	queue_cond_map_type::const_iterator i = _queue_cond.find(key);
	if(i == _queue_cond.end())
	{
		ACE_DEBUG((LM_ERROR,"û�ж�Ӧ�Ķ���[%s]",key.c_str()));
		return -1;
	}
	
	ACE_DEBUG((LM_TRACE,"���Ѷ�����[%s]...",key.c_str()));
	Queue_List_Cond *cond = i->second;
	return cond->signal();
}

void KSG_Task_Queue_Pool::free_all_queue()
{
	key_queue_map_type::const_iterator i;
	for(i = _key_queue_list.begin();i != _key_queue_list.end();++i)
	{
		std::string key = i->first;
		queue_cond_map_type::const_iterator cond_iter = _queue_cond.find(key);
		Queue_List_Cond *cond = cond_iter->second;
		cond->broadcast();
		delete cond;
		queue_list_type *list = i->second;
		std::for_each(list->begin(),list->end(),
			boost::bind(&KSG_Task_Queue_Pool::free_queue_list,this,_1));
	}
}

void KSG_Task_Queue_Pool::free_queue_list(KSG_Task_Queue *queue)
{
	if(_queue_pool.is_from(queue))
		_queue_pool.destroy(queue);
}

///////////////////////////////////////////////////////////////////////////
// KSG_Task_Schd_Token_Guard
KSG_Task_Schd_Token_Guard::KSG_Task_Schd_Token_Guard(ACE_Token &token)
:_token(token),_owner(0)
{

}

KSG_Task_Schd_Token_Guard::~KSG_Task_Schd_Token_Guard()
{
	if(this->_owner == 1)
	{
		ACE_MT(this->_token.release());
		this->_owner = 0;
	}
}

int KSG_Task_Schd_Token_Guard::acquire_token(ACE_Time_Value *time_out)
{
	int ret;
	if(time_out)
	{
		ACE_Time_Value tv = ACE_OS::gettimeofday();
		tv += *time_out;
		ret = this->_token.acquire(&tv);
	}
	else
	{
		ret = this->_token.acquire();
	}
	if(ret == -1)
	{
		if(errno == ETIME)
			return 0;
		return -1;
	}
	this->_owner = 1;
	return ret;
}

int KSG_Task_Schd_Token_Guard::release_token()
{
	if(this->_owner)
	{
		this->_token.release();
		this->_owner = 0;
	}
	return 0;
}

int KSG_Task_Schd_Token_Guard::is_owner() const
{
	return this->_owner;
}
///////////////////////////////////////////////////////////////////////////
// KSG_Task_Scheduler 
KSG_Task_Scheduler::KSG_Task_Scheduler(KSG_Task_Scheduler_Implementation *impl)
	:_implement(NULL)
{
	if(impl)
	{
		_implement = impl;
	}
	else
	{
		_implement = new KSG_Queue_Task_Scheduler_Impl;
	}
}

KSG_Task_Scheduler::~KSG_Task_Scheduler()
{
	if(_implement)
	{
		// terminate 
	}
}

int KSG_Task_Scheduler::process_loop_done()
{
	return _implement->process_loop_done();
}

int KSG_Task_Scheduler::process_task(long time_out)
{
	KSG_Task_Queue *queue = NULL;
	int ret;

L_AGAIN:
	{
		//ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex,mon,_process_mutex,-1);
		KSG_Task_Schd_Token_Guard guard(_process_mutex);
		ret = guard.acquire_token(NULL);

		if(!guard.is_owner())
			return ret;

		// ���û�ж��У���ǰ�߳̽�������״̬
		queue = _implement->peek_queue(time_out);		
	}
	
	// �жϵĹ����в���Ҫ����
	if(!queue)
	{
		// waiting for sleeping queue to be wake up
		ACE_DEBUG((LM_TRACE,"�����̵߳ȴ�������"));
		ret = _implement->wait_for_wake_up(time_out);
		if(ret>0)
		{
			ACE_DEBUG((LM_TRACE,"�ȴ���ʱ..."));
			return 1;
		}
		else if(ret == 0)
		{
			ACE_DEBUG((LM_TRACE,"�����߳��ҵ�ִ��ָ�������"));
			goto L_AGAIN;
		}
		else
			return -1;
	}
	ACE_DEBUG((LM_DEBUG,"queue-��ʼ�����������,queue[%s]",queue->queue_name().c_str()));
	// ִ������
	ret = execute_task(queue);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�������queue[%s],���ش���[%d]",queue->queue_name(),ret));
	}

L_FINISH:
	if(queue)
	{
		ACE_DEBUG((LM_DEBUG,"queue-�����������,queue[%s]",queue->queue_name().c_str()));
		KSG_Task_Schd_Token_Guard guard(_process_mutex);
		ret = guard.acquire_token(NULL);
		if(!guard.is_owner())
		{
			ACE_DEBUG((LM_ERROR,"�ȴ��黹����ʧ�ܣ�"));
			goto L_FINISH;
		}
		ret = _implement->push_queue(queue);
		if(ret)
			ACE_DEBUG((LM_NOTICE,"���������ɣ����ն���ʧ�ܣ�����"));
		//ACE_DEBUG((LM_INFO,"ִ����ɣ�������������[%d]",queue->count_of_tasks()));
	}
	return 1;
}

int KSG_Task_Scheduler::execute_task(KSG_Task_Queue *queue)
{
	std::string retmsg;
	int ret;
	int exec_time = 0;
	// ����ָ��
	task_type task;
	void *arg;
	if(queue->count_of_preemptive_tasks() > 0)
	{
		// �ȴ�����ռʽ����
		task = queue->peek_preemptive_task();
	}
	else
	{
		task = queue->peek_task();
	}
	if(!task)
	{
		ACE_DEBUG((LM_ERROR,"������ȷ!"));
		return -1;
	}
	KSGDeviceNode* node = task->GetDeviceNode();
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"ָ��[%d]û��ִ���豸",task->GetTaskId()));
		return -1;
	}
	arg = task->private_data();
	// ����ִ����
	KSGTaskExecutor* exec = NULL;
	try
	{
		exec = KSGTaskExecutorFactory::instance()->Create(
			task->GetTaskCode());
	}
	catch(...)
	{
		//
		ACE_DEBUG((LM_TRACE,"����ָ��ִ����ʧ��task[%d]",task->GetTaskCode()));
	}
	if(exec)
	{
		if(exec->PreExecuteTask(arg,task.get()))
		{
			ACE_DEBUG((LM_ERROR,"��ʼ��ָ�����,taskid[%d],taskcode[%d]"
				,task->GetTaskId(),task->GetTaskCode()));
		}
	}
	//ACE_DEBUG((LM_INFO,"���л���[%d]������",queue->count_of_tasks()));
	// ִ��ָ��
	//ACE_DEBUG((LM_INFO,"taskid[%d]���л���[%d]������",task->GetTaskId(),queue->count_of_tasks()));
	task->GetParams();
	task->SetNeedResponse();
	ret = do_try_task(task.get());
	switch(ret)
	{
	case -1:
		retmsg = "δʵ���豸�ӿ�";
		break;
	case TASK_SUCCESS:
		// ִ��ָ��ɹ�
		retmsg = "�ɹ�";
		break;
	case TASK_ERR_NOT_SUPPORT: 
		retmsg = "�豸��֧��ָ��";
		ret = TASK_SUCCESS;
		break;
	case TASK_ERR_TIMEOUT:
		// ִ�г�ʱ
		retmsg = "ִ�г�ʱ";
		break;
	case TASK_ERR_EXECUTE:
		retmsg = "ִ��ʧ��";
		break;
	case TASK_ERR_PARAM:
		retmsg = "��������";
		break;
	case TASK_ERR_CONNECT:
		// �����豸ʧ��
		retmsg = "�����豸ʧ��";
		// ����������½����б�־Ϊ blocking 
		queue->status(KSG_Task_Queue::tq_blocking);
		break;
	default:
		// ָ��ִ��ʧ��
		// ������ָ��
		break;
	}
	if(ret == TASK_SUCCESS && exec)
	{
		if(exec->PostExecuteTask(arg,task.get()))
		{
			ACE_DEBUG((LM_ERROR,"��������ָ�����,taskid[%d],taskcode[%d]"
				,task->GetTaskId(),task->GetTaskCode()));
		}
	}
	if(task->task_modal() == tt_push)
	{
		//��������
		KSG_BCC_Svr_Handler *req = static_cast<KSG_BCC_Svr_Handler*>(arg);
		if(req)
		{
			if(ret != TASK_SUCCESS)
			{
				req->SetStringField("vsmess",retmsg.c_str());
				req->put_one_row();
			}
			req->finish(ret);
		}
	}
	else
	{
		if(task->NeedResponse())
		{
			// ���µ���̨
			exec_time = 0;
L_ANSWER_AGAIN:
			try
			{
				DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
				if(!obj)
				{
					if(exec_time++<3)
						goto L_ANSWER_AGAIN;
					return -1;
				}
				obj->SetRequestHeader(KsgGetGateway()->GetConfig()->_taskResponseFuncNo);
				obj->AddField(F_LVOL1,task->GetTaskId());
				obj->AddField(F_LVOL4,ret);
				std::string addition_msg("");
				task->GetResponse().GetFieldValue(KEY_TASK_ERR_MSG,addition_msg);
				retmsg += addition_msg;
				obj->AddField(F_VSMESS,retmsg.c_str());
				try
				{
					if(exec && ret == TASK_SUCCESS)
					{
						if(exec->ExecuteTask(obj.operator ->(),task.operator->()))
						{
							ACE_DEBUG((LM_ERROR,"ָ��ִ����ִ��ʧ��!"));
						}
					}
				}
				catch(...)
				{
					//
				}
				int exec_timeout = KsgGetGateway()->GetConfig()->_execTimeout;
				exec_time = 0;
				ret = -1;
				while(exec_time++<3)
				{
					if(obj->Connect() || obj->SendRequest(exec_timeout)
						|| obj->GetReturnCode())
						ACE_DEBUG((LM_ERROR,"ָ��Ӧ��ʧ��...taskid[%d]ret[%d]"
						,task->GetTaskId(),obj->GetReturnCode()));
					else
					{
						ACE_DEBUG((LM_TRACE,"ָ��Ӧ��ɹ�taskid[%d]",task->GetTaskId()));
						ret = 0;
						break;
					}
				}
				
			}
			catch (...)
			{
				ACE_DEBUG((LM_ERROR,"Ӧ��ָ�����쳣"));
			}

		}
	}
	ACE_DEBUG((LM_TRACE,"ָ�����ִ��ָ�����,taskid[%d]taskcode[%d]"
		,task->GetTaskId(),task->GetTaskCode()));
	return 0;
}

int KSG_Task_Scheduler::do_try_task(TaskPointer task)
{
	int ret;
	KSGDeviceNode* node = task->GetDeviceNode();
	int exec_time = 0;
	while(exec_time++ < task->exec_times())
	{
		ret = TASK_ERR_COMMON;
		try
		{
			ACE_DEBUG((LM_TRACE,"��ʼִ��ָ��id[%d]task[%d]",
				task->GetTaskId(),task->GetTaskCode()));
			ret = node->ExecuteTask(task);
			
			if(ret)
				ACE_DEBUG((LM_ERROR,"ִ��ָ��ʧ��[%d]task[%d]dev[%d]ret[%d]",
				task->GetTaskId(),task->GetTaskCode(),node->GetDevId(),ret));
			else
				ACE_DEBUG((LM_TRACE,"ִ��ָ��ɹ�[%d]task[%d]dev[%d]"
				,task->GetTaskId(),task->GetTaskCode(),node->GetDevId()));
			switch(ret)
			{
			// ����ɹ�,���߲�֧�ַ���
			case TASK_SUCCESS:
			case TASK_ERR_NOT_SUPPORT:
			case -1:
				return ret;
			default:
				break;
			}
		}
		catch(...)
		{
			// ָ���ʽ����ȷ
		}
	}
	return ret;
}
int KSG_Task_Scheduler::end_process_loop()
{
	return _implement->end_process_loop();
}

int KSG_Task_Scheduler::open(const std::string &key)
{
	return _implement->open(key);
}

int KSG_Task_Scheduler::wait_semaphore()
{
	return _start_sem.acquire();
}

int KSG_Task_Scheduler::release_semaphore()
{
	return _start_sem.release(1);
}

int KSG_Task_Scheduler::notify_new_task()
{
	return _implement->notify_new_task();
}
////////////////////////////////////////////////////////////////////////////
// KSG_Queue_Task_Scheduler_Impl

KSG_REGISTER_SCHD_IMPL_CLASS(KSG_SCHEDULER_STATUS,KSG_Queue_Task_Scheduler_Impl);

KSG_Queue_Task_Scheduler_Impl::KSG_Queue_Task_Scheduler_Impl()
	:KSG_Task_Scheduler_Implementation(), _head_of_running(NULL)
	,_head_of_waiting(NULL),_head_of_sleeping(NULL),_head_of_blocking(NULL)
	,_is_end_loop(0)
{
	// empty
}
KSG_Queue_Task_Scheduler_Impl::~KSG_Queue_Task_Scheduler_Impl()
{
	// empty
	free_queue_head(_head_of_running);
	free_queue_head(_head_of_sleeping);
	free_queue_head(_head_of_waiting);
	free_queue_head(_head_of_blocking);
}

void KSG_Queue_Task_Scheduler_Impl::free_queue_head(Queue_Head *head)
{
	Task_Queue_Pool::instance()->remove_queue(_queue_key,head->_head);
	delete head;
}

int KSG_Queue_Task_Scheduler_Impl::open(const std::string &key)
{
	KSG_Task_Queue_Pool::queue_list_type *list;
	if(Task_Queue_Pool::instance()->is_contain_key(key))
		list = Task_Queue_Pool::instance()->find_queue_list(key);
	else
	{
		ACE_ERROR_RETURN((LM_INFO,"û���ҵ���Ҫ���ȵ��豸����[%s]",key.c_str()),-1);
	}

	// �����ĸ����е�ͷ���
	initial_new_queue(key,&_head_of_sleeping);
	initial_new_queue(key,&_head_of_waiting);
	initial_new_queue(key,&_head_of_running);
	initial_new_queue(key,&_head_of_blocking);
	KSG_Task_Queue_Pool::queue_list_type::iterator i;
	KSG_Task_Queue *element = _head_of_sleeping->_head;
	
	// ����һ����������
	for( i = list->begin(); i != list->end(); ++i)
	{
		KSG_Task_Queue *curr = *i;
		if(curr == _head_of_sleeping->_head
			|| curr == _head_of_waiting->_head
			|| curr == _head_of_running->_head
			|| curr == _head_of_blocking->_head)
			continue;
		element->next(curr);
		element = curr;
	}
	_head_of_sleeping->_head->previous(element);
	_queue_key = key;
	return 0;
}

void KSG_Queue_Task_Scheduler_Impl::initial_new_queue(const std::string &key,Queue_Head **queue)
{
	if(*queue != NULL)
	{
		Task_Queue_Pool::instance()->remove_queue(key,(*queue)->_head);
		delete *queue;
		*queue = NULL;
	}
	Queue_Head *q = new Queue_Head;
	if(q)
	{
		q->_head = Task_Queue_Pool::instance()->add_initial_queue(key);
		*queue = q;
		// ��ɿ�����
		q->_head->next(q->_head);
	}
}

static void do_dump_task_queue(KSG_Task_Queue * head,const char *queue_name)
{
	KSG_Task_Queue *queue;
	int count;
	for (count=0,queue=head->next();queue!=head;queue=queue->next(),count++)
	;
	ACE_DEBUG((LM_TRACE,"queue[%s] count[%d]",queue_name,count));
	
}
KSG_Task_Queue* KSG_Queue_Task_Scheduler_Impl::peek_queue(long time_out)
{
	KSG_Task_Queue *queue;
	// �� running �в��Ҷ���
	// TODO must be test

	//ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_head_of_running->_mutex,NULL);
	if(_head_of_running->_head->next() != _head_of_running->_head)
	{
		queue = _head_of_running->_head->next();
		if(remove_queue(_head_of_running,queue) == NULL)
			ACE_DEBUG((LM_ERROR,"��������ȡ������ʧ��"));
		return queue;
	}
	// ������
	{
		//ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon2,_head_of_waiting->_mutex,NULL));
		//if(_head_of_waiting->_head->next() == _head_of_waiting->_head)
		//	return NULL;

		//ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon1,_head_of_running->_mutex,NULL));
		// ���� running & waiting 
		std::swap(_head_of_running,_head_of_waiting);
	}
	// �� waiting �в��Ҷ���
	if(_head_of_running->_head->next() != _head_of_running->_head)
	{
		queue = _head_of_running->_head->next();
		if(remove_queue(_head_of_running,queue) == NULL)
			ACE_DEBUG((LM_ERROR,"��������ȡ������ʧ��"));
		return queue;
	}

	// ���� sleeping �����е�����
	notify_new_task();
	//do_dump_task_queue(_head_of_running->_head,"running");
	//do_dump_task_queue(_head_of_sleeping->_head,"sleeping");

	return NULL;
}

int KSG_Queue_Task_Scheduler_Impl::wait_for_wake_up(long time_out)
{
	int ret = Task_Queue_Pool::instance()->wait_for_queue(_queue_key,time_out);
	if(ret)
		return ret;
	ACE_DEBUG((LM_TRACE,"����������ȳɹ�..."));
	// modify by tc 
	// ����������������̰߳�ȫ�ģ���˲������������
	//notify_new_task();
	return 0;
}

KSG_Task_Queue* KSG_Queue_Task_Scheduler_Impl::remove_queue(Queue_Head *head,KSG_Task_Queue *queue)
{
	KSG_Task_Queue *pre;
	pre = queue->previous();
	pre->next(queue->next());
	queue->reset();
	return pre;
}

KSG_Task_Queue* KSG_Queue_Task_Scheduler_Impl::push_back_queue(Queue_Head *head,KSG_Task_Queue *queue)
{
	KSG_Task_Queue *tail;
	tail = head->_head->previous();
	tail->next(queue);
	queue->next(head->_head);
	return queue->next();
}

KSG_Task_Queue * KSG_Queue_Task_Scheduler_Impl::insert_front_queue(
	Queue_Head *head,KSG_Task_Queue *queue)
{
	KSG_Task_Queue *first_queue = head->_head->next();
	head->_head->next(queue);
	queue->next(first_queue);
	return queue->next();
}
int KSG_Queue_Task_Scheduler_Impl::push_queue(KSG_Task_Queue *queue)
{
	Queue_Head *q;
	int restart_schd = 0;
	// ��¼�� blocking ����
	if(queue->status() == KSG_Task_Queue::tq_blocking)
	{
		// the blocking queue must be test 
		// TODO : ��� blocking �����е��豸
		//q = _head_of_blocking;
		q = _head_of_sleeping;
	}
	else if(queue->count_of_preemptive_tasks()>0)
	{
		ACE_DEBUG((LM_DEBUG,"��������ռʽ����count[%d]",queue->count_of_preemptive_tasks()));
		q = _head_of_running;
		restart_schd = 1;
	}
	else if(queue->count_of_tasks() > 0)
	{
		// ��¼�� waiting ����
		// now , there are some tasks left in the queue , so we put it into the waiting queue list
		ACE_DEBUG((LM_DEBUG,"���н���ȴ�count[%d]",queue->count_of_tasks()));
		q = _head_of_waiting;
		restart_schd = 1;
	}
	else
	{
		// ��¼�� sleeping ����
		// here , we should monitor the sleeping queue.
		ACE_DEBUG((LM_DEBUG,"����������"));
		q = _head_of_sleeping;
	}
	{
		//ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,q->_mutex,-1));
		push_back_queue(q,queue);
	}
	if(restart_schd)
	{
		// �������񣬻���
		//notify_new_task();
		Task_Queue_Pool::instance()->singal_queue(_queue_key,queue);
		ACE_DEBUG((LM_TRACE,"�����̻߳��Ѷ���......"));
	}
	return 0;
}

int KSG_Queue_Task_Scheduler_Impl::process_loop_done()
{
	return _is_end_loop != 0;
}

int KSG_Queue_Task_Scheduler_Impl::end_process_loop()
{
	_is_end_loop = 1;
	return 0;
}

int KSG_Queue_Task_Scheduler_Impl::notify_new_task()
{
	int count;
	// reload sleeping queue
	{
		// 
		//ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_head_of_waiting->_mutex,-1));
		//ACE_MT(ACE_GUARD_RETURN(ACE_Thread_Mutex,mon1,_head_of_sleeping->_mutex,-1));
		KSG_Task_Queue *queue,*pre;
		count = 0;
		for(queue = _head_of_sleeping->_head->next();
			queue != _head_of_sleeping->_head;)
		{
			if(queue->count_of_tasks() > 0 || queue->count_of_preemptive_tasks()>0)
			{
				pre = remove_queue(_head_of_sleeping,queue);
				//ACE_DEBUG((LM_DEBUG,"push queue to waiting queue!"));
				push_back_queue(_head_of_waiting,queue);
				count++;
			}
			else
				pre = queue;
			// Ӧ�ò�������������
			if(!pre)
			{
				ACE_DEBUG((LM_ERROR,"��������д���"));
				goto L_END; 
			}
			queue = pre->next();
		}
	}
L_END:
	if(count > 0)
		return 0;
	return -1;
}

