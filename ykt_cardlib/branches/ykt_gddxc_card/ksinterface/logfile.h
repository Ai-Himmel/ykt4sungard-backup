#ifndef _KSYKT_LOGFILE_H_
#define _KSYKT_LOGFILE_H_

#include <stdio.h>
#include <stdlib.h>

#define LOG_MAX_APP_NAME 128
#define MAX_LOG_PATH 1024

class KSYkt_Log_Writer 
{
private:
	FILE *log_file_fp_;
	char curr_date_[9];
	char app_name_[LOG_MAX_APP_NAME+1];
	char log_path_[MAX_LOG_PATH+1];
	int open_current_log_file();
	void get_current_time(char time_str[15]);
	int test_log_dir(const char *log_dir);
public:
	KSYkt_Log_Writer(const char *app_name = NULL);
	~KSYkt_Log_Writer();
	int openlog(const char *log_path);
	void writelog(const char *fmt,...);
	void flush_log();
};

extern KSYkt_Log_Writer g_logger;

#define DEBUG_LOG(x) do{ g_logger.writelog("F[%s]L[%d]",__FILE__,__LINE__);g_logger.writelog x ; } while(0)

#endif // _KSYKT_LOGFILE_H_
