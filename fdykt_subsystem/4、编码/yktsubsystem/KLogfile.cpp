// KLogfile.cpp: implementation of the KLogfile class.
/** 
 * 模块名					外接子系统
 * 文件名					KLogfile.cpp
 * 文件实现功能				日志功能类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-01
 * 备注
 * $Id: KLogfile.cpp 15 2005-08-22 02:39:12Z cash $
 */

//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KLogfile.h"
#include <fstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KLogfile::~KLogfile()
{
	if(m_logFileStream != NULL)
	{
		m_logFileStream->close();
		delete m_logFileStream;
	}
}
KLogfile::KLogfile():m_IsLogOpen(false),m_logFileStream(NULL)
{
	
}
KLogfile::KLogfile(const char* filename):m_logFileStream()
{
	m_LogFileName = filename;
	OpenLogfile(filename);
}

int KLogfile::OpenLogfile(const char * logfile)
{
	if(m_logFileStream != NULL)
	{
		m_logFileStream->close();
		int state = m_logFileStream->rdstate();
		delete m_logFileStream;
	}
	m_logFileStream = new ofstream(logfile,ios::app|ios::out);
	int state = m_logFileStream->rdstate();
	if(state & ios::failbit)
	{
		return -1;
	}
	m_LogFileName = logfile;
	m_IsLogOpen = true;
	return 0;
}
int KLogfile::CloseLog()
{
	try
	{
		m_logFileStream->close();
		delete m_logFileStream;
		m_logFileStream = NULL;
		m_LogFileName = "";
		m_IsLogOpen = false;
		return 0;
	}
	catch(...)
	{
		return -1;
	}
}
void KLogfile::Flush()
{
	if(m_logFileStream != NULL)
		m_logFileStream->flush();	
}

string KLogfile::GetCurrentTimeString()
{
#ifdef WIN32
	SYSTEMTIME stime;
	char buf[1024] = "";
	GetLocalTime(&stime);
	sprintf(buf,"%d-%.02d-%.02d %.02d:%.02d:%0.2d:%d",
		stime.wYear,stime.wMonth,stime.wDay,stime.wHour,
		stime.wMinute,stime.wSecond,stime.wMilliseconds);
	return string(buf);
#else
	return string;
#endif
}

KLogfile& KLogfile::operator<<(const char* msg)
{
	if(NULL == m_logFileStream)
		return (*this);
	(*m_logFileStream)<<msg<<endl;
	return *this;
}
KLogfile& KLogfile::WriteLog(const char* fmt,...)
{
	int state;
	va_list arg;
	char buf[4096] = "";
	if( NULL == m_logFileStream )
		return (*this);
	va_start(arg,fmt);
	vsprintf(buf,fmt,arg);
	va_end(arg);

	(*m_logFileStream)<<"Time:["<<GetCurrentTimeString()<<"]: "
		<<buf<<endl;
	state = m_logFileStream->rdstate();
	switch(state)
	{
	case ios::goodbit:
		
		break;
	case ios::eofbit:
		break;
	case ios::failbit:
		break;
	case ios::badbit:
		break;
	}
	m_logFileStream->flush();
	return *this;
}
