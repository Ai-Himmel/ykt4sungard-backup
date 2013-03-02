/********************************************************************
	created:	2004/03/15
	created:	15:3:2004   20:18
	filename: 	E:\proj\goldmem\ksbcc\KSLog.cpp
	file path:	E:\proj\goldmem\ksbcc
	file base:	KSLog
	file ext:	cpp
	author:		CHENYH
	
	purpose:	作为一种Kingstar内部调试跟踪的能够包含数据日志的日志文件格式的操作，与
            pen他们编写的日志显示程序兼容，并且能够记录到LINUX等平台上。
            
*********************************************************************/
// KSLog.cpp: implementation of the CKSLog class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "KSLog.h"
#include "sysgvars.h"


#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void	AddSlash(char *path)
{
	int len;

	len = strlen(path);
	if (len == 0)
   {
      strcpy(path,".");
   }
	else
	{
		if (path[len-1]=='\\'||path[len-1]=='/')
			return;
	}
#ifdef WIN32
   strcat(path,"\\");
#else
   strcat(path,"/");
#endif
}

void	MakePath(char *path)
{
	char rpath[MAX_PATH];
	int i,l;
	AddSlash(path);
	l = strlen(path);
	for (i=0;i<l;i++) 
	{
		if (path[i]=='\\'||path[i]=='/') 
		{
			memcpy(rpath,path,i);
			rpath[i]='\0';
			if (access(rpath,0)!=0) 
#ifdef WIN32
            mkdir(rpath);
#else
            mkdir(rpath,0777);
#endif
		}
	}
}


CKSLog::CKSLog()
{
   Init();
}

CKSLog::~CKSLog()
{
	CloseFile();
}

bool CKSLog::SetFileMode(char *pszFilePath, char *pszFileHead, char *pszFileExt, unsigned int dwFileOpt)
{
	m_dwFileOpt =  dwFileOpt;
	if(strlen(pszFilePath) >= sizeof(m_szFilePath) 
		|| strlen(pszFileHead) >= sizeof(m_szFileHead)
		|| strlen(pszFileExt) >= sizeof(m_szFileExt))
	{
		return false;
	}
	strcpy(m_szFilePath,	pszFilePath);
	strcpy(m_szFileHead,	pszFileHead);
	strcpy(m_szFileExt,		pszFileExt);
	
	char	szTmp[12]	= "";
	char	szDate[12]	= "";

	if(m_dwFileOpt & LOG_FILEYEAR)
	{
		sprintf(szTmp, "%04d", g_Vars.g_iToday/10000);
		strcat(szDate, szTmp);
	}
	if(m_dwFileOpt & LOG_FILEMONTH)
	{
		sprintf(szTmp, "%02d", (g_Vars.g_iToday%10000)/100);
		strcat(szDate, szTmp);
	}
	if(m_dwFileOpt & LOG_FILEDAY)
	{
		sprintf(szTmp, "%02d", g_Vars.g_iToday%100);
		strcat(szDate, szTmp);
	}
	if(strcmp(m_szFileDate, szDate) == 0)
	{
		return true;
	}
	else
	{
		strcpy(m_szLogFile, "");
		strcpy(m_szFileDate, szDate);
	}

	strcpy(m_szLogFile, m_szFilePath);
	MakePath(m_szLogFile);

	strcat(m_szLogFile, m_szFileHead);
	strcat(m_szLogFile, m_szFileDate);
	strcat(m_szLogFile, m_szFileExt);
	
	return true;

}

