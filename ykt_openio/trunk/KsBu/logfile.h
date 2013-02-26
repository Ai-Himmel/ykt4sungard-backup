/********************************************************************
	created:	2004/02/13
	created:	13:2:2004   10:16
	filename: 	E:\proj\goldmem\ksbcc\logfile.h
	file path:	E:\proj\goldmem\ksbcc
	file base:	LogFile
	file ext:	h
	author:		CHENYH
	
	purpose:	
      20040405��
      ���ı���־�ļ�����Ϊ����ÿ��һ����־�ļ����Ա��ѯ�ȴ���
*********************************************************************/
// logfile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)
#define AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_
#ifdef _MT   // �����ģ�����ڶ��߳�ϵͳ��ʱ����Ҫ���궨��
#include "mutex.h"
#endif

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class BUPUB_API CLogFile  
{
private:
   FILE *fp;      // ��־�ļ����
   char logpath[256];   // ��־�ļ����·��
   int  logdate;        // ��ǰ��־�ļ�����
   time_t lastftime;
   int flashdelay;      // ˢ����ʱ, ��λ��
   int mode;            // 0:����PID��1:��PID
   int m_FileNumber;  // CYH Added for controlling file length

   int m_WriteLevel;    // 2007-10-31 17:28:54 for disable writing

#ifdef _MT
   CMUTEX m_mutex;   // ������
#endif

private:
	bool open();
	void close();
   
public:
	void SetWriteLevel(int level);
	void ToFlush();
	int RemoveOverdueLogFile(int overdue=30);
	bool Open(char *szLogPath=NULL,int LogFileMode=0);
	void WriteLogEx(int level, char *pFormat, ...);
	void SetFlushDelay(int iFlushDelayInSecond);
	void Close();
	CLogFile(char *szLogPath=NULL,int fdelay=60);
	virtual ~CLogFile();

};

BUPUB_API void SetLogShowLevel(int logshowlevel);

#undef BUPUB_API

//extern int g_ShowLogLevel;
#endif // !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)
