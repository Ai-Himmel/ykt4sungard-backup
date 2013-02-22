#include "logfile.h"
#include <time.h>
#ifdef WIN32
#include <windows.h>
#include <WinBase.h>
#endif

KSYkt_Log_Writer::KSYkt_Log_Writer(const char* an)
	:log_file_fp_(NULL)
{
	memset(app_name_,0,sizeof app_name_);
	if(an)
		strncpy(app_name_,an,sizeof(app_name_) - 1);
	memset(log_path_,0,sizeof log_path_);
	memset(curr_date_,0,sizeof curr_date_);
}

KSYkt_Log_Writer::~KSYkt_Log_Writer()
{
	if(log_file_fp_)
	{
		fclose(log_file_fp_);
		log_file_fp_ = NULL;
	}
}

void KSYkt_Log_Writer::get_current_time(char time_str[15])
{
	time_t curr;
	struct tm curr_tm;
	time(&curr);
	curr_tm = *localtime(&curr);
	sprintf(time_str,"%.04d%.02d%.02d%.02d%.02d%.02d",curr_tm.tm_year+1900
		,curr_tm.tm_mon+1,curr_tm.tm_mday,curr_tm.tm_hour
		,curr_tm.tm_min,curr_tm.tm_sec);

}

int KSYkt_Log_Writer::openlog(const char *log_path)
{
	memset(log_path_,0,sizeof log_path_);
	strncpy(log_path_,log_path,sizeof(log_path_)-1);
	return open_current_log_file();
}

int KSYkt_Log_Writer::open_current_log_file()
{
	char curr_time[15] = "";
	char now_date[9] = "";
	get_current_time(curr_time);
	strncpy(now_date,curr_time,8);
	// 需要重新创建目录
	if(strcmp(now_date,curr_date_) !=0)
	{
		if(log_file_fp_)
		{
			fclose(log_file_fp_);
			log_file_fp_ = NULL;	
		}
		strcpy(curr_date_,now_date);
	}
	// 检查目录
	if(!log_file_fp_)
	{
		
		char out_put_file[MAX_LOG_PATH+LOG_MAX_APP_NAME+1] = "";
		sprintf(out_put_file,"%s\\%s\\",log_path_,curr_date_);
		if(test_log_dir(out_put_file))
		{
			return -1;
		}
		strcat(out_put_file,app_name_);
		strcat(out_put_file,".log");
		if((log_file_fp_ = fopen(out_put_file,"a+"))==NULL)
			return -1;
	}
	return 0;
}

int KSYkt_Log_Writer::test_log_dir(const char *log_dir)
{
	int create_dir = 0;
#ifdef WIN32
	DWORD dir_attr;
	dir_attr = GetFileAttributes(log_dir);
	if(dir_attr == INVALID_FILE_ATTRIBUTES )
		create_dir = 1;
	else if(dir_attr != FILE_ATTRIBUTE_DIRECTORY)
		return -1;
	if(create_dir)
	{
		if(!CreateDirectory(log_dir,NULL))
			return -1;
	}
#else
#endif
	return 0;
}

void KSYkt_Log_Writer::writelog(const char *fmt,...)
{
	int pos = 0;
	char msg[4096] = "";
	char time_str[15] = "";
	get_current_time(time_str);
	if(open_current_log_file())
		return;
	pos = sprintf(msg,"%s - : ",time_str);
	va_list args;
	va_start(args,fmt);
	pos += vsprintf(msg+pos,fmt,args);
	va_end(args);
	msg[pos] = '\n';
	msg[pos+1] = 0;
	fprintf(log_file_fp_,msg);
	flush_log();
	fprintf(stderr,msg);
}

void KSYkt_Log_Writer::flush_log()
{
	if(log_file_fp_)
	{
		fflush(log_file_fp_);
	}
}