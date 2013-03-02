#ifndef _KSG_MSWSVR_H_
#define _KSG_MSWSVR_H_

#include <ace/Event_Handler.h>
#include <ace/NT_Service.h>
#include <ace/Singleton.h>
#include <ace/Mutex.h>
#include "ksgateway.h"

class KSGService : public ACE_NT_Service
{
public:
	KSGService(void);
	~KSGService();

	virtual void handle_control(DWORD control_code);

	virtual int handle_exception(ACE_HANDLE h);

	virtual int svc(void);

	virtual int handle_timeout(const ACE_Time_Value& tv,const void* arg=0);

private:
	KSGateway* _gateway;
	int _stop;
};

class KSGProcess
{
private:
	int _opt_install;
	int _opt_remove;
	int _opt_start;
	int _opt_kill;
	int _opt_debug;
	char _progname[128];
	int parse_args(int argc,char** argv);
	void print_usage();
	void print_version();
public:
	KSGProcess();
	~KSGProcess();
	int run(int argc,char ** argv);
};

typedef ACE_Singleton<KSGService,ACE_Mutex> KSG_SERVICE;

#endif // _KSG_MSWSVR_H_
