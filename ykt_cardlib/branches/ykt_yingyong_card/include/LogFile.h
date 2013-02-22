// logfile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)
#define AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_
#ifdef _MT   // 如果本模块用于多线程系统的时候，需要本宏定义
#include "mutex.h"
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLogFile  
{
private:
   FILE *fp;      // 日志文件句柄
   char logpath[256];   // 日志文件存放路径
   int  logdate;        // 当前日志文件日期
   time_t lastftime;
   int flashdelay;      // 刷新延时, 单位秒
   int mode;            // 0:不带PID，1:带PID

#ifdef _MT
   CMUTEX m_mutex;   // 互斥量
#endif

private:
	bool open();
	void close();
   
public:
	CLogFile(char *szLogPath = NULL, int fdelay = 60);
	virtual ~CLogFile();
	void ToFlush();
	int	 RemoveOverdueLogFile(int overdue = 30);
	int  RemoveOverdueFile(char *path_mark, char *ext, int overdue);
	void OnRemoveOverdueFile(char *path_mark, char *ext, int overdue, char *file);
	char *getfmttime(void *ptm,int fmttype,char *outstr);
	bool Open(char *szLogPath = NULL, int LogFileMode = 0);
	void WriteLogEx(int level, char *pFormat, ...);
	void SetFlushDelay(int iFlushDelayInSecond);
	void Close();
};
 
void SetLogShowLevel(int logshowlevel);

//extern int g_ShowLogLevel;
#endif // !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)