void CKSLog::Init()
{
	//	读写控制
	m_fp		= NULL;
   
	m_nOpenMode	= LOG_OPENNODEFINE;
	//	文件名命名方式
	m_dwFileOpt	= 0;
	strcpy(m_szFileExt, "");
	strcpy(m_szFileHead, "");
	strcpy(m_szFilePath, "");
	strcpy(m_szLogFile, "");
	//	文件信息
	memset(&m_stHead, 0, sizeof(m_stHead));
	m_stHead.stInfo.wVer = 100;
	strcpy(m_stHead.stInfo.szCompany, COMPANYNAME);
	strcpy(m_stHead.stInfo.szProduct, PRODUCTNAME);
	strcpy(m_stHead.stInfo.szPassword, "1234567890");	
	int i;
	for(i=0;i<(int)sizeof(m_stHead.stInfo.szPassword)-1;i++)
	{
		unsigned int dwTmp;
		char	chTmp;
		dwTmp = GetTickCount();
		chTmp = (char)((dwTmp%90) + 32);
		m_stHead.stInfo.szPassword[i] = chTmp;
		mysleep(chTmp%10);
	}
	m_stHead.stInfo.szPassword[i] = 0;
   ST_LOGFILEAPP *pApp = m_stHead.stApp;
	for(i=0;i<LOG_APPMAXCOUNT;i++)
	{
		pApp->nReserve = LOG_APPWRITE;
      //memcpy(&(m_stHead.stApp[i].nReserve),&ltype,sizeof(short));
	}
	//	设置文件头中固定的信息
	m_stHead.stInfo.dwHeadLen = (unsigned int)(sizeof(m_stHead));
	m_stHead.stInfo.dwValidLen = m_stHead.stInfo.dwHeadLen;

	//	系统日志
	AddAppName(LOG_APPSYSID, LOG_APPSYSNAME);
	AddAppName(LOG_APPPACKID, LOG_APPPACKNAME);
	AddAppName(LOG_APPDATAID, LOG_APPDATANAME);

}

bool CKSLog::AddAppName(short nAppID, const char *pszAppName)
{
	if(nAppID < 0 )
	{
		ASSERT(false);
		return false;
	}
	if((int)strlen(pszAppName) >= LOG_APPMAXNAME)
	{
		
		return false;		//	AppName is too long
	}
	
   ST_LOGFILEAPP *pApp;
   pApp = m_stHead.stApp;
	for(int i=0;i<m_stHead.stInfo.nAppCount;i++,pApp++)
	{
		if(pApp->nAppID == nAppID)
		{
			if(strcmp(pApp->szAppName, pszAppName) == 0)
			{
				pApp->nReserve = LOG_APPWRITE;
				return true;
			}
			else
				return false;
		}
	}

	if (m_stHead.stInfo.nAppCount>=LOG_APPMAXCOUNT)
		return false;

   pApp = m_stHead.stApp+m_stHead.stInfo.nAppCount;

/* ****** Updated by CHENYH at 2004-4-16 17:10:40 ****** 
	m_stHead.stApp[m_stHead.stInfo.nAppCount].nAppID = nAppID;
	m_stHead.stApp[m_stHead.stInfo.nAppCount].nReserve = LOG_APPWRITE;
	strcpy(m_stHead.stApp[m_stHead.stInfo.nAppCount].szAppName, pszAppName);
*/
   pApp->nAppID = nAppID;
   pApp->nReserve = LOG_APPWRITE;
   strcpy(pApp->szAppName,pszAppName);
	m_stHead.stInfo.nAppCount++;
	SaveFileHead(true);
	return true;

}

bool CKSLog::SaveFileHead(bool bForceSave)
{

	if(m_fp == NULL)
	{
		return false;
	}

	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
	
	if (bForceSave==false) 
   {
		return true;
	}

	int  nFileOffset = ftell(m_fp);


/* ****** Updated by CHENYH at 2004-3-31 22:02:09 ****** 
   防止是否在别的平台中，如下赋值会有问题？
	ST_LOGHEAD TmpHead = m_stHead;
*/
   ST_LOGHEAD TmpHead;
   memcpy(&TmpHead,&m_stHead,sizeof(ST_LOGHEAD));

	char	szFilePassword[12];
	char	szCryptPassword[12];
	//memset(szFilePassword, 0, sizeof(szFilePassword));
	strcpy(szFilePassword, m_stHead.stInfo.szPassword);
   if (ntohs(1)==1)
   {
      ReverseLogHead(&m_stHead);
   }
	Crypt((char*)&m_stHead, sizeof(m_stHead), szFilePassword);
	
	//memset(szCryptPassword, 0, sizeof(szCryptPassword));
	strcpy(szCryptPassword, CRYPTPASSWORD);
	Crypt(szFilePassword, sizeof(szFilePassword), szCryptPassword);
	memcpy(m_stHead.stInfo.szPassword, szFilePassword, sizeof(szFilePassword));
	fseek(m_fp, 0, SEEK_SET);
	fwrite(&m_stHead, sizeof(m_stHead), 1, m_fp);
	fflush(m_fp);

/* ****** Updated by CHENYH at 2004-3-31 22:03:26 ****** 
	m_stHead = TmpHead;		//	ReadFileHead();
*/
   memcpy(&m_stHead,&TmpHead,sizeof(ST_LOGHEAD));

	fseek(m_fp, nFileOffset, SEEK_SET);
	return true;
}

