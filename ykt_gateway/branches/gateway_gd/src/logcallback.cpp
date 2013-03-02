#include <stdafx.h>
#include "logcallback.h"
#include "xutils/xtype_trait.h"
#include "xutils/xstring.h"
#include "osutil.h"
#include <ace/Log_Msg.h>
#include <list>
#include <ace/OS.h>
#include <fstream>
#include <iostream>
#define _MAX_SIZE 1024 << 10

KSGLogCallback::KSGLogCallback():_verbose(0),_recursive(1)
{
	//
}

void KSGLogCallback::log(ACE_Log_Record& log_record)
{
	ACE_TCHAR msg_data[ACE_Log_Record::MAXVERBOSELOGMSGLEN];
	ACE_OS::sprintf(msg_data,"F[%s]L[%d]-%s\n",ACE_LOG_MSG->file()
		,ACE_LOG_MSG->linenum(),log_record.msg_data());
	log_record.msg_data(msg_data);
}


KSGLogBackend::KSGLogBackend(const std::string& level
							 ,const std::string& appender
							 ,const std::string& filepath
							 ,int max_file_size
							 ,int file_count)
							 :_level(level),_appender(appender)
							 ,_filepath(filepath),_logfile(NULL)
							 ,_file_max_count(file_count),_file_max_size(max_file_size)
							 ,_file_curr_size(0)
#ifndef WIN32
							 ,_syslog(NULL)
#endif

{
	if(_level == "debug")
		_priority = LM_DEBUG;
	else if(_level == "info" )
		_priority = LM_INFO;
	else if(_level == "error" )
		_priority = LM_ERROR;
	else if(_level == "notice")
		_priority = LM_NOTICE;
	else if(_level == "alert")
		_priority = LM_ALERT;
	else 
		_priority = LM_INFO;

	std::list<std::string> alist;

	_log_app = 0;
	std::back_insert_iterator<std::list<std::string> > iter(alist);
	xutil::StringUtil::SpliteString(_appender,",",iter);
	for(std::list<std::string>::iterator i = alist.begin();i != alist.end();
		++i)
	{
		if("stdout" == *i)
			_log_app |= laStdout;
		else if("file" == *i)
			_log_app |= laFile;
		else if("syslog" == *i)
			_log_app |= laSyslog;
	}
	// 默认为 stdout
	if(!_log_app)
		_log_app = laStdout;

	if((_log_app & laFile) && (_filepath.length() != 0))
	{
		// open log file
		_logfile = new ofstream(_filepath.c_str(),std::ios_base::out|std::ios_base::app);
		if(_logfile->bad())
		{
			ACE_DEBUG((LM_ERROR,"打开日志文件失败"));
		}
		else
		{
			_file_curr_size = ACE_OS::filesize(_filepath.c_str());
			check_file_size(0);
		}
	}
#ifndef WIN32
	if(_log_app & laSyslog)
	{
		_syslog = new ACE_Log_Msg_UNIX_Syslog;
		_syslog->open("gwmain");
	}
#endif
}

KSGLogBackend::~KSGLogBackend()
{
	// empty
	_file_mutex.remove();
	if(_logfile)
	{
		_logfile->close();
		delete _logfile;
		_logfile = NULL;
	}
#ifndef WIN32
	if(_syslog)
	{
		_syslog->close();
		delete _syslog;
	}
#endif
}

int KSGLogBackend::open(const ACE_TCHAR *logger_key)
{
	
	return 0;
}

int KSGLogBackend::close()
{
	return 0;
}

int KSGLogBackend::reset()
{
	return 0;
}

int KSGLogBackend::log(ACE_Log_Record& log_record)
{
	if(log_record.type() < _priority )
		return 0;
	int len;
	ACE_TCHAR msg_data[ACE_Log_Record::MAXVERBOSELOGMSGLEN + 1];
	//ACE_OS::memset(msg_data,0,sizeof msg_data);
	len = ACE_OS::snprintf(msg_data,ACE_Log_Record::MAXVERBOSELOGMSGLEN,"P[%u]F[%s]L[%d]- %s\n"
		,static_cast<unsigned>(ACE_OS::thr_self())
		,ACE_LOG_MSG->file(),ACE_LOG_MSG->linenum(),log_record.msg_data());
	msg_data[len] = '\0';
	log_record.msg_data(msg_data);
	log_record.format_msg(ACE_LOG_MSG->local_host(),ACE_LOG_MSG->flags()
		,msg_data);
	//len = ACE_OS::strlen(msg_data);
	if(_log_app & laStdout)
		ACE_OS::printf(msg_data);
	if(_log_app & laFile)
		log2file(msg_data,len);

#ifndef WIN32
	if(_log_app & laSyslog)
		log2syslog(log_record);
#endif

	return 0;
}

int KSGLogBackend::backup_curr_file()
{
	int ret;
	if(_file_mutex.tryacquire() == -1)
		return -1;
	time_t last = 0;
	int first_index = 0;
	std::string backfile;
	char indx[10] = "";
	int i;
	for(i = 1; i <= _file_max_count; ++i)
	{
		ACE_OS::sprintf(indx,".%d",i);
		backfile = _filepath + indx;
		if(KSGOSUtil::FileExists(backfile.c_str()))
		{
			ACE_stat file_stat;
			ACE_OS::stat(backfile.c_str(),&file_stat);
			if(0 == last)
			{
				last = file_stat.st_mtime;
				first_index = i;
			}
			else if(file_stat.st_mtime < last )
			{
				last = file_stat.st_mtime;
				first_index = i;
			}
			continue;
		}
		break;
	}
	ret = 0;
	if(i > _file_max_count)
	{
		// 删除第一个文件
		ACE_OS::sprintf(indx,".%d",first_index);
		backfile = _filepath + indx;
		if(ACE_OS::unlink(backfile.c_str()))
		{
			ret = -1;
		}
	}
	if(!ret)
	{
		_logfile->flush();
		_logfile->close();
		delete _logfile;
		//  备份
		if(ACE_OS::rename(_filepath.c_str(),backfile.c_str()))
			ret = -1;
		_logfile = new ofstream(_filepath.c_str(),std::ios_base::out|std::ios_base::app);
		if(_logfile->bad())
		{
			ret = -1;
		}
		else
		{
			_file_curr_size = ACE_OS::filesize(_filepath.c_str());
		}
	}
	_file_mutex.release();
	return ret;
}
int KSGLogBackend::check_file_size(long msglen)
{
	if(_file_curr_size > _file_max_size)
	{
		// 备份日志
		backup_curr_file();
	}
	if(msglen <= 0)
		return -1;
	if(_file_mutex.tryacquire() == -1)
		return -1;
	_file_curr_size += msglen;
	_file_mutex.release();
	return 0;
}
void KSGLogBackend::log2file(const ACE_TCHAR *msg,int msglen)
{
	check_file_size(msglen);
	if(_logfile && _logfile->is_open())
	{
		(*_logfile)<<msg<<std::flush;
	}
}

void KSGLogBackend::log2syslog(ACE_Log_Record& log_record)
{
	// TODO : to be implements
#ifndef WIN32
	_syslog->log(log_record);
#endif
}
