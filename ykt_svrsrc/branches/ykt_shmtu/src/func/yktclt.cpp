#include "yktclt.h"
#include <string.h>

int KS_YKT_Clt::s_has_init = 0;
int KS_YKT_Clt::s_drtp_count = 0;
char KS_YKT_Clt::s_global_xpack_path[1024] = "cpack.dat";
KS_YKT_Clt::drtp_ip_def_t KS_YKT_Clt::s_drtps[KS_YKT_Clt::MAX_DRTP_COUNT];

bool KS_YKT_Clt::Initialize()
{
	if(KS_YKT_Clt::s_has_init)
		return true;
	if(!BCCCLTInit(MAX_DRTP_COUNT))
		return false;
	else if(!XPackInit(1))
		return false;
	KS_YKT_Clt::s_has_init = 1;
	KS_YKT_Clt::s_drtp_count = 0;
	memset(&s_drtps,0,sizeof s_drtps);
	return true;
}

bool KS_YKT_Clt::Uninitialize()
{
	KS_YKT_Clt::s_has_init = 0;
	return true;
}

int KS_YKT_Clt::find_drtp_by_ip(const char *ip)
{
	int i;
	if(strlen(ip) == 0)
		return -1;
	for(i = 0;i < s_drtp_count;++i)
	{
		if(strcmp(s_drtps[i].drtp_ip_,ip)==0)
		{
			return i;
		}
	}
	return -1;
}

void KS_YKT_Clt::set_xpack_path(const char *path)
{
	strcpy(s_global_xpack_path,path);
}

KS_YKT_Clt::KS_YKT_Clt(const char *ip,int port,int main_func)
:err_code_(0),req_row_(0),resp_row_(0),time_out_(0),main_func_(main_func)
{
	init_drtp(ip,port,main_func);
	if(drtp_idx_ < 0)
	{
		handler_ = NULL;
		err_code_=1001;
		strcpy(err_msg_,"connect drtp error!");
		return;
	}
	memset(err_msg_,0,sizeof err_msg_);

	handler_ = 	NewXpackHandle(s_global_xpack_path);
	if(!handler_)
	{
		err_code_=1002;
		strcpy(err_msg_,"cannot create drtp handle!");
	}
	
}

KS_YKT_Clt::KS_YKT_Clt(const char *xpack_data,const char *ip,int port,int main_func)
:err_code_(0),req_row_(0),resp_row_(0),time_out_(0),main_func_(main_func)
{
	init_drtp(ip,port,main_func);
	if(drtp_idx_ < 0)
	{
		handler_ = NULL;
		err_code_=1001;
		strcpy(err_msg_,"connect drtp error!");
		return;
	}
	
	memset(err_msg_,0,sizeof err_msg_);
	handler_ = 	NewXpackHandle(xpack_data);
	if(!handler_)
	{
		err_code_=1002;
		strcpy(err_msg_,"cannot create drtp handle!");
	}
	
}

int KS_YKT_Clt::init_drtp(const char *ip,int port,int main_func)
{
	drtp_idx_ = find_drtp_by_ip(ip);
	if(drtp_idx_ < 0)
	{
		if(s_drtp_count >= MAX_DRTP_COUNT)
			return -2;
		strcpy(s_drtps[s_drtp_count].drtp_ip_,ip);
		s_drtps[s_drtp_count].drtp_port_ = port;
		s_drtps[s_drtp_count].drtp_no_ = ::AddDrtpNode((char*)ip,port);
		if(s_drtps[s_drtp_count].drtp_no_ < 0)
			return -1;
		drtp_idx_ = s_drtp_count;
		s_drtp_count++;
	}
	return 0;
}

KS_YKT_Clt::~KS_YKT_Clt()
{
	if(handler_)
	{
		DeleteXpackHandle(handler_);
	}
}

KS_YKT_Clt::KS_YKT_Clt(const KS_YKT_Clt &rhs)
{
	if(rhs.handler_)
	{
		if(this->handler_)
		{
			DeleteXpackHandle(this->handler_);
		}
		CopyHandle(this->handler_,rhs.handler_);
		this->err_code_ = rhs.err_code_;
		strcpy(this->err_msg_,rhs.err_msg_);
		this->record_count_ = rhs.record_count_;
		this->resp_row_ = rhs.resp_row_;
		this->req_row_ = rhs.req_row_;
		this->return_code_ = rhs.return_code_;
		this->time_out_ = rhs.time_out_;
		this->main_func_ = rhs.main_func_;
		this->drtp_idx_ = rhs.drtp_idx_;
	}
}

