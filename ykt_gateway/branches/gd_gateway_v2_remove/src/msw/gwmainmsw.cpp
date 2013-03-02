
#ifdef _DEBUG
//#include <vld.h>
//#include <vldapi.h>
#endif
#include <ace/ACE.h>
#include <ace/Get_Opt.h>
#include <fstream>
#include "ksgateway.h"
#include "version.h"
#include "msw/mswsvr.h"

typedef struct 
{
	DWORD e_code;
	const char *e_msg;
}win32_exception_information_t;

static win32_exception_information_t g_global_excpt_array [] =
{
	EXCEPTION_ACCESS_VIOLATION, "The thread tried to read from or write to a virtual address for which it does not have the appropriate access. ",
	EXCEPTION_ARRAY_BOUNDS_EXCEEDED, "The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking. ",
	EXCEPTION_BREAKPOINT,"A breakpoint was encountered. ",
	EXCEPTION_DATATYPE_MISALIGNMENT,"The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on. ",
	EXCEPTION_FLT_DENORMAL_OPERAND, "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. ",
	EXCEPTION_FLT_DIVIDE_BY_ZERO, "The thread tried to divide a floating-point value by a floating-point divisor of zero. ",
	EXCEPTION_FLT_INEXACT_RESULT, "The result of a floating-point operation cannot be represented exactly as a decimal fraction. ",
	EXCEPTION_FLT_INVALID_OPERATION, "This exception represents any floating-point exception not included in this list. ",
	EXCEPTION_FLT_OVERFLOW, "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. ",
	EXCEPTION_FLT_STACK_CHECK, "The stack overflowed or underflowed as the result of a floating-point operation. ",
	EXCEPTION_FLT_UNDERFLOW, "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. ",
	EXCEPTION_ILLEGAL_INSTRUCTION, "The thread tried to execute an invalid instruction. ",
	EXCEPTION_IN_PAGE_ERROR, "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. ",
	EXCEPTION_INT_DIVIDE_BY_ZERO, "The thread tried to divide an integer value by an integer divisor of zero. ",
	EXCEPTION_INT_OVERFLOW, "The result of an integer operation caused a carry out of the most significant bit of the result. ",
	EXCEPTION_INVALID_DISPOSITION, "An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. ",
	EXCEPTION_NONCONTINUABLE_EXCEPTION, "The thread tried to continue execution after a noncontinuable exception occurred. ",
	EXCEPTION_PRIV_INSTRUCTION, "The thread tried to execute an instruction whose operation is not allowed in the current machine mode. ",
	EXCEPTION_SINGLE_STEP, "A trace trap or other single-instruction mechanism signaled that one instruction has been executed. ",
	EXCEPTION_STACK_OVERFLOW, "The thread used up its stack. ",
	//0xFFFFFFFF,NULL,
};

static LPTOP_LEVEL_EXCEPTION_FILTER g_top_level_exception = NULL;
//////////////////////////////////////////////////////////////////////////
// 异常捕获接口
LONG WINAPI KSG_UnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	char expt_msg[512] = "";
	int i;
	ACE_OS::sprintf(expt_msg,"exception cause at addr[%08X] code[%X]\n"
		,pExceptionInfo->ExceptionRecord->ExceptionAddress
		,pExceptionInfo->ExceptionRecord->ExceptionCode);
	for(i = 0;i < sizeof (g_global_excpt_array)/sizeof(g_global_excpt_array[0]);++i)
	{
		if(g_global_excpt_array[i].e_code == pExceptionInfo->ExceptionRecord->ExceptionCode)
		{	
			ACE_OS::strcat(expt_msg,g_global_excpt_array[i].e_msg);
			break;
		}
	}
	if(i == sizeof (g_global_excpt_array)/sizeof(g_global_excpt_array[0]))
		ACE_OS::strcat(expt_msg," Unknown exception! ");
	
	ACE_DEBUG((LM_ERROR,expt_msg));
	if(g_top_level_exception)
		return g_top_level_exception(pExceptionInfo);
	else
		return EXCEPTION_CONTINUE_SEARCH;
}

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

void KSGProcess::print_version()
{
	ACE_OS::printf("%s\n",KSG_COPYRIGHT_STRING);
	ACE_OS::printf("version : %s\n",KSG_FULL_VERSION);
	ACE_OS::printf("build : %s\n",KSG_BUILD_INFO);
	ACE_OS::printf("build with ACE : %s  , boost : %s , libcurl : %s\n"
		,KSG_ACE_VERSION,KSG_BOOST_VERSION,KSG_CURL_VERSION);
	ACE_OS::exit(1);
}
void KSGProcess::print_usage()
{
	ACE_OS::printf(KSG_COPYRIGHT_STRING
		"\nUsage: %s "
				     "-i -r -s -k -d -v \n"
					 "  -i : Install program as NT Service\n"
					 "  -r : Remove program from Service Manager\n"
					 "  -s : Start the service\n"
					 "  -k : Kill the service\n"
					 "  -d : Use debug mode to start program\n"
					 "  -v : show version\n"
					 ,_progname);
	ACE_OS::exit(1);
}
int KSGProcess::parse_args(int argc,char** argv)
{
	ACE_Get_Opt get_opt(argc,argv,ACE_TEXT("irskdhv"));
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
		case 'v':
			print_version();
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
		ACE_OS::printf("install NT Service success!\n");
		return 0;
	}
	if(_opt_remove && !_opt_install)
	{
		if(-1 == KSG_SERVICE::instance()->remove())
		{
			ACE_OS::printf("remove from Service Manager error![%d]\n",ACE_OS::last_error());
			return -1;
		}
		ACE_OS::printf("remove from Service Manager success!\n");
		return 0;
	}
	if(_opt_start && _opt_kill)
		print_usage();
	if(_opt_start)
	{
		ACE_OS::printf("正在启动前置机...\n");
		g_top_level_exception = SetUnhandledExceptionFilter(KSG_UnhandledExceptionFilter);
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
		g_top_level_exception = SetUnhandledExceptionFilter(KSG_UnhandledExceptionFilter);
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