///////////////////////////////////////////////////////////////////////////////
////
#include "std.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <wx/snglinst.h>
#include <wx/aboutdlg.h>

#include "resource.h"
#include "kscarddaemondlg.h"
#include "daemonsvr.h"
#include "kscarddaemon.h"
#include "dbhandler.h"
#include "svrrequest.h"
//////////////////////////////////////////////////////////////////////////////
KsCardProcessor* KsCardProcessor::instance_ = NULL;
KsCardProcessor* KsCardProcessor::instance()
{
	if(NULL == instance_)
	{
		instance_ = new KsCardProcessor;
	}
	return instance_;
}
void KsCardProcessor::FreeAll()
{
	if(NULL != instance_)
	{
		delete instance_;
		instance_ = NULL;
	}
}

KsCardProcessor::KsCardProcessor()
{
	requestHandler_.clear();
}
KsCardProcessor::~KsCardProcessor()
{
	freeHandler();
}

int KsCardProcessor::ProcessRequest(KsCardMsg &req,KsCardMsg &resp)
{
	REQUEST_HANDLER_MAP_TYPE::iterator iter;
	iter = requestHandler_.find(req.MsgType());
	if(iter != requestHandler_.end())
	{
		KsCardRequestHandler* handler = iter->second;
		if(NULL == handler)
			return -2;
		resp.SetMsgType(req.MsgType());
		return handler->ProcessRequest(req,resp);
	}
	return -2;
}
int KsCardProcessor::RegisterRequest(const std::string &msgtype,KsCardRequestHandler *handler)
{
	REQUEST_HANDLER_MAP_TYPE::iterator iter;
	iter = requestHandler_.find(msgtype);
	if(iter != requestHandler_.end())
	{
		return -1;
	}
	requestHandler_.insert(REQUEST_HANDLER_MAP_TYPE::value_type(msgtype,handler));
	return 0;
}
void KsCardProcessor::freeHandler()
{
	REQUEST_HANDLER_MAP_TYPE::iterator iter;
	for(iter = requestHandler_.begin();iter != requestHandler_.end();++iter)
	{
		KsCardRequestHandler* handler = iter->second;
		if(NULL != handler)
		{
			delete handler;
		}
	}
	requestHandler_.clear();
}
std::string KsCardProcessor::CalcAuthCode(int termid)
{
	time_t t;
	t = time(NULL);
	srand(t);
	int r = rand();
	r += termid;
	char temp[20]={0};
	sprintf(temp,"%08X",r);
	this->authcode_ = temp;
	return this->authcode_;
}
int KsCardProcessor::CheckAuthCode(const std::string &authcode)
{
	return (authcode == this->authcode_) ? 0 : -1;
}

///////////////////////////////////////////////////////////////////////////////
KsCardRequestHandler::KsCardRequestHandler()
{
}
KsCardRequestHandler::~KsCardRequestHandler()
{
}

///////////////////////////////////////////////////////////////////////////////
class KsCardLoginHandler : public KsCardRequestHandler
{
public:
	KsCardLoginHandler():KsCardRequestHandler()
	{
	}
	virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp)
	{
		TransDB trans;
		int termid = 0,termseqno = 0;
		
		if(trans.Open(wxGetApp().dbpath_))
		{
			resp.SetIntPara("data.retcode",EKS_DATABASE);
		}
		else
		{
			if(!req.GetIntPara("data.termid",&termid))
				return -1;
			if(trans.Login(termid,&termseqno))
			{
				resp.SetIntPara("data.retcode",EKS_SYSTEM);
			}
			else
			{
				std::string authcode = KsCardProcessor::instance()->CalcAuthCode(termid);
				resp.SetStrPara("authcode",authcode);
				resp.SetIntPara("data.retcode",EKS_SUCCESS);
				resp.SetIntPara("data.termseqno",termseqno);
			}
		}
		return 1;
	}
};
REGISTER_HANDLER("login",KsCardLoginHandler);

class KsCardInit4Purchase : public KsCardRequestHandler
{
public:
	KsCardInit4Purchase():KsCardRequestHandler()
	{
	}
	virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp)
	{
		std::string authcode;
		std::stringstream errmsg;
		TransDB trans;
		int retcode = EKS_SUCCESS;
		if(!req.GetStrPara("authcode",authcode))
			return -1;
		if(KsCardProcessor::instance()->CheckAuthCode(authcode))
		{
			errmsg<<"授权码错误";
			retcode = EKS_AUTHCODEERR;
		}
		else
		{
			if(trans.Open(wxGetApp().dbpath_))
			{
				errmsg<<"不能打开数据库";
				retcode = EKS_DATABASE;
			}
			else
			{
				int ret = trans.Init4Purchase(req);
				if(ret)
				{
					errmsg<<"写流水失败";
					retcode = EKS_DATABASE;
				}
				else
				{
					std::string value;
					if(!req.GetStrPara("data.termid",value))
						return -1;
					resp.SetStrPara("data.termid",value);

					if(!req.GetStrPara("data.termseqno",value))
						return -1;
					resp.SetStrPara("data.termseqno",value);

					resp.SetStrPara("data.cardstatus","N");
					errmsg<<"成功";
				}
			}
		}
		resp.SetIntPara("data.retcode",retcode);
		resp.SetStrPara("data.retmsg",errmsg.str());
		return 1;
	}
};
REGISTER_HANDLER("init4purchase",KsCardInit4Purchase);

class KsCardDebit4Purchase : public KsCardRequestHandler
{
public:
	KsCardDebit4Purchase():KsCardRequestHandler()
	{
	}
	virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp)
	{
		std::string authcode;
		std::stringstream errmsg;
		TransDB trans;
		int retcode = EKS_SYSTEM;
		if(!req.GetStrPara("authcode",authcode))
			return -1;
		if(KsCardProcessor::instance()->CheckAuthCode(authcode))
		{
			errmsg<<"授权码错误";
			retcode = EKS_AUTHCODEERR;
		}
		else
		{
			if(trans.Open(wxGetApp().dbpath_))
			{
				errmsg<<"不能打开数据库";
				retcode = EKS_DATABASE;
			}
			else
			{
				int ret = trans.Debit4Purchase(req);
				if(ret)
				{
					errmsg<<"写流水失败";
					retcode = EKS_DATABASE;
				}
				else
				{
					std::string value;
					if(!req.GetStrPara("data.termid",value))
						return -1;
					resp.SetStrPara("data.termid",value);

					if(!req.GetStrPara("data.termseqno",value))
						return -1;
					resp.SetStrPara("data.termseqno",value);
					errmsg<<"成功";
					retcode = EKS_SUCCESS;
				}
			}
		}
		resp.SetIntPara("data.retcode",retcode);
		resp.SetStrPara("data.retmsg",errmsg.str());
		return 1;
	}
};
REGISTER_HANDLER("debit4purchase",KsCardDebit4Purchase);