KS_YKT_Clt& KS_YKT_Clt::operator=(const KS_YKT_Clt &rhs)
{
	if(rhs.handler_)
	{
		if(this->handler_)
		{
			DeleteXpackHandle(this->handler_);
		}
		CopyHandle(this->handler_,rhs.handler_);
		this->err_code_ = rhs.err_code_;
		strcpy(this->err_msg_,rhs.err_msg_);
		this->record_count_ = rhs.record_count_;
		this->resp_row_ = rhs.resp_row_;
		this->req_row_ = rhs.req_row_;
		this->return_code_ = rhs.return_code_;
		this->time_out_ = rhs.time_out_;
		this->main_func_ = rhs.main_func_;
		this->drtp_idx_ = rhs.drtp_idx_;
	}
	return *this;
}

bool KS_YKT_Clt::GetDoubleFieldByName(char * FieldName,double * Value)
{
	if(!handler_)
		return false;
	return ::GetDoubleFieldByName(handler_,resp_row_,FieldName,Value);
}

bool KS_YKT_Clt::GetIntFieldByName(char * FieldName,int * Value)
{
	if(!handler_)
		return false;
	return ::GetIntFieldByName(handler_,resp_row_,FieldName,Value);
}

bool KS_YKT_Clt::GetStringFieldByName(char * FieldName,char * Value,int ValueBufferSize)
{
	if(!handler_)
		return false;
	return ::GetStringFieldByName(handler_,resp_row_,FieldName,Value,ValueBufferSize);
}

bool KS_YKT_Clt::SetDoubleFieldByName(char * FieldName,double Value)
{
	if(!handler_)
		return false;
	return ::SetDoubleFieldByName(handler_,resp_row_,FieldName,Value);
}

bool KS_YKT_Clt::SetIntFieldByName(char * FieldName,int Value)
{
	if(!handler_)
		return false;
	return ::SetIntFieldByName(handler_,resp_row_,FieldName,Value);
}

bool KS_YKT_Clt::SetStringFieldByName(char * FieldName,char * Value)
{
	if(!handler_)
		return false;
	return ::SetStringFieldByName(handler_,resp_row_,FieldName,Value);
}

void KS_YKT_Clt::Reset()
{
	req_row_ = 0;
	resp_row_ = -1;
	//err_code_ = 0;
	return_code_ = 0;
	record_count_ = 0;
	time_out_ = 0;
}

bool KS_YKT_Clt::SendRequest(int request,int timeout)
{
	if(!handler_)
	{
		return false;
	}
	Reset();
	time_out_ = timeout;
	if(!::SetRequestType(handler_,request))
		return false;
	else if(::CallRequest(handler_,KS_YKT_Clt::s_drtps[drtp_idx_].drtp_no_,
		0,main_func_,time_out_,&err_code_,err_msg_)== false)
	{
		return false;
	}
	::GetRetCode(handler_,&return_code_);
	if(return_code_)
	{
		GetStringFieldByName("vsmess",err_msg_,sizeof(err_msg_)-1);
		return false;
	}
	return true;
}

bool KS_YKT_Clt::SendNextRequest()
{
	resp_row_ = -1;
	record_count_ = 0;
	return CallNext(handler_,time_out_,&err_code_,err_msg_);
}

bool KS_YKT_Clt::HasMoreRecord()
{
	if(record_count_ <= 0)
	{
		if(!GetRecordCount(handler_,&record_count_))
		{
			return false;
		}
		if(record_count_ <= 0)
			return false;
	}
	if(resp_row_ + 1 < record_count_)
	{
		return true;
	}
	else if(!HaveNextPack(handler_))
	{
		return false;
	}
	else if(!SendNextRequest())
	{
		return false;
	}
	else if(!GetRecordCount(handler_,&record_count_))
	{
		return false;
	}
	else if(resp_row_ + 1< record_count_)
		return true;
	else
		return false;
}

bool KS_YKT_Clt::GetNextPackage()
{
	resp_row_++;
	if(resp_row_ < record_count_)
	{
		return true;
	}
	return false;
}

void KS_YKT_Clt::GetReturnMsg(char *msg) const
{
	strcpy(msg,err_msg_);
}

void KS_YKT_Clt::ResetHandler()
{
	if(handler_)
		::ResetPackHandle(handler_);
}

