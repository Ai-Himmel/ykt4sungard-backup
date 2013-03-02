#pragma once

class CLogFile
{
private:
	bool open();
	void close();

public:
	void ToFlush();
	int RemoveOverdueLogFile(int overdue = 30);
	bool Open(char *szLogPath = NULL, int LogFileMode = 0);
	void WriteLogEx(int level, char *pFormat, ...);
	void SetFlushDelay(int iFlushDelayInSecond);
	void Close();
	CLogFile(char *szLogPath = NULL, int fdelay = 60);
	virtual ~CLogFile();

private:
	FILE *fp;			 // 日志文件句柄
	char logpath[256];   // 日志文件存放路径
	int  logdate;        // 当前日志文件日期
	time_t lastftime;	 // 上次显示时间
	int flashdelay;      // 刷新延时, 单位秒
	int mode;            // 0:不带PID，1:带PID
	int filecount;		 // 文件计数
/*
#ifdef _MT
	CMUTEX m_mutex;		// 互斥量
#endif
*/
};