bool CKSLog::Crypt(char *pszOld, int nLen, char *pszPassword)
{
	if(pszOld == NULL)
		return false;
	if(nLen <= 0)
		return false;
	int   nPassLen = strlen(pszPassword);
	if(nPassLen == 0)
		return false;
	
	int	i;
	for(i=0;i<nLen ;i++)
	{
		pszOld[i] = pszOld[i] ^ pszPassword[i%nPassLen];
	}
	return true;
}

bool CKSLog::OpenLogFile(const char *szFileName)
{
	if (szFileName!=NULL && szFileName[0]!='\0')
	{
		m_nOpenMode = LOG_OPENFORREAD;
		strcpy(m_szLogFile, szFileName);
	}
	else
	{
		m_nOpenMode = LOG_OPENFORWRITE;
	}
	return OpenFile();   
}

bool CKSLog::OpenFile()
{
	if(!strlen(m_szLogFile))
	{
		return false;
	}
	if(m_fp != NULL)
	{
		return false;
	}

 	if(access(m_szLogFile, 0)== -1 && m_nOpenMode == LOG_OPENFORWRITE)
	{
		m_fp = sh_fopen(m_szLogFile, "ab+",SH_DENYNO);
		if(m_fp != NULL)
		{
			fclose(m_fp);
			m_fp = sh_fopen(m_szLogFile, "rb+",SH_DENYNO);
			ResizeFile();
			SaveFileHead(true);
			fclose(m_fp);
		}
		else
		{
			return false;
		}
	}
	
	//m_fp = _fsopen(m_szLogFile, "rb+", _SH_DENYWR);
	if (m_nOpenMode == LOG_OPENFORWRITE)
		m_fp = sh_fopen(m_szLogFile,"rb+",SH_DENYNO);
	else
		m_fp = sh_fopen(m_szLogFile,"rb",SH_DENYNO);

	if(m_fp != NULL)
	{
		ReadFileHead();
		if(m_stHead.stInfo.dwTotalLen < m_stHead.stInfo.dwValidLen
			|| m_stHead.stInfo.dwHeadLen != sizeof(m_stHead)
			|| m_stHead.stInfo.wVer != 100)
		{
			m_nOpenMode = LOG_OPENNODEFINE; //  防止误写别人的文件
			CloseLogFile();
			return false;
		}
		if(strcmp(m_stHead.stInfo.szCompany, COMPANYNAME)
			|| strcmp(m_stHead.stInfo.szProduct, PRODUCTNAME))
		{
			m_nOpenMode = LOG_OPENNODEFINE; //  防止误写别人的文件
			CloseLogFile();
			return false;
		}
	}
	else
	{
		return false;
	}

	fseek(m_fp, m_stHead.stInfo.dwValidLen, SEEK_SET);
	WriteLog(0, "启动日志。");
	return true;
}

bool CKSLog::ResizeFile()
{
	if(m_fp == NULL)
	{
		return false;
	}
	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
	int		nFileOffset = ftell(m_fp);

	fseek(m_fp, 0, SEEK_END);
   char p[LOG_FILEBLOCK];
	memset(p, 0, LOG_FILEBLOCK);
	int nRet = fwrite(p, LOG_FILEBLOCK, 1, m_fp);
	fflush(m_fp);
	fseek(m_fp, nFileOffset, SEEK_SET);
	
	if(nRet)
	{
		m_stHead.stInfo.dwTotalLen += LOG_FILEBLOCK;
		return true;
	}
	else
	{
		return false;
	}
}

