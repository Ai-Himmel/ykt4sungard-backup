#include "ksgateway.h"
#include "bcc_server.h"
#include <ace/Guard_T.h>

#define TEST_HANDLER_RETURN(r) do { if(this->handler_ == NULL) return r;} while(0)

KSG_BCC_Svr_Handler::HANDLER_LIST_TYPE KSG_BCC_Svr_Handler::s_handlers_;
ACE_Thread_Mutex KSG_BCC_Svr_Handler::s_handler_mutex_;
char KSG_BCC_Svr_Handler::s_xpack_data_[KSG_BCC_Svr_Handler::s_max_pack_path_len_]; 

int KSG_BCC_Svr_Handler::init(const char *xpack_path)
{
	memset(&s_xpack_data_,0,sizeof s_xpack_data_);
	strcpy(s_xpack_data_,xpack_path);
	return 0;
}

int KSG_BCC_Svr_Handler::uninit()
{
	return 0;
}

KSG_BCC_Svr_Handler* KSG_BCC_Svr_Handler::create_new_handler()
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,s_handler_mutex_,NULL);
	KSG_BCC_Svr_Handler *ret = NULL;
	if(s_handlers_.size() > 0)
	{
		// 先检查缓存区
		ret = s_handlers_.front();
		s_handlers_.pop_front();
	}
	else
	{
		ret = new KSG_BCC_Svr_Handler;
		int svrid = KsgGetGateway()->get_bcc_config()->bcc_svrid;
		if(BindService(ret->get_handler(),svrid)<0)
		{
			ACE_DEBUG((LM_ERROR,"绑定 bcc svrid[%d] 失败",svrid));
			delete ret;
			ret = NULL;
		}
	}
	return ret;
}

int KSG_BCC_Svr_Handler::free_handler(KSG_BCC_Svr_Handler *handler)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,guard,s_handler_mutex_,-1);
	int ret = 0;
	if(s_handlers_.size() > s_max_free_handlers_)
	{
		ret = 1;
		delete handler;
	}
	else
	{
		s_handlers_.push_back(handler);
	}
	return 0;
}



KSG_BCC_Svr_Handler::KSG_BCC_Svr_Handler()
:handler_(XDHANDLE(0)),req_row_num_(0),resp_row_num_(0),req_rows_(0)
{
	//
	handler_ = NewXpackHandle(s_xpack_data_);
	if(!handler_)
	{
		ACE_DEBUG((LM_ERROR,"创建句柄失败!请检查 cpack.dat 文件"));
	}
}
KSG_BCC_Svr_Handler::~KSG_BCC_Svr_Handler()
{
	//
	if(handler_ != NULL)
	{
		DeleteXpackHandle(handler_);
		handler_ = NULL;
	}
}

XDHANDLE KSG_BCC_Svr_Handler::get_handler()
{
	return handler_;
}

int KSG_BCC_Svr_Handler::put_one_row()
{
	int ret;
	TEST_HANDLER_RETURN(-1);
	ret = PutRow(handler_,0);
	if(ret >= 0)
	{
		resp_row_num_++;
	}
	return (ret >= 0) ? 0 : -1;
}

int KSG_BCC_Svr_Handler::finish(int ret)
{
	int res;
	TEST_HANDLER_RETURN(-1);
	res = DataDone(handler_,ret);
	return (res >= 0) ? 0 : -1;
}

int KSG_BCC_Svr_Handler::SetStringField(const char *field,const char *value,int val_len)
{
	TEST_HANDLER_RETURN(-1);
	if(val_len==0)
		return (SetStringFieldByName(handler_,field,value) ? 0 : -1);
	else
	{
		// TODO : 根据长度设置
		return (SetStringFieldByName(handler_,field,value) ? 0 : -1);
	}
}

int KSG_BCC_Svr_Handler::SetIntField(const char *field,long value)
{
	TEST_HANDLER_RETURN(-1);
	return (SetIntFieldByName(handler_,field,value) ? 0 : -1);
}

int KSG_BCC_Svr_Handler::SetDoubleField(const char *field,double value)
{
	TEST_HANDLER_RETURN(-1);
	return (SetDoubleFieldByName(handler_,field,value) ? 0 : -1);
}

int KSG_BCC_Svr_Handler::get_req_row_count()
{
	TEST_HANDLER_RETURN(-1);
	if(req_rows_== 0)
	{
		req_rows_ = GetRecordCount(handler_);
	}
	return req_rows_;
}

int KSG_BCC_Svr_Handler::has_more_req_rows()
{
	return (req_row_num_ < get_req_row_count()) ? 1 : 0;
}

int KSG_BCC_Svr_Handler::get_next_req()
{
	if(req_row_num_ < get_req_row_count())
	{
		req_row_num_++;
	}
	return 0;
}
int KSG_BCC_Svr_Handler::GetIntField(const char *field,long *value)
{
	TEST_HANDLER_RETURN(-1);
	return (GetIntFieldByName(handler_,req_row_num_,field,value) ? 0 : -1);
}

int KSG_BCC_Svr_Handler::GetStrigField(const char *field,char *value,int max_size)
{
	TEST_HANDLER_RETURN(-1);
	return (GetStringFieldByName(handler_,req_row_num_,field,value,max_size) ? 0 : -1);
}

int KSG_BCC_Svr_Handler::GetDoubleField(const char *field,double *value)
{
	TEST_HANDLER_RETURN(-1);
	return (GetDoubleFieldByName(handler_,req_row_num_,field,value) ? 0 : -1);
}

int KSG_BCC_Svr_Handler::get_req_msg_id()
{
	TEST_HANDLER_RETURN(-1);
	return GetMsgID(handler_);
}

int KSG_BCC_Svr_Handler::get_request_type()
{
	TEST_HANDLER_RETURN(-1);
	return GetRequestType(handler_);
}
