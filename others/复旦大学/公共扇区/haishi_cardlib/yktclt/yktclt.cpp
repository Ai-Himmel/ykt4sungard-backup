#include "yktclt.h"
#include <string.h>

int KS_YKT_Clt::drtp_no_ = -1;
int KS_YKT_Clt::main_func_ = 0;

bool KS_YKT_Clt::Initialize(const char *ip,int port,int main_func)
{
	if(KS_YKT_Clt::drtp_no_ >= 0)
		return true;
	KS_YKT_Clt::main_func_ = main_func;
	if(!BCCCLTInit(1))
		return false;
	else if((KS_YKT_Clt::drtp_no_=AddDrtpNode((char*)ip,port)) < 0)
		return false;
	else if(!XPackInit(1))
		return false;
	return true;
}

bool KS_YKT_Clt::Uninitialize()
{
	KS_YKT_Clt::drtp_no_ = -1;
	KS_YKT_Clt::main_func_ = 0;
	return true;
}

KS_YKT_Clt::KS_YKT_Clt():err_code_(0),req_row_(0),resp_row_(0),time_out_(0)
{
	handler_ = 	NewXpackHandle("cpack.dat");
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
	resp_row_ = 0;
	err_code_ = 0;
	return_code_ = 0;
	record_count_ = 0;
	time_out_ = 0;
}

bool KS_YKT_Clt::SendRequest(int request,int timeout)
{
	if(!handler_)
		return false;
	Reset();
	time_out_ = timeout;
	if(!SetRequestType(handler_,request))
		return false;
	else if(CallRequest(handler_,KS_YKT_Clt::drtp_no_,
		0,KS_YKT_Clt::main_func_,time_out_,&err_code_,err_msg_)== false)
	{
		return false;
	}
	else if(::GetRetCode(handler_,&return_code_))
	{
		return false;
	}
	else if(return_code_)
	{
		return false;
	}
	else if(!GetRecordCount(handler_,&record_count_))
	{
		return false;
	}
	return true;
}

bool KS_YKT_Clt::SendNextRequest()
{
	resp_row_ = 0;
	record_count_ = 0;
	return CallNext(handler_,time_out_,&err_code_,err_msg_);
}

bool KS_YKT_Clt::HasMoreRecord()
{
	if(record_count_ <= 0)
		return false;
	else if(resp_row_ < record_count_)
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
	else if(resp_row_ < record_count_)
		return true;
	else
		return false;
}

bool KS_YKT_Clt::GetNextPackage()
{
	if(resp_row_+1 < record_count_)
	{
		resp_row_++;
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
		ResetPackHandle(handler_);
}