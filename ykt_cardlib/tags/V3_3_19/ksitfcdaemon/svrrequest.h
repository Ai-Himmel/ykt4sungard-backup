#ifndef _SVRREQUEST_H_
#define _SVRREQUEST_H_

#include <string>
#include <map>

#include "dbhandler.h"

class KsCardRequestHandler;

class KsCardProcessor
{
private:
	static KsCardProcessor *instance_;
	typedef std::map<std::string,KsCardRequestHandler*> REQUEST_HANDLER_MAP_TYPE;
	std::string authcode_;
	REQUEST_HANDLER_MAP_TYPE requestHandler_;
	KsCardProcessor();
	void freeHandler();
	TransDB transdb_;
	InfoDB infodb_;
public:
	static KsCardProcessor* instance();
	static void FreeAll();
	~KsCardProcessor();
	int ProcessRequest(KsCardMsg &req,KsCardMsg &resp);
	int RegisterRequest(const std::string &msgtype,KsCardRequestHandler *handler);
	std::string CalcAuthCode(int termid);
	int CheckAuthCode(const std::string &authcode);
	TransDB& GetTransDB();
	InfoDB& GetInfoDB();
};

class KsCardRequestHandler
{
public:
	KsCardRequestHandler();
	virtual ~KsCardRequestHandler();
	virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) = 0;
};

#define REGISTER_HANDLER(t,h) static int _i##h = KsCardProcessor::instance()->RegisterRequest(t,new h)

class  CardVerInfo
{
private:
	
public:
	CardVerInfo():cardno_(0),flag_(0)
	{
	}
	CardVerInfo(const CardVerInfo& rhs)
	{
		this->cardphyid_ = rhs.cardphyid_;
		this->cardno_ = rhs.cardno_;
		this->flag_ = rhs.flag_;
		this->cardverno_ = rhs.cardverno_;
	}
	CardVerInfo& operator=(const CardVerInfo & rhs)
	{
		this->cardphyid_ = rhs.cardphyid_;
		this->cardno_ = rhs.cardno_;
		this->flag_ = rhs.flag_;
		this->cardverno_ = rhs.cardverno_;
		return *this;
	}
	bool operator==(const CardVerInfo & rhs)
	{
		return (this->cardphyid_ == rhs.cardphyid_ && this->cardno_ == rhs.cardno_
			&& this->cardverno_ == rhs.cardverno_);
	}
	std::string cardphyid_;
	int cardno_;
	int flag_;
	std::string cardverno_;
};

#endif // _SVRREQUEST_H_
