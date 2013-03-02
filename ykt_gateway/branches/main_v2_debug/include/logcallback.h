#ifndef _KSG_LOGCALLBACK_H_
#define _KSG_LOGCALLBACK_H_

#ifdef _MSC_VER
# pragma once
#endif

#include <ace/Log_Msg_Callback.h>
#include <ace/Log_Record.h>
#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Log_Msg_Backend.h>
#include <ace/Mutex.h>
#ifndef WIN32
#include <ace/Log_Msg_UNIX_Syslog.h>
#endif
#include <fstream>

class KSGLogCallback : public ACE_Log_Msg_Callback
{
public:
	KSGLogCallback();
	
	void log(ACE_Log_Record& log_record);

	inline void verbose(int v)
	{
		_verbose = v;
	}
private:
	int _verbose;
	int _recursive;
};


class KSGLogBackend : public ACE_Log_Msg_Backend
{
private:
	typedef enum { laStdout = 0x01,laFile= 0x02,laSyslog=0x04 } LOG_APPENDER;
	std::string _level;
	std::string _appender;
	std::string _filepath;
	unsigned long _file_max_size;
	int _file_max_count;
	volatile unsigned long _file_curr_size;

	ACE_Log_Priority _priority;
	u_long _log_app;
	std::ofstream *_logfile;
	ACE_Mutex _file_mutex;

#ifndef WIN32
	ACE_Log_Msg_UNIX_Syslog* _syslog;

#endif

	void log2file(const ACE_TCHAR *msg,int msglen);
	void log2syslog(ACE_Log_Record& log_record);

	int check_file_size(long msglen);
	int backup_curr_file();
public:
	KSGLogBackend(const std::string& level,const std::string& appender
		,const std::string& filepath,int max_file_size,int file_count);
	virtual ~KSGLogBackend();
	int open(const ACE_TCHAR *logger_key);
	int log(ACE_Log_Record& log_record);
	int close();
	int reset();
	inline void set_file_size(unsigned long size)
	{
		_file_max_size = size;
	}
	inline void set_file_max_count(int count)
	{
		_file_max_count = count;
	}
};

//typedef ACE_Singleton<KSGLogCallback,ACE_Null_Mutex> LOGMSG_CALL_BACK;

#endif // _KSG_LOGCALLBACK_H_
