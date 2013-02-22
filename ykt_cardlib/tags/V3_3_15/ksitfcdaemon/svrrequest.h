#ifndef _SVRREQUEST_H_
#define _SVRREQUEST_H_

#include <string>
#include <map>

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
public:
	static KsCardProcessor* instance();
	static void FreeAll();
	~KsCardProcessor();
	int ProcessRequest(KsCardMsg &req,KsCardMsg &resp);
	int RegisterRequest(const std::string &msgtype,KsCardRequestHandler *handler);
	std::string CalcAuthCode(int termid);
	int CheckAuthCode(const std::string &authcode);
};

class KsCardRequestHandler
{
public:
	KsCardRequestHandler();
	virtual ~KsCardRequestHandler();
	virtual int ProcessRequest(KsCardMsg &req,KsCardMsg &resp) = 0;
};

#define REGISTER_HANDLER(t,h) static int _i##h = KsCardProcessor::instance()->RegisterRequest(t,new h)

#endif // _SVRREQUEST_H_
