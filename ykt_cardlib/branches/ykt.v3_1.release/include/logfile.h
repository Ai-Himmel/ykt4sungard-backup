#ifndef _KSYKT_LOGFILE_H_
#define _KSYKT_LOGFILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <map>

#define LOG_MAX_APP_NAME 128
#define MAX_LOG_PATH 1024

class KSYkt_Log_Writer 
{
private:
	static KSYkt_Log_Writer *instance_;
private:
	FILE *log_file_fp_;
	char curr_date_[9];
	char app_name_[LOG_MAX_APP_NAME+1];
	char log_path_[MAX_LOG_PATH+1];
	int open_current_log_file();
	void get_current_time(char time_str[15]);
	int test_log_dir(const char *log_dir);
	KSYkt_Log_Writer(const char *app_name = NULL);
public:
	~KSYkt_Log_Writer();
	int openlog(const char *log_path);
	void writelog(const char *fmt,...);
	void writemsg(const char *fmt,...);
	void flush_log();
	static KSYkt_Log_Writer* instance();
	static KSYkt_Log_Writer* make_instance(const char *app_name = NULL);
};

class KS_Log_Tracer
{
private:
	std::list<std::string> errMsgList_;
	std::list<std::string> errFileInfo_;
	typedef std::map<std::string,std::string> PARA_MAP;
	PARA_MAP paras_;
	int traceLevel_;
	int traceFileNo_;
	char traceFileName_[1024];
	int GetIntPara(const char *para,int *val);
	void clearAll();
private:
	KS_Log_Tracer();
	static KS_Log_Tracer * instance_;
public:
	~KS_Log_Tracer();
	void BeginTrace(const char *msg);
	void TraceMsg(const char *msg,int level = 1);
	void TraceMsg2(const char *fmt,...);
	void EndTrace();
	void SetPara(const char *para,const char *val);
	void GetPara(const char *para,char *val);
	void SetTraceFile(const char *file,int no);
	void GetLastMsg(char *msg);
	static KS_Log_Tracer * instance();
	static void instance(KS_Log_Tracer *i);
	static const char TRACE_FUNC[];
	static const char VERBOSE[];
	static const char OUTPUT_DATETIME[];
	static const char OUTPUT_FILE[];
};

class KS_Log_Tracer_Guard
{
public:
	KS_Log_Tracer_Guard(const char *msg,const char *file,int line);
	~KS_Log_Tracer_Guard();
};

#define DCLR_LOGMSG(x) KS_Log_Tracer_Guard _log_guard(x,__FILE__,__LINE__)
#define TRACE2_LOG(x) do{KS_Log_Tracer::instance()->SetTraceFile(__FILE__,__LINE__); KS_Log_Tracer::instance()->TraceMsg2 x ; }while(0)
#define TRACE_LOG(x) do{ KS_Log_Tracer::instance()->SetTraceFile(__FILE__,__LINE__); KS_Log_Tracer::instance()->TraceMsg(x); }while(0)
#define TRACEMSG_LOG(x) do {KS_Log_Tracer::instance()->SetTraceFile(__FILE__,__LINE__); \
	std::stringstream _oss; _oss<<x; KS_Log_Tracer::instance()->TraceMsg(_oss.str().c_str()); } while(0)

//extern KSYkt_Log_Writer g_logger;

#define DEBUG_LOG(x) do{ KSYkt_Log_Writer::instance()->writelog x ; } while(0)

#endif // _KSYKT_LOGFILE_H_
