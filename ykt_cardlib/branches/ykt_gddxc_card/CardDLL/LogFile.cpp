// LogFile.cpp: implementation of the CLogFile class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include "LogFile.h"
#include <time.h>
//#include "mypub.h"

#ifdef WIN32
#include <process.h>
#include <direct.h>
#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#include <share.h>
#define sh_fopen(a,b,c) _fsopen(a,b,c)
#include <io.h>
#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK  '/'
#define MAKEPATH(a) mkdir(a,0777)
#define SH_DENYNO    0x40
#define SH_DENYWR    0x20
#define sh_fopen(a,b,c) fopen(a,b)
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif


int g_ShowLogLevel=10000;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogFile::CLogFile(char *szLogPath,int fdelay)
{
   if (szLogPath!=NULL && szLogPath[0]!='\0')
      strncpy(logpath,szLogPath,sizeof(logpath));
   else
      strcpy(logpath,".");  // 缺省为当前目录下
   logpath[sizeof(logpath)-1]='\0';

   fp = NULL;
   lastftime = 0;
   flashdelay = fdelay;
   logdate = 0;
   mode = 0;
}

CLogFile::~CLogFile()
{
#ifdef SYSLOG
   closelog();
#endif 
   Close();
}

void CLogFile::Close()
{
#ifdef _MT
   CPMUTEX amutex(&m_mutex);
#endif
   close();
}

bool CLogFile::Open(char *szLogPath, int LogFileMode)
{
#ifdef _MT
   CPMUTEX amutex(&m_mutex);
#endif
   if (szLogPath!=NULL && szLogPath[0]!='\0')
      strncpy(logpath,szLogPath,sizeof(logpath));
   logpath[sizeof(logpath)-1]='\0';
   mode = LogFileMode;
   return(open());
}


void CLogFile::SetFlushDelay(int iFlushDelayInSecond)
{
   flashdelay = iFlushDelayInSecond;
}

void CLogFile::WriteLogEx(int level, char *pFormat, ...)
{
   va_list pArg;
   char chMsg[8192];
   int i;
#ifdef _MT
   CPMUTEX amutex(&m_mutex);
#endif
   struct tm tmloc;
   time_t curtime;
   time(&curtime);
   memcpy(&tmloc,localtime(&curtime),sizeof(tmloc));
   sprintf(chMsg,"%02d/%02d %02d:%02d:%02d ",
      tmloc.tm_mon+1,
      tmloc.tm_mday,
      tmloc.tm_hour,
      tmloc.tm_min,
      tmloc.tm_sec
      );
   //getfmttime(0,1,chMsg);
   //strcat(chMsg," ");
   i = strlen(chMsg);
   sprintf(chMsg+i,"%d Level%d -- ",getpid(),level);
   i = strlen(chMsg);
   va_start(pArg,pFormat);
   vsprintf(chMsg+i,pFormat,pArg);
   va_end(pArg);
   i = strlen(chMsg);
   if (chMsg[i-2]!='\n')
   {
      strcat(chMsg,"\n");
   }
   if (logdate!=((tmloc.tm_year+1900)*100+tmloc.tm_mon+1)*100+tmloc.tm_mday)
      open();
#ifdef SYSLOG
   int slevel;
   if (level<10000)
      slevel = LOG_INFO;
   else
      slevel = LOG_CRIT;
   syslog(slevel|LOG_USER,"%s",chMsg);
#else
   if (fp!=NULL)
   {
      fprintf(fp,"%s",chMsg);
      if (curtime-lastftime>flashdelay)
      {
         fflush(fp);
         lastftime = curtime;
      }
   }
#endif
   if (level>=g_ShowLogLevel)
      printf("%s",chMsg);
}

void CLogFile::close()
{
#ifdef SYSLOG
   closelog();
#else
   if (fp!=NULL)
   {
      fclose(fp);
   }
#endif
   fp = NULL;
   lastftime = time(NULL);
   logdate = 0;
}

bool CLogFile::open()
{
   int shflag;
   int len;
   struct tm tmloc;
   char fname[1024];
   close();

   len = strlen(logpath);
   if (logpath[len-1]==PATHMARK)
      logpath[len-1]='\0';

   time(&lastftime);
   memcpy(&tmloc,localtime(&lastftime),sizeof(tmloc));
   logdate = ((tmloc.tm_year+1900)*100+tmloc.tm_mon+1)*100+tmloc.tm_mday;
#ifdef SYSLOG
   sprintf(fname,"%d.log",logdate);
   openlog(fname,LOG_PID|LOG_PERROR,LOG_USER);
   return(true);
#else
   if (access(logpath,0)!=0)
   {
      MAKEPATH(logpath);
   }

   if (mode)
   {
#ifdef WIN32
      sprintf(fname,"%s%c%d_%u.log",logpath,PATHMARK,logdate,GetCurrentProcessId());
#else
      sprintf(fname,"%s%c%d_%d.log",logpath,PATHMARK,logdate,getpid());
#endif
   }
   else
   {
      sprintf(fname,"%s%c%d.log",logpath,PATHMARK,logdate);
   }
   
   shflag = SH_DENYNO;
   fp = sh_fopen(fname,"a+t",shflag);
   if (fp==NULL)
   {
      fp = sh_fopen(fname,"w+t",shflag);
   }
   return(fp!=NULL);
#endif
}

