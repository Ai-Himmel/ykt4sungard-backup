#include "profile.h"
#include "funclist.h"
#ifndef WIN32
#include <stdarg.h>
#endif
// vim: tabstop=4

KSFileServer::KSFileServer():drtp_port_(0),main_func_(0),load_config_(0),server_start_(0),
	debug_(0),klg_open_(0),service_id_(-1),bcc_handle_(NULL),err_code_(0)
{
	//
	memset(err_msg_,0,sizeof err_msg_);
}
KSFileServer::~KSFileServer()
{
	stop_svr();
	BCCSvrExit();
}
int KSFileServer::load_config(const char *cfg)
{
	char buffer[1024];
	int buflen;
	if(load_config_ == 1)
		return 1;
	TIniFile ini;
	if(!ini.Open((char*)cfg))
	{
		printf("can't open config file[%s]\n",cfg);
		return -1;
	}

	buflen = sizeof(buffer) - 1;

	// DRTPIP
	memset(buffer,0,sizeof buffer);
	ini.ReadString("SERVER","DRTPIP","",buffer,buflen);
	if(strlen(buffer)==0)
	{
		printf("DRTPIP has not been set!\n");
		return -1;
	}
	strcpy(drtp_ip_,buffer);

	
	// PORT
	drtp_port_ = ini.ReadInt("SERVER","PORT",0);
	if(drtp_port_ == 0)
	{
		printf("DRTPPORT has not been set!\n");
		return -1;
	}


	// MAINFUNC
	main_func_= ini.ReadInt("SERVER","MAINFUNC",0);
	if(main_func_ == 0)
	{
		printf("DRTPPORT has not been set!\n");
		return -1;
	}

	// XPACK
	memset(buffer,0,sizeof buffer);
	ini.ReadString("SERVER","XPACK","",buffer,buflen);
	if(strlen(buffer)==0)
	{
		printf("XPACK file has not been set!\n");
		return -1;
	}
	strcpy(xpack_path_,buffer);
	
	//  DEBUG
	debug_ = ini.ReadInt("SERVER","DEBUG",0);

	// download dir
	memset(buffer,0,sizeof buffer);
	ini.ReadString("BASE","downloaddir","",buffer,buflen);
	if(strlen(buffer)==0)
	{
		printf("download dir has not been set!\n");
		return -1;
	}
	KSConfiguration::getInstance()->PutStringPara("downloaddir",buffer);
	// upload dir
	memset(buffer,0,sizeof buffer);
	ini.ReadString("BASE","uploaddir","",buffer,buflen);
	if(strlen(buffer)==0)
	{
		printf("upload dir has not been set!\n");
		return -1;
	}
	KSConfiguration::getInstance()->PutStringPara("uploaddir",buffer);

	// execute command
	memset(buffer,0,sizeof buffer);
	ini.ReadString("BASE","cmd","",buffer,buflen);
	KSConfiguration::getInstance()->PutStringPara("cmd",buffer);

	// execute command argument
	memset(buffer,0,sizeof buffer);
	ini.ReadString("BASE","cmdarg","",buffer,buflen);
	KSConfiguration::getInstance()->PutStringPara("cmdarg",buffer);
	
	open_log("klg");
	if(!BCCSvrInit("forward",600))
	{
		printf("BCCSvrInit error!\n");
		return -1;
	}
	load_config_ = 1;
	return 0;
	
}

int KSFileServer::new_bcc_handle()
{
	if(bcc_handle_ == NULL)
	{
		bcc_handle_ = BSNewHandle(xpack_path_);
	}
	if(bcc_handle_ == NULL)
		return -1;
	BSBindService(bcc_handle_,service_id_);
	return 0;
}
void KSFileServer::free_bcc_handle()
{
	if(bcc_handle_ != NULL)
	{
		BSDeleteHandle(bcc_handle_);
		bcc_handle_ = NULL;
	}
}

