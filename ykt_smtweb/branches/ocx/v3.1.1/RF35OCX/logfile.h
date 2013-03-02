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
	FILE *fp;			 // ��־�ļ����
	char logpath[256];   // ��־�ļ����·��
	int  logdate;        // ��ǰ��־�ļ�����
	time_t lastftime;	 // �ϴ���ʾʱ��
	int flashdelay;      // ˢ����ʱ, ��λ��
	int mode;            // 0:����PID��1:��PID
	int filecount;		 // �ļ�����
/*
#ifdef _MT
	CMUTEX m_mutex;		// ������
#endif
*/
};