bool CKSLog::ReadFileHead()
{
	if(m_fp == NULL)
	{
		return false;
	}
	char	szFilePassword[12];
	char	szCryptPassword[12];
	strcpy(szCryptPassword, CRYPTPASSWORD);
	fseek(m_fp, 0, SEEK_SET);
	fread(&m_stHead, sizeof(ST_LOGHEAD), 1, m_fp);
	fseek(m_fp, m_stHead.stInfo.dwValidLen, SEEK_SET);
	//memset(szFilePassword, 0, sizeof(szFilePassword));
	memcpy(szFilePassword, m_stHead.stInfo.szPassword, sizeof(szFilePassword));
	Crypt(szFilePassword, sizeof(szFilePassword), szCryptPassword);
	Crypt((char*)&m_stHead, sizeof(m_stHead), szFilePassword);

   if (ntohs(1)==1)
   {
      ReverseLogHead(&m_stHead);
   }

	memcpy(m_stHead.stInfo.szPassword, szFilePassword, sizeof(szFilePassword));
	//strcpy(m_stHead.stInfo.szPassword, szFilePassword);
   ST_LOGFILEAPP *pApp = m_stHead.stApp;
	for(int i=0;i<LOG_APPMAXCOUNT;i++,pApp++)
	{
		pApp->nReserve = LOG_APPWRITE;
	}
	return true;
}

void CKSLog::CloseLogFile()
{
	CloseFile();
	Init();
}

void CKSLog::CloseFile()
{
   if(m_fp != NULL)
   {
      WriteLog(0, "关闭日志。");
#ifdef _MT
      m_mutex.Lock();
#endif
      SaveFileHead(true);
      fclose(m_fp);
      m_fp = NULL;
#ifdef _MT
      m_mutex.UnLock();
#endif
   }
}

bool CKSLog::WriteLog(short nAppID, char *pMsg, ...)
{
	if(m_fp == NULL)
	{
		return false;
	}
	if(nAppID < 0 || nAppID == LOG_APPPACKID || nAppID == 12 || nAppID == 13)
	{
		return false;
	}
	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
	int	i;
   ST_LOGFILEAPP *pApp = m_stHead.stApp;
	for(i=0;i<LOG_APPMAXCOUNT;i++,pApp++)
	{
		if(pApp->nAppID == nAppID)
		{
			if(pApp->nReserve == LOG_APPREAD)
			{
				return true;
			}
			else
			{
				break;
			}
		}
	}
	if(i == LOG_APPMAXCOUNT)
	{
		return false;
	}
	
#ifdef _MT
   m_mutex.Lock();
#endif

	//	在程序运行超过一天的时候可以按新日期重新写入日志文件
	CheckFileName();

	char	szTmpBuf[LOG_MAXLINE]="";
	short	nTmpLen = 0;

	va_list Marker;
	va_start(Marker, pMsg);
	nTmpLen = vsprintf(szTmpBuf, pMsg, Marker);
	va_end(Marker);

   bool bRtn=WriteToFile(nAppID, szTmpBuf, nTmpLen);
	if(bRtn)
   {
	   // 修改文件头
	   SaveFileHead();
   }
	
#ifdef _MT
   m_mutex.UnLock();
#endif
   return(bRtn);
}

void CKSLog::CheckFileName()
{
	char szOldLogFile[MAX_PATH];
	strcpy(szOldLogFile, m_szLogFile);

	SetFileMode(m_szFilePath, m_szFileHead, m_szFileExt, m_dwFileOpt);
	if (strcmp(szOldLogFile, m_szLogFile) && m_fp) {

		SaveFileHead(true);
		fclose(m_fp); m_fp = NULL;
		unlink(m_szLogFile);
		m_fp = sh_fopen(m_szLogFile, "ab+",SH_DENYNO);
		if(m_fp != NULL)
		{
			fclose(m_fp);
			m_fp = sh_fopen(m_szLogFile, "rb+",SH_DENYNO);
			m_stHead.stInfo.dwHeadLen = sizeof(m_stHead);
			m_stHead.stInfo.dwValidLen = m_stHead.stInfo.dwHeadLen;
			m_stHead.stInfo.dwTotalLen = 0;
			m_stHead.stInfo.dwRecordCount = 0;
			m_stHead.stInfo.dwPackCount = 0;
			ResizeFile();
			SaveFileHead(true);
			fseek(m_fp, m_stHead.stInfo.dwValidLen, SEEK_SET);
		}
	}
}

