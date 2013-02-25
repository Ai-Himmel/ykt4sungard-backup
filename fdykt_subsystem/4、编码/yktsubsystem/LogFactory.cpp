// LogFactory.cpp: implementation of the KLogFactory class.
/** 
 * 模块名					外接子系统
 * 文件名					LogFactory.cpp
 * 文件实现功能				日志类工厂方法类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-01
 * 备注
 * $Id: LogFactory.cpp 15 2005-08-22 02:39:12Z cash $
 */
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogFactory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
KLogFactory* KLogFactory::ms_Instance = NULL;
KLogFactory::KMutex KLogFactory::ms_Mutex;
string KLogFactory::ms_LogFileName("applog");
string KLogFactory::ms_LogDir("");

KLogFactory::KLogFactory()
{
	m_CurrentDate = "2000-01-01";
}

KLogFactory::~KLogFactory()
{
	m_logfile.CloseLog();
}

KLogFactory* KLogFactory::GetInstance()
{
	if(ms_Mutex.Lock() == 0)
	{
		if(NULL == ms_Instance)
		{
			ms_Instance = new KLogFactory();
		}
		ms_Mutex.UnLock();
	}
	return ms_Instance;
}

void KLogFactory::Release()
{
	if(ms_Mutex.Lock() == 0)
	{
		if(NULL != ms_Instance)
		{
			delete ms_Instance;
			ms_Instance = NULL;
		}
		ms_Mutex.UnLock();
	}
}
int KLogFactory::RenameFile(const std::string& timestampe)
{
	string newname = ms_LogDir;
	newname.append("/").append(ms_LogFileName).append(".")
		.append(timestampe);
	string oldname = ms_LogDir;
	oldname.append("/").append(ms_LogFileName);
	return rename(oldname.c_str(),newname.c_str());
}
void KLogFactory::GenLogFileName(string& filename,
		const string& timestampe)
{
	filename.append(ms_LogDir).append("/").append(ms_LogFileName)
		.append("_").append(timestampe).append(".txt");
}
void KLogFactory::SetLogFileDirectory(const std::string& path)
{
	ms_LogDir = path;
}

KLogfile* KLogFactory::GetLogSys()
{
	static long tickCount = GetTickCount();
	string NowDate = GetCurrentDateString();
	if( NowDate != m_CurrentDate)
	{
		// 使用新的日志文件
		m_logfile.CloseLog();
		string newfile("");
		GenLogFileName(newfile,NowDate);
		m_logfile.OpenLogfile(newfile.c_str());
		m_CurrentDate = NowDate;
	}
	else
	{
		long currentTick = GetTickCount();
		// 每十分钟Flush一次
		if(currentTick - tickCount > 600000)
		{
			m_logfile.Flush();
			tickCount = currentTick;
		}
	}
	return &m_logfile;
}

int KLogFactory::KMutex::Lock()
{
	try
	{
		EnterCriticalSection(&m_mutex);
		return 0;
	}
	catch(...)
	{
		return -1;
	}
}
int KLogFactory::KMutex::UnLock()
{
	try
	{
		LeaveCriticalSection(&m_mutex);
		return 0;
	}
	catch(...)
	{
		return -1;
	}
}

KLogFactory::KMutex::KMutex()
{
#ifdef WIN32
	InitializeCriticalSection(&m_mutex);
#else

#endif
}

KLogFactory::KMutex::~KMutex()
{
#ifdef WIN32
	DeleteCriticalSection(&m_mutex);
#else
#endif
}

string KLogFactory::GetCurrentDateString()
{
#ifdef WIN32
	char buf[128] = "";
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	sprintf(buf,"%d-%.02d-%.02d",stime.wYear,stime.wMonth,stime.wDay);
	return string(buf);
#else
#endif
}
long KLogFactory::GetTickCount()
{
#ifdef WIN32
	return ::GetTickCount();
#else
#endif	
}
