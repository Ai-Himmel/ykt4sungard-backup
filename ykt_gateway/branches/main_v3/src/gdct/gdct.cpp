#include "gdct/gdct.h"
#include "gdct/gdctpub.h"
#include "netutil.h"
#include "ksgateway.h"
#include <ace/SOCK_Connector.h>
#include <ace/Singleton.h>
#include <ace/Handle_Set.h>
#include "pubfunc.h"

DECLARE_NAMESPACE_BEGIN(GDCT)
//////////////////////////////////////////////////////////////////////////
KSG_ADD_LISTENER_CLASS(KSG_GDCT_LISTENER,GDCT_Service_Acceptor);
//////////////////////////////////////////////////////////////////////////
static GDCT_Service_Request *g_gdct_request = NULL;
typedef ACE_Singleton<GDCT_Transfer,ACE_Null_Mutex> GDCT_TRANSFER;
//////////////////////////////////////////////////////////////////////////
int GDCT_Service_Acceptor::start_listen()
{
	// �˿ڴӺ�̨�ж�ȡ1
	std::string value;
	int port = 7000;
	char temp[129] = "";
	GDCT_TRANSFER::instance()->do_get_svr_param("transsvrport",temp);
	port = ACE_OS::atoi(temp);
	if(port == 0)
		port = 7000;
	if(open(ACE_INET_Addr(port)) == -1 )
	{
		ACE_DEBUG((LM_ERROR,"ѶԴ���г�ֵ������������ʧ��\n"));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"ѶԴ���г�ֵ�����߳�ThreadId[%u]�˿�[%d]\n",ACE_OS::thr_self(),port));
	// ����ѶԴ����������ǩ��
	g_gdct_request = new GDCT_Service_Request();
	GDCT_TRANSFER::instance()->activate();
	return 0;
}
int GDCT_Service_Acceptor::stop_listen()
{
	handle_close();
	if(g_gdct_request != NULL)
		delete g_gdct_request;
	return 0;
}
KSG_Service_Handler* GDCT_Service_Acceptor::new_handle()
{
	KSG_Service_Handler * hd = NULL;
	try
	{
		hd = new GDCT_Service_Handler(this->reactor());
	}
	catch (...)
	{
		ACE_DEBUG((LM_EMERGENCY,"���ܴ����µ��������󣡣���"));
	}
	return hd;
}