void KSFileServer::sleep_thread(long sleeptime)
{
#ifdef WIN32
	static const int span = 500;
	unsigned int usecs = 0;
	unsigned int total_usecs = sleeptime;
	while(total_usecs > 0)
	{
		if(total_usecs > span)
		{
			usecs = span;
		}
		else
			usecs = total_usecs;
		total_usecs-=usecs;
		Sleep(usecs);
	}
#else
	static const int span = 500 * 1000;
	unsigned int usecs = 0;
	unsigned int total_usecs = sleeptime * 1000;
	while(total_usecs > 0)
	{
		if(total_usecs > span)
		{
			usecs = span;
		}
		else
			usecs = total_usecs;
		total_usecs-=usecs;
		usleep(usecs);
	}
#endif
}

int KSFileServer::handle_request()
{
	int ret,errcnt;
	int request_type;
	errcnt = 0;
	while(server_start_)
	{
		if(new_bcc_handle())
		{
			write_msg("new bcc handle error");
			stop_svr();
			return -1;
		}
		memset(err_msg_,0,sizeof err_msg_);
		ret = BSReceiveMsg(bcc_handle_,err_msg_,sizeof(err_msg_)-1);
		switch(ret)
		{
		case 1:
		case 2:
			request_type = BSGetRequestType(bcc_handle_);
			write_msg("收到通知类消息[%d],不处理",request_type);
			break;
		case 0:
		case -1:
			sleep_thread(BCC_TR0);
			break;
		case 3:
			ret = process_request(bcc_handle_);
			break;
		case -2:
		default:
			// 系统错误
			write_msg(err_msg_);
			free_bcc_handle();
			stop_svr();
			return -1;
		}
	}
	return 0;
}
int KSFileServer::process_request(BSHANDLE handle)
{
	int request_type = 0;
	int i,ret,found;
	static const int func_size = sizeof(g_functions)/sizeof(g_functions[0]);
	request_type = ::BSGetRequestType(handle);
	BCCHandle bcc(handle);
	char msg[512] = {0};
	ret = 9999;
	write_xpack(handle,10,"");
	for(i = 0,found = 0;i < func_size; ++i)
	{
		if(g_functions[i].requestType == request_type)
		{
			found = 1;
			ret =  g_functions[i].func(bcc,msg);
			break;
		}
	}
	if(!found)
	{
		// not found
		bcc.SetStringFieldByName("vsmess","无请求功能号");
		bcc.PutRow(9999);
		bcc.DataDone(9999);
		return 0;
	}
	else
	{
		if(ret)
		{
			bcc.SetStringFieldByName("vsmess",msg);
			bcc.PutRow(ret);
		}
		bcc.DataDone(ret);
		return 0;
	}
}

int KSFileServer::start_svr()
{
	int sid;
	if(load_config_ == 0)
	{
		printf("未加载配置文件!\n");
		return -1;
	}
	if(server_start_ == 1)
	{
		printf("服务已启动\n");
		return 1;
	}
	int funclist[2];
	funclist[0] = 2;
	funclist[1] = main_func_;
	sid = BSAddService(0,drtp_ip_,drtp_port_,funclist,2,true);
	if(sid < 0)
	{
		write_msg("连接DRTP失败,ip[%s]port[%d]",drtp_ip_,drtp_port_);
		return -1;
	}
	service_id_ = sid;
	server_start_ = 1;
	return 0;
}
int KSFileServer::stop_svr()
{
	if(server_start_ == 0)
	{
		printf("服务已停止\n");
		return 1;
	}
	BSStopService(service_id_);
	server_start_ = 0;
	return 0;
}
int KSFileServer::check_svr()
{
	return (server_start_==1) && (BSIsServiceOK(service_id_));
}
void KSFileServer::write_msg(char *fmt,...)
{
	if(debug_ == 0)
		return;
	va_list args;
	va_start(args,fmt);
	BSKLGMsg(fmt,args);
	va_end(args);
}
void KSFileServer::write_xpack(void *pBuf, int nBufLen,const char *pszPackHint)
{
	if(debug_ == 0)
		return;
	//KLGWritePack(pBuf,nBufLen,pszPackHint);
}

