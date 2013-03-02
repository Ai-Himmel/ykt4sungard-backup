
#ifdef _DEBUG
//#include <vld.h>
//#include <vldapi.h>
#endif
#include <ace/ACE.h>
#include <ace/Get_Opt.h>
#include <fstream>
#include "ksgateway.h"
#include "msw/mswsvr.h"

////////////////////////////////////////////////////////////
// KSGService
KSGService::KSGService():_gateway(0),_stop(0)
{
	// empty
}

KSGService::~KSGService()
{
	// empty
}

void KSGService::handle_control(DWORD control_code)
{
	if(SERVICE_CONTROL_STOP == control_code
		|| SERVICE_CONTROL_SHUTDOWN == control_code)
	{
		report_status(SERVICE_STOP_PENDING);
		if(_gateway)
			_gateway->stop();
	}
	else
	{
		
		ACE_NT_Service::handle_control(control_code);
	}
}

int KSGService::handle_exception(ACE_HANDLE h)
{
	return 0;
}

int KSGService::handle_timeout(const ACE_Time_Value& tv,const void* arg/* =0 */)
{

	return 0;
}

int KSGService::svc()
{
	// 启动服务
	int ret = -1;
	if(!_gateway)
	{
		_gateway = new KSGateway;
	}
	if(_gateway)
	{
		report_status (SERVICE_RUNNING);
		ret = KsgStartServer(_gateway);
		delete _gateway;
		_gateway = NULL;
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////
// KSGProcess
KSGProcess::KSGProcess()
:_opt_install(0),_opt_remove(0),_opt_start(0),_opt_kill(0),_opt_debug(0)
{
	ACE_OS::strcpy(_progname,"gwmain");
	ACE::init();
}

KSGProcess::~KSGProcess()
{
	ACE::fini();
}

void KSGProcess::print_usage()
{
	ACE_OS::printf("Usage: %s "
				     "-i -r -s -k -d\n"
					 "  -i : Install program as NT Service\n"
					 "  -r : Remove program from Service Manager\n"
					 "  -s : Start the service\n"
					 "  -k : Kill the service\n"
					 "  -d : Use debug mode to start program\n"
					 ,_progname);
	ACE_OS::exit(1);
}
int KSGProcess::parse_args(int argc,char** argv)
{
	ACE_Get_Opt get_opt(argc,argv,ACE_TEXT("irskdh"));
	int c;
	while((c = get_opt()) != -1)
	{
		switch(c)
		{
		case 'i':
			_opt_install = 1;
			break;
		case 'r':
			_opt_remove = 1;
			break;
		case 's':
			_opt_start = 1;
			break;
		case 'k':
			_opt_kill = 1;
			break;
		case 'd':
			_opt_debug = 1;
			break;
		case 'h':
			print_usage();
			break;
		default:
			print_usage();
			break;
		}
	}
	return 0;
}
static BOOL __stdcall
ConsoleHandler (DWORD ctrlType)
{
	ACE_UNUSED_ARG (ctrlType);
	KSG_SERVICE::instance ()->handle_control (SERVICE_CONTROL_STOP);
	return TRUE;
}

ACE_NT_SERVICE_DEFINE (ykt_gateway,
				   KSGService,
				   ACE_TEXT ("ykt_gateway"));

int KSGProcess::run(int argc,char ** argv)
{
	KSG_SERVICE::instance()->name(ACE_TEXT("ykt_gateway"),
		ACE_TEXT("ykt_gateway"));
	parse_args(argc,argv);
	if(_opt_install && !_opt_remove)
	{
		KSGService * svr = KSG_SERVICE::instance();
		if(-1 == svr->insert(SERVICE_DEMAND_START))
		{
			ACE_OS::printf("install NT Service error[%d]!\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_remove && !_opt_install)
	{
		if(-1 == KSG_SERVICE::instance()->remove())
		{
			ACE_OS::printf("remove from Service Manager error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_start && _opt_kill)
		print_usage();
	if(_opt_start)
	{
		ACE_OS::printf("正在启动前置机...\n");
		if(-1 == KSG_SERVICE::instance()->start_svc())
		{
			ACE_OS::printf("start service error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_kill)
	{
		ACE_OS::printf("正在停止前置机...\n");
		if(-1 == KSG_SERVICE::instance()->stop_svc())
		{
			ACE_OS::printf("stop service error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		return 0;
	}
	if(_opt_debug)
	{
		// 直接启动
		SetConsoleCtrlHandler (&ConsoleHandler, 1);
		int ret = KSG_SERVICE::instance()->svc();
		//system("pause");
		return ret;
	}
	else
	{
		/*std::ofstream *output_file = new std::ofstream("ntsvc.log", std::ios::out);
		if (output_file && output_file->rdstate() == std::ios::goodbit)
			ACE_LOG_MSG->msg_ostream(output_file, 1);
		
		ACE_LOG_MSG->open(argv[0],
			ACE_Log_Msg::STDERR | ACE_Log_Msg::OSTREAM,
			0);

		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("%T (%t): Starting service.\n")));*/
		ACE_NT_SERVICE_RUN (ykt_gateway,KSG_SERVICE::instance (),
			ret);
		if(ret == 0)
		{
			ACE_OS::printf("Couldn't start service!\n");
		}
		else
		{
			ACE_OS::printf("Service exits [%d]!\n",ACE_OS::last_error());
		}
		return 0;
	}
	return 0;
}
typedef ACE_Singleton<KSGProcess,ACE_Mutex> KSG_PROCESS;
////////////////////////////////////////////////////////////////////
// main function
int ACE_TMAIN(int argc, ACE_TCHAR * argv[])
{
#ifdef _DEBUG
	//VLDEnable();
#endif
	return KSG_PROCESS::instance()->run(argc,argv);
}