int GDCT_Service_Acceptor::free_handle(KSG_Service_Handler *handle)
{
	delete handle;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
GDCT_Service_Handler::GDCT_Service_Handler(ACE_Reactor *r):KSG_Service_Handler(r)
{
	this->request_ = g_gdct_request;
}
int GDCT_Service_Handler::recv_data(ACE_Message_Block *&blk)
{
	int ret;
	size_t maxlen,data_len;
	char temp[10]="";
	ACE_Time_Value tv(0);
	if(blk == NULL)
	{
		ACE_NEW_RETURN(blk,ACE_Message_Block(512),-1);
	}
	else
	{

	}
	maxlen = 4;
	ret = KSGNetUtil::recv_buffer(peer().get_handle(),(unsigned char*)blk->wr_ptr(),maxlen,&tv);
	if(ret)
	{
		return -1;
	}
	if(maxlen !=4)
		return -1;
	// ������ͷ
	
	ACE_OS::memcpy(temp,blk->rd_ptr(),4);
	data_len = ACE_OS::atoi(temp);
	// ��ȡ���
	if(data_len > 512)
		return -1;
	maxlen = blk->size()-4;
	ret = KSGNetUtil::recv_buffer(peer().get_handle(),(unsigned char*)blk->wr_ptr()+4,maxlen,&tv);
	if(ret)
	{
		return -1;
	}
	maxlen += 4;
	blk->wr_ptr(maxlen);
	// TODO: �жϰ�����
	if(data_len != blk->length() )
		return -1;
	return 1;
}
int GDCT_Service_Handler::process_request(long timeout)
{
	return -1;
}

//////////////////////////////////////////////////////////////////////////
int GDCT_Service_Request::process_request(void *arg,long timeout )
{
	int ret;
	KSG_WORK_SVR_HANDLER * hd = reinterpret_cast<KSG_WORK_SVR_HANDLER*>(arg);
	if(hd==NULL)
		return -1;
	try
	{
		ret = do_request(hd);
		return ret;
	}
	catch (...)
	{
		ACE_DEBUG((LM_ERROR,"������ҵ������ʧ�ܣ�"));
		return -1;
	}
}

int GDCT_Service_Request::do_request(KSG_WORK_SVR_HANDLER *handle)
{
	char *buffer = handle->mblk_->rd_ptr();
	int buflen = handle->mblk_->length();
	GDCT_Data the_data;
	the_data.handle_ = handle->handle_;
	the_data.msg_ = handle->mblk_->clone();
	ACE_ASSERT(the_data.msg_ != NULL);
	// �������ʧ�ܣ��ͷ���Դ
	if(GDCT_TRANSFER::instance()->push_queue(&the_data)!=0)
	{
		the_data.msg_->release();
		return -1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
GDCT_Transfer::GDCT_Transfer():is_connected_(0)
{
	ACE_OS::strcpy(gdct_msgtype_,"DCCZ");
}
GDCT_Transfer::~GDCT_Transfer()
{
	// empty
}
int GDCT_Transfer::svc()
{
	// 1 ����ѶԴ������
	// 2 ��ѶԴ������ǩ��
	// 3 �˳�ʱǩ��
	do_setup();
	is_connected_ = 0;
	// ������ѭ��
	while(KsgGetGateway()->is_running())
	{
		if(is_connected_!=1)
		{
			if(do_connect_svr()!=0)
			{
				KSG_SLEEP(5000);
				continue;
			}
			if(do_login_svr()!=0)
			{
				// ��½ʧ�ܣ�
				do_disconnect();
				KSG_SLEEP(5000);
				continue;
			}
		}
		ACE_Time_Value now_time = ACE_OS::gettimeofday();
		if(now_time.sec()-this->last_success_time_.sec() > 180)
		{
			// �� 180s û��ͨѶ�ɹ�������һ����������
			do_send_heartbeat();
			continue;
		}
		do_main_service();
	}
	return 0;
}
int GDCT_Transfer::push_queue(GDCT_Data *the_data)
{
	char seqno[11] = "";
	memcpy(seqno,the_data->msg_->rd_ptr()+4,10);
	ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
	MESSAGE_MAP_TYPE::const_iterator i = input_queue_.find(seqno);
	if(i == input_queue_.end())
	{
		input_queue_.insert(MESSAGE_MAP_TYPE::value_type(seqno,*the_data));
		return 0;
	}
	return -1;
}
int GDCT_Transfer::peek_msg(GDCT_Data *the_data)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
	MESSAGE_MAP_TYPE::iterator i = input_queue_.begin();
	if(i != input_queue_.end())
	{
		*the_data = i->second;
		input_queue_.erase(i);
		return 0;
	}
	return 1;
}
int GDCT_Transfer::do_setup()
{
	char temp[129] = "";
	memset(temp,0,sizeof temp);
	do_get_svr_param("svrip",temp);
	svr_ip_ = temp;

	memset(temp,0,sizeof temp);
	do_get_svr_param("svrport",temp);
	svr_port_ = ACE_OS::atoi(temp);

	memset(temp,0,sizeof temp);
	do_get_svr_param("svrpswd",temp);
	ACE_OS::strcpy(gdct_company_pswd_,temp);

	memset(temp,0,sizeof temp);
	do_get_svr_param("companycode",temp);
	ACE_OS::strcpy(gdct_company_code_,temp);

	memset(temp,0,sizeof temp);
	do_get_svr_param("timeout",temp);
	default_timeout_ = ACE_Time_Value(ACE_OS::atoi(temp),0);
	
	return 0;
}
int GDCT_Transfer::do_get_svr_param(const char *param,char *value)
{
	/*
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		return -1;
	}
	obj->SetRequestHeader(850007);
	obj->AddField(F_SNAME,"GDCT");
	obj->AddField(F_SNAME2,param);
	if(obj->Connect())
		return -1;
	if(!obj->SendRequest(5000))
	{
		if(obj->GetReturnCode()!=0)
		{
			ACE_DEBUG((LM_ERROR,"��ȡ�������󣬲���[%s]ret[%d]",param,obj->GetReturnCode()));
			return -1;
		}
	}
	if(obj->HasMoreRecord())
	{
		ST_PACK *data = obj->GetNextRecord();
		ACE_OS::strncpy(value,data->vsvarstr0,128);
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"��ȡ�������󣬲���[%s]",param));
	return -1;
	*/
	std::string v;
	int ret;
	ret = KsgGetUserParam("GDCT",param,v);
	if(!ret)
		ACE_OS::strncpy(value,v.c_str(),128);
	return ret;
}
int GDCT_Transfer::do_connect_svr()
{
	ACE_SOCK_Connector conn;
	ACE_INET_Addr addr(svr_port_,svr_ip_.c_str());
	ACE_Time_Value to = default_timeout_;
	if(conn.connect(connector_,addr,&default_timeout_)!=0)
	{
		int r = ACE_OS::last_error();
		ACE_DEBUG((LM_ERROR,"����ѶԴ������ʧ��[%s:%d]ret[%d:%s]",svr_ip_.c_str(),svr_port_,
			r,ACE_OS::strerror(r)));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"����ѶԴ�������ɹ�[%s:%d]",svr_ip_.c_str(),svr_port_));
	is_connected_ = 1;
	return 0;
}
int GDCT_Transfer::do_disconnect()
{
	if(connector_.get_handle() != ACE_INVALID_HANDLE)
	{
		connector_.close();
		is_connected_ = 0;
		ACE_DEBUG((LM_INFO,"�Ͽ���ѶԴ������������!"));
		return 0;
	}
	return 0;
}
int GDCT_Transfer::do_login_svr()
{
	ACE_ASSERT(is_connected_ == 1);
	gdct_msg_t mymsg,recvmsg;
	ACE_OS::memset(&mymsg,0,sizeof mymsg);
	ACE_OS::memset(&recvmsg,0,sizeof recvmsg);
	ACE_OS::strcpy(mymsg.msgcode,"000001");
	ACE_OS::strcpy(mymsg.msgtype,gdct_msgtype_);
	// ��Ӫ��
	ACE_OS::strcpy(mymsg.body,"00000000");
	mymsg.bodylen=8;
	// ��ҵ����
	ACE_OS::strcpy(mymsg.body+mymsg.bodylen,gdct_company_code_);
	mymsg.bodylen+=8;
	// ��ҵ����
	ACE_OS::strcpy(mymsg.body+mymsg.bodylen,gdct_company_pswd_);
	mymsg.bodylen+=32;
	// Э��汾
	ACE_OS::strcpy(mymsg.body+mymsg.bodylen,"0010");
	mymsg.bodylen+=4;
	if(do_send_and_recv(&mymsg,&recvmsg)!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������[��¼]ʧ��"));
		return -1;
	}
	if(ACE_OS::strncmp(recvmsg.msgcode,"800001",6)!=0)
	{
		ACE_DEBUG((LM_ERROR,"[��¼]���󣬽������ݰ�ʵ������Ϊ[%s]",recvmsg.msgcode));
		return -1;
	}
	if(ACE_OS::strncmp(recvmsg.respcode,"0000",4)!=0)
	{
		ACE_DEBUG((LM_ERROR,"ѶԴ������[��¼]ʧ�ܣ�������[%s]",recvmsg.respcode));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"[��¼]ѶԴ�������ɹ�!"));
	last_success_time_ = ACE_OS::gettimeofday();
	return 0;
}
int GDCT_Transfer::do_logout_svr()
{
	ACE_ASSERT(is_connected_ == 1);
	gdct_msg_t mymsg,recvmsg;
	ACE_OS::memset(&mymsg,0,sizeof mymsg);
	ACE_OS::memset(&recvmsg,0,sizeof recvmsg);
	ACE_OS::strcpy(mymsg.msgcode,"000002");
	ACE_OS::strcpy(mymsg.msgtype,gdct_msgtype_);
	mymsg.bodylen = 0;
	if(do_send_and_recv(&mymsg,&recvmsg)!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������[ע��]ʧ��"));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"ѶԴ������[ע��]�ɹ�!"));
	return 0;
}
int GDCT_Transfer::do_send_heartbeat()
{
	ACE_ASSERT(is_connected_ == 1);
	gdct_msg_t mymsg,recvmsg;
	ACE_OS::memset(&mymsg,0,sizeof mymsg);
	ACE_OS::memset(&recvmsg,0,sizeof recvmsg);
	ACE_OS::strcpy(mymsg.msgcode,"000119");
	ACE_OS::strcpy(mymsg.msgtype,gdct_msgtype_);
	mymsg.bodylen = 0;
	
	if(do_send_and_recv(&mymsg,&recvmsg)!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������[��������]ʧ��"));
		do_disconnect();
		return -1;
	}
	if(ACE_OS::strncmp(recvmsg.msgcode,"800119",6)!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������[��������]ʧ��,���մ������ݰ�"));
		do_disconnect();
		return -1;
	}
	ACE_DEBUG((LM_DEBUG,"ѶԴ������[��������]�ɹ�!"));
	last_success_time_ = ACE_OS::gettimeofday();
	return 0;
}
int GDCT_Transfer::do_send_one_data(GDCT_Data *the_data)
{
	int ret;
	ACE_Time_Value to = default_timeout_;
	unsigned char *buf = (unsigned char*) the_data->msg_->rd_ptr();
	size_t buflen = the_data->msg_->length();
	ret = KSGNetUtil::send_buffer(connector_.get_handle(),buf,buflen,&to);
	if(ret)
	{
		int r = ACE_OS::last_error();
		ACE_DEBUG((LM_ERROR,"�������ݵ�ѶԴ����,error[%d:%s]",r,ACE_OS::strerror(r)));
		the_data->msg_->release();
		REACTOR_SCHEDULER::instance()->close_error_socket(the_data->handle_);
		return -1;
	}
	{
		// ���浽�ȴ����ն���
		char seqno[11] = "";
		memcpy(seqno,the_data->msg_->rd_ptr()+4,10);
		ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
		output_queue_.insert(MESSAGE_MAP_TYPE::value_type(seqno,*the_data));
	}
	return 0;
}
int GDCT_Transfer::do_recv_one_data()
{
	char resp_data[512];
	size_t recv_len;
	gdct_msg_t recv_msg;
	GDCT_Data the_data;
	int ret;
	ACE_Time_Value to = default_timeout_;
	memset(resp_data,0,sizeof resp_data);
	recv_len = 4;
	ret = KSGNetUtil::recv_buffer(connector_.get_handle(),(unsigned char*)resp_data,recv_len,&to);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ�������������ݴ��󣬰�ͷ����"));
		if(ret == TASK_INVALID_CONN)
		{
			do_disconnect();
		}
		return -1;
	}
	ACE_OS::memset(&recv_msg,0,sizeof recv_msg);
	recv_msg.datalen = ACE_OS::atoi(resp_data);
	if(recv_msg.datalen > 512)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ�������������ݴ��󣬰�ͷ���ȴ���[%d]",recv_msg.datalen));
		return -1;
	}
	recv_len = recv_msg.datalen-4;
	to = default_timeout_;
	ret = KSGNetUtil::recv_buffer(connector_.get_handle(),(unsigned char*)resp_data+4,recv_len,&to);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ�������������ݴ��󣬰������"));
		return -1;
	}
	recv_len += 4;
	UnPackCTRequest(&recv_msg,resp_data,recv_len);
	last_success_time_ = ACE_OS::gettimeofday();
	char seqno[11];
	sprintf(seqno,"%010d",recv_msg.seqno);
	MESSAGE_MAP_TYPE::iterator i;
	{
		ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
		i = output_queue_.find(seqno);
		if(i != output_queue_.end())
		{
			the_data = i->second;
			output_queue_.erase(i);
			the_data.msg_->release();
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"����ѶԴӦ��Ϊ�ҵ���Ӧ����seqno[%d],msgcode[%s]",
				recv_msg.seqno,recv_msg.msgcode));
			return -1;
		}
	}

	// ����
	to = default_timeout_;
	ret = KSGNetUtil::send_buffer(the_data.handle_,(unsigned char*)resp_data,recv_len,&to);
	ACE_HEX_DUMP((LM_DEBUG,resp_data,recv_len));
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"ת��ѶԴӦ��ʧ��"));
		return -1;
	}
	
	REACTOR_SCHEDULER::instance()->close_error_socket(the_data.handle_);
	return 0;
}
int GDCT_Transfer::get_output_queue_count()
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
	return output_queue_.size();
}
int GDCT_Transfer::get_input_queue_count()
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,m,msg_mutex_,-1);
	return input_queue_.size();
}
int GDCT_Transfer::do_main_service()
{
	GDCT_Data data;
	int ret,flag;
	ACE_Handle_Set rd_set;
	ACE_Handle_Set wr_set;
	memset(&data,0,sizeof data);
	ACE_Time_Value to(1);
	rd_set.set_bit(connector_.get_handle());
	wr_set.set_bit(connector_.get_handle());
	flag = 0;
	if(get_input_queue_count()>0)
		ret = ACE_OS::select(2,rd_set,wr_set,NULL,to);
	else
		ret = ACE_OS::select(2,rd_set,NULL,NULL,to);
	if(ret > 0)
	{
		// ���Է�������
		if(wr_set.is_set(connector_.get_handle()))
		{
			ret = peek_msg(&data);
			if(ret == 0)
			{
				// ��ȡ������
				// ��������
				ACE_DEBUG((LM_INFO,"ת�����ݰ�"));
				do_send_one_data(&data);
				flag++;
			}
			else if(ret == 1)
			{
				ACE_DEBUG((LM_DEBUG,"���������������"));
			}
			else
			{
				// ����
				ACE_DEBUG((LM_ERROR,"��ȡ��������ʧ��"));
			}
		}
		//  ���Խ�������
		if(rd_set.is_set(connector_.get_handle()))
		{
			ACE_DEBUG((LM_INFO,"�������ݰ�"));
			do_recv_one_data();
			flag++;
		}
		//if(flag == 0)
		//	wait_for_input();
	}
	else if(ret == 0)
	{
		ACE_DEBUG((LM_DEBUG,"������"));
		KSG_SLEEP(100);
	}
	else
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ���Ӵ���"));
		return -1;
	}
	
	return 0;
}
int GDCT_Transfer::do_send_and_recv(gdct_msg_t *sendmsg,gdct_msg_t *mymsg)
{
	char resp_data[512];
	size_t recv_len;
	int offset,ret;
	ACE_Time_Value to = default_timeout_;
	memset(resp_data,0,sizeof resp_data);
	PackCTRequest(sendmsg,resp_data,(int&)recv_len);
	ret = KSGNetUtil::send_buffer(connector_.get_handle(),(unsigned char*)resp_data,recv_len,&to);
	if(ret != 0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������ͨѶ,��������ʧ��!"));
		return -1;
	}
	to = default_timeout_;
	recv_len = 4;
	memset(resp_data,0,sizeof resp_data);
	ret = KSGNetUtil::recv_buffer(connector_.get_handle(),(unsigned char*)resp_data,recv_len,&to);
	if(ret!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������ͨѶ,��������ʧ��!"));
		return -1;
	}
	mymsg->datalen = ACE_OS::atoi(resp_data);
	if(mymsg->datalen > sizeof(resp_data) ||
		mymsg->datalen < 24 )
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������ͨѶ,��������������ݰ�ͷ����!"));
		return -1;
	}
	recv_len = sizeof(resp_data)-4;
	ret = KSGNetUtil::recv_buffer(connector_.get_handle(),(unsigned char*)resp_data+4,recv_len,&to);
	if(ret!=0)
	{
		ACE_DEBUG((LM_ERROR,"��ѶԴ������ͨѶ,��������ʧ�ܣ����ݰ������!"));
		return -1;
	}
	
	offset = 4;
	GetBufferAsInteger(resp_data+offset,10,mymsg->seqno);
	offset += 10;
	GetBufferAsString(resp_data+offset,4,mymsg->msgtype);
	offset += 4;
	GetBufferAsString(resp_data+offset,6,mymsg->msgcode);
	offset += 6;
	GetBufferAsString(resp_data+offset,4,mymsg->respcode);
	offset += 4;
	// ��Ϣ��
	ACE_OS::memcpy(mymsg->body,resp_data+offset,mymsg->datalen-offset);
	mymsg->bodylen = mymsg->datalen-offset;
	return 0;
}
DECLARE_NAMESPACE_END(GDCT);