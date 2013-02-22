#include "stdafx.h"
#include ".\logfile.h"
#include <stdio.h>
#include <sys/stat.h>
#include <process.h>
#include <direct.h>
#include <share.h>
#include <io.h>

#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#define sh_fopen(a,b,c) _fsopen(a,b,c)

int g_ShowLogLevel = 10000;

CLogFile::CLogFile(char *szLogPath, int fdelay)
{
	if (szLogPath != NULL && szLogPath[0] != '\0')
		strncpy(logpath, szLogPath, sizeof(logpath));
	else
		strcpy(logpath,".");  // 缺省为当前目录下
	
	logpath[sizeof(logpath) - 1] = '\0';

	fp = NULL;
	lastftime = 0;
	flashdelay = fdelay;
	logdate = 0;
	mode = 0;
	filecount = 0;
}

CLogFile::~CLogFile(void)
{
	Close();
}

bool CLogFile::open()
{
	int shflag;
	int len;
	struct tm tmloc;
	char fname[1024];
	close();

	len = strlen(logpath);
	if (logpath[len-1] == PATHMARK)
		logpath[len-1] = '\0';

	time(&lastftime);
	memcpy(&tmloc, localtime(&lastftime), sizeof(tmloc));
	logdate = ((tmloc.tm_year + 1900) * 100 + tmloc.tm_mon + 1) * 100 + tmloc.tm_mday;
//	logdate = ((tmloc.tm_year + 1900) * 100 + tmloc.tm_mon + 1) * 100 + tmloc.tm_mday + tmloc.tm_hour + tmloc.tm_min + tmloc.tm_sec;
//#ifdef SYSLOG
//	sprintf(fname,"%d.log",logdate);
//	openlog(fname,LOG_PID|LOG_PERROR,LOG_USER);
//	return(true);
//#else
	if (access(logpath, 0) != 0)
	{
		MAKEPATH(logpath);
	}

	if (mode)
	{
//#ifdef WIN32
		sprintf(fname, "%s%c%d_%u.log", logpath, PATHMARK, logdate, GetCurrentProcessId());
//#else
//		sprintf(fname,"%s%c%d_%d.log",logpath,PATHMARK,logdate,getpid());
//#endif
	}
	else
	{
		sprintf(fname, "%s%c%d.log", logpath, PATHMARK, logdate);
	}
	/**********************************************************/
	shflag = SH_DENYNO;
	fp = sh_fopen(fname, "a + t", shflag);
	if (fp == NULL)
	{
		fp = sh_fopen(fname, "w + t", shflag);
	}

	return (fp != NULL);
//#endif
}

void CLogFile::close()
{
/*
#ifdef SYSLOG
	closelog();
#else
*/
	if (fp != NULL)
	{
		fclose(fp);
	}
//#endif
	fp = NULL;
	lastftime = time(NULL);
	logdate = 0;
}

void CLogFile::Close()
{
	close();
}

bool CLogFile::Open(char *szLogPath /* = NULL */, int LogFileMode /* = 0 */)
{
	if (szLogPath != NULL && szLogPath[0] != '\0')
		strncpy(logpath, szLogPath, sizeof(logpath) - 1);

	logpath[sizeof(logpath) - 1] = '\0';
	mode = LogFileMode;
	return (open());
}

void CLogFile::ToFlush()
{
	if (fp!=NULL)
	{
		fflush(fp);
		lastftime = time(NULL);
	}
}

void SetLogShowLevel(int logshowlevel)
{
	g_ShowLogLevel = logshowlevel;
}

// overdue按照天数来计算
int CLogFile::RemoveOverdueLogFile(int overdue)
{
	char szPath[1024] = "";
	sprintf(szPath,"%s%c", logpath, PATHMARK);
//	return(RemoveOverdueFile(szPath, ".log", overdue));
	int nfs = 0;
	char szfile[1024] = "";
	time_t odtime;
	if (overdue < 1)
		return 0;
	odtime = time(NULL) - (overdue * 86400);   
	sprintf(szfile, "%s*%s", szPath, ".log");
//#ifdef WIN32
	struct _finddata_t fd;
	int dh;
	dh = _findfirst(szfile, &fd);
	if (dh == -1) 
		return 0;
	do
	{
		if ((odtime > fd.time_write) && strstr(fd.name, ".log") != NULL)
		{
			sprintf(szfile, "%s%s", szPath, fd.name);
			remove(szfile);
			nfs++;
		}
	} while (_findnext(dh, &fd) != -1);
	_findclose(dh);
//#else
	/*
	DIR *dp;
	struct dirent *dirp;
	struct stat fst;
	dp = opendir(path_mark);
	if (dp==NULL) 
		return(0);
	while ((dirp=readdir(dp))!=NULL)
	{
		sprintf(szfile,"%s%s",path_mark,dirp->d_name);
		if (strstr(dirp->d_name,ext)!=NULL 
			&& stat(szfile,&fst)==0 
			&& odtime>fst.st_mtime)
		{
			remove(szfile);
			nfs++;
		}
	}
	closedir(dp);
	*/
//#endif
	return nfs;
}

void CLogFile::WriteLogEx(int level, char *pFormat, ...)
{
	va_list pArg;
	char chMsg[8192] = "";
	int i;
	/*
#ifdef _MT
	CPMUTEX amutex(&m_mutex);
#endif
	*/
	
	struct tm tmloc;
	time_t curtime;
	time(&curtime);
	/*
	memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
	sprintf(chMsg,"%02d-%02d %02d:%02d:%02d ",
		tmloc.tm_mon+1,
		tmloc.tm_mday,
		tmloc.tm_hour,
		tmloc.tm_min,
		tmloc.tm_sec
		);
	*/
	//getfmttime(0,1,chMsg);
	//strcat(chMsg," ");

/*	此处不提供PID和level
	i = strlen(chMsg);
	sprintf(chMsg + i, "PID%d Level%d -- ", getpid(), level);
*/

	i = strlen(chMsg);
	va_start(pArg, pFormat);
	vsprintf(chMsg + i, pFormat, pArg);
	va_end(pArg);
	i = strlen(chMsg);
	if (chMsg[i - 2] != '\n')
		strcat(chMsg, "\n");
	
	if (logdate != ((tmloc.tm_year + 1900) * 100 + tmloc.tm_mon + 1) * 100 + tmloc.tm_mday)
		open();
	
/*
#ifdef SYSLOG
	int slevel;
	if (level<10000)
		slevel = LOG_INFO;
	else
		slevel = LOG_CRIT;
	syslog(slevel|LOG_USER,"%s",chMsg);
#else
*/
	if (fp != NULL)
	{
		fprintf(fp, "%s", chMsg);
		if (curtime - lastftime > flashdelay)
		{
			fflush(fp);
			lastftime = curtime;
		}
	}
//#endif
	/*
	if (level >= g_ShowLogLevel)
		printf("%s", chMsg);
	*/
}
