#include "stdafx.h"
#include <ace/ACE.h>
#include <ksgateway.h>
#include "osutil.h"
#include <ace/Get_Opt.h>


static int start_as_daemon = 0;

static int parse_args(int argc,char *argv[])
{
	ACE_Get_Opt get_opt(argc,argv,"b",1);
	for(int c;(c = get_opt())!= -1;)
	{
		switch(c)
		{
		case 'b':
			start_as_daemon = 1;
			break;
		default:
			break;
		}
	}
	return 0;
}

static int do_daemonize()
{
	pid_t pid;
	pid = ACE_OS::fork();
	if(pid != 0)
		ACE_OS::exit(0);
	//ACE_OS::signal (SIGHUP, SIG_IGN);
	ACE_OS::setsid();
	pid = ACE_OS::fork();
	if(pid != 0)
		ACE_OS::exit(0);

	ACE_OS::umask(0);
	for(int i = ACE::max_handles() - 1;i >= 0;--i)
		ACE_OS::close(i);
	return 0;
}

int ACE_TMAIN(int argc, ACE_TCHAR * argv[])
{
	//ACE_DEBUG((LM_DEBUG,"[%s][%d]my id %d\n",argv[0],argc,ACE_OS::getpid()));
	//ACE_Service_Config daemon(argv[0]);
	int ret;
	char * p = ACE_OS::strdup(ACE::dirname(argv[0]));

	ACE_OS::chdir(p);
	KSGOSUtil::Program_name(argv[0]);
	//int ret = ACE_Service_Config::open(argc,argv,ACE_DEFAULT_LOGGER_KEY,1,1);
	ret = parse_args(argc,argv);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"≥ı ºªØ ß∞‹[%d]",ret));
		//ACE_OS::exit(1);
	}
	if(start_as_daemon)
	{
		//ret = ACE::daemonize(NULL);
		ret = do_daemonize();
		if(ret)
			ACE_OS::exit(ret);
		//fprintf(stdout,"daemonize return [%d]\n",ret);
		//KSGThreadUtil::Sleep(15000);
	}
	ACE_DEBUG((LM_DEBUG,"gwmain running process id: %d",ACE_OS::getpid()));
	KSGateway * gateway = new KSGateway;
	KsgStartServer(gateway);
	delete gateway;
	return 0;
}