int KSFileServer::open_log(const char *klgpath)
{
	if(klg_open_ == 1)
		return 0;
	if(BSKLGOpen((char*)klgpath))
	{
		klg_open_ = 1;
		return 0;
	}
	printf("打开日志失败[%s]\n",klgpath);
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////////
KSConfiguration* KSConfiguration::instance_ = NULL;
KSConfiguration* KSConfiguration::getInstance()
{
	if(instance_ == NULL)
	{
		instance_ = new KSConfiguration();
	}
	return instance_;
}
KSConfiguration::KSConfiguration()
{
}
KSConfiguration::~KSConfiguration()
{
	cfgs_.clear();
}
int KSConfiguration::GetIntPara(const char *param,int *value) const
{
	char v[513] = {0};
	if(GetStringPara(param,v))
		return -1;
	*value = atoi(v);
	return 0;
}
int KSConfiguration::GetStringPara(const char *param,char *value) const
{
	VALUE_MAP_TYPE::const_iterator iter;
	iter = cfgs_.find(param);
	if(iter == cfgs_.end())
		return -1;
	strncpy(value,(iter->second).c_str(),512);
	return 0;
}
int KSConfiguration::GetDoublePara(const char *param,double *value) const
{
	char v[513] = {0};
	if(GetStringPara(param,v))
		return -1;
	*value = atof(v);
	return 0;
}
void KSConfiguration::PusIntPara(const char *param,int value)
{
	char v[512]={0};
	sprintf(v,"%d",value);
	PutStringPara(param,v);
}
void KSConfiguration::PutStringPara(const char *param,const char *value)
{
	VALUE_MAP_TYPE::const_iterator iter;
	iter = cfgs_.find(param);
	if(iter != cfgs_.end())
	{
		return;
	}
	cfgs_.insert(VALUE_MAP_TYPE::value_type(param,value));
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
BCCHandle::BCCHandle(BSHANDLE bcc_handle)
{
	BCCHandle::BCCHandle();
	bcc_handle_ = bcc_handle;
	Reset();
}
BCCHandle::BCCHandle():bcc_handle_(NULL),current_row_(0),record_count_(-1)
{
	
}
BCCHandle::BCCHandle(const BCCHandle &rhs)
{
	this->bcc_handle_ = rhs.bcc_handle_;
	this->current_row_ = rhs.current_row_;
	this->record_count_ = rhs.record_count_;
}
BCCHandle& BCCHandle::operator=(const BCCHandle &rhs)
{
	this->bcc_handle_ = rhs.bcc_handle_;
	this->current_row_ = rhs.current_row_;
	this->record_count_ = rhs.record_count_;
	return *this;
}
void BCCHandle::Reset()
{
	current_row_ = 0;
	record_count_ = -1;
	if(this->bcc_handle_)
		::BSClearRow(bcc_handle_);
}
int BCCHandle::PutRow(int retCode)
{
	if(::BSPutRow(bcc_handle_,retCode)>=0)
	{
		::BSClearRow(bcc_handle_);
		return 0;
	}
	return -1;
}
int BCCHandle::DataDone(int retCode)
{
	if(::BSDataDone(bcc_handle_,retCode)>=0)
		return 0;
	return -1;
}
int BCCHandle::SetStringFieldByName(const char *fieldname,const char *val)
{
	if(::BSSetStringFieldByName(bcc_handle_,fieldname,val))
		return 0;
	return -1;
}
int BCCHandle::SetIntFieldByName(const char *fieldname,long value)
{
	if(::BSSetIntFieldByName(bcc_handle_,fieldname,value))
		return 0;
	return -1;
}
int BCCHandle::SetDoubleFieldByName(const char *fieldname,double value)
{
	if(::BSSetDoubleFieldByName(bcc_handle_,fieldname,value))
		return 0;
	return -1;
}
int BCCHandle::GetIntFieldByName(const char *fieldname,int *value)
{
	long v;
	if(::BSGetIntFieldByName(bcc_handle_,current_row_,fieldname,&v))
	{
		*value=(int)v;
		return 0;
	}
	return -1;
}
int BCCHandle::GetDoubleFieldByName(const char *fieldname,double *value)
{
	if(::BSGetDoubleFieldByName(bcc_handle_,current_row_,fieldname,value))
		return 0;
	return -1;
}
int BCCHandle::GetStringFieldByName(const char *fieldname,char *value)
{
	if(::BSGetStringFieldByName(bcc_handle_,current_row_,fieldname,value,255))
		return 0;
	return -1;
}
int BCCHandle::HasMoreRecord()
{
	if(current_row_ < GetRecordCount())
		return 1;
	return 0;
}
int BCCHandle::GetNextRecord()
{
	if(current_row_ < GetRecordCount())
		current_row_++;
	return current_row_;
}
int BCCHandle::GetRecordCount()
{
	if(record_count_ == -1)
	{
		int r = ::BSGetRecordCount(bcc_handle_);
		record_count_ = r;
	}
	return record_count_;
}
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
static int CreatePipHandle(STARTUPINFO *siStartInfo)
{
	SECURITY_ATTRIBUTES saAttr; 
	// Set the bInheritHandle flag so pipe handles are inherited. 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL;

	if(!CreatePipe(&(siStartInfo->hStdInput),&(siStartInfo->hStdOutput),&saAttr,0))
	{
		return -1;
	}
	return 0;
}
#endif

int ExecuteCommand(const char *cmd,const char *cmdarg,std::string &output)
{
#ifdef WIN32
	BOOL rc;
	STARTUPINFO siStartInfo;
	PROCESS_INFORMATION piProcInfo;
	char cmdline[2046];
	char buf[256];
	DWORD dwRead;

	memset(&siStartInfo,0,sizeof siStartInfo);
	memset(&piProcInfo,0,sizeof piProcInfo);
	siStartInfo.cb = sizeof(STARTUPINFO); 

	if(CreatePipHandle(&siStartInfo))
	{
		return -1;
	}
	siStartInfo.hStdError = siStartInfo.hStdOutput;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	if(strlen(cmdarg) > 0)
		sprintf(cmdline,"%s %s",cmd,cmdarg);
	else
		strcpy(cmdline,cmd);

	rc = CreateProcess(NULL, 
						cmdline,     // command line 
						NULL,          // process security attributes 
						NULL,          // primary thread security attributes 
						TRUE,          // handles are inherited 
						NORMAL_PRIORITY_CLASS,             // creation flags 
						NULL,          // use parent's environment 
						NULL,          // use parent's current directory 
						&siStartInfo,  // STARTUPINFO pointer 
						&piProcInfo);  // receives PROCESS_INFORMATION
	if(!rc)
	{
		return -1;
	}
	WaitForSingleObject(piProcInfo.hProcess,INFINITE);
	do
	{
		rc = ReadFile( siStartInfo.hStdInput, buf, sizeof(buf)-1, &dwRead, NULL);
		if( ! rc || dwRead == 0 ) break; 
		buf[dwRead] = 0;
		output += buf;
		if(dwRead < sizeof(buf)-1)
			break;
	}while(1);
	CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
	return 0;
#else
	FILE * fp = NULL;
	int readlen;
	char buf[256];
	char cmdline[2048];
	strcpy(cmdline,cmd);
	strcat(cmdline,cmdarg);
	fp = popen(cmdline,"r");
	if(fp == NULL)
		return -1;
	while(!feof(fp))
	{
		readlen = fread(buf,1,sizeof(buf)-1,fp);
		if(readlen > 0)
		{
			buf[readlen] = 0;
			output += buf;
		}
	}
	pclose(fp);
	return 0;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	KSFileServer fileSvr;
	if(fileSvr.load_config("filesvr.ini"))
	{
		return -1;
	}
	if(fileSvr.start_svr())
	{
		return -1;
	}
	fileSvr.handle_request();
	return 0;
}