bool CKSLog::WriteToFile(short nAppID, void *pBuf, short nBufLen)
{
	if(m_fp == NULL || pBuf == NULL || nBufLen <= 0)
	{
		return false;
	}
	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
	
	for(;;)
	{
		if(m_stHead.stInfo.dwTotalLen >= m_stHead.stInfo.dwValidLen)
		{
			if((m_stHead.stInfo.dwTotalLen - m_stHead.stInfo.dwValidLen) > (unsigned int)(nBufLen+LOG_SIZEOFLOGHEAD+LOG_SIZEOFSHORT))
			{
				//TRACE("resize total:%d  valid:%d \n", m_stHead.stInfo.dwTotalLen, m_stHead.stInfo.dwValidLen);
				break;
			}
			else
			{
				if(ResizeFile() == false)
					return false;
			}
		}
		else
		{
			ASSERT(false);
			return false;
		}
	}
	//TRACE("total:%d  valid:%d \n", m_stHead.stInfo.dwTotalLen, m_stHead.stInfo.dwValidLen);
	//	预留两个学节来存储这一记录的长度
	char	szTmpBuf[LOG_MAXLINE]="";
//	char	szDate[LOG_SIZEOFDATE];
	short	nTmpLen = 0, nLen = 0;

	//	写日志长度
	nLen = nBufLen + LOG_SIZEOFLOGHEAD; 
	if(nBufLen > LOG_MAXLINE)
	{		
		nBufLen = LOG_MAXLINE;
	}
	memcpy(szTmpBuf, &nLen, LOG_SIZEOFSHORT);	
	nTmpLen += LOG_SIZEOFSHORT;
	
	//	写应用ID
	memcpy(szTmpBuf+nTmpLen, &nAppID, LOG_SIZEOFSHORT);
	nTmpLen += LOG_SIZEOFSHORT;


   /* ****** Updated by CHENYH at 2004-4-6 17:02:07 ****** 
      应pen要求，能够支持类似IBM机器的字序：
   */
   if (ntohs(1)==1)
   {
      reverse(szTmpBuf,sizeof(nLen));
      reverse(szTmpBuf+sizeof(nLen),sizeof(nAppID));
   }
   

	//	写系统时间,先把系统时间写到日志里
   sprintf(szTmpBuf+nTmpLen,"%08d %02d:%02d:%02d",
      g_Vars.g_iToday,
      g_Vars.g_iHhmmss/10000,
      (g_Vars.g_iHhmmss/100)%100,
      g_Vars.g_iHhmmss%100
      );
	nTmpLen += LOG_SIZEOFDATE;
	
	//	复制数据
	memcpy(szTmpBuf+nTmpLen, pBuf, nBufLen);
	nTmpLen += nBufLen;
	//	加密
	Crypt(szTmpBuf+LOG_SIZEOFSHORT, nLen, m_stHead.stInfo.szPassword);
	
	fwrite(szTmpBuf, nTmpLen, 1, m_fp);
	//fflush(m_fp);
	//	修改文件头
	m_stHead.stInfo.dwRecordCount ++;
	m_stHead.stInfo.dwValidLen += (unsigned int)(nBufLen+LOG_SIZEOFLOGHEAD+LOG_SIZEOFSHORT);
	
	return true;	
}