int CLogFile::RemoveOverdueLogFile(int overdue)
{
   char szpath[1024];
#ifdef SYSLOG
   return(-1);
#endif   
   sprintf(szpath,"%s%c",logpath,PATHMARK);
   return(RemoveOverdueFile(szpath,".log",overdue));
}

int CLogFile::RemoveOverdueFile(char *path_mark, char *ext, int overdue)
{
	int nfs=0;
	char szfile[2048];  // 2006-6-20 10:29:54
	time_t odtime;
	if (overdue<1)
		return(0);
	if (ext[0]=='\0'||memcmp(ext,".*",2)==0)
		return(0); // 防止错误删除文件  
	odtime = time(NULL)-(overdue*86400);   
	sprintf(szfile,"%s*%s",path_mark,ext);
#ifdef WIN32
	struct _finddata_t fd;
	int dh;
	dh = _findfirst(szfile,&fd);
	if (dh==-1) 
		return(0);
	do
	{
		if ((odtime>fd.time_write) && strstr(fd.name,ext)!=NULL)
		{
			sprintf(szfile,"%s%s",path_mark,fd.name);
			remove(szfile);
			OnRemoveOverdueFile(path_mark,ext,overdue,szfile);
			nfs++;
		}
	} while (_findnext(dh,&fd)!=-1);
	_findclose(dh);
#else
	DIR *dp;
	struct dirent *dirp;
	struct stat fst;
	dp = opendir(path_mark);
	if (dp == NULL) 
		return(0);
	while ((dirp = readdir(dp)) != NULL)
	{
		sprintf(szfile,"%s%s",path_mark,dirp->d_name);
		if (strstr(dirp->d_name,ext)!=NULL 
			&& stat(szfile,&fst)==0 
			&& odtime>fst.st_mtime)
		{
			remove(szfile);
			OnRemoveOverdueFile(path_mark,ext,overdue,szfile);
			nfs++;
		}
	}
	closedir(dp);
#endif
	return(nfs);
}

void CLogFile::OnRemoveOverdueFile(char *path_mark, char *ext, int overdue, char *file)
{
	FILE *fp;
	fp = fopen("RMFile.lst","a+t");				// 写日志将清理的文件记录下来
	if (fp!=NULL)
	{
		fprintf(fp,
			"%s: rm <%s> where path=<%s> ext=<%s> overdue=%d\n",
			getfmttime(NULL,1,NULL),
			file, path_mark, ext, overdue
			);
		fclose(fp);
	}
}

void CLogFile::ToFlush()
{
#ifdef _MT
   CPMUTEX amutex(&m_mutex);
#endif
#ifdef SYSLOG
#else
   if (fp!=NULL)
   {
      fflush(fp);
      lastftime = time(NULL);
   }
#endif
}

char *CLogFile::getfmttime(void *ptm,int fmttype,char *outstr)
{
	static char tstr[80];
	struct tm tmloc;
	time_t timet;

	if (ptm==NULL)
	{
		ptm = &timet;
		time(&timet);
	}
	else
	{
		memcpy(&timet,ptm,sizeof(timet));
	}
	if (outstr==NULL)
	{
		outstr = tstr;
	}
	//localtime_r(&tm,&tmloc);
	memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
	if (fmttype==0)
	{
		// %H:%M:%S:
		strftime(outstr,79,"%H:%M:%S",&tmloc);
	}
	else if (fmttype==1)
	{
		// %m/%d-%H:%M:%S
		strftime(outstr,79,"%m/%d %H:%M:%S",&tmloc);
	}
	else if (fmttype==2)
	{
		strftime(outstr,79,"%Y/%m/%d %H:%M:%S",&tmloc);
	}
	else if (fmttype==3)
	{
		strftime(outstr,79,"%Y%m%d",&tmloc);
	}
	else if (fmttype==4)
	{
		strftime(outstr,79,"%H%M%S",&tmloc);
	}
	else 
	{
		strftime(outstr,79,"%Y%m%d%H%M%S",&tmloc);
	}
	return(outstr);
}

void SetLogShowLevel(int logshowlevel)
{
   g_ShowLogLevel = logshowlevel;
}