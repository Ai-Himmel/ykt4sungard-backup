// LogFile.cpp: implementation of the CLogFile class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "logfile.h"
#include "mypub.h"

#include <sys/stat.h>

#ifdef WIN32
#include <process.h>
#include <direct.h>
#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK  '/'
#define MAKEPATH(a) mkdir(a,0777)
#endif


int g_ShowLogLevel=10000;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogFile::CLogFile(char *szLogPath,int fdelay) {
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

CLogFile::~CLogFile() {
#ifdef SYSLOG
    closelog();
#endif
    Close();
}

void CLogFile::Close() {
#ifdef _MT
    CPMUTEX amutex(&m_mutex);
#endif
    close();
}

bool CLogFile::Open(char *szLogPath, int LogFileMode) {
#ifdef _MT
    CPMUTEX amutex(&m_mutex);
#endif
    if (szLogPath!=NULL && szLogPath[0]!='\0')
        strncpy(logpath,szLogPath,sizeof(logpath));
    logpath[sizeof(logpath)-1]='\0';
    mode = LogFileMode;
    return(open());
}


void CLogFile::SetFlushDelay(int iFlushDelayInSecond) {
    flashdelay = iFlushDelayInSecond;
}

void CLogFile::WriteLogEx(int level, char *pFormat, ...) {
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
    if (chMsg[i-2]!='\n') {
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
    if (fp!=NULL) {
        fprintf(fp,"%s",chMsg);
        if (curtime-lastftime>flashdelay) {
            fflush(fp);
            lastftime = curtime;
        }
    }
#endif
    if (level>=g_ShowLogLevel)
        printf("%s",chMsg);
}



void CLogFile::close() {
#ifdef SYSLOG
    closelog();
#else
    if (fp!=NULL) {
        fclose(fp);
    }
#endif
    fp = NULL;
    lastftime = time(NULL);
    logdate = 0;
}

bool CLogFile::open() {
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
    if (access(logpath,0)!=0) {
        MAKEPATH(logpath);
    }

    /* ****** Updated by CHENYH at 2005-11-17 16:28:25 ****** */
    if (mode) {
#ifdef WIN32
        sprintf(fname,"%s%c%d_%u.log",logpath,PATHMARK,logdate,GetCurrentProcessId());
#else
        sprintf(fname,"%s%c%d_%d.log",logpath,PATHMARK,logdate,getpid());
#endif
    } else {
        sprintf(fname,"%s%c%d.log",logpath,PATHMARK,logdate);
    }
    /**********************************************************/
    shflag = SH_DENYNO;
    fp = sh_fopen(fname,"a+t",shflag);
    if (fp==NULL) {
        fp = sh_fopen(fname,"w+t",shflag);
    }
    return(fp!=NULL);
#endif
}

int CLogFile::RemoveOverdueLogFile(int overdue) {
    char szpath[1024];
#ifdef SYSLOG
    return(-1);
#endif
    sprintf(szpath,"%s%c",logpath,PATHMARK);
    return(RemoveOverdueFile(szpath,".log",overdue));
}

void CLogFile::ToFlush() {
#ifdef _MT
    CPMUTEX amutex(&m_mutex);
#endif
#ifdef SYSLOG
#else
    if (fp!=NULL) {
        fflush(fp);
        lastftime = time(NULL);
    }
#endif
}


void SetLogShowLevel(int logshowlevel) {
    g_ShowLogLevel = logshowlevel;
}