bool CKSLog::WritePack(void *pBuf, int nBufLen, char *pszPackHint)
{
	if(m_fp == NULL)
	{
		return false;
	}
	if(nBufLen >= LOG_MAXLINE-LOG_MAXPACKHINT)
	{
		return false;
	}
	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
#ifdef _MT
   m_mutex.Lock();
#endif

	//	在程序运行超过一天的时候可以按新日期重新写入日志文件
	CheckFileName();

	char	szHint[LOG_MAXLINE];
	memcpy(szHint, pszPackHint, LOG_MAXPACKHINT-1);
	memcpy(szHint+LOG_MAXPACKHINT-1, pBuf, nBufLen);
	bool bRet = WriteToFile(LOG_APPPACKID, szHint, nBufLen+LOG_MAXPACKHINT-1);
	//	修改文件头
	m_stHead.stInfo.dwPackCount++;
	SaveFileHead();

#ifdef _MT
   m_mutex.UnLock();
#endif
	
	return bRet;

}

bool CKSLog::WriteRawLog(short nAppID, void *pBuf, int nBufLen)
{
	if(m_fp == NULL)
	{
		return false;
	}
	if(nAppID < 0)
	{
		return false;
	}
	if(m_nOpenMode != LOG_OPENFORWRITE)
	{
		return true;
	}
	

/* ****** Updated by CHENYH at 2004-4-16 17:27:03 ****** 
	int	i;
   ST_LOGFILEAPP *pApp = m_stHead.stApp;
	for(i=0;i<LOG_APPMAXCOUNT;i++,)
	{
		if(m_stHead.stApp[i].nAppID == nAppID)
		{
			if(m_stHead.stApp[i].nReserve == LOG_APPREAD)
			{
				return true;
			}
			else
			{
				break;
			}
		}
	}
	if(i == LOG_APPMAXCOUNT)
	{
		return false;
	}
*/
	
#ifdef _MT
   m_mutex.Lock();
#endif

	//	在程序运行超过一天的时候可以按新日期重新写入日志文件
	CheckFileName();
   bool bRtn = WriteToFile(nAppID, pBuf, nBufLen);

	if(bRtn)
	{
	   // 修改文件头
	   SaveFileHead();
	}
	
#ifdef _MT
   m_mutex.UnLock();
#endif
	
	return bRtn;

}

bool CKSLog::WriteData(void *pBuf, int nBufLen)
{
   return WriteRawLog(LOG_APPDATAID, pBuf, nBufLen);
}

bool CKSLog::FlushToKLogFile()
{
   bool brtn;
#ifdef _MT
   m_mutex.Lock();
#endif
   brtn = SaveFileHead(true);
#ifdef _MT
   m_mutex.UnLock();
#endif
   return(true);
}

int CKSLog::RemoveOverdueKLogFile(int overdue)
{
   char filepath[1024];
   strcpy(filepath,m_szFilePath);
   AddSlash(filepath);
   return(RemoveOverdueFile(filepath,m_szFileExt,overdue));
}

void CKSLog::reverse(void *data, int len)
{
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;

   ASSERT(len<=16);

   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
   }
}

void CKSLog::ReverseLogHead(ST_LOGHEAD *head)
{
   int i;
   reverse(&(head->stInfo.dwHeadLen) ,sizeof(head->stInfo.dwHeadLen));
   reverse(&(head->stInfo.dwPackCount) ,sizeof(head->stInfo.dwPackCount));
   reverse(&(head->stInfo.dwRecordCount) ,sizeof(head->stInfo.dwRecordCount));
   reverse(&(head->stInfo.dwTotalLen) ,sizeof(head->stInfo.dwTotalLen));
   reverse(&(head->stInfo.dwValidLen) ,sizeof(head->stInfo.dwValidLen));
   reverse(&(head->stInfo.nAppCount) ,sizeof(head->stInfo.nAppCount));
   reverse(&(head->stInfo.wVer) ,sizeof(head->stInfo.wVer));
   ST_LOGFILEAPP *pApp = head->stApp;
   for (i=0;i<LOG_APPMAXCOUNT;i++,pApp++)
   {
      reverse(&(pApp->nAppID),sizeof(pApp->nAppID));
      reverse(&(pApp->nReserve),sizeof(pApp->nReserve));
   }
}